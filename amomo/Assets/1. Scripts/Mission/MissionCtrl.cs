using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MissionCtrl : MonoBehaviour
{
    public GameObject text_anim,mainView;
    int missionCount;
    public CircleCollider2D[] colls;
    public Slider guage;
    
    // 미션 성공하면 호출
    public void MissionSuccess(CircleCollider2D coll)
    {
        missionCount++;
        guage.value = missionCount / 7f;

        // 성공한 미션은 다시 플레이 하지 못하도록 - 써클 콜라이더 2D 사용해야 한다.
        coll.enabled = false;

        //모든 미션 성공 여부 체크
        if(guage.value == 1)
        {
            text_anim.SetActive(true);
            Invoke("Change", 1f);

        }

    }

    //미션 초기화 기능
    public void MissionReset()
    {
        text_anim.SetActive(false);

        guage.value = 0;
        missionCount = 0;

        //콜라이더도 활성화 해야 한다.
        for(int i = 0; i < colls.Length; i++)
        {
            colls[i].enabled = true;

        }
    }

    // 미션 모두 성공 시 화면 전환 
    public void Change()
    {
        mainView.SetActive(true);
        gameObject.SetActive(false);

        // 캐릭터 삭제
        FindObjectOfType<PlayerCtrl>().DestroyPlayer();
    }
}
