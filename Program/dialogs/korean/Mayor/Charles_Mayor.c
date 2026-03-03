// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무엇을 원하시오? 물어보시오.","듣고 있소, 무슨 질문이오?"),"두 번째로 다시 묻는 것이오...","세 번째로 다시 묻는군요...","이게 언제 끝나겠소?! 나는 식민지의 일을 처리하느라 바쁜 사람이오, 그런데도 아직도 뭘 더 묻고 있단 말이오!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소...","지금은 아니오. 장소와 시간이 맞지 않소."),"그렇소... 하지만 나중에, 지금은 아니오...","물어보겠소... 하지만 조금 있다가...","죄송합니다, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "saga" && !CheckAttribute(npchar, "quest.saga"))
			{
				link.l1 = "슈발리에 드 푸앵시를 뵙고 싶습니다. 제 형제의 빚에 관한 일입니다.";
                link.l1.go = "puancie";
			}
			//<-- Бремя гасконца
		break;
		
		case "puancie":
			dialog.text = "아하, 그렇군. 그 빚에 대해서는 알고 있소... 필요한 금액을 가지고 왔소?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "물론이지요. 달리 어찌 되었겠소?";
				link.l1.go = "puancie_1";
			}
			else
			{
				link.l1 = "아니오, 아직 그만한 돈은 없습니다.";
				link.l1.go = "puancie_exit";
			}
		break;
		
		case "puancie_exit":
			dialog.text = "그럼 그것을 구해 오시오, 그리고 슈발리에 나리를 귀찮게 하지 마시오.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "puancie_1":
			dialog.text = "그렇다면 오른쪽 문으로 들어가시오. 그 다음 슈발리에께서 당신을 맞이하실 것이오.";
			link.l1 = "감사합니다!";
			link.l1.go = "puancie_2";
		break;
		
		case "puancie_2":
			DialogExit();
			npchar.quest.saga = "true";
			bDisableFastReload = true;//закрыть переход
			LocatorReloadEnterDisable("Charles_townhall", "reload1_back", true);//чтобы не вышел
			LocatorReloadEnterDisable("Charles_townhall", "reload3", false);//откроем вход к Пуанси
			ref sld = characterFromId("Puancie");
			ChangeCharacterAddressGroup(sld, "Charles_Roomtownhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			sld.dialog.currentnode = "saga";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
