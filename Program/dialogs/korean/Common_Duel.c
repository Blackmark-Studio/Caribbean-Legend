//navy 26.07.06
//генератор дуэлей...
//в диалоге НПС делаем линк с проверкой флага оскорбления... по нему переход на "outraged"
//если НПС сделал что-то ГГ (продажа фальшивки) или ГГ наехал на НПС, вешаем на него флаг.
//для некоторых, например ПГГ, можно делать переход сразу на вызов: "let_s_duel"
void ProcessDuelDialog(ref NPChar, aref Link, aref NextDiag)
{
	int iHour;
	string sLocation;

	//флаг убираем
	DeleteAttribute(NPChar, "Outrage");
    switch (Dialog.CurrentNode)
	{
	case "outraged":
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("감히 나를 모욕하다니, 이 망할 놈아?!","네 말값을 톡톡히 치르게 해주마!"),RandPhraseSimple("내 명예를 모욕했군, "+GetAddress_Form(NPChar)+"! 그리고 그 대가를 치르게 될 거야.","감히 뭐라고 했어? 당장 네 말 취소해!"));

		//это такая засада.. чтобы читали текст :)
		MakeRandomLinkOrderTwo(link, 
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("Ha?! I don't even want to stain my sword with your blood!", "Ha?! I don't even want to stain my sword with your blood!"), 
				RandPhraseSimple("I am always at your service!", "I am not going to choose words while speaking with the rabble!")), "outraged_1",
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("I didn't mean it!", "I fired up..."), 
				RandPhraseSimple("That was a mistake. I am sorry.", "I took you for someone else, " + GetAddress_FormToNPC(NPChar) + ". Please forgive me.")), "change_mind");
		break;

	case "outraged_1":
		Dialog.Text = NPCharRepPhrase(NPChar,RandPhraseSimple("네 귀를 잘라버릴 거야!","네 심장을 도려내주마!"),RandPhraseSimple("네 변명을 듣게 되길 바란다, 아니면 내가 나 자신을 제어할 수 있을지 장담 못 해!","무슨 뜻인지 알아... 알아?"));

		MakeRandomLinkOrderTwo(link,
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("I hope that your saber is as swift as your tongue!", "My blade will speak for me."), 
				RandPhraseSimple("I challenge you to a duel!", "That's a matter of honor!")), "let_s_duel",
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("I think I am not ready yet!", "Think, we shouldn't get excited! These are words only!"), 
				RandPhraseSimple("I remembered, I am waiting. All blessings...", "Ah! Seems, my ship is sailing already. Bye.")), "change_mind");
		break;

	case "let_s_duel":
		//проверка на начатые дуэли.
		if (CheckAttribute(PChar, "questTemp.duel.Start") && sti(PChar.questTemp.duel.Start))
		{
			Dialog.Text = "먼저 다른 이들과 볼일을 끝내고, 그 다음에 우리 얘기하자.";
			if (PChar.questTemp.duel.enemy == NPChar.id)
			{
				Dialog.Text = "우리는 이미 합의에 도달했소.";
			}
			link.l1 = RandSwear()+"아, 내가 어찌 잊을 수 있겠어...";
			link.l1.go = "exit";
			break
		}
		//может отказаться.
		if (rand(100) < 30)
		{
			Dialog.Text = RandPhraseSimple("결투?! 꺼져, 너한테 시간 낭비할 가치도 없어.","결투? 너 따위가 그런 영광을 받을 자격은 없어! 꺼져!");
			link.l1 = RandPhraseSimple("좋아...","기다릴 수밖에 없겠군...");
			link.l1.go = "exit";
/**/
			//можно дать возможность драться полюбому :)			
			if (rand(100) < 30)
			{
				link.l1 = RandPhraseSimple("그렇게 생각해? 너무 확신하지 마라, 이 자식아!!!","정말이냐?! 네 피가 무슨 색인지 직접 확인해주지!");
				link.l1.go = "fight_right_now";
			}
/**/
			break;
		}

		//согласен.
		Dialog.Text = RandPhraseSimple("결투라니, 좋아. 우리 무기는 검과 권총이 될 거다.","너 칼이나 제대로 쥘 수는 있냐?");
		link.l1 = RandPhraseSimple("넌 무릎 꿇고 자비를 빌게 될 거다.","내 손으로 직접 네 놈을 목 졸라 죽여주겠다, 이 악당아!");
		link.l1.go = "land_duel";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			Dialog.Text = RandPhraseSimple(Dialog.Text+" 아니면 우리가 나가서 누가 누군지 직접 확인해 보자!","결투라고?!! 하, 널 벌레처럼 짓밟아 주지! 어떻게 죽고 싶은지 골라 봐!");
			link.l2 = RandPhraseSimple("바다에서는 내가 최고다.","내 배가 네 낡은 배 따위는 쉽게 침몰시킬 거야!");
			link.l2.go = "sea_duel";
		}
		link.l3 = "생각이 바뀌었어...";
		link.l3.go = "change_mind";
		break;

	//дуэль на подводных лодках :))))
	case "sea_duel":
		Dialog.Text = RandPhraseSimple("항구에 네 배가 안 보이는데...","최소한 낡은 고물 배라도 구할 때까지 꺼져!");
		link.l1 = RandPhraseSimple("내 실수군...","그럼 나는 너를 두고 떠난다.");
		link.l1.go = "exit";
		if (pchar.location.from_sea == GetCurrentTown() + "_town")
		{
			Dialog.Text = "좋아, 내가 만 앞바다 출구에서 기다리고 있을게...";
			link.l1 = "너무 오래 기다리게 하진 않겠소.";

			pchar.questTemp.Duel.enemy = NPChar.id;
			pchar.questTemp.Duel.Sea_Location = Islands[GetCharacterCurrentIsland(PChar)].id;
			AddDialogExitQuestFunction("Duel_Sea_Prepare");
		}

		break;

	//на суше
	case "land_duel":
		iHour = 1 + rand(2);
		if (GetTime() > 4.0 && GetTime() < 17.0)
		{
//			iHour = MakeInt(18.0 - GetTime()) + rand(2); //раскоментировать для дуэлей только по ночам
		}
		pchar.questTemp.Duel.WaitTime = iHour;
		Dialog.Text = RandSwear()+RandPhraseSimple("칼을 뽑아라, 네 피가 무슨 색인지 한번 보자!","글쎄, 죽고 싶다면야...");
		link.l1 = RandPhraseSimple("우리가 너무 많은 목격자가 없는 곳으로 가는 게 좋겠어. 도시 성문을 지나면 딱 맞는 장소를 알아. 거기서 만나자. "+iHour+" 시간.","진정하게. 이런 일은 남의 눈 없이 해결하는 게 좋지. 들어와. "+iHour+"  도시 성문까지 몇 시간 남았어.");
		link.l1.go = "fight_off_town";
		link.l2 = RandPhraseSimple("그래, 그렇게 죽고 싶다면...","젠장! 네 눈으로 지옥을 보게 해주지!");
		link.l2.go = "fight_right_now";
		link.l3 = "내가 마음을 바꿨어...";
		link.l3.go = "change_mind";

		if (rand(1))
		{
			Dialog.Text = RandSwear()+RandPhraseSimple("우리는 성문을 지나가는 게 좋을 것 같아. 거기서 기다리고 있을게, "+pchar.questTemp.Duel.WaitTime+" 몇 시간 남았어. 지체하지 마!","여기는 분쟁을 해결하기에 좋은 곳이 아니야. 우리 그냥 마을을 벗어나는 게 낫겠어. In "+pchar.questTemp.Duel.WaitTime+" 몇 시간 후면 내가 거기 있을 거야.");
			link.l1 = RandPhraseSimple("너는 그 영예를 받을 자격이 없어! 싸울 준비나 해!","시간 없어! 칼 뽑아!");
			link.l1.go = "fight_right_now";
			link.l2 = RandPhraseSimple("좋아, 산책이나 하자.","아마 네 말이 맞을 거야. 성문 밖에서 만나자.");
			link.l2.go = "fight_off_town_prep";
		}
		break;

	//предложение "пойдём выйдем" рассматривается
	case "fight_off_town":
		Dialog.Text = RandPhraseSimple("너는 그런 영예를 받을 자격이 없어! 스스로를 지켜라!","시간 없어! 바로 여기서, 지금 당장!");
		link.l1 = RandPhraseSimple("그래, 그렇게 죽고 싶다면...","젠장! 네 눈으로 지옥을 직접 보게 해주지!");
		link.l1.go = "fight_right_now";
		if (rand(1))
		{
			Dialog.Text = RandPhraseSimple("좋아, 산책이나 하자.","아마 네 말이 맞을 거야. 성문 너머에서 만나자.");
			link.l1 = RandPhraseSimple("거기서 기다리고 있겠소.","지체하지 마라.");
			link.l1.go = "fight_off_town_prep";
		}
		break;

	//что ж, пойдём выйдем
	case "fight_off_town_prep":
		SaveCurrentQuestDateParam("questTemp.Duel.StartTime");
		PChar.questTemp.duel.Start = true;
		PChar.questTemp.duel.enemy = NPChar.id;
		sLocation = GetCurrentTown();
		if (sLocation != "")
		{
			//где?
			sLocation += "_ExitTown";
			pchar.questTemp.duel.place = sLocation;

			Locations[FindLocation(sLocation)].DisableEncounters = true;
			//приходит ко времени.
			pchar.quest.duel_move_opponent2place.win_condition.l1 = "Location";
			pchar.quest.duel_move_opponent2place.win_condition.l1.location = pchar.questTemp.duel.place;
			pchar.quest.duel_move_opponent2place.function = "Duel_Move_Opponent2Place";
			//на случай, если не дождется, часа вполне достаточно
			SetTimerConditionParam("duel_move_opponentBack", "Duel_Move_OpponentBack", 0, 0, 0, sti(GetTime() + 0.5) + sti(pchar.questTemp.Duel.WaitTime) + 1, false);
			pchar.quest.duel_move_opponentBack.function = "Duel_Move_OpponentBack";
			if (CheckAttribute(NPChar, "CityType"))
			{
				DeleteAttribute(NPChar, "City"); // чтоб не было ругани с нацией
	    		DeleteAttribute(NPChar, "CityType");
				if (!CheckAttribute(NPChar, "PGGAi")) 
				{
					if (!CheckAttribute(NPChar, "LifeDay")) npchar.LifeDay = 0;
					npchar.LifeDay = sti(npchar.LifeDay) + 3; // чтоб до дуэли не помер
				}
    		}
		}
		NextDiag.CurrentNode = "let_s_duel";
		DialogExit();
		break;

	//последнее слово перед боем
	case "talk_off_town":
		Dialog.Text = "그래서, 준비됐나?";
		link.l1 = "그래. 누가 더 강한지 한번 보자!";
		link.l1.go = "fight_right_now";
		link.l2 = "아니오, 내가 직접 사과드리기로 했소. 내가 잘못했고, 너무 흥분했소.";
		link.l2.go = "change_mind";
		if (rand(100) < 20)
		{
			Dialog.Text = RandPhraseSimple("이봐, 들어봐. 곰곰이 생각해보니 내가 틀렸던 것 같아. 미안하다.","젠장! 이 모든 게 그 빌어먹을 럼주 때문이야!!! 미안하오, "+GetSexPhrase("형제","자매")+"!");
			link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("아니, 이제는 네 피만이 나를 만족시킬 수 있어!","칼 뽑고 징징대지 좀 마!"),RandPhraseSimple("안 돼! 결투를 요구하겠어!","너는 네 가족의 수치다! 칼을 뽑아라!"));
			link.l1.go = "fight_right_now";
			link.l2 = NPCharRepPhrase(pchar,RandPhraseSimple("좋아, 동의해. 우리가 좀 흥분했었지.","친구 사이에 누가 점수를 따지겠어!"),RandPhraseSimple("아마 네 말이 맞아. 이런 사소한 일로 피를 흘릴 필요는 없지.","내 관대함은 끝이 없지! 용서해 주겠다!"));
			link.l2.go = "peace";
		}
		NextDiag.TempNode = npchar.BackUp.DialogNode;
		pchar.questTemp.Duel.End = true;
		break;

	//дуэли быть!
	case "fight_right_now":
		PChar.questTemp.duel.enemy = NPChar.id;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "fight_right_now_1":	
		PChar.questTemp.duel.enemy = NPChar.id;
		PChar.questTemp.duel.enemyQty = rand(2) + 1;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();	
		break;
		
	//передумал, э... не хорошо ;)
	case "change_mind":
		if (CheckAttribute(pchar, "questTemp.Duel.End")) LAi_SetWarriorType(NPChar);
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("그럼 꺼져!","그럼 꺼져, 내가 마음 바꾸기 전에."),RandPhraseSimple("그렇다면 더 이상 지체하지 않겠소!","그럼 내가 마음을 바꾸기 전에 어서 떠나는 게 좋을 거다."));
		link.l1 = "나는 이미 떠나고 있어...";
		link.l1.go = "peace";
		break;

	case "after_peace":
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("꺼져!","내가 마음을 바꾸기 전에 내 눈앞에서 사라져라."),RandPhraseSimple("도와드릴까요?","뭐 원하는 거 있어?"));
		link.l1 = "나는 떠난다.";
		link.l1.go = "peace";
		break;

	//мир и все такое.
	case "peace":
		LAi_SetWarriorType(NPChar);
		NextDiag.CurrentNode = "after_peace";
		DialogExit();
		break;
	}
}
