package main

// Reference: https://blog.csdn.net/qq_44336275/article/details/113574591

import (
    "encoding/json"
    "fmt"
)

type Status int

func (s Status) String() string {
	return statusMap[s]
}

/*
func (s *Status) MarshalJSON() ([]byte, error) {
	return [] byte("\"" + statusMap[*s] + "\""), nil
}

func (s *Status) UnmarshalJSON(b []byte) error {

	tmp := string(b)
	fmt.Printf("UnmarshalJSON 1... tmp=%s\n", tmp)
	fmt.Printf("%i\n", statusReprMap[tmp])
	*s = statusReprMap[tmp]

	fmt.Printf("UnmarshalJSON 2... %d\n\n", *s)

	return nil
}
*/

const (
    Running Status = iota
	Waiting
	Pending
	Killed
	Terminated
	Succeeded
	Failed
	Unknown
)

var statusMap = map[Status]string{
	Waiting:    "Waiting",
	Running:    "Running",
	Pending:    "Pending",
	Killed:     "Killed",
	Terminated: "Terminated",
	Succeeded:  "Succeeded",
	Failed:     "Failed",
	Unknown:    "Unknown",
}

var statusReprMap = map[string]Status {
	"Waiting":    Waiting,
	"Running":    Running,
	"Pending":    Pending,
	"Killed":     Killed,
	"Terminated": Terminated,
	"Succeeded":  Succeeded,
	"Failed":     Failed,
	"Unknown":    Unknown,
}

// PSStatus defines status for process
type Process struct {
	PId       int64 `json:"pid"`
	Status    Status `json:"status"`
}

func (p Process) MarshalJSON() ([]byte, error) {
	type ProcessAlias Process

	res, err := json.Marshal(struct {
		ProcessAlias
		Status string `json:"status"`
	}{
		ProcessAlias: ProcessAlias(p),
		Status: statusMap[p.Status],
	})

	if err != nil {
		return nil, err
	}
	
	return res, nil
}

func (p *Process) UnmarshalJSON(b []byte) error {
	type ProcessAlias Process

	pw := struct {
		ProcessAlias
		Status string `json:"status"`
	}{}

	err := json.Unmarshal(b, &pw)
	if err != nil {
		return err
	}
	
	*p = Process(pw.ProcessAlias)
	p.Status = statusReprMap[pw.Status]
	return nil
}


func (p Process) String() string {
	return fmt.Sprintf("pid: %v, status: %v", p.PId, p.Status)
}

func main() {

    p := Process{
        PId: 9999,
        Status: Succeeded,
    }

    fmt.Printf("1111111111111111 %v\n", p.Status);

    //temp := []byte("testing")
    //fmt.Printf("%s\n", temp)

    res, err := json.Marshal(p)
    if err != nil {
        fmt.Printf("Marshal Error: %s\n", err)
    } else {
        fmt.Printf("%s\n", res)
    }

    ps2 := Process{
    	PId: 1,
    	Status: Unknown,
    }
    err = json.Unmarshal(res, &ps2)
    if err != nil {
    	fmt.Printf("Unmarshal Error: ", err)
    } else {
	    fmt.Printf("%v\n", ps2)
    }

    ps3 := Process{}
    s := `{"pid": 888, "status": "Waiting"}`
	fmt.Printf("============ parse %v ====================\n", s)
	json.Unmarshal([]byte(s), &ps3)
	fmt.Printf("Result: %v\n", &ps3)
}
