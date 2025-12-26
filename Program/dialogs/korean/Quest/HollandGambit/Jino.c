// Джино Гвинейли - алхимик
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> Страж истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino1")
			{
				dialog.text = "오! 좋은 하루입니다, 나리. 어떻게 여기 오셨습니까?";
				link.l1 = "좋은 하루네, 지노. 서로 알아가 보세. 나는 선장이오 "+GetFullName(pchar)+" 그리고 나는 존의 허락을 받고 여기 왔소. 분명히 해두겠소 - 내가 자네의 도움이 필요하듯, 나 역시 자네를 도울 수 있소.";
				link.l1.go = "guardoftruth_0";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "오! 좋은 하루입니다, 나리. 어떻게 여기 오셨습니까? 그리고 존은 어디 있습니까?";
				link.l1 = "그래, 그래... 이 닫힌 문 뒤에 항상 숨어 있던 게 바로 너였군! 흥미롭네... 존 말인데... 그는 이제 없어. 그리고 이 집은 이제 내 거야. 하지만 걱정 마. 서로 좀 알아보자고. 너는 누구고, 여기서 뭐 하고 있는 거지?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
			}
			else
			{
				// --> Страж истины
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "threeitems")
				{
					dialog.text = "안녕하세요, "+pchar.name+". 네 얼굴을 보니 뭔가 중요한 걸 찾은 것 같군. 진리의 수호자의 모든 구성 요소를 모았나?";
					link.l1 = "정확해! 세 가지 물건 모두 내가 가지고 있지: 단검, 지도, 그리고 나침반!";
					link.l1.go = "guardoftruth_34";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino")
				{
					dialog.text = "안녕하세요, "+pchar.name+". 무슨 일이 있었소? 얼굴이 이상하게 굳어 있군...";
					link.l1 = "지노, 너와 상의할 일이 있어. 중요한 일이야.";
					link.l1.go = "guardoftruth";
					break;
				}
				// Ксочитэм
				if (CheckAttribute(pchar, "questTemp.Ksochitam") && pchar.questTemp.Ksochitam == "begin")
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"그래, 기억하네. 이틀이 지났고 자네는 진리의 수호자에 대해 알고 싶어 하는군, 맞지?";
					link.l1 = "그래, 맞아! 뭔가 알아낸 게 있나?";
					link.l1.go = "ksochitam";
					break;
				}
				//--> Португалец
				if (CheckAttribute(pchar, "questTemp.Portugal.Nomoney"))
				{
					dialog.text = "5,000페소 가져왔나, "+pchar.name+"?";
					if (sti(pchar.money) >= 5000)
					{
						link.l1 = "알겠소. 자, 여기 돈이니 필요한 건 모두 사시오.";
						link.l1.go = "Portugal_3";
						SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
						DeleteAttribute(pchar, "questTemp.Portugal.Nomoney");
						pchar.quest.Portugal_Ill1.over = "yes";
						pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
						pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";
					}
					else
					{
						link.l1 = "안타깝게도, 지금은 돈이 없어.";
						link.l1.go = "Portugal_nomoney";
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal.Die"))
				{
					dialog.text = "아아, "+pchar.name+", 정말 유감이오 - 환자가 죽었소. 갑자기 상태가 악화되어 아주 빨리 세상을 떠났소.";
					link.l1 = "안타깝군... 신께서 그의 영혼을 불쌍히 여기시길!";
					link.l1.go = "exit";
					DeleteAttribute(pchar, "questTemp.Portugal.Die");
					pchar.quest.Remove_Avendel.win_condition.l1 = "Location_Type";
					pchar.quest.Remove_Avendel.win_condition.l1.location_type = "town";
					pchar.quest.Remove_Avendel.function = "RemoveAvendelnDoc";
					AddQuestRecord("Portugal", "6");
					CloseQuestHeader("Portugal");
					pchar.questTemp.Portugal = "end";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToAntigua")
				{
					dialog.text = "안녕하세요, "+pchar.name+". 무슨 일이라도 있소? 몹시 걱정스러워 보이는데...";
					link.l1 = "지노, 자네에게 좀 특별한 부탁이 있네! 내 배에 고열에 시달리는 남자가 있는데, 지금 헛소리를 하며 의식도 없어... 도와줄 수 있겠나?";
					link.l1.go = "Portugal";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Portugal_wait")
				{
					dialog.text = ""+pchar.name+", 나는 환자를 기다리고 있네. 서두르게, 그를 여기로 빨리 데려올수록 내가 살릴 수 있는 가능성이 높아지니.";
					link.l1 = "그래, 그래, 곧바로 여기로 데려오게.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentStart")
				{
					dialog.text = "딱 맞는 때에 그를 데려왔군, "+pchar.name+". 그는 위독한 상태지만, 아직 희망은 있습니다.\n선장님, 약재가 거의 다 떨어졌고 정글에서 채집할 시간도 없습니다. 현지 약초상들에게서 전부 사야 하는데 5,000페소가 필요합니다. 그 돈을 마련해 주실 수 있습니까?";
					if (sti(pchar.money) >= 5000)
					{
					link.l1 = "알겠소. 자, 돈을 가져가서 필요한 건 모두 사시오.";
					link.l1.go = "Portugal_3";
					SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
					}
					else
					{
						link.l1 = "유감이지만, 지금은 돈이 없어.";
						link.l1.go = "Portugal_nomoney";
						pchar.quest.Portugal_Ill.over = "yes";
						pchar.quest.Portugal_Ill1.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill1.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
						pchar.quest.Portugal_Ill1.function = "Portugal_ToAntiguaOver";//не принесёт через 1 день - Португальцу капут
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentCurrent")
				{
					dialog.text = "지금은 할 말이 없소, "+pchar.name+". 나는 환자의 생명을 위해 싸우고 있소. 아직 희망이 조금 남아 있소. 나중에 다시 찾아오시오, 곧 더 구체적으로 말씀드릴 수 있을 것 같소.";
					link.l1 = "좋아, Gino, 나중에 다시 오겠다.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentFinish")
				{
					pchar.quest.Portugal_Ill.over = "yes";
					dialog.text = "소식이 있소,"+pchar.name+". 네 부하가 괜찮다고는 못 하겠지만, 살아 있어. 병세가 가라앉고 있고, 호전되는 게 보여. 솔직히 말해 내 약이 이렇게까지 효과를 볼 줄은 몰랐지.";
					link.l1 = "좋은 소식이군, 지노. 그런데 말해보게, 내가 그를 언제 데려갈 수 있나? 우리는 먼 항해를 해야 하고, 시간이 촉박하네.";
					link.l1.go = "Portugal_4";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentComplete")
				{
					dialog.text = "안녕하십니까, 선장님. 뵙게 되어 반갑습니다.";
					link.l1 = "우리 환자는 어때, 지노?";
					if (GetQuestPastDayParam("questTemp.Portugal_threedays") > 2) link.l1.go = "Portugal_9";
					else link.l1.go = "Portugal_threedays";
					break;
				}
				// <--Португалец
				dialog.text = "안녕하십니까, 선장님. 잘 지내고 계십니까? 제 도움이 필요하신가요?";
				if (!CheckAttribute(npchar, "quest.rome"))
				{
					link.l1 = "그래. 지노, 자네는 박식한 사람인 것 같으니, 혹시 라틴어도 아는가...";
					link.l1.go = "rome";
				}
				if (CheckCharacterItem(pchar, "chemistry"))
				{
					link.l2 = "나는 좀 다른 게 있소. 작은 선물을 준비했지. 자, 이 책을 한번 보시오.";
					link.l2.go = "chemistry";
				}
				if (CheckAttribute(npchar, "quest.colt") && CheckCharacterItem(pchar, "pistol7"))
				{
					link.l2 = "그래, 지노. 이 권총을 보여주고 싶어. 이런 걸 본 적 있나?";
					link.l2.go = "colt";
				}
				if (CheckAttribute(npchar, "quest.sample") && CheckCharacterItem(pchar, "pistol7") && CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
				{
					link.l2 = "내 권총에 쓸 화약 샘플을 가져왔소.";
					link.l2.go = "colt_1";
				}
				if (CheckAttribute(npchar, "quest.cartridge"))
				{
					link.l2 = "권총 건에 대한 혐의는 어떻게 됐어? 아직 단서라도 잡았나?";
					link.l2.go = "cartridge";
				}
				// Addon 2016-1 Jason Пиратская линейка
				if (CheckAttribute(pchar, "questTemp.Mtraxx.Gord"))
				{
					link.l3 = "지노, 선장 일지에서 'gord'라는 낯선 단어를 발견했어. 무슨 뜻인지 알아?";
					link.l3.go = "mtraxx";
				}
				link.l9 = "좋은 하루구나, 지노. 나는 잘 지내고 있으니, 도움은 필요 없네. 그냥 자네가 잘 있는지 확인하고 잠깐 이야기나 하려고 왔네.";
				link.l9.go = "exit";	
			}
			NextDiag.TempNode = "First time";
		break;

		case "meeting":
			pchar.questTemp.HWIC.Jino = "true"; // Addon 2016-1 Jason Пиратская линейка
			dialog.text = "내 이름은 지노야. 지노 그비네일리. 나는 과학자지. 내 일은 머독 나리를 위해 가루, 혼합물, 그리고 다른 약들을 만드는 거야. 하지만 그가 사라진 이후로는...";
			link.l1 = "글쎄, 나는 "+GetFullName(pchar)+". 내 배의 선장이 되었군. 그럼, 자네는 연금술사란 말인가?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "나는 연금술사일 뿐만 아니라 의사이기도 하오. 의학에 대해 상당한 지식이 있지. 치유에 쓰이는 약초에 대해 잘 알고, 그것들로 혼합물과 물약을 만들 수도 있소. 하지만 화학이야말로 내 진정한 소명이라네. 나는 많은 실험을 하고, 내 발명품 중 일부는 자네 같은 이들에게 쓸모가 있을 수도 있지.\n나는 라틴어, 프랑스어, 영어, 이탈리아어를 알고 있네. 자네가 머독 씨처럼 약국을 운영할 생각이라면 내 도움이 반드시 필요할 것이오...";
			link.l1 = "오호! 이렇게 박식한 사람을 만나는 건 흔치 않은 일이군. 약국 일도 괜찮지만, 나는 선원이야... 흠, 나도 좀 이상하게 들리네... 아무튼, 우리 곧 친구가 될 거라 확신해, 지노. 여기 계속 살면서 네 과학 연구를 해도 돼...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "";
			link.l1 = "그리고 내가 언젠가 연금술사나 치료사, 과학자의 도움이 필요하게 된다면 누구에게 부탁해야 할지 알겠군... 그런데, 왜 항상 실내에만 있소? 밖에는 전혀 나가지 않소?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "실험에 쓸 재료나 약초가 필요할 때는 밖에 나가긴 하지. 혼자 사는 게 내 방식이고, 그게 좋아. 나는 평생을 과학에 바쳤고, 평범한 삶에는 아무런 흥미도 없어. 책, 논문, 시험관, 증류기...\n머독 나리가 약을 만들어 주는 대가로 그런 기회를 내게 주었지.";
			link.l1 = "이제 시간이 더 많아지겠군, 지노. 하지만 내가 도움이 필요할 땐 실험 시간을 좀 양보해야 할 거야, 알겠지?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "물론입니다, 선장님. 앞으로 선장님이라 부르겠습니다, "+GetAddress_Form(NPChar)+", 괜찮으시다면요? 혹시 내 실무 능력이나 이론적 지식이 필요할 때를 대비해 모든 연구 자료를 남겨두겠습니다.";
			link.l1 = "훌륭하군. 이렇게 빨리 서로 이해하게 되어 기쁘오. 비용에 대해서는 걱정 마시오, 나나 내 경리관이 때때로 적당한 금액을 남겨둘 것이니.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "감사합니다, 선장님. 저는 많이 필요하지 않아요... 선장님, 제게 생각이 있는데요... 연금술 기술을 좀 배워보시는 게 어떨까요? 정말 도움이 될 수도 있어요.";
			link.l1 = "흠. 예전에 형이 내게 말했지 - 뭐든 직접 손으로 하는 걸 주저하지 말라고. 그러니, 좋아. 왜 안 되겠어. 뭘 보여줄 건가?";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "글쎄, 확실히 네가 철을 금으로 바꿀 수는 없겠지, 그건 아직 불가능하니까... 하지만 지침에 따라 재료를 섞어서 물약이나 다른 유용한 물건을 만드는 법은 배울 수 있어. 자, 이 가방을 가져가. 초보 연금술사에게 필요한 모든 것이 들어 있다네: 시험관, 플라스크, 증류기, 증류 장치, 주걱, 유리관, 버너 등등...\n";
			link.l1 = "흥미롭군!";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			Log_Info("You have received an alchemist's kit");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "물약이나 아이템을 만들려면 반드시 조제법을 알아야 하오. 조제법은 상인에게서 살 수도 있고, 어디서든 발견할 수도 있지. 조제법을 익힌 뒤에는 필요한 모든 재료를 모으고, 거기에 적힌 대로 정확히 따라야 하오.\n 연금술 도구를 사용하고, 절구와 막자를 찾아 구입하며, 도가니도 구해 보시오—아쉽게도 내가 줄 여분은 없네. 약초, 증류주, 물약, 광물, 잡동사니—올바른 조제법과 도구만 있다면 뭐든 쓸 수 있지.";
			link.l1 = "알겠어. 시간 날 때 뭔가 한번 섞어볼게. 고마워, 지노! 간단한 조리법 하나 알려줄 수 있어? 처음 시작할 만한 걸로? ";
			link.l1.go = "meeting_8";
		break;
		
		case "meeting_8":
			dialog.text = "간단한 일은 없네... 하지만 여기, 해독제 조제법을 가져가게. 이 정도는 자네가 해낼 수 있을 거라 생각하네. 받아가게.";
			link.l1 = "고마워! 내가 배울게. 이제 안녕, 지노! 내 집을 잘 지켜줘. 내가 이곳에 자주 올 것 같지 않아서, 네 방뿐만 아니라 건물 전체를 마음껏 써도 돼.";
			link.l1.go = "meeting_9";
		break;
		
		case "meeting_9":
			DialogExit();
			GiveItem2Character(pchar, "recipe_potion4"); // belamour legendary edition
			Log_Info("You have received an antidote recipe");
			PlaySound("interface\notebook.wav");
			Log_Info("You need to have the Alchemy skill in order to craft potions, amulets and items!");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "rome":
			dialog.text = "예, 선장님, 저는 고대 로마인들의 언어를 압니다. 모든 학자, 특히 치료사나 연금술사는 반드시 라틴어를 알아야 하니까요. 제 라틴어 지식이 필요하십니까?";
			link.l1 = "그래. 지노, 날 바보로 보지 마. 하지만... 음, 뭐라고 설명해야 할지...";
			link.l1.go = "rome_1";
		break;
		
		case "rome_1":
			dialog.text = "솔직하게 말하시오, 선장. 머뭇거리지 말고.";
			link.l1 = "좋아. 학문적인 라틴어 격언 목록을 만들어줄 수 있겠나? 있잖아, 내게 자기 '박식함'을 자랑하길 좋아하는 사람이 있는데, 가끔은 그런 라틴어 문구를 써서 나를 무식하게 보이게 하거든. 예를 들면... 'si vis pacem, para bellum' 같은 거 말이야...";
			link.l1.go = "rome_2";
		break;
		
		case "rome_2":
			dialog.text = "'Si vis pacem, para bellum', 그 말인가?";
			link.l1 = "그래, 그래. 건방진 내 브... 아니, 내 친구를 이기려고 그 기술들을 배우고 싶어.";
			link.l1.go = "rome_3";
		break;
		
		case "rome_3":
			AddQuestRecordInfo("Rome", "1");
			dialog.text = "당신의 부탁에는 이상한 점도, 부끄러운 점도 없소, 선장. 역사의 한 페이지를 장식한 옛 현인들의 격언을 아는 것은 교양인의 증거지. 자, 이 글을 받으시오. 당신이 원하던 것이오.";
			link.l1 = "고마워, 지노! 정말 고맙다! 한가할 때 읽어볼게...";
			link.l1.go = "exit";
			npchar.quest.rome = true;
			NextDiag.TempNode = "First time";
		break;
		
		case "chemistry":
			RemoveItems(pchar, "chemistry", 1);
			Log_Info("You have given Lavoisier's chemistry textbook");
			dialog.text = "보여줘... (읽으며) 말도 안 돼! '작은 선물'이라고? 이 책은 값을 매길 수 없어! 어디서 구한 거지?! 이건... 진짜 보물이잖아!";
			link.l1 = "마음에 들어 하니 기쁘군.";
			link.l1.go = "chemistry_1";
		break;
		
		case "chemistry_1":
			dialog.text = "(읽으며) 믿을 수가 없어! 이런 건 들어본 적도 없는데... 그리고 이건? 도무지 이해가 안 되네... 하지만 곧 알게 되겠지, 젠장! 아, 곧 내 실험실에서 일이 끓어오를 거야! "+pchar.name+", 너는 네가 내게 무엇을 준 건지도 모르고 있군...";
			link.l1 = "왜 안 하겠소? 하지. 과학자에게 과학 서적을 주는 거지...";
			link.l1.go = "chemistry_2";
		break;
		
		case "chemistry_2":
			dialog.text = "하지만 이 기적의 저자가 누구지? 앙투안-로랑 드 라부아지에, 프랑스... 들어본 적 없는데. 그런데 잠깐! 이게 어떻게 된 거지! 인쇄 연도가 1789년이라고? 그런데 어떻게...";
			link.l1 = "나도 왜 그 해가 거기에 적혀 있는지 모르겠어. 아니, 어쩌면 알지도 모르지. 하지만 너무 깊이 생각하지 않는 게 좋을 거야. 책이 쓸모 있으면 그걸로 충분하니까.";
			link.l1.go = "chemistry_3";
		break;
		
		case "chemistry_3":
			dialog.text = "내가 기대했던 것보다 훨씬 희망적이군, 그리고 그 해는 뭔가 인쇄상의 오류인 게 틀림없어... 뭐, 아무튼. 정말 고맙소, 선장!";
			link.l1 = "천만에, Gino. 이제 모두 네 거다.";
			link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "pistol7"))
			{
				link.l1 = "그게 다가 아니야, Gino. 이 권총을 보여주고 싶어. 이런 건 본 적 있나?";
				link.l1.go = "colt";
			}
			npchar.quest.colt = true;
		break;
		
		case "colt":
			dialog.text = "나는 총기 장인은 아니지만 한번 살펴보지... 아니, 이런 건 본 적이 없어. 왜 묻는 거지?";
			link.l1 = "이 권총은 강력하고 파괴적이지만, 사용하려면 특별한 탄약이 필요해. 다른 건 전혀 소용없어. 그리고 나도 추가 탄환을 어떻게 만드는지 전혀 모르겠어. 그래서 조언을 구하려고 여기 온 거야.";
			link.l1.go = "colt_1";
		break;
		
		case "colt_1":
			dialog.text = "예시로 보여줄 탄환 한 개라도 가지고 있소? 없다면, 유감이지만 도와줄 수 없겠군.";
			if (CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
			{
				link.l1 = "그렇소. 탄약은 두 부분으로 되어 있소: 총알이 들어 있는 탄환 자체와, 화약에 불을 붙이는 이 장치요.";
				link.l1.go = "colt_2";
			}
			else
			{
				link.l1 = "이런 실패라니! 정말 부끄럽군! 좋아, 더 찾아서 당신에게 가져다주지.";
				link.l1.go = "exit";
				npchar.quest.sample = true;
			}
			DeleteAttribute(npchar, "quest.colt");
		break;
		
		case "colt_2":
			RemoveItems(pchar, "pistol7", 1);
			RemoveItems(pchar, "GunCap_colt", 1);
			RemoveItems(pchar, "shotgun_cartridge", 1);
			Log_Info("You have given a revolver's cartridge");
			Log_Info("You have given a capsule");
			PlaySound("interface\important_item.wav");
			dialog.text = "흥미로운데! 간단해 보이지만, 안에 화약이 들어가고, 총알은 위에서 넣는 거군. 그런데 좀 이상하게 생겼네. 그리고 이 '물건'... 흠. 이게 없으면 화약이 터지지 않는 거지? 궁금하군... 봐, 선장. 이건 전부 나한테 맡겨. 권총이랑 장전물까지. 한 달 후에 나를 찾아오게. 분석할 시간이 필요하니까.";
			link.l1 = "좋아! 이게 어떻게 작동하는지 알아봐 줘, 나 이 권총 정말 쏴보고 싶거든.";
			link.l1.go = "colt_3";
		break;
		
		case "colt_3":
			dialog.text = "주된 문제는 화약이 폭발하게 만드는 이 물질이 무엇으로 이루어졌는지 알아내는 것이오.\n이 책이 도움이 될 거요.\n내가 이 일의 진상을 밝혀내 보겠소.";
			link.l1 = "좋아. 잘 가라, 지노!";
			link.l1.go = "colt_4";
		break;
		
		case "colt_4":
			DialogExit();
			DeleteAttribute(npchar, "quest.sample");
			SetFunctionTimerCondition("Colt_Timer", 0, 0, 30, false); // таймер
		break;
		
		case "cartridge":
			dialog.text = "예, 권총의 탄환이 무엇으로 만들어졌는지 알아냈습니다. 당신이 준 책 덕분에 가능했지요. 그 책이 없었으면 불가능했을 겁니다. 하지만 경고해야겠군요, 선장님. 이 무기에 쓸 탄환과 캡슐을 만드는 일은 쉽지 않을 것입니다.";
			link.l1 = "캡슐?";
			link.l1.go = "cartridge_1";
		break;
		
		case "cartridge_1":
			dialog.text = "캡슐이란, 네가 말한 대로 화약에 불을 붙이는 '그것'이야. 하지만 처음부터 시작하자. 준비됐나?";
			link.l1 = "그래! 아주 잘 듣고 있소.";
			link.l1.go = "cartridge_2";
		break;
		
		case "cartridge_2":
			AddQuestRecordInfo("Recipe", "shotgun_bullet");
			SetAlchemyRecipeKnown("shotgun_bullet");
			dialog.text = "그러니 먼저, 특별한 탄환을 만들어야 하오. 평범한 탄환으로는 안 되지. 반드시 특이한 원뿔형이어야 하오. 그런 탄환을 만들려면, 내가 부르는 탄환 주형을 찾아야 하오. 평범한 납탄을 구해 도가니에 녹이고, 녹인 납을 탄환 주형에 부으시오. 주형이 식을 때까지 기다렸다가 완성된 탄환을 꺼내면 되오.";
			link.l1 = "그런 탄환 주형은 어디서 구할 수 있지?";
			link.l1.go = "cartridge_3";
		break;
		
		case "cartridge_3":
			dialog.text = "모르겠습니다, 선장님. 저는 연금술사지 대장장이가 아닙니다. 이 탄환을 예로 들어보시지요, 아마 무엇을 해야 할지 감이 올 수도 있습니다.";
			link.l1 = "좋아. 계속해...";
			link.l1.go = "cartridge_4";
		break;
		
		case "cartridge_4":
			AddQuestRecordInfo("Recipe", "shotgun_cartridge");
			SetAlchemyRecipeKnown("shotgun_cartridge");
			dialog.text = "그다음에는 화약을 담을 통을 만들어야 하네. 그 안에 탄환을 넣는 거지. 내가 자네를 위해 자세한 설명서를 써두었네. 꼼꼼히 읽고 한번 해보게.";
			link.l1 = "좋군...";
			link.l1.go = "cartridge_5";
		break;
		
		case "cartridge_5":
			AddQuestRecordInfo("Recipe", "GunCap_colt");
			SetAlchemyRecipeKnown("GunCap_colt");
			dialog.text = "이제 우리는 캡슐을 구해야 해. 아주 얇은 구리판이 필요하니, 구리 덩어리로 직접 만들어라.\n그 위에 탄환과 같은 크기의 원을 새겨.\n그리고 그 안에 왁스를 이용해 폭발성 은을 넣어라.";
			link.l1 = "폭발성 은? 그게 뭐지?";
			link.l1.go = "cartridge_6";
		break;
		
		case "cartridge_6":
			dialog.text = "나도 그 사실을 몰랐네, 자네 책을 보고 그 비밀을 알게 되었지. 은과 알코올, 질산으로 만들 수 있는 흰 가루야. 마찰이나 흔들림에도 쉽게 폭발해서, 권총 탄환의 화약을 점화하는 데 아주 유용하지. 썩 유쾌한 물건은 아니야, 실험 중에 두 번이나 터져버렸거든. 그러다 겨우 조제법을 알아냈지.";
			link.l1 = "이 책을 가지고 있어서 운이 좋았어!";
			link.l1.go = "cartridge_7";
		break;
		
		case "cartridge_7":
			dialog.text = "조심 또 조심해, 이건 엄청나게 폭발성이 강하니까! 나도 직접 만들 수는 있지만, 뇌은을 보관하는 건 너무 위험해. 만들어지자마자 바로 캡슐에 넣는 게 아주 중요하지. 나는 구리 캡슐을 만들 수 없어, 대장장이가 아니라고 전에 말했잖아.";
			link.l1 = "좋아. 조리법을 줘, 내가 직접 배울 테니까.";
			link.l1.go = "cartridge_8";
		break;
		
		case "cartridge_8":
			AddQuestRecordInfo("Recipe", "OxyHydSilver");
			SetAlchemyRecipeKnown("OxyHydSilver");
			dialog.text = "천만에. 반드시 조리법을 정확히 따르고, 순서를 조심해서 지켜라. 그렇지 않으면 플라스크와 함께 하늘로 날아가게 될 테니.";
			link.l1 = "조심하겠습니다.";
			link.l1.go = "cartridge_9";
		break;
		
		case "cartridge_9":
			dialog.text = "또한, 이 두 개의 플라스크도 가져가시오. 이것에는 질산이 들어 있고, 저것에는 알코올이 들어 있소. 이걸로 약 20개의 캡슐을 채울 만큼의 폭발성 은을 만들 수 있을 것이오.";
			link.l1 = "고마워, Gino!";
			link.l1.go = "cartridge_10";
		break;
		
		case "cartridge_10":
			GiveItem2Character(pchar, "Mineral29");
			GiveItem2Character(pchar, "Mineral28");
			Log_Info("You have received a flask of nitric acid");
			Log_Info("You have received a flask of spirit");
			PlaySound("interface\important_item.wav");
			dialog.text = "권총과 샘플 화약도 가져가시오. 행운을 빕니다, 선장님. 화약 제조 잘 하시고, 무사히 살아남으시길 바라오.";
			link.l1 = "나는 내 몸은 내가 지킬 것이오. 그리고, 지노, 내가 자네더러 천재라고 말한 적 있던가?";
			link.l1.go = "cartridge_11";
		break;
		
		case "cartridge_11":
			TakeNItems(pchar, "pistol7", 1);
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 1);
			dialog.text = "선장님, 그런 말씀 하시면 제가 다 얼굴이 빨개지잖아요. 진심입니다...";
			link.l1 = "좋아. 잘 가라, 지노! 너는 내 최고의 연금술사야!";
			link.l1.go = "cartridge_12";
		break;
		
		case "cartridge_12":
			DialogExit();
			DeleteAttribute(npchar, "quest.cartridge");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx":
            dialog.text = "고르드, 고르드... 선장에 대해 좀 더 말해 줄 수 있나? 그는 어디 출신인가?";
			link.l1 = "모르겠어. 북쪽 어딘가에서 태어났다고는 하지만, 가끔 그를 바이킹이라고 불렀지.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "바이킹! 그래, 그래, 기억나, 역사책에서 읽은 적 있어. 고르드는 자유로운 야를의 요새화된 취락이야.";
			link.l1 = "자유로운 야를? 그게 누군데?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "북방인들의 왕자다. 자유로운 야를들과 그들의 전사 무리가 수백 년 전 드라카르라는 배를 타고 유럽을 약탈하고 노략질하곤 했지. 해적이라고 부를 수도 있겠군. 고르드는 그들의 근거지이자 집이었고, 쉴 수 있고 농사짓고 연회를 벌이던 곳이었지.";
			link.l1 = "알겠어. 그럼 이 골짜기가 저 해적의 소굴이겠군... 고마워, 지노!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookFourth");
		break;
		
	// ----------------------------------------- Португалец ----------------------------------------------------
		case "Portugal":
			dialog.text = "열과 망상이라니, 흥미롭군. 즉시 그를 여기로 데려오시오! 내가 할 수 있는 건 해보겠소. 하지만 상태가 너무 심각하다면 아무것도 약속할 수 없소... 그가 그대의 장교요?";
			link.l1 = "아니, 다행히도 그는 아니야. 지노, 들어봐, 그가 누군지 묻지 말고 그냥 네가 할 수 있는 만큼만 해 줘, 이건 정말 나한테 중요해!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "좋아, 그를 집 안 네 방으로 데려가거라. 내가 약초 몇 가지를 준비하마... 어쩌면 이 뿌리가...";
			link.l1 = "지금 당장 그를 여기로 데려오겠소!";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1 = "location";
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1.location = "SentJons_HouseF3";
			PChar.quest.Portugal_DoctorPodhodit.function = "Portugal_DoctorPodhodit";
		break;
		
		case "Portugal_nomoney":
			dialog.text = "그럼 최대한 빨리 찾아오시오, 약이 없으면 내가 그를 치료할 수 없고, 서두르지 않으면 이미 늦을 수도 있소.";
			link.l1 = "좋아, 내가 돈을 마련하겠소.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal.Nomoney = "true";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "훌륭합니다, 선장님. 이제 제가 혼합약을 좀 준비하겠으니, 제 환자 곁을 떠나시길 권합니다. 내일 다시 오십시오.";
			link.l1 = "좋아, 지노. 나는 네 조제와 천재성을 믿지.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal = "TreatmentCurrent";
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
		break;
		
		case "Portugal_4":
			dialog.text = "글쎄, 내 생각엔 2주면 괜찮아질 거요. 춤을 출 수 있을지는 장담 못 하지만, 적어도 자기 발로 설 수는 있을 테니 그건 확실하오.";
			link.l1 = "젠장, 나에겐 2주나 기다릴 시간이 없어! 최대한 빨리… 출항해야 해!";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "선장님, 저는 마법사는 아니지만 저 사람은 지금 너무 약해졌다는 건 확실히 말씀드릴 수 있습니다. 배에서 며칠도 버틸 수 있을지 모르겠으니, 절대 그를 옮기면 안 됩니다!";
			link.l1 = "좋아, 좋아, 하지만 2주—아니, 1주일도 너무 길어!";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "사흘... 그래, 사흘 후라면 항해를 시도해도 되겠지만, 그가 간호와 약이 필요하니 중간에 정박도 해야 할 것이오.";
			link.l1 = "나는 의사가 있으니 그가 그를 돌볼 거요. 사흘 뒤에 돌아와서 그를 데려가겠소, 내가 할 수 있는 최대한이오. 우리는 이동해야 하오, 중간에 멈추더라도... 그래, 그리고 한 가지 더 - 지노, 너는 천재야!";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			dialog.text = "감사합니다, 선장님. 사흘 뒤에 친구를 데리러 오십시오. 그 전까지는 절대 방해하지 마십시오. 완전히 쉬어야 하니까요.";
			link.l1 = "좋아, 알겠어. 사흘 안에 그 자를 데려올게.";
			link.l1.go = "Portugal_8";
		break;
		
		case "Portugal_8":
			DialogExit();
			SaveCurrentQuestDateParam("questTemp.Portugal_threedays");
			pchar.quest.Portugal_Ill2.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill2.function = "Portugal_ToAntiguaOver";//чтобы не тянул
			pchar.questTemp.Portugal = "TreatmentComplete";
			pchar.quest.Avendel_room.win_condition.l1 = "location";
			pchar.quest.Avendel_room.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room.function = "AvendelSpeach";
		break;
		
		case "Portugal_threedays":
			dialog.text = "그는 잘 지내고 있지만, 진전이 더딥니다.\n아직 데려갈 수 없습니다.";
			link.l1 = "그래, 그래, 지노, 기억하고 있어. 사흘...";
			link.l1.go = "exit";
		break;
		
		case "Portugal_9":
			pchar.quest.Portugal_Ill2.over = "yes";
			dialog.text = "악화되진 않았지만, 그렇다고 딱히 호전된 것도 아니오. 아직 의식이 없고, 자신이 어디에 있는지, 왜 여기 있는지도 전혀 모르는 상태요. 그래도 크게 괴로워하는 것 같진 않소. 아직 열이 있어서, 지금 그를 배에 태우는 게 좋은 생각인지는 잘 모르겠소.";
			link.l1 = "더는 기다릴 수 없어, 여기서 이미 너무 오래 머물렀잖아. 그 자식 항해에 도움이 될 만한 약재 챙기고, 이제 출발한다. 저 놈이 사형 선고를 받을 때까지 살아남을 만큼은 튼튼하길 바랄 뿐이지...";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			dialog.text = "잠깐만요, 선장님! 내가 지금까지 사형수들을 치료한 거였소? 이게 뭐야, 도대체? 여기서 엄청난 일이 벌어졌는데, 마른 화약을 만드는 게 얼마나 힘든지 아시오...";
			link.l1 = "지노, 그건 네가 알 필요 없는 일이야. 너무 걱정하지 마, 그는 해적이고 자기 부류 중에서도 악명이 높은 놈이야. 나는 가능한 한 빨리 그를 회사 당국과의 회의를 위해 퀴라소로 데려가야 해. 끝.";
			link.l1.go = "Portugal_11";
		break;
		
		case "Portugal_11":
			dialog.text = "좋아, 네가 더 잘 알겠지. 해적이라면... 퀴라소로 가. 뭐든 상관없지만, 내 말 들어. 그는 대부분의 시간을 자고 있겠지만, 배가 흔들리고 숨막히는 더위 때문에 모든 과정이 지연될 수 있어. 며칠 항해한 뒤에는 정박해서 네... 포로를 뭍에서 쉬게 하는 걸 추천하네. 그렇지 않으면 퀴라소에 도착해서 시체만 매달게 될 수도 있어... ";
			link.l1 = "좋소, 그렇게 하지. 마르티니크면 충분하겠군, 쿠라사오까지 거의 중간쯤이니. 바람이 순조롭기를 바라오. 이제 그를 데리고 가서 출발하겠소. 다시 한 번 고맙소, 지노.";
			link.l1.go = "Portugal_12";
		break;
		
		case "Portugal_12":
			dialog.text = "환영하오, 선장. 네게는 나흘, 아니 다섯 날이 있소—그 이상은 안 되오. 그리고 마지막으로 한마디만 더... 알겠지만, 나는 대개 사람을 치료해서 그들이 내 치료 후에 교수형을 당하라고 하는 게 아니오. 의사는 환자가 누구든 책임이 있소. 그런데 지금은 정말 기분이 좋지 않구려...";
			link.l1 = "이 모든 일에 당신을 끌어들여 미안하오, 하지만 당신 없이는 우리에게 아무런 희망도 없었소. 지금 당장 출항해야 하오, 아니면 포르투갈 녀석들이 우릴 막으려고 문 앞에 다 모일 것이오.";
			link.l1.go = "Portugal_13";
		break;
		
		case "Portugal_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3_Room", "goto", "goto2", "Portugal_JinoNorm", -1);//Джино в свою комнату
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			pchar.quest.Portugal_Ill3.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill3.function = "Portugal_ToAntiguaOver";//5 дней до Мартиники
			pchar.questTemp.Portugal = "ToMartinique";
			pchar.quest.Avendel_room1.win_condition.l1 = "location";
			pchar.quest.Avendel_room1.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room1.function = "AvendelSpeach";
			pchar.quest.Portugal_street.win_condition.l1 = "location";
			pchar.quest.Portugal_street.win_condition.l1.location = "SentJons_town";
			pchar.quest.Portugal_street.function = "PortugalOnStreet";
		break;
		// <-- Португалец
		case "guardoftruth_0":
			dialog.text = "흥미롭군... 그런데 정확히 어떻게 나를 도울 수 있다는 거지? 나는 아무런 도움이 필요 없고, 부탁한 적도 없네...";
			link.l1 = "하지만 그게 필요할 거요. 내 말부터 듣고, 그다음에 결정하시오.";
			link.l1.go = "guardoftruth";
		break;
		
		case "guardoftruth":
			dialog.text = "귀 기울이고 있소.";
			link.l1 = "나는 최근에 산티아고에 다녀왔네... 빈첸토 신부를 방문했지. 그분이 실종된 비서 이름을 찾고 있었는데... 이런, 지노, 왜 그렇게 창백해졌나?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "너... 혹시 종교재판관을 봤어? 그 사람이...";
			link.l1 = "걱정 마, 지노. 네 놈을 그에게 넘길 생각은 없어. 그게 그의 명령이었고, 널 찾아서 데려오라 했지만 말이야. 나는 이차족 인디언에 관한 정보를 좀 얻어야 해. 타야살과 그 보물, 그리고 그곳을 둘러싼 '악'에 대해 말해 봐.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "잘 알고 계시는군요. 이건 빈첸토 신부가 말해 주었소?";
			link.l1 = "그에게서도 정보를 얻었고, 다른 사람들에게서도 들었소. 하지만 자네 이야기도 듣고 싶군. 자네는 한때 그의 비서였으니 심문 기록을 남겼을 터, 맞지?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "그가 그 불쌍한 인디언에게 무슨 짓을 했는지 상상도 못할 거야!.. 그 심문을 떠올릴 때마다 온몸에 소름이 돋아.";
			link.l1 = "그래도 이야기해 보자. 그 인디언은 누구였지? 어떻게 빈첸토 신부 손에 들어가게 된 거야?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "그는 타야살에서 출발해 쿠쿨칸의 가면, 즉 고대 마야 신 쿠쿨칸의 유물을 찾으러 온 이차족 인디언들 중 한 명이었소. 그 인디언들은 스코틀랜드 출신 보물 사냥꾼 아치볼드 칼훈이 이끄는 백인 모험가 무리와 마주쳤지. 인디언 중 살아남은 이는 단 한 명, 그의 이름은 크사틀 챠였소. 그는 흥미로운 물건 세 개를 지니고 있었는데, 그 이야기는 나중에 해 주겠소.  
칼훈은 포로에게 보물에 대해 말하라고 강요했으나, 그는 끝내 입을 열지 않았소. 그래서 스코틀랜드인은 그를 산티아고로 데려가 빈첸토 신부에게 넘겼고, 그 대가로 1년간 스페인 도시들을 방문할 수 있는 허가를 받았지. 칼훈은 그 종교재판관이 온갖 현지의 신비와 전설에 관심이 많다는 걸 알고 있었소. 빈첸토 신부는 인디언의 입을 열게 했고, 그는 엄청나게 많은 이야기를 쏟아냈소. 우리가 알아낸 정보는 종교재판관마저 충격에 빠뜨렸지.";
			link.l1 = "정말인가? 대체 어떤 일이 그분을 떨게 만들었지?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "모든 것을 순서대로 말씀드리겠소. 유카탄 정글 깊은 곳에 테야살이라는 고대 마야 도시가 있소. 그곳에는 마야의 후손인 이차족이 살고 있지. 그들은 조상들의 규칙과 전통을 지키며 살아가려 애쓰고 있소. 물론, 그들은 현대 세계의 상황, 즉 백인들의 지배를 달가워하지 않소.\n그들은 옛 영광의 시절을 꿈꾸고 있지. 그리고 여기서부터가 가장 흥미로운 부분이오. 백인 모험가 무리가 우연히 테야살 근처까지 접근했다가 이차족 최고 추장의 딸을 납치하는 일이 있었소. 거의 25년 전의 일이오.\n이 사건이 마지막 인내의 한계였고, 추장 카넥은 분노했지. 그는 마야의 가장 위험하고 비밀스러운 의식, 즉 인디언 신을 불러 백인 정복자들의 모든 후손을 지워버리려는 의식을 치르기로 결심했소...";
			link.l1 = "흠... 저게 분명히 빈첸토 신부가 말한 악마겠지. 그런데 이 인디언 신이 백인 식민자들을 어떻게 상대한단 말인가? 용으로 나타나서 전부 불태워버리기라도 한단 말인가?\n";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "오, "+pchar.name+", 이런 불괴물 이야기는 늙은 할멈들에게나 맡기라고! 사실 완전히 틀린 말은 아니지만, 우리의 경우는 훨씬 더 어렵고 심각해. 대홍수조차도 유럽이 신세계로 팽창하는 걸 막을 수 없을 거야. 한 명이 죽으면 열 명이 더 올 테니까. 카넥은 유럽 식민화의 가능성 자체를 없애야 했지.";
			link.l1 = "이미 일어난 일이오.";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "옳은 방향으로 생각하고 있소, 선장... 카넥의 의식 목적은 상위 존재를 소환하는 것뿐만 아니라, 시공간의 균열을 만드는 데에도 있었소.";
			link.l1 = "뭐?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "고대 마야인들은 놀라운 지식을 가지고 있었소, 선장. 카넥이 시간을 조종할 수 있는 의식에 대한 설명을 찾아냈소.";
			link.l1 = "우와! 대단한데!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "들어봐. 의식의 궁극적인 목적은 과거를 바꿔 백인이 신세계에 도착하는 것을 불가능하게 만드는 거야. 그런 일을 하려면, 그들은 권위와 권력, 그리고 사람들의 운명을 바꿀 수 있는 능력을 가진 누군가를 과거로 보낼 거야. 하지만 무엇보다 중요한 건, 그 사람이 현대의 지식을 갖추고 있어야 한다는 점이지.\n생각해 봐. "+pchar.name+", 만약 콜럼버스의 캐러벨이 현대식 대포로 무장한 인디언 함대의 프리깃과 갤리온을 만났다면 어떻게 되었을까? 그리고 백인 병사들의 화승총에 맞선 것이 활과 창이 아니라 박격포와 머스킷이었다면 어땠을까?";
			link.l1 = "아메리카 대륙은 아예 발견되지도 않았을 것 같군....";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "정확히 그렇지! 어쩌면 어떤 인디언 '콜럼버스'가 유럽을 발견했을지도 모르지...";
			link.l1 = "흥미롭군, 그런데 카넥은 과거로 누구를 보낼 셈이지? 자기 벌거벗은 전사들 중 한 명이라도? 자기 조상들에게 뭘 가르칠 수 있을지 의심스럽군...";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "웃지 마시오, 선장. 카넥은 마야 사원에서 그저 그들의 글만 읽으며 세월을 보낸 게 아니오. 인디언 신이 인간의 모습으로 과거에 보내져야만 하오...";
			link.l1 = "지노, 무슨 헛소리를 하는 거야? 너 혹시....";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "우리 주님의 아들, 예수 그리스도조차도 인간의 모습으로 이 땅에 오셔서 성모 마리아라는 인간 여성에게서 태어나셨지...";
			link.l1 = "이런, 지노... 진심이야?";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "그래, 맞아. 크사틀 차가 아주 설득력 있었지...";
			link.l1 = "그런 '고귀한' 임무에 카넥이 선택한 신은 누구였지?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "그 의식은 오직 한 명의 고위 존재만을 소환하기 위한 것이었소. 깃털 달린 뱀, 케찰코아틀, 쿠쿨칸...\n";
			if (CheckAttribute(pchar, "questTemp.Dolly")) link.l1 = "쿠쿨칸?! 나는 이미 그 조각상에 깃든 그의 '영혼'을 만나는 무모함을 저질렀지. 이제야 알겠군... 계속 말해!";
			else link.l1 = "흠. 흥미롭군. 그 이름은 이미 빈첸토 신부에게서 들었소... 계속하시오!";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "카넥은 쿠쿨칸의 고대 유물, 즉 쿠쿨칸의 가면을 이미 이차족이 소유하고 있었기에 쿠쿨칸을 소환하기로 결정했다. 가면을 가진 자만이 포털을 통과할 수 있으며, 오직 그 자만이 고대 마야인들에게 살아있는 신으로 받아들여진다.\n사제가 의식을 집전하여 쿠쿨칸이 인간의 몸에 현신하도록 소환했다. 또한 그는 시간의 균열을 만들어 미래에서 무작위로 몇몇 사람들을 우리 시대로 끌어들였다.\n이렇게 사람들을 불러온 목적은 쿠쿨칸의 현신에게 우리 시대뿐 아니라 미래의 지식까지 부여하기 위함이었다. 그러나 무언가 잘못되어, 그 사람들은 모두 테야살이 아닌 다른 곳에 도착했다. 나는 그들 중 누구도 만난 적이 없다.\n군도 곳곳에 여러 개의 포털이 만들어졌는데, 이는 미래의 지식을 지닌 자들과 이차의 요원들을 이 지역과 테야살로 이동시키기 위한 것이었다. 하지만 이 포털들은 제 역할을 하지 못했고, 지난 25년간 테야살로 온 자는 아무도 없었다...";
			if (CheckAttribute(pchar, "questTemp.Dolly"))
			{
				link.l1 = "그래... 이 포탈들은 잡힌 사람들만 서로에게 보내 주니까. 믿기지 않는군!";
				link.l1.go = "guardoftruth_15a";
			}
			else
			{
				link.l1 = "흥미롭군...";
				link.l1.go = "guardoftruth_16";
			}
		break;
		
		case "guardoftruth_15a":
			dialog.text = "그 포탈들 봤어? 말해 봐!";
			link.l1 = "나중에 하자, 지노... 지금은 네 이야기가 더 궁금하거든. 계속해!";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "내가 당신에게 말한 모든 것을 빈첸토 신부도 이미 알고 있소. 그래서 그분도 걱정하고 계시지. 쿠쿨칸이 인간의 모습으로 현신하여, 가면과 그동안 모은 모든 지식을 가지고 포탈에 도달한다면... 세상의 끝이오. 종말이오.\n과거가 바뀌면 미래도 바뀌오. 우리의 현실이 변하고, 사라지고, 녹아 없어질 것이오. 당신과 나는 태어나지 않을 수도 있소. 아니면 전혀 다른 존재가 될 수도 있지. 쿠쿨칸이 과거에 도달하는 순간, 우리는 존재를 멈추게 될 것이오.";
			link.l1 = "그럼 쿠쿨칸의 화신은 누구지?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "누가 알겠나. 의식이 치러진 25년 전에 태어난 누구라도 될 수 있지. 예를 들어, 너 말이야... 농담이야. 하지만 아직 희망은 있어. 첫째, 쿠쿨칸의 화신도 결국 평범한 인간일 뿐이니, 익사할 수도 있고, 칼에 찔릴 수도, 총에 맞을 수도, 열병으로 죽을 수도 있지. 그런 일이 일어난다면 세상의 종말 따위는 오지 않을 거야.\n둘째, 가면 없이는 과거로 갈 수 없어. 카넥이 그걸 아주 잘 숨겨놨지—어쩌면 너무 잘 숨긴 것 같기도 하고. 어쩌면 쿠쿨칸의 화신조차도 그걸 찾지 못할 수도 있어.";
			link.l1 = "더 말해 보시오.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "의식이 끝난 후 얼마 지나지 않아, 스페인 콘키스타도르 무리가 거의 타야살에 도달해 보물창고까지 접근할 뻔했소. 이차족은 그들 모두를 죽였으나, 단 한 명—키가 일곱 자나 되는 거대한 사내만은 예외였지. 카넥은 아무 이방인이라도 가면을 훔칠 수 있다는 사실에 불안해져 유물을 지키기로 결심했소. 그는 고대 마야의 지식을 이용해 자신만의 의식을 고안했지. 백인의 힘이 깃들었다고 믿은 세 가지 물건—코르테스가 직접 썼던 단검, 나침반, 그리고 포로로 잡힌 스페인 거인의 등에서 단검으로 도려낸 피부 조각을 준비했소. 그 사내는 쿠쿨칸의 제단에서 제물로 바쳐졌지. 의식에는 이 세 가지 물건이 쓰였소. \n그리고 이 의식으로 인해 새로운 섬이 탄생했네. 유카탄에서 멀지 않은 망망대해에 말이오. 그 위치는 아무도 모르지만, 가면은 그곳에 숨겨져 있지. 그것을 찾으려면 단검, 나침반, 그리고 피부 조각을 사용해야 하오. 게다가, 보물창고의 모든 물건에는 저주가 걸려 있어서, 그 어떤 것도 군도 밖으로 가지고 나갈 수 없소. \n만약 시도한다면, 폭풍이 배를 가면이 숨겨진 섬의 암초로 몰아넣게 되지. 그 섬의 이름은 크소체아템이라 하오. 영리하지 않은가?";
			link.l1 = "아마 너무 똑똑한 거겠지. 그건 부정할 수 없군. 하지만 대체 어떻게 크살트 차가 그렇게 잘 알고 있었던 거지? 카넥이 그런 정보를 평범한 전사들과 나누고 있었을 리는 없잖아...";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "문제는, 지금의 이차 추장인 우라칸, 카넥의 아들이 이 전사에게 모든 것을 말했다는 거야.\n우라칸은 크살트 차와 전사들을 이끌고 비밀의 섬과 쿠쿨칸의 가면을 찾으라고 보냈지.\n그 일을 위해 진실의 수호자를 주었어. 그건 세 가지 물건, 즉 단검, 나침반, 인간 가죽으로 만든 지도를 합쳐 부르는 이름이야.";
			link.l1 = "지도 말인가? 그리고 우라칸이 왜 가면이 필요했지? 설마 그가 직접 과거를 바꿀 생각을 한 건가?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "피부에는 군도의 윤곽이 새겨져 있어서, 사람들은 그것을 지도라 부르지. 우라칸이 가면을 원했던 이유는 아주 단순했어 – 그는 현존하는 현실을 파괴하거나, 고대인들의 영광을 위해 자기 목숨과 자기 민족의 목숨을 희생하고 싶지 않았던 거야.\n그래서 그는 어떤 대가를 치르더라도 가면을 파괴하려 했지. 하지만 크살트 차는 칼훈에게 붙잡혔고... 뭐, 그 다음 이야기는 알겠지. 그는 결코 크소체아템에 도달하지 못했어.";
			link.l1 = "그러니까 가면을 찾아서 파괴하면 종말을 막을 수 있다는 말인가? 그럼 지금 그... 진리의 수호자는 어디에 있지?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "단검 '족장의 발톱'과 나침반 '길의 화살'은 칼훈에게 남겨졌고, 가죽 지도 '두 얼굴의 지도'는 아직도 종교재판소 어딘가에 있다네.\n칼훈은 그걸 죄수의 입을 막는 농담거리로 썼지. 그 물건들이 무슨 용도인지 그는 전혀 몰랐어.";
			link.l1 = "뭐라고 했어? '족장의 발톱'이라고? 젠장, 이 단검 지금 내 몸에 있잖아! 파데이가 우리 형한테 진 빚 대신 나한테 준 거야! 한번 봐봐!\n";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			dialog.text = "믿기지 않아... 정말이야. 기억나.";
			link.l1 = "지노, 말해 봐. 비첸토 신부가 네 이야기 중에서 정확히 무엇을 알고 있지?";
			link.l1.go = "guardoftruth_23";
		break;
		
		case "guardoftruth_23":
			dialog.text = "진실의 수호자에 관한 정보와 쿠쿨칸의 가면이 숨겨진 비밀 섬의 위치를 드러내는 방법만 빼고는 전부 말했지. 그 이야기는 우리가 단둘이 있을 때 크살트 차가 내게 해줬어. 내가 그의 고통을 끝내주려고 독약을 건네주기 직전이었지. 그는 미소를 지으며 죽었어.\n내가 그런 일을 저지른 뒤에 산티아고에 머무를 수는 없었지. 나는 심각하게 의심했어. 내가 종교재판관에게 중요한, 그리고 위험한 증인이 되어버렸다고 말이야. 빈첸토 신부는 무슨 수를 써서라도 원하는 걸 얻는 사람이야. 크살트 차는 그에게 타야살의 보물창고에 대해 말해줬지.";
			link.l1 = "이 보물들은 이미 미겔 디초소라는 모험가가 찾아냈소. 그 사람에 대해 들어본 적 있소?";
			link.l1.go = "guardoftruth_24";
		break;
		
		case "guardoftruth_24":
			dialog.text = "아니. 그럼 지금 그는 어디에 있지, 그의 보물들과 함께?";
			link.l1 = "나 자신을 알고 싶소. 그래서 당신을 찾아왔소, 나는 그 인디언 금을 찾고 있소. 디초소가 보물을 유럽으로 가져가서 사라졌소.";
			link.l1.go = "guardoftruth_25";
		break;
		
		case "guardoftruth_25":
			dialog.text = "보물과 디초소 본인이 어디 있는지 내가 알려주겠다.";
			link.l1 = "지노, 넌 날 놀라게 하는군. 그걸 어떻게 알았지?!";
			link.l1.go = "guardoftruth_26";
		break;
		
		case "guardoftruth_26":
			dialog.text = "내 이야기를 들으면 스스로 알 수 있을 것이오, 선장. 타야살의 보물들은 저주받았소 – 그 어떤 물건도 이 군도에서 가지고 나갈 수 없소. 어떤 배라도...\n";
			link.l1 = "... 폭풍에 휘말려 쿠쿨칸의 가면이 숨겨진 섬으로 내던져질 거야! 나는 눈이 멀었지만, 이제야 보이기 시작했어. 이제 크소체아템과 보물, 그리고 그 가면을 찾기에 충분한 정보를 알게 된 것 같아!";
			link.l1.go = "guardoftruth_27";
		break;
		
		case "guardoftruth_27":
			dialog.text = "세상을 구하고 싶소, 선장?";
			link.l1 = "나는 내 방탕한 형을 찾고 싶어... 지노, 진리의 수호자가 섬의 위치를 밝히게 하려면 어떻게 해야 하지? 네가 방법을 안다고 했잖아!";
			link.l1.go = "guardoftruth_28";
		break;
		
		case "guardoftruth_28":
			dialog.text = "방법은 알지만, 세부 사항은 몰라. 수호자의 모든 부품을 다 모으기 전에는 도와줄 수 없어.";
			link.l1 = "흠. 단도는 이미 우리 손에 있지. 이제 나침반과 지도만 남았군. 나침반은 칼훈이 가지고 있고, 지도는 빈첸토 신부가 가지고 있어...";
			link.l1.go = "guardoftruth_29";
		break;
		
		case "guardoftruth_29":
			dialog.text = "이제 종교재판관에게 돌아갈 생각이오? 그런데 어떻게 보고할 셈이오...";
			link.l1 = "내가 빈첸토 신부에게 네가 죽었다고 설득해야 해, 지노. 그래야만 그분이 수색을 멈출 거야. 내가 나타났을 때 갑자기 뇌졸중이 왔다고 하자. 네가 죽었다는 증거로 쓸 수 있는 물건을 하나 줘야 해.";
			link.l1.go = "guardoftruth_30";
		break;
		
		case "guardoftruth_30":
			dialog.text = "빈첸토는 심장마비 이야기는 믿지 않겠지만, 내가 아몬드 냄새가 나는 독을 마시고 자살했다고 말하면 그건 믿을 거야. 내 연감도 그에게 주게, 내가 절대 그걸 손에서 놓지 않는다는 걸 그는 아니까.";
			link.l1 = "좋아. 내가 종교재판관과의 인맥이 꼭 필요하거든. 그자가 우리 일에 대해 많이 알고 있을 테니까.";
			link.l1.go = "guardoftruth_31";
		break;
		
		case "guardoftruth_31":
			dialog.text = "비첸토 신부를 조심하게. 그 자는 호랑이만큼 위험하고, 자기만의 게임을 하지. 자네와 보물도, 명예도 나누지 않을 걸세.";
			link.l1 = "알겠소. 좋아, 지노, 네 연감이나 내게 넘기고, 인디언이 진실의 수호자에 대해 뭐라고 했는지 기억해 보도록 하시오. 내가 다 맞춰보고 싶으니. 나는 크소체아템을 찾아야 하오. 거기서 가면과 보물뿐만 아니라 내 사랑하는 형제도 찾게 될 거라 확신하오.";
			link.l1.go = "guardoftruth_32";
		break;
		
		case "guardoftruth_32":
			dialog.text = "가져가시오. 행운을 빕니다, 선장!";
			link.l1 = "나는 작별 인사를 하는 게 아니야, 지노...";
			link.l1.go = "guardoftruth_33";
		break;
		
		case "guardoftruth_33":
			DialogExit();
			Log_Info("You have received an almanac");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "Almanac");
			ChangeItemDescribe("Almanac", "itmdescr_jinobook");
			pchar.questTemp.Guardoftruth = "twoitems";
			AddQuestRecord("Guardoftruth", "37");
		break;
		
		case "guardoftruth_34":
			dialog.text = "힘들었습니까, 선장님?";
			link.l1 = "그 얘기는 하지 말자... 이 물건들을 얻으려고 너무 많은 사람들이 죽었어. 정말 너무 많았지. 신비한 크소체아템을 찾으려는 게 나만이 아닌 것 같군. ";
			link.l1.go = "guardoftruth_35";
		break;
		
		case "guardoftruth_35":
			dialog.text = "상상이 가는군... 그런데, 비첸토 신부님은 어떻게 지내시나? 그분과는 자주 연락하고 있나?";
			link.l1 = "지금까지는 그랬지만, 이제 더 이상 그럴 필요가 없을 것 같아. 나는 진리의 수호자 모든 부품을 가지고 있으니, 그 말은 곧 크소체아템의 위치를 알 수 있는 열쇠를 쥐고 있다는 뜻이지. 그런데 왠지, 이 성공을 각하께 보고하고 싶은 마음이 들지 않는군.";
			link.l1.go = "guardoftruth_36";
		break;
		
		case "guardoftruth_36":
			dialog.text = "조심해, "+pchar.name+". 빈첸토 신부는 수백 개의 눈과 손을 가졌지. 아주 긴 손을...";
			link.l1 = "지난 몇 달 동안 정말 많은 일을 겪었지. 이제 와서야 나는 빈첸토 신부도, 그의 눈과 손도 전혀 두렵지 않아. 뭐, 상관없지. 이제 우리도 수호자의 구성품을 이용해서 크소체아템을 찾아야 할 때야. 그 방법을 알고 있나? ";
			link.l1.go = "guardoftruth_37";
		break;
		
		case "guardoftruth_37":
			dialog.text = "꼭 그렇진 않아. 크사틀 차는 꽤 모호하게 말했지. 내 생각엔 그 인디언도 수호자를 어떻게 작동시키는지 제대로 몰랐던 것 같아. 부품들은 나한테 맡겨. 내가 한번 알아볼 테니. 이틀 뒤에 나를 찾아오면, 어쩌면 이 수수께끼를 풀어놓았을지도 몰라.";
			link.l1 = "좋아, 지노. 자네를 믿겠네. 자, 이것들을 가져가게.";
			link.l1.go = "guardoftruth_38";
		break;
		
		case "guardoftruth_38":
			dialog.text = "나와 함께라면 그들이 안전하게, 다치지 않고 지낼 수 있다는 것만은 확신하시오.";
			link.l1 = "그럴 줄 알았네. 자, 당분간은 귀찮게 하지 않겠네, Gino. 연구 잘 하게!";
			link.l1.go = "guardoftruth_39";
		break;
		
		case "guardoftruth_39":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			RemoveItems(pchar, "knife_01", 1);
			RemoveItems(pchar, "skinmap", 1);
			RemoveItems(pchar, "arrowway", 1);
			pchar.questTemp.Guardoftruth = "end";
			SetFunctionTimerCondition("Ksochitam_StartSearchIsland", 0, 0, 2, false);
			CloseQuestHeader("Guardoftruth");
			AddQuestRecord("Ksochitam", "1");
		break;
		
		case "ksochitam":
			dialog.text = "부분적으로는 그래. 그러니까, 뭔가 있긴 한데 이걸 어떻게 제대로 완성해야 할지 모르겠어. 같이 이 퍼즐을 풀어보자.";
			link.l1 = "해보자! 아이디어를 내봐.";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "크사틀 차가 이렇게 말했다고 하더군: '족장의 발톱이 지도를 드러나게 할 것이고, 길의 화살이 출현의 방향을 보여줄 것이다.'\n";
			link.l1 = "그래서 뭘 해냈지?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "지도가 스스로 '드러나게' 하는 방법을 알아냈어. 두 모습의 지도, 한번 살펴봤나?";
			link.l1 = "흠. 그리고 뭔가 이상한 점은 없었나? 군도의 어딘가 수상한 윤곽이라든가...";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			GiveItem2Character(pchar, "skinmap");
			dialog.text = "가져가서 다시 한 번 살펴봐. 주의 깊게 봐.";
			link.l1 = "그래, 그렇게 하자고 고집한다면 그렇게 하지.";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_1";
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "ksochitam_wait":
			dialog.text = "지도를 안 봤군, "+pchar.name+"...";
			link.l1 = "그래, 그래, 지금 할게...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_wait";
		break;
		
		case "ksochitam_5":
			dialog.text = "";
			link.l1 = "봤어. 새로 본 건 없었어. 그냥 섬이랑 본토의 희미한 윤곽만 보였지. 거기서 내가 뭘 더 봐야 하지?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "잠깐만. 이제 이 지도가 모습을 드러내게 해야 해. 단도를 들어서 그 날로 지도를 살짝 건드려 봐. 힘주지 말고, 손상되면 안 되니까. 단도를 들어. 그리고 잘 지켜봐!";
			link.l1 = "흥미로운데! 어디 한번 볼까...";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			DialogExit();
			GiveItem2Character(pchar, "knife_01");
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_2";
			sld = ItemsFromID("skinmap");
			sld.mark = 2;
		break;
		
		case "ksochitam_8":
			dialog.text = "자, 이제 뭐가 달라진 게 보이나?";
			link.l1 = "그래. 단검으로 지도를 건드리면 해골 표시 두 개가 나타나는데, 항상 같은 자리에 있지...";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "똑같은 두 곳에서, "+pchar.name+"! 그래서 그 지도가 '두 모습의 지도'라고 불렸던 것이오!";
			link.l1 = "그게 무슨 뜻이지?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "많이 그런 것 같군... 하지만 다음엔 더 많은 수수께끼가 기다리고 있어. 이 해골들이 바로 크살트 차가 말하던 유령들이겠지. 그렇다면 나침반이 저 해골들로부터 크소체아템으로 가는 올바른 방향을 가리키는 게 분명해. 혹시 그 나침반을 본 적 있나,\n "+pchar.name+"?";
			link.l1 = "예. 겉보기에는 평범한 해군 나침반이지만, 이상하게도 바늘이 여러 방향으로 움찔거리거나 갑자기 미친 듯이 빙글빙글 돌기 시작하오.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "나는 나침반을 해골들 위에 올려두면 바늘이 멈추고 지도에 뚜렷한 방향을 보여줄 거라고 생각했어. 그렇게 하려고, 한 해골 위에 올려놓았다가 다른 해골 위에도 올려놓았지, 그동안 단검으로 지도를 만지면서 말이야.";
			link.l1 = "그래서?";
			link.l1.go = "ksochitam_12";
		break;
		 
		case "ksochitam_12":
			dialog.text = "헛수고였다. 나침반은 전혀 반응을 보이지 않았다. 바늘은 여전히 미친 듯이 빙글빙글 돈다. 뭔가 내가 잘못하고 있는 것 같다. 아니면 카살 차의 말을 내가 잘못 이해한 걸지도 모르겠다.";
			link.l1 = "그러니까 단검이랑 지도는 작동하는데, 나침반은 안 된다는 거야?";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			dialog.text = "길의 화살은 분명 작동할 수 있을 거야, 다만 아직 우리가 어떻게 작동시키는지 모를 뿐이지. "+pchar.name+", 자네가 이 군도의 지리를 나보다 더 잘 알지... 말해 보게, 두 얼굴의 지도가 가리키는 곳이 어디인가?";
			link.l1 = "잠깐만! (한번 볼게)... 자, 자... 왼쪽에 보이는 땅이 서메인이고, 오른쪽은 도미니카 섬처럼 보이네. 대충 그런 것 같아.";
			link.l1.go = "ksochitam_14";
		break;
		
		case "ksochitam_14":
			dialog.text = "그리고 말해 보시오: 그곳들에... 특별히 주목할 만한 것이 있소?";
			link.l1 = "무슨 뜻이오?";
			link.l1.go = "ksochitam_15";
		break;
		
		case "ksochitam_15":
			dialog.text = "나도 잘 모르겠어... 음, 뭔가 특별한 거라도?";
			link.l1 = "지노, 수수께끼처럼 말하지 마라. 간단히 설명해라.";
			link.l1.go = "ksochitam_16";
		break;
		
		case "ksochitam_16":
			dialog.text = "나는 이 해골들이 실제 장소를 가리키고 있다고밖에 생각할 수 없군. 길잡이 화살은 지도 그림 위에 꽂아두면 작동하지 않아. 아마도 지도가 밝혀낸 실제 지형 근처에서는 작동할지도 모르지?";
			link.l1 = "지노, 너 천재구나! 웨스턴 메인, 도미니카라고? 해골 표시가 너무 커서 정확한 위치를 알 수가 없어.";
			link.l1.go = "ksochitam_17";
		break;
		
		case "ksochitam_17":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = ""+pchar.name+", 이렇게 하세. 군도 지도를 가져와서 '두 모습' 지도와 합치고, 그 모습들이 나타나는 곳에 십자가 표시를 하게. 어쩌면 그럼 뭔가 추측할 수 있지 않겠나?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "이 군도에 대한 오래된 지도가 있소.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "이 군도의 훌륭한 지도가 내게 있소.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "이 군도에 대한 훌륭한 지도가 내게 있소.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "좋소. 내가 지도를 가져오면 계속하겠소...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_17_1":
			dialog.text = "아, 좀 그러지 마, "+pchar.name+"! 이 콜럼버스 시대 양피지 지도도 가죽 지도랑 별반 다를 게 없군. 세상에 이딴 쓰레기보다 나은 게 분명히 있을 텐데. 다른 지도를 가져와라, 더 최근 걸로!";
			link.l1 = "좋아...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_2":
			dialog.text = "훌륭하오! 이제 그 위에 출몰 위치를 표시하시오. 그러면 추측을 세우기가 더 쉬워질 것이오.";
			link.l1 = "잠깐만, Gino!";
			link.l1.go = "ksochitam_18";
		break;
		
		case "ksochitam_17_3":
			dialog.text = "이렇게 훌륭한 지도를 우리 낙서로 망칠 순 없지. 너도 직접 필요할 거야, "+pchar.name+". 좀 더 소박한 지도를 하나 더 가져오라!";
			link.l1 = "좋아...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_map_wait":
			dialog.text = "군도 지도를 가져왔소, "+pchar.name+"?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "이 군도에 대한 오래된 지도가 있소.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "이 군도 지도의 훌륭한 사본이 내게 있소.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "이 군도에 대한 훌륭한 지도가 여기 있소.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "아직 아니지만, 이미 주문해 두었소. 곧 받을 테니 계속하겠소...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_18":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_19";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto1", "Ksochitam_SitTable", -1);
		break;
		
		case "ksochitam_19":
			dialog.text = "";
			link.l1 = "끝났어... 표시를 해두긴 했지만, 정보가 아직 정확하지 않아. 첫 번째 위치는 블루웰드 북서쪽 어딘가야. 두 번째는 도미니카 섬 중앙이야.";
			link.l1.go = "ksochitam_20";
		break;
		
		case "ksochitam_20":
			dialog.text = "생각나는 거 있어?";
			link.l1 = "아니. 하지만 나는 우리가 거기로 Way의 화살호를 가져가서 그 반응을 관찰해야 한다고 생각해. 물론, 건초 더미에서 바늘 찾기나 다름없지만, 어차피 더 나은 방법도 없잖아.";
			link.l1.go = "ksochitam_21";
		break;
		
		case "ksochitam_21":
			dialog.text = "당신 말에 동의합니다, "+pchar.name+". 나랑 같이 항해하게 해줄래?";
			link.l1 = "그대의 추측을 시험해보고 싶은가? 내 배 갑판에 그대를 모실 수 있다면 영광이겠소, Gino. 짐을 싸시오!";
			link.l1.go = "ksochitam_22";
		break;
		
		case "ksochitam_22":
			dialog.text = "오래 걸리지 않을 거야. 몇 시간 안에 준비할게. 자, 이 길잡이의 화살을 가져.";
			link.l1 = "배에 온 걸 환영한다!";
			link.l1.go = "ksochitam_23";
		break;
		
		case "ksochitam_23":
			LAi_SetOwnerType(npchar);
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_24";
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetPlayerType(pchar);
			GiveItem2Character(pchar, "arrowway");
			pchar.questTemp.Ksochitam = "seekway";
			sld = ItemsFromID("skinmap");
			sld.mark = 1;
			pchar.quest.Ksochitam_room.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Ksochitam_room.win_condition.l1.location = pchar.location;
			pchar.quest.Ksochitam_room.function = "Ksochitam_JinoPassenger";
			AddQuestRecord("Ksochitam", "2");
		break;
		
		case "ksochitam_24":
			dialog.text = "그래, 그래, "+pchar.name+", 준비하고 있소. 곧 준비될 것이오.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_24";
		break;
		
		case "ksochitam_25":
			dialog.text = "그래서 뭐, "+pchar.name+", 우리 수색에서 성과가 좀 있나?";
			link.l1 = "우리가 맞았어. 이거야. 인디언 우상은 그것의 한 형태야.";
			link.l1.go = "ksochitam_26";
		break;
		
		case "ksochitam_26":
			dialog.text = "오! 이건 분명히 사람을 테야살로 순간이동시킨다는 그 우상들 중 하나군! 내가 전에 얘기해줬던 거 기억하지? 자, 그럼 길의 화살표는 어디를 가리키고 있지?";
			link.l1 = "북서쪽을 가리키고 있네. 내가 지도에 방향을 표시해 두었어. 그려진 선이 카리브 해 전체를 거의 가로지르더군. Ksocheatem을 찾으려면 도미니카에서 또 다른 흔적을 찾아야 하네.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_27":
			dialog.text = "나는 우리가 그곳에서 또 다른 우상을 찾게 될 거라고 확신하오... 내 가설에 동의하시오, "+pchar.name+"?";
			link.l1 = "그래, Gino. 이제 시간 낭비하지 말고 바로 수색을 시작하자.";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_28":
			DialogExit();
			locations[FindLocation(pchar.location)].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
		break;
		
		case "ksochitam_29":
			dialog.text = "그래서 뭐, "+pchar.name+", 흥미로운 걸 찾았소?";
			link.l1 = "우리가 맞았어. 이거야. 인디언 우상은 그것의 한 형태야.";
			link.l1.go = "ksochitam_30";
		break;
		
		case "ksochitam_30":
			dialog.text = "오! 이건 분명히 사람을 타야살로 순간이동시킨다는 그 우상들 중 하나로군! 내가 전에 얘기했던 거 기억하지? 자, 그럼 길의 화살표는 어디를 가리키고 있지?";
			link.l1 = "북서쪽이오. 지도에 방향을 표시해 두었소. 그려진 선이 카리브 해 전체를 거의 가로지르지만,\nKsocheatem을 찾으려면 본토에 다른 상륙 지점을 찾아야 하오.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_31":
			dialog.text = "그래서 뭐, "+pchar.name+", 두 번째 우상을 찾았나?";
			link.l1 = "그래. 나는 길잡이 화살이 가리킨 방향을 그려 두었어. 이제 크소체아템의 위치를 알게 되었지; 정확한 지점은 아니지만, 어디서 찾아야 할지는 알잖아! 선들이 교차하는 그 지역 전체를 샅샅이 뒤져서, 반드시 그 빌어먹을 섬을 찾아낼 거야!";
			link.l1.go = "ksochitam_32";
		break;
		
		case "ksochitam_32":
			dialog.text = "그렇게 열정적인 목소리를 들으니 기쁘군. 하지만 다가오는 원정에 철저히 대비해야 하오; 그곳에서 무엇을 마주하게 될지 알 수 없으니. 따뜻한 환영을 받을 것 같지는 않소...";
			link.l1 = "무엇인가 구체적으로 걱정되는 게 있소, 아니면 그냥 우려를 표하는 것이오?";
			link.l1.go = "ksochitam_33";
		break;
		
		case "ksochitam_33":
			dialog.text = "생각해 봐, "+pchar.name+".. 크소체아템은 카넥이 행한 마야의 마법으로 만들어진 것이오. 자연적으로 생긴 것이 아니며, 사악하고 파괴적인 힘을 지녔지. 그곳에 무엇이 기다리고 있을지는 아무도 모르오; 나는 그곳에서 햇살이나 평온한 바다, 창녀들, 잔잔한 바람 따위는 기대하지 않소.";
			link.l1 = "좋아, 지노. 네 말을 고려해서 원정 준비를 하겠네. 내 배를 준비하고, 물약과 탄약도 챙기도록 하지...";
			link.l1.go = "ksochitam_34";
		break;
		
		case "ksochitam_34":
			dialog.text = "매우 현명한 결정이오. 자, 이제 배로 돌아갈까?";
			link.l1 = "그래! 가자!";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_35":
			dialog.text = "도착했다, "+pchar.name+"! 으, 바람이 으르렁거린다!";
			link.l1 = "그래, 지노, 네 말이 맞아. 우리를 반겨줄 햇살도 없군... 창녀들도 안 보이고. 사실, 여기서 우리를 뭘 기다리고 있는지 전혀 모르겠어.";
			link.l1.go = "ksochitam_36";
		break;
		
		case "ksochitam_36":
			dialog.text = "글쎄, 선장! 이런 나쁜 곳에 상륙하다니! 사방이 바위랑 절벽뿐이군! 여기서 섬 안쪽으로는 어떻게 들어갈 생각이오?";
			link.l1 = "이 빌어먹을 폭풍 때문에 이 섬에 상륙할 만한 다른 만은 못 봤어! 뭐, 아무것도 없는 것보단 이게 낫지. 이런 바위들 사이로 길쯤이야 내가 알아서 찾을 수 있어, 더한 것도 겪어봤으니까. 당황하지 마, 친구!";
			link.l1.go = "ksochitam_37";
		break;
		
		case "ksochitam_37":
			dialog.text = "이 섬, 마음에 안 들어. "+pchar.name+"! 으스스하군. 그리고 이 폭풍은 분명히 섬에 달라붙어 있는 것 같아. 이곳은 망했어, 그건 확실해!";
			link.l1 = "나도 이곳이 별로 마음에 들지 않아, Gino! 하지만 이 섬이 실제로 존재한다는 건 쿠쿨칸의 이야기가 사실이라는 뜻이야. 그가 가면을 가지고 타야살에 도착한다면 우리 모두 위험에 처하게 될 거야...\n";
			link.l1.go = "ksochitam_38";
		break;
		
		case "ksochitam_38":
			dialog.text = "가면을 꼭 찾아야 해요, 선장님! 이건 세상의 모든 보물보다 더 중요해요! 분명 이 근처 어딘가에 있을 거예요! 우리가 가면을 손에 넣으면 쿠쿨칸의 계획을 무너뜨리고, 그가 과거를 바꾸지 못하게 막을 수 있어요!";
			link.l1 = "그 가면이 어떻게 생겼는지, 알고 있소?";
			link.l1.go = "ksochitam_39";
		break;
		
		case "ksochitam_39":
			dialog.text = "전혀 모르겠어! 하지만 보면 알 거야. 고대 인디언 유물이라 다른 것과 헷갈릴 수가 없어!";
			link.l1 = "알겠어. 내가 눈을 부릅뜨고 있을게! 좋아, 지노, 배로 돌아가! 섬을 돌아다닐 필요 없어, 네 목숨이 너무 소중하니까!";
			link.l1.go = "ksochitam_40";
		break;
		
		case "ksochitam_40":
			dialog.text = "거짓말하지 않겠소, 선장님. 나는 싸움을 잘 못하고 이곳이 영 불편하오. 조언 하나 해도 되겠소? 가디언의 모든 부품은 이 섬의 마법과 연결되어 있소. 크살트 차가 단검이 이곳 주민들에게 영향을 미친다고 했는데, 무슨 뜻인지는 모르겠소.   나는 배에 남겠소. 도움이 필요하면 그리로 오시오.";
			link.l1 = "좋아. 이제 내게 행운을 빌어 줘, 지노!";
			link.l1.go = "ksochitam_41";
		break;
		
		case "ksochitam_41":
			dialog.text = "행운을 빌어, "+pchar.name+"! 신의 가호와 보호가 함께하길!";
			link.l1 = "...";
			link.l1.go = "ksochitam_42";
		break;
		
		case "ksochitam_42":
			DialogExit();
			NextDiag.CurrentNode = "adversary";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "quest", "quest1", "Ksochitam_JinoStay", 10.0);
			AddQuestRecord("Ksochitam", "6");
		break;
		
		case "adversary":
			dialog.text = "어떻게 지내고 있나, "+pchar.name+" ? 조언이 필요해? ";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L1"))
			{
				link.l1 = "이 피투성이 섬에는 언데드가 들끓고 있어, 저 빌어먹을 해골놈들은 생각보다 끈질기게 버틴다. 어떻게 싸워야 할지 전혀 모르겠어.";
				link.l1.go = "adversary_1";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L2"))
			{
				link.l1 = "갈림길에서 왼쪽으로 가면 결국 동굴에 도착할 거야.\n하지만 다음엔 어디로 가야 하지?\n동굴이 막다른 길일까 봐 두렵군...";
				link.l1.go = "adversary_2";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L3"))
			{
				link.l1 = "나는 젖은 동굴 안으로 들어가는 길을 찾았어, 너도 그 안의 수중 구역으로 잠수할 수 있어. 하지만 거기서 나가는 출구는 못 찾겠어...";
				link.l1.go = "adversary_3";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L4"))
			{
				link.l1 = "갈림길에서 왼쪽으로 가면 동굴에 도착할 거야. 하지만 그 다음엔 어디로 가야 하지? 동굴이 막다른 길일까 봐 걱정이군...";
				link.l1.go = "adversary_4";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L5"))
			{
				link.l1 = "큰 동굴 안에 잠긴 구역으로 잠수할 수 있는 곳이 있소. 하지만 거기서는 나갈 길이 없는 듯하오...";
				link.l1.go = "adversary_5";
			}
			link.l10 = "지금까지는 다 괜찮아, Gino. 나 멀쩡해.";
			link.l10.go = "exit";
			NextDiag.TempNode = "adversary";
		break;
		
		case "adversary_1":
			dialog.text = "크사틀 차가 족장의 발톱을 언급했지. 그걸 해골들에게 써 보게. 인디언이 말하길, 이 단검에는 크소체아템의 주민들을 지배하는 힘이 담겨 있다고 했어.";
			link.l1 = "반드시 해보겠습니다!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L1");
		break;
		
		case "adversary_2":
			dialog.text = "그 동굴은 어떻게 생겼지?";
			link.l1 = "글쎄, 바위에 작은 동굴이 하나 있는데, 축축하고, 바닥에는 파도처럼 물이 출렁거려...";
			link.l1.go = "adversary_2_1";
		break;
		
		case "adversary_2_1":
			dialog.text = "물이 흔들린다면, 이 동굴이 바다와 연결되어 있다는 뜻이니 막다른 길일 리 없지. 통로를 찾아봐, 분명 있을 거다.";
			link.l1 = "가는 중이야...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L2");
		break;
		
		case "adversary_3":
			dialog.text = "만약 주 동굴에서 침수된 동굴로 통하는 길이 있고, 주 동굴의 물이 파도처럼 출렁인다면, 침수된 동굴에는 또 다른 통로가 있을 것이오. 더 철저히 찾아보되, 조심하지 않으면 익사할 수 있으니 주의하시오.";
			link.l1 = "나는 잠수할 거야...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L3");
		break;
		
		case "adversary_4":
			dialog.text = "그 동굴은 어떻게 생겼지?";
			link.l1 = "음, 꽤 넓고 동굴이 몇 개 있어. 축축하고, 고인 물이 있는 작은 구멍도 있지...";
			link.l1.go = "adversary_4_1";
		break;
		
		case "adversary_4_1":
			dialog.text = "물이 고요하다면, 그 동굴은 바다와 연결되어 있지 않아 막다른 길일 수도 있겠군.";
			link.l1 = "나도 같은 생각이었소. 나도 그곳을 오래 찾아봤지만, 입구는 하나뿐이고, 그게 곧 출구이기도 하오...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L4");
		break;
		
		case "adversary_5":
			dialog.text = "동굴 안에 아직도 물이 고여 있다면, 네 말이 맞을 수도 있겠군. 좀 더 찾아보게. 하지만 아무것도 못 찾아도 너무 실망하지 말게. 막다른 길일 가능성이 높으니.";
			link.l1 = "그렇군...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L5");
		break;
		
		case "adversary_6":
			dialog.text = ""+pchar.name+", 스페인 배들이 우리를 쫓아오고 있어! 지금은 얘기할 때가 아니야!";
			link.l1 = "그래, 물론이지...";
			link.l1.go = "exit";
			NextDiag.TempNode = "adversary_6";
		break;
		
		case "ksochitam_43":
			dialog.text = "당신의 행복한 눈빛을 보니 찾던 것을 이미 발견한 모양이군요.";
			link.l1 = "그래. 미겔 디초소의 보물과 쿠쿨칸의 가면 말이야. 이제 그의 화신은 결코 미래를 바꿀 수 없겠군!";
			link.l1.go = "ksochitam_44";
		break;
		
		case "ksochitam_44":
			dialog.text = "믿을 수 없군! 자네는 영웅이야, "+pchar.name+"...";
			link.l1 = "지노, 이걸로 쿠쿨칸을 막기에 충분하다고 확신하나?";
			link.l1.go = "ksochitam_45";
		break;
		
		case "ksochitam_45":
			dialog.text = "크사틀 차에 따르면 그렇다네. 그리고 그는 우라칸의 말을 인용했지. 그의 아버지 카넥이 이 모든 혼란을 시작한 장본인이었어. 의심 가는가?";
			link.l1 = "만에서 나를 맞이한 것은 과거에서 온 손님, 알론소 데 말도나도였다. 그는 카넥이 진리의 수호자를 탄생시키는 의식을 치를 때 타야살에 있었다. 그는 시공간의 균열에 휘말렸지만 살아남았지... 오늘까지는.";
			link.l1.go = "ksochitam_46";
		break;
		
		case "ksochitam_46":
			dialog.text = "";
			link.l1 = "그는 우리 세계를 영원히 지키려면 포탈 자체를 닫아야 한다고 했어. 그러기 위해서는 타야살에 있는 어떤 제단에서 가면을 파괴해야 해.";
			link.l1.go = "ksochitam_47";
		break;
		
		case "ksochitam_47":
			dialog.text = "그런데 타야살로 간다고? 이건 미친 짓이야! "+pchar.name+", 이제 네가 가면을 손에 넣었으니 쿠쿨칸의 화신도 아무것도 할 수 없지! 카넥 본인도 그걸 확신하고 있어! 그래서 우라칸이 크살 차를 크소체아템을 찾으러 보낸 거야 - 가면을 손에 넣고 파괴하려고.";
			link.l1 = "만약 이 우라칸이 타야살에서 가면을 파괴할 계획이었다면 어쩌겠소?";
			link.l1.go = "ksochitam_48";
		break;
		
		case "ksochitam_48":
			dialog.text = ""+pchar.name+", 지금까지 Tayasal에서 살아서 도망친 사람은 단 한 명, 미겔 디초소뿐이었소. 그리고 말도나도도 있지만, 그는 예외였지. 쿠쿨칸의 화신이 과거로 돌아간다 해도, 고대 마야인들에게 죽임을 당할 것이오!";
			link.l1 = "만약 그들이 그를 죽이지 않고 알아본다면 어떻게 하지?";
			link.l1.go = "ksochitam_49";
		break;
		
		case "ksochitam_49":
			dialog.text = "그래서, 테야살로 원정을 계획하고 있소?";
			link.l1 = "나도 모르겠어, 지노. 정말로 모르겠어...";
			link.l1.go = "ksochitam_50";
		break;
		
		case "ksochitam_50":
			dialog.text = "그럼 생각해 보시오, 왜 그렇게 해야 하는지? 내 의견은 들었으니, 이제 결정은 그대에게 달렸소..."+pchar.name+", 세인트 존스로 데려다줄 수 있겠소?";
			link.l1 = "그래, 지노. 가능한 한 빨리 출항하자. 이 끔찍한 섬은 이제 진절머리가 난다.";
			link.l1.go = "ksochitam_51";
		break;
		
		case "ksochitam_51":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_52";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Ksochitam", "16");
			pchar.quest.Ksochitam_gohome.win_condition.l1 = "location";
			pchar.quest.Ksochitam_gohome.win_condition.l1.location = "sentjons_town";
			pchar.quest.Ksochitam_gohome.function = "Ksochitam_ArriveHome";
			pchar.questTemp.Ksochitam = "gohome";
		break;
		
		case "ksochitam_52":
			dialog.text = "곧 집에 갈 수 있을까, "+pchar.name+"? 내 플라스크랑 시험관이 정말 그리워...";
			link.l1 = "그래, 그래, 지노, 곧 우리가 앤티가에 도착할 거야.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_52";
		break;
		
		case "ksochitam_53":
			dialog.text = "드디어 돌아와서 기쁘군요! 당신네 선원들은 어떻게 그렇게 오랜 시간을 배에서 보내는지 상상이 안 돼요...";
			link.l1 = "습관의 문제지, 지노.";
			link.l1.go = "ksochitam_54";
		break;
		
		case "ksochitam_54":
			dialog.text = "나는 단단한 땅 위에 누워 침대에서 쉴 생각에 무척 기쁘구나... 바라건대, 그렇게 되길. "+pchar.name+", 테야살에 가볼 생각조차 하지 않은 건가?";
			link.l1 = "아직 잘 모르겠어, Gino. 솔직히 말해서, 아직도 확신이 안 들어.";
			link.l1.go = "ksochitam_55";
		break;
		
		case "ksochitam_55":
			dialog.text = "쿠쿨칸의 가면을 파괴하고 근심 없이 사시오, 선장. 원하신다면 내가 가진 가장 강한 산에 그 가면을 녹여 없애드릴 수도 있소. 그런 일로 원한을 품지는 않을 테니.";
			link.l1 = "있잖아, 나는 좀 기다릴 거야. 파괴할 시간은 언제든 있으니까.";
			link.l1.go = "ksochitam_56";
		break;
		
		case "ksochitam_56":
			dialog.text = "결정은 당신 몫이오. 만약 이 유물을 세상에서 없애기로 한다면, 나에게 오시오. 멋진 항해에 감사하오, 선장!";
			link.l1 = "언제든지, Gino. 또 보자!";
			link.l1.go = "exit";
			NextDiag.TempNode = "first time";
			AddDialogExitQuestFunction("Ksochitam_TripComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("너는 "+GetSexPhrase("도둑이다, 나리! 경비병들아, 저 놈을 잡아라\n","도둑이다, 저 계집애를 잡아라! 경비병들, 저년을 붙잡아! ")+"!!!","저것 좀 봐! 내가 잠깐 생각에 잠긴 사이에 내 가슴을 확인하려 들다니! 도둑이다! 도둑 잡아라!!!","경비병들! 도둑이야! 저 도둑 잡아라!!!");
			link.l1 = "젠장!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
