using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI; // 이미지 사용을 할 수 있게 해준다.


public class Settings : MonoBehaviour
{
    public bool isJoyStick;
    public Image touchBtn, joyStickBtn;
    public Color blue;
    public PlayerCtrl playerCtrl_script;

    // playerctrl에도 추가
    GameObject mainView, playView;

    private void Start()
    {
        mainView = playerCtrl_script.mainView;
        playView = playerCtrl_script.playView;
    }

    //설정 버튼을 누르면 호출
    public void ClickSetting()
    {
        gameObject.SetActive(true);
        playerCtrl_script.isCantMove= true;
    }
    // 게임으로 돌아가기 버튼을 누름
    public void ClickBack()
    {
        gameObject.SetActive(false);
        playerCtrl_script.isCantMove = false;

    }

    //터치 이동을 누르면 호출될 함수
    public void ClickTouch()
    {
        isJoyStick = false;
        touchBtn.color = blue;
        joyStickBtn.color = Color.white;
    }

    public void ClickJoyStick()
    {
        isJoyStick = true;
        touchBtn.color = Color.white;
        joyStickBtn.color = blue;
    }

    // 게임 나가기 버튼을 누를 시 (미션 -> 메인 화면)
    public void ClickQuit()
    {
        mainView.SetActive(true);
        playView.SetActive(false);

        // 캐릭터 삭제
        playerCtrl_script.DestroyPlayer();
    }
} 
