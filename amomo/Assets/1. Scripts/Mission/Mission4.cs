using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class Mission4 : MonoBehaviour
{
    // ��ư�� ��������
    public Transform numbers;
    public Color blue;
    Animator anim;
    PlayerCtrl playerCtrl_script;
    MissionCtrl missionCtrl_script;

    int count;
    // Start is called before the first frame update
    void Start()
    {
        //getcomponent�� �׳� ���� �ȵȴ�. ���⼭ �ִϸ��̼��� ���� ���Ͽ� �ִ�.
        anim = GetComponentInChildren<Animator>();
        missionCtrl_script = FindObjectOfType<MissionCtrl>();

    }

    //�̼� ����
    public void MissionStart()
    {
        anim.SetBool("IsUp", true);
        playerCtrl_script = FindObjectOfType<PlayerCtrl>();
        // ��� ��ư�� ���� �Ͼ������ �ʱ�ȭ
        for(int i = 0; i < numbers.childCount; i++)
        {
            numbers.GetChild(i).GetComponent<Image>().color = Color.white;
            numbers.GetChild(i).GetComponent<Button>().enabled = true; // ��ư �ʱ�ȭ
        }

        // ���� ���� ��ġ
        for(int i = 0; i < 10; i++)
        {
            //���δ� ���δ�.
            Sprite temp = numbers.GetChild(i).GetComponent<Image>().sprite;

            int rand = Random.Range(0,10);
            numbers.GetChild(i).GetComponent<Image>().sprite = numbers.GetChild(rand).GetComponent<Image>().sprite;
            numbers.GetChild(rand).GetComponent<Image>().sprite = temp;

        }
        count = 1;
    }

    //x��ư ������ ȣ��
    public void ClickCancle()
    {
        anim.SetBool("IsUp", false);
        playerCtrl_script.MissionEnd();
    }

    // ���� ��ư ������ ȣ�� �� �Լ�
    public void ClickNumber()
    {
        if(count.ToString() == EventSystem.current.currentSelectedGameObject.GetComponent<Image>().sprite.name)
        {// ���ʴ�� ���ڸ� ���������� �Ǵ�
            // ��ư �� ����
            EventSystem.current.currentSelectedGameObject.GetComponent<Image>().color = blue; // �ٲٴ°� ����� �ʱ�ȭ�� �����ؾ� �Ѵ�.

            // ���������� ��ư ��Ȱ��ȭ
            EventSystem.current.currentSelectedGameObject.GetComponent<Button>().enabled = false;//�ٽ� ���� �� ����! �׷� �ʱ�ȭ�� !

            count++;

            // ���� ���� üũ
            if(count == 11)
            {
                Invoke("MissionSuccess",0.2f); // 0.2�ʵ� ���� 
            }
        }
    }


    // �̼� �����ϸ� ȣ��� �Լ�
    public void MissionSuccess()
    {
        missionCtrl_script.MissionSuccess(GetComponent<CircleCollider2D>());

        ClickCancle();
    }
}
