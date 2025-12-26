// Маркус Тиракс, барон Ла Веги
int iTerraxTotalTemp;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;
	bool bOk;

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
					if (npchar.angry.name == "pirate_threat")
                    {
                        if (Dialog.CurrentNode == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                        else Dialog.CurrentNode = "AngryRepeat_1";
                    }
                break;
            }
        }
    }
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && !CheckAttribute(npchar, "quest.mtraxx_complete")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "아, 왕자 나리, 드디어 왔군. 그나마 너 하나라도 나타났으니 다행이지! 할 일은 산더미인데 다들 어디로 사라진 거야! 도대체 다들 어디 있는 거냐?";
					link.l1 = "모르겠어... 마커스, 난 그만둘래. 이제 진절머리가 나. 죽은 놈들이 꿈에 찾아오고 루시퍼까지 내 목덜미를 노리고 있어. 요즘 피가 너무 많이 흘렀어.";
					link.l1.go = "mtraxx_113";
					break;
				}
			}
			// Jason НСО
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "나한테 맡길 '일거리' 있냐?";
				link.l1 = "왔군, Marcus. 그래, '일거리' 하나 있지. 돈도 되고 실용적이야.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "돈 가져왔냐?";
				link.l1 = "내가 했다.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "저놈이 바로 우리 손님이지! 일은 끝났고, 네 바론은 경비가 삼엄한 감옥에 처박혀 있어. 혹시 구경이라도 하고 싶나, 크크?!";
				link.l1 = "그럴 시간은 넉넉히 있지, 하하. 그 자식, 잘 대접받고 있나?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "찰스, 대체 뭐 하는 거야?!";
				link.l1 = "마커스, 모든 게 엉망이 됐어. 오지도 못했고, 연락도 못 했어...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "여기 우리 꼭두각시 조종사가 왔군!";
				link.l1 = "하하! 구경거리가 끝내줬지!";
				link.l1.go = "patria_x29";
				break;
			}
			
			link.l0 = ""+npchar.name+", 나는" + GetSexPhrase("", "요") + " 바다에서의 내 안전에 대해 이야기하고 싶어. 해안 형제단 녀석들이 내 겸손한 존재에 지나치게 관심을 보이고 있어. 그들을 좀 억눌러 줄 수 있겠어?";
			link.l0.go = "pirate_threat";

            dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("나한테 할 말이라도 있나? 없어? 그럼 꺼져!","하, "+pchar.name+"! 나한테 볼일 있냐? 없어? 그럼 귀찮게 하지 마.")+"","내가 분명히 말했을 텐데... 나가라고 했잖아, 근데 계속 귀찮게 하네!","그래, 이 무례함에 슬슬 질린다.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("나는 벌써 떠난다.","그래, Marcus...","미안하다, Marcus...","이런...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("미쳤냐? 도살놀이라도 하고 싶었던 거야? 모든 해적들이 너한테 화났어, 꼬마야, 여기서 당장 꺼지는 게 좋을 거다...","미친 거 아니냐, 이놈. 몸 좀 풀고 싶었나? 기분 나쁘게 듣지 마라, 네가 여기 있을 자리는 아니야. 꺼져!");
				link.l1 = RandPhraseSimple("이봐, 이 상황을 바로잡고 싶어...","이 문제 좀 해결해 줘...");
				link.l1.go = "pirate_town";
				break;
			}
			// Сага - завершаем искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				// Addon 2016-1 Jason пиратская линейка патч 17/1
				if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "마커스, 너 언제까지 나한테 화낼 거냐? 내가 너 친구 빈센트도 구했잖아, 우리랑 같이 카르타헤나 턴 그 녀석 말이야, 그리고 네 목숨도 내가 살렸지! 아니면 베르나르가 아직 너한테 말도 안 했냐?";
					link.l1.go = "Temptation_13";
				}
				else
				{
					link.l1 = "왜 이렇게 무례하냐, Marcus? Bernard가 나에 대해 아무 말도 안 했냐?";
					link.l1.go = "Temptation";
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "to_lavega")
			{
				link.l2 = "일거리 좀 찾고 있는데... 돈 좀 되는 일 없나?";
				link.l2.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "비단 좀 팔려고 한다.";
				link.l2.go = "Mtraxx_silktrade";
			}
			if (pchar.questTemp.Mtraxx == "silk_14")
			{
				link.l1 = "네 물건을 사줄 사람을 찾았다. 포트 로얄에서 온 조선공이다. 그 자는 조선 작업에 쓸 선박용 비단이 필요해서, 매달 백 통씩 한 통에 5두블룬에 사갈 거다. 놈의 부하들이 매달 10일부터 15일까지 밤에 네그릴 곶에서 물건을 가져갈 거다. 암호는 '리옹의 상인'이다. 대머리 제프리가 이미 첫 번째 물량을 자메이카에 전달했다.";
				link.l1.go = "mtraxx_13";
			}
			if (pchar.questTemp.Mtraxx == "silk_15")
			{
				link.l1 = "네 놈한테 구매자를 찾아줬다. 포트 로얄에서 온 조선공이다. 자기네 생산에 쓸 배 실크가 필요해서, 매달 백 통씩 한 통에 5두블룬에 사겠다고 하더군. 그놈 부하들이 10일부터 15일까지, 밤에 네그릴 곶에서 물건을 받아갈 거다. 암호는 '리옹의 상인'이다. 이런 구매자 구하는 데 두 달이 넘게 걸렸으니, 제프리가 이미 실크를 밀수꾼들한테 팔아버렸을지도 모르지. 미안하다, 마커스.";
				link.l1.go = "mtraxx_15";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("미쳤냐? 도살놀이라도 하고 싶었던 거야? 모든 해적들이 너한테 화났어, 꼬마야, 여기서 당장 꺼지는 게 좋을 거다...","미친 거 아니냐, 이놈. 몸 좀 풀고 싶었나? 기분 나쁘게 듣지 마라, 네가 여기 있을 자리는 아니야. 꺼져!");
				link.l1 = RandPhraseSimple("이봐, 이 상황을 바로잡고 싶어...","이 문제 좀 해결해 줘...");
				link.l1.go = "pirate_town";
				break;
			}
			// Jason НСО
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "찰스, 뭐 하는 짓이야?!";
				link.l1 = "마커스, 모든 게 엉망이 됐어. 오지도 못했고, 연락도 못 했어...";
				link.l1.go = "patria_33";
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "반갑다, 친구!";
				link.l1 = "나도 반갑군. 멋진 구경거리 고맙다!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "반갑다, 이놈! 뭐 도와줄까?";
				link.l1 = "너한테 제안이 있어. 해적한테 딱 맞는 거지, 알겠어!";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "저놈이 우리 손님이지! 일은 끝났고, 네 바론은 경비가 삼엄한 감옥에 처박혀 있어. 혹시 구경이라도 하고 싶나, 흣?!";
				link.l1 = "그럴 시간은 넉넉히 있지, 하하. 그 녀석 제대로 대접받고 있나?";
				link.l1.go = "patria_10";
				break;
			}
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "나한테 시킬 일 있냐?";
				link.l1 = "왔군, Marcus. 그래, 한 건 있지. 돈 되고 해적질다운 일이다.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "돈 가져왔냐?";
				link.l1 = "내가 했다.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "저놈이 우리 손님이야! 일은 끝났고, 네 바론은 경비가 삼엄한 감옥에 처박혀 있지. 혹시 구경이라도 할래, 크크?!";
				link.l1 = "그럴 시간은 넉넉히 있지, 하하. 그 녀석 대접은 잘 받고 있나?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "찰스, 이게 대체 뭐야?!";
				link.l1 = "마커스, 모든 게 엉망이 됐어. 나도 오지 못했고, 연락도 못 했어...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "여기 우리 꼭두각시 조종사가 왔군!";
				link.l1 = "하하! 구경거리가 완벽했지!";
				link.l1.go = "patria_x29";
				break;
			}
			// Тени прошлого
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "반갑다, 이놈! 뭐 도와줄까?";
				link.l1 = "Marcus, 너랑 얘기 좀 해야겠다. 네가 좋아할 얘기는 아닐 거 같지만, 그래도 네 도움이 필요해.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "하, 여기 있었군, "+pchar.name+". 네가 오기를 기다리고 있었다. 토르투가에 관한 네 문제 때문에 숲의 악마가 나까지 골치 아프게 만들었지...";
				link.l1 = "네가 해결책을 찾았다고 그가 말하더군. 내가 맞지?";
				link.l1.go = "terrapin";
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "나는 비단을 팔려고 한다.";
				link.l2.go = "Mtraxx_silktrade";
			}
			
			link.l0 = ""+npchar.name+", 나는" + GetSexPhrase("", "요") + " 바다에서의 내 안전에 대해 이야기하고 싶어. 해안 형제단 녀석들이 내 겸손한 존재에 지나치게 관심을 보이고 있어. 그들을 좀 억눌러 줄 수 있겠어?";
			link.l0.go = "pirate_threat";

            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", 반갑군! 이번엔 무슨 일로 왔지?","뭘 원하지?","또야? 할 일 없으면 사람들 귀찮게 하지 마!","너는 "+GetSexPhrase("좋은 사략선장","착한 여자")+", 그러니 지금은 살려두지. 하지만 더 이상 너랑 말하고 싶지 않아.","repeat",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("그냥 네 얼굴이나 보려고 왔지.","아무것도 아니다.","좋아, Marcus, 미안하다.","젠장, 정말 미안하다, Marcus!",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("강도질이냐! 그건 용납 못 한다! 죽을 준비나 해라, 쥐새끼야...","이봐, 거기서 뭐 하는 거야?! 나 털 수 있을 줄 알았냐? 이제 끝장이다...","잠깐, 이게 뭐야?! 결국 네가 도둑이었군! 여기서 끝이다, 이 개자식아...");
			link.l1 = LinkRandPhrase("젠장!","제기랄!","아, 젠장!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("꺼져라","꺼져")+" 여기서부터다!","내 집에서 꺼져!");
			link.l1 = "이런...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "쓸데없는 말로 내 일 방해하지 마라. 다음번엔 네놈, 이렇게 끝나지 않을 거다...";
        			link.l1 = "알겠어, Marcus.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("난 네가 지겨워.","난 너랑 말하고 싶지 않으니까, 내 근처에 얼씬도 하지 마.");
			link.l1 = RandPhraseSimple("음...","흠, 좋아...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "이제 네 쓸데없는 말로 나를 귀찮게 하지 마라, 아니면 죽여야 할 테니까. 솔직히 말해서, 나도 그리 하고 싶진 않다.";
        			link.l1 = "그건 확실하니 걱정 마, Marcus, 나는 절대...";
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
		
//--> -----------------------------Сага - Искушение Барбазона завершающие этапы---------------------------
		case "Temptation":
			dialog.text = "하! 터크의 영웅이라고? 거친 인사라 미안하다, 꼬마야. 버나드가 이미 네가 한 짓에 대해 얘기했고, 나한테 덫을 놓았다는 소문도 들었다. 자세한 얘기를 듣고 싶군...";
			link.l1 = "함정이었지. 그놈들은 베르나르가 아니라 너를 노리고 있었어. 베르나르는 그냥 미끼였을 뿐이야.";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "";
			link.l1 = "계획은 단순했지. 네가 친구를 구하고 '세퍼레이터'에 가장 먼저 올라타기로 되어 있었어. 그리고 바로 그 순간, 놈들이 배에 포격을 가해서 산산조각 내버릴 참이었지.\n브리건틴에는 지옥에 유황이 가득하듯 화약이 잔뜩 실려 있었어.";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "젠장! 그 미친 짓은 도대체 누구 생각이었지?! 그리고 내가 대체 어떻게 버나드를 어디에 숨겼는지 알아내란 거야?!";
			link.l1 = "그 계획을 짠 놈들은 잭맨이랑 그 동생 데이비드였지. 전령이 널 찾아가서 '세퍼레이터'가 터크스 남쪽 만에서 네 도움을 기다린다고 전했을 거다.\n그 전령으로 날 고른 게 걔네 실수였지.";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "이해가 안 돼! 네가 여기서 무슨 역할을 하는 거지?";
			link.l1 = "나는 그 자식 잭맨을 오래전부터 지켜보고 있었지. 혹시 모를까 봐 말해두는데, 나는 얀 스벤손이랑 같이 일해. 숲의 악마랑 나는 그놈을 까발리기로 했어. 얀은 블레이즈가 죽은 게 전적으로 저놈 탓이라고 확신하고 있고, 스티븐은 억울하게 누명 쓴 거라더군.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end") link.l1.go = "Temptation_14";
			else link.l1.go = "Temptation_4"; //патч 17/1
		break;
		
		case "Temptation_4":
			dialog.text = "헤! 하지만 블레이즈 시체에서 이니셜이 새겨진 상어 이빨이 나왔지 – S.D. – 이건 스티븐 거라는 거 다들 알잖아...";
			link.l1 = "전부 함정이었어. 잭맨은 큰 판을 벌였지. 네이선 호크를 제거하고 마룬 타운에서 그 자리를 차지했어, 그리고 샤프를 죽이고 그 죄를 샤크에게 뒤집어씌웠지. 나는 그의 악행을 입증할 증거가 충분히 있어. 제이콥의 상자에서 찾았거든. 거기에 샤프의 지도 두 번째 조각과 호크의 파편이 있었어.";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			dialog.text = "젠장! 그럼 스티븐은 결백한 거였어? 그런데 제이콥은 왜 이런 짓을 한 거지?";
			link.l1 = "그자는 자신이 해적단의 우두머리가 될 거라 기대했고, 이슬라 테소로와 관련된 무언가를 예상하고 있었지. 너와 스벤슨의 지지를 얻지 못하자, 둘 다 제거하기로 결심했어. 네가 첫 번째 표적이었고, 가장 위험한 얀은 두 번째였지.";
			link.l1.go = "Temptation_6";
		break;
		
		case "Temptation_6":
			dialog.text = "그 자식 어디 있어?! 내가 갈기갈기 찢어버릴 거야!";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "잭맨과 그의 형제는 죽었고, 그의 사냥꾼들도 모두 죽었다. 내가 직접 처리했다. 이 개자식은 더 이상 아무도 해치지 못해. 마커스, 스티븐 도드슨에게 표를 줄 생각 있나? 이건 내 개인적인 부탁이다.";
				link.l1.go = "Temptation_7";
			}
			else
			{
				link.l1 = "잭맨과 그의 형제, 그리고 다른 사냥꾼들도 다 죽었다. 내가 직접 처리했지. 이 개자식은 이제 더 이상 아무도 해치지 못해. 안타깝게도 스티븐이 죽었어...";
				link.l1.go = "Temptation_10";
			}
		break;
		
		case "Temptation_7":
			dialog.text = "그래, 투표하지! 나는 항상 블레이즈 다음으로 샤크가 우리 중에서 가장 자격 있다고 생각했지. 나도 한때는 그가 죄인일지도 모른다고 거의 믿었어. 우리 모두 그랬지! 자, 내 조각 받아.";
			link.l1 = "좋아! 이제 숨 좀 쉴 수 있겠군.";
			link.l1.go = "Temptation_8";
		break;
		
		case "Temptation_8":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "그래... 내가 알기로는, 네가 상어의 이익을 대변하는 거지?";
			link.l1 = "그래. 얀 스벤손이랑 나. 좋아, 마르쿠스, 또 보자!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_10":
			dialog.text = "죽었다고?! 어떻게? 이것도 Jackman 짓이냐?";
			link.l1 = "아니. 그건 그의 보선이 한 짓이야, 이름은 챈드 캐퍼였지. 그는 이미 자기 죗값을 치렀어... 마커스, 스벤슨이 너야말로 형제단의 새 우두머리가 될 자격이 있다고 생각한다. 나머지 남작들도 이 결정을 지지할 거다. 받아들이겠나?";
			link.l1.go = "Temptation_11";
		break;
		
		case "Temptation_11":
			dialog.text = "헤! 두 번 말할 필요도 없지. 형제단의 우두머리가 되는 건 큰 영광이야! 내가 반대할 거라고는 꿈도 꾸지 마.";
			link.l1 = "좋아. 이걸 받아들여서 기쁘군.";
			link.l1.go = "Temptation_12";
		break;
		
		case "Temptation_12":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "여기, 내 조각을 가져가. 스벤손에게 전해. 그 자가 책임자인가?";
			link.l1 = "그래, 맞아. 좋아, Marcus, 또 보자!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_9":
			dialog.text = "그래, 그리고 내 친구 베르나르를 구해줘서 고맙다고 말하고 싶어. 자, 이 금주머니 받아라.";
			link.l1 = "고맙다! 잘 가라!";
			link.l1.go = "Temptation_exit";
		break;
		
		case "Temptation_exit":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 300);
			Log_Info("You have received 300 doubloons");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "25");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "Temptation_13":
			dialog.text = "그래, 그놈이 터크스에서 찰리 프린스가 멋지게 도착했다는 얘길 해줬지... 내 목숨을 구해줬다고? 어떻게? 버나드가 함정 얘길 좀 하던데...";
			link.l1 = "그래, 함정이었지. 네가 목표였고, 베르나르는 그냥 미끼였어...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_14":
			dialog.text = "하하하, 숲의 악마 밑에서 일하는 거냐, 왕자? 그래서 내 밑에서 일할 때보다 돈을 더 잘 버냐? 솔직히 말해 봐라!";
			link.l1 = "마커스, 이제 과거는 완전히 잊자. 우리에겐 지금 공동의 목표가 있어, 대상단 약탈보다 훨씬 중요한 일이야. 젠장! 지금은 그게 제일 중요한 거라고! 형제단의 미래가 걸려 있잖아!";
			link.l1.go = "Temptation_15";
		break;
		
		case "Temptation_15":
			dialog.text = "좋아, 나리. 알겠다! 결국 너는 자유로운 사략선이니까, 숲의 악마 밑에서 일하는 건 네 선택이었고, 잘한 결정이었지... 스티븐 말인데... 네가 그가 누명을 썼다고 했지?";
			link.l1 = "완전히 맞아.";
			link.l1.go = "Temptation_4";
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "물론이지, 최선을 다해 도와줄게! 계속 말해봐.";
			link.l1 = "한번 봐, Marcus... 이건 상어 이빨이야. 이거에 대해 뭐 아는 거 있냐?";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "하! 그건 스티븐 도드슨이 한 여자를 감동시키려고 죽인 백상아리의 이빨이지. 그때부터 사람들은 그를 상어라고 불렀어. 그런 걸 단순한 세이버 하나만 들고 물속에서 해낼 수 있는 놈은 몇 안 돼. 하지만 그는 젊고 멍청했지, 그리고 비트리스 샤프는 카리브에서 가장 아름다운 여자였어... 그런데, 그걸 어떻게 손에 넣은 거지?";
			link.l1 = "이건 세인트 존스의 전직 교수형 집행인이 내게 준 거다.\n이 이빨로 한 놈을 죽였지.\n그 자의 이름은... 조슈아 리드비터였다.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "그건 오래된 이야기다. 스티븐이 그 남자를 죽였지. 그는 비트리스의 죽음에 충격을 받아 리드비터만이 그 일에 책임 있는 유일한 생존자라고 생각했어. 하지만 나중에 조슈아의 시체에서 몇몇 문서를 발견하고, 그것들을 읽어본 뒤 자신의 짓을 뉘우쳤지.\n비트리스의 죽음은 마스크의 잘못이 아니었어. 마스크는 그저 부처만 필요했을 뿐이지. 이 모든 일은 부처의 질투 많은 전 여자친구 제시카가 꾸민 짓이었어.";
			link.l1 = "그 문서들 읽어봤냐?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "내가 왜 그래야 하지? 당연히 안 하지. 걔네들한테 관심도 없었어. 하지만 네가 시간 좀 남는다면 왜 마스크가 도살꾼을 쫓았는지 말해줄 수는 있지. 술주정뱅이 스티븐이 이 얘기를 여러 번 해줬거든.";
			link.l1 = "시간 plenty하지. 내 관심엔 다 이유가 있어. 이 이야기를 내가 직접 써도 될 판이야.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "네가 시간 낭비하는 놈이 아니라는 건 안다. 그러니 잘 들어. 조슈아 리드비터는 영국 해군의 선장이었고, 전설적인 '넵튠'이 그의 지휘 아래 있었지...";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("One hour later", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... 하지만 리드비터는 살아남아 지나가던 배에 구조되었지. 상처 때문에 얼굴이 망가져서 그때부터 가면을 쓰고 다녔어. 시간이 지나자 사람들은 그를 ‘가면’이라고 부르기 시작했지. 평생 지울 수 없는 상처를 남긴 놈에게 복수하는 것만이 그의 유일한 목적이 되었어.";
			link.l1 = "알겠군... 전부 적어 놨다. 다시 읽어보고 내가 이미 가진 정보들과 비교해 봐야겠어. 참으로 슬픈 이야기로군. 제시카를 본 적 있나?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "그래! 그녀는 도살자와 모든 항해를 함께했지, 그가 베아트리스를 위해 그녀를 떠날 때까지 말이야. 제스는 그걸 용서하지 못했어. 사람들은 그녀를 도살자의 부적이라고 불렀지, 그녀가 곁에 있을 때마다 도살자에게 행운이 따랐으니까.\n믿거나 말거나, 바베이도스에서 그녀를 떨쳐낸 순간부터 도살자의 운이 나빠졌고, 전리품도 시원찮아졌으며, '넵튠'은 이슬라 테소로 조선소의 단골손님이 되었지. 하지만 그건 도살자가 갑판 위가 아니라 선실에서 베아트리스와 대부분의 시간을 보냈기 때문이라고 설명할 수도 있겠지.\n베아트리스는 제시카와 달랐어. 모험이나 전쟁에 빠져 있지 않았고, 니콜라스가 펜싱과 항해를 가르치긴 했지만, 그녀에겐 강철 같은 기질이 부족했지. 물론 바다의 낭만을 좋아하긴 했지만, 도살자의 '넵튠'은 그녀에게 어울리는 곳이 아니었어. 결국, 그게 그녀를 죽였지.";
			link.l1 = "제시카는 어쩔 건데?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "오, 그 여자는 정말 대단했지... '네프튠'호의 모든 선원이 그녀의 명령에 따랐어, 단순히 선장의 여자친구라서가 아니었지. 제스는 펜싱과 항해의 달인이었고, 부처의 노력이 헛되지 않았어. 그녀는 강인하고 무모했으며, 정말 아름다웠지. 많은 남자들이 그녀와 한 침대를 쓰고 싶어 했지만, 그녀는 오직 부처만을 원했어. 그녀를 건드리는 건 정말 위험했지; 많은 놈들이 그 대가를 뼈저리게, 말 그대로 피부로 느꼈고, 특히 끈질긴 놈들에겐 그녀의 펜싱 수업이 인생의 마지막이 되었지. 제스는 카리브 해에서 유일무이한 아주 특별한 검을 가지고 있었어. 어디서 구했는지는 나도 전혀 몰라. 불꽃 모양의 칼날이었지. 그 칼날은 맨손으로 잡을 수 없었고, 살짝 스치기만 해도 끔찍한 상처를 남겼어. 제스는 태생이 아니라 천성적으로 모험가였지. 그런데 말이야, 그녀에 대해 더 알고 싶으면 네 지인한테 물어봐도 돼. 나보다 훨씬 더 많은 걸 들려줄 수 있을 거야.";
			link.l1 = "정말이냐? 그리고 이 자가 누구지?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "얀 스벤손. 숲의 악마는 절대 인정하지 않겠지만, 제시카를 노리고 있었지. 그때 이미 그는 웨스턴 메인을 손에 넣었고, 그의 명성은 누구나 부러워할 만했으니, 호랑이 같은 제시카가 딱 어울렸던 거야.\n도살자가 제스를 처리한 뒤, 얀은 바베이도스에 수상할 정도로 자주 들락거렸고, 그때마다 주둔군이 공포에 떨었지. 알다시피, 제시카는 브리지타운 플랜터의 딸이었어.\n결국 그의 속셈은 사적인 모임에서는 다 알려져 있었지만, 아무도 감히 입 밖에 내지 못했지. 요즘 얀은 블루웰드에서 빈둥거리지만, 그땐 그에게 잘못 말 한마디 했다간 끝장이었거든.\n결국 둘의 사이는 잘 되지 않았어. 제스는 도살자의 배신이 남긴 상처를 견디지 못했고, 1년 뒤 마스크의 도움으로 복수를 했지. 이 복수는 모두에게 비극으로 끝났어: 도살자, 비트리스, 마스크, 그리고 제스 자신까지. 모두 죽었지.";
			link.l1 = "아니. Butcher는 아직 살아 있어.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "뭐?! 내가 잘못 들은 거야?! 그 자가 살아 있다고?!";
			link.l1 = "그래. 부처 선장은 교수형을 당하지 않았어. 아니, 사실은 당했지. 하지만 교수형 집행인을 겁준 제이콥 잭맨과 헨리 더 행맨 덕분에 살아남았어. 교수형은 그냥 연극이었지. 내가 증거도 갖고 있어.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "믿기지 않는군! 그런데 지금 그 자는 어디 있지?";
			link.l1 = "그 자는 로렌스 벨트롭이라고 알려져 있고 포트 로얄에 살고 있다. 하지만 여전히 변하지 않았고 여전히 위험한 놈이지. 브라더후드 안에서 많은 문제를 일으킨 잭맨도 그의 명령을 따르고 있었어.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "젠장! 결국 그 분기장은 자기 선장을 찾아냈군! 그렇게 많은 세월이 지난 후에... 벨트롭이라고 했지... 잠깐! 이제야 알겠군, 왜 블레이즈 서류에 그 이상한 심문 절차가 있었는지... 블레이즈가 도살자 벨트롭에 대해 뭔가 흥미로운 걸 알아낸 모양이야...";
			link.l1 = "무슨 소리야?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "내가 이 거처를 차지했을 때, 블레이즈의 문서들을 좀 살펴볼 시간을 가졌지. 그 중에 사무엘 브룩스라는 자에 대한 심문 기록이 있더군. 거기엔 유명한 해적이자 니콜라스 샤프의 가장 가까운 친구인 토마스 벨트로프의 모험에 관한 세부 내용이 많았어. 보아하니 그가 바로 부처의 아버지인 것 같더군.";
			link.l1 = "재밌군. 벨트롭과 샤프의 자식들이 자기 아비들 짓을 이어가는 모양이야...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "그래 보이네... 이봐, 친구, 왜 그렇게 오래 전에 죽은 놈들의 과거에 관심이 많은 거지? 대체 뭐 하자는 거야?";
			link.l1 = "엘렌 맥아더가 비트리스 샤프의 딸이며 니콜라스 샤프의 손녀라는 것, 그리고 이 성을 쓸 정당한 권리가 있다는 걸 증명하는 서류가 필요해. 엘렌의 성이 벨트롭일 수도 있다는 건 신경 안 써.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "블레이즈의 기록에서 엘렌 맥아더에 대한 아무런 정보도 찾지 못했다. 베아트리스가 자신의 조카가 태어난 걸 블레이즈에게 말하지 않았다니 이상하군. 그녀답지 않은데.";
			link.l1 = "이봐, 샤프의 서류에 이 이야기와 관련된 다른 내용이 있을지도 모르잖아? 내가 얻을 수 있는 모든 세부사항이 필요해!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "흠... 그럴지도. 블레이즈의 기록에 따르면, 그는 여동생이 죽은 섬을 찾으려고 했지. 리드비터의 징벌 원정에 관한 기록 사본도 있어. 별로 흥미로운 건 없고, 위도 숫자 몇 개뿐이야.\n이 위도는 카리브 해 북쪽을 가로지르지. 하지만 경도는 전혀 없어. 분명히 블레이즈의 수색은 실패했을 거다; 그 위도에 작은 섬이 얼마나 많은지 상상도 못 할 거야.";
			link.l1 = "위도는 얼마지?";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "보자... 여기 있군: 북위 21도 32분. 이게 너한테 어떻게 도움이 될지는 모르겠다.";
			link.l1 = "그럴 수 있지. 솔직하게 이야기해 줘서 정말 고맙다, Marcus. 또 보자!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "I_know_you_good";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "terrax"; // 280912
		break;		
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "그래, 네 놈을 위해 뭔가 해줄 수 있지. 알다시피, 토르투가의 경비는 라 로슈 요새뿐만 아니라, 섬 해안을 항상 지키는 해적 함대가 함께 맡고 있다. 토르투가 항구는 안전하다, 이 녀석들은 제 할 일 잘 알고 있고, 강력한 배들도 가지고 있지. 르바쇠르가 이 선장들을 오래 전부터 꼬셔 왔지.\n이 자들은 전열함대와 맞서 싸울 능력도 있고, 만만치 않은 상대가 될 거다. 그러니, 내가 해적 규약의 수호자이자 코스트의 형제단 우두머리로서, 이 감시견들을 토르투가 해안에서 물러나게 할 수 있다.";
			link.l1 = "그게 다야?";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "그 정도면 됐지 않아? 더 이상 도와줄 수 없어. 요새는 네가 직접 파괴해야 해. 그래도 경비선들과 싸울 필요는 없으니 다행이지. 내 말 믿어, 그놈들이 요새보다 훨씬 위험하니까 내가 도와주면 훨씬 쉬워질 거야.";
			link.l1 = "그래, 어차피 내가 공격해야 한다면 해적 함대가 출항하는 게 정말 도움이 되겠군. 고맙다, 마커스! 내가 토르투가를 언제 공격할 수 있지?";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "언제든 네가 원할 때. 내 신호만 기다리면 호위선들이 출항할 거다.";
			link.l1 = "좋아. 이제 준비하러 가야겠다.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			DialogExit();
			// Левассера - к барьеру!
			sld = characterFromId("Tortuga_Mayor");
			LAi_LoginInCaptureTown(sld, true);
			pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
			pchar.questTemp.Terrapin = "hardcore";
			pchar.questTemp.Sharlie.DelTerGuard = "true"; // убираем пиратскую эскадру
		break;
		
		case "pirate_town":
            dialog.text = "문제를 해결하라고? 네가 무슨 짓을 저질렀는지 알기는 하냐? 어쨌든, 백만 페소를 가져와라. 그러면 내가 놈들에게 네 짓을 잊으라고 설득해주지. 그게 싫으면 지옥이나 꺼져라.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "좋아, 돈 낼 준비 됐다.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "잘 가라...";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "좋아! 이제 다시 깨끗해졌다고 생각해라. 하지만 다시는 그런 역겨운 짓 하지 마라.";
			link.l1 = "안 해. 나한텐 너무 비싸. 잘 있어라...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		case "pirate_threat":
			if (GetNpcQuestPastDayWOInit(NPChar, "ThreatTalk") == 0)
			{
				dialog.text = NPCStringReactionRepeat("오늘은 이미 그 얘길 했잖아.",
				                                      "내 말이 이해가 안 됐나?",
				                                      "너무 끈질기군.",
				                                      "더는 못 참겠다. 당장 꺼져!",
				                                      "repeat", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("다음에 다시 이야기하지 뭐...",
				                                   "물론이지, "+npchar.name+"...",
				                                   "미안해, "+npchar.name+"...",
				                                   "아야...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
				break;
			}
			if (iGPThreat != 0)
			{
				iBarbazonTotalTemp = 10 * iGPThreatRate;
				dialog.text = "하! 우리 형제단이 널 괴롭히고 있나 보군, " + GetSexPhrase("친구", "아가씨") + "? 뭐, 잠시 동안은 그들을 진정시켜 줄 수 있지. 하지만 대가가 필요해. " + FindRussianDublonString(iBarbazonTotalTemp) + "만 내면, 그렇게 하지.";
				if (PCharDublonsTotal() > iBarbazonTotalTemp)
				{
					if (iGPThreat < 5) link.l0 = "좋아, 여기 네 돈이야.";
					else link.l0 = "어쩔 수 없지. 여기 있어.";
					link.l0.go = "pirate_threat_pay";
				}
				link.l1 = "다음에 다시 올게...";
				link.l1.go = "exit";
			}
			else
			{
				SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
				if (NextDiag.TempNode != "I_know_you_good")
					dialog.text = "미쳤" + GetSexPhrase("니", "니") + "? 우리 녀석들은 널 마치 전염병처럼 피해 다녀. 그러니까 꺼지고 귀찮게 하지 마.";
				else
					dialog.text = "무슨 말이야, " + GetSexPhrase("친구", "아가씨") + "? 넌 골칫덩어리야 — 개들조차도 그걸 알아. 아무도 너랑 엮이고 싶어하지 않아.";
				link.l1 = "알겠어...";
				link.l1.go = "exit";
			}
		break;

		case "pirate_threat_pay":
			iGPThreatRate = 0;
			iGPThreat = 0;
			SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
			RemoveDublonsFromPCharTotal(iBarbazonTotalTemp);
			DialogExit();
			PiratesDecreaseNotif("");
		break;
		
		// Addon 2016-1 Jason ------------------------- пиратская линейка --------------------------
		case "Mtraxx":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "먼저 배부터 구해라, 그 다음에 일거리를 찾아봐라. 뭍사람이 여기서 할 일은 없어. 꺼져!";
				link.l1 = "흠... 알겠군.";
				link.l1.go = "exit";
				break;
			}
			if(ChangeCharacterHunterScore(Pchar, "spahunter", 0) > 10)
			{
				dialog.text = "정신이 완전히 나간 거냐? 스페인 놈들 반이 너 뒤쫓고 있어. 네가 더 해를 끼칠 뿐이야. 네 문제부터 해결하고 다시 와라. 내가 할 말은 그게 다다! 썩 꺼져!";
				link.l1 = "흠... 알겠군.";
				link.l1.go = "exit";
				break;
			}
            dialog.text = "재미 좀 보려고 온 거냐, 응? 하하! 좋아... 하지만 경고한다, 꼬마야. 나랑 있으면 평온 따윈 기대하지 마라. 화약 냄새가 무섭거나 피 한 방울도 못 흘리겠으면, 문은 저기다. 난 겁쟁이 놈들은 딱 질색이거든. 그리고 동료 몫 훔치는 쥐새끼나 고자질쟁이라면 나랑 오래 못 버틴다. 자, 어때? 할 거냐?";
			link.l1 = "나도 끼겠어, 마커스. 싸우는 거 두렵지 않고, 나를 겁쟁이나 쥐새끼라고 부를 놈은 아무도 없어.";
			link.l1.go = "Mtraxx_1";
			link.l2 = "이봐, 그건 나한텐 너무 과하군! 미안하지만, Marcus, 난 이만 가보는 게 좋겠어...";
			link.l2.go = "Mtraxx_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "Mtraxx_exit":
            DialogExit();
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_wait":
            dialog.text = "뭐야, 아직도 여기 있냐?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "비단 좀 팔려고 한다.";
				link.l2.go = "Mtraxx_silktrade";
				link.l1 = "난 이미 떠난다.";
				link.l1.go = "exit";
				break;
			}
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "Mtraxx_1":
            dialog.text = "하하, 그래, 그래, 우리 용감한 꼬마 해적아, 그럼 이제 거래 얘기를 해보자. 산토도밍고에 있는 내 정보원이 스페인 선장 하나에 대해 알려줬는데, 그놈은 파란 호박을 너무 많이 갖고 있어서 창녀들한테까지 뿌리고 다닌다더라. 파란 호박에 대해 들어본 적 있냐?";
			link.l1 = "있지. 희귀하고 값진 돌이다.";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "정확히 그렇지. 여기서도 은행가나 보석상들이 그걸 비싼 값에 사들이고, 유럽 본토에선 그 값이 열 배는 더 뛰지. 카리브에선 호박이 드문 돌은 아니지만, 파란 호박은 진짜 귀한 물건이야. 그런데 지금은 어떤 카스티야 놈이 쿠바랑 이스파니올라 은행가들이 가진 노란 호박 전부 합친 것보다 자기가 더 많은 파란 호박을 갖고 있다고 자랑질하고 있지.";
			link.l1 = "술에 취한 스페인 놈 얘기를 믿을 수 있겠어? 겨우 두블룬 세 개 주웠다고 엘도라도라도 찾은 양 떠들고 다니잖아\n";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "나라도 안 했겠지, 하지만 그 자식이 진짜로 창녀들에게 푸른 호박을 주고 있더군. 허풍에도 뭔가 진실이 있나 보지. 산토도밍고에 가서 조사해 봐. 만약 푸른 호박 매장지를 찾아낸다면 더 좋고. 이 일을 해내면 라 베가에서 보상과 존경을 보장해 주지.";
			link.l1 = "네 정보가 쓸모없으면 어쩔 건데?";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "그럼 그 카스티야 놈이 거짓말쟁이라는 걸 증명해 봐.";
			link.l1 = "좋아. 산토도밍고에서 네 정보원이 누구지?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 60 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 60) 
					{
						sTemp = ". Wait a minute, take a trading license for 60 days."; 
						GiveNationLicence(HOLLAND, 60);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ". Wait a minute, take a 60-day trade license and a Spanish flag to land in Santo Domingo. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
						GiveNationLicence(HOLLAND, 60);
						STH_SetJokerFlag(SPAIN, true);
						log_info("You have received spanish flag");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 60) 
						{
							sTemp = ". Wait, how are you going to trade without having the right flag?! Here you go, a 60-day trading license, longer than yours. As well as the Spanish flag for landing in Santo Domingo. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
							GiveNationLicence(HOLLAND, 60);
							STH_SetJokerFlag(SPAIN, true);
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Wait, how are you going to trade without having the right flag?! Here, take the Spanish flag for the Santo Domingo landings. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
							STH_SetJokerFlag(SPAIN, true);
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "너한텐 가브리엘라 차파도라는 창녀가 필요해. 내 이름이랑 암호 '호박 목걸이'를 말해. 그럼 자세한 걸 알려줄 거다. 시간 낭비하지 마라 - 정보가 아직 따끈따끈하지만 하루 이틀 지나면 쓸모없어질 수도 있으니까."+sTemp;
			link.l1 = "알겠어, Marcus. 나 산토도밍고로 간다.";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_1";
			pchar.questTemp.Mtraxx.AffairOfHonor = "true"; // конфликт с делом чести
			pchar.questTemp.ZA.Block = true;			// конфликт с квестом "Заносчивый аристократ"
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_1", "1");
			Mtraxx_JewelryBegin();
			AddMapQuestMarkCity("SantoDomingo", false);
		break;
		
		case "mtraxx_7":
			i = GetCharacterItem(pchar, "jewelry7");
            dialog.text = "네가 도착했다는 건 이미 들었다. 보고나 해!";
			link.l1 = "그 파란 호박에 미친 놈은 처리했어, 쉽진 않았지만. 그의 은닉처를 찾아내서 약탈했지. 네게 가져왔다\n "+FindRussianQtyString(i)+" 푸른 호박 조각.";
			link.l1.go = "mtraxx_8";
			DelLandQuestMark(characterFromId("Terrax"));
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "mtraxx_8":
			if (sti(pchar.questTemp.Mtraxx.JewQty) > GetCharacterItem(pchar, "jewelry7"))
			{
				PlaySound("interface\important_item.wav");
				Log_Info("You have given "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" pieces of blue amber");
				RemoveItems(pchar, "jewelry7", GetCharacterItem(pchar, "jewelry7"));
				dialog.text = "그래, 그래... 아들아, 내가 쥐새끼처럼 굴면 어떤 위험이 따르는지 경고했던 거 기억나냐? 그때 네가 뭐라고 했지? 아무도 널 탓할 수 없다고 했던가? 내가 바보로 보이냐, 꼬마야? 네가 약탈한 거 뻔히 다 알고 있다\n "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.JewQty))+" 모스키토 해안의 푸른 호박 조각들이다. 이제 도망쳐라, 쥐새끼야, 도망치고 두 번 다시 내 앞에 나타나지 않기를 빌어라!";
				link.l1 = "젠장!";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.Dialog.currentnode = "First time";
				CloseQuestHeader("Roger_1");
				// belamour legendary edition забрать флаг обратно
				if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
				{
					DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
					STH_SetJokerFlag(SPAIN, false); 
					log_info("You have given spanish flag");
				}
			}
			else
			{
				PlaySound("interface\important_item.wav");
				Log_Info("You have given "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" pieces of blue amber");
				RemoveItems(pchar, "jewelry7", sti(pchar.questTemp.Mtraxx.JewQty));
				dialog.text = "잘했구나, 이놈! 어려운 일을 잘 처리했고, 약탈한 것도 다 가져왔군. 수고했다! 내가 너를 잘못 본 게 아니라서 다행이야.";
				link.l1 = "내 몫은 어쩔 건데, Marcus?";
				link.l1.go = "mtraxx_9";
			}
		break;
		
		case "mtraxx_9":
			i = sti(pchar.questTemp.Mtraxx.JewQty)/2;
			PlaySound("interface\important_item.wav");
			Log_Info("You have received "+FindRussianQtyString(i)+" pieces of blue amber");
			TakeNItems(pchar, "jewelry7", i);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				STH_SetJokerFlag(SPAIN, false); 
				log_info("You have given spanish flag");
			}
            dialog.text = "진짜 해적답게 말했군, 하하하! 전리품의 절반은 네 거다. 가져가라.";
			link.l1 = "고마워, 선장. 또 시킬 일 있냐?";
			link.l1.go = "mtraxx_10";
			DeleteAttribute(pchar, "questTemp.Mtraxx.JewQty");
			CloseQuestHeader("Roger_1");
			Achievment_Set("ach_57");
		break;
		
		case "mtraxx_10":
            dialog.text = "나는 항상 쓸만한 놈들에게 맡길 일이 있다. 이번엔 좀 민감한 건인데, 네가 처리해 줬으면 한다. 캡스터빌에 정박 중인 '스네이크'라는 배가 있는데, 그 선장은 제프리 브룩, 일명 대머리 제프리다. 내 밑에서 일하는 놈이지. 싸움은 끝내주게 잘하고, 총이랑 칼에 대해서는 모르는 게 없지만, 그 외에는 완전 바보야. 뭐, 대머리라고 너무 구박하지 말자. 완벽한 놈이 어디 있겠냐, 하하!\n그래서 말인데, 이 놈이 세인트 마틴 북쪽에서 네덜란드 호송선을 공격해서 밀가루 자루로 가득 찬 바크선을 하나 잡았다. 그런데 그 자루들 사이에서 숨겨진 선박용 비단을 찾아냈지. 엄청난 양이야. 이 물건은 엄청나게 귀하고 값비싼 거다. 네덜란드 놈들이 유럽에서 군용으로만 들여오는 거거든. 이 비단은 특별한 돛을 만드는 데 쓰여서, 배의 속도와 바람을 타는 능력을 높여 준다. 사는 건 거의 불가능하지, 파는 건 쉽지만 제대로 된 값을 받기가 힘들다. 이 빌어먹을 상인 놈들은 항상 값을 깎아내리거든!\n내가 알기로는, 카리브 해에는 이 비단을 사려고 금화로 제대로 값을 쳐줄 놈들이 있다. 네 임무는 그런 놈들을 찾아내는 거다. 뭐? 아무 멍청이나 캐러밴을 털 수는 있지만, 장사는 머리에 최소한 뇌가 들어 있는 놈만 할 수 있지. 나는 앞으로 매달 선박용 비단을 팔 생각이니, 네가 해야 할 일은 한 롤에 최소 금화 4두블론을 주고 살 단골손님을 찾는 거다. 두 달 안에 해내라. 대머리 제프리를 캡스터빌에 영원히 묶어둘 순 없으니까. 할 말은 다 했다. 당장 캡스터빌로 가서, 제프리가 그 화물을 밀수꾼한테 헐값에 넘기기 전에 만나 봐라. 내가 이미 말했지, 그 놈 좀 '단순하다'고.";
			link.l1 = "흠... 알겠다. 이미 가는 중이다.";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_1";
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_2", "1");
			Mtraxx_SilkBegin();
		break;
		
		case "mtraxx_12":
            dialog.text = "하! 여기 용감한 선장이 왔군 "+GetFullName(pchar)+"! 그 구매자는 어쩔 건데?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				link.l1 = "네 놈을 위해 구매자를 찾아냈다. 포트 로얄에서 온 조선공이다. 그 자는 자기 생산에 쓸 배 실크가 필요해서, 한 달에 백 통씩, 통당 5두블룬에 살 수 있다. 그놈 부하들이 10일부터 15일까지, 밤에 네그릴 곶에서 물건을 가져갈 거다. 암호는 '리옹의 상인'이다. 이런 구매자 찾느라 두 달이 넘게 걸렸다; 제프리가 이미 그 실크를 밀수업자들에게 팔아버렸을지도 모르지. 미안하다, 마르쿠스.";
				link.l1.go = "mtraxx_15";
			}
			else
			{
				link.l1 = "네 놈한테 구매자를 찾아줬다. 포트 로얄에서 온 조선공이지. 그 자는 선박 제작에 쓸 선박용 비단이 필요해서, 매달 백 통씩 한 통에 5두블룬에 사갈 거다. 그놈 부하들이 10일부터 15일까지 밤에 네그릴 곶에서 물건을 받아갈 거다. 암호는 '리옹의 상인'이다. 대머리 제프리가 이미 첫 번째 물량을 자메이카로 넘겼다.";
				link.l1.go = "mtraxx_13";
			}
		break;
		
		case "mtraxx_13":
            dialog.text = "좋아, 친구! 잘했군. 손이랑 머리 둘 다 쓸 줄 아는 놈은 찾기 힘들지. 20일 뒤에 와서 보상 받아가라. 그때쯤이면 대머리 제프리가 첫 거래에서 나온 돈을 가져올 거다."; // правки прогона 3
			link.l1 = "좋아, Marcus. 곧 보자. 또 다른 일거리가 있길 바란다.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_14":
            dialog.text = "알겠어. 나중에 보자.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 30, false);
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 40, false);
				AddQuestRecord("Roger_2", "23");
			}
			else
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 20, false); // правки прогона 3
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 30, false);
				AddQuestRecord("Roger_2", "24");
			}
		break;
		
		case "mtraxx_15":
			pchar.quest.Mtraxx_SilkTimeLateAll.over = "yes";
            dialog.text = "아쉽지만, 그래도 대단한 성공이군. 수고했다! Geffrey의 물건 몫은 못 받겠지만, 네가 받을 보상은 따로 있다. 한 달 뒤에 나를 찾아와라. 그때쯤이면 네 구매자에게 첫 물건을 팔아넘겼을 테니, 그때 얘기하지.";
			link.l1 = "좋아, Marcus. 곧 보자. 또 다른 일거리가 있길 바란다.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_16":
			//pchar.quest.Mtraxx_SilkPayLate.over = "yes";
            dialog.text = "거기 있었군, "+pchar.name+". 네 보상에 대해 얘기하자.";
			link.l1 = "이런 대화 참 좋다, 하하하! 다 듣고 있지.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate")) link.l1.go = "mtraxx_19";
			else link.l1.go = "mtraxx_17";
		break;
		
		case "mtraxx_17":
            dialog.text = "대머리 제프리가 네 구매자에게 첫 번째 선적분인 선박용 비단 105필을 팔았다. 나는 한 필당 4두블룬에 팔 거라 기대했으니, 그 차액을 네게 주는 게 공평하다고 본다. 그게 내 결정이다. 네 몫은 105두블룬에 보너스까지, 즉 한 필당 한 두블룬이다. 합쳐서 210두블룬이 된다. 자, 가져가라.";
			link.l1 = "고마워, Marcus!";
			link.l1.go = "mtraxx_18";
		break;
		
		case "mtraxx_18":
			TakeNItems(pchar, "gold_dublon", 210);
			PlaySound("interface\important_item.wav");
            dialog.text = "한 가지 더 있지. 이걸로 좀 더 벌 수 있어.";
			link.l1 = "재밌군... 계속해.";
			link.l1.go = "mtraxx_19";
		break;
		
		case "mtraxx_19":
            dialog.text = "네 구매자가 앞으로 두 달 동안 100필 이상의 비단을 원한단다. 가지고 있다면 20필에서 100필까지 가져와라. 한 필에 5두블룬을 쳐주지. 이 제안은 두 달간 유효하다.";
			link.l1 = "좋아! 더 있으면 가져오지.";
			link.l1.go = "mtraxx_20";
			pchar.questTemp.Mtraxx.SilkTrade = "true";
			SetFunctionTimerCondition("Mtraxx_SilkTradeOver", 0, 0, 60, false);
		break;
		
		// торговля шелком
		case "mtraxx_silktrade":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "얼마나 가지고 있지?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			if (iTotalTemp > 100) link.l1.go = "mtraxx_silktrade_2";
			else link.l1.go = "mtraxx_silktrade_1";
		break;
		
		case "mtraxx_silktrade_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*5);
            dialog.text = "좋아. 금을 가져가라 - 주사위 한 판에 5두블룬, 약속한 대로다.";
			link.l1 = "감사하지!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_2":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 100);
			TakeNItems(pchar, "gold_dublon", 500);
            dialog.text = "백 개 가져가지. 금 가져가라 - 한 롤당 5두블룬, 약속한 대로다.";
			link.l1 = "감사하지!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_3":
            DialogExit();
			npchar.dialog.currentnode = "First time";
			DeleteAttribute(pchar, "questTemp.Mtraxx.SilkTrade");
		break;
		
		case "mtraxx_20":
            dialog.text = "더 급한 얘기를 하자, 위험한 일 좀 해볼래?";
			link.l1 = "좋아! 나랑 내 놈들은 당장 출항할 준비가 되어 있다.";
			link.l1.go = "mtraxx_24";
		break;
		
		case "mtraxx_22":
            dialog.text = "젠장, "+pchar.name+", 도대체 어디 쳐박혀 있었던 거야? 내가 오라고 했던 거 기억나지? 너한테 줄 일이 있었는데, 네 그 지랄맞은 타이밍 덕분에 다 망쳤다. 아주 열받게 하는구나, 이놈아. 꺼져, 믿을 수 없는 놈이랑은 일 안 해.";
			link.l1 = "젠장...";
			link.l1.go = "mtraxx_23";
		break;
		
		case "mtraxx_23":
			DialogExit();
            npchar.dialog.currentnode = "First time";
			CloseQuestHeader("Roger_2");
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_24":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 40 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 40) 
					{
						sTemp = ", as well as a trade license for 40 days."; 
						GiveNationLicence(HOLLAND, 40);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ", as well as a trade license for 40 days. Besides, how are you going to fool the bungler in the fort?! You will let me down one day with such sloppiness... Here you go... You will return it back upon arrival. The new generation, pah...";
						GiveNationLicence(HOLLAND, 40);
						STH_SetJokerFlag(SPAIN, true);
						log_info("You have received spanish flag");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 40) 
						{
							sTemp = ". Tell me, how are you going to fool the bungler in the fort?! Your paper won't help you without the right flag. I feel that you will let me down one day with such sloppiness... Here, a trading license for 40 days, more than yours. As well as the Spanish flag for landing in Maracaibo. You will return it upon arrival. The new generation, pah...";
							GiveNationLicence(HOLLAND, 40);
							STH_SetJokerFlag(SPAIN, true);
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Tell me, how are you going to fool the bungler in the fort?! Your paper won't help you without the right flag. I feel that you will let me down one day with such sloppiness... Here you go... You will return it back upon arrival. The new generation, pah...";
							STH_SetJokerFlag(SPAIN, true);
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "그럼 잘 들어. 두 달 전에 장 피카르라는 선장, 일명 잘생긴 장과 약속이 있었지. 그런데 그 자식이 약속 장소에 나타나지 않았어. 나는 그와 중요한 얘기를 하려고 했기 때문에, 그놈의 행방을 좀 조사해 봤다. 알고 보니 우리 용감한 사략선장과 그의 브리건틴이 도네두아르도 데 로사드라는 놈이 지휘하는 스페인 중무장 갤리온과 싸움을 벌였더군. 그놈, 아주 지독한 악질이야. 그 결과, 장과 남은 선원들은 마라카이보로 끌려가서 현지 플랜테이션에 팔려버렸지. 지금 그 자식은 거기서 땀 흘리며 정직하게 일하고 있다.\n네 임무는 이렇다. 첫째, 그놈이 왜 그렇게 꼬였는지 자세히 조사해라. 둘째, 플랜테이션에서 그놈을 살아서 꺼내 이리 데려와라. 나는 그 자식의 이야기를 꼭 들어야겠다. 널 돕도록 '모레이'라는 바르퀸틴의 선장을 붙여주지. 그 선장의 이름은 폴 샹트, 일명 커틀라스 펠리다. 제프리 기억하지? 걔만큼 멍청하지만 싸움은 잘한다.\n그놈은 바베이도스의 라겟 포인트 곶에서 널 기다릴 거다. 그놈과 '모레이'를 찾아서 마라카이보로 가라. 커틀라스는 쓸데없는 질문 없이 네 명령만 따른다. 아니, 아예 질문 자체를 안 할 거다. 그냥 네 할 일만 하고 돌아와라. 여기 앞으로 쓸 경비로 만 페소를 준다."+sTemp+". 질문 있냐?";
			link.l1 = "아니. 다 명확해. 바베이도스로 간다.";
			link.l1.go = "mtraxx_25";
		break;
		
		case "mtraxx_25":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "그럼 행운을 빌지. 빨리 가, 커틀러스랑 불쌍한 장을 너무 오래 기다리게 하지 마라.";
			link.l1 = "알겠어요, 보스! 바로 갈게.";
			link.l1.go = "mtraxx_26";
		break;
		
		case "mtraxx_26":
            DialogExit();
			CloseQuestHeader("Roger_2");
			npchar.dialog.currentnode = "mtraxx_wait";
			// belamour legendary edition по пути могут заскочить к Московиту, если рабов нет
			pchar.questTemp.Mtraxx.GiveMeSlaves = "Baster";
			AddQuestRecord("Roger_3", "1");
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			Mtraxx_PlantBegin();
		break;
		
		case "mtraxx_27":
			pchar.quest.Mtraxx_PlantGoHomeOver.over = "yes"; 
            dialog.text = "돌아왔군, 내 용감한 코르세어, 하하! 스페인 함대를 박살냈나? 피카르가 벌써 말해줬다. 잘했어!";
			link.l1 = "그래, 우리가 마라카이보에서 떠날 때 내 놈들이 제대로 한 방 먹여줬지.";
			link.l1.go = "mtraxx_28";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup3"))
			{
				dialog.text = "돌아왔구나, 내 용감한 코르세어 놈, 하하! 피카르가 이미 말해줬다. 잘했어!";
				link.l1 = "...";
				link.l1.go = "mtraxx_28";
			}
		break;
		
		case "mtraxx_28":
            dialog.text = "네 눈을 보니 보상이나 기다리고 있는 게 분명하군. 뭐, 그럴 만하지. 장이 네게 돈을 줄 거다. 어차피 우리가 구하려던 건 그의 목숨이었으니까. 청구서는 나중에 보내라 – 그 녀석 지금은 선원도, 배도 없어. 똑똑한 녀석이야, 너처럼. 곧 다시 일어설 거다.";
			link.l1 = "흠... 뭐... 좀 기다려야겠군. 일거리 있냐, Marcus? 누굴 구하거나 찾아오는 그런 거 말고?";
			link.l1.go = "mtraxx_29";
		break;
		
		case "mtraxx_29":
            dialog.text = "제일 똑똑한 촛불 노릇이 지겨워졌나? 실망시키겠군. Cutlass 같은 멍청한 놈들은 이미 충분히 있으니, 네 재능은 그에 맞게 써주지. 한 달 뒤에 너한테 맡길 일이 있다. 지금은 Isla Tesoro로 가서 Pasquale Lavoisier를 만나. 그 자는 Sharptown의 상인이다.\n그가 급한 일로 당장이라도 거친 해적을 보내달라고 했으니, 네가 딱 원하던 일일 거다. 머리 쓰는 건 적고 총질은 많은 일이지. 그에게 일주일 안에 가서 자신을 소개해야 하니 시간 낭비하지 마라. 늦으면 이 임무는 날아간다. 그리고 예의 차려라, 속이려고 들지 마. 이 남자는 해적단 사이에서 존경받는 인물이니까. 이제 가라. 한 달 뒤에 다시 내 앞에 나타나. 늦지 마!";
			link.l1 = "좋아, Marcus. 또 보자!";
			link.l1.go = "mtraxx_30";
		break;
		
		case "mtraxx_30":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				STH_SetJokerFlag(SPAIN, false); 
				log_info("You have given spanish flag");
			}
			CloseQuestHeader("Roger_3");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_4", "1");
			pchar.questTemp.Mtraxx = "pasq_start";
			Mtraxx_PasqualeBegin();
			SetFunctionTimerCondition("Mtraxx_PlantFithTaskTimer", 0, 0, 35, false);
			SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
		
		case "mtraxx_31":
            dialog.text = "이런! 죽은 놈이 돌아왔군! 우린 이미 너를 묻었었지, 이 자식아! 그런데 아직도 살아 있나 보네\n";
			link.l1 = "보다시피, 마커스...";
			link.l1.go = "mtraxx_32";
		break;
		
		case "mtraxx_32":
            dialog.text = "그럼 마라카이보에서 이스파니올라까지 왜 그렇게 오래 걸렸지? 이제 내 조직에서 나가, 이놈아. 네가 살아 있는 건 정말 반갑지만, 여기서 더 이상 줄 일거리는 없다.";
			link.l1 = "에이!.. 아깝군...";
			link.l1.go = "mtraxx_33";
		break;
		
		case "mtraxx_33":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_34x":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_34";
		break;
		
		case "mtraxx_34":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 35 && !bImCasual) // опоздал
			{
				dialog.text = "젠장 "+pchar.name+", 어디 갔다 온 거야?! 한 달 뒤에 보자고 내가 말했잖아! 여기가 군대는 아니지만, 최소한의 규율은 지켜야 할 거 아냐! 꺼져, 이제 너랑은 일 안 해!";
				link.l1 = "원하는 대로 해...";
				link.l1.go = "mtraxx_33";
				break;
			}*/
			if (GetNpcQuestPastDayParam(npchar, "task_date") < 28) // рано пришёл
			{
				dialog.text = ""+pchar.name+", 한 달 뒤에 보자고 했잖아. 지금은 너한테 쓸 시간 없어.";
				link.l1 = "좋아...";
				link.l1.go = "mtraxx_34x";
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_angry")
			{
				dialog.text = "라부아지에의 심복이 네가 그의 흑단을 엿먹였다고 하더군. 내가 쥐새끼처럼 굴지 말고 파스콸레한테 공정하게 굴라고 경고했지. 그런데 둘 다 어겼어. 머리는 잘 돌아가지만, 이건 용납 못 한다. 당장 꺼져, 그리고 여기 오는 길은 싹 잊어버려.";
				link.l1 = "젠장...";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_fail")
			{
				dialog.text = "라부아지에의 첩자가 네가 그놈의 흑단목을 제대로 넘기지 않고 일부만 가져왔다고 하더군. 멍청한 커틀러스나 볼드 같은 놈들이었으면 진짜로 전부 못 챙겼다고 믿었겠지. 하지만 너처럼 약삭빠른 놈이... 파스콸레를 속이려고 한 거냐? 내가 '그 자를 속이지 말라'고 했을 텐데! 이제 너한테 더 이상 신뢰도, 볼 일도 없다. 당장 꺼져라, 그리고 이곳 오는 길은 싹 잊어버려!";
				link.l1 = "네 라부아지에 놈도 쥐새끼야!";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_late" || pchar.questTemp.Mtraxx == "pasq_sink" || pchar.questTemp.Mtraxx == "pasq_esc")
			{
				pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират // правки прогона 3
				dialog.text = "하! Charlie Prince, 용감한 선장 놈! 라 베가에선 그게 네 새 이름이란 거, 몰랐지? 자, 짐승처럼 날뛰는 거 재밌었냐? 아니? 이번엔 행운의 여신이 너한테 등을 돌렸나 보군? 내 멍청한 부하 Cutlass 같은 놈들이 다 그렇게 산다. 오늘은 창관에서 번 돈 다 날려버리며 놀아대고, 일주일 뒤엔 내 집 문 앞에서 자기 같은 바보 선원들 월급 좀 쥐어 달라고 구걸하지. 뭐, 됐다. 이제 일 얘기나 할까?";
				link.l1 = "그래!";
				link.l1.go = "mtraxx_36";
				break;
			}
            dialog.text = "하! Charlie Prince, 용감한 선장이로군! 하하! Lavoisier의 앞잡이가 네가 잘했다고 전하더라. 우리 장사꾼에게 네가 조금이나마 예의를 차렸다는 게 마음에 드는군.";
			link.l1 = "그 자가 좀 더 후했으면 나쁠 건 없겠지...";
			link.l1.go = "mtraxx_35";
		break;
		
		case "mtraxx_35":
			pchar.questTemp.Mtraxx.Pasquale.Continue = "true"; // правки прогона 3
            dialog.text = "내가 멍청한 놈들이랑 장물 사는 놈들에 대해 뭐라고 했는지 기억나지? 그래. 앞으로 이런 일은 절대 맡지 마라. 커틀러스 같은 놈들한테나 맡기라고. 아무튼. 이제 본론 얘기할까?";
			link.l1 = "그래!";
			link.l1.go = "mtraxx_36";
		break;
		
		case "mtraxx_36":
            dialog.text = "좋아! 장 피카르가 여기로 오고 있어, 그가 더 자세히 말해줄 거다. 너랑 장이 이번 임무를 같이 하게 될 거야. 게다가, 이번이 그가 너한테 진 빚을 갚을 기회지... 저기 오고 있군!";
			link.l1 = "...";
			link.l1.go = "mtraxx_37";
		break;
		
		case "mtraxx_37":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_38";
			chrDisableReloadToLocation = true;
			// преобразуем Пикара
			sld = characterFromId("Mrt_Rocur");
			sld.model = "Jan_Pikar";
		
			SetCharacterPerk(sld, "GunProfessional");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			GiveItem2Character(sld, "blade_17");
			EquipCharacterbyItem(sld, "blade_17");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterbyItem(sld, "pistol6");
			TakeNItems(sld, "bullet", 40);
			TakeNItems(sld, "gunpowder", 40);
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.dialog.currentnode = "rocur_29";
			sld.greeting = "Rocur_03";
			Characters_RefreshModel(sld);
			LAi_SetCheckMinHP(sld, 10, true, "");
			TakeNItems(sld, "potion2", 7);
			TakeNItems(sld, "potion3", 7);
			TakeNItems(sld, "potion4", 7);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "mtraxx_38":
            dialog.text = "내 놈이 네 약탈에 합류할 거다. 이름은 루카 바야르, 대개 루크 레프리콘으로 알려져 있지. 그와 그의 놈들은 부카니어, 즉 히스파니올라 숲에서 평생을 사냥하며 살아온 사냥꾼들이다. 그러니 정글을 헤치고 다니는 데는 도가 텄지. 네 놈 전사들을 그놈들한테 붙여라. 그러면 메리다는 네 것이나 다름없다. 전리품의 3분의 1은 네가 가져가라. 나머지는 장에게 간다. 장, 네 몫에서 이 용감한 선장에게 빚을 갚고, 남은 건 내게 가져와라. 그다음에 우리끼리 정산하지. 질문 있나? 좋아! 레프리콘은 우리 항구에서 널 기다릴 거다. 행운을 빌지, 해적 놈들아, 하하!\n";
			link.l1 = "...";
			link.l1.go = "mtraxx_39";
		break;
		
		case "mtraxx_39":
            DialogExit();
			CloseQuestHeader("Roger_4");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_5", "1");
			pchar.questTemp.Mtraxx = "merida_start";
			Mtraxx_MeridaBegin();
			LAi_SetHuberType(npchar);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Mtraxx_MeridaAddPicar", 5.0);
			pchar.GenQuest.HunterLongPause = true;
		break;
		
		case "mtraxx_40":
            dialog.text = "돌아왔군, 우리 용감한 살인마! 네가 습격한 소문은 이미 우리 귀에 들어왔지.";
			link.l1 = "듣기 싫군. 그런 건 모르는 게 나아...";
			link.l1.go = "mtraxx_41";
		break;
		
		case "mtraxx_41":
            dialog.text = "나만 믿어, 그런 일은 절대 없어, 친구야. 뭐, 됐다. 피카르가 너한테 빚 다 갚았냐?";
			link.l1 = "그래.";
			link.l1.go = "mtraxx_42";
		break;
		
		case "mtraxx_42":
            dialog.text = "아주 좋아. 루크 레프리콘이 너한테 좋은 인상을 남겼냐?";
			link.l1 = "그놈이 그랬지.";
			link.l1.go = "mtraxx_43";
		break;
		
		case "mtraxx_43":
            dialog.text = "좋아, 그럼. 모두들 만족하고, 모두 돈도 받았지.";
			link.l1 = "마르쿠스, 나한테 시킬 일 있나?";
			link.l1.go = "mtraxx_44";
			// belamour legendary edition отказ после событий Мериды
			link.l2 = "있잖아, Marcus, 내가 다 생각해봤는데 이 일은 내 길이 아니야. 미안하지만, 이미 마음을 정했어.";
			link.l2.go = "mtraxx_44a";
		break;
		
		case "mtraxx_44":
            dialog.text = "아직 제대로 된 일은 없어. 하지만 개인적으로 부탁할 게 있는데. 관심 있나?";
			link.l1 = "알겠어, 두목. 무슨 부탁이야?";
			link.l1.go = "mtraxx_45";
		break;
		
		case "mtraxx_45":
            dialog.text = "라 베가 해안 근처에 '키티'라는 피나스가 있다. 며칠째 거기서 브리지타운까지 호위를 기다리고 있지. 뻔한 이유로 혼자 항해하게 둘 수는 없어. 같이 가줄 수 있겠나? 돌아오면 진짜 일을 맡기지. 물론, 이번 호위에 대한 보수도 줄 거다.";
			link.l1 = "거래지.";
			link.l1.go = "mtraxx_46";
		break;
		
		case "mtraxx_46":
            dialog.text = "좋아! 항해 잘했군.";
			link.l1 = "고맙다!";
			link.l1.go = "mtraxx_47";
		break;
		
		case "mtraxx_47":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_6", "1");
			pchar.questTemp.Mtraxx = "ignasio_start";
			sld = characterFromId("Mtr_KittyCap");
			DeleteAttribute(sld, "DontDeskTalk");
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
		break;
		// belamour legendary edition -->
		case "mtraxx_44a":
            dialog.text = "뭐라고?! 내가 널 거리에서 끌어냈고, 네 주머니에 호박이랑 보석도 채워줬잖아! 그런데 이렇게 보답하는 거냐?";
			link.l1 = "메리다가 나에게 이 일에 내가 충분히 무자비하지 않다는 걸 보여줬지. 너랑 네 놈들만큼은 아니더군. 너무 잔인하게 굴진 마라.";
			link.l1.go = "mtraxx_45a";
		break;
		
		case "mtraxx_45a":
            dialog.text = "약골 놈! 썩 꺼져라! 짐이나 나르든가, 아니면 다른 찌질이들처럼 술 처먹고 죽어버려!";
			link.l1 = "...";
			link.l1.go = "mtraxx_46a";
		break;
		
		case "mtraxx_46a":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "First time";
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			sld = characterFromId("Mtr_KittyCap");
			sld.lifeday = 0;
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx = "fail";
			if(CheckAttribute(pchar, "GenQuest.HunterLongPause")) DeleteAttribute(pchar, "GenQuest.HunterLongPause");
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <--- legendary edition
		case "mtraxx_48":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "아, 여기 있었군... 널 기다리고 있었다. '키티'를 호위한 대가로 1만을 주지.";
			link.l1 = "고맙다... 너랑 얘기할 게 있어, Marcus.";
			link.l1.go = "mtraxx_49";
		break;
		
		case "mtraxx_49":
            dialog.text = "네가?! 하하! 쏴 봐!..";
			link.l1 = "장 피카르가 어떻게 노예가 됐는지 기억하지? 처음엔 영국 사략선과 함께 네덜란드 상단을 약탈했지. 그런데 똑같이 스페인 중무장 갤리온에게 당했어.";
			link.l1.go = "mtraxx_50";
		break;
		
		case "mtraxx_50":
            dialog.text = "기억해라. 그리고?";
			link.l1 = "브리지타운에서 이그나시오 마르코가 나한테 접근했지. 영국을 위해 일하는 그 포르투갈 사략선 말이다. 그놈이 쿠라사오와 트리니다드 사이 무인도 근처 해안에서 네덜란드 대상단을 털자고 제안하더군.";
			link.l1.go = "mtraxx_51";
		break;
		
		case "mtraxx_51":
            dialog.text = "그래, 그래... 동의했나?";
			link.l1 = "내가 그랬지. 우선, 꽤 괜찮은 거래였거든. 그리고 피카르의 이야기가 생각나서 조사해 보기로 했지...";
			link.l1.go = "mtraxx_52";
		break;
		
		case "mtraxx_52":
            dialog.text = "그래, 분명 그랬겠지.";
			link.l1 = "그래. 대상단이 있었지, 우리는 깔끔하게 일 처리했어. 그 다음엔 해안에서 전리품을 나눴지. 하지만 먼저 내가 몰래 망원경 든 감시병을 언덕 위에 보냈어. 그게 통했지, 곧바로 스페인 함대가 나타났거든, 무거운 갤리온이 이끌고 있었어.";
			link.l1.go = "mtraxx_53";
		break;
		
		case "mtraxx_53":
            dialog.text = "네 동료가 분명 도망쳤으니, 그래서 스페인 놈들이 널 쫓은 거냐?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.LosadaSink")) 
			{
				link.l1 = "그래, 맞아. 놈들은 그 자식한테 신경도 안 썼지. 지들한테는 안타까운 일이야. 우리가 스페인 놈들이 평생 못 잊을 만큼 박살냈거든. 카스티야 놈들, 싸움은 잘했지만 결국 우리가 전대를 전부 박살냈지.";
				link.l1.go = "mtraxx_53x";
			}
			else
			{
				link.l1 = "그래. 놈들은 그 자에게 신경도 안 썼지. 나는 간신히 도망쳤어, 내 감시인 덕분에...";
				link.l1.go = "mtraxx_53y";
			}
		break;
		
		case "mtraxx_53x":
			DeleteAttribute(pchar, "questTemp.Mtraxx.LosadaSink");
            dialog.text = "헤! 에두아르도 데 로사드 함대를 박살냈다니! 넌 진짜 바다의 악마다, 왕자 놈! 분명 스페인 놈들이 벌써 네놈 잡으려고 사냥꾼들을 보냈겠지.";
			link.l1 = "걔네들 꼴 좋지... 그래도 이 쓰레기들은 처리해야지, Ignacio. 무슨 말인지 알겠지.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_53y":
            dialog.text = "헤! 카스티야 놈들이 네가 빠져나간 걸 알아챘을 때 얼마나 난리가 났을지 상상만 해도 웃기다! 잘했어!";
			link.l1 = "그건 걔네 문제지, 내 문제가 아니야. 그래도 이 쓰레기들은 처리해야겠지, Ignacio. 무슨 말인지 알겠지.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_54":
            dialog.text = "내가 처리하지. 이 Ignacio Marco에 대해 더 알아봐야겠어. 누군가를 위해 일하고 있을지도 몰라. 내 부하들에게 '관심'을 보이는 게 수상하군. 무슨 배를 소유하고 있지?";
			link.l1 = "폴라크선, '토레로'. 독특한 배로군, 분명히 원본 설계겠지.";
			link.l1.go = "mtraxx_55";
		break;
		
		case "mtraxx_55":
            dialog.text = "좋아, 그럼 더 쉽게 그녀를 쫓을 수 있겠군... 알겠다. 그리고 너한테 일이 하나 있다, 프린스. 할 준비 됐나?";
			link.l1 = RandSwear()+"당연하지, 두목!";
			link.l1.go = "mtraxx_56";
		break;
		
		case "mtraxx_56":
            dialog.text = "그럼 잘 들어라. 얼마 전에 우리 지역에 특이한 해적이 하나 있었지. 이름은 울프릭 이오간센, 일명 레드 울프다. 아주 괴짜였지. 몇 해 전에 북유럽에서 여기로 왔다. 이 바이킹은 르바쇠르에게 보호비도 안 내고, 누구랑도 어울리지 않고 혼자 다녔다. 완전 비밀스러운 놈이었지, 그의 선원 중 살아서 나간 놈은 아무도 없었다. 선술집에서 약탈 얘기하다가 혀가 풀린 놈들은 직접 혀를 잘랐다는 소문도 돌았고... 우리 같은 놈들과 달리, 울프릭은 창녀나 술에 돈을 낭비하지도 않았고, 약탈품을 헐값에 팔지도 않았지. 은행가도 안 믿었고, 배도 바꾼 적이 없었다. '프레이야'라는 멋진 코르벳과 충성스러운 선원들이 있었는데, 그들에게는 입 다무는 값까지 넉넉히 쳐줬다. 내 생각엔, 가능한 한 금을 모아서 유럽으로 돌아가 왕처럼 살려고 했던 것 같다. 하지만 스페인 사냥꾼들 덕분에 그 꿈은 끝났지. 이놈이 스페인에 엄청난 피해를 입혀서, 징벌대가 이스파니올라 근해에서 그를 쫓아 '프레이야'를 침몰시키고, 선원 전부와 함께 울프도 죽였다. 얕은 바다에서 스페인 배들에게 포위당한 레드 울프는 그렇게 죽음을 맞았다. 문제는, 라 베가에 있는 놈들은 다 울프의 보물 얘기를 알고 있었고, 침몰한 '프레이야'도 찾아냈지만, 현지인이나 인디언 잠수부 누구도 보물을 못 찾았다는 거다. 바보가 아니었으니, 분명 그 근처 어딘가에 그와 선원들만 아는 엄청난 은닉처가 있었을 거다. 하지만... 이유는 뻔하니 그놈들에게 물어볼 수도 없지. 이제부터가 재밌는 부분이다. 내가 그놈 배에 있던 자물쇠 상자에서 멀쩡한 항해일지를 하나 손에 넣었거든. 보물에 대한 뚜렷한 단서는 없지만, 네가 행간을 잘 읽으면 뭔가 찾을 수 있을 거다. 일지를 읽고, 바이킹이 카리브 해에서 2년간 약탈한 보물을 어디 숨겼는지 알아내서 찾아라. 성공하면, 3분의 2는 네 거다. 할래?";
			link.l1 = "흠... 어두운 방에서 검은 고양이 찾는 거랑 다를 게 없군. 항해일지는 어디 있지?";
			link.l1.go = "mtraxx_57";
		break;
		
		case "mtraxx_57":
            dialog.text = "여기, 가져가라. 행운을 빌지!";
			link.l1 = "고맙다, 정말 필요할 거야...";
			link.l1.go = "mtraxx_58";
		break;
		
		case "mtraxx_58":
            DialogExit();
			CloseQuestHeader("Roger_6");
			npchar.dialog.currentnode = "mtraxx_wait";
			GiveItem2Character(pchar, "wolfreeks_book");
			AddQuestRecord("Roger_7", "1");
			pchar.questTemp.Mtraxx = "wolfreek_start";
			pchar.questTemp.Mtraxx.Logbook.CanRead = "true";
			pchar.questTemp.Mtraxx.Logbook.Page1 = "true";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
		break;
		
		case "mtraxx_59":
            dialog.text = "아, 우리 용감한 선장이 왔군. 붉은 늑대의 보물은 어떻게 됐지?";
			link.l1 = "하고 있어. 이것 좀 도와줘야겠다.";
			link.l1.go = "mtraxx_60";
		break;
		
		case "mtraxx_60":
            dialog.text = "듣고 있지.";
			link.l1 = "Wulfric의 항해일지에 'Gord'라는 알 수 없는 단어가 여러 번 적혀 있군. 조사를 계속하려면 그 의미를 반드시 알아내야 해.";
			link.l1.go = "mtraxx_61";
		break;
		
		case "mtraxx_61":
            dialog.text = "흠... 고드라고 했나... 나도 처음 듣는 이름이군. 좋아, 일주일 뒤에 다시 와라. 배에서 회계 일을 하는 똑똑한 놈들 몇 명한테 물어보지. 적어도 숫자 세고 글은 읽을 줄 아니까. 뭔가 실마리를 줄지도 모르지.";
			link.l1 = "좋아, Marcus. 그럼 일주일 후에 보자.";
			link.l1.go = "mtraxx_62";
		break;
		
		case "mtraxx_62":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			SetFunctionTimerCondition("Mtraxx_WolfreekTimer", 0, 0, 7, false);
		break;
		
		case "mtraxx_63":
            dialog.text = "대답해 주지. 어떤 똑똑한 놈이 알려줬거든. 고르드는 자유 야를의 요새화된 정착지란다.";
			link.l1 = "자유로운 야를? 그게 누구야?";
			link.l1.go = "mtraxx_64";
		break;
		
		case "mtraxx_64":
            dialog.text = "뭐, 바이킹 해적 제독 같은 거지. 예를 들어, 나는 자유로운 야를이고 라 베가는 내 고르드야. 레드 울프 녀석, 조상들 이야기를 꽤 즐겼나 보군, 하하! 이 정보가 도움이 됐냐?";
			link.l1 = "아직 몰라. 먼저 기록을 비교해 봐야겠어. 그러니까 Gord가 정착지를 뜻하는 거군... 고마워, Marcus!";
			link.l1.go = "mtraxx_65";
		break;
		
		case "mtraxx_65":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			Mtraxx_WolfreekReadLogbookFourth();
		break;
		
		case "mtraxx_66":
            dialog.text = "그래? 그 잘난 얼굴 보니 성공했군.";
			link.l1 = "그래. 레드 울프의 보물이 드디어 발견됐어! 쉽지는 않았지만.";
			link.l1.go = "mtraxx_67";
		break;
		
		case "mtraxx_67":
            dialog.text = "우리 바이킹이 얼마나 챙겼지?";
			link.l1 = "75만 페소와 900 두블룬.";
			link.l1.go = "mtraxx_68";
		break;
		
		case "mtraxx_68":
            dialog.text = "호호! 잘했군, 왕자. 내 몫은 어쩔 거지?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "여기, 이거 가져가라. 약속대로다: 25만 페소와 300 두블룬이다.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "페소랑 두블룬 전부 내 선실에 있다. 잠깐만 기다려, 내가 가져올 테니까!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_68_1":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_68_2";
		break;
		
		case "mtraxx_68_2":
            dialog.text = "내 몫 가져왔냐?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "여기, 이거 가져가라. 약속대로다: 25만 페소와 300 두블룬이다.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "그래, 그래, 지금 가고 있어!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_69":
			AddMoneyToCharacter(pchar, -250000);
			RemoveDublonsFromPCharTotal(300); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "아주 좋아. 또 한 건 제대로 해냈군. 잘했어!";
			link.l1 = "Marcus, Ignacio Marco에 대해 뭐 알아낸 거 있나?";
			link.l1.go = "mtraxx_70";
			// mitrokosta возможность отстройки исламоны
			pchar.questTemp.IslaMona = "start";
		break;
		
		case "mtraxx_70":
            dialog.text = "그래, 하지만 먼저 확인해야겠어...";
			link.l1 = "뭐?";
			link.l1.go = "mtraxx_71";
		break;
		
		case "mtraxx_71":
            dialog.text = "나는 마르코가 누군가와 연관되어 있다는 의심이 들어... 네가 그게 누군지 알아내야겠다. 마르티니크로 가라. 생피에르에 배를 두고 정글을 지나 르 프랑수아로 가. 우리 사람이 거기서 목격됐다는 말을 들었거든. 해적들한테 묻지 말고, 그냥 지켜보고 관찰해라. 그를 찾으면 따라가서 어디로 가는지, 누구를 만나는지 확인해. 그나 그의 배를 공격하지 마라. 그러면 내가 지금 준비 중인 계획을 망치게 될 테니까! 분명히 경고했다! 따라가서 지켜보고, 충분히 알게 되면 내게 돌아와라. 그 자식 목을 조르고 싶은 마음이 들겠지만, 머리는 차갑게 유지해라. 이제 가라. 3주 시간이 있다. 행운을 빈다.";
			link.l1 = "가는 중이야, 두목.";
			link.l1.go = "mtraxx_72";
		break;
		
		case "mtraxx_72":
            DialogExit();
			CloseQuestHeader("Roger_7");
			RemoveItems(pchar, "wolfreeks_book", 1);
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_8", "1");
			pchar.questTemp.Mtraxx = "corrida_start";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1.location = "Martinique";
			pchar.quest.mtraxx_corrida_martinique.function = "Mtraxx_CorridaStart";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1.location = "LaVega_exittown";
			pchar.quest.mtraxx_pasq_continue.function = "Mtraxx_PasqualeJan";
			bDisableFastReload = true;
			//SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
			
		case "mtraxx_73":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 22) // опоздал
			{
				dialog.text = "젠장, 프린스! 네가 그렇게 굼뜨지만 않았어도 복수도 하고 엄청난 돈도 손에 넣을 수 있었을 텐데! 너한테 이런 실망을 할 줄은 몰랐지만, 네가 착한 녀석이니 용서해주지. 한 달 뒤에 내 눈에 다시 명예를 되찾을 기회가 있을 거다. 전부 모아서 약탈을 준비하고 있다!\n한 달 뒤에, 강력한 단 한 척의 배만 끌고 내게 와라. 루크, 커틀라스, 제프리, 그리고 장도 같이 참가한다. 하루라도 늦지 마라!";
				link.l1 = "알겠어, Marcus. 다시는 이런 일 없을 거야!";
				link.l1.go = "mtraxx_73x";
				break;
			}*/
			dialog.text = "때마침 잘 왔군! 당장 나한테 보고해.";
			link.l1 = "나는 내 채무자를 르 프랑수아까지 추적했어. 그의 폴라크는 코르벳과 프리깃이 포함된 편대의 일부였지. 마르코 본인은 바르바종을 직접 찾아갔고, 그의 집에서 두 시간 동안 회의를 가졌어. 다른 방문객들은 그의 경비병들이 내보냈지. 그 후 그는 우울하게 생긴 두 놈과 함께 집을 나섰어. 한 놈은 붉은 머리에 수염이 있었고, 라이테르 흉갑을 입고 있었지. 다른 놈은 콧수염에 무거운 참호 갑옷을 입고 있었어. 그들은 모두 항구로 가서 내가 생피에르에 도착하기 전에 떠나버렸지.";
			link.l1.go = "mtraxx_74";
		break;
		
		/*case "mtraxx_73x":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "5");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
		break;*/
		
		case "mtraxx_74":
            dialog.text = "좋아. 이제 모든 상황이 보이는군. 네가 본 그 두 놈은 바르바존이나 잭맨 밑에서 일하는 자들이야. 내 부하인 볼드와 커틀라스처럼 붙어 다니지만, 싸움은 더 잘하지. 빨간 머리 녀석은 프로울러라고 하는데, '커틀피쉬'라는 코르벳함의 선장이야. 콧수염 난 놈은 굴이고, '머시리스'라는 프리깃을 타고 다닌다. 그리고 우리 친구 이그나시오 말인데, 그 자는 영국놈들이나 스페인 돈 로사드뿐 아니라 바르바존을 위해서도 일하고 있지. 그래서 너랑 피카르를 함정에 빠뜨리려 한 거다.";
			link.l1 = "왜?";
			link.l1.go = "mtraxx_75";
		break;
		
		case "mtraxx_75":
            dialog.text = "바르바존의 명령이다. 너는 몰랐겠지만, 자크는 내 밥에 오줌 싸는 기회를 절대 놓치지 않는 놈이지. 뻔한 이유로 대놓고 나한테 대들진 못하니까, 항상 뒤에서 내게 칼을 꽂는다. 피카르와 네가 내 사람인 걸 그 자식도 알고 있었어. 자기 용병을 너한테 보낸 것도 그놈다운 짓이지. 그리고 네가 직접 봤듯이, 멍청이를 보낸 것도 아니었다.";
			link.l1 = "마르코부터 처리하고 바로 바르바존을 찾아가겠다...";
			link.l1.go = "mtraxx_76";
		break;
		
		case "mtraxx_76":
            dialog.text = "이딴 헛소리 집어치워! 너 따위가 바르바존이랑 정면으로 붙어서 이길 가능성은 없어. 그는 널 아주 쉽게 박살낼 거다. 우린 그 자식 수법 그대로 갚아줄 거야, 그놈 졸개들부터 쳐서 말이지. 할 준비 됐냐? 더럽고 위험한 일이야.";
			link.l1 = "내 취향에 딱 맞는 일이군!";
			link.l1.go = "mtraxx_77";
		break;
		
		case "mtraxx_77":
            dialog.text = "이그나시오, 마르코, 프라울러, 굴, 그리고 바르바존의 또 다른 부하인 조커 짐이 황금 함대의 스페인 선박 중 하나를 탈취할 계획을 세웠다. 이 작전 전체는 바르바존이 직접 고안한 것이고, 나는 내 첩자들을 통해 그 세부사항을 알아냈지. 황금 함대의 대형 갤리온 한 척이 아바나 조선소에 머물렀고, 나머지 전대는 스페인으로 떠났다. 그 갤리온은 수리를 마쳤고 곧 두 척의 배와 함께 유럽으로 향할 예정이다. 전대는 쿠바에서 북동쪽으로 항해할 예정이지만, 정확한 항로는 나도 모른다.\n스페인 선박들이 산토도밍고로 향한 뒤 푸에르토리코 해안을 따라 곧장 대양으로 나갈 계획이라는 정보를 입수했다. 바르바존도 이 사실을 알고 있지. 하지만 에스파뇰라 섬은 남쪽뿐 아니라 북쪽으로도 돌아갈 수 있기 때문에, 항로를 바꿔 산토도밍고에 들르지 않고 터크스나 이슬라-테소로를 통해 바로 대양으로 나갈 수도 있다. 그래서 자크는 만일을 대비해 교활한 여우 이그나시오를 쿠바로 보냈다.\n마르코의 임무는 쿠바에서 출항해 나중에 함대를 따라잡을 예정인 스페인 갤리온의 항해 일정을 알아내는 것이다. 그는 스페인 내부에 연줄이 있으니 이 일은 별문제가 되지 않을 거다. 바르바존의 나머지 일당은 상 마르탱에서 마르코를 기다리고 있는데, 그곳이 이 노획물을 사냥하기에 최적의 장소다. 하지만 마르코와 네덜란드인들은 사이가 좋지 않아서 상 마르탱 해역에 들어갈 수 없으니, 멀리서 동료들에게 소식을 전해야 할 거다...";
			link.l1 = "여기서 내가 뭘 해야 하는지 알 것 같군...";
			link.l1.go = "mtraxx_78";
		break;
		
		case "mtraxx_78":
            dialog.text = "꽤 영리하군, 하지만 아직 끝나지 않았어. 나는 가브리엘라 차파다의 도움으로 이 계획을 망쳐놨지. 그 여자 알잖아. 우리 둘이서 스페인 놈들에게 해적 매복이 푸에르토리코 근처에 있을 거라고 알려줬어. 그래서 갈레온은 그쪽으로 항해하지 않지만, 대신 몰래 해적 사냥꾼 함대를 그곳에 보냈지. 네가 할 일이 몇 가지 있다. 첫 번째는 '토레로'를 찾아서 붙잡는 거야. 그 선장을 어떻게 해야 할지는 네가 잘 알겠지.";
			link.l1 = "당연하지...";
			link.l1.go = "mtraxx_79";
		break;
		
		case "mtraxx_79":
            dialog.text = "둘째로, 스페인 황금 갤리온의 실제 항로를 알아내야 해. 마르코가 그 일정을 갖고 있을 거다. 그걸 가져와서 나한테 보내.";
			link.l1 = "어떻게?";
			link.l1.go = "mtraxx_80";
		break;
		
		case "mtraxx_80":
			GiveItem2Character(pchar, "Dove"); 
            dialog.text = "공중으로 보내는 거다. 새장 하나 가져가라... 이 녀석은 스파이크, 라 베가에서 태어나고 자란 전서구다. 트리니다드에서도 여기로 돌아올 줄 안다. 일정표를 손에 넣으면 쪽지를 써서 스파이크 다리에 묶고 날려 보내라. 몇 시간 안에 스파이크가 내게로 날아올 거다. 녀석 잘 챙겨라, 왕자!";
			link.l1 = "당연하죠, 두목!";
			link.l1.go = "mtraxx_81";
		break;
		
		case "mtraxx_81":
            dialog.text = "셋째, '토레로'호를 타고 생마르탱으로 항해해라. 반드시 그 배만 타야 한다! 안 그러면 놈들이 너무 빨리 눈치챌 거다. 놈들에게 푸에르토리코로 항해하라는 신호를 보내. 거기서 스페인 놈들이 기다리고 있을 거다. 신호 암호는 마르코의 서류에 있을 테니, 아니면 직접 마르코한테 배워도 된다.";
			link.l1 = "알겠군. 바르바존 놈들을 스페인 놈들한테 보낸 건 영악한 수지, 하하!";
			link.l1.go = "mtraxx_82";
		break;
		
		case "mtraxx_82":
            dialog.text = "그래, 맞아! 나는 그림자 속에서 놈을 치겠다. 그 자가 했던 것처럼. 그리고 마지막으로, 신호를 보내면 곧바로 출항해서 스페인 갈레온과 호위함을 가로막아라. 지체할 시간 따윈 없다.";
			link.l1 = "폴라크 한 척으로? 무거운 갤리언이랑 배 두 척 더, 그리고 분명히 스쿠너도 아니라고? 놈들이 나를 갈기갈기 찢어버릴 거야!";
			link.l1.go = "mtraxx_83";
		break;
		
		case "mtraxx_83":
            dialog.text = "애처럼 징징거리지 마! 왜 내가 스파이크를 보내줄 거라 생각하지? 증원 없이 내버려두진 않을 거다. 그냥 대상단이 도망치지 못하게 해, 바다까지 못 가게 막아. 알겠어?";
			link.l1 = "그래, 두목.";
			link.l1.go = "mtraxx_84";
		break;
		
		case "mtraxx_84":
            dialog.text = "네 보상은 금화 한 짐과 마르코의 폴라크레다. 그 배가 아주 쓸만하다고들 하더군. 질문 있나? 임무는 제대로 이해했지?";
			link.l1 = "나는 커틀라스가 아니야, 뭘 해야 할지는 안다. '토레로'를 어디서 가로채야 하지?";
			link.l1.go = "mtraxx_85";
		break;
		
		case "mtraxx_85":
            dialog.text = "우리가 이렇게 얘기하는 동안 배는 쿠바에서 필립스버그로 곧장 빠르게 항해 중이다. 지금쯤 토르투가 근처거나, 아니면 그보다 좀 더 동쪽일 거다. 그러니 닻 올리고 생마르탱으로 가서, 섬에서 멀지 않은 곳에서 '토레로'를 가로채라. 단, 바르바종 놈들이 싸우는 걸 보면 내 계획이 망치니까 조심해라.";
			link.l1 = "바로 한다!";
			// belamour legendary edition испанский флаг к выдаче -->
			if(IsCharacterPerkOn(pchar,"FlagSpa")) link.l1.go = "mtraxx_86";
			else link.l1.go = "mtraxx_85f";
		break;
		
		case "mtraxx_85f":
			STH_SetJokerFlag(SPAIN, true);
			log_info("You have received a spanish flag");
			pchar.questTemp.GiveMeSpaFlag = true;
            dialog.text = "뭐야, 젠장? 벽난로 쇠꼬챙이로 한 대 갈겨줄까, 프린스. 이런 기본적인 것도 내가 설명해야 한다고는 생각 못 했지. 스페인 깃발이나 잘 붙잡고 있어, 안 그러면 시작도 전에 다 망칠 테니까. 그거 내놔. 이제 꺼져!";
			link.l1 = "나 이미 바다에 나와 있어, 두목\n";
			link.l1.go = "mtraxx_86";
		break;
		// <-- legendary edition
		case "mtraxx_86":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			AddQuestRecord("Roger_8", "6");
			pchar.questTemp.Mtraxx = "corrida_marko";
			/*pchar.quest.mtraxx_corrida_landtimer.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.function = "Mtraxx_CorridaLandTimer";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_corrida_checktime.function = "Mtraxx_CorridaCheckTime";*/
			pchar.quest.mtraxx_corrida_torero.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.hour  = sti(GetTime()+12);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.function = "Mtraxx_CorridaToreroOnMap";
			SetFunctionTimerCondition("Mtraxx_CorridaTimeFindTorero", 0, 0, 7, false); // время на перехват Тореро, снимать при потоплении или захвате
		break;
		
		case "mtraxx_87":
            dialog.text = "그래서, 왕자 놈, 너는 뭐든 다 망쳐버리는 거냐?";
			link.l1 = "내가 했지. 이번 임무는 내가 생각했던 것보다 훨씬 더 힘들었어. 이제 나한테 화내고 내쫓아도 돼.";
			link.l1.go = "mtraxx_88";
		break;
		
		case "mtraxx_88": // belamour legendary edition увеличиваем срок
            dialog.text = "그만해라, 됐어. 이런 일은 다 있는 거야. 너도 훌륭한 코르세어고, 누구나 가끔은 실패하지. 금을 못 챙긴 건 아쉽지만... 한 군데서 못 얻으면 다른 데서 얻으면 되지, 하하! 명예를 회복할 기회가 있을 거다. 3주 후에 나한테 와라. 가능하면 더 튼튼한 배로, 하지만 한 척만 가져와라. 우리 전부가 한 함대가 될 거니까. 다 같이 약탈하러 갈 거다!\n3주 후에 강력한 배 한 척만 타고 나한테 와라. 루크, 커틀라스, 제프리, 그리고 장도 참가할 거다. 늦지 마!";
			link.l1 = "안 해, 두목!";
			link.l1.go = "mtraxx_89";
		break;
		
		case "mtraxx_89":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				STH_SetJokerFlag(SPAIN, false); 
				log_info("You have given a spanish flag");
			}
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "22");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			//SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
			if (CheckCharacterItem(pchar, "Dove")) RemoveItems(pchar, "Dove", 1);
		break;
		
		case "mtraxx_board":
            dialog.text = "호호, 이봐, 꼬마! 내가 여기 있을 줄은 몰랐지? 하하하! 결국 스페인 호송대를 찾아냈다니까...";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Gold")) // был абордаж
			{
				link.l1 = "그래, 두목, 했어. 쉽진 않았지만.";
				link.l1.go = "mtraxx_board_1";
			}
			else
			{
				link.l1 = "그래, 하지만 골든 갤리온은 금과 함께 가라앉았지.";
				link.l1.go = "mtraxx_board_7";
			}
		break;
		
		case "mtraxx_board_1":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_GOLD);
            dialog.text = "우리가 금을 얼마나 챙겼지, 왕자?";
			if (iTotalTemp < 1) link.l1 = "에... 아무것도 아니야.";
			else link.l1 = "크크... "+iTotalTemp+" 전부 합쳐서!";
			link.l1.go = "mtraxx_board_2";
		break;
		
		case "mtraxx_board_2":
			if (iTotalTemp < 20)
			{
				dialog.text = "젠장! 스페인 놈들이 우리가 못 찾게 바다에 던져버린 게 틀림없어. 그래도 대가를 치렀지. 바르바존의 놈들도 마찬가지였으니, 그것도 승리라 할 수 있겠군...";
				link.l1 = "금에 대해서는 미안하다... 이제 어쩔 거냐, 마커스? 라 베가로 가는 거냐?";
				link.l1.go = "mtraxx_board_4";
				AddQuestRecord("Roger_8", "18");
				break;
			}
			if (iTotalTemp >= 20 && iTotalTemp < 300)
			{
				dialog.text = "한심하군. 이걸로 내가 여기까지 온 비용도 안 나와. 스페인 놈들이 우리가 못 찾게 바다에 던졌나 보지. 그래도 그 값은 받았으니 됐다. 바르바존 놈들도 마찬가지고, 그것도 승리지...";
				link.l1 = "금에 대해서는 미안하다... 그래도 나눠 갖자.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				break;
			}
			if (iTotalTemp >= 300 && iTotalTemp < 700)
			{
				dialog.text = "이건 형편없는 전리품이군. 겨우 경비나 메울 정도지. 스페인 놈들이 우리가 못 가져가게 일부러 바다에 던져버렸나 보군. 그래도 값은 치렀지. 바르바존의 놈들도 마찬가지였으니, 그것도 승리라 할 수 있겠군...\n";
				link.l1 = "금은 미안하게 됐군... 그래도 나눠 가지자.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				break;
			}
			if (iTotalTemp >= 700 && iTotalTemp < 1000)
			{
				dialog.text = "나쁘지 않군, 그래도 더 나을 줄 알았지. 스페인 놈들이 우리가 못 챙기게 일부를 바다에 던졌나 보군. 뭐, 어쨌든 대가는 치렀지. 바르바존 놈들도 마찬가지고, 그것도 승리라 할 수 있겠지...";
				link.l1 = "전리품 나누자!";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "20");
				AddCharacterExpToSkill(pchar, "Fortune", 200);
				break;
			}
			dialog.text = "훌륭하군! 멋진 전리품을 챙겼어, 친구! 그리고 바르바존의 놈들도 당할 만큼 당했지, 하하!";
			link.l1 = "크크, 금이 엄청 많군! 나눠 가지자!";
			link.l1.go = "mtraxx_board_3";
			AddQuestRecord("Roger_8", "21");
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mtraxx_board_3":
			RemoveCharacterGoods(pchar, GOOD_GOLD, makeint(iTotalTemp/2));
			WaitDate("", 0, 0, 0, 3, 10);
			LAi_Fade("", "");
            dialog.text = "... 항상 우리 형제단에서 하던 대로지 - 각자 공평하게 나누는 거다. '토레로'는 네가 가져라, 그게 네 전리품이니까.";
			link.l1 = "다음은 뭐지, Marcus? 우리 La Vega로 가는 거야?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_board_4": // belamour legendary edition увеличиваем срок до 3х месяцев
            dialog.text = "나는 반드시 라 베가에 있을 거다, 거기서 3주 동안 널 기다릴 거야. 준비되면 와라. 가능하면 더 튼튼한 배로 오면 좋겠지만, 한 척만 가져와라 - 우린 전체 함대가 될 거니까. 내 부하들 전부 출동시킬 거다. 넌 내 지휘 아래 들어가게 될 거고, 장 핸섬, 대머리 제프리, 클리버 펠리, 그리고 루크 레프리콘도 함께 갈 거다. 준비해라. 이번엔 제대로 된 원정이고, 전리품도 꽤 클 거다. 자세한 건 나중에 알려주지.";
			link.l1 = "좋아요, 두목! 3주 뒤 라 베가에서 보자.";
			link.l1.go = "mtraxx_board_5";
		break;
		
		case "mtraxx_board_5":
            dialog.text = "잘 가라, 죽일 놈! 하하!";
			link.l1 = "...";
			link.l1.go = "mtraxx_board_6";
		break;
		
		case "mtraxx_board_6":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Ship_SetTaskRunAway(SECONDARY_TASK, sti(npchar.index), sti(pchar.index));
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_corrida_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_corrida_complete.function = "Mtraxx_CorridaComplete";
			RemoveItems(pchar, "wolfreeks_book", 1);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				STH_SetJokerFlag(SPAIN, false); 
				log_info("You have given spanish flag");
			}
		break;
		
		case "mtraxx_board_6x":
            dialog.text = "또 뭐 있어?";
			link.l1 = "아니, 그렇게 생각 안 해. 난 이미 내 배로 가는 중이야.";
			link.l1.go = "mtraxx_board_6y";
		break;
		
		case "mtraxx_board_6y":
            DialogExit();
			npchar.DeckDialogNode = "mtraxx_board_6x";
		break;
		
		case "mtraxx_board_7":
            dialog.text = "크크! 그게 누구 잘못인데, 왕자? 네 잘못이냐?";
			link.l1 = "미안해, 두목. 우리 둘 다 꽤 잘했어... 너도 사격 정말 잘했지. 조준도 끝내줬고...";
			link.l1.go = "mtraxx_board_8";
		break;
		
		case "mtraxx_board_8":
            dialog.text = "뭐, 됐다. 잘못은 우리 둘 다에게 있지. 그래도 빈손은 아니야 - 바르바존 놈들한테 줄 건 다 줬으니, 그 자체로 승리지...\n";
			link.l1 = "금에 대해서는 미안하다... 이제 뭐 할 거지, Marcus? 라 베가로 가는 거냐?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_90x":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_90";
		break;
		
		case "mtraxx_90":
			pchar.quest.Mtraxx_CartahenaLate.over = "yes";
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "왕자, 제정신이냐? 내가 배 한 척만 끌고 오라고 했잖아! 당장 남는 배 치우고 최대한 빨리 돌아와! 지금 당장!";
				link.l1 = "알았어, 알았다고!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (RealShips[sti(pchar.Ship.Type)].Type.Merchant) // торговые
			{
				dialog.text = "왕자, 내 두 번째 커틀라스가 되기로 결심한 건가? 왜 상선을 끌고 왔지? 난 너를 믿었는데! 가서 제대로 된 군함을 가져와! 당장!";
				link.l1 = "알았어, 알았어!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) > 3)
			{
				dialog.text = "나리, 네가 날 놀라게 했군. 내가 전함을 가져오라고 했잖아! 이런 고물 배로 뭘 도와준다는 거지? 3등급이나 2등급 배로 다시 와. 그 이상도, 그 이하도 안 돼! 당장! 난 누구도 기다려주지 않는다.";
				link.l1 = "알았어, 알았다고!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "왕자 나리, Sovereign of the Seas를 여기로 끌고 오라는 게 아니었잖아? 전함을 가져오라 했지, 이런 빌어먹을 전열함을 끌고 오라는 말은 안 했다고! 3등급이나 2등급 함선을 타고 다시 와! 당장! 누구도 기다려줄 생각 없으니까.";
				link.l1 = "알겠어, 알겠다고!";
				link.l1.go = "mtraxx_90x";
				break;
			}
            dialog.text = "좋은 타이밍이군, 해적놈! 멀쩡히 살아 돌아온 걸 보니 반갑다! 항해할 준비 됐냐?";
			link.l1 = "알겠어, 두목. 언제든 준비됐지.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon")) link.l1.go = "mtraxx_91";
			else link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_91":
            dialog.text = "그런데, 네가 푸에르토리코로 보낸 바르바존 함대에 대해 알고 싶어?";
			link.l1 = "완전히 잊고 있었군. 당연히 알고 싶지. 놈들이 죽었나?";
			link.l1.go = "mtraxx_92";
		break;
		
		case "mtraxx_92":
            dialog.text = "그래, 당연히 그랬지! 기함, 조커 짐의 프리깃 '올빼미'는 물가까지 타버렸어. 조커 짐 그 놈은 흔적도 없이 사라졌고. 트램프랑 굴도 박살이 났지만 간신히 도망쳤지. 트램프는 라 로차의 대포 보호 아래 토르투가로, 굴은 이슬라 테소로로 갔어. 파스칼레가 그러는데, 굴은 샤프타운 근처 암초에 배를 좌초시켜서 겨우 빼냈다더라. 이제 알렉서스 영감이 골치 좀 썩겠지, 허허. 뭐, 결국 스페인 놈들은 좀 실망이야. 다 죽일 줄 알았거든.";
			link.l1 = "헤. 뭐 어때, 그래도 바르바존 놈 신발에 오줌은 제대로 갈겼지. 메시지는 확실히 전해줬다.";
			link.l1.go = "mtraxx_93";
		break;
		
		case "mtraxx_93":
            dialog.text = "맞아. 이제 거래 얘기나 하자.";
			link.l1 = "듣고 있지.";
			link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_94":
            dialog.text = "내 정보원, 즉 내 좋은 친구 베르나르 벵상이 보고하기를, 스페인 놈들이 카르타헤나에 엄청난 금괴 더미를 쌓아두었다더군. 더 정확히 말하면 그 요새 밑에 말이지. 원래라면 스페인 황금 함대의 몫이었겠지만, 이번엔 우리가 차지할 차례다. 우리는 스페인 본토로 가서 카르타헤나를 습격할 거다.";
			link.l1 = "아르! 내가 잘못 들은 건 아니겠지? 피투성이 요새까지 있는 식민지 전체를 약탈하러 간다고?";
			link.l1.go = "mtraxx_95";
			// belamour legendary edition отказ от великого похода
			link.l2 = "나는 너랑 카르타헤나에 가지 않아, 마르쿠스. 도시 하나를 통째로 불태우는 건 내 방식이 아니야.";
			link.l2.go = "mtraxx_94a";
		break;
		
		case "mtraxx_95":
            dialog.text = "잘 들었군. 우리가 바로 그걸 할 거다. 내 전함이 요새를 상대할 거고, 물론 네 도움이 필요하지. 대담한 제프리는 네덜란드 놈들에게서 훔친 새 이스트 인디아맨으로 육상군을 실어 나를 거다. 펠리는 드디어 너덜너덜한 브리건틴을 처분하고, 내 돈 좀 보태서 그럴싸한 코르벳을 손에 넣었지. 폴 샹과 너는 순찰 함대를 처리할 책임이 있다; 너희 선원들도 공격에 참가할 거고, 그리고 너, 샤를, 그렇게 싸움 잘하고 선장 노릇도 제대로 하는 네가 내 요새 파괴에 힘을 보태는 거다. 장 피카르는 나타나지 않았어, 이상하지, 그 자의 코르벳이 포트 로얄에서 목격됐는데 말이지. 뭐, 스페인 금에 관심 없으면 그놈 손해지, 지옥이나 가라지. 대신 내 친구 베르나르 벵상이 이번 습격에 합류한다. 거기에 레프리콘과 그 부카니어들도 우리 군을 도울 거다. 우리는 요새에서 금을, 도시에서 몸값을 챙길 거다. 절대 못 잊을 거다, 하하! \n이제 가서 쉬어라. 그리고 오늘 저녁엔 나랑 다른 선장들하고 선술집에서 합류해라! 우리의 대의를 위해 한잔해야지! 내가 주점 주인한테 동네 주정뱅이들 다 쫓아내라고 할 테니, 우리 여섯 명이랑 매력적인 아가씨들만 있을 거다. 오늘 밤은 동료들과 술 마시는 거고, 내일 아침엔 네가 편대를 이끌고, 네가 진로를 정한다. 그리고 최대한 빨리 우리를 카르타헤나로 데려가도록 해라. 다 알아들었지?";
			link.l1 = "알겠어, 우두머리!";
			link.l1.go = "mtraxx_96";
		break;
		
		case "mtraxx_96":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			chrDisableReloadToLocation = true;
			CloseQuestHeader("Roger_8");
			pchar.questTemp.Mtraxx = "cartahena";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LaVega_townhall", "goto", "goto3");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaReloadInTavern", 10.0);
			pchar.worldmapencountersoff = "1"; // уберем враждебные энкаунтеры
		break;
		// belamour legendary edition -->
		case "mtraxx_94a":
            dialog.text = "너... 너... 미친 왕자 놈! 나를 엿먹이려는 거냐?! 됐다, 엿이나 먹어라! 네놈에겐 형제단에 들어올 기회도 있었고, 이 쓸모없는 오합지졸 무리에서 벗어날 기회도 있었지. 그런데도 겁쟁이처럼 그 기회를 놓쳐버렸군. 징징대지 말고 꺼져라! 약골 놈! 다시 한 번 내 눈에 띄면 개들을 풀어버릴 거다!\n";
			link.l1 = "...";
			link.l1.go = "mtraxx_95a";
		break;
		
		case "mtraxx_95a":
            DialogExit();
			QuestSetCurrentNode("Terrax", "First time");
			CloseQuestHeader("Roger_8");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Corrida");
			DeleteAttribute(pchar, "questTemp.Mtraxx.InTavern");
			LocatorReloadEnterDisable("LaVega_town", "reload6", true); // закрыть на месяц
			SetFunctionTimerCondition("Mtraxx_CartahenaLateOpen", 0, 0, 30, false);
			Mtraxx_TerraxReset(8);
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <-- legendary edition
		case "mtraxx_97":
            dialog.text = "드디어 왔군, 나리! 이봐, 놈들아 - 우리가 선물을 준비했는데, 저 양반은 어디서 헤매고 있잖아! 앉아, 이제 시작한다!\n자, 용감한 코르세어들! 카르타헤나의 금이 우리를 기다리고 있다, 하하! 우리가 반드시 차지할 거다, 천둥에 맹세하지! 하지만 열심히 일한 놈들은 제대로 쉬어야 한다! 그래서 오늘 밤은 이 멋진 술집에서 실컷 즐긴다! 럼을 부어라, 많이 부을수록 좋다! 잔을 가득 채워라! 보물의 바람을 위하여, 행운의 바람을 위하여! 마지막 한 방울까지 마신다!\n너희를 위해 우리 선술집 지하실에서 꺼낸 최고의 술과, 섬에서 가장 아름다운 아가씨들을 준비했다, 하하하!\n그리고 너를 위해, 찰스, 우리 모두가 준비한 멋진 모자다. 써 봐, 괜히 딴지 걸지 말고!\n코르세어들아, 우리 노래를 불러라! 제일 좋아하는 그 곡이다!..";
			link.l1 = "";
			link.l1.go = "mtraxx_98";
		break;
		
		case "mtraxx_98":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			LAi_SetSitType(npchar);
			GiveItem2Character(PChar, "hat8");
			EquipCharacterByItem(PChar, "hat8");
			DoQuestCheckDelay("Mtraxx_CartahenaTavernSong", 1.0);
		break;
		
		case "mtraxx_99":
            dialog.text = "이제 우리가 누구인지 보여줄 때다, 해적들아. 레프리콘! 네 놈 부하들 데리고 성문 장악해라. 놈들이 요새로 증원군 보내지 못하게 막아야 한다! 우리가 요새 병사들 뚫고 들어갈 때 뒤에서 세게 쳐라!\n";
			link.l1 = "";
			link.l1.go = "mtraxx_100";
		break;
		
		case "mtraxx_100":
            dialog.text = "프린스, 폴! 군함 세 척이 있는 군대 함대를 봤지, 저놈들 처리해. 요새에는 가까이 가지 말고, 놈들 배에 올라타지도 마라. 전리품 챙길 시간도 여유도 없어. 다 알아들었지?! 프린스, 특히 너한테 하는 말이다, 네 영웅놀이 버릇 다 알고 있으니까, 나중에 실컷 해라!\n요새에 너무 가까이 가지 말고, 저 배들만 처리해서 돌아와! 우린 여기서 기다릴 거다. 다 알아들었나? 좋아, 하하하하! 돌격!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaSquadronAttack");
		break;
		
		case "mtraxx_101":
            dialog.text = "그래, 스페인 함대는 완전히 끝장났지. 이제 '레드 드래곤'이 나설 차례다. 우리가 카르타헤나 요새를 잿더미로 만들어버릴 거다. 같이 할 거냐?";
			link.l1 = "그래!";
			link.l1.go = "mtraxx_102";
		break;
		
		case "mtraxx_102":
            dialog.text = "'레드 드래곤'은 아주 튼튼한 배에다 화력도 강하다, 네 배로는 상대도 안 돼. 그러니까 조심해라, 영웅인 척하지 말고 내 대포 근처엔 얼씬도 하지 마!";
			link.l1 = "...";
			link.l1.go = "mtraxx_103";
		break;
		
		case "mtraxx_103":
            DialogExit();
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
	
			Weather.Wind.Angle = 0.0;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Group_FindOrCreateGroup("Terrax_SeaGroup2");
			Group_DelCharacter("Terrax_SeaGroup", "Jeffry");
			Group_DelCharacter("Terrax_SeaGroup", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Jeffry");
			Group_AddCharacter("Terrax_SeaGroup2", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Pelly");
			Group_SetGroupCommander("Terrax_SeaGroup2", "Jeffry");
			Group_SetTaskNone("Terrax_SeaGroup2");
			Group_LockTask("Terrax_SeaGroup2");
			sld = CharacterFromID("Cartahena Fort Commander");
			LAi_SetImmortal(sld, false);
			Ship_SetTaskAttack(SECONDARY_TASK, sti(npchar.index), sti(sld.index));
			AddQuestRecord("Roger_9", "5");
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx.Cartahena.Fort = "true";
			SetFunctionExitFromLocationCondition("Mtrxtofort", pchar.location, false);
		break;
		
		case "mtraxx_104":
            dialog.text = RandSwear()+"지옥 같은 전투였군! 이게 바로 우리가 해낸 거다, 용감한 해적 놈들아! 카르타헤나는 이제 우리 거다! 저항은 끝났어! 대담하게 가자, 레프리콘! 나랑 같이 요새로 가자 – 버니가 이미 금을 찾았을 거다. 프린스, 커틀러스를 데리고 가서 총독한테 몸값 25만 페소를 내놓으라고 협상해! 돈은 있으니 끝까지 밀어붙여. 넌 할 수 있다는 거 내가 안다.";
			link.l1 = "헤! 기꺼이 하겠습니다, 두목!";
			link.l1.go = "mtraxx_105";
		break;
		
		case "mtraxx_105":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "Cartahena_fort", "goto", "goto10", "", 5.0);
			sld = CharacterFromID("Jeffry");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto11", "", 5.0);
			sld = CharacterFromID("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto12", "", 5.0);
			sld = CharacterFromID("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			AddQuestRecord("Roger_9", "6");
			// запрещаем драки в городе, резиденции, форте
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_fort")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_town")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_townhall")], true);
			LAi_LocationDisableOfficersGen("Cartahena_townhall", true);
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1 = "locator";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.location = "Cartahena_town";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator = "reload3_back";
			pchar.quest.mtraxx_cartahena_townhall.function = "Mtraxx_CartahenaToResidence";
		break;
		
		case "mtraxx_106":
            dialog.text = "어떻게 지내나, 프린스?";
			link.l1 = "모든 게 완벽하지. 내가 카르타헤나에서 제일 부자인 놈들한테 35만 페소를 뜯어냈지.";
			link.l1.go = "mtraxx_107";
		break;
		
		case "mtraxx_107":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "호호, 내 아들답군! 그런데 돈은 어디 있지?";
				link.l1 = RandSwear()+"곧 가져오겠다!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "호호, 그게 바로 내 놈이지! 너랑 커틀라스는 속도랑 수완 덕에 각각 5만씩 보너스로 챙겨라. 나머지는 나중에 우리 모두가 나눌 거다.";
				link.l1 = "자, 받아라!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_107x":
           DialogExit();
		   npchar.dialog.currentnode = "mtraxx_108";
		break;
		
		case "mtraxx_108":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "그래? 그만 뻐기고 돈이나 가져와!";
				link.l1 = "가는 중이야!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "좋아! 너랑 커틀라스는 속도랑 수완 덕분에 보너스로 각각 5만씩 챙겨라. 나머지는 나중에 우리 모두가 나눌 거다.";
				link.l1 = "자, 받아라!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_109":
			AddMoneyToCharacter(pchar, -300000);
            dialog.text = "우리 금에 대해 걱정하고 있겠지? 이미 찾았어 - 5,000단위나 되고, 지금 우리 배로 옮기고 있는 중이다. 분배는 이미 끝났고, 놈들도 다 동의했다. Cutlass랑 너도 딴소리 안 할 거라 믿는다.";
			link.l1 = "내 몫이 뭐지?";
			link.l1.go = "mtraxx_110";
		break;
		
		case "mtraxx_110":
            dialog.text = "작전 전체를 내가 계획했고, '레드 드래곤'이 요새를 상대하는 가장 힘든 임무를 맡았으니, 나와 내 부하들이 전리품의 절반을 가져간다. 나머지 절반은 다른 네 척의 선장들이 각자 선원 수에 따라 나눠 가질 거다. 너는 "+GetCrewQuantity(pchar)+" 네놈이 쓸 수 있는 놈들은 이 정도고, 네 몫은 "+sti(pchar.questTemp.Mtraxx.Cartahena.Gold)+" 금화 단위와\n "+sti(pchar.questTemp.Mtraxx.Cartahena.Money)+" 페소.";
			link.l1 = "그래, 다들 괜찮다니 나도 상관없어!";
			link.l1.go = "mtraxx_111";
		break;
		
		case "mtraxx_111":
            dialog.text = "훌륭하다. 이번 항해의 성공을 축하한다, 해적 놈들아! 여기서 더 할 일은 없으니, 이제 집으로 돌아갈 시간이다. 우리 모두, 나까지 포함해서 한 달 휴가를 받는다. 하지만 너는 아니야, 프린스. 너한테는 다른 임무가 있다. 있잖아, 토르투가의 창관 마담 자네트가 너에 대해 불평을 했거든. 찰리 프린스가 자기 업소에 별로 관심도, 애정도 안 준다고 말이야. 그래서 명령한다, 토르투가로 가서 자네트네에 들러서 네 보너스를 거기서 써라. 그럴 자격은 충분히 있다. 마담과 그녀의 여자들을 기쁘게 해 줘라. 토르투가에서 실컷 쉬기 전엔 내 앞에 나타나지 마라, 하하하!";
			link.l1 = "알겠어요, 보스. 이렇게 기분 좋은 임무는 처음 받아봐요. 곧 끝내겠습니다!";
			link.l1.go = "mtraxx_112";
		break;
		
		case "mtraxx_112":
            dialog.text = "잘 가라, 이놈들아! 배로 돌아가서 당장 출항해! 라 베가에서 다들 보자!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaFinal");
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "mtraxx_113":
            dialog.text = "뭐라고?! 장은 이제 영국 놈들의 개가 됐고, 볼드랑 커틀러스는 사라졌고, 레프리콘이랑 그 졸개들도 어디 있는지 모르겠다고! 그리고 이제 너까지?!";
			link.l1 = "마커스, 내 결정을 내렸어. 난 꽤 돈을 벌었고, 너도 나 덕분에 한몫 챙겼지. 하지만 이제 끝이야. 난 떠난다.";
			link.l1.go = "mtraxx_114";
		break;
		
		case "mtraxx_114":
            dialog.text = "너도 피카르드처럼 혼자서 더 잘 벌 수 있다고 생각하나? 그래? 나 없이도 해낼 수 있을 것 같아? 하하하! 당장 꺼져, 프린스. 나는 너 붙잡지 않는다. 곧, 아주 곧 네가 얼마나 잘못 생각했는지 알게 될 거다. 그때 가서 내 앞에 무릎 꿇고 빌게 되겠지. 그런데 말이지? 나는 안 받아준다! 하하! 내 눈앞에서 꺼져!";
			link.l1 = "...";
			link.l1.go = "mtraxx_115";
		break;
		
		case "mtraxx_115":
            DialogExit();
		    npchar.quest.mtraxx_complete = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "호호! 제대로 찾아왔군! 얼른 말해봐!";
			link.l1 = "해적을 두려워하지 않는 놈이 하나 있지. 우리를 우습게 본다 이거야. 놈한테 존경이 뭔지 똑똑히 가르쳐 줘야 해. 하지만, 죽이지는 마라.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "허! 이게 누구야, 늙은이 찰스 아니냐! 또 무슨 일에 휘말린 거지? 자, 자세히 말해 봐. 이번엔 누가 표적이고, 그놈한테 뭘 가르쳐줘야 하지?";
			link.l1 = "유럽에서 온 손님, 프랑스 재무부의 감찰관이자 남작인 노엘 포르게가 있지. 이 자가 여기서 프랑스 무역 회사를 세우려 하는데, 내 오랜 친구와 나는 반대하고 있어. 우리는 남작에게 네덜란드 놈들, 영국 놈들, 그리고 특히 르바쇠르가 패한 뒤로 더 극성이 된 해적들 때문에 여기서 무역하는 건 아주 위험하다고 설득하려 했지만, 듣질 않더군. 저 자가 직접 뼈저리게 느끼도록 겁을 줘야 해.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_x":
			dialog.text = "호호! 제대로 찾아왔군! 어서 말해봐!";
			link.l1 = "해적을 두려워하지 않는 놈이 하나 있다. 우리를 우습게 본다. 제대로 예의를 가르쳐 줄 필요가 있지. 하지만, 죽이지는 마라.";
			link.l1.go = "patria_x1";
		break;
		
		case "patria_x1":
			dialog.text = "흥! 갑자기 왜 해적을 고용하겠다고 나선 거지? 뭐, 돈만 제대로 주면 상관없어. 이제 본론으로 들어가자, 이번에는 누가 표적이고 뭘 가르쳐줘야 하지\n";
			link.l1 = "유럽에서 온 손님이자 프랑스 재무부의 감찰관, 노엘 포르게 바론이다. 이 자가 여기 프랑스 무역 회사를 세우려 하는데, 내 오랜 친구와 나는 반대하고 있지. 우리는 바론에게 네덜란드 놈들, 영국 놈들, 그리고 특히 르바쇠르가 패한 뒤로 해적들 때문에 여기서 무역하는 건 아주 위험하다고 설득하려 했지만, 듣질 않더군. 놈이 직접 뼈저리게 느끼도록 겁을 줘야 해.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "그래, 그래... 진짜 남작이잖아! 그 자식 배를 쳐들어갈까?";
			link.l1 = "계획은 이렇다. 그의 배가 곧 포르토프랭스에서 캡스터빌로 출항할 거다.\n생키츠 근처에서 그 바론을 가로채서 인질로 잡아야 해. 배를 침몰시키거나 선원들을 죽이지 않는 게 좋겠지. 프랑스 놈들은 어쨌든 우리 친구니까.\n그 정도는 할 수 있겠지?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "글쎄, 아무것도 장담 못 해. 그래도 해볼게. 무슨 배지?";
			link.l1 = "'Favory'라는 브리그야.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "브리그 따위가 내 '레드 드래곤' 상대가 되겠어? 우리가 쉽게 처리하지. 만약 항복하면, 모두 살려주지.";
			link.l1 = "완벽하다. 공포를 심어주고 항복할 기회를 줘라. 그 다음엔 남작을 쥐들이 들끓는 선창에 처박아 둬. 최대한 더러운 곳을 찾아보되, 하루 이상 두진 마라. 병들어 죽을 수도 있으니까. 그 후엔 선실로 옮겨서, 외진 곳에 가둬라. 네 부하 몇 놈을 프랑스 상인으로 위장시켜서 포로처럼 행동하게 해. 사흘 내내, 해적들이 얼마나 무자비하게 쫓고, 약탈하고, 몸값을 요구하고, 고문하는지... 필요한 세부사항까지 모조리 들려주게 해라.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "하하하! 이렇게 웃긴 일은 정말 오랜만이군! 좋아, 그런 배우들을 찾아주지, 이놈. 걱정 마라, 그놈들 얘기 듣고 나면 네 바론 놈이 바지에 똥을 쌀 거다! 칼자국이랑 달군 총봉 자국까지 다 보여줄 테니까...";
			link.l1 = "완벽해! 그럼 그 자식에게 드 푸앵시에 몸값을 요구하는 편지를 쓰게 만들어. 저런 거물한테 삼백오십만이면 그리 큰돈도 아니지.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "좋아. 이제 뭐 할 거지?";
			link.l1 = "그리고 나서 네가 그 남작을 터크스로 데려가. 거기서 몸값을 받고, 남작은 나한테 넘겨. 그리고 그 자식한테 프랑스 놈들 전부가 토르투가와 르바쇠르 일로 대가를 치르게 될 거라고 전해. 한 번이 아니라 여러 번 말이야.";
			if (CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax")) link.l1.go = "patria_x7";
			else link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "하하하! 이거 제대로 한 건 했구나! 우리야, 알다시피, 레바쇠르한테 어떻게 했는지 알잖아, 그런데 지금은... 하하하!.. 좋아, 이놈. 그렇게 해주지! 그럼 네 말은 배가 곧 도착한다는 거지?";
			link.l1 = "곧이다. 경계 태세를 유지해야 해.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_x7":
			dialog.text = "하하하! 이거 제대로 한 판 벌였구나! 이런 웃긴 쇼값을 얼마쯤 받아야 할까? 좋아, 십만이면 끝내주지. 돈 내놔.";
			if (sti(pchar.money) >= 100000) 
			{
				link.l1 = "가져가.";
				link.l1.go = "patria_x8";
			}
			else
			{
				link.l1 = "좋아, 내가 가져올게.";
				link.l1.go = "patria_xwait";
			}
		break;
		
		case "patria_xwait":
			DialogExit();
			pchar.questTemp.Patria.Condotier.NeedMoney = "true";
		break;
		
		case "patria_x8":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "완벽하군! 배가 곧 도착한다고 했지?";
			link.l1 = "곧이다. 경계해야 해.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "걱정하지 마, 실망시키지 않을 거다. 내가 직접 처리하지. 바론이 잡혔다는 소문이 들리면 나한테 와라.";
			link.l1 = "좋아. 고맙다, Marcus.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "71");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
			else LocatorReloadEnterDisable("Lavega_town", "reload6", true);
		break;
		
		case "patria_10":
			dialog.text = "물론이지, 이 자식아. 약속대로다. 무자비한 해적들이 죄 없는 프랑스 상인들을 도륙하는 무시무시한 이야기, 채찍 소리, 신음과 비명. 숯불이 피워진 화로와 그을린 수갑. 그래야 제대로지.";
			link.l1 = "야, 야! 진정해! 난 저 놈이 살아 있어야 해";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "걱정 마, 저놈은 살아남을 거야. 손이 덜덜 떨리면서 이 편지를 썼더군. 여기 있다.";
			link.l1 = "거기 뭐라고 적혀 있지? 저 자식이 푸앵시한테 자기 좀 꺼내 달라고 빌고 있나?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "맞아, 이놈아! 저 자식이 빌고 있잖아, 하!";
			link.l1 = "이 편지는 버려라, 아니면 차라리 태워버려. 일주일 후에 터크스에서 만나자. 우리가 몸값을 모으는 데 시간이 필요한 것처럼 보여야 해.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "알겠어. 일주일 뒤에 터크스 북쪽 만에서 봐. 돈 챙기는 거 잊지 마라. 그럴싸하게 보여야 하니까. 다 끝나면 나한테 와, 얘기 좀 하자.";
			link.l1 = "물론이지, 나중에 보자, Marcus!";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "이봐, 개구리 처먹는 놈! 멈춰!";
			link.l1 = "나는 안 움직여.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "여기 네 바론이 있다. 좀 헤졌지, 허, 그래도 멀쩡하게 한 덩어리로 데려왔어. 아직 알아볼 수 있겠냐? 하하하!";
			link.l1 = "그래... 뭐, 그렇지.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "완벽해. 이제 돈 내놔, 아니면 저 자식 끝장난다! 그리고 꼼수 부릴 생각 마라, 우린 이미 너를 조준하고 있으니까!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "여기, 가져가.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "젠장! 그걸 배에 두고 내렸잖아...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "하하하! 영리한 녀석이구나, 프랑스 놈. 네 '각하'나 가져가라. 그리고 푸앵시한테 돈 준비하라고 전해라. 레바쇠르와 토르투가에서 저지른 짓값을 치러야 할 테니까. 그리고 네 상인들도 우리한테 물건과 배로 값을 치르게 될 거다. 하하하! 군도에 남은 남작들도 더 데려오라고 잊지 마라, 그놈들이 우리한테 이익을 잔뜩 가져다주거든! 하하하!\n";
			link.l1 = "제발, 내 배로 가시오, 남작.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "그리고 우리를 쫓을 생각도 하지 마라, 선장. 내가 누군지 알잖아. 나는 더 많은 개구리 처먹는 놈들을 포로로 잡고 있어. 내가 제때 집에 안 돌아가면 전부 처형당할 거다. 알겠어?";
			link.l1 = "때가 오면, 우리가 너희 저주받은 불경한 놈들 처리해주겠다!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "하하하하! 당연히 그렇게 하지!";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax"))
			{
				LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
				Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			}
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "장난하냐?! 이게 무슨 수작이야?!";
			link.l1 = "잠깐만, 내가 가져올게...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "아르, 마르쿠스, 네 멍청이가 또 무슨 짓을 한 거야!";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) link.l1.go = "patria_25";
			else link.l1.go = "patria_x25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, 뭐 하고 있었어? 돈은 어디 있지? 내 부하들한테 이게 가짜라고 말 안 했거든... 그래서 이 멍청이가 네가 우리를 속이려 한다고 생각했지...";
			link.l1 = "이게 무슨 재앙이냐! 남작이 죽었어... 이제 드 푸앵시는 어떻게 할까?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_x25":
			dialog.text = "Charles, 뭐 하고 있었어? 돈은 어디 있지? 내 부하들한테 이게 가짜라고 말 안 했거든... 그래서 이 멍청이가 네가 속이려고 한다고 생각했지...";
			link.l1 = "이런 재앙이 있나! 남작이 죽었어... 이제 드 푸앵시는 어쩔 셈이지?";
			link.l1.go = "patria_x26";
		break;
		
		case "patria_x26":
			dialog.text = "그래, 이봐 꼬마, 그건 네 잘못이야, 그건 알고 있겠지. 어쩌면 그게 더 나은 걸지도 몰라, 죽은 놈은 더 이상 문제를 일으키지 않으니까.";
			link.l1 = "내가 얼마나 바보인지! 전부 망쳐버렸어. 좋아, 푸앵시에 가겠어... 이렇게 멍청하게 굴어서 미안하다, 마르쿠스, 또 보자.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_26":
			dialog.text = "그래, 이놈아, 네 잘못이야. 그건 네가 알아둬야 해. 어쩌면 이게 차라리 잘된 일일지도 모르지.";
			link.l1 = "내가 얼마나 바보였는지! 전부 망쳐버렸군. 좋아, 푸앵시에 가겠다... 이렇게 멍청하게 굴어서 미안하다, 마르쿠스, 또 보자.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "좀 쉬어야겠군, 감각이 무뎌졌어. 언젠가 나한테 와라, 럼주랑 좋은 계집애들 좀 구해주지.";
			link.l1 = "고맙다, 시간 나면 찾아가마.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "천만에, 이 녀석아. 나한텐 올해 들어 가장 재밌는 시간이었지! 나랑 내 놈들이 얼마나 웃었는지 몰라! 그래서 이걸로 너한테 감사 인사라도 해야겠다. 여기 네 돈이다.";
			link.l1 = "네가 한 짓에 대한 보상으로 일부는 챙겨둬야지.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_x29":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "돈이나 챙겨, '계략가' 놈. 하하! 재밌었군.";
			link.l1 = "도와줘서 고맙다, Marcus. 행운을 빌지!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "잊어버려. 우리 우정을 위해 한 일이야. 코스트의 형제단이 너한테 진 빚이 훨씬 더 많지만, 넌 금화 한 닢도 요구하지 않았지.";
			link.l1 = "그래도 네 수고비와 보상으로 최소한 오만은 가져가라. 고맙다, Marcus!";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "천만에. 시간 나면 언제든 들르라고, Charles!";
			link.l1 = "기꺼이!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "일주일이나 늦었군! 내 부하들한테 이게 가짜라고 말 안 했거든... 놈들은 더는 못 기다리겠다며 네 바론을 끝장내기로 했지!";
			link.l1 = "내가 얼마나 바보냐! 다 망쳐버렸잖아! Poincy한테 뭐라고 말하지?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_x33":
			dialog.text = "일주일이나 늦었군! 내가 내 부하들한테 이게 가짜라고 말하지 않았지... 놈들은 더는 못 기다리겠다며 네 바론을 끝장내기로 했어!";
			link.l1 = "내가 얼마나 바보인 거야! 다 망쳐버렸잖아! Poincy한테 뭐라고 말하지?";
			link.l1.go = "patria_x34";
		break;
		
		case "patria_34":
			dialog.text = "그래, 이 자식아, 이건 네 잘못이야. 그거 이해하고 있겠지. 어쩌면 그게 너한테 더 나을 수도 있겠군.";
			link.l1 = "좋아, 푸앵시로 가지... 내가 바보였던 걸 용서해라, Marcus, 또 보자...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_x34":
			dialog.text = "이 꼴이 된 건 네 잘못이야, 네가 자초한 일이니까.";
			link.l1 = "나중에 보자고, 뭐...";
			link.l1.go = "patria_36";
		break;
		
		case "patria_35":
			dialog.text = "쉬어야겠군, 감각이 무뎌지고 있어. 언젠가 나한테 와라, 럼주랑 멋진 계집애들 좀 구해줄 테니.";
			link.l1 = "고맙다, 시간 되면 찾아가마.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ_1":
			DelLandQuestMark(npchar);
			
			if (pchar.questTemp.Mtraxx == "full_complete")
			{
				dialog.text = "오랜만이군, 왕자.";
				link.l1 = "이 이름이 나한테 불운 말고 다른 걸 가져다준 적이 있는지 모르겠군, Marcus.";
				link.l1.go = "PZ_Prince1";
			}
			else
			{
				dialog.text = "드 모레! 여기 웬 일이야?";
				link.l1 = "아, Marcus. 너한테 물어보고 싶은 게 있었어.";
				link.l1.go = "PZ_DeMaure1";
			}
		break;
		
		case "PZ_Prince1":
			dialog.text = "보아하니 전혀 반대군. 뭐 때문에 여기 온 거지?";
			link.l1 = "토르투가에 새로 생긴 사창가 소식 들었어?";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_DeMaure1":
			dialog.text = "그럼 어서 물어봐. 내가 형식 따위 싫어하는 거 알잖아, 돌려 말하지 말고 바로 본론으로 들어가.";
			link.l1 = "토르투가에 새로 생긴 사창가 소식 들었냐?";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "술 취했냐? 그게 무슨 질문이야? 진짜 그딴 얘기하려고 온 거면 내 시간 낭비하지 마.";
			link.l1 = "아직 못 들었나 보군? 거기 최근에 새로운 사창가가 열렸어—아주 비싼 곳이지. 거기엔 가장 예쁘고, 건강하고, 잘 차려입은 여자들만 일한단 말이야.";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "아, 그거! 당연히 들었지 – 안 들어본 놈이 어디 있겠어?";
			link.l1 = "글쎄, 나도 며칠 전에야 알게 됐지.";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "하하하하, 이 악당아, 젠장할 놈! 그래도, 왜 나랑 이 얘길 하는 거지? 먼저 호크스한테 가보지 그래? 흐흐. 아니면... 거기서 이미 좀 재미 좀 봤나?";
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				link.l1 = "있지. 그런데 저놈들은 두블룬만 받아.";
				link.l1.go = "PZ_Fucked1";
			}
			else
			{
				link.l1 = "나는 그곳을 방문했지만, 의식에는 참여하지 않았어. 하지만...";
				link.l1.go = "PZ_NoFucked1";
			}
		break;
		
		case "PZ_Fucked1":
			dialog.text = "그래서 자랑하러 온 거냐! 하, 이 망할 놈.";
			link.l1 = "사실 아니야. 정말로 너한테 물어보고 싶은 게 있었어, Marcus.";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_NoFucked1":
			dialog.text = "안 했다고?! 넌 바보구나, 드 모르. 내가 너라면...";
			link.l1 = "너라면 제대로 난장판을 벌였겠지, 알아. 하지만 내가 너랑 얘기하고 싶은 건 그게 아니야.";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			dialog.text = "뭐야? 어서 말해, 괜히 애태우지 말고.";
			link.l1 = "저 그곳의 주인을 찾고 있어. 그녀가 너를 만나고 싶어 하고, 자기 장사에 투자 기회를 제안하고 싶다고 들었지. 절대 헷갈릴 리 없어 – 그녀는 중국인이거든.";
			link.l1.go = "PZ_6";
		break;
		
		case "PZ_6":
			dialog.text = "호호. 아니, 요즘 중국 여자를 만난 적은 없어. 하지만 그녀를 만나서 그 사업에 투자하는 것도 나쁘지 않지. 어차피 네가 그냥 레바쇠르의 구역에 들어갈 수 있는 것도 아니고, 네 왕의 신하라면 그 자식은 내 '드래곤'을 보자마자 해안 경비선으로 바로 포격할 거야.";
			link.l1 = "먼저 포르토프랭스를 고려하는 것 같군...";
			link.l1.go = "PZ_7";
		break;
		
		case "PZ_7":
			dialog.text = "그렇게 생각하나? 그건 착각이지. 드 무삭이 나보다 돈이 많다고 해도, 난 그럴 리 없다고 보지만, 아무리 금이 많이 들어와도 시 예산을 사창가에 쓸 수는 없어.";
			link.l1 = "좋은 지적이군. 저 여자는 자기 야망을 제대로 생각해본 적이 없는 게 분명해.";
			link.l1.go = "PZ_8";
		break;
		
		case "PZ_8":
			dialog.text = "있지, 난 항상 다른 사창가들이 어떻게 버티는지 궁금했어. 여자가 머리 쓴다고 되는 것도 아니고, 더더욱 다스릴 능력은 없지 – 내 말 명심해.";
			link.l1 = "그건 네가 잘못 알고 있는 거야. 시간 내줘서 고맙다, Marcus! 내가 먼저 그녀를 만나면 네가 보고 싶어 한다고 전해줄게.";
			link.l1.go = "Exit";
			
			AddQuestRecord("PZ", "32");
			
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