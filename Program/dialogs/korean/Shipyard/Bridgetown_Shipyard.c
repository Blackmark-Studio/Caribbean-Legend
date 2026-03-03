// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요?"),"조금 전에 나에게 뭔가 물어보려고 했지...","내 조선소나 이 마을 어디에서도 그렇게 호기심 많은 사람들은 처음 봤소.","질문이 왜 이렇게 많아? 내 일은 배를 만드는 거야. 그 일부터 처리하자.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"음, 내 기억이 다 어디로 갔지...","흠, 그래...","계속해...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "나는 커피를 싣고 블루웰드로 가는 길이야. 더 많은 상품을 사고 싶은데, 문제는 이거야. 내가 전쟁광한테 산 이 브리그에는 무거운 대포가 무려 24문이나 달려 있어. 전쟁하러 가는 것도 아닌데 말이지. 이 대포 전부 당신한테 팔고, 6파운드포 12문만 사고 싶어. 그 정도면 해적쯤은 충분히 쫓아낼 수 있거든. 남는 공간은 전부 상품으로 채울 생각이야.";
                link.l1.go = "ShipyardDone";
			}
		break;
		
		case "ShipyardDone":
			dialog.text = "그래, 팔아도 된다. 6파운더는 항상 충분히 있지만, 대포는 항상 부족해서 골치야. 다들 자꾸 사가고, 아무도 팔려고 하지 않거든. 완전히 망가지지 않는 한 말이지. 그러니 만약 아직 쓸 만하다면, 제값 쳐주지.";
			link.l1 = "이런 젠장, 대단하군! 바로 명령 내릴게.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-10");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
			DelMapQuestMarkCity("Bridgetown");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				//if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
				//else AddDialogExitQuestFunction("CreateVanBergInWorld");
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
