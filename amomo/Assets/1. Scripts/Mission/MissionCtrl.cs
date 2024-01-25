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
    
    // �̼� �����ϸ� ȣ��
    public void MissionSuccess(CircleCollider2D coll)
    {
        missionCount++;
        guage.value = missionCount / 7f;

        // ������ �̼��� �ٽ� �÷��� ���� ���ϵ��� - ��Ŭ �ݶ��̴� 2D ����ؾ� �Ѵ�.
        coll.enabled = false;

        //��� �̼� ���� ���� üũ
        if(guage.value == 1)
        {
            text_anim.SetActive(true);
            Invoke("Change", 1f);

        }

    }

    //�̼� �ʱ�ȭ ���
    public void MissionReset()
    {
        text_anim.SetActive(false);

        guage.value = 0;
        missionCount = 0;

        //�ݶ��̴��� Ȱ��ȭ �ؾ� �Ѵ�.
        for(int i = 0; i < colls.Length; i++)
        {
            colls[i].enabled = true;

        }
    }

    // �̼� ��� ���� �� ȭ�� ��ȯ 
    public void Change()
    {
        mainView.SetActive(true);
        gameObject.SetActive(false);

        // ĳ���� ����
        FindObjectOfType<PlayerCtrl>().DestroyPlayer();
    }
}
