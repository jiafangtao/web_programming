/**
 * You are free to use this piece of code at no restriction.
 * If it works, it's written by jiab; Otherwise I don't know who wrote it.
 * The day 2019/3/5 is another beautiful day. Happy coding.
 */

import org.apache.commons.io.FilenameUtils;

import java.io.File;

public class Main {

    public static void main(String args[]) {

        System.out.println("====== FilenameUtils.getFullPath ========");

        String [] filePaths = new String[3];
        filePaths[0] = "c:\\work\\git\\adsk\\";
        filePaths[1] = "/home/centos/downloads" + File.separator + "result";
        filePaths[2] = "/tmp/a.tmp";

        for(String filePath : filePaths) {
            String output = FilenameUtils.getFullPath(filePath);

            System.out.println("Path          : " + filePath);
            System.out.println("getFullPath   : " + output);
            System.out.println();
        }

        final String zipFilePath = "/tmp/dts/downloads/dts-1234.zip";
        final String sanitized = FilenameUtils.getFullPath(zipFilePath)
                + FilenameUtils.getName(zipFilePath);

        System.out.println(zipFilePath);
        System.out.println(FilenameUtils.getFullPath(zipFilePath));
        System.out.println(sanitized);
    }
}
