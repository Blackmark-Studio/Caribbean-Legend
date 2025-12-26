// Жак Барбазон в Ле Франсуа
int iBarbazonTotalTemp;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

//--> -----------------------------------------------блок angry-------------------------------------------------
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
//<-- -------------------------------------------блок angry------------------------------------------------------

	switch(Dialog.CurrentNode)
	{
	// ----------------------------------- Диалог первый - первая встреча---------------------------------------
		case "First time":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("미쳤냐? 도살놀이라도 하고 싶었던 거야? 모든 해적들이 너한테 화났어, 꼬마야, 여기서 당장 꺼지는 게 좋을 거다...","미친 거 아니냐, 이놈. 몸 좀 풀고 싶었나? 기분 나쁘게 듣지 마라, 네가 여기 있을 자리는 아니야. 꺼져!");
				link.l1 = RandPhraseSimple("이봐, 이 상황을 바로잡고 싶어...","이 문제 좀 해결해 줘...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", 나는" + GetSexPhrase("", "요") + " 바다에서의 내 안전에 대해 이야기하고 싶어. 해안 형제단 녀석들이 내 겸손한 존재에 지나치게 관심을 보이고 있어. 그들을 좀 억눌러 줄 수 있겠어?";
			link.l0.go = "pirate_threat";

			dialog.text = NPCStringReactionRepeat("나한테 할 말 있냐? 없어? 그럼 꺼져!",
						"내 말 알아들었지, 그만 귀찮게 해.","내가 분명히 말했는데도, 자꾸 성가시게 굴잖아!",
						"그래, 이 무례함에 슬슬 질린다.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("나 이제 간다.",
						"그래, "+npchar.name+"...",
						"미안하다, "+npchar.name+"...",
						"아야...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
		//----------------------------------Сага - искушение Барбазона---------------------------------------
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "begin")
			{
				link.l1 = "너랑 얘기 좀 해야겠어, 자크... 단둘이.";
				link.l1.go = "Temptation";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "give_silk" && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 60)
			{
				link.l1 = "나는 생마르탱에서 왔어, 자크...";
				link.l1.go = "Temptation_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				link.l1 = "언제까지 짖기만 할 거냐, 자크? 남자답게 말 좀 해봐라. 내가 올 줄은 몰랐지?";
				link.l1.go = "terrax";
			}
			
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "네 죄수 때문에 왔다.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}
             	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "안녕, Jacques, 네 임무 때문에 왔다.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "네 죄수 때문에 왔다.";
					link.l1.go = "CapComission6";
				}
			}	
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "죄수들과 관련된 일에 네가 관여하고 있다는 소문을 들었는데...";
				link.l1.go = "Marginpassenger";
			}
		break;
			

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("미쳤냐? 도살놀이라도 하고 싶었던 거야? 모든 해적들이 너한테 화났어, 꼬마야. 여기서 당장 꺼지는 게 좋을 거다...","정신이 나간 모양이군, 꼬마. 몸 좀 풀고 싶었나? 기분 나쁘게 듣지 마, 넌 여기 올 자격 없어. 꺼져!");
				link.l1 = RandPhraseSimple("이봐, 내가 이 상황을 바로잡고 싶어...","이 문제 좀 해결해 줘...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", 나는" + GetSexPhrase("", "요") + " 바다에서의 내 안전에 대해 이야기하고 싶어. 해안 형제단 녀석들이 내 겸손한 존재에 지나치게 관심을 보이고 있어. 그들을 좀 억눌러 줄 수 있겠어?";
			link.l0.go = "pirate_threat";
			
			dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+"! 이번엔 또 뭘 원하지?",
						"뭔가 나한테 말 안 한 거라도 있나? 듣고 있다.",
						"이게 언제까지 계속될 거야... 할 일 없으면 남 방해하지 마!","너는 나더러 예의를 지키라고 했지. 하지만 나도 똑같이 예의를 요구한다!","repeat",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("별거 아니야. 그냥 들른 거다.",
						"아무것도...",
						"좋아...",
						"네 말이 맞아. 미안하다.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "네 죄수 때문에 왔다.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "안녕, Jacques, 네 임무에 관한 거다.";
				link.l1.go = "CapComission3";
			}
		/*	if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak")) //лишний диалог лесник
			{
				link.l1 = "네 죄수 때문에 왔다.";
				link.l1.go = "CapComission6";
			}*/
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "죄수들과 관련된 일에 네가 관여하고 있다는 소문을 들었지...";
				link.l1.go = "Marginpassenger";
			}
		break;

