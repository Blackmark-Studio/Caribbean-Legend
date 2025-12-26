// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;   
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이오, "+GetSexPhrase("젊은이","아가씨")+"?","무엇이 필요하신가, "+GetSexPhrase("잘생긴","예쁜이")+"? 물어보시오."),"또 질문이군","히히, 괜찮으시다면... 질문을 하시겠소...",""+GetSexPhrase("흠, 어째서 직접 미인을 고르지 않으시나요? 점점 의심이 가기 시작하는데요...","흠, 어여쁜 아가씨 하나 골라보시는 게 어떠신가요? 유감스럽게도 저희 집엔 남자애들은 없답니다, 히히...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("생각이 바뀌었소, 실례하오.","사실, 됐소."),"저... 실례하오, 지금은 질문이 없소.","맞아요, 벌써 세 번째군요. 실례했습니다.","다음에 뵙지요, 마님.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start")
			{
				DelLandQuestMark(npchar);
				link.l1 = "듣게, 아우로라, 오늘 밤 함께할 아가씨가 필요해. 그리고 집에 데려가고 싶어. 그럴 수 있겠나?";
                link.l1.go = "Gigolo";
			}	
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Gigolo":
			dialog.text = "물론이지요, 나리. 이미 적당한 처녀를 찾으셨습니까, 아니면 제가 골라드릴까요?";
			link.l1 = "분명히 그랬소. 루실이라는 이름의 아가씨에게 눈길이 가더군.";
			link.l1.go = "Gigolo_1";
		break;
		
		case "Gigolo_1":
			dialog.text = "루실 몽테뉴를 말씀하시는 건가요?";
			link.l1 = "사실을 말하자면, 그녀의 성은 묻지 않았소. 내가 아는 건 그녀가 루실이라는 이름의 젊고 아름다운 금발 아가씨라는 것뿐이오.";
			link.l1.go = "Gigolo_2";
		break;
		
		case "Gigolo_2":
			dialog.text = "예, 그 말이 딱 맞는군요. 알겠소. 그런데, 왜 하필 그녀요? 다른 아가씨들은 마음에 들지 않으시오?";
			link.l1 = "음, 있잖소... 그녀는 이제 막 여기서 일하기 시작했으니, 아직 '장사'에 충분히 익숙하지 않아서 내 지갑에 큰 부담이 되지는 않을 거라 생각하오.";
			link.l1.go = "Gigolo_2_1";
			link.l2 = "보시다시피, 나는 피부가 하얀 금발을 아주 좋아하오. 그 점에서 루실이 완벽할 것이오.";
			link.l2.go = "Gigolo_2_2";
		break;
		
		case "Gigolo_2_1":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand1) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 5000;
				dialog.text = "이봐 나리, 그건 사실이 아니오! 그 아가씨는 젊고, 예쁘고, 경험도 많소. 내 손님들 모두가 그녀를 칭찬하지. 그녀와 하룻밤을 보내려면 돈이 꽤 들 거요. 오천 페소, 단 한 푼도 깎아줄 수 없소.";
				if (sti(pchar.money) >= 5000)
				{
					link.l1 = "비싸군, 하지만 좋소. 여기 돈이오.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "그건 비싸군! 나한텐 그만한 돈이 없어. 나중에 다시 이야기하겠소.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 2500;
				dialog.text = "하, 맞으십니다, 나리. 그 아이는 예쁘고 젊지만 경험이 부족하지요. 내 손님들은 대개 그녀를 눈여겨보지 않기에 내가 여쭤본 것이오. 하지만 정말로 수줍은 아가씨를 좋아하신다면, 그녀도 괜찮은 선택이 될 것이오. 가격은 이천오백 페소입니다.";
				if (sti(pchar.money) >= 2500)
				{
					link.l1 = "안타깝지만, 그녀라면 충분하겠군. 돈을 내시오.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "비싸군! 그 정도 돈은 없어. 나중에 다시 이야기하지.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_2_2":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand2) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 4500;
				dialog.text = "자네가 처음은 아니야, 잘생긴 양반. 가끔 내 손님들이 그녀의 관심을 받으려고 줄을 서기도 하지. 우리 섬의 흑갈색 피부 딸들과는 아주 다르거든. 그녀와 함께하려면 사천오백 페소가 들 거야.";
				if (sti(pchar.money) >= 4500)
				{
					link.l1 = "비싸지만, 좋소. 돈을 내시오.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "비싸군요! 그 정도 돈은 없소. 나중에 다시 이야기합시다.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 3000;
				dialog.text = "정말이오, 나리? 벌써 향수병이 드셨소? 내 크리올 아가씨들, 특히 물라토들은 저 느긋한 파리 골목 고양이보다 훨씬 더 열정적이오. 하지만 어쩔 수 없지, 선택은 나리의 몫이니. 그녀는 삼천 페소가 들 것이오.";
				if (sti(pchar.money) >= 3000)
				{
					link.l1 = "비싸군, 하지만 좋소. 여기 돈이오.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "비싸군요! 그 정도 돈은 없어. 나중에 다시 얘기하겠소.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharlie.Gigolo.Money));
			dialog.text = "원하시는 대로 하세요, 자기야. 루실이 밤 열한 시에 당신을 애타게 기다릴 거예요. 그리고 아침 일곱 시 이후에는 반드시 돌아와야 해요. 자정 전에 오지 않으면, 그녀는 다른 손님을 받게 되고, 그럼 다음 밤까지 기다려야 그녀를 볼 수 있어요. 그리고 감히... 그녀를 조금이라도 다치게 한다면, 반드시 후회하게 될 거예요. 경고는 충분히 했어요, 자기야.";
			link.l1 = "걱정 마시오, 나는 그녀를 난폭하게가 아니라 연인처럼 대할 것이오. 11시에 그녀를 데려가겠소. 그때까지는 무엇을 하면 되겠소?";
			link.l1.go = "Gigolo_4a";
		break;
		
		case "Gigolo_4a":
			dialog.text = "글쎄요, 나도 잘 모르겠네, 자네. 선술집에 들러서 주점 주인과 이야기라도 해보게...";
			link.l1 = "나쁘지 않은 생각이군. 그렇게 하겠소. 좋은 하루 되시오!";
			link.l1.go = "Gigolo_4";
		break;
		
		case "Gigolo_4":
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			DialogExit();
			AddQuestRecord("SharlieC", "2");
			pchar.questTemp.Sharlie.Gigolo = "girl";
			Sharlie_CreateGigoloGirl();
			QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerDelLoc("fortfrance_brothel", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
			//NewGameTip("Доступна функция перемотки времени! Она доступна через опцию 'мысли вслух' в меню действий (ENTER).");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
