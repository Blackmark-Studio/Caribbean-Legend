// Чарли Книппель - старый артиллерист
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, iTemp, amount;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		//ветка на взятие 2 варианта прохождения - за Англию
		if(CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Eng") && !CheckAttribute(npchar, "quest.HWICTake") && !CheckAttribute(pchar, "questTemp.HWIC.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
		{
			dialog.text = "이봐, 친구, 체인 샷이 내 엉덩이에나 맞을 일이지! 여긴 무슨 일로 왔어?";
			link.l1 = "체인 샷으로 네... 뭐라고? 아, 됐다, 그냥 인사나 하려고 했어.";
			link.l1.go = "exit";
			link.l2 = "안녕하시오, Knippel 나리. 하, 왜 사람들이 그대를 Knippel이라 부르는지 알겠군. 아무튼, 그대가 예전에 영국 해군에서 복무했다는 소문이 있더이다. 내게는 훌륭한 배와 숙련된 선원들이 있소. 나와 내 배를 영국 왕실... 아니, 연방의 봉사에 바치고 싶소. 혹시 조언을 해주거나, 누군가에게 나를 추천해주거나, 아니면 이 일에 도움을 줄 수 있겠소?\n";
			link.l2.go = "Knippel_check";
			break;
		}
		//за Голландию
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "toKnippel")
			{
				dialog.text = "이봐, 친구, 체인 샷은 엉덩이에나 맞으라지! 뭐 하러 여기 온 거야?";
				link.l1 = "안녕하시오, Knippel 나리. 하, 왜 사람들이 그대를 Knippel이라 부르는지 알겠군. 예전에 영국 해군에서 복무했다는 소문이 있던데, 그래서 자네에게 도움을 청하고 싶소...";
				link.l1.go = "Dominica";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "체인 샷은 무슨 놈의 체인 샷이야! 뭐 원하는 거야, 이 친구야?";
			link.l1 = "아니, 아무것도 아니오. 나는 가겠소.";
			link.l1.go = "exit";
			break;
		}
		//за Англию
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
		{
			if (pchar.questTemp.HWIC.Eng == "TakeHollConvoy")
			{
				dialog.text = "이봐, 선장, 은화 수송대가 습격당했다는 소문을 들었어...";
				link.l1 = "정보가 빠르군, Knippel 나리.";
				link.l1.go = "HollConvoy_Check";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SentJons");
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Wait")
			{
				dialog.text = "질문 있나, 선장?";
				link.l1 = "아니, 아무것도 아니오. 나는 가겠소.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Start_main")
			{
				dialog.text = "만나서 반갑소, 선장! 내 상관 리처드 플리트우드가 직접 여기 와서 당신을 만나려 했는데, 어제 저녁에 사고가 있었소... 누가 길 한복판에서 그를 죽이려 했지, 체인 샷이 내 엉덩이에나 맞을 일이군!";
				link.l1 = "불가능해! 경비병들은 도대체 뭐 하고 있었던 거지?";
				link.l1.go = "Fleetwood_house";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "질문 있나, 선장?";
			link.l1 = "아니, 아무것도 아니오. 나는 가겠소.";
			link.l1.go = "exit";
		break;
		}
			dialog.text = "이봐, 체인 샷은 집어치워! 뭐 때문에 여기 온 거야?";
			link.l1 = "안녕, 그냥 들렀어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------за Голландию--------------------------------------------------	
		case "Dominica":
			dialog.text = "아, 그런가? 그런데 오래 전에 뭍에 내려앉은 늙은 뱃사람이 너한테 어떻게 도움이 될 수 있겠냐, 이 친구?";
			link.l1 = "봐... 나는 그냥 평범한 선장일 뿐이고 마르티니크와 퀴라소 사이를 정기적으로 오가며 항해하지. 마르티니크에서 멀지 않은 곳에서 유령선에게 두 번이나 공격당했어... 그런데 말이지, 그 배는 파타 모르가나도 아니고 플라잉 더치맨도 아니야. 평범한 포탄으로도 그 배의 돛을 찢을 수 있었거든!";
			link.l1.go = "Dominica_1";			
		break;
		
		case "Dominica_1":
			dialog.text = "그런가? 유령선이 탄환에 돛을 잃다니, 참으로 드문 일이군, 내 뼈가 오싹하네...";
			link.l1 = "우리가 살아남을 수 있었던 건 내 배가 바람을 맞받아 달릴 수 있었기 때문이오. 지난번에는 선체를 가볍게 하려고 화물을 전부 바다에 던져야 했소... 그 손해가 얼마나 큰지 상상이나 가시오? 가슴이 미어지오!";
			link.l1.go = "Dominica_2";			
		break;
		
		case "Dominica_2":
			dialog.text = "이런 젠장, 선장...";
			link.l1 = "쿠라사오의 총독 마티아스 벡은 내 불평을 그냥 무시해 버렸어. 유령선 이야기는 헛소리라 하고, 내 감시병들이 그저 그로그에 취했을 뿐이라고 하더군. 마르티니크의 총독은 순찰대를 보내겠다고 약속했지만, 그의 눈빛은 아무것도 할 생각이 없다는 걸 말해 주었지. 그 빌어먹을 해적 '유령'이 근처를 어슬렁거리는 동안에는 마르티니크로 돌아갈 수도 없어. 내 배도 작고 선원도 적어서, 그놈과 세 번째로 마주치면 살아남지 못할 것 같아...\n";
			link.l1.go = "Dominica_3";			
		break;
		
		case "Dominica_3":
			dialog.text = "정말 안타까운 일이군, 친구야. 그런데 내가 어떻게 도와줄까?";
			link.l1 = "이 근처 선원들에게 들으니, 세인트 존스에 리처드 플리트우드라는 선장이 있는데 그 사람도 이 유령선을 쫓았다고 하더군. 나는 그를 직접 알지는 않으니, 이 이야기를 자네에게 하는 거야. 혹시 내 불운담을 그에게 전해줄 수 있겠나? 분명 그 더러운 해적이 도미니카의 거친 해안 어딘가에 숨어서 바베이도스와 마르티니크 사이를 약탈하고 있을 게야.";
			link.l1.go = "Dominica_4";			
		break;
		
		case "Dominica_4":
			dialog.text = "바베이도스와 마르티니크 사이? 하! 살찐 부자 무역로지. 딱 그 배때지 쥐새끼가 할 짓 같군.";
			link.l1 = "나는 부자도 아니고 뚱뚱하지도 않으며, 해군 선장에게 군사 호위를 부탁할 뇌물도 없어. 하지만 플리트우드 나리께서 이미 이 배수구 쥐를 쫓고 계시다면, 그분께 이 '플라잉 더치맨'을 어디서 찾을 수 있는지 알려주실 수 있겠소?";
			link.l1.go = "Dominica_5";			
		break;
		
		case "Dominica_5":
			dialog.text = "여기 와서 잘했군. 네 이야기는 내가 적임자들에게 전하겠네, 내 간을 쇠사슬 탄환으로 쏴버려도 좋아! 곧 마르티니크와 다시 교역할 수 있을 거야.";
			link.l1 = "신께서 그대의 말을 들어주시길 바라오! 내 말을 들어줘서 고맙네, Charlie. 정말 좋은 결과가 있기를 바라오. 안녕히 가게, 그리고 쇄탄을 잘 피하게나!";
			link.l1.go = "Dominica_6";			
		break;
		
		case "Dominica_6":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toDominica";
			AddQuestRecord("Holl_Gambit", "1-17");
			pchar.quest.toDominica.win_condition.l1 = "location";
			pchar.quest.toDominica.win_condition.l1.location = "Dominica";
			pchar.quest.toDominica.function = "PrepareToFleetwoodAttack";
			DelMapQuestMarkShore("Shore1");
			DelMapQuestMarkShore("Shore2");
			AddMapQuestMarkIsland("Dominica", true);
		break;

//----------------------------------------------за Англию--------------------------------------------------	
		case "Knippel_check"://начинаем проверять нашего ГГ по всем статьям
			if(makeint(PChar.reputation.nobility) < 48)//низкая репа
			{
				Notification_Reputation(false, 48, "low");
				PlaySound("Voice\English\hambit\Charlie Knippel-04.wav");
				dialog.text = "명랑한 영국이 무슨 도둑놈들한테 신세를 지겠냐, 체인 샷 같은 소리 하네! 공손하게 말하자면, 좆까고 꺼져라.";
				link.l1 = "이봐, 이봐, 친구, 입 조심해라 안 그러면 내가 꿰매 버릴 거니까!";
				link.l1.go = "exit";
				break;
			}
			else
			{
				Notification_Reputation(true, 48, "low");
			}
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 30)//низкая навигация
			{
				dialog.text = "선장님, 솔직히 말할게요. 지금은 젖은 자루에서도 못 빠져나올 실력이에요. 항해술 좀 더 익히고 다시 오시죠, 알겠어요?";
				// belamour legendary edition покажем критерии  -->
				notification("Skill Check Failed (30)", SKILL_SAILING);
				//<--
				dialog.text = "카온, 우리 함대에는 풋내기가 아니라 경험 많은 선장이 필요하다. 항해술을 제대로 익히고 나서 다시 오도록 해.";							 
				link.l1 = "그렇군... 그럼 나중에 보겠소.";
				link.l1.go = "exit";
				break;
			}
			else
			{
				notification("Skill Check Passed", SKILL_SAILING);
			}
			dialog.text = "이봐, 딱 맞춰 왔군, 선장. 체인 샷은 내 엉덩이에나 써라! 리처드는 이 위험한 일에 누구를 믿어야 할지 몰라서, 심지어 거절할까도 고민했지... 그러니 오늘은 기회의 새들이 네 귀에 달콤하게 노래하고 있는 거다. 우리 기준에 맞게 해낸다면, 내가 아주 중요한 분께 너를 추천해주지. 이 일 감당할 만큼 배짱은 있냐?";
			link.l1 = "포도탄을 가득 실었소, Knippel 나리.";
			link.l1.go = "Knippel_task";
		break;
		
		case "Knippel_task"://первое задание
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Lucas"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "아하! 기분이 좋아 보이는군, 선장! 곧 불꽃이 뒤따를 거야! 이제 잘 들어. 네덜란드 서인도 회사의 은화 함대가 하루 이틀 전에 퀴라소의 빌렘스타트를 떠났어. 지금 필립스버그로 항해 중이지. 이번엔 함대에 배가 몇 척 안 돼. 은을 실은 갤리언 한 척과 호위선 두 척뿐이야. 은화 함대를 가로채서, 은을 실은 이스트 갤리언을 포획해 앤티가로 끌고 와. 호위선들은 가라앉혀도 돼, 쓸모없는 놈들이니까. 체인 샷으로 간을 갈겨버려, 야르!";
			link.l1 = "저들의 날도 얼마 남지 않았다.";
			link.l1.go = "Knippel_task_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_task_1":
			dialog.text = "조언 하나 하지, 선장. 큐라소에서 신트마르턴으로 가는 교역로는 세인트 크리스토퍼 해안에서 멀지 않아. 거기서 매복을 준비하는 게 좋겠어. 이번 작전을 위해 너와 네 배를 잘 준비해둬라. 서인도 회사랑 엮이는 건 예쁜 아가씨랑 산책하는 일 따위가 아니거든.";
			link.l1 = "무슨 일에 휘말리는지 알고 있소. 그래도 솔직하게 말해줘서 고맙소, Knippel 나리. 네덜란드 은화를 가지고 돌아오겠소.";
			link.l1.go = "Knippel_task_2";			
		break;
		
		case "Knippel_task_2":
			DialogExit();
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Eng = "true";//признак, что английка уже бралась
			HWICSilverConvoyInWorld();
			AddQuestRecord("Holl_Gambit", "2-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила ,чтобы вышел из архива. 																				   
			pchar.questTemp.HWIC.Eng = "begin";
			SetFunctionTimerCondition("HollConvoy_Over", 0, 0, 15, false);
		break;
		
		case "HollConvoy_Check"://начинаем проверять
			int iHal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_GALEON_L) iHal++;
				}
			}//признак наличия ТГ в компаньонах
			if (iHal > 0)
			{
				amount = sti(pchar.questTemp.HWIC.Eng.SlvQty) - GetSquadronGoods(pchar, GOOD_SILVER);
				if (amount <= 0)
				{
					dialog.text = "무슨 일이 있었는지 말할 필요 없어, 선장. 세관원이 네 배를 검사하는 동안 이미 다 들었거든... 아주 잘했어, 선장. 정말 훌륭해! 쉽지 않았다고 하더군, 체인 샷이 뭐 대수냐!";
					link.l1 = "인정받으니 기분이 좋군.";
					link.l1.go = "HollConvoy_complete";
				}
				else
				{
					dialog.text = "무슨 일이 있었는지 말할 필요 없어. 네 배를 세관원이 검사하는 동안 이미 전부 보고받았으니까... 은화를 다 가져오지 못했지, 체인 샷 핑계는 집어치워! 그 동인도 회사 배에 은화가 얼마 있었는지, 페소 단위까지 내가 다 알고 있다. 이번 임무의 목적은 네 전투 실력뿐 아니라 정직함도 시험하는 데 있었어. 그런데 그 정직함에서 넌 낙제했다. 내 집에서 당장 꺼져, 풋내기!";
					link.l1 = "그럼 지옥이나 가라, 멍청이 놈아!";
					link.l1.go = "HollConvoy_fail";
				}
			}
			else
			{
				dialog.text = "이봐, 친구. 네 함대에 네덜란드 동인도 상선이 안 보이는데. 내가 그 배를 노획해서 여기로 끌고 오라고 했잖아. 그런데 네가 그 배를 팔아넘기고 돈을 혼자 챙기려 한 거지, 응?";
				link.l1 = "잠깐, 내가 배도 가져와야 했다고? 난 은만 원한 줄 알았는데.";
				link.l1.go = "HollConvoy_noShip";
			}
		break;
		
		case "HollConvoy_noShip":
			dialog.text = "찰리 크니펠을 바보로 아는 놈은 없어! 내가 너한테 뭐라고 했고, 뭐라고 안 했는지 똑똑히 기억하고 있지. 너는 우리 거래 조건을 어겼고, 정직한 영국인은 너 같은 자와 일하지 않아. 여기에는 악당이 설 자리가 없다. 내 집에서 당장 꺼져, 꼬마 선원!";
			link.l1 = "그럼 지옥이나 가라, 멍청이 놈!";
			link.l1.go = "HollConvoy_fail";
		break;
		
		case "HollConvoy_fail":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-3");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Eng");//зачищаем для возможности отката к голландскому варианту
			pchar.questTemp.HWIC.Fail2 = "true";
		break;
		
		case "HollConvoy_complete":
			dialog.text = "내일 나를 찾아오면 내 후원자를 소개해 주지. 그분이 자네 실력에 걸맞은 더 좋은 일거리를 줄 걸세. 게다가... 금전적 보상도 챙겨줄 테니. 닻 올려라!";
			link.l1 = "알겠소, Knippel 나리. 내일 여기 있겠소.";
			link.l1.go = "exit";
			npchar.greeting = "knippel_2";
			AddDialogExitQuestFunction("HollConvoy_Remove");
			AddQuestRecord("Holl_Gambit", "2-4");
			SetTimerFunction("EnglandGambit_2_ZadanieStart", 0, 0, 1);
			pchar.questTemp.HWIC.Eng = "Wait";
			AddSimpleRumourCity("They say that you captured a Dutch ship filled with silver. Well done! You are a valiant sailor, captain! Godspeed!", "SentJons", 10, 3, "");
		break;
		
		case "Fleetwood_house":
			dialog.text = "나도 똑같은 생각을 하고 있었어... 어떤 놈이 플리트우드 선장 눈에 후추가루를 뿌리고, 리처드가 칼을 뽑기도 전에 가슴을 찔렀지. 그 살인자는 한 번에 선장을 끝장내려고 했던 거야, 또 찌를 시간은 없으니까. 하지만 실패했지. 플리트우드 선장은 항상 코트 안에 흉갑을 입고 다니거든\n그 더러운 놈, 체인 샷으로 간을 맞추고는 도망쳐서 숨었어. 도시 안에 친구들이 있는 것 같더라. 선장이 기억하는 유일한 특징은 그 암살자가 외눈이라는 거야. 하지만 별 도움은 안 될 거야, 요즘 부두에 그런 외눈박이 놈들이 넘쳐나거든\n리처드는 피를 너무 많이 흘렸고, 후추 때문에 눈이 심하게 상해서 지금 거의 앞을 못 볼 지경이야...";
			link.l1 = "갈아낸 후추라니? 누군가를 눈멀게 하기에 꽤 비싼 방법이군. 플리트우드가 정말 누군가의 심기를 건드린 모양이야. 네 선장에게 유감이네. 공격자를 찾는 수사는 뭔가 성과가 있었나?";
			link.l1.go = "Fleetwood_house_1";
		break;
		
		case "Fleetwood_house_1":
			dialog.text = "플리트우드 선장의 해병대가 마을 전체랑 근처 만까지 샅샅이 뒤졌는데, 아무것도 못 찾았어, 목에 체인샷이나 맞으라지! 공격 직후에 그 놈을 못 잡았다면, 이제는 찾을 가망도 없어. 플리트우드 선장은 원수도 많지... 그래도 선장님, 우리 지휘관께서 그 일에도 불구하고 선장님을 뵙고 싶어 하셔. 지금 자기 집에서 쉬고 계시니까, 같이 가자고. 따라와!";
			link.l1 = "앞장서시오, Knippel 씨.";
			link.l1.go = "Fleetwood_house_2";
		break;
		
		case "Fleetwood_house_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			bDisableFastReload = true;//закроем быстрый переход
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_town", "reload", "houseH1", "OpenTheDoors", -1);
			pchar.quest.Knippel_Outside.win_condition.l1 = "location";
			pchar.quest.Knippel_Outside.win_condition.l1.location = "SentJons_town";
			pchar.quest.Knippel_Outside.function = "Knippel_GoTown";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);
			sld = characterFromId("Fleetwood");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
			AddLandQuestMark(sld, "questmarkmain");
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.money = 110000;
		break;
		
		case "InFleetwoodHouse":
			dialog.text = "플리트우드 선장은 위층 자기 방에 계셔. 그에게 가, 너를 기다리고 있어. 나는 여기 남을게.";
			link.l1 = "알겠소, Knippel 나리. 지금 가는 중이오.";
			link.l1.go = "exit";	
		break;
		
		case "Knippel_ToOfficer":
			dialog.text = "듣시오, 선장... 플리트우드 선장님은 이제 안전하게 보호받고 있소. 그를 공격한 그 개자식에게 복수하는 데 내가 힘을 보태고 싶소. 포술 장교로 내 실력을 제공하겠소. 검술은 별로 자신 없고, 나이도 많아 그럴 힘도 없지만, 상선의 돛대쯤은 천 걸음 밖에서도 날려버릴 수 있소.";
			link.l1 = "그거 한번 보고 싶군. 환영하오, Knippel 나리!";
			link.l1.go = "Knippel_ToOfficer_1";	
		break;
		
		case "Knippel_ToOfficer_1":
			ForceHeroAutolevel(npchar);
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", false);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", false);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", false);//откроем локаторы
			//Книппеля - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 20;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			SetFunctionTimerCondition("GotoBridgetownOver", 0, 0, 30, false);//на все дела - 1 месяц
			AddSimpleRumourCity("They say that Sir Richard Fleetwood himself is indebted in you. You are a very important man in our town, sir", "SentJons", 10, 3, "");
		break;
		
		case "hired":
			dialog.text = "이봐, 선장! 뭐 필요한 거라도 있어?";
			link.l1 = "아니, 아무것도 없어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			if (pchar.questTemp.HWIC.Eng == "MirageFail")
			{
				dialog.text = "넌 완전한 바보구나, 체인 샷은 무슨! 기본적인 임무도 실패했잖아 - '발키리'를 잃지 않고 '미라주'를 포획하라는 거였는데\n우리 선원들은 더 이상 네 지휘 아래에서 일하지 않을 거다. 플리트우드 나리도 우리의 결정을 분명히 찬성할 거야, 그 양반도 우리만큼 멍청이를 싫어하거든.";
				link.l1 = "네 놈이랑 네 주인 다 지옥에나 떨어져라!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "GotoBridgetown" || pchar.questTemp.HWIC.Eng == "SeekVanBerg")
			{
				dialog.text = "너는 완전한 바보야, 체인 샷 같은 소리 하고 있네! 네 개인적인 문제 해결하느라 우리가 너무 많은 시간을 낭비했어\n우리 선원들은 더 이상 너를 따르지 않을 거다. 플리트우드 나리도 우리의 결정을 분명히 찬성할 거야, 그 양반도 우리만큼 바보를 싫어하거든.";
				link.l1 = "네 놈이랑 네 주인 다 지옥에나 떨어져라!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "VanBergFailInWorld")
			{
				dialog.text = "너는 완전한 바보야, 체인 샷은 무슨! '발키리'에서 외로운 상인처럼 행동하라고 했더니, 네가 뭘 했는지 알아? 네 함대로 해적을 겁줘서 쫓아버렸잖아!\n우리는 플리트우드 나리도 우리의 결정을 승인할 거라 확신해. 그 양반도 우리만큼이나 바보를 싫어하거든.";
				link.l1 = "네 놈이랑 네 주인 다 지옥에나 떨어져라!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "MirageTake")
			{
				dialog.text = "넌 완전한 바보야, 체인 샷은 무슨! '미라주'를 잡아서 앤티과로 가는 것 말고 딴 짓 하면서 우리 시간이나 낭비하려고 작정했냐?\n우리 선원들은 더 이상 너 따위 밑에서 일 안 해. 플리트우드 나리도 우리만큼이나 바보를 싫어하니, 우리가 내린 결정에 분명 동의할 거다.";
			link.l1 = "네 놈이랑 네 주인 다 지옥에나 떨어져라!";
			link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_VALCIRIA)//если сам на Валькирии
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "Boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA)
						{
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Eng.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			pchar.questTemp.HWIC.Detector = "eng_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "OnCuracao":
			pchar.quest.HWICEng_toBarbadosOver.over = "yes";//снять прерывание
			dialog.text = "안녕하십니까, 선장님. 다시 뵙게 되어 반갑습니다!";
			link.l1 = "안녕하시오, Knippel 나리. 돈은 준비됐소? 내게 주고, Willemstad로 가서 Abigail을 데려오세. 함께 가겠소?";
			link.l1.go = "OnCuracao_1";	
		break;
		
		case "OnCuracao_1":
			dialog.text = "선장님, 들어보세요... 이제 어디 갈 필요 없어요.";
			link.l1 = "무슨 소리야? 이건 말도 안 돼!";
			link.l1.go = "OnCuracao_2";	
		break;
		
		case "OnCuracao_2":
			dialog.text = "플리트우드 선장에게서 온 편지와 돈을 가져왔소. 하지만 이 돈은 아비게일 아버지에게 주는 게 아니라, 바로 당신을 위한 것이오. 이십만 페소요. 편지를 읽고, 그를 너무 심하게 탓하지는 말아주시오...\n";
			link.l1 = "요즘 도대체 무슨 일이 벌어지고 있는 거야?! 또 불쾌한 소식인가? 편지 내놔!";
			link.l1.go = "OnCuracao_3";	
		break;
		
		case "OnCuracao_3":
			DialogExit();
			NextDiag.CurrentNode = "OnCuracao_4";
			AddMoneyToCharacter(pchar, 200000);
			LAi_SetCitizenType(npchar);
			npchar.lifeday = 1;//ещё денек пусть погуляет по пляжу
			pchar.quest.Holland_ShoreAttack.win_condition.l1 = "location";
			pchar.quest.Holland_ShoreAttack.win_condition.l1.location = "Curacao";
			pchar.quest.Holland_ShoreAttack.function = "CreateHollandShorePatrol";//патруль в прибрежных водах
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", false);//открыть подземелье
			pchar.questTemp.HWIC.Eng = "MerdokMeeteng";
			AddQuestRecordInfo("LetterFromFleetwood", "1");
			AddQuestRecord("Holl_Gambit", "2-23");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "OnCuracao_4":
			dialog.text = "읽어봤어, 선장? 솔직히 말할게. 플리트우드 선장이 한 짓이 부끄럽다, 체인 샷으로 자기... 아, 젠장. 로덴부르크는 아비게일과 리처드의 연애를 알게 되자 분노했지. 순찰대가 퀴라소를 샅샅이 뒤지고 있고, 회사 군함들이 근처 바다를 돌아다니고 있어. 여기서 얼른 빠져나가야 해.\n 선장, 포수 필요해? 나는 사치 필요 없어 - 그냥 평범한 바다 식량만 주기적으로 주면 돼. 검 싸움은 잘 못 해, 나이도 많고. 하지만 상선의 톱갤런트 돛대쯤은 천 걸음 밖에서도 날려버릴 수 있어.";
			link.l1 = "이런, 정말 그걸 해내는 걸 보고 싶군, Knippel 나리. 선원으로 온 걸 환영하네!";
			link.l1.go = "Knippel_hire";
			link.l2 = "처음부터 너희 영국 놈들을 도운 걸 후회한다. 이제는 이 엉망진창에서 어떻게 빠져나가야 할지 모르겠군. 각자 갈 길 가라, 난 더 이상 놀랄 일은 질렸다.";
			link.l2.go = "Knippel_exit";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*200;
			npchar.OfficerWantToGo.DontGo = true;
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 120, 120);
			LAi_SetOfficerType(npchar);
			npchar.greeting = "knippel_hire";
			NextDiag.CurrentNode = "Knippel_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			ForceHeroAutolevel(npchar);
			
			//Sinistra - через 2 месяца стартует личный квест Чарли Книппеля "Длинные тени старых грехов"
			SetTimerCondition("DTSG_Start", 0, 0, 60, false);
		break;
		
		case "Knippel_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
		break;
		
//------------------------------------------------против всех-----------------------------------------------
		case "Knippel_abordage":
			dialog.text = "이봐, 이 쥐새끼야! 왜 이 평화로운 네덜란드 배를 공격한 거냐? 나한텐 값진 물건도 금도 없어, 체인 샷은 무슨 놈의 체인 샷이야!";
			link.l1 = "네덜란드 배라고? 하하! 웃기지 마라, '네덜란드 놈'. 내가 네 브리건틴을 습격한 건 바로 너를 잡으려고였지, 귀여운 찰리. 내 화물칸에 온 걸 환영한다. 어디로 왜 항해하고 있었는지 우리 좀 얘기해 보자고...\n";
			link.l1.go = "Knippel_abordage_1";	
		break;
		
		case "Knippel_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-20");
            pchar.quest.Knippel_DieHard.over = "yes";
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "KnippelPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveKnippelOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Knippel_prisoner":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			dialog.text = "너는 악마다, 해적놈... 네 모든 죄로 지옥불에 타게 될 거다! 끄아악...";
			link.l1 = "진정해, 설교쟁이. 청교도처럼 설교하네. 네 영혼 상태나 먼저 챙기는 게 좋을 거다.";
			link.l1.go = "Knippel_prisoner_1";
		break;
		
		case "Knippel_prisoner_1":
			dialog.text = "무슨 꿍꿍이냐, 이 악당아? 내 지휘관과 그 불쌍한 네덜란드 아가씨에게서 뭘 바라는 거지?";
			link.l1 = "네 일 아니야, Charlie. 이제 너 필요 없어. 일어나.";
			link.l1.go = "Knippel_prisoner_2";	
		break;
		
		case "Knippel_prisoner_2":
			dialog.text = "나를 죽이려고? 너 같은 잡놈한테 딱 어울리군. *퉤* 젠장할 놈!";
			link.l1 = "일어나, Charlie. 마지막 기도나 해.";
			link.l1.go = "Knippel_prisoner_3";	
		break;
		
		case "Knippel_prisoner_3":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_StandUp", "Kill_Knippel", 3.5);
			pchar.quest.RemoveKnippelOver.over = "yes";//снять таймер
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Knippel_officer":
			dialog.text = "이봐, 선장, 체인 샷은 엿이나 먹으라고 해!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "내 간에 대포알 박아 줘, 선장님. 이제 육지에는 절대 발도 들이지 않겠네. 지난번 술집에서 주사위 놀이할 때, 어떤 놈이 주머니 속 동전까지 싹 다 털어갔거든.";
				Link.l1 = "하‑하, 도박으로 다 잃은 거 아냐, "+npchar.name+"? 뭐, 그건 그거고… 얘기 좀 하려 했어. 난 유럽으로 항해하기로 했네 — 남의 배에 승객으로 올라타서 말이지. 언제 돌아올지 모른다. 여기서 날 기다리라고 부탁하진 않을 게다. 그리고 너를 끌고 가지도 않겠네.";
				Link.l1.go = "SharlieEpilog_Knippel_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Knippel 나리, 나는 고대 인디언의 잃어버린 도시 타야살로 갈 생각이오. 분명히 말해두겠소, 이번 여정은 매우 위험할 뿐만 아니라, 아주 특이한 일이 될 것이오 – 저... 마법의 우상을 통해서만 갈 수 있소. 함께하겠소?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Knippel 나리, 배에 대한 전체 보고를 해주시오.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "우리가 항구에 정박할 때마다 특정 물품을 구입해 주었으면 하오.";
				Link.l12.go = "QMASTER_2";
			}
			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "명령에 따라 도착했습니다, 선장님.";
				Link.l2 = "당신에게 몇 가지 명령을 내려야겠소.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Knippel_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "내 명령을 들어라!";
            Link.l1.go = "stay_follow";
			link.l2 = "별거 아니오. 해산하라!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Knippel_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "이런 젠장... 대포들은 멀쩡하오, 터진 건 갈아끼우고 화약도 잘 말려서 안전하게 보관하고 있소. 대체 어떤 보고를 기대하신 거요, 선장? 나는 늙은 포수일 뿐이지, 급사 따위가 아니오. 쇠사슬탄? 웃기지 마시오, 그래도 카리브에서 내가 제일가는 포수라는 건 명심하시오!";
			Link.l1 = "여기서 말싸움할 필요 없소, Knippel 나리, 자네 솜씨는 내가 잘 알지. 급사야 내가 직접 구할 테니 걱정 말게.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "늙은 찰리한테 포갑을 버리고 함교로 올라가란 말이오? 선장, 나는 배를 가라앉히는 놈이지, 푼돈 한 푼에 흥정하는 놈이 아니오. 그리고 분명 우리가 처음 가는 식민지에서부터 사기나 당할 게 뻔하오.";
			link.l1 = "하지만 물론이지, Knippel 나리. 이제 제대로 된 급사부터 찾아봐야겠군.";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "듣고 있소.";
			Link.l1 = "이건 승선에 관한 일이야.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "이건 당신 배에 관한 일이오.";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "잠시 내 함대에서 떨어져 혼자서 운을 시험해 보길 바라네.";
				Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "아직 아무것도 없어.";
			Link.l8.go = "exit";
			break;

		case "Companion_TaskBoarding":
			dialog.Text = "그래서 무엇을 원하시오?";
			Link.l1 = "적선에 올라타지 마라. 너 자신과 선원들부터 챙겨.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "적선에 승선해 주었으면 하오.";
			Link.l2.go = "Companion_TaskBoardingYes";
			break;

		case "Companion_TaskChange":
			dialog.Text = "그래서 무엇을 원하시오?";
			Link.l1 = "나는 네가 승선한 후에 다른 배로 바꾸지 않았으면 하오. 네 배는 너무 소중하니까.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "적선에 올라타면, 그 배가 쓸 만하다 싶으면 네 것으로 가져도 된다.";
			Link.l2.go = "Companion_TaskChangeYes";
			break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "알겠어!";
			Link.l1 = "편히 있으시오.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
			break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "그렇게 하겠습니다.";
			Link.l1 = "편히 있으시오.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
			break;

		case "Companion_TaskChangeNo":
			dialog.Text = "알겠어!";
			Link.l1 = "그렇게 하겠습니다.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
			break;

		case "Companion_TaskChangeYes":
			dialog.Text = "그렇게 하겠습니다.";
			Link.l1 = "편히 있으시오.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
			break;
			//	<========////////////////////////////////////////

		case "stay_follow":
            dialog.Text = "명령이오?";
            Link.l1 = "여기 서 있어!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "나를 따라오고, 뒤처지지 마!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "당신의 화기 탄약 종류를 변경하십시오.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "탄약 종류 선택:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "태도가 바뀌었군!";
            Link.l1 = "해산하라.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "기세가 바뀌었다!";
            Link.l1 = "해산!";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "내가 근무하는 동안 정말 정이 많이 들었소, "+pchar.name+", 그리고 나는 내 선장을 곤경에 빠뜨리지 않아. 필요하다면 지옥까지라도 따라가겠어. 나는 당신 편이야!";
			link.l1 = "고마워요, Knippel 씨! 내 예상이 맞아서 기쁩니다.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "언제 시작할 건데, 젠장 내 눈알!";
			link.l1 = "조금 있다가. 우리도 준비해야 해.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "22");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// Эпилог
		case "SharlieEpilog_Knippel_1":
			dialog.text = "그래, 참으로 안된 일이군… 내 장비에 대포알이 박히다니. 사실은 유럽 보는 것도 나쁘지 않다고 생각하고 있었네.";
			link.l1 = "그런 말을 너한테 들을 줄 몰랐네. 자, '"+GetShipName("Ulysse")+"' 핀네이스에 온 걸 환영한다. 원한다면 우리 옛 친구 리처드 플리트우드를 찾아가 볼 수도 있겠군. 그 친구한테 할 말도 많을 거야.";
			link.l1.go = "SharlieEpilog_Knippel_2";
		break;

		case "SharlieEpilog_Knippel_2":
			dialog.text = "아니오, 각하. 리처드 같은 놈은 지옥에나 가라지. 그의 이름도 듣기 싫고, 그 얼굴 따위는 보기도 싫네.";
			link.l1 = "네 뜻대로 해라, "+npchar.name+" , 네 뜻대로. 우린 2주 후에 출항한다네. 제대로 된 송별 파티를 하려고 해. 너도 꼭 와라.";
			link.l1.go = "SharlieEpilog_Knippel_3";
		break;

		case "SharlieEpilog_Knippel_3":
			dialog.text = "거절한다면 대포알에 내 목이 부러지겠지, 선장!";
			link.l1 = "좋아. 그럼 다른 일 먼저 처리하고 나서 선술집에서 보자고.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Knippel_officer";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			pchar.questTemp.SharlieEpilog_Knippel = true;
			pchar.questTemp.SharlieEpilog_Friends = sti(pchar.questTemp.SharlieEpilog_Friends) + 1;
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("너는 "+GetSexPhrase("도둑이오, 나리! 경비병들, 저 자를 잡아라\n","도둑이다, 저 계집애를 잡아라! 경비병들, 저년을 붙잡아!")+"!!!","저것 좀 봐! 내가 잠깐 한눈판 사이에 내 상자를 뒤지다니! 도둑 잡아라!!!","경비병들! 도둑이야! 저 도둑 잡아라!!!");
			link.l1 = "젠장!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
