using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MainMenu : MonoBehaviour
{
    public GameObject missionView,killView;
    // 게임 종료 버튼 누르면 호출
    public void ClickQuit()
    {
        // 유니티 에디터
#if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = false; 

        // 안드로이드
#else
        Application.Quit();
#endif

    }
    // 미션 버튼 누르면 호출
    public void ClickMission()
    {
        gameObject.SetActive(false);
        missionView.SetActive(true);
        //캐릭터가 메인 화면에서 보이는 것 때문에 캐릭터를 지운 뒤 여기서 읽어 온다.
        GameObject player = Instantiate(Resources.Load("Character"), new Vector3(0,-2,0),Quaternion.identity)as GameObject;
        // PlayerCtrl 스크립트를 가져와서 메인 뷰에 게임 오브젝트를 넣는다.
        player.GetComponent<PlayerCtrl>().mainView = gameObject;
        player.GetComponent<PlayerCtrl>().playView = missionView;
        player.GetComponent<PlayerCtrl>().isMission = true;

        missionView.SendMessage("MissionReset");
    }    
    // 킬 버튼 누르면 호출
    public void ClickKill()
    {
        gameObject.SetActive(false);
        killView.SetActive(true);
        //캐릭터가 메인 화면에서 보이는 것 때문에 캐릭터를 지운 뒤 여기서 읽어 온다.
        GameObject player = Instantiate(Resources.Load("Character"), new Vector3(0,-2,0),Quaternion.identity)as GameObject;
        // PlayerCtrl 스크립트를 가져와서 메인 뷰에 게임 오브젝트를 넣는다.
        player.GetComponent<PlayerCtrl>().mainView = gameObject;
        player.GetComponent<PlayerCtrl>().playView = killView;
        player.GetComponent<PlayerCtrl>().isMission = false;

        killView.SendMessage("KillReset");
    }
}
