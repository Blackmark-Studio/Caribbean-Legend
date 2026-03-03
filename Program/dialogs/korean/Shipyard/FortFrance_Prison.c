// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "말해라, 듣고 있다";
			link.l1 = "내가 착각했군. 잘 가라.";
			link.l1.go = "Exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "장교 나리, 당신 감옥에 폴케 들루크라는 남자가 있다고 들었소. 그를 석방할 수 있도록 내가 할 수 있는 일이 있소?";
                link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "장교 나리, 포크 들루크 죄수 건으로 또 왔소. 내가 그의 빚 권리를 샀으니 이 자를 석방해서 내게 넘기시오. 여기 그의 채무 서류가 있으니, 확인해 보시오.";
                link.l1.go = "Sharlie_3";
			}	
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Deluck"))
			{
				link.l1 = "안녕하세요, 장교님. 내 선원에 대해 좀 묻고 싶은데...";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_DeluckSvoboda"))
			{
				link.l1 = "여기 서류다, 이제 내 사람을 풀어 줘.";
                link.l1.go = "Del_DeluckSvoboda";
			}
			//<-- Миниквест "Делюк"
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "아, 그 선원 말인가? 우리 은행가에게 큰돈을 빌려 갚지 않았고, 심지어 도망치려다가 금방 잡혔지. 그때부터 쭉 감금되어 있고, 빚을 갚을 때까지 여기서 나가지 못할 거다.";
			link.l1 = "흠. 그런데 감옥에 있으면서 그걸 어떻게 한다는 거지?";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "난 신경 안 써, 나리.";
			link.l1 = "재밌군... 이 불쌍한 놈이 얼마나 빚졌지?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "모르겠소. 은행가에게 물어보면 자세한 내용을 알려줄 것이오.";
			link.l1 = "알겠소. 정보 고맙소, 장교.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskiper";
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", false);
			AddLandQuestMark(characterFromId("FortFrance_usurer"), "questmarkmain");
		break;
		
		case "Sharlie_3":
			Log_Info("You have given debt papers");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			DelLandQuestMark(npchar);
			dialog.text = "흠. 다 맞는 말이군. 정말로 그 죄수를 풀어주길 원하는 건가?";
			link.l1 = "그래. 나는 그놈이 빚을 갚아야 해서 필요하고, 그가 갚을 방법도 알고 있지.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "좋소, 거절할 이유는 없군. 델루크를 곧 이리로 데려오겠다. 하지만 경고해두지, 저 여우 같은 놈은 기회만 생기면 도망칠 테니, 그에 대해 환상은 갖지 말게.";
			link.l1 = "알겠소, 장교 나리. 이제 내 채무자를 데려가고 싶소.";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "예, 물론이지. 병장! 죄수를 데려와라! Folke Deluc, 이제 새로운 주인이 생긴 것 같군!";
			link.l1 = "...";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			DialogExit();
			// создаем штурмана
			sld = InitFolke("Folke", "Deluc");
			pchar.questTemp.Sharlie = "takeskiper";	
			ForceHeroAutolevel(sld);
			AddDialogExitQuestFunction("Del_Turma");
		break;
		//<-- Бремя гасконца
		
		//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
		case "Del_Deluck":
			DelLandQuestMark(npchar);
			dialog.text = "하! 이봐, 자네가 처한 곤경에 대한 소문이 생피에르에서 오래도록 회자될 거라네. 하지만 너무 마음에 두지 말게, 선장. 자네는 분명 운이 나빴던 희생자일 뿐이야. 들어오게, 그리고 걱정 말게. 자네 항해사가 이 대화에서 빠져나가진 못할 테니, 하하!";
			link.l1 = "우습군. 고맙소, 장교.";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("Del_prison");
		break;
		
		case "Del_DeluckSvoboda":
			dialog.text = "알겠습니다, 선장님. 그렇게 진행하겠습니다.";
			link.l1 = "...";
			link.l1.go = "Del_DeluckSvoboda_2";
			Log_Info("You have given debt papers");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			DelLandQuestMark(npchar);
		break;
		
		case "Del_DeluckSvoboda_2":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Del_DeluckSvoboda");
			
			sld = CharacterFromID("Folke");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_Folke_10";
			
			AddDialogExitQuestFunction("Del_Turma");
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
