// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 일로 왔소? 물어보시오.","듣고 있소, 무슨 질문이오?"),"두 번째로 다시 묻는 것이오...","세 번째로 다시 묻는 것이오...","이게 언제 끝나겠소?! 나는 식민지의 업무로 바쁜 몸이오, 그런데도 아직도 뭔가를 묻고 있구려!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소...","지금은 아니오. 장소와 시간이 맞지 않소."),"그렇소... 하지만 나중에, 지금은 아니오...","물어보겠소... 하지만 조금 있다가...","죄송합니다, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "마르티니크에서 이익이 되는 거래를 마치고 이제 블루웰드로 항해할 계획입니다.\n귀하의 식민지에서 레드우드와 커피를 구입하고 싶습니다.\n게다가 제 브리그는 제가 원하는 만큼의 화물을 실을 수 없어, 이곳 조선소에서 플루이트선을 구입해야 합니다.\n이 일들에 대해 도움을 받을 수 있겠습니까?";
                link.l1.go = "MayorDone";
            }
		break;
		
		case "MayorDone":
			dialog.text = "제 도움이 필요하십니까? 우리 상인은 매우 정직한 사람이니, 당신을 속이려 할 리 없소. 플루트에 관해서는 선박장과 상의해 보시오, 그가 이 일에 도움을 줄 것이오. 그래도 어려움이 있다면 언제든 나를 찾아오시오. 나는 우리 식민지와의 무역 관계 증진에 관심이 많으니, 전폭적으로 지원하겠소.\n그리고 오늘 밤 연회를 준비하고 있소, 브리지타운의 내로라하는 인사들이 모두 참석할 것이오. 당신도 오시지요, 선장.";
			link.l1 = "초대해 주셔서 감사하오나, 유감스럽게도 너무 바쁘오. 안녕히 계시오, 그리고 도와주셔서 다시 한 번 감사드리오!";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-8");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
			pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
			DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				//if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
				//else AddDialogExitQuestFunction("CreateVanBergInWorld");
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
