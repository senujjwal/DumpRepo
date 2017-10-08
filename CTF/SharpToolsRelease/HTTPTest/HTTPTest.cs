using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Net;
using IntelligentStreaming.SharpTools;

namespace HTTPTest
{
    class HTTPTest
    {
        static HTTPWorker http = new HTTPWorker();
        static HttpWebResponse rsp = null;

        static void Main(string[] args)
        {
            http.Url = "https://btsusqualifiersexternalwebchallenges.azurewebsites.net/kakjsskkskh/";
            http.PersistCookies = true; 
            rsp = http.SendRequest();

            string resp = http.ResponseText;

            Console.WriteLine(resp);
            string vs = ExtractString(resp,"id=\"__VIEWSTATE\" value=\"" ,"\" />");
            string vsg = ExtractString(resp,"id=\"__VIEWSTATEGENERATOR\" value=\"","\" />");
            
            http.Url = "https://btsusqualifiersexternalwebchallenges.azurewebsites.net/kakjsskkskh/";
            http.Type = HTTPRequestType.Post;
            http.AddValue("__VIEWSTATE", vs);
            http.AddValue("__VIEWSTATEGENERATOR", vsg);
            
            rsp = http.SendRequest();
            resp = http.ResponseText;
            Console.WriteLine(resp);
          /*

            http.Url = "https://btsusqualifiersexternalwebchallenges.azurewebsites.net/kakjsskkskh/";
            http.PersistCookies = true; 
            rsp = http.SendRequest();
            http.Url = "https://btsusqualifiersexternalwebchallenges.azurewebsites.net/kakjsskkskh/";
            string resp = http.ResponseText;
            Console.WriteLine(resp);
            
            int cnt = http.Cookies.Count;
            for(int i = 0; i < cnt; i++)
            {
                Console.WriteLine(http.Cookies[i].ToString());
            }
            */
                Console.Read();
        }

        static string ExtractString(string StringToSearch, string Prefix, string Postfix)
        {
            int startPos = StringToSearch.IndexOf(Prefix) + Prefix.Length;
            int endPos = StringToSearch.IndexOf(Postfix, startPos);

            return StringToSearch.Substring(startPos, endPos - startPos);
        }


        static string MakeGETRequest(string URL)
        {
            http.Url = URL;
            rsp = http.SendRequest();

            if(rsp.StatusCode == HttpStatusCode.OK)
            {
                return http.ResponseText;
            }
            else
            {
                return rsp.StatusCode.ToString();
            }
        }

     
        static void Main2(string[] args)
        {
            HTTPWorker http = new HTTPWorker();
            HttpWebResponse rsp = null;

            string username;
            string password;

            string uriLogin = "http://yoursite/login.php";
            string uriUpload = "http://yoursite/upload.php";

            string uploadFile1 = @"someFile.jpg";
            string uploadFile2 = @"someFile.txt";

            Console.Write("Enter username: ");
            username = Console.ReadLine();
            Console.Write("Enter password: ");
            password = Console.ReadLine();

            // Login example

            http.Url = uriLogin;
            http.Type = HTTPRequestType.Post;
            http.AddValue("username", username);
            http.AddValue("password", password);

            try
            {
                rsp = http.SendRequest();
            }
            catch (WebException ex)
            {
                Console.WriteLine(ex.Message);
                return;
            }

            if (rsp.StatusCode == HttpStatusCode.OK)
            {
                if (http.ResponseText.Contains("Username or password incorrect"))
                    Console.WriteLine("Your login details were wrong.");
                return;
            }

            if (rsp.StatusCode != HttpStatusCode.Found)
            {
                Console.WriteLine("Got unexpected status code '{0}' when trying to login.", rsp.StatusCode);
                return;
            }

            string locationHeader = rsp.GetResponseHeader("Location");

            Console.WriteLine("Logged in successfully");

            // Upload example

            http.Url = uriUpload;
            http.Type = HTTPRequestType.MultipartPost;
            
            // Allow auto-redirect so we can parse the page to see if we were successful
            http.RequestObject.AllowAutoRedirect = true;
            http.RequestObject.KeepAlive = true;
            http.RequestObject.Headers.Add("Pragma", "no-cache");

            http.AddValue("someValue", "abc");
            http.AddValue("someValue2", "123");

            http.AddFile("imageFile", uploadFile1);
            http.AddFile("textFile", uploadFile2);

            try
            {
                rsp = http.SendRequest();
            }
            catch (WebException ex)
            {
                Console.WriteLine(ex.Message);
                return;
            }

            Console.WriteLine("Request URI: {0}", http.Url);

            Console.WriteLine("Cookies:");
            foreach (Cookie c in http.Cookies)
                Console.WriteLine(c.ToString());

            if (rsp.StatusCode != HttpStatusCode.OK)
            {
                Console.WriteLine("Upload attempt returned {0}", rsp.StatusCode);
                if (rsp.StatusCode == HttpStatusCode.Found)
                    Console.WriteLine(rsp.GetResponseHeader("Location"));
            }
            else
                Console.WriteLine("Received 200 OK from upload attempt");

            if (http.ResponseText.Contains("Upload failed!"))
            {
                Console.WriteLine("The upload failed due to an error on the form.");
            }
            else
            {
                Console.WriteLine("Upload successful!");
            }
        }
    }
}