//--> -----------------------------------Сага - Искушение Барбазона---------------------------------------------
		case "Temptation":
			dialog.text = "나 건드리는 게 얼마나 위험한지 아냐? 좋아, 들어주지.";
			link.l1 = "빚이 있어. 큰 빚이지. 곧 갚아야 하는데, 가진 동전이 하나도 없어. 착한 사람들이 그러던데, 너는 계획 짜는 데 소질이 있고, 언제나 한탕 크게 벌 수 있는 곳을 잘 안다더라...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "잘 들어, 꼬마! 나한테 충성하는 놈들에게만 나는 자크 더 카인드맨이다. 다른 놈들에겐 바르바존이고, 때로는 루시퍼 그 자체지. 내가 어떻게 너를 믿을 수 있을지 알겠냐?";
			link.l1 = "덤벼 봐. 절대 후회 안 할 거다!";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "흠... 자크 더 카인드맨이 자기한테 사기 친 놈들한테 뭘 하는지 알겠지? 뭐, 끔찍한 얘기까지는 안 하겠다. 작은 일 하나 시킬 거다. 그거만 해내면 돈 걱정은 싹 사라질 거다.";
			link.l1 = "나를 의심하지 마, 나는 수많은 싸움을 겪었고...";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "닥치고 내 말 들어! 몇 주 전에 네덜란드 순찰대가 내 부하 하나를 생마르탱 근처에서 잡았다. 그놈이 나한테 네덜란드산 비단을 가져오고 있었지. 아주 귀한 물건이야; 네덜란드 놈들은 회사 해군의 수요 때문에 여기엔 소량만 들여온다니까.\n그래서 내가 비단 여섯 타래를 샀고, 시몽 모렐이 자기 브리건틴 '솔트 도그'에 실어 나한테 가져오기로 했는데, 그만 네덜란드 순찰대랑 맞닥뜨렸지. 아니면 일부러였을지도 모르지. 그건 모렐의 항해사가 한 말이야—그 싸움에서 살아남은 건 자기뿐이라고 하더군.\n그 자가 내게 모렐의 항해일지도 줬는데, 거기에도 그 얘기가 적혀 있더라. 일지에 따르면, 모렐은 도망치려다 비단을 바다에 던졌대. 이상하지 않냐? 비단은 가벼운 물건인데. 대포나 버렸어야지; 어차피 순찰대 상대로는 승산도 없었을 텐데.";
			link.l1 = "여기 뭔가 정말 잘못됐군.";
			link.l1.go = "Temptation_4";
		break;
		
		case "Temptation_4":
			dialog.text = "뭐든 가능하지. 내 밑에서 일하는 놈들 중 용감한 놈들은 많지만, 똑똑한 놈들은 훨씬 적지. 기분 나쁘게 듣지 마라, 허. 모렐이 짐을 버린 장소를 직접 확인해야 한다. 선장 일지에 따르면 북위 21도 10분, 서경 61도 30분이다.\n네덜란드 놈들은 비단을 코르크 막대에 감아서 포장하니, 짐뭉치들이 아직도 물 위에 떠 있을 거다. 반드시 여섯 개가 있어야 한다. 당장 출항해라, 시간이 급하다.";
			link.l1 = "가는 중이다!";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			DialogExit();
			SetFunctionTimerCondition("Saga_BarbTemptationOver", 0, 0, 10, false); // таймер
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.quest.BarbTemptation.win_condition.l1 = "location";
			pchar.quest.BarbTemptation.win_condition.l1.location = "SentMartin";
			pchar.quest.BarbTemptation.function = "Saga_BarbTemptationBarkas";
			pchar.questTemp.Saga.BarbTemptation = "silk";
			AddQuestRecord("BarbTemptation", "2");
		break;
		
		case "Temptation_6":
			dialog.text = "좋아! 내 비단 찾았냐?";
			link.l1 = "그래, 네 말대로 여섯 놈이다.";
			link.l1.go = "temptation_wrong";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 90)
			{
				link.l2 = "그래. 그런데 네가 말한 것보다 더 많았어, 여섯이 아니라 아홉 명이었다. 전부 여기 데려왔으니, 이제 네가 이게 어떻게 된 일인지 알아내야지.";
				link.l2.go = "temptation_right";
			}
		break;
		
		case "temptation_wrong":
			dialog.text = "틀린 대답이군. 아홉 개의 포대가 있었어야 했지. 여섯 개를 찾았다면 나머지도 당연히 찾았을 거다. 그러니 네놈은 쥐새끼거나 그냥 게으른 멍청이야. 나한테 비단 세 포대 빚졌고, 날 속이려 한 대가로 '도의적 보상'으로 세 포대 더 내놔야 해.";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 120)
			{
				link.l1 = "건방진 놈 같으니! 기억해 두겠다. 여기 네 비단이다, 내 잘못은 잊자고.";
				link.l1.go = "temptation_wrong_1";
			}
			link.l2 = "여섯 개의 뭇짐이 있었다고 들었지, 한 뭇짐도 더 없다고. 내가 찾은 건 다 줬고, 네가 뭘 생각하든 난 신경 안 써. 비단은 더 없어.";
			link.l2.go = "temptation_wrong_2";
		break;
		
		case "temptation_wrong_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 120);
			dialog.text = "좋아. 다시는 이런 일이 없길 바란다, 왜냐하면 너한테 중요한 일을 맡기고 싶으니까. 돈을 얼마나 벌고 싶어?";
			link.l1 = "돈은 언제나 환영이지. 지금은 오만 페소면 딱 좋겠군.";
			link.l1.go = "junior";
		break;
		
		case "temptation_wrong_2":
			dialog.text = "오, 이제 그런 식으로 말하는 거냐! 이대로 넘어갈 줄 알지 마라. 내가 경고했지 - 감히 나를 속이려고 하지 마! 경비병들! 이 저택에 쥐새끼가 들어왔다!\n";
			link.l1 = "젠장!";
			link.l1.go = "temptation_wrong_fight";
		break;
		
		case "temptation_wrong_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LeFransua_townhall", "goto", "goto1");
			LAi_SetImmortal(npchar, true);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i = 1; i <= 3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("BarbGuard_"+i, "citiz_4"+(i+6), "man", "man", 80, PIRATE, 1, true, "quest"));
				FantomMakeCoolFighter(sld, 80, 100, 100, "blade_21", "pistol4", "bullet", 3000);
				ChangeCharacterAddressGroup(sld, "LeFransua_townhall", "reload", "reload1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "temptation_right":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 80);
			dialog.text = "수고했다. 내가 네 욕심을 시험해봤는데, 잘 통과했군. 아홉 개의 짐이 있었을 거다. 그중 하나는 네 거다. 이제 진지하게 얘기해보자. 돈이 얼마나 필요하지?";
			link.l1 = "돈은 언제나 환영이지, 지금은 오만 페소면 충분하겠다.";
			link.l1.go = "junior";
		break;
		
		case "junior":
			dialog.text = "더 큰 돈을 벌 기회가 있지. 어떤 양반이 나한테 너처럼 믿을 만한 놈을 찾아달라고 했거든. 일은 까다롭고 위험해. 그 자식은 돈이 아주 많으니, 실망시키지만 않으면 그에 걸맞은 보상을 해줄 거다.";
			link.l1 = "준비됐어.";
			link.l1.go = "junior_1";
		break;
		
		case "junior_1":
			dialog.text = "좋아. 이제 잘 들어. 'Knave'라는 이름의 그의 연락책을 찾아야 해. 그 자는 폴라크선 'Marlin'의 선장이야, 내가 아는 건 그게 전부다. Kapsterville에서 그를 찾을 수 있을 거다.\n암호는 '사냥이 시작됐다'야. 그가 뭘 해야 할지 알려줄 거다. 나한테 빚진 건 없어. 그냥 도와주고 싶을 뿐이야. 운이 좋으면, 또 만나게 되겠지.";
			link.l1 = "도와줘서 고맙다. 이제 간다!";
			link.l1.go = "junior_2";
		break;
		
		case "junior_2":
			DialogExit();
			AddQuestRecord("BarbTemptation", "7");
			Saga_SetJuniorInCharles(); // ставим Валета
			pchar.questTemp.Saga.BarbTemptation = "valet";
		break;
		
		case "terrax":
			dialog.text = "뭐라고?! 네놈의... 찢어버리겠다...";
			link.l1 = "넌 못해, 바르바존. 자, 카드나 까보자! 난 얀 스벤손 밑에서 일하지. 네가 잭맨이랑 짠 음모 다 들통났어. 네가 뭘 꾸몄는지, 무슨 역할 했는지 전부 안다. 잭맨이랑 그 동생은 이미 죽었지. 첫째는 블레이즈 샤프를 죽이고 자기 운명도 정했고, 둘째는 입이 너무 무거웠더군, 유감이지만...\n";
			link.l1.go = "terrax_1";
		break;
		
		case "terrax_1":
			dialog.text = "젠장! 타이렉스가 이 일은 절대 용서하지 않겠지, 그래도 나는 아직..";
			link.l1 = "멍청한 짓 하지 마, 자크. 이 대화가 쉽지 않을 거란 건 이미 알고 있었지, 그래서 미리 대비해 놨다. 창문 좀 봐라... 네 오두막은 내 머스킷병들이 포위하고 있다. 내 놈들이 네 마을 곳곳에 있고, 돌격대가 바로 문 앞에 대기 중이다. 학살을 벌이고 싶어? 아주 쉬운 일이지!";
			link.l1.go = "terrax_2";
		break;
		
		case "terrax_2":
			dialog.text = "빌어먹을 놈! 뭐 원하는 거야?";
			link.l1 = "믿지 않겠지, Barbazon. 하지만 내가 원하는 건... 평화야! 난 평화를 원해. 그래서 네가 Tyrex에게 반역한 사실을 그에게 말하지 않을 거다. 하지만, 네가 내가 원하는 대로 한다면 말이지...";
			link.l1.go = "terrax_3";
		break;
		
		case "terrax_3":
			dialog.text = "나한테서 뭘 원하는 거냐? 돈? 얼마면 되지?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "아, 아니, 머리 없는 네 졸개들한테나 맡겨둬라. 나는 다른 게 필요해. 나는 네가 스티븐 도드슨에게 표를 주길 원한다.";
			}
			else
			{
				link.l1 = "오, 아니, 그 멍청한 부하들에게나 맡겨둬라. 난 다른 게 필요해. 마커스 타이렉스에게 표를 주길 원한다.";
			}
			link.l1.go = "terrax_4";
		break;
		
		case "terrax_4":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "And Steven Dodson is on our side.";
			else sTemp = "";
			dialog.text = "진심이냐? 생각 좀 해보자... 내가 싫다고 하면 어쩔 건데?";
			link.l1 = "그럼 넌 완전히 혼자가 되겠지. 정말로 혼자야. 스벤슨, 타이렉스, 그리고 호크가 너를 적대할 거다."+sTemp+"나는 놈들에게 그냥 Knave의 편지랑 Jackman의 형제만 보여줄 거다. 내 말도 믿게 될 테지. 자, 그 다음엔 네가 얼마나 편하게 앉아 있을 수 있을 것 같아?";
			link.l1.go = "terrax_5";
		break;
		
		case "terrax_5":
			dialog.text = "호크? 그 놈이 살아 있다고?!";
			link.l1 = "그래, 맞아. 내가 잭맨이 판 함정에서 그를 구해냈지. 이제 야곱의 가장 가까운 친구가 그의 원수가 될 거다. 그리고 나도 그들 편에 설 거야, 이 점 잊지 마, 바르바존.";
			link.l1.go = "terrax_6";
		break;
		
		case "terrax_6":
			dialog.text = "잭맨은 내 친구가 아니야! 젠장할 놈! 날 궁지에 몰아넣었군!";
			link.l1 = "헛소리 하지 마. 내가 말한 놈에게 표를 던지면 너한테 달라질 건 없어. 이미 말했잖아, 자크, 나는 평화를 원해. 원하면 모든 바론들이 너를 증오하게 만들 수도 있지만... 아직은 안 할 거다.";
			link.l1.go = "terrax_7";
		break;
		
		case "terrax_7":
			GiveItem2Character(pchar, "splinter_jb"); // дать осколок
			dialog.text = "좋아. 됐다. 내 약속이다. 자, 내 돌 조각 가져가라, 네가 필요하지, 맞지?";
			link.l1 = "그래. 드디어 합의에 도달해서 기쁘군, 자크. 그리고 '네이브'의 편지는 기념품 삼아 가져가든가, 아니면 차라리 태워버려. 들키면 곤란하잖아. 아, 그리고 마지막으로 한 가지 더...";
			link.l1.go = "terrax_8";
		break;
		
		case "terrax_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "마지막으로 한 가지 더?! 대체 나한테 또 뭘 원하는 거야?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon"))
			{
				link.l1 = "뭐 하나 상기시켜 주지. 얼마 전, 네가 이그나시오 마르코라는 개를 보내 날 암살하려 했지. 내가 그놈을 죽였고, 네가 스페인 금화 갤리온을 털려던 계획도 내가 파묻었어. 네 친구들을 생마르탱 근처 스페인 매복에 처넣은 것도 나야. 내 이름은 찰리 프린스다! 이제 끝났으니, 자크, 다음에 만나면 나한테 좀 더 예의 갖춰라. 잘 들어, '꼬마', 우린 또 만나게 될 거다, 한 번이 아닐 거라고 장담하지.";
				link.l1.go = "terrax_8_1";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon") && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "뭐 하나 상기시켜 주지. 얼마 전 네 놈이 이그나시오 마르코라는 개를 보내 날 암살하려 했지. 내가 그 자를 죽였고, 내가 네 놈의 스페인 금화 갤리온 약탈 계획도 파묻어 버렸다. 내 이름은 찰리 프린스다! 이제 끝이다, 자크. 다음에 만날 땐 나한테 좀 더 예의 갖춰라. 믿어라, '꼬마', 우린 또 만나게 될 거다, 한 번이 아닐 거야. 잊지 마라, 난 모든 해적 남작들을 내 편으로 두고 있다. 잘 있어라, 바르바존...";
					link.l1.go = "terrax_9";
				}
				else
				{
					link.l1 = "다음에 다시 만나면 나한테 좀 더 공손하게 굴어라. 믿어라, 이 꼬마야, 우리 또 만나게 될 거다, 한 번이 아닐 거고. 잊지 마라, 카리브의 모든 해적 남작들이 내 편이란 걸. 잘 가라, Barbazon...";
					link.l1.go = "terrax_9";
				}
			}
		break;
		
		case "terrax_8_1":
			dialog.text = "";
			link.l1 = "잊지 마라, 카리브의 모든 해적 남작들이 내 편이라는 걸. 잘 가라, Barbazon...";
			link.l1.go = "terrax_9";
		break;
		
		case "terrax_9":
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "26");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Saga_SGM_"+i);
				LAi_SetCitizenType(sld);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
			}
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			bDisableFastReload = false;
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
		break;

