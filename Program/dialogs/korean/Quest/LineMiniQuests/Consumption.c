// диалоги по квесту Цена чахотки
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.Consumption == "final")
			{
				dialog.text = "선장님! 바다로 나가셨다면서요! 무슨 일이 있었습니까? 뭔가 알아내셨나요? 제발, 말씀 좀 해주세요, 얼른 말해보세요!";
				if (CheckAttribute(pchar, "questTemp.Consumption.TakeMoney"))
				{//взял деньги
					link.l1 = "아니야, 내 이쁜이, 이번 습격은 총독 각하의 요청으로 이루어진 거야. 정말 유감이지만, 안젤로는 요새 지하 감옥에서 죽었어 – 이제는 의심의 여지가 없어. 마음 단단히 먹어!\n ";
					link.l1.go = "Waitress";
				}
				else
				{//убил Хуана
					if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
					{
						link.l1 = "네 말이 맞았어. 네 동생이 납치당했더군. 사령관이 죄수들을 가축처럼 '컨섬션'이라는 별명의 노예상인에게 팔아넘기고 있었지. 하지만 내가 그 배를 따라잡았고, 이제 그자는 바다 밑에 누워 있어. 네 동생 안젤로도 곧 상륙할 거야. 안타깝게도 모든 승객을 한 번에 육지로 데려갈 만큼 긴보트가 충분하지 않아. ";
						link.l1.go = "Waitress_2";
					}
					else
					{//отпустил Хуана
						link.l1 = "네 말이 맞았어. 네 동생이 납치됐더군. 사령관이 죄수들을 가축처럼 '컨섬션'이라는 별명의 노예상에게 팔아넘기고 있었어. 하지만 내가 그 자의 배를 따라잡았지. 그 자식은 죽이지 못했지만, 네 동생 안젤로는 곧 상륙할 거야. 안타깝게도 모든 승객을 한 번에 데려올 만큼 긴 보트가 충분하지 않아. ";
						link.l1.go = "Waitress_2";
					}
					sld = characterFromId("ConAndjelo");
					sld.lifeday = 0;
					RemovePassenger(Pchar, sld);
				}
			}
			else
			{
				dialog.text = "안젤로의 운명에 대해 뭔가 알아냈소, 선장?";
				link.l1 = "아직 아니야. 하지만 곧 소식이 있을 것 같아. 그냥 기다리기만 하면 돼. ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		case "without_moneysss": // лесник  если Гг нажрался..сволочь:D:D:D
		    dialog.text = "나리, 제 형을 찾아주겠다고 약속하셨잖아요... 왜 여기서 술만 마시며 시간만 허비하시는 겁니까?";
			link.l1 = "오오... 그래, 맞아... 헉... 진정해, 아가씨... 예수가 다 알아서 해... '꿀꺽'... 예수가 다 알아서 해. 난 이미 갔어... 헉...";
			link.l1.go = "exit";
		break;
		
		case "Servant":
			dialog.text = "좋은 오후요, 나리. 여기서 무슨 일로 오셨소?";
			link.l1 = "나리 사령관께 전할 전갈을 가져왔지만, 직접 전해 드려야겠소.";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "그럼 네가 요새에 가서 그를 찾아봐.";
			link.l1 = "이 전갈은 너무 중요해서 병사들이 보면 안 돼. 내가 너무 일찍 온 걸지도 모르지만, 여기서 그를 기다릴 수 있어. 믿어 줘, 정말 중요한 일이야!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < 40)
			{
				notification("Skill Check Failed (40)", SKILL_SNEAK);
				dialog.text = "나리 사령관께서는 보통 일상에 변동이 필요한 중요한 일에 대해 항상 미리 경고해 주십니다... 있잖아요, 사실 이번 일에 대해서도 미리 경고하셨었죠.";
				link.l1 = "그래서 그가 뭐라고 했지?";
				link.l1.go = "Servant_3";
			}
			else
			{
				notification("Skill Check Passed", SKILL_SNEAK);
				dialog.text = "좋아, 네 말을 믿지. 그리고 사령관 나리가 와서 네 말을 확인해 주면 더 믿어 주지. 하지만 그때까지는 계속 널 지켜볼 거다.";
				link.l1 = "원하는 만큼 나를 지켜봐도 돼...";
				link.l1.go = "Servant_4";
			}
		break;
		
		case "Servant_3":
			dialog.text = "그는 이런 경우엔 주둔지 경비병을 부르라고 했지. 하지만 우리끼리도 충분히 할 수 있을 거야. 얘들아! 저 놈 배를 갈라버리자!";
			link.l1 = "젠장!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Servant_4":
			DialogExit();
			NextDiag.CurrentNode = "Servant_repeat";
			LAi_SetOwnerType(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Servant_repeat":
			dialog.text = "또 뭘 원하지? 내게 전할 말을 정했어?";
			link.l1 = "아니, 나는 사령관을 기다릴 거야...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Servant_repeat";
		break;
		
		case "Servant_fight":
			int iRank = sti(pchar.rank)+5;
			int iScl = 15 + 2*sti(pchar.rank);
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			chrDisableReloadToLocation = true;
			for (i=9; i<=11; i++)
			{	
				sld = GetCharacter(NPC_GenerateCharacter("Conservant_"+i, "citiz_"+i, "man", "man", iRank, SPAIN, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "goto", "goto5");
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Consumption_AfterHouseFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//попытка залезть в сундук
		case "Man_FackYou":
			dialog.text = "너 도둑이냐! 아니면 첩자냐? 이봐, 아래층에 있는 녀석들, 빨리 와!";
			link.l1 = "이런, 망할 놈!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Sergio":
			dialog.text = "실례합니다, 잠시 말씀 좀 나눌 수 있을까요?";
			link.l1 = "솔직히 말해서, 나 지금 급해. 뭐 원하는 거야?";
			link.l1.go = "Sergio_1";
		break;
		
		case "Sergio_1":
			dialog.text = "우리 감옥에 있는 후안이라는 남자와 병에 대해 네가 수소문하고 있다는 얘기를 들었어...";
			link.l1 = "그래, 내가 그랬지... 너 자신에 대해 설명해 볼래?";
			link.l1.go = "Sergio_2";
		break;
		
		case "Sergio_2":
			dialog.text = "진정해, 진정하라고! 진정하고 칼에 손 대지 마! 우리 같은 편이잖아! 네가 왜 우리 문제에 신경 쓰는지는 모르겠지만, 이건 반드시 막아야 해! 더 이상 침묵할 수 없어!";
			link.l1 = "조용히 있으라고? 뭘 말이지? 결핵에 대해 뭘 아는데?";
			link.l1.go = "Sergio_3";
		break;
		
		case "Sergio_3":
			dialog.text = "나는 많은 걸 알고 있어, 아니 거의 다 안다고 해도 돼. 그리고 내 이야기를 해주겠지만… 여기서는 안 돼. 불이 꺼지는 저녁에 만나자. 나는 의무병이라 요새를 나갈 수 있어. 마을 문 밖에서 만나자, 그때 모든 걸 말해줄게. 제발 부탁이야—더 이상 묻지 마, 괜히 그들의 눈길을 끌기 전에, 아니면 이미 끌었을지도 모르니까… 이제 가봐야 해. 기억해, 밤에, 마을 문 밖에서.";
			link.l1 = "알겠어, 곧 갈게. 이봐! 잠깐만...";
			link.l1.go = "Sergio_4";
		break;
		
		case "Sergio_4":
			DialogExit();
			AddQuestRecord("Consumption", "8");
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption3.win_condition.l1 = "location";
			pchar.quest.Consumption3.win_condition.l1.location = "PortSpein_Exittown";
			pchar.quest.Consumption3.win_condition.l2 = "Hour";
			pchar.quest.Consumption3.win_condition.l2.start.hour = 0;
			pchar.quest.Consumption3.win_condition.l2.finish.hour = 3;
			pchar.quest.Consumption3.function = "Consumption_MeetSergio";
			pchar.quest.Consumption4.win_condition.l1 = "Timer";
			pchar.quest.Consumption4.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Consumption4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Consumption4.function = "Consumption_FailSergio";
			locations[FindLocation("PortSpein_Exittown")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("PortSpein_Exittown", true);//офицеров не пускать
		break;
		
		case "Sergio_5":
			dialog.text = "신께 감사하네, 자네가 와줘서... 혹시 누가 따라오진 않았지?";
			link.l1 = "왜? 너 너무 의심이 많아, 아마 그 꼴통 사령관 나리보다도 더하겠는걸. 그러니 본론으로 들어가자... 후안에 대해 뭘 알고 있지?";
			link.l1.go = "Sergio_6";
		break;
		
		case "Sergio_6":
			dialog.text = "내 이름은 세르히오 살도야. 우리 요새에서 의무병으로 일하고 있고...";
			link.l1 = "";
			link.l1.go = "Sergio_6_1";
		break;
		
		case "Sergio_6_1":
			dialog.text = "";
			link.l1 = "잠깐! 방금 들었어?";
			link.l1.go = "Sergio_7";
			Play3DSound("lomanie_vetki", -33.25, 1.00, 3.73)
		break;
		
		case "Sergio_7":
			dialog.text = "뭐?! 어디?";
			link.l1 = "젠장, 여기 우리만 있는 게 아니잖아... 이 망할 놈아, 누구를 데려온 거야?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Consumption_CreateBandits");
		break;
		
		case "Bandit":
			dialog.text = "우릴 발견했어! 너는 의사를 맡아, 나는 다른 놈을 맡을게!";
			link.l1 = "...";
			link.l1.go = "Bandit_1";
		break;
		
		case "Bandit_1":
			DialogExit();
			sld = characterFromId("Sergio");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=3; i++)
			{	
				sld = characterFromId("Conbandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Conbandit_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Sergio_8":
			dialog.text = "칼 집어 넣어, 끝났어! 너도 봤잖아, 쟤네가 나까지 죽이려고 했다는 걸!";
			link.l1 = "음, 이건 음모치고는 너무 정교한 것 같군 - 그러니까, 너는 그들과 한패가 아니란 거지. 어디까지 얘기했더라? 너 감옥 의사 맞지?";
			link.l1.go = "Sergio_9";
		break;
		
		case "Sergio_9":
			dialog.text = "그래. 나는 감옥의 의사로 일하고 있지. 어릴 때 의학을 공부했는데, 여기엔 배운 사람이 별로 없어. 그래서 감옥에서 무슨 일이 벌어지는지 누구보다 내가 더 잘 알지!";
			link.l1 = "무슨 일이야? 포로들은 어떻게 된 거지? 갑자기 사라진 거에 대해 뭐 아는 거라도 있어?";
			link.l1.go = "Sergio_10";
		break;
		
		case "Sergio_10":
			dialog.text = "우리 사령관이 그들을 팔아... 후안이라는 노예상에게 소처럼 팔아넘기지. 아무도 찾지 않을 놈들, 거지나 떠돌이 선원들을 골라서 말이야. 그리고는 갑자기 '폐병으로 죽었다'고 하지... 그 다음은 네가 알아서 생각해 봐라...\n";
			link.l1 = "결국 후안도 인간이구나! 그 자에 대해 뭘 알고 있지?";
			link.l1.go = "Sergio_11";
		break;
		
		case "Sergio_11":
			dialog.text = "조금 알지. 예전엔 베르베르 해적들이랑 모로코에서 더러운 짓을 하곤 했어. 가끔 여기 들를 때마다 그 시절 얘기를 늘어놓는 걸 좋아하지. 거기서 별명도 얻었지, '소모증'이라고. 그 별명의 유래는 생각하고 싶지도 않아\n매달 여기 와서 죄수들을 전부 배에 싣고 가.";
			link.l1 = "'소모병!' 그리고 나보고 냉소적이라고 했지! 그래서 그랬던 거군... 네 그 나리 사령관, 진짜 재수 없는 놈이야!";
			link.l1.go = "Sergio_12";
		break;
		
		case "Sergio_12":
			dialog.text = "내가 알기로는, 실종된 죄수들 중 누군가가 필요하다는 거지? 아니면 이 이야기를 어떻게 알겠어, 맞지? 그렇다면 서둘러야 할 거야: 오늘 밤이 이번 달 마지막 밤이니까. 나는 이미 세 명이 더 죽었다는 서류에 서명했어, 그리고 후안은 그들을 인도받는 대로 내일 정오 전에 닻을 올릴 거야!\n";
			link.l1 = "무엇에 서명한 거지? 무슨 말인지 잘 모르겠는데...";
			link.l1.go = "Sergio_13";
		break;
		
		case "Sergio_13":
			dialog.text = "몇 달 동안이나 계속해 온 일이니 어쩔 수 없었지! 그래서 이걸 막으려고 여기 온 거야. 닥터 피네로가 어떻게 죽었는지 알아? 나보다 먼저 죄수들을 치료했던 그 사람이 말이야?";
			link.l1 = "그가 폐병으로 죽었다고 들은 것 같은데, 맞지? 그래서 어쩔 수 없이 이렇게 된 거군. 그건 이해가 가. 그런데 왜 아무도 이 일에 대해 당국에 연락하지 않았지?";
			link.l1.go = "Sergio_14";
		break;
		
		case "Sergio_14":
			dialog.text = "이걸 누가 믿겠어? 난 아무 증거도 없고, 죄수들을 지키라는 군인들도 두둑이 돈을 받아서, 카리브족에게 사람을 식사거리로 팔아넘겨도 신경도 안 쓸 거야\n죄수 따위 아무도 신경 안 써, 그게 바로 사령관 놈의 비장의 수지. 하지만 후안만 없애면, 적어도 당분간은 이 짓을 막을 수 있어!";
			link.l1 = "내가 알기로는, 저기 육지에 있던 놈들이 그 자의 부하들이었지, 안 그래? 그를 어떻게 찾을 수 있지?";
			link.l1.go = "Sergio_15";
		break;
		
		case "Sergio_15":
			dialog.text = "네가 질문을 하도 해서 누군가의 눈에 띈 것 같군... 내가 더 조심하라고 했잖아! 하지만 지금 그게 중요한 건 아니야. 후안의 배에 대해서는 나도 아는 게 없어. 하지만 죄수들은 항상 섬 북쪽에 있는 갈레라 곶으로 보내지. 아마 노예상 배도 근처에 있을 테니 따라잡을 수 있을 거야. 그의 심부름꾼들이 오늘, 그가 내일 정오에 떠날 거라고 하더군.";
			if (!CheckCharacterItem(pchar, "letter_consumption"))
			{
				link.l1 = "고맙네, Sergio, 자네는 진정한 장교이자 명예로운 사나이야. 지금 당장 닻을 올려서 그 더러운 배를 찾아내겠네. 자네는 수색이 시작되기 전에 요새로 돌아가야 하네.";
				link.l1.go = "Sergio_16";
			}
			else
			{
				link.l1 = "음, 이제 내가 알아야 할 건 다 들었군. 저 '컨섬션'을 신세계 전체에서 찾아 헤매고 싶지 않다면 지금 당장 닻을 올려야겠어. 그동안 너는 이걸 좀 살펴봐.";
				link.l1.go = "Sergio_17";
			}
		break;
		
		case "Sergio_16":
			dialog.text = "행운을 빌어요, 선장님! 나 걱정은 말고, 가장 중요한 건 이 일을 적어도 잠시라도 막는 거예요. 행운을 빌겠소!";
			link.l1 = "내 대포야말로 병과 악을 고치는 최고의 약이지. 맹세컨대, 모든 포로들은 새벽 전에 육지에 내리게 될 거고, 후안의 배는 바닷속에 가라앉을 거다!";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_17":
			RemoveItems(PChar, "letter_consumption", 1);
			Log_Info("You have given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "무엇이지? 여기 대령의 이름과 'J'라는 모노그램이 있군? 믿을 수가 없어! 이걸 어디서 구했나?";
			link.l1 = "그건 모르는 게 좋겠지만, 네가 그걸 가장 잘 활용할 거라 믿는다.";
			link.l1.go = "Sergio_18";
		break;
		
		case "Sergio_18":
			dialog.text = "맹세코, 반드시 그렇게 하겠소! 이달이 끝나기 전에 대령은 교수대에 오를 것이오! 내가 직접 처리하겠소!";
			link.l1 = "그 자는 이번이 처음도 아닐 테니 징계로 끝날 것 같아 걱정이오. 차라리 그 놈을 쏴버리는 게 낫지 않을까? 아주 효과적인 방법이긴 하니까... 이제 가봐야겠소 - '컨섬션'을 오래 기다리게 하고 싶진 않으니.";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_19":
			DialogExit();
			AddQuestRecord("Consumption", "11");
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption5.win_condition.l1 = "location";
			pchar.quest.Consumption5.win_condition.l1.location = "Trinidad";
			pchar.quest.Consumption5.function = "Consumption_CreateJuan";
			pchar.quest.Consumption6.win_condition.l1 = "HardHour";
			pchar.quest.Consumption6.win_condition.l1.hour = 13;
			pchar.quest.Consumption6.function = "Consumption_FailJuan";
			// Сержио теперь наш друг и будет торговать смолами
			SetFunctionTimerCondition("Oil_PrepareSergio", 0, 0, 20, false); // таймер
		break;
		
		// генератор торговли смолами
		case "Sergio_20":
			dialog.text = "오, 이런 행운이! 나리 "+GetFullName(pchar)+"! 다시 보게 되어 정말 반갑구나!";
			link.l1 = "세르히오 나리! 여기서 뵐 줄은 몰랐습니다! 잘 지내십니까? 그 훌륭한 옛 사령관님은 어떻게 지내시나요?";
			link.l1.go = "Sergio_21";
		break;
		
		case "Sergio_21":
			dialog.text = "나는 괜찮아, 그리고 사령관 나리는 로스-테케스 광산으로 갔어 - 후안 컨섬션과 짠 더러운 계략이 들통났거든.";
			link.l1 = "지뢰라고?! 이런 맙소사! 저 자식에게 정의가 실현될 줄은 꿈에도 몰랐는데...";
			link.l1.go = "Sergio_22";
		break;
		
		case "Sergio_22":
			dialog.text = "아, 그랬으면 좋겠지만, 선장님... 그는 그냥 전출되고 강등만 당했소. 지금은 주둔지에서 복무 중이고, 장교 계급도 박탈당하지 않았소. 뭐, 적어도 산호세는 이 쓰레기를 치웠으니 다행이오.";
			link.l1 = "음, 지금까지는 괜찮군. 하지만 더 기대했었지.";
			link.l1.go = "Sergio_23";
		break;
		
		case "Sergio_23":
			dialog.text = "나도 그래... 하지만 그 쓰레기는 잊자. 그놈은 말할 가치도 없어. 나리, 당신 배가 곧 항구에 들어온다는 소식을 듣자마자 나는 서둘러 부두로 달려왔소. 당신에게 제안할 거래가 있소.";
			link.l1 = "정말이야? 듣고 있어.";
			link.l1.go = "Sergio_24";
		break;
		
		case "Sergio_24":
			dialog.text = "선장님, 당신은 믿을 만한 사람처럼 보입니다. 또 한 가지 아주 중요한 점은, 당신이 "+GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"")+" 그리고 이제 당신만의 배도 있군. 거래 협정을 맺자고 제안하지.";
			link.l1 = "괜찮게 들리는데! 무슨 합의인데?";
			link.l1.go = "Sergio_25";
		break;
		
		case "Sergio_25":
			dialog.text = "이 얘기는 다른 데서 하는 게 좋겠어 – 등대지기 오두막에서 말이야. 그는 내 오랜 친구라 믿을 수 있지. 오늘이나 내일 산호세 등대로 와. 거기서 기다리고 있겠네. 내 제안이 아주 흥미로울 거라고 확신하네!";
			link.l1 = "알겠소, Sergio 나리. 거기서 뵙겠소!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Oil_SergioRuntoMayak");
		break;
		
		case "Sergio_26":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Oil_SetSergioToMayakOver.over = "yes"; //снять прерывание
			dialog.text = "또 오셨군, 나리. 이 일에 대해 설명해 드리지. ";
			link.l1 = "듣고 있어. ";
			link.l1.go = "Sergio_27";
		break;
		
		case "Sergio_27":
			dialog.text = "이미 알다시피, 나는 군인일 뿐만 아니라 의사이기도 하오. 왜냐고? 나는 교양 있는 사람이기 때문이오. 내 교육 덕분에 여기서 여자나 술에 시간을 허비하지 않았지. 대신 여러 차례 탐험을 조직했고, 이 근처에서 송진 매장지를 발견하는 데 성공했소\n이건 전략적으로 매우 중요한 자원이오. 이 섬은 튼튼하고 오래가는 선박을 만드는 데 쓰이는 특별한 송진을 찾을 수 있는 유일한 곳이오\n총독과 지휘관이 내게 송진 전부를 스페인 해군에 팔라고 명령했소\n문제는, 그들이 시가의 절반밖에 주지 않고, 나는 다른 데 팔 수도 없다는 거요. 그래서 자네에게 이 송진을 살 기회를 주겠소. 매우 중요한 상품이고, 구하기도 무척 어렵소.";
			link.l1 = "우리 합의 조건이 뭐지? ";
			link.l1.go = "Sergio_28";
		break;
		
		case "Sergio_28":
			dialog.text = "내 계산에 따르면, 한 달에 60통까지는 의심받지 않고 모을 수 있어. 거래하자고 – 매달 5일에 이 등대에 와서 내 친구랑 한잔할 거야. 송진을 사고 싶으면 같이 오면 돼. 한 통에 금화 10두블룬이야.\n전량 한꺼번에 계산하고 가져가. 강요는 안 해, 네 선택이야. 자, 거래하는 거지?";
			link.l1 = "내 생각엔 이거 완전 끝내주는 거래 같은데! 물론이지, 거래야!";
			link.l1.go = "Sergio_29";
		break;
		
		case "Sergio_29":
			dialog.text = "훌륭하군. 그럼 매달 5일마다 나는 내 오랜 친구인 관리인과 함께 카나리아 와인 한 병을 마시며 그대가 오기를 기다리겠소.";
			link.l1 = "좋아. 그렇게 하자.";
			link.l1.go = "Sergio_30";
		break;
		
		case "Sergio_30":
			dialog.text = "우리가 합의하게 되어 기쁘군. 또 보자, 선장!";
			link.l1 = "수지 장사에 행운을 빌지, 나리!";
			link.l1.go = "Sergio_31";
		break;
		
		case "Sergio_31":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			pchar.questTemp.OilTrade = "true";
			pchar.quest.Oil_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.Oil_fail.win_condition.l1.character = "Sergio";
			pchar.quest.Oil_fail.function = "Oil_TradeFail";
			AddQuestRecordInfo("Unique_Goods", "4");
		break;
		
		case "oil_trade":
			dialog.text = "안녕하시오, 선장 나리! 수지 한 통 받으러 오신 거겠지.";
			link.l1 = "맞아요, Sergio 나리. 다 준비됐습니까?";
			link.l1.go = "oil_trade_1";
			link.l2 = "세르히오 나리, 지금은 거래할 기분이 아니오. 나중에 하도록 하지.";
			link.l2.go = "oil_trade_exit";
		break;
		
		case "oil_trade_exit":
			DialogExit();
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "oil_trade_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeOil"))
			{
				dialog.text = "그래. 2550두블론 가지고 있나?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "물론이지. 여기 있어.";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "운이 없군! 돈은 내 배에 두고 왔어. 금방 가져올게!";
					link.l1.go = "oil_trade_exit";
				}
			}
			else
			{
				dialog.text = "그래. 지금 육백 두블론 가지고 있나?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "물론이지. 여기 있어.";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "운이 없군! 돈을 내 배에 두고 왔어. 금방 가져올게!";
					link.l1.go = "oil_trade_exit";
				}
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && !CheckAttribute(pchar, "questTemp.SergioOilBlock")) // увеличить объём поставок смолами
			{
				link.l4 = "세르히오 나리, 송진을 더 사고 싶소. 다섯 배쯤 더 큰 양으로도 공급해 줄 수 있겠소?";
				link.l4.go = "UpgradeOil";
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && CheckAttribute(pchar, "questTemp.SergioOilPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок смолами, если в первый раз не принесли
			{
				link.l4 = "여기 있습니다, 약속대로, Sergio 나리, 요청하신 삼천 두블룬입니다.\n당신의 선견지명과 나의 투자라면 이 사업이 우리 둘 모두에게 상당한 이익을 가져다줄 것이라 확신합니다.";
				link.l4.go = "UpgradeOil_Agreed";
			}
		break;
		
		case "oil_trade_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) RemoveDublonsFromPCharTotal(2550);
			else RemoveDublonsFromPCharTotal(600);
			PlaySound("interface\important_item.wav");
			dialog.text = "당신과 거래하게 되어 기쁩니다, 선장님. 내 사람들이 당신 배에 통을 싣는 걸 도와줄 겁니다.";
			link.l1 = "감사합니다!";
			link.l1.go = "oil_trade_3";
		break;
		
		case "oil_trade_3":
			dialog.text = "거래는 여전히 유효하다. 또 한 번 물건이 필요하면 한 달 뒤에 다시 오도록 하라.";
			link.l1 = "알겠어, Sergio. 또 보자.";
			link.l1.go = "oil_trade_4";
		break;
		
		case "oil_trade_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) AddCharacterGoods(pchar, GOOD_OIL, 300);
			else AddCharacterGoods(pchar, GOOD_OIL, 60);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.SergioOil = sti(pchar.questTemp.SergioOil) + 1; // счётчик покупок
		break;
		
		case "UpgradeOil":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Señor"+GetSexPhrase("","ita")+", 자네가 송진을 더 많이 사려는 걸 보니 우리 사업을 신뢰한다는 뜻이겠지. 하지만 한 가지 문제가 있네\n물량이 늘어나면 섬 당국의 눈에 띌 위험도 커지고, 이런 화물을 관리하려면 사람과 보안 조치가 필요한데, 솔직히 그게 싸지 않네. 만약 자네가 일회성으로 삼천 두블론을 추가로 지불할 의향이 있다면, 내가 믿을 만한 사람들을 고용해서 화물을 지키고 정보 유출도 막을 수 있지. 그러면 우리 노선이 더 안전해지고, 매달 송진 삼백 통을 공급해 줄 수 있네. 자네의 투자를 보상하기 위해 앞으로 모든 화물에 대해 도매상으로서 15퍼센트 할인도 제공하겠네.";
				link.l1 = "화물을 안전하게 지키는 데 삼천 두블론이라니? 세르히오 나리, 솔직히 말해서 이 가격은 믿기 힘들군 – 마치 송진 화물 하나 지키는 게 아니라 에스코리알에서 음모라도 꾸미자는 것처럼 들리오!";
				link.l1.go = "UpgradeOil_1";
				Notification_Skill(true, 80, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Señor"+GetSexPhrase("","ita")+", 네 관심은 고맙지만, 이런 큰 거래는 경험과 신중함이 필요하지. 솔직히 말해서, 네가 아직 이런 규모의 거래를 감당할 만큼 무역 실력이 높지 않아. 좀 더 경험을 쌓고, 대형 선적을 준비할 수 있을 때 다시 오도록 해라. 그러면 그때 가서 제대로 이야기해 볼 수 있겠지.";
				link.l1 = "좋소. 이 문제는 나중에 다시 다루겠소.";
				link.l1.go = "oil_trade_exit";
				Notification_Skill(false, 80, SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeOil_1":
			dialog.text = "Señor"+GetSexPhrase("","ita")+", 네 걱정은 이해해. 하지만 알다시피 보안이란 절대 싸지 않아, 특히 이렇게 희귀한 물건일수록 더 그렇지. 게다가 나는 정보 유출도 절대 없다고 보장할 뿐만 아니라, 시간이 지나면 네 투자도 보상할 수 있을 만큼 할인까지 해주고 있어. 이 정도면 합리적인 타협 아니겠어?";
			link.l1 = "인정하지. 우리 업계에서 신뢰와 비밀은 값비싼 것이고, 할인 덕분에 거래가 좀 더 매력적으로 보이긴 해. \n하지만 삼천 두블룬은 너무 많은 금액이야. 조금 깎아줄 수는 없겠나?";
			link.l1.go = "UpgradeOil_2";
		break;
		
		case "UpgradeOil_2":
			dialog.text = "유감이지만, 이런 일에선 어중간하게 해선 안 되오. 완전히 보호하든가, 아니면 모든 걸 걸고 위험을 감수해야 하오. 금액은 변함없으며, 오직 이렇게 해야만 내가 신뢰와 비밀을 보장할 수 있소. 왕실 함대 전체가 먼저 나를, 그 다음엔 자네를 쫓는 꼴을 원치 않을 테지?\n";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "좋소, 살도 나리, 설득당했소. 안전과 신뢰는 그만한 값어치가 있지. 삼천 두블룬이오. 여기 있소.";
				link.l1.go = "UpgradeOil_Agreed";
			}
			link.l2 = "Saldo 나리, 당신의 조치가 필요하다는 점은 납득했습니다. 하지만 삼천 두블룬은 상당한 금액이고, 지금은 그 돈이 없습니다. 필요한 금액을 모을 때까지 기다려야겠군요.";
			link.l2.go = "UpgradeOil_4";
			link.l3 = "그 돈이면 함대 전체와 대륙의 모든 병사들까지도 매수할 수 있겠소. 하물며 송진 한 짐 지키는 경비원쯤이야 말할 것도 없지! 미안하지만, 그런 제안에는 동의할 수 없소. 그냥 지금 있는 그대로, 불필요한 추가 비용 없이 두도록 합시다.";
			link.l3.go = "UpgradeOil_3";
		break;
		
		case "UpgradeOil_Agreed":
			dialog.text = "그렇다면, 나리, 우리 서로 신뢰하는 것 같군. 안심하게. 모든 건 제대로 준비될 거야. 이제 세부사항을 말하자면, 평소처럼 송진 300통이 매달 5일 트리니다드 등대에서 널 기다릴 거야.\n전량을 2550두블론에 살 수 있어.";
			link.l1 = "훌륭하군, Sergio 나리. 실망시키지 마시오.";
			link.l1.go = "UpgradeOil_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "4_1");
			pchar.questTemp.UpgradeOil = true;
			pchar.questTemp.SergioOilBlock = true;
			DeleteAttribute(pchar, "questTemp.SergioOilPotom");
		break;
		
		case "UpgradeOil_Agreed_1":
			dialog.text = "의심하지 마시오, 나리"+GetSexPhrase("","ita")+". 모든 것이 최고의 수준으로 준비될 것이니, 우리의 공동 노력이 결실을 맺을 것이오.";
			link.l1 = "또 보자.";
			link.l1.go = "oil_trade_exit";
		break;
		
		case "UpgradeOil_3":
			DialogExit();
			pchar.questTemp.SergioOilBlock = true;
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "UpgradeOil_4":
			dialog.text = "전액을 마련하면 다시 오시오. 기꺼이 새 거래를 해 주겠소.";
			link.l1 = "좋아.";
			link.l1.go = "oil_trade_exit";
			pchar.questTemp.SergioOilBlock = true;
			pchar.questTemp.SergioOilPotom = true;
		break;
	// <-- генератор смол
		
		case "Juan_abordage":
			dialog.text = "너 도대체 누구야!?";
			link.l1 = "내 이름은 "+GetFullName(pchar)+", 너 말이다, 결핵아, 악마가 널 기다리고 있어 – 네 영혼 곧 가져갈 거다!";
			link.l1.go = "Juan_abordage_1";
		break;
		
		case "Juan_abordage_1":
			if (CheckAttribute(pchar, "questTemp.Consumption.House"))
			{
				dialog.text = "이 배는 곧 폭발할 거야 – 화약고에 이미 도화선이 붙었어 – 우리 둘 다 죽을 필요 없잖아? 칼을 내려놓자. 너는 충분히 빠져나갈 시간이 있을 거고, 나는 바다로 뛰어내릴 거야 – 갈레라 곶이 여기서 침 뱉을 거리밖에 안 돼. 금이 필요하면 가져! 오백 두블론, 바로 현찰로 줄게 – 그리고 넌 날 잊고, 나도 널 잊는 거야! 어때?\n";
				link.l1 = "금? 나는 이 모든 걸 돈 때문에 시작한 게 아니야, 후안. 오직 쓰레기들을 죽이려고 시작했지. 그리고 너야말로 내가 얻은 최고의 보상이다.";
				link.l1.go = "Juan_abordage_2";
				link.l2 = "오백 두블론? 나를 놀리는 거냐, 컨섬션. 네가 여기다 최소 두 배는 숨겨놨을 거라고 본다... 당장 천 두블론 내놓으면 꺼져도 좋다, 아니면...";
				link.l2.go = "Juan_abordage_3";
			}
			else
			{
				dialog.text = "배가 곧 폭발할 테니, 좋은 동행이 생기겠군. 어떻게 생각해?";
				link.l1 = "너 말이 너무 많아, 컨섬션. 요점만 말해!";
				link.l1.go = "Juan_abordage_5";
			}
		break;
		
		case "Juan_abordage_2":
			dialog.text = "우리가 합의를 볼 수도 있었는데... 에이, 됐다!";
			link.l1 = "이 불쌍한 사람들을 감옥에서 끌고 나와 놓고, 그들은 저항도 도망도 할 수 없었지. 너는 겁쟁이야, 컨섬션. 그리고 지금도 겁쟁이로 죽게 될 거다.";
			link.l1.go = "Juan_abordage_5";
		break;
		
		case "Juan_abordage_3":
			dialog.text = "사업 수완이 좋구나, 친구... 자, 이게 내가 가진 전부야. 그렇다고 해도 인생치곤 별거 아니지?";
			link.l1 = "네 목숨은 총알 한 발 값도 안 하니, 내 인생에서 가장 이득 보는 거래로군. 이제 꺼져.";
			link.l1.go = "Juan_abordage_4";
			TakeNItems(pchar, "gold_dublon", 1000);
			Log_Info("You received 1000 doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			OfficersReaction("bad");
			pchar.questTemp.Consumption.TakeMoney = "true"; //атрибут для диалога
		break;
		
		case "Juan_abordage_4":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "ConJuan_AfterFight_1", 10.0);
		break;
		
		case "Juan_abordage_5":
			dialog.text = "모두를 구하고 나까지 죽일 시간은 없겠지, 안 그래? 도화선은 타들어가고 있고, 시간은 점점 줄어들고 있어...";
			link.l1 = "젠장! 이 사람들을 여기서 내보내야 해... 꺼져, 쓰레기들아 – 언젠가는 너희도 대가를 치르게 될 거야!";
			link.l1.go = "Juan_abordage_4";
			link.l2 = "그래도 한번 해볼게...";
			link.l2.go = "Juan_abordage_6";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
			sld = GetCharacter(NPC_GenerateCharacter("ConAndjelo", "citiz_9", "man", "man", 5, SPAIN, -1, true, "quest"));
			sld.name = "Angelo";
			sld.lastname = "";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
		break;
		
		case "Juan_abordage_6":
			//LAi_SetCurHPMax(NPChar);
			//LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("ConJuan_AfterFight_2"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Consumption.KillJuan = "true"; //атрибут для диалога
		break;
		
		case "Waitress":
			dialog.text = "아... 할 말을 잃었군... 이게 무슨 악몽이람!";
			link.l1 = "아아, 나는 아무것도 할 수 없었어. 미안하다, 아가씨. 잘 가.";
			link.l1.go = "Waitress_1";
		break;
		
		case "Waitress_1":
			DialogExit();
			AddQuestRecord("Consumption", "16");
			AddQuestUserData("Consumption", "sSex", GetSexPhrase("",""));
			Consumption_Close();
		break;
		
		case "Waitress_2":
			dialog.text = "믿을 수가 없어! 너... 정말 그를 구한 거야? 어떻게 감사해야 할지 모르겠어.";
			if (CheckAttribute(npchar, "quest.Consumption.sex"))
			{
				link.l1 = "그럴 줄 알았지, 미녀야. 하지만 내 몫은 이제 끝났어 - 아주 작은 일 하나만 남았지.";
				link.l1.go = "Waitress_3";
			}
			link.l2 = "의무가 나를 불렀고, 나는 행동했지. 그게 다야.";
			link.l2.go = "Waitress_5";
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan")) AddQuestRecord("Consumption", "18");
			else AddQuestRecord("Consumption", "17");
		break;
		
		case "Waitress_3":
			dialog.text = "나... 오, 맙소사! 네 말이 맞아. 그를 위해, 내가 약속한 대로... 위층 방으로 올라가. 시간이 많지 않아.";
			link.l1 = "그럼 서두르자!";
			link.l1.go = "Waitress_4";
		break;
		
		case "Waitress_4"://благодарность натурой
			DialogExit();
			LocatorReloadEnterDisable("PortSpein_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("PortSpein_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "PortSpein_tavern_upstairs", "goto", "goto3", "ConsumptionSexWaitress", -1);
			pchar.questTemp.Consumption.Sex = "true";
		break;
		
		case "Waitress_sex":
			dialog.text = "여기 있소, 내 용감한 카발레로! 그리고 내가 뭘 가져왔는지 좀 보시오.";
			link.l1 = "오, 오, 감탄스럽군. 그 체리 와인이나 따자고! 그리고 나서 다른 것도 열어보자... 오늘은 네가 운 좋은 날이니까... 하하!";
			link.l1.go = "Waitress_sex_1";
		break;
		
		case "Waitress_sex_1":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;
		
		case "Waitress_5":
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
			{
				dialog.text = "당신은 진정한 기사요! 카바예로! 자, 모욕으로 받아들이지 말고 받아주시오. 이 돈은 안젤로의 몸값을 위해 모은 것이지만, 이제는 더 이상 중요하지 않소! 제발, 거절하지 말고 받아주시오!";
				link.l1 = "그래, 네 눈은 기억하겠어, 세뇨리타. 고통이 아니라 행복의 눈물로 빛날 때 훨씬 더 아름답거든. 네 선물은 받겠어. 잘 가, 그리고 너와 안젤로에게 행운이 있기를.";
				link.l1.go = "Waitress_6";
				AddMoneyToCharacter(pchar, 5000);
			}
			else
			{
				dialog.text = "너는 진정한 기사야! 카바예로! 모두에게 말할 거야! 나는 너를 영원히 기억할게!";
				link.l1 = "그래, 그리고 나는 네 눈을 기억할 거야, 세뇨리따. 고통이 아닌 행복의 눈물로 빛날 때 훨씬 더 아름답거든. 언제나 행복하길 바라. 안녕!";
				link.l1.go = "Waitress_6";
			}
		break;
		
		case "Waitress_6":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			Consumption_Close();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
