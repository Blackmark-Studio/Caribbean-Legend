// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("무슨 질문인데?","뭘 원하지?");
			link.l1 = RandPhraseSimple("내 마음이 바뀌었어.'","지금은 할 말이 없어.");
		    link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin") && CheckAttribute(PChar, "questTemp.Terrapin.SJ_count"))
			{
				link.l1 = "나는 존스 씨를 찾고 있어. 그 사람 알아?";
				link.l1.go = "terrapin";
			}
		break;
		
		case "terrapin":
			if (sti(pchar.questTemp.Terrapin.SJ_count) == 5 || rand(9) == 1) // 10% или числом
			{
				dialog.text = "여기에는 존스라는 사람이 많아. 내가 아는 가장 유명한 존스는 폭스 대령 휘하의 부관인 벤자민 존스야. 그는 보통 연대 본부에서 방문객들을 맞이하지.";
				link.l1 = "그에게 몰리라는 이름의 여동생이 있나?";
				link.l1.go = "terrapin_yes";
			}
			else
			{
				dialog.text = LinkRandPhrase("어떤 존스를 찾는 거야? 내가 아는 존스만 해도 적어도 스무 명은 돼...","여기 존스가 너무 많아. 좀 더 구체적으로 말해 줘.","여기에는 존스도 많고, 존슨이나 잭슨도 많아. 좀 더 구체적으로 말해 줘야지, 알겠어?");
				link.l1 = "그에게는 몰리라는 이름의 누나가 있어. 듣자 하니 아주 보기 드문 미인이라더군.";
				link.l1.go = "terrapin_no";
			}
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_no":
			dialog.text = RandPhraseSimple(LinkRandPhrase("흠, 그건 도와줄 수 없을 것 같군.","아니, 난 그 사람 몰라.","푸하! 내가 아는 몰리 존스가 진짜 미인이라면, 폭스 대령은 신부님이지."),LinkRandPhrase("몰리 존스라는 이름 가진 사람 몇 명 알아. 그 중 한 명은 오빠가 있긴 한데... 네가 찾는 그 여자는 아니야. 원숭이랑 같이 산 놈만이 그녀를 '희귀한 미인'이라고 부를걸.","미안하지만, 내가 아는 모든 존스 집안에는 누이가 없어.","미안하지만, 도와줄 수 없어. 다른 사람한테 물어봐."));
			link.l1 = "알겠소. 번거롭게 해서 미안하오.";
			link.l1.go = "exit";
			pchar.questTemp.Terrapin.SJ_count = sti(pchar.questTemp.Terrapin.SJ_count)+1;
		break;
		
		case "terrapin_yes":
			dialog.text = "그래, 하지만 저 아이는 차라리 그의 남동생이었으면 더 나았겠지. 저렇게 우람한 계집애는 저 못생긴 얼굴 때문에 신랑을 못 찾을 거야.";
			link.l1 = "감사하오.";
			link.l1.go = "terrapin_yes_1";
		break;
		
		case "terrapin_yes_1":
			DialogExit();
			AddQuestRecord("Terrapin", "2");
			pchar.questTemp.Terrapin.Benjamin = true;
			DeleteAttribute(pchar, "questTemp.Terrapin.SJ_count");
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "내가 혹시 비밀 정보국에서 일한다고 생각하나 "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "음... 아니. 그럼 안녕히 가시오.";
			link.l1.go = "exit";
			link.l2 = "다른 질문 있나?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "내가 무슨 조사국이라도 되는 줄 알아? 몰라, 아무것도 모른다니까.";

            link.l1 = "너 정말 덜렁거리네! 꺼져.";
			link.l1.go = "exit";
			link.l2 = "그럼, 다른 질문 있나?";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
