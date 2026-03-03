int iLoxlyPseudoGlobal;

// Альберт Локсли - адвокат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
    string sTemp, attrLoc;
	
    attrLoc = Dialog.CurrentNode;
	int iSumm = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
	{
		i = findsubstr(attrLoc, "_" , 0);
		npchar.quest.relation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
			Dialog.CurrentNode = "RelationYet";
		}
		else Dialog.CurrentNode = "RelationAny_Done";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "내 이름은 알베르 로슬리이고, 나는 변호사요. 나는 재판에서 의뢰인의 이익을 대변하지. 내 서비스는 비싸지만, 그만한 가치가 있으니 안심하시오.";
				if(SandBoxMode)
				{					
					if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
					{
						link.l1 = "영국 당국 때문에 곤란한 상황에 처했소.";
						link.l1.go = "RelationTo_0";
					}
					
					if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
					{
						link.l2 = "나는 프랑스 당국과 문제가 생겼어.";
						link.l2.go = "RelationTo_1";
					}
					if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
					{
						link.l3 = "나는 스페인 당국과 문제가 생겼어.";
						link.l3.go = "RelationTo_2";
					}

					if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
					{
						link.l4 = "나는 네덜란드 당국과 문제가 생겼어.";
						link.l4.go = "RelationTo_3";
					}
					if (ChangeContrabandRelation(pchar, 0) <= 5)
					{
						Link.l5 = "나는 밀수업자들과 다투었어.";
						Link.l5.go = "contraband";
					}
					Link.l7 = "감사하지만, 다행히도 지금까지 변호사의 도움이 필요했던 적은 없었소.";
					Link.l7.go = "exit";
					NextDiag.TempNode = "Loxly";
					npchar.quest.meeting = "1";
					break;
				}
				link.l1 = "감사하지만, 다행히도 지금까지는 변호사의 도움이 필요하지 않았소.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "loxly")
				{
					link.l1 = "당신의 도움이 필요하오. 나는 헬렌 맥아더라는 젊은 아가씨의 공식 대리인이오. 그녀는 유명한 니콜라스 샤프의 손녀지. 어머니와 삼촌이 세상을 떠난 뒤로 법적으로 남은 유일한 상속인이오. 그녀의 삼촌 유언장에 따르면, 그녀는 이슬라 테소로에 대한 모든 권리를 가지고 있소. 헬렌이 그 섬의 정당한 주인이 되도록 돕는 대가로 얼마를 원하오?";
					link.l1.go = "saga";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga"))
				{
					if (pchar.questTemp.Saga == "loxly") // первое обращение по саге
					{
						dialog.text = "제 도움이 필요하십니까, 나리? 만족하실 겁니다, 장담하오.";
						link.l1 = "그래, 필요하네. 나는 헬렌 맥아더라는 젊은 아가씨의 공식 대리인이오. 그녀는 유명한 니콜라스 샤프의 손녀지. 어머니와 삼촌이 세상을 떠난 후, 그녀만이 법적으로 유일한 상속인이오. 삼촌의 유언장에 따라 그녀는 이슬라 테소로에 대한 모든 권리를 가지고 있소. 헬렌이 그 섬의 정당한 주인이 되도록 도와주는 대가로 얼마를 원하오?\n";
						link.l1.go = "saga";
						break;
					}
					if (pchar.questTemp.Saga == "bakaut")
					{
						dialog.text = "나리, 아직 나리의 일에 대해 자세히 알지 못하오. 이미 말씀드렸듯이, 나중에 다시 찾아와 주시기 바라오.";
						link.l1 = "좋아.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "molligan" || pchar.questTemp.Saga == "sellbakaut")
					{ // если не выполнил до конца квест по бакауту
						dialog.text = "나리, 유감스럽게도 모든 필요한 서류를 기록 보관소에서 모으려면 시간이 더 필요합니다. 아직 준비가 되지 않았습니다. 부디 나중에 다시 찾아주십시오.";
						link.l1 = "좋아.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "removebakaut") // с бакаутом разобрались
					{
						// четвертая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							RemoveItems(pchar, "map_sharp_full", 1);
							dialog.text = "나리, 왜 그렇게 느릿느릿 일하셨소?! 이제 당신 주인에게는 끝장이오. 유언장 검증 기간이 이미 지났고, 이제 이슬라 테소로는 영국의 소유요. 곧 군사 기지가 될 것이오.";
							link.l1 ="이런 젠장! 내 모든 노력이 다 허사가 된 것 같군...";
							link.l1.go = "saga_l3";							
						}
						else
						{
							dialog.text = "아, 여기 계셨군요, 나리. 자료는 이미 숙지했으니, 이제 선불을 받을 차례입니다. 두블룬을 가져오셨습니까?";
							if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) {n = 1000;}
							else {n = 450;}
							if (PCharDublonsTotal() >= n)
							{
								link.l1 = "그래, 가지고 있네. 여기 자네의 두블룬이야.";
								link.l1.go = "saga_5";
							}
							else
							{
								link.l1 = "기억력이 좋지 않아 용서해 주시오, 그것들은 내 배의 상자에 두고 왔소. 곧 가져오겠소.";
								link.l1.go = "exit";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "shadow")
					{
						// пятая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							dialog.text = "이봐, 왜 그렇게 느릿느릿 일한 거야?! 네 주인장은 이제 끝장이야. 유언장 검증 기간이 끝나서 이제 이슬라 테소로는 영국 땅이 됐어. 곧 군사 기지가 될 거다.";
							link.l1 ="이런 젠장! 내 모든 노력이 헛수고였던 것 같군...";	
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "나리, 주인분의 혈통을 증명할 만한 무언가를 찾으셨습니까?";
							if (!CheckCharacterItem(pchar, "Letter_beatriss"))
							{
								link.l1 = "아직 아니오. 하지만 지금 진행 중이오.";
								link.l1.go = "exit";
							}
							else
							{
								link.l1 = "그래. 나는 정말로 철저한 증거를 가지고 있네.";
								link.l1.go = "saga_14";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "court" && GetNpcQuestPastDayParam(npchar, "court_date") >= 1 && IsOfficer(characterFromId("Helena")))
					{
						 // запрет сохранения чтобы ленку не заграбастали себе умники всякие с ГК-  лесник
						InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться																																			   
						dialog.text = "아, 여기 계셨군요, 나리. 뵙게 되어 반갑습니다. 사실, 꽤 오래 기다렸다는 걸 인정해야겠군요. 이분이 당신의 주인입니까?";
						link.l1 = "네. 헬렌 맥아더를 소개해 드리겠습니다.";
						link.l1.go = "saga_26";
						break;
					}
					dialog.text = "제 도움이 필요하십니까, 나리? 만족하실 겁니다, 제가 보장하지요.";
					link.l1 = "감사하지만, 지금은 필요하지 않소.";
					link.l1.go = "exit";
				}
				if (CheckAttribute(npchar, "quest.waitgold"))
				{
					dialog.text = "좋은 하루입니다, 나리. 제 보수를 가져오셨겠지요?";
					if (PCharDublonsTotal() >= 450)
					{
						link.l1 = "그래, 가지고 있네. 여기 자네의 두블룬이야.";
						link.l1.go = "saga_36";
					}
					link.l2 = "있잖소, 록슬리 나리, 내가 생각해봤는데... 내 말은, 900두블룬이면 당신 일값으로 충분하고도 남는다는 거요.";
					link.l2.go = "saga_38";
					link.l3 = "기억하고 있습니다, 록슬리 나리. 조금 있다가 가져다드리겠습니다...";
					link.l3.go = "exit";
					break;
				}
				dialog.text = "제 도움이 필요하십니까, 나리? 만족하실 겁니다, 제가 보장하오.";
				link.l1 = "고맙지만, 지금은 필요하지 않소.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "saga":
			// третья проверка времени. Отбираем Элен, чистим квестовый лут, даем флаг на Свенсона, вызываем перемены
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				RemoveItems(pchar, "map_sharp_full", 1);
				dialog.text = "나리, 바다에 너무 오래 계셨나 봅니다. 이제 이슬라 테소로는 영국 해군의 군사 기지요! 그래요, 샤프의 유언장은 존재하지만 이미 효력이 끝났고, 이슬라 테소로는 영국 왕실의 소유가 되어버렸소. 유감이오!";
				link.l1 ="이런 젠장! 내 모든 노력이 헛수고였던 것 같군...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "그 아가씨가 섬 전체의 소유주라고 주장한다고? 흠... 이건 쉽지 않은 문제일 것 같군. 이슬라 테소로는 이미 거의 영국 식민지나 다름없으니...\n";
				link.l1 = "아직 아니오. 유언장에 따르면, 지도 두 조각을 모두 제시하는 남자든 여자든 이슬라 테소로의 소유주가 되오. 우리는 샤프의 지도 두 조각을 모두 가지고 있으니, 그것이 바로 상속의 주요 증거요.";
				link.l1.go = "saga_1";
			}
		break;
		
		case "saga_1":
			dialog.text = "니콜라스 샤프... 그래, 그래. 나는 기록 보관소에 들러서 이슬라 테소로와 관련된 자료들을 살펴봐야겠어. 지도를 가지고 있나?";
			link.l1 = "가지고 있소. 하지만 계약서에 서명한 후에만 넘겨주겠소. 자, 그대의 보수는 얼마요?";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			sTemp = "";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = " Your esteemed involvement won't go unnoticed either. Cartagena... There will be questions.";
			dialog.text = "내가 말했듯이, 쉽지 않을 거야. 낡은 배나 오두막이 아니라 섬 전체에 대한 소유권을 증명해야 하거든. 게다가 니콜라스 샤프는 해적이었고, 해적이나 그 친척을 돕는 건 대가가 많이 드는 일이야."+sTemp;
			link.l1 = "실제로 얼마인지 말해 줄 건가?";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			sTemp = "four hundred and fifty";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "one thousand";
			dialog.text = "나리, 최종 금액은 재판 중에 결정될 것입니다. 아직 얼마나 문제가 될지 저도 모릅니다. 그러나 선지급액을 추산할 준비는 되어 있습니다 - "+sTemp+" 두블론이다. 사업이 얼마나 잘 풀리느냐에 따라 이 금액을 한두 번 더 내야 할 수도 있네.\n일주일 안에 돈을 가져오게. 나는 기록을 확인하고 준비할 시간이 필요하네. 그 다음에 거래를 진행하지. 약속하겠나?";
			link.l1 = "당신이 이 군도에서 최고의 변호사라고 추천받았으니, 거래가 성사된 거요. 일주일 후에 봅시다!";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			DialogExit();
			pchar.questTemp.Saga = "bakaut"; // обновляем флаг
			AddQuestRecord("Testament", "2");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) AddQuestUserData("Testament", "sMoney", "1000");
			else AddQuestUserData("Testament", "sMoney", "450");
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				bDisableFastReload = true;
				SetFunctionLocationCondition("HelenDrinking_PortRoyalDialog", "PortRoyal_town", false);
			}
		break;
		
		case "saga_5":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
			{
				RemoveDublonsFromPCharTotal(1000);
				//Log_Info("You have given 1450 doubloons");
			}
			else
			{
				RemoveDublonsFromPCharTotal(450);
				//Log_Info("You have given 450 doubloons");
			}
			PlaySound("interface\important_item.wav");
			dialog.text = "좋습니다. 당신의 사건을 맡아 법정에서 이익을 대변할 준비가 되어 있습니다. 이제 본론으로 들어갑시다. 저는 기록 보관소에서 성과를 내고 중요한 인물들과도 이야기를 나눴습니다. 샤프의 유산 사건은 쉽지 않을 것입니다. 지도를 두 조각 모두 손에 넣은 건 다행이지만, 그것만으로는 부족할 수도 있습니다.\n도일 대령은 토르투가 장악에 실패한 뒤로 이슬라 테소로에 큰 계획을 세우고 있습니다. 그곳은 천연 방어선을 갖추고 있어 이 지역의 미래 군사 기지로 삼을 수 있기 때문입니다.";
			link.l1 = "하지만 헬렌은 영국 법에 따라 그 섬에 대한 모든 권리가 있어!";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "자네는 고 샤프가 유언장에 추가 조항을 넣었다는 걸 모를 수도 있겠군. 상속인 또는 상속인들은 그의 성을 가져야 하네. 내가 기억하기로는, 자네 딸은 성이 다르지 않나? 맥아더라고 했지?";
			link.l1 = "이것은 그녀의 양아버지의 성이지만, 엘렌은 샤프라는 이름을 쓸 정당한 권리가 있소. 그녀는 이미 세상을 떠난 비어트리스 샤프의 딸이며, 비어트리스는 니콜라스의 딸이었으니까.";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "훌륭하군! 하지만 맹세코 그걸 증명할 수 있는 사람이 누구지? 헬렌의 양부모가 비트리스 샤프와 알고 지냈나?";
			link.l1 = "내가 알기로는, 그렇지 않았소. 맥아더 나리는 그녀를 글래디스의 딸로 여겼고, 글래디스는 그 소녀의 아버지와는 아는 사이일 뿐이었소.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "안타깝군요. 기록 보관소 어디에도 비트리스 샤프에게 자식이 있었다는 언급을 찾지 못했소. 아이의 출생에 대한 공식적인 기록 자체가 없을 가능성도 있지. 누구든 샤프의 손자라고 자칭하며 그의 성을 쓸 권리가 있다고 주장할 수 있으니.";
			link.l1 = "하지만 헬렌만이 완전한 지도를 가지고 있어!";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "이게 그녀의 비장의 카드지. 아마 현지 당국이 이슬라 테소로에 대한 자기들만의 계획이 없었다면 이걸로 충분했을 거야. 비아트리스의 필체와 서명이 담긴 문서가 기록 보관소에 있어. 우리는 그녀가 직접 쓴, 딸의 출생 사실을 증명할 수 있는 문서를 찾아야 해—그 딸이 바로 그 글래디스에게 맡겨졌지... 에이, 성이 뭐였더라?\n";
			link.l1 = "챈들러. 벨리즈에서 온 글래디스 챈들러.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "정확해. 그런 걸 찾을 기회가 있나?";
			link.l1 = "의심스럽군. 너무 많은 세월이 흘렀지. 전설에 따르면, 헬렌의 아버지가 바로 도살자 선장일지도 모른다네. 아마 세인트 존스의 전직 교수형 집행인이 이 일에 대해 뭔가 말해줄 수 있을 거야. 그가 헬렌의 아버지를 마지막으로 살아 있을 때 본 사람이거든.";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "흠. 정말 재미있는 사람이었지. 내가 기억하기로는 이름이 레이먼드 베이커였어. 한 번 그와 대화할 기회가 있었는데, 운이 좋았지. 똑똑하고 교양 있는 사람이더군. 자, 너는 앤티과에서 뭔가 찾아보고, 나는 계속해서 기록 보관소를 뒤져볼게. 어쩌면 쓸만한 걸 찾을 수도 있겠지.";
			link.l1 = "좋아. 나도 괜찮아.";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "샤프의 지도를 내놓고 서둘러, 베이커와 이야기해 봐. 그의 도움으로 문서를 찾을 수도 있을 거야. 어쩌면 그녀의 출생 증거도 찾을 수 있겠지.";
			link.l1 = "에이, 나도 그러고 싶지. 좋아, 잘 가, 록슬리 나리.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			DialogExit();
			RemoveItems(pchar, "map_sharp_full", 1);
			pchar.questTemp.Saga = "shadow";
			pchar.questTemp.Saga.Shadows = "sentjons";
			AddQuestRecord("Shadows", "1");
		break;
		
		case "saga_14":
			dialog.text = "그런가? 이 증거를 한번 보지.";
			link.l1 = "이것은 비트리스 샤프가 오빠에게 쓴 개인적인 편지야.\n여기 보면 그녀가 딸을 낳았고, 그 아이의 아버지가 사실상 로렌스 벨트로프였다고 적혀 있어.\n그 소녀는 글래디스 챈들러라는 젊은 과부에게 보내졌지.\n로렌스 벨트로프는 선장 부처로도 알려져 있어.\n자, 이 편지를 가져가...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			RemoveItems(pchar, "Letter_beatriss", 1);
			dialog.text = "";
			link.l1 = "글래디스는 선서하고서라도 그것을 증언할 준비가 되어 있습니다. 또한 그 아버지가 자신을 부처 선장이라고 소개했다는 것도 확인할 준비가 되어 있습니다.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) // Белтроп убит
			{
				dialog.text = "잠깐만! 악명 높은 해적이자 영국 신민의 살해자인 부처 선장은 20년 전에 세인트 존스 요새에서 교수형을 당했어. 그리고 리처드 도일의 절친이었던 로렌스 벨트로프는 얼마 전에 비극적으로 죽었지. 무엇보다도, 도일은 그를 샤프타운의 새 총독으로 만들고 싶어 했어!";
				link.l1 = "하! 그래, 아무도 모르는 사실이지... 나는 세인트 존스의 전직 교수형 집행인 레이먼드 베이커가 죽음의 위협 아래 도살자의 처형을 위조할 수밖에 없었다고 쓴 증언서를 가지고 있다네! 여기, 한번 보시게...\n";
				link.l1.go = "saga_17";
			}
			else
			{
				dialog.text = "잠깐만! 악명 높은 해적이자 영국 신민의 살인자인 부처 선장은 20년 전에 세인트 존스 요새에서 교수형을 당했어. 그리고 로렌스 벨트로프는 살아 있고 포트 로얄의 최고 저택 중 한 곳에 살고 있지. 게다가 도일은 그를 샤프타운의 새 총독으로 만들려고 해!";
				link.l1 = "하! 그래, 아무도 모를 거야... 나는 세인트 존스의 전 형리 레이먼드 베이커가 쓴 증언서를 가지고 있어. 그는 확실한 죽음의 위협 아래에서 부처의 처형을 조작할 수밖에 없었다고 했지! 자, 여기, 한번 봐봐...\n";
				link.l1.go = "saga_17";
			}
		break;
		
		case "saga_17":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "흠. 그래, 그래...";
			link.l1 = "참으로 교묘하지 않은가? 부처 선장은 살아남아 영국으로 돌아갔지. 본래 이름인 로렌스 벨트로프로 다시 바꾸고 아무도 모르게 여기로 돌아왔어.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "saga_18";
			else link.l1.go = "saga_22";
		break;
		
		case "saga_18":
			dialog.text = "하지만 이건... 이건 모든 걸 바꿔 놓는군! 베아트리스의 편지를 공개하면, 그동안 군사 총독이 도망자 해적 부처를 숨기고 있었다는 사실이 드러나겠지. 부처는 보자마자 체포되어 과거의 죄로 재판을 받아야 할 놈이었으니까!\n그리고 베이커의 증언이 있으면 그 어떤 반박도 완전히 무너질 거야! 정말 대단하군! 이런 비장의 패가 있으니, 도일을 정정당당하게 이길 수 있겠어!";
			link.l1 = "기쁘구나. 이번 시련에서 너를 믿고 있네. 그리고 한 가지 더 묻겠네, 로렌스 벨트로프는 어떻게 죽었는가?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "이건 으스스한 이야기입니다, 나리. 그는 자기 침실에서 일그러진 얼굴로 발견되었지요. 그 두려움을 모르는 사내가 무엇에 그렇게 겁을 먹었는지 상상하기도 어렵습니다. 사람들 말로는 온몸이 서리로 뒤덮여 있었다고 합니다. 몸에는 끔찍하고 찢긴 상처가 가득했지만, 바닥에는 피 한 방울도 없었어요! 상상해 보십시오! 피 한 방울도 없었다니!";
			link.l1 = "그래, 정말 악몽에서나 나올 법한 이야기군. 살해당한 것 같아... 하지만 누가 그런 짓을 했을까?";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "알 수 없소. 너무 복잡하게 얽혀 있소... 주둔지 의사는 그의 상처가 치명적이지 않다고 했소. 벨트로프는 두려움이나 고통, 아니면 다른 무언가로 죽었소. 아무튼, 이건 미스터리한 죽음이오.";
			link.l1 = "알겠소... 재판은 언제 시작되오?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "모든 것은 당신에게 달렸소, 나리. 두 번째 수수료인 450두블론을 지불하시면 즉시 모든 서류를 법정에 제출하겠소. 그 후 일주일 뒤에 헬렌이 자신의 권리를 얻게 될 것이오.";
			if (PCharDublonsTotal() >= 450)
			{
				link.l1 = "좋소. 여기 금화들이오.";
				link.l1.go = "saga_24";
			}
			else
			{
				link.l1 = "네, 물론이지요. 필요한 금액을 가져오겠습니다.";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_23";
			}
		break;
		
		case "saga_23":
			// шестая проверка времени
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				dialog.text = "나리, 저를 정말 놀라게 하셨군요! 당신이 많은 일을 해주셔서 섬이 거의 우리 손에 들어올 뻔했는데, 제 보수 지급을 미루신 탓에 이제 다 끝나버렸습니다! 유언장이 만료되어 이제 이슬라 테소로는 영국 왕실 소유가 되었소. 그곳은 군사 기지가 될 겁니다.";
				link.l1 ="이런 젠장! 내 모든 노력이 헛수고였던 것 같군...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "내 보수의 두 번째 부분을 가져왔나, 나리?";
				if (PCharDublonsTotal() >= 450)
				{
					link.l1 = "네, 물론이죠. 여기 금화가 있습니다.";
					link.l1.go = "saga_24";
				}
				else
				{
					link.l1 = "기억이 좋지 않아 실례를 범했소, 그 물건들은 내 배에 있는 상자에 두고 왔소. 곧 가져오겠소.";
					link.l1.go = "exit";
					NextDiag.TempNode = "saga_23";
				}
			}
		break;
		
		case "saga_22":
			dialog.text = "하지만 이건... 이건 모든 걸 바꾸는군! 베아트리스의 편지를 공개하면 로렌스 벨트로프는 즉시 체포되어 과거의 죄로 재판을 받아야 해!\n그리고 베이커의 증언이 있으면 그 어떤 반박도 완전히 무너질 거야! 정말 훌륭하군! 이런 비장의 패가 있으니 도일을 정정당당하게 이길 수 있겠어!";
			link.l1 = "매우 기쁩니다. 재판은 언제 시작됩니까?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_24":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "훌륭합니다, 나리. 함께 거래하게 되어 기쁩니다. 자, 이제 조건을 말씀드리죠. 내일 다시 여기로 오십시오. 그래요, 맞게 들으셨습니다 – 내일입니다! 어쨌든 저는 이 군도에서 최고의 변호사이고, 인맥도 넓으니까요.\n당신의 의뢰인도 데려오십시오, 그녀 없이는 재판이 열리지 않을 테니까요. 늦지 말고, 도시를 떠나지 마십시오. 그리고 가능하다면 마지막 잔금도 가져오십시오. 우리의 승리를 저는 확신합니다.";
			link.l1 = "좋소. 내일 당신 사무실로 가겠소, 록슬리 나리.";
			link.l1.go = "saga_25";
		break;
		
		case "saga_25":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "court_date");
			pchar.questTemp.Saga = "court"; // обновляем флаг
			AddQuestRecord("Testament", "10");
			NextDiag.CurrentNode = "First time";
			// закрываем выходы из города
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", true);// лесник там нет этого пирса
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true);
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
			// снимаем общий таймер Саги!
			pchar.quest.Saga_TimeOver.over = "yes";
		break;
		
		case "saga_26":
			dialog.text = "맥아더? 아니, 샤프다! 자, 이제 따라와!";
			link.l1 = "...";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			DialogExit();
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto10");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			sld = characterFromId("Helena");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(npchar, "reload", "reload1", "Saga_CourtGo", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			LAi_ActorFollow(sld, npchar, "", -1);
			NextDiag.CurrentNode = "saga_28";
			// открываем выходы из города
			//LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник рано 
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", false);
			//LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "saga_28":
			dialog.text = "축하를 드리오, 나리, 그리고 당신의 주인에게도. 이제 그녀가 이슬라 테소로의 정당한 통치자요. 이 일로 샴페인 한잔 할 만하오!";
			link.l1 = "물론이지, 록슬리 나리. 연설이 정말 훌륭했소. 벨트롭 로렌스가 부처 선장이라고 법정에서 말했을 때 도일 대령이 심장마비라도 일으킬 줄 알았다오.";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "그래, 도일 나리도 이제 이슬라 테소로에 군사 기지를 세우겠다는 꿈과 작별해야겠지. 그리고 어쩌겠나? 법은 법이고, 모두를 위해 쓰인 것이니 존경받는 대령에게도 예외는 없지.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die"))
			{
				link.l1 = "서류는 모두 제대로 갖추어졌나, 그리고 그 서류들이 헬렌의 섬 상속권을 확인해 주는가?";
				link.l1.go = "saga_30";
			}
			else
			{
				link.l1 = "로렌스 벨트롭의 체포를 판사가 명령했다는 소문을 들었소. 교수형에 처해질 예정이오?";
				link.l1.go = "saga_34";
			}
		break;
		
		case "saga_30":
			dialog.text = "물론입니다, 나리. 모든 쉼표를 하나하나 확인했습니다. 정확하다고 확신하셔도 됩니다.";
			link.l1 = "좋소...";
			link.l1.go = "saga_31";
		break;
		
		case "saga_31":
			dialog.text = "자, 제 일은 끝났습니다. 이번 사건은 까다로웠지만, 우리가 함께 이겨냈지요. 이제, 나리, 마지막 수고비만 지불해 주시면 됩니다. 부담 갖지 마십시오, 바쁘신 거 잘 압니다. 하지만 일주일 안에 남은 450두블룬을 꼭 가져다주실 거라 믿습니다.\n게다가, 나리 같은 고객께는 언제나 넉넉한 할인을 드리니 안심하셔도 됩니다. 저는 나리께 큰 도움이 될 수 있습니다. 군도 각지의 수도, 심지어 적대적인 곳에도 인맥이 있으니 어떤 법적 문제든 해결해 드릴 수 있습니다.";
			link.l1 = "훌륭하군. 이제 누구에게 물어봐야 할지 알겠어.";
			link.l1.go = "saga_32";
		break;
		
		case "saga_32":
			dialog.text = "가장 어려운 상황에서도 유리한 결과를 보장하오.";
			link.l1 = "좋군. 이제 가봐야겠어, 헬렌이랑 할 일이 많거든.";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "안녕히 가십시오, 나리.";
			link.l1 = "안녕히 가십시오, Loxley 나리.";
			link.l1.go = "saga_35";
		break;
		
		case "saga_34":
			dialog.text = "그렇다고 생각하오, 그는 부처 선장, 해적이자 도적이오. 지금은 포트 로얄에 없소. 운 좋게도 도망쳐서 섬 깊숙이 숨어들었지. 하지만 사냥이 시작됐으니 반드시 잡힐 것이오.";
			link.l1 = "그렇군... 서류는 제대로 준비되어 있나?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_35":
			DialogExit();
			SetFunctionTimerCondition("Saga_RemainGoldLoxly", 0, 0, 10, false); // таймер на оплату услуг
			DoQuestReloadToLocation("PortRoyal_town", "quest", "quest3", "Saga_HelenaIslaTesoro");
			npchar.quest.waitgold = "true";
			pchar.questTemp.Saga = "lastpages";
			NextDiag.CurrentNode = "First time";
		break;
		
		case "saga_36":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "훌륭하군요! 거래하게 되어 기뻤습니다, 나리! 이제 어떤 일이든 제게 도움을 청하시면 할인을 드리겠습니다. 법에 문제가 있거나 현상금이 걸렸을 때도... 언제든 환영입니다. 항상 뵙게 되어 기쁠 것입니다.";
			link.l1 = "문제에 아예 휘말리지 않는 게 더 좋겠지만... 일이란 게 그렇지 않지. 고맙습니다, 록슬리 나리. 안녕히 계십시오.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			DialogExit();
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			NextDiag.CurrentNode = "Loxly"; // услуги адвоката
		break;
		
		case "saga_38":
			dialog.text = "무슨 말씀이십니까, 나리? 우리 합의 조건을 어기시겠다는 겁니까?";
			link.l1 = "정확해. 내가 거의 모든 일을 했지. 내가 증거를 얻으려고 무슨 짓까지 했는지 너는 상상도 못 할 거야. 그런데 넌 그 서류만 챙겨서 법정에 갔잖아. 아홉백 두블룬이면 충분하고도 남아, 그건 확실해.";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = "너 해적처럼 말하는구나, 나리! 뭐, 450두블론 잃는다고 내가 거지 되진 않겠지만, 너도 부자 되긴 글렀다. 사실, 너는 방금 훨씬 더 많은 걸 잃었어! 그리고 앞으로도 뭔가를 더 잃게 될지도 모르지... 당장 내 집에서 나가라, 그리고 다시는 여기 나타나지 마라!\n";
			link.l1 = "그리고 나는 그렇게 할 것이오. 잘 가시오, 록슬리 나리.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			LocatorReloadEnterDisable("PortRoyal_town", "houseSp4", true); // закроем вход к Локсли
			ChangeCharacterNationReputation(pchar, ENGLAND, -10);
		break;
		
		case "saga_40":
			dialog.text = "너랑 말하고 싶지 않아. 꺼져, 아니면 경비병을 부를 거야!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
		break;
		
		// провалы Саги
		case "saga_l3":
			dialog.text = "나리, 좀 더 일찍 저를 찾아오셨다면 사건을 이겼을 텐데요. 유언장의 효력이 이미 끝났습니다. 유감입니다.";
			link.l1 = "에이, 나는 더 미안하군! 자, 안녕히 가시오, 록슬리 나리.";
			link.l1.go = "saga_l3_1";
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l3";
		break;
		
		case "saga_l3_1":
			DialogExit();
			pchar.quest.Saga_Late_3.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_3.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_3.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga = "late_l3"; // для Свенсона
		break;
		
	//-------------------------------------- адвокатские услуги ------------------------------------------------
		case "Loxly":
			dialog.text = TimeGreeting()+", 나리. 뵙게 되어 반갑습니다. 제 도움이 필요하십니까?";
			link.l1 = "그래. 그래서 내가 여기 온 거야.";
			link.l1.go = "loxly_1";
			link.l2 = "아니, 다행히 지금은 필요 없네. 그냥 인사나 하려고 왔어.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "loxly_1":
			dialog.text = "당신의 말을 들을 준비가 되어 있소. 어떤 도움이 필요하오?";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l1 = "나는 영국 당국과 문제가 생겼어.";
				link.l1.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l2 = "나는 프랑스 당국에 곤란을 겪고 있어.";
				link.l2.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l3 = "나는 스페인 당국과 문제가 생겼어.";
				link.l3.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "나는 네덜란드 당국과 문제가 생겼어.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "나는 밀수꾼들과 다투었어.";
				Link.l5.go = "contraband";
            }
			Link.l7 = "미안하오, 마음이 바뀌었소...";
			Link.l7.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "RelationYet": // уже оплачено
			dialog.text = "이미 당신 일은 처리하고 있습니다. 걱정 마십시오, 잘 해결될 것이니 제가 보장하오.";
			Link.l1 = "감사합니다. 기다리고 있겠습니다.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		// --> снятие НЗГ
		case "RelationAny_Done":
			i = sti(npchar.quest.relation);
			iLoxlyPseudoGlobal = CalculateRelationSum(i, true);
			int iRate = abs(ChangeCharacterNationReputation(pchar, i, 0));
			if (iRate <= 10) sTemp = "Well, I wouldn't call that trouble. Just a little problem. I will settle the affair at once";
			if (iRate > 10 && iRate <= 30) sTemp = "Yes, your reputation is slightly spoiled but I don't see anything critical. I will settle the affair at once";
			if (iRate > 30 && iRate <= 60) sTemp = "Yes, you went down the wrong path with the authorities. It won't be easy but I am sure that I will be able to settle your disagreements without a hitch";
			if (iRate > 60 && iRate <= 90) sTemp = "And how did you do that, Sir? Your troubles are not just serious, they are really serious. The authorities are very eager to get you. I will have to put a lot of effort into settling your disagreements";
			if (iRate > 90) sTemp = "Well... The situation is catastrophic - you are claimed to be the most bitter enemy. It will be tough but I am the best lawyer in the Caribbean after all, so I will settle your disagreements";
			dialog.text = ""+sTemp+" 와 함께 "+XI_ConvertString(Nations[i].Name+"Abl")+". 대가를 치러야 할 거요 "+FindRussianMoneyString(iLoxlyPseudoGlobal)+".";
			if(sti(pchar.money) >= iLoxlyPseudoGlobal)
			{
				link.l1 = "좋소, Loxley 나리, 동의하오. 여기 돈이니, 가능한 한 빨리 일을 정리하도록 하시오.";
				link.l1.go = "relation";
			}
			link.l2 = "지금은 네가 요구하는 돈이 없어. 나중에 다시 올게!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;

		case "relation":
			i = sti(npchar.quest.relation);
			dialog.text = "거래하게 되어 기쁩니다, 나리. 이제 다시 안심하셔도 됩니다. 당신의 문제는 앞으로 2주 안에 해결될 것입니다. 부디 충돌은 피하시길 바랍니다\n "+XI_ConvertString(Nations[i].Name+"Abl")+", 내가 협상 중일 때.";
			link.l1 = "좋소, 경고는 명심하겠소. 고맙소, 그리고 안녕히 가시오!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -iLoxlyPseudoGlobal);
			ChangeNationRelationFromRelationAgent(i);
			attrLoc = "RelationAgent" + GetNationNameByType(i);
            Pchar.GenQuest.(attrLoc) = true;
			Pchar.GenQuest.(attrLoc).loyer = "true";
			NextDiag.TempNode = "Loxly";
		break;
		// <-- снятие НЗГ
		
		case "contraband":
			iLoxlyPseudoGlobal = CalculateRelationContraSum(true);
			dialog.Text = "그런데 왜 그런 짓을 한 거지? 밀수꾼들도 나름대로는 괜찮은 녀석들이야, 자기들 방식대로는 솔직하지. 우리 모두 살아야 하고 먹고살아야 하잖아... 좋아, 큰일은 아니고 네게 드는 비용도 얼마 안 될 거야 "+FindRussianMoneyString(iLoxlyPseudoGlobal)+".";
			if(sti(Pchar.money) >= iLoxlyPseudoGlobal)
			{
				Link.l1 = "알겠소, Loxley 나리. 동의하오. 여기 돈이니, 가능한 한 빨리 일을 정리하도록 하시오.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "지금은 네가 요구하는 돈이 없어. 나중에 다시 올게!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "훌륭하오, 내가 그대의 문제를 해결하겠소. 곧 다시 그대와 거래하고 싶어질 것이오.";
			Link.l1 = "고마워!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -iLoxlyPseudoGlobal);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