//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "하하. 내가 여기 죄수 한 놈만 있다고 생각하나? 이름 대봐.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+". 그 자 여기 있나?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "그랬지. 내가 그 녀석을 바베이도스에서 온 플랜테이션 주인, 비숍 대령한테 팔았어. 그자가 일주일 전에 여기 왔을 때 말이야.";
				link.l1 = "젠장...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "아, 드디어 왔군. 난 그 녀석을 바베이도스에서 온 플랜테이션 주인놈한테 팔 생각하고 있었지, 일주일이나 이주일 안에 온다더군... 몸값은 가져왔나?";
				link.l1 = "봐라, 약간 문제가 있지... 사실, 나한텐 그렇게 많은 돈이 없어. 하지만 일할 의지는 있다.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "그 자를 아직 팔지 않았다니 다행이군. 여기 네 돈이다 – 15만 페소다. 그놈은 어디에 있지?";
					link.l2.go = "CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "너무 굼떴군... 그리고 그 자식이 뭐가 그리 중요하지? 난 그의 친척들이랑만 협상했어.";
			link.l1 = "놈들이 나보고 여기 오라고 했지.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "그래, 너 늦었군. 내가 해줄 수 있는 건 없어.";
			link.l1 = "이봐, 그놈을 얼마에 팔았지, 비밀 아니면 말해 봐?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "에이, 아니야. 하지만 말 안 해줄 거다... 말하면 너 분명 비웃을 테니까. 하하하하! 잘 가라.";
			link.l1 = "또 보자.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{

				dialog.text = "그래, "+pchar.name+", 있잖아, 세상일이 그렇게 돌아가지 않아. 돈 들고 다시 오면 네 그 약골 놈을 데려가게 해주지, 하하.";
				link.l1 = "좋아. 또 보자.";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "그래, 그래... 할 일이 좀 있지... 어디서부터 시작해야 할지 모르겠군. 선을 넘은 해적 하나를 바다에 수장시켜야 해.";
				link.l1 = "정글에서 그냥 죽이면 안 되나?";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "장사는 그렇게 하는 게 아니야, 알겠어... 내가 그 자식 죽일 필요는 없어, 그냥 몇 놈한테 내 몫을 건드리면 어떻게 되는지 가르쳐 줄 뿐이지. 하지만 그놈이 상어 밥이 된다 해도, 난 전혀 신경 안 써.";
			link.l1 = "왜 네 놈 부하들을 직접 보내지 않지?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
			dialog.text = "흠... 그래, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" 우리 보물창고가 저쪽에서 멀지 않은 곳에 있어서 거기에 해적들의 몫이 숨겨져 있다고 몇몇 해적들을 설득했지\n "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". 그들의 두 척 배 '"+pchar.GenQuest.CaptainComission.ShipName1+"' 그리고 '"+pchar.GenQuest.CaptainComission.ShipName2+"'가 얼마 전에 닻을 올리고 출항해서 "+sLoc+". 이제 내가 왜 내 부하놈들한테 이 일을 맡길 수 없는지 알겠지?";
			link.l1 = "그래. 시간이 얼마나 남았지?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12일에서 15일, 그 이상은 안 돼. 놈들이 은닉처에 도착하지 못하게 하는 게 내겐 중요해. 귀중한 화물을 싣고 있는데 가라앉혀 봤자 아무 소용 없지. 그런 경우라면 차라리 여기로 가져오게 하는 게 낫겠군...";
			link.l1 = "좋아, 나도 끼지. 놈들 잡아보겠다.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает имя . лесник
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "걱정하지 마. 내 부하들이 그놈을 네 배로 데려다 줄 거다. 그런데 넌 왜 그놈한테 신경을 쓰는 거지?";
			link.l1 = "나는 아니다. 그의 친척들이 나한테 그를 데려오라고 했지.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "아, 괜찮아. 네 놈 부하를 그렇게 헐값에 사려던 내가 다 미안할 뻔했군. 하하하하! 잘 가라.";
			link.l1 = "또 보자.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																								
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");		// лесник																												  
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в СЖ не работает
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "그래서, , "+GetFullName(pchar)+", 내 놈들이 내 동료들을 침몰시켰나? 크크크...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "아니. 놈들을 잡지 못했어. 돌아오는 길에도 마주치지 않았지.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "내가 그랬지. 놈들은 상어밥으로 던져줬다.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "젠장! 내가 그놈들을 만났든 안 만났든 이제 상관없어! 그리고 네 다음 제안은 뭐지?";
			link.l1 = "혹시 더 쉬운 일 없나?";
			link.l1.go = "CapComission4_1";
			link.l2 = "들어봐, "+NPChar.name+", 죄수 값 좀 깎아라...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "아니.";
			link.l1 = "그럼 작별이다...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "값을 깎으라고?! 네 놈 무능함 때문에 내 물건 다 날렸잖아! 이젠 오히려 값을 올릴 수 있지! 원하면 20만 페소에 데려가든가, 아니면 당장 꺼져.";
			link.l1 = "너무 비싸군... 잘 가라...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "젠장, 동전이나 가져가.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // лесник																			  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));// в СЖ не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правка	// лесник																	  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "이 약골은 네가 데려가도 돼...";
			link.l1 = "잘 가라.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правки имени в сж лесник
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));//в СЖ не работает // belamour gen : это хорошо, но закомментить нужно было)))
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "호호! 잘했군! 저 약골이나 데려가고 운이나 빌어라.";
			link.l1 = "고맙다. 잘 가라.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
	   	/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		     ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "몸값 가져왔나\n "+GetSexPhrase("","라")+"? 내가 그놈을 플랜터들에게 팔아넘기겠다고 한 말, 농담 아니었어.";			
			link.l1 = "들어봐, "+NPChar.name+", 있잖아... 난 그런 돈 없어. 하지만 할 마음은 있어"+GetSexPhrase("","а")+" 처리해.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "그놈을 아직 팔지 않아서 다행이군. 여기 네 돈이다 - 15만 페소. 그놈은 어디에 있지?"link.l2.go ="CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "돈 가져왔냐? 그 자를 플랜테이션에 팔겠다는 말, 농담 아니었어.";			
			link.l1 = "돈 없어, "+NPChar.name+", 하지만 지금 처리 중이다.";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "그 자를 아직 팔지 않았다니 다행이군. 여기 네 돈이다 – 15만 페소다. 그 자는 어디에 있지?"link.l2.go ="CapComission2_3";
			}			
		break;
																																					 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "내가 뭘 하든 네가 뭔 상관이야? 이봐, 꺼지는 게 좋을 거다...";
			link.l1 = "쳇, 진정해라. 너랑 볼 일이 있다. 네가 잡아둔 죄수에 관한 거다.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "아, 좋아. 누구를 몸값 받고 풀어주길 원하지?";
			link.l1 = "잠깐. 나는 누구를 사러 온 게 아니고, 너한테 죄수 하나를 사라고 기회를 주러 왔다. 그리고, 그 놈을 위해 몸값을 챙길 기회도 생길 거다.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "흠. 그런데 왜 내 도움이 필요하지? 왜 직접 돈을 챙기지 않는 거야?";
			link.l1 = "이건 나한테 꽤 위험한 일이야. 당국에 문제 생길 수도 있지.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "하... 좋아, 그럼 보자. 네 포로가 누구냐?";
			link.l1 = "이거야 "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "그래... 네가 거짓말이 아니라면 공정한 거래겠지. 이 놈 값은 쳐줄 수 있겠다 "+iTemp+" 페소를 주든가, 아니면 흥미로운 정보를 대신 줄 수도 있지. 선택은 네가 해.";
			link.l1 = "페소나 챙기는 게 낫겠군. 이딴 일은 지긋지긋하다...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "하! 더 말해 봐. 너 따위가 나한테 흥미로운 얘기 하나쯤은 있겠지.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "돈이다. 가져가라. 이제 네 일이 아니다. 여기서 물건 팔아라.";
			link.l1 = "지금쯤이면 성문 근처에 있을 거야. 고마워! 정말 큰 도움을 줬어.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "천만에, 더 가져와... 또 보자!";
			link.l1 = "행운을 빌지...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT, FLAG_GOODS_VALUABLE_WOOD);
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "똑똑한 놈하고 거래하는 건 괜찮지. 이제 잘 들어라: 며칠 안에\n "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat")+" 스페인 원정대가 본토에서 귀중한 물자를 싣고 올 거다. 그놈들은 화물을 실어갈 배를 기다릴 거야. 일주일 안에 도착하면 그 화물을 네가 차지할 기회가 있지.\n내가 너라면 벌써 내 배로 달려갔을 거다. 그리고 죄수는 여기로 데려와.";
					link.l1 = "고맙다! 물건들은 내 고생에 대한 충분한 보상이 되겠지. 그리고 내 승객은 이미 마을 입구 근처에 있을 거다. 그놈을 네게 데려오게 하겠다.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "똑똑한 놈이랑 거래하니 괜찮군. 이제 잘 들어라: 대략 일주일 후에, 스페인 브리건틴 '"+pchar.GenQuest.Marginpassenger.ShipName1+"' 값진 물건을 가득 실은 배가 출항할 거다 "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" 에게 "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". 서두르면 쉽게 잡을 수 있어.\n아직도 여기 있냐? 내가 너라면 벌써 내 배로 가고 있을 거다. 그리고 죄수도 여기로 데려와.";
					link.l1 = "고맙군! 이 물건들이 내 고생에 대한 충분한 보상이 되겠지. 그리고 내 승객은 이미 마을 입구 근처에 있을 거다. 곧 네게 데려다 줄 거야.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));//лесник - окончание в СЖ // belamour gen
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
//---------------------------------------попытка залезть в сундуки --------------------------------------------
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("강도질이냐!!! 그건 용납 못한다! 각오해라, "+GetSexPhrase("놈","계집")+"...","이봐, 거기서 뭐 하는 거야, 이 자식아?! 나 털 수 있을 줄 알았어? 이제 끝장이야... ","잠깐, 뭐야 이게? 손 떼! 결국 네가 도둑이었군! 여기서 끝이다, 이 자식아...");
			link.l1 = LinkRandPhrase("젠장!","제기랄!!","젠장!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
// ----------------------------------------------блок нод angry--------------------------------------------------
		case "AngryRepeat_1":
            dialog.text = "꺼져라!";
			link.l1 = "이런...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "네 싸구려 수작 따위로 귀찮게 하지 마라. 다음엔 결과가 마음에 안 들 거다...";
        			link.l1 = "알겠어.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("끝났어, 말하지 마.","더 이상 너랑 말하고 싶지 않으니까, 귀찮게 하지 마라.");
			link.l1 = RandPhraseSimple("원하는 대로 해...","흠, 좋아...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "네가 좀 더 예의를 갖추고 무례하게 굴지 않길 바란다?";
        			link.l1 = "확실히 할 거다, Jacques.";
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
            DoReloadCharacterToLocation("LeFransua_town","reload","reload6");
		break;
		
		case "pirate_town":
            dialog.text = "문제를 해결하라고? 네가 무슨 짓을 했는지 알기나 해? 어쨌든, 백만 페소 가져와. 그러면 내가 놈들에게 네 '공적'을 잊으라고 설득해 주지. 그게 싫으면 지옥이나 꺼져.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "좋아, 돈 낼 준비 됐어.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "알겠다. 난 간다.";
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
			link.l1 = "안 해. 나한텐 너무 비싸. 잘 있어...";
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
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
