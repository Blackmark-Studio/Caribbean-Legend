// Эдвард Мэнсфилд, глава буканьеров и авторитетный пират, английская линейка
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
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
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================
	switch(Dialog.CurrentNode)
	{
		case "First time":
            NextDiag.TempNode = "First time";
            if (CheckAttribute(npchar, "Sp5LaVegaAttackDone"))
            {
            	if (NPChar.quest.meeting == "0")
				{
					dialog.Text = TimeGreeting()+"! 나는 "+GetFullName(NPChar)+", 이 구덩이의 새로운 총독이지. 이 동네 깡패놈들 통제하는 게 쉽진 않겠지만, 이제 더 이상 스페인 식민지에 위협이 되진 않아.";
					Link.l1 = "만나서 반갑군. 나는 선장이야 "+GetFullName(Pchar)+". 미안하지만, 난 가봐야겠어.";
					Link.l1.go = "exit";
					NPChar.quest.meeting = "1";
				}
				else
				{
					dialog.Text = TimeGreeting()+". 나는 바쁘다, 정말 바쁘다. 스페인 식민지에 위협이 가지 않게 이 동네 깡패들을 단속해야 하거든.";
					Link.l1 = "그럼 더 이상 귀찮게 안 하지.";
					Link.l1.go = "exit";
				}
            }
            else
            {
				dialog.text = NPCStringReactionRepeat("나한테 할 말 있나? 없어? 그럼\n "+GetSexPhrase("여기서 꺼져!","나를 방해하지 말라고 했잖아.")+"","내 말 충분히 알아들었겠지...","내가 분명히 말했는데도, 자꾸 귀찮게 구는군!","그래, 너는 정말 비교할 수 없는 놈이군 "+GetSexPhrase("너무 무례하군, 내 사랑","이런 무례함이라니, 계집애야","이런 무례함이냐, 계집애")+"...","repeat",30,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("나 간다.","그래, "+npchar.name+", 그렇군.","미안하다, "+npchar.name+"...","아야...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}


					if (npchar.city == sti(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "나한테 시킬 일 있냐?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "자취는 잡았지만, 쥐새끼를 굴에서 끌어내려면 돈이 좀 필요해 — 3만 페소 말이지.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "여기, 밀수꾼 시체에서 찾은 이 편지를 봐라";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "끝났다. 노먼 비고와 그의 배는 이제 바다 악마의 것이야.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "흠... 일거리라, 그랬나? 사실 네가 물어봐서 잘 됐다. 나는 외부 사람이 필요하다. 근처 마을에서 뭔가 알아봐야 하는데, 내 놈들은 거기서 얼굴이 알려져 있거든. 많이는 못 주지만, 뭔가는 챙겨주지.";
			link.l1 = "임무가 뭐지?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "미안하지만, 몇 푼 안 되는 돈 때문에 위험을 감수하진 않겠다. 잘 가라.";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "그럼 잘 들어. 한 달 전에 나는 슬루프 'Saintblue' 선장과 노예 200명을 넘기는 거래를 했지. 그 노예들을 현지 플랜테이션 주인에게 팔 생각이었어. 기한은 이미 지났고, 의뢰인은 걱정하기 시작했지. 그런데 어제, 그 슬루프가 섬 근처에서 목격됐다는 소식을 들었어. 하지만! 선장은 나타나지 않았지. 오늘 내 의뢰인은 선불을 돌려달라고 요구했고, 다른 판매자로부터 노예를 제안받았다고 했어. 더 비싸긴 하지만, 노예 전부를 한 번에 넘긴다고 하더군.";
			link.l1 = "그래서? 네놈 선금 날릴까 봐 내가 며칠 만에 노예 200명을 구해와야 한다고? 그깟 동전 몇 푼 때문에?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "당연히 아니지. 내가 바보처럼 보여? 어차피 그놈한테 선불금 돌려줄 생각 없어. 하지만 그놈이 받은 노예들이 내 것이라는 증거가 필요해. 그놈한테 새 거래를 제안한 놈들을 찾아내면 네놈한테 1만 페소를 주지. 거래할래?";
			link.l1 = "나도 끼지. 누가 범인일지 짐작 가는 놈이라도 있나?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "가망 없어. 다른 놈 찾아봐, 겨우 만 골드에? 미안하지만 그딴 건 안 통해.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "내게 뭔가 생각이 있었으면, 네놈 같은 놈한테 절대 일 안 맡겼지. 그 자식들은 진작에 죽었을 거다. 하지만 놈들이 어떻게 'Saintblue'의 화물과 내 의뢰인에 대해 알게 됐는지 궁금하단 말이지. 놈들한텐 꽤 쉬운 일이었던 것 같아. 이제 알겠냐?";
			link.l1 = "그래, 누군가 네 놈을 배신했지.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "그래, 맞아! 내가 그 놈을 찾고 있지. 내 경쟁자들을 죽이거나 내 노예들을 돌려받는 건 네 우선순위가 아니야. 내가 필요한 건 그 쥐새끼, 아니, 솔직히 말해서 그 놈의 머리를 꼬챙이에 꽂아오는 거다. 이제 왜 내 부하들이 네 임무에 대해 아무것도 알아서는 안 되는지 알겠지? 누가 정보를 팔아넘기는지 알아낼 때까지 모두를 의심할 거다. 그리고 솔직히, 그딴 건 정말 원치 않아...\n";
			link.l1 = "알겠다. 그럼 조용히 움직이겠다. 가는 중이다.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "삼만이라고? 꽤 큰 돈이군... 지금 내가 줄 수 있는 건 5,000페소뿐이다. 그게 전부야. 그리고 돈 들고 튈 생각은 꿈도 꾸지 마라, 잡히면 바로 근처 울타리에 매달아 죽여버릴 테니까! 알겠어?";
			link.l1 = "좋아, 그럼 오천 내놔...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "가져가. 네 수색 결과를 기다리고 있다.";
			link.l1 = "괜찮을 거다.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "하! 좋은 소식이군! 네가 해낼 줄 알았지. 흥미로운 정보가 좀 있어.";
			link.l1 = "내 할 일은 끝냈으니 내 만 금화 내놔.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "그래, 여기 네 보상이다. 하지만 도망치지 마라, 할 일이 하나 더 있다.\n파이퍼는 루거선 '셉티마'의 노먼 비고 선원이다. 노먼 비고가 우리 중 하나라 해도 쥐새끼라는 건 확실하다. 최근 그놈이 섬 근처 바다에서 목격됐지. 네 임무는 그 쥐새끼를 바다 악마한테 보내는 거다. 처음에 내 기대를 저버리지 않았으니, 이것도 네가 처리해줬으면 한다. 15,000페소를 주겠다. 어때, 거래할래?";
			link.l1 = "내가 처리하지! 그 배신자는 죽은 목숨이야.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "있지, 난 그 일에 끼고 싶지 않아... 어차피 시간도 없어. 미안하지만, 난 간다.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "알고 있다, 알고 있어. 내 부하들이 전투를 지켜봤고, 네가 완벽하게 이긴 걸 이미 내게 보고했다. 좋아, 네 일은 잘 끝냈다. 약속대로 15,000페소다. 그리고 고맙다, 네 덕분에 큰 도움이 됐다.";
			link.l1 = "괜찮아, 도와줄 수 있어서 기뻤어! 하지만 이제 가봐야 해, 여기 너무 오래 있었고 할 일이 많거든. 잘 있어라!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;
				
 		case "No_Mansfield_first_time":
			dialog.text = "인사하지, 내 이름은 알리스테어 굿이다. 맨스필드가 죽은 뒤에 내가 버커니어들의 우두머리로 뽑혔다.";
			link.l1 = "반갑군, Alistair.";
			link.l1.go = "exit";
			NextDiag.TempNode = "No_Mansfield";
  		break;
 		case "No_Mansfield":
			dialog.text = "너랑 얘기할 시간 없어. 나중에 와.";
			link.l1 = "나는 이미 떠난다.";
			link.l1.go = "exit";
  		break;
		

// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Get","Get")+" 나가!","내 집에서 꺼져!");
			link.l1 = "이런...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Мэнсфилдом через 30 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "귀찮게 하지 마, 명심해.";
        			link.l1 = "알겠어.";
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
            DoReloadCharacterToLocation("LaVega_town","reload","reload6");
		break;
// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
