const createScene =  () => {
    const scene = new BABYLON.Scene(engine);

    /**** Set camera and light *****/
    const camera = new BABYLON.ArcRotateCamera("camera", -Math.PI / 2, Math.PI / 2.5, 10, new BABYLON.Vector3(0, 0, 0));
    camera.attachControl(canvas, true);
    const light = new BABYLON.HemisphericLight("light", new BABYLON.Vector3(1, 1, 0));

    const box = BABYLON.MeshBuilder.CreateBox("box", {});
    box.position.y = 0.5;

    console.info(box.position);
    
    const ground = BABYLON.MeshBuilder.CreateGround("ground", {width:10, height:10});

    return scene;
}
