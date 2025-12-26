// заместитель Маркуса Тиракса в Ла Веге
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = NPCStringReactionRepeat("나에게 할 말이 있소? 없소? 그럼 당장 나가시오!","내가 충분히 설명했으니, 더 이상 귀찮게 하지 마시오.","분명히 말했건만, 자꾸 나를 성가시게 하는군!","옳소, 이 무례함에 슬슬 지쳐가는군.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("나는 이제 떠나겠소.","Sure"+npchar.name+"...","죄송합니다, "+npchar.name+"...","이런...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", 다시 보게 되어 반갑소! 무슨 일로 왔소?","또 무엇이오?"," 또 왔나? 할 일 없으면 남을 귀찮게 하지 마시오!","그대가 훌륭한 분임을 알고 있소. 하지만 더 이상 그대와 이야기하지 않겠소.","repeat",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("아무것도 아닙니다. 그냥 뵙고 싶었습니다.","아무것도...","좋소, "+npchar.name+", 미안하오...","젠장, 이 모든 게 내 잘못이야...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("도둑질이라고?! 진심이오?! 이제 끝났구나, 이 친구...","잠깐, 이게 뭐야? 결국 도둑이었군! 이제 끝장이야...");
			link.l1 = LinkRandPhrase("제기랄!","카라암바!!","젠장!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("가거라","비켜라 ")+" 여기서부터요!","내 집에서 나가시오!");
			link.l1 = "이런...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "값싼 말로 나를 귀찮게 하지 마시오. 다음번에는 결과가 마음에 들지 않을 것이오...";
        			link.l1 = "알겠습니다.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "끝났으니, 더 이상 말하지 마시오.";
			link.l1 = RandPhraseSimple("원하시는 대로...","좋소, 그럼...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "나에게 더 많은 존경을 표하고 무례를 그만두기를 바라오. 그렇지 않으면 그대를 죽여야만 하오. 그것은 매우 불쾌한 일이 될 것이오.";
        			link.l1 = ""+npchar.name+", 확실히 그렇게 하겠습니다.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ_1":
			dialog.text = "아, 그대였군, 드 모르 나리. 이런, 놀랍구려. 바다의 악마에 맹세코, 그대의 도착이 오랜만에 일어난 가장 흥미로운 일이오, 젠장.";
			link.l1 = "그대도 반갑소, 벤상. 마을을 다스리는 일이 즐거운가?";
			link.l1.go = "PZ_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_2":
			dialog.text = "내가 어떻게 그러겠소? 나는 선장이오, 그것도 제법 뛰어난 선장이지, 썩을 회계사 따위가 아니오. 그리고 나는 마커스의 사자가 새 항해를 위해 나를 부르러 오기를 크리스마스를 기다리는 것보다 더 오래 기다렸소, 젠장할 저주 같으니!";
			link.l1 = "크리스마스와 저주를 한 문장에 담다니, 참 대단하군. 그래, 나는 자네가 부럽지 않네. 하지만 많은 이들이 자네의 지금 위치를 탐낼 걸세. 하지만 나는 사업 때문에 자네를 찾아왔네, 벤상.";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "용건이 뭐요?! 어서 말해보시오 - 무슨 생각이라도 했소? 괜찮은 소식이라도 있소? 이 지긋지긋한 계산에 지쳐 심심함을 달래려면 이 동네 술창고라도 다 비워버릴 판이오.";
			link.l1 = "글쎄요, 사실은 당신께 여쭙고 싶은 것이 있을 뿐입니다, 그 이상은 아닙니다.";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "젠장! 좋아, 듣고 있네, Charles.";
			link.l1 = "여인이 당신을 찾아온 적이 있소? 아니면 라 베가에서 본 적이 있소? 그녀는 벨 에투알이라는 이름으로 불리지만, 그건 가명일 뿐이니 다른 이름으로 자신을 소개했을 수도 있소. 중요한 것은 그녀가... 그녀가 황색 피부를 가졌다는 점이오. 하지만 노예나 노동자가 아니라, 부유한 여인이오.";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			dialog.text = "피부는 누렇지만, 부자라니? 우리 여기서는 그런 사람을 본 적이 없소, 단 한 번도! 역시나 흥미로운 삶을 살고 있구려, 드 모르 나리! 거의 부러울 지경이오.";
			link.l1 = "그런가... 자네 시간 내줘서 고맙네, Vensan. 더 이상 회계 일 방해하지 않겠네, 허허.";
			link.l1.go = "Exit";
			
			AddQuestRecord("PZ", "40");
			
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1 = "location";
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PZ_SetHeavyFrigate.win_condition = "PZ_SetHeavyFrigate";
			DelMapQuestMarkCity("LaVega");
			AddMapQuestMarkCity("PortPax", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
		break;
	}
}
