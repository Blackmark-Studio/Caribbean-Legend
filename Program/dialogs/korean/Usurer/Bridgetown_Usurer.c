// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있습니까?","무엇을 도와드릴까요?"),"얼마 전에 나한테 그 질문을 하려고 했었지...","그래, 맞지... 또 뱅뱅 도는 거냐?","이봐, 여기서 재정은 내가 맡고 있어, 질문엔 답하지 않아...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없소."),"으음, 내 기억이 다 어디로 갔지...","맞췄군, 미안하네...","알겠습니다...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "나는 와인 화물을 싣고 블루웰드로 가는 중이오. 그런데 어떤 선장에게서 블루웰드에서 커피 수요가 늘었다는 소문을 들었소, 이유는 잘 모르겠지만 말이오. 그래서 와인을 팔고 대신 커피를 사볼까 생각 중인데, 내 창고를 가득 채울 만큼 돈이 부족하오. 혹시 이자로 돈을 좀 빌릴 수 있겠소?";
                link.l1.go = "UsurerDone";
            }
		break;
		
		case "UsurerDone":
			dialog.text = "신용이 좋은 상인이라면 문제없지. 얼마가 필요한가? 함께 논의해 보세.";
			link.l1 = "알겠습니다. 창고에 짐을 싣고 남은 공간이 얼마나 되는지 세어보겠습니다. 그리고 부족한 양을 계산한 뒤, 필요하다면 다시 찾아오겠습니다.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-13");
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
