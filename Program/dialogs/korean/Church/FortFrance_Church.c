// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데, "+GetSexPhrase("아들아","내 딸")+"?","물어보시오, 듣고 있네..."),"듣고 있다, 이제 말해라. "+GetSexPhrase("아들아","내 딸")+"...","세 번째로, "+GetSexPhrase("아들아","내 딸")+", 필요한 것이 있으면 말하시오.","성직자는 할 일이 많으니 네가 방해하고 있군, "+GetSexPhrase("아들아","내 딸")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 아니오, 신부님..."),"드릴 말씀이 없소, 미안하오.","나중에 물어볼게요. 용서해 주십시오, 신부님.","실례합니다, 신부님...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "choose" && !CheckAttribute(npchar, "quest.LongHappy"))
			{
				link.l1 = "신부님, 저는 베누아 아빠트를 찾고 있습니다. 그분께 급한 용무가 있는데요. 어디서 그분을 만날 수 있는지 알려주실 수 있습니까?";
				link.l1.go = "LH_church";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_church":
			dialog.text = "베누아 아빠트께서 신대륙의 스페인 가톨릭 선교단 대표들과 교회 업무로 도시를 떠나셨소. 자세한 내용은 모르지만, 베누아 아빠트께서 꽤 오래 자리를 비우셨으니 협상이 길어졌거나, 가는 길에 무슨 일이 생긴 것 같소. 우리 모두 불안하지만, 그저 기도하며 소식을 기다릴 수밖에 없소.";
			link.l1 = "모든 일이 순조로울 거라고는 생각하지 않습니다. 신부님, 베누아 수도원장이 정확히 어디로 갔는지 말씀해 주실 수 있습니까? 최대한 빨리 그를 찾아야 합니다.";
			link.l1.go = "LH_church_1";
		break;
		
		case "LH_church_1":
			dialog.text = "유감이지만, 아들아, 내가 해줄 수 없구나. 내가 알기로 베누아 수도원장은 신(新) 스페인의 주교와 종교재판소의 고위 성직자인 빈첸초 팔로티 신부와 협상하러 갔지만, 어디서 만남이 열릴지는 말하지 않았단다.";
			link.l1 = "이 정도면 충분합니다, 신부님, 감사합니다. 팔로티 신부를 어떻게든 알고 있습니다... 산티아고에서 한번 둘러보겠습니다.";
			link.l1.go = "LH_church_2";
		break;
		
		case "LH_church_2":
			DialogExit();
			npchar.quest.LongHappy = "true";
			LongHappy_GoToSantiago();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
