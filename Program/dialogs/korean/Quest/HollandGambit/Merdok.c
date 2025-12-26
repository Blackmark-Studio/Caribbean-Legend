// Джон Мердок, он же Йохан ван Мерден, соратник Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		if (!CheckAttribute(pchar, "questTemp.HWIC.Self") && LAi_grp_playeralarm > 0)
		{
			dialog.text = "나리, 지금 한가하게 잡담할 때가 아니오. 주둔군 전체가 자네를 찾고 있소. 어서 빨리 사라지는 게 좋을 거요...";
			link.l1 = "걱정 마시오. 오래 머무르지 않을 것이오.";
			link.l1.go = "exit";
			break;
		}
		// продажа алхимического набора, если провалил гамбит
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && !CheckAttribute(npchar, "quest.alchemy"))
		{
			bOk = (findsubstr(pchar.questTemp.HWIC.Detector, "_fail" , 0) != -1) || (pchar.questTemp.HWIC.Detector == "eng_win_half");
			if (bOk)
			{
				dialog.text = "어서 오시오, 선장. 흥미로운 제안에 관심 있겠소? ";
				link.l1 = "이 근처엔 온갖 사람들이 그런 제안을 하더군. 나는 호기심이 많은 사람이니, 무슨 일인지 말해 보시지? ";
				link.l1.go = "alchemy";
				break;
			}
		}
		// Страж Истины
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok1")
		{
			dialog.text = "안녕하십니까. 제 약방에 오신 것을 환영합니다. 대부분의 질병과 허약함을 치료할 약이 있습니다. 무엇을 드릴까요?";
			link.l1 = "이봐, 존, 네 집 2층에 누가 산다는 소문이 돌고 있어...";
			link.l1.go = "guardoftruth";
			break;
		}
//-----------------------------------------за Голландию------------------------------------------------
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.location.from_sea == "SentJons_town" && pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "좋은 하루입니다. 제 약방에 오신 걸 반갑게 맞이합니다. 대부분의 질병과 증상을 치료할 약이 있습니다. 무엇을 드릴까요?";
				link.l1 = "안녕하십니까, 머독 나리. 저는 루카스 로덴부르크를 대신해 왔습니다. 리처드 플리트우드와 관련된 문제를 논의하라고 저를 보내셨습니다.";
				link.l1.go = "Knippel_exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "안녕하세요. 무슨 문제로 오셨습니까? 기침약도 있고 설사약도 있습니다!";
				link.l1 = "안녕하십니까, 머독 나리. 저는 루카스 로덴부르크를 대신해 왔습니다. 리처드 플리트우드와 관련된 문제를 상의하라고 저를 보냈습니다.";
				link.l1.go = "Knippel";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "KillMerdok")
			{
				dialog.text = "아, 여기 로덴부르크가 고용한 개가 왔군... 에르퀼, 롱웨이, 이리 나와 주겠나?\n이 자를 죽여라!";
				link.l1 = "잠깐, 처방전이 있어!";
				link.l1.go = "Merdok_fight";
				break;
			}
			dialog.text = "좋은 오후입니다. 제 약국에 오셔서 반갑습니다. 대부분의 질병과 허약함을 치료할 약이 있습니다. 무엇을 드릴까요?";
			link.l1 = "지금은 아무 일도 없소, 고맙소. 몸도 아주 괜찮소.";
			link.l1.go = "exit";
			break;
		}
//----------------------------------------------за Англию---------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "MerdokMeeteng")
			{
			dialog.text = "안녕하시오, 불청객이여. 자네는 가면으로 얼굴을 가리지도 않았고, 도둑처럼 보이지도 않는군. 그러니 가난한 약제사에게서 다른 무언가를 얻으려는 것이라 결론내리겠소. 설사약이라도 필요하오?";
			link.l1 = "너에게도 인사하지, 요한 반 메르덴. 에르큘 톤자가 안부를 전하라고 했어. 이름을 아는 것 같군.";
			link.l1.go = "Merdok_talk";
			DelLandQuestMark(npchar);
			break;
			}
//--------------------------------------------против всех--------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "HuntFleetwood")
				{
					dialog.text = "아, 여기 있었군. 그래, 에르퀼을 만났나? ";
					link.l1 = "그래. 우리 합의를 봤네. 존, 나는 에르퀼을 도울 생각이네, 그리고 리처드 플리트우드에 관해 자네에게 물어볼 것이 몇 가지 있네.";
					link.l1.go = "About_Fleetwood";
					break;
				}
				if (GetQuestPastDayParam("questTemp.Wait_Fleetwood") > 6 && pchar.questTemp.HWIC.Self == "WaitFleetwood")
				{
					dialog.text = "안녕하세요! 다시 만나서 반갑습니다, "+pchar.name+"!";
					link.l1 = "안녕, John. Fleetwood에 대해 뭐 알아낸 거 있어?";
					link.l1.go = "About_Fleetwood_9";
					pchar.quest.Wait_FleetwoodOver.over = "yes"; //снять таймер
					break;
				}
				if (pchar.questTemp.HWIC.Self == "HWICSelf_fail")
				{
					dialog.text = "늦었군. 새는 이미 날아가 버렸어. 찰리 크니펠이 빌렘스타트에 다녀와서 리처드를 위해 거기서 여자를 데려왔지. 이제 그들은 하루 이틀 안에 군함대와 함께 영국으로 떠날 거야. 플리트우드는 떠났고, 이 생에서는 다시 볼 일 없을 거다.";
					link.l1 = "젠장. 리처드 일은 완전히 잊고 시간 가는 줄도 몰랐네. 또 보자.";
					link.l1.go = "About_Fleetwood_17";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileOnShip")
				{
					dialog.text = "다시 돌아왔군, "+pchar.name+"! 지금은 줄 게 없어. 플리트우드 소식도 없고, 찰리 크니펠도 아직 퀴라소에서 돌아오지 않았어...";
					link.l1 = "그는 앞으로도 절대 못 올 거다. 그도, 그의 브리건틴도.";
					link.l1.go = "Abigile";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInHouse")
				{
					dialog.text = "아, 손님이 오셨군! 안녕, Charlie! 좋은 오후야, 아가씨!";
					link.l1 = "안녕하세요, John! 제 여성 동행이자 Richard의 약혼녀인 매력적인 Abigail Shneur를 소개하겠습니다.";
					link.l1.go = "Abigile_7_1";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInRoom")
				{
					dialog.text = "목소리 낮춰... 이제 뭐 할 거야?";
					link.l1 = "다음? 차라리 좀 자고 싶지만, 안타깝게도 그럴 시간이 없군. 나는 플리트우드를 그가 숨어 있는 구멍에서 끌어내서, 에르퀼의 일을 끝낼 거야.";
					link.l1.go = "Abigile_9";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "LetterToFleetwood")
				{
					dialog.text = "글 다 썼어? 어디 좀 보자... 이런 맙소사, 찰리, 너 정말 미친놈이구나! 이거 너무 자세하게 쓴 거 아니냐? 아니, 슈뇌르 아가씨 손가락이랑 귀, 얼굴 얘기 말이야? 넌 진짜 이상한 재주가 있네, 그건 확실해. 젠장, 나 토할 것 같잖아!\n";
					link.l1 = "나는 허세 부리는 거야, John. 그 여자애를 죽일 생각은 없어. 손가락 하나쯤 잘라낼 수도 있겠지만... 그 이상은 안 해. 어차피 손가락은 아홉 개나 더 있으니까.";
					link.l1.go = "Abigile_15";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodAgree")
				{
					dialog.text = "잘 됐나? 네 눈을 보니 알겠어 - 해냈구나!";
					link.l1 = "그래. 플리트우드가 내 조건을 받아들였어. 덫이 서서히 닫히고 있지. 이제 기다리기만 하면 돼.";
					link.l1.go = "Abigile_23";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodDied")
				{
					dialog.text = "아, 돌아왔구나, 친구! 무슨 소식이 있나?";
					link.l1 = "플리트우드는 죽었다. 모든 것이 계획대로 진행됐지. 그가 섬에 도착하자, 내가 해변에 매복을 준비해 두었거든. 녀석도 꽤나 저항했지만, 소용없었지. 그 해변에서 살아나온 건 우리 중 한 명뿐이었다.";
					link.l1.go = "Abigile_27";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "MeetTonzag")
				{
					dialog.text = "Alright "+pchar.name+", 당신에게 중대한 제안을 하나 하지. 내가 말하려는 일은 매우 위험하지만, 당신이 플리트우드를 처리한 방식을 보니 충분히 해낼 수 있을 것 같소. 당신은... 까다로운 문제를 해결하는 데 특별한 재능이 있구려.";
					link.l1 = "과찬이군. 계속 말해봐.";
					link.l1.go = "Lucas";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SeekAbiIsland")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "다시 돌아왔군, "+pchar.name+"! 나한테 좋은 소식 있나?";
					link.l1 = "존, 이제부터는 베개 밑에 칼을 두지 않고도 잘 수 있네. 루카스는 더 이상 자네에게 위협이 되지 않아. 그는 체포되어 감금된 상태고, 머지않아 네덜란드로 송환되어 반란, 살인 미수, 그리고 기타 악행들로 재판을 받을 거야.";
					link.l1.go = "Lucas_10";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "다시 보게 되어 반갑소, "+pchar.name+"! 살아 있었군 - 다행이야. 소식은 있나?";
					link.l1 = "그래. 판 베르크는 완전히 끝났어. 네 말대로, 그 자가 나를 끝까지 쫓아와서 가장 불편한 순간에 공격했지. 판 베르크는 만만치 않은 놈이었지만, 결국 내가 그놈을 끝장냈다.";
					link.l1.go = "Final";
					break;
				}
			dialog.text = "다른 필요한 것이 있소?";
			link.l1 = "아니, John, 아무것도 없어. 난 떠난다.";
			link.l1.go = "exit";
			break;
			}
			dialog.text = "좋은 오후입니다. 제 약국에 오신 걸 반갑게 생각합니다. 대부분의 질병과 허약함에 쓸 약이 있습니다. 무엇을 드릴까요?";
			link.l1 = "지금은 아무것도 없습니다, 감사합니다. 몸 상태도 아주 좋습니다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------за Голландию-----------------------------------------------------
		case "Knippel_exit":
			dialog.text = "무슨 말씀을 하시는지 전혀 모르겠소, 나리. 루카스 로덴부르크가 누구요? 나는 네덜란드인들과 아무런 거래도 한 적 없소. 분명 착각하신 게요.";
			link.l1 = "뭐라고? 로덴부르흐 나리가 나를 당신에게 보냈어!";
			link.l1.go = "Knippel_exit_1";
		break;
		
		case "Knippel_exit_1":
			dialog.text = "다시 한 번 말하겠소 - 나는 마인헤르 로덴부르크라는 사람을 전혀 모릅니다. 네덜란드인들과도 거래하지 않소. 내가 이 세상에서 참을 수 없는 건 두 가지뿐이오: 남의 문화를 이해하지 못하는 사람들, 그리고 네덜란드인들. 그러니 약이 필요 없다면, 제발 내 일이나 하게 내버려 두시오.";
			link.l1 = "점점 더 이상해지네...";
			link.l1.go = "exit";
		break;

		case "Knippel":
			dialog.text = "오, 그래... 자네, 로덴부르크 나리 쪽에서 온 건가? 좋아. 말해보게.";
			link.l1 = "플리트우드 선장과 외진 곳에서 만남을 주선해야 하오. 나는 플리트우드 나리가 그토록 잡고 싶어 하는 네덜란드 사략선장 야콥 판 베르흐에게서 '미라주'를 빌렸소. '미라주'가 머지않아 도미니카 해안에 정박할 예정임을 그에게 알리고 싶소. ";
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			dialog.text = "야곱이 자네에게 자기 배를 줬나? 흠, 이제 자네는 '미라주'가 곧 도미니카 해안에 나타날 거라고 플리트우드 나리에게 대신 전해줄 사람이 필요한 거군, 자네가 어떤 사정 때문에 직접 리처드에게 말할 수 없으니 말이야...\n";
			link.l1 = "정확합니다. 로덴부르크 나리가 이 문제를 당신에게 말씀드리라고 추천했습니다.";
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			dialog.text = "이번 경우에는 찰리 크니펠이 당신에게 필요한 인물이오. 플리트우드의 충직한 친구이자... 그의 첩자요. 그와 대화하면서 리처드가 알아야 할 모든 것을 언급하시오. 조심하게, 크니펠은 꽤 단순해 보일 수 있지만, 결코 바보가 아니오.\n그는 해안에서 멀지 않은 작은 오두막에 있을 것이오. 거기서 그를 찾을 수 있을 거요.";
			link.l1 = "알겠습니다. 감사합니다, 머독 나리. 안녕히 계십시오!";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "toKnippel";
			AddQuestRecord("Holl_Gambit", "1-16");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
		break;
		
		case "Merdok_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			sld = characterFromId("Tonzag");
			PlaySound("Voice\English\hambit\Ercule Tongzag-04.wav");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			//а вот и китаец нарисовался
			sld = characterFromId("Longway");
			LAi_SetWarriorType(sld);
			FantomMakeCoolFighter(sld, 18, 40, 40, "blade_08", "pistol1", "bullet", 70);
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayEnemy"))//враг
			{
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, "EnemyFight");
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayFriend"))//друг
			{
				LAi_warrior_DialogEnable(sld, true);
				sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
				sld.dialog.currentnode = "Longway_hire";
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayNeutral")) sld.lifeday = 0;//нейтрал - просто нет
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattle");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//-------------------------------------------------за Англию-----------------------------------------------------
		case "Merdok_talk":
			dialog.text = "정말인가? 나는 그 불쌍한 가스통이 이미 한참 전부터 지옥에서 타고 있을 줄 알았는데.";
			link.l1 = "그럴 수도 있겠지. 하지만 가스통 같은 놈은 분명히 또 없더군. 나는 비밀 섬에 있는 늙은 유대인의 보물 더미에서 그의 머리를 발견했어. 그런데도 그는 너한테 인사를 전하더라. 그리고 우리에게 공통의 적이 있다고도 했지. 바로 로덴부르크 나리야. 톤자가 말하길, 네가 루카스에게 중요한 서류를 가지고 있을지도 모른다던데, 그걸로 그 놈을 퀴라소의 은신처에서 끌어낼 수 있을 거라고 하더군.";
			link.l1.go = "Merdok_talk_1";			
		break;
		
		case "Merdok_talk_1":
			dialog.text = "그가 옳았소. 로덴부르크가 밤잠을 설치는 것도 내 기록보관소 때문이오. 그 자가 아직도 이곳을 떠나지 못하는 이유도 바로 그것이지. 사실, 그는 네덜란드 연합주 본국의 회사 이사회에서 편한 자리를 약속받았소. 그런데 이 기록보관소에는 루카스의 과거와 현재에 관한 흥미로운 정보가 많이 담겨 있기에, 만약 이 사실이 널리 알려진다면 그의 출세 꿈은 산산이 부서질 거요. 그 경우, 그가 바랄 수 있는 최선은 교수형 대신 목이 잘리는 것뿐이겠지.";
			link.l1 = "기록물을 내게 넘기시오, 내가 우리의 적을 처리하겠소.";
			link.l1.go = "Merdok_talk_2";			
		break;
		
		case "Merdok_talk_2":
			dialog.text = "날 바보로 아는 모양이군. 내가 아직 살아 있는 건 그걸 아직 가지고 있기 때문이야. 네가 지금 루카스를 위해 일하지 않는다는 걸 내가 어떻게 알 수 있지?";
			link.l1 = "내 말을 믿어야 할 거다 - 아니면 죽게 될 거야.";
			link.l1.go = "Merdok_talk_3";			
		break;
		
		case "Merdok_talk_3":
			PlaySound("Voice\English\hambit\John Mardock-07.wav");
			dialog.text = ""틀렸군, 넌 여기서 지금 죽는다! 롱웨이, 공격해라!"\n";
			link.l1 = "오호, 저 중국놈이 그림자 속에서 기어나오는군! 걱정 마라, 너희 둘 다 잡채로 만들어주지!";
			link.l1.go = "Merdok_fightEng";			
		break;
		
		case "Merdok_fightEng":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");	
			sld = characterFromId("Longway");
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_08", "pistol1", "bullet", 80);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
			PlaySound("Voice\English\hambit\Longway-02.wav");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattleEng");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//----------------------------------------против всех-------------------------------------------------------
		case "MC_InHouse":
			PlaySound("Voice\English\hambit\John Mardock-02.wav");
			dialog.text = "마침내 다시 일어났군. 혹시 깨어나지 못할까 봐 걱정했었어.";
			link.l1 = "뭐...? 너 누구야? 여긴 대체 어디지? 내가 어떻게 여기 온 거야?";
			link.l1.go = "MC_InHouse_1";	
		break;
		
		case "MC_InHouse_1":
			dialog.text = "진정하게, 한꺼번에 그렇게 많은 질문을 하지 마. 너무 흥분하면 네 건강에 좋지 않아. 내 이름은 존 머독이고, 여기 세인트 존스에서 약사로 일하고 있지. 너는 플리트우드 놈들과 싸우다가 의식을 잃었어. 솔직히 말해서, 그놈들이 너를 제대로 두들겨 팼지... 널 여기 약국까지 데려온 건 에르퀼이었고, 나는 내 약과 약초로 네 상처를 치료했어.";
			link.l1 = "에르큘? 누구? 거리에서 나를 도와줬던 그 남자? ";
			link.l1.go = "MC_InHouse_2";			
		break;
		
		case "MC_InHouse_2":
			dialog.text = "그래. 그 사람 맞아. 그런데 그가 너와 얘기하고 싶어 하더군. 마을에서 그를 만나야 해. 아직 걸을 수 있지? 좋아. 밤에 나가. 내 집 1층 문 뒤에서 시작하는 비밀 통로를 이용해. 어두워질 때까지는 나가지 마. 플리트우드의 부하들이 널 찾고 있으니까.";
			link.l1 = "그래... 내 배는 어디 있지?";
			link.l1.go = "MC_InHouse_3";			
		break;
		
		case "MC_InHouse_3":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "당신의 배는 압류되었고, 선원들은 플리트우드의 부하들에게 죽임을 당할까 두려워 뿔뿔이 흩어졌소. 유감이오.";
				link.l1 = "젠장...";
			}
			else
			{
				dialog.text = "그 여자는 항구에 있어, 평소 있던 자리에.";
				link.l1 = "휴... 다행이군. 그녀를 잃은 줄 알았거든.";
			}
			link.l1.go = "MC_InHouse_4";			
		break;
		
		case "MC_InHouse_4":
			dialog.text = "에르퀼을 만나야 하오. 비밀 통로를 통해 밤에 도시로 가시오. 그가 먼저 접근할 것이오. 이제 좀 쉬시오, 나는 내 일로 돌아가야 하니.";
			link.l1 = "알겠어, John. 그리고... 도와줘서, 또 치료해줘서 고마워!";
			link.l1.go = "MC_InHouse_5";
		break;
		
		case "MC_InHouse_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			npchar.greeting = "merdok_2";
			AddQuestRecord("Holl_Gambit", "3-12");
			pchar.questTemp.HWIC.Self = "MainBegin";//новый флаг квеста
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.greeting = "barmen_1";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", true);//закрыть выход из аптеки через дверь
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//открыть подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//открыть дом из подземелья
			pchar.quest.Tonzag_Meeting.win_condition.l1 = "location";
			pchar.quest.Tonzag_Meeting.win_condition.l1.location = "SentJons_town";
			pchar.quest.Tonzag_Meeting.win_condition.l2 = "Night";
			pchar.quest.Tonzag_Meeting.function = "TonzagMeeting";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);	
		break;
		
		case "About_Fleetwood":
			DelLandQuestMark(npchar);
			dialog.text = "플리트우드? 그 사람에 대해 뭘 알고 싶은데?";
			link.l1 = "전부 말해. 네가 아는 건 다 말해 봐. 에르퀼이 왜 앤티과에 온 건 너한텐 비밀도 아닌 것 같은데. 나는 그쪽 편이야.";
			link.l1.go = "About_Fleetwood_1";
		break;
		
		case "About_Fleetwood_1":
			dialog.text = "좋소. 로열... 아니, 커먼웰스 해군의 리처드 플리트우드 선장 말이오... 젠장, 저 광신자 크롬웰이 정권을 잡고 이름을 바꾼 걸 자꾸 잊어버리네. 어쨌든, 플리트우드는 훌륭한 전사이자 노련한 선원이오. '발키리'라는 브리그선을 지휘하는데, 정말 뛰어난 배요. 승무원들도 정예 선원과 해병들이지. 그는 연합주 전체, 특히 네덜란드 서인도 회사와 사적인 전쟁을 벌이고 있소. 수많은 네덜란드 상선을 약탈했고, 보험료를 천정부지로 올려놨지. 퀴라소 총독이 그의 목에 사상 최고 금액의 현상금을 걸었소.";
			link.l1 = "흠... '코먼웰스 해군' 장교가 해적으로 변하는 건 좀 이상한데...";
			link.l1.go = "About_Fleetwood_2";
		break;
		
		case "About_Fleetwood_2":
			dialog.text = "그래, 맞네. 그는 정말 아슬아슬한 줄타기를 하고 있지. 영국인들은 공식적으로 그의 행동을 인정하지 않고, 아무 관련도 없는 척하지만, 실제로는 뒤에서 그를 부추기고 있네. 나는 그가 카리브 해의 영국 첩보 조직과 어떻게든 연관되어 있다고 생각할 만한 이유가 있네, 그리고 그 악당들은 함부로 건드릴 상대가 아니지\n";
			link.l1 = "진지한 사람이군... 이게 다야? Hercule이 자기 부하 중 한 명에 대해 말해줬는데... 또 다른 Charlie... 이름이 뭐였더라... 캐니스터? 캐넌볼?";
			link.l1.go = "About_Fleetwood_3";
		break;
		
		case "About_Fleetwood_3":
			dialog.text = "크니펠? 그래, 그런 녀석 있지. 찰리 크니펠은 영국 해군의 포술장이었는데, 지금은 은퇴했어. 지금은 해안가에서 조용히 살고 있지. 그는 세인트 존스에서 플리트우드의 눈과 귀야, 그러니 조심하고 리처드에 대해 캐묻을 생각은 하지도 마. 감옥에 가거나 더 나쁜 꼴을 당할 거야.";
			link.l1 = "알겠소. 플리트우드에 대해 더 언급할 만한 것이 있소?";
			link.l1.go = "About_Fleetwood_4";
		break;
		
		case "About_Fleetwood_4":
			dialog.text = "앤티과의 모든 여자들, 열여섯부터 예순까지의 우상이었지. 그에 대해 더 할 말도 없는 것 같군. 뭐, 이제 그가 어떻게 됐는지 알겠지. 침대에 누워 상처나 핥으며 지내고 있어.";
			link.l1 = "그 자도 약점이나 악습이 있을 텐데...";
			link.l1.go = "About_Fleetwood_5";
		break;
		
		case "About_Fleetwood_5":
			dialog.text = "무슨 뜻이오?";
			link.l1 = "글쎄, 아마 도박을 좋아하거나 술을 심하게 마시거나 여자들을 그냥 지나치지 못하는 그런 부류겠지. 결혼은 했나?";
			link.l1.go = "About_Fleetwood_6";
		break;
		
		case "About_Fleetwood_6":
			dialog.text = "아니, 미혼이오. 당신이 언급한 것들에 대해서는 그와 관련된 소문은 없소.";
			link.l1 = "알겠소. 하지만 그래도 그에게 뭔가 특별한 점이 있지 않겠소? 저런 사람도 약점 하나쯤은 있을 테니까!";
			link.l1.go = "About_Fleetwood_7";
		break;
		
		case "About_Fleetwood_7":
			dialog.text = "모르겠어. 자, 이렇게 하자. 일주일 뒤에 나를 다시 찾아와. 그동안 내가 플리트우드의 사생활을 조사해 볼게. 어때?\n";
			link.l1 = "좋아. 고마워, John! 일주일 뒤에 여기 있을게.";
			link.l1.go = "About_Fleetwood_8";
		break;
		
		case "About_Fleetwood_8":
			DialogExit();
			pchar.questTemp.HWIC.Self = "WaitFleetwood";
			SaveCurrentQuestDateParam("questTemp.Wait_Fleetwood");
			SetFunctionTimerCondition("Wait_FleetwoodQM", 0, 0, 7, false);
			SetFunctionTimerCondition("Wait_FleetwoodOver", 0, 0, 12, false);//чтобы не опаздывал
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", false);//открыть выход из аптеки
			AddQuestRecord("Holl_Gambit", "3-14");
		break;
		
		case "About_Fleetwood_9":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "네, 하지만 아쉽게도 별로 많지 않소. 그리고 유감스럽게도 그다지 쓸모도 없을 것 같소.";
			link.l1 = "불어! Fleetwood와 관련된 거라면 사소한 것 하나까지 다 중요하니까.";
			link.l1.go = "About_Fleetwood_10";
		break;
		
		case "About_Fleetwood_10":
			dialog.text = "얼마 전, 리처드는 이름 모를 섬에서 유대인 난민 두 명을 데려왔소. 노인과 그의 딸이었는데, 윌렘스타트로 가는 길이었지. 그들이 타고 있던 배는 해적들에게 침몰당했소. 플리트우드는 자신의 목숨을 걸고 몰래 그들을 퀴라소로 데려왔지. 그로부터 몇 달이 지났소. 이제 그는 충직한 부하 찰리 크니펠을 윌렘스타트로 파견했소...\n";
			link.l1 = "흠... 어떻게 연결되어 있지?";
			link.l1.go = "About_Fleetwood_11";
		break;
		
		case "About_Fleetwood_11":
			dialog.text = "찰리가 윌렘스타드에서 어떤 여자를 이리로 데려오라는 명령을 받았다는 걸 알아냈어. 이름은 아비가일 슈네르라는 유대인 여자야. 그래, 그 섬에서 온 바로 그 여자. 리처드가 그녀에게 반한 모양이야, 최고의 첩보원을 직접 보내는 걸 보니.\n이게 전부야. 도움이 될지는 모르겠다.";
			link.l1 = "오호호! 하하하! 우리 자타공인 독신남이 유대 여인의 교활한 매력에 빠진 모양이군. 정말 훌륭한 일이야, 존, 고맙네! 이제, 우리의 친구 크니펠은 언제 퀴라소로 떠나나?";
			link.l1.go = "About_Fleetwood_12";
		break;
		
		case "About_Fleetwood_12":
			dialog.text = "그는 어제 떠났소.";
			link.l1 = "그리고 어느 배에서?";
			link.l1.go = "About_Fleetwood_13";
		break;
		
		case "About_Fleetwood_13":
			dialog.text = "그럴 줄 알았지. 그는 연방에서 임대한 브리건틴, 아니, 젠장, '로열 네이비' 소속 배에 타고 있어. 이름은 'Zeekalf'야.";
			link.l1 = "'Zeekalf'? 영국 배치고는 꽤 네덜란드스러운 이름이군... 아, 이제 알겠네.";
			link.l1.go = "About_Fleetwood_14";
		break;
		
		case "About_Fleetwood_14":
			dialog.text = "머리가 빠르군... 저 배의 원래 이름은 '로열 메리'였지만, 이번 항해에서는 '지칼프'로 불리고 있지. 그리고 네덜란드 국기를 달고 있어.";
			link.l1 = "네 도움이 정말 귀중했네, John. 이제 출발하네. 곧 돌아올 것이니, 내가 회복할 때 머물렀던 2층 방을 다시 써야겠네.";
			link.l1.go = "About_Fleetwood_15";
		break;
		
		case "About_Fleetwood_15":
			dialog.text = "무슨 일 하고 있나?";
			link.l1 = "내가 돌아오면 모든 걸 말해주겠네. 행운을 빌어주게, 존! 잘 있거라.";
			link.l1.go = "About_Fleetwood_16";
		break;
		
		case "About_Fleetwood_16":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-16");
			pchar.questTemp.HWIC.Self = "HuntKnippel";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("HuntKnippelOver", 0, 0, 10, false);
			pchar.quest.Hunt_Knippel.win_condition.l1 = "location";
			pchar.quest.Hunt_Knippel.win_condition.l1.location = "Curacao";
			pchar.quest.Hunt_Knippel.function = "CreateKnippelShip";
			LocatorReloadEnterDisable("SentJons_town", "houseH1", true);//закрыть хижину Чарли
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		case "About_Fleetwood_17":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-15");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "Abigile":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "정말이오? 왜 그렇게 확신하시오?";
			link.l1 = "찰리는 바닷속에서 물고기 밥이 되었으니. 내가 '지칼프'에 올라타서 크니펠을 지옥으로 보냈지. 물론 그 전에 심문도 했고... 놈이 가지고 있던 편지 덕분에, 우리 용감한 리처드의 연인인 유대인 아가씨 아비게일에게 내가 크니펠인 척 접근할 수 있었어.";
			link.l1.go = "Abigile_1";
		break;
		
		case "Abigile_1":
			dialog.text = "흠... 영리하군. 그러니까, 네 말은...";
			link.l1 = "그래. 유대인 여자를 앤티과로 데려왔지. 지금 내 배에 타고 있어. 이제 플리트우드와의 게임에서 비장의 패가 생겼군! 그 녀석, 그녀를 위해서라면 뭐든 할 거야...";
			link.l1.go = "Abigile_2";
		break;
		
		case "Abigile_2":
			dialog.text = "확실하오? 모든 일이 그대가 암시하는 것처럼 그렇게 단순하지 않을 수도 있소...";
			link.l1 = "아, 그래, 난 정말 확신해. 편지를 보니 아비가일의 아버지가 돈 문제 때문에 리처드와의 결혼을 반대했던 것 같아. 알잖아, 전형적인 유대인 장인이지. 그래서 플리트우드가 그녀의 아버지에게 지참금으로 20만 페소를 주기로 했어! 이제 말해 봐, 세상에 그만한 값어치가 있는 여자가 몇이나 될까?";
			link.l1.go = "Abigile_3";
		break;
		
		case "Abigile_3":
			dialog.text = "헤! 유대인 여자는 절대 아니지! 내 평생 그만한 가치가 있는 기독교 여자애는 한 번도 본 적 없어, 그건 확실해. "+pchar.name+", 너 참 교활한 악당이군. 그녀를 어떻게 할 셈이지?";
			link.l1 = "내가 유대인 여자를 여기 데려오겠소, 그리고 당신 방에 머물게 할 것이오. 리처드가 바다로 나가 아직 돌아오지 않았다고 그녀에게 말할 테니, 그녀는 일주일 동안 우리 손님이 될 것이오.\n그녀는 내가 찰리 크니펠이라고 생각하고 있소.";
			link.l1.go = "Abigile_4";
		break;
		
		case "Abigile_4":
			dialog.text = "흥미롭군. 그래서 내 집에 그 아가씨를 두기로 했다는 건가? 흠...";
			link.l1 = "존, 저 여자는 유대인이야. 네덜란드 식민지에서 온 국적 없는 떠돌이지. 여기 세인트 존스에서는 아무도 그녀를 모르는, 이름 없는 존재야. 안심해, 우리가 하고 싶은 대로 해도 그녀는 감히 한마디도 못할 거야. 가진 돈도, 친구도 하나 없어. 그리고 어차피 오래 머물 손님도 아니야. 내가 그녀를 미끼로 플리트우드를 유인할 거고, 그 후엔 더 이상 그녀가 필요 없을 테니까.";
			link.l1.go = "Abigile_5";
		break;
		
		case "Abigile_5":
			dialog.text = "샤를, 너 점점 무서워지는데. 설마 저 아가씨를 이용하려는 건 아니겠지? 아니면 그 니펠처럼 똑같은 결말을 맞게 하려는 거야?";
			link.l1 = "아니, 당연히 아니지. 내가 '교활한 악당'일 수는 있어도, 아름다운 아가씨들의 적은 아니야 – 유대인이든 기독교인이든. 못생긴 아가씨라도 마찬가지고. 얌전히만 있으면, 모든 일이 끝난 뒤에 그녀를 빌렘스타드에 있는 아버지에게 데려다 줄 거야. 그 늙은 구두쇠는 아마 내 무릎에라도 매달려, 그 배신자 영국놈에게서 딸을 구해줘서 고맙다고 할걸.";
			link.l1.go = "Abigile_6";
			// belamour legendary edition -->
			link.l2 = "그 여자는 이 연극에서 맡은 역할이 있지. 연극이 끝나면 더 이상 쓸모없을 거다.";
			link.l2.go = "Abigile_6a";
		break;
		
		case "Abigile_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 60);
			dialog.text = "알겠소, 그러면 당분간 내가 그녀를 돌봐야겠군.";
			link.l1 = "억지로 하진 않겠어, 친구. 네가 정말 반대라면, 그 여자는 내 배에 남겨도 돼. 하지만 그 경우엔 안전을 위해 쇠사슬에 묶어서 쥐들 있는 창고에 가둬야 할 거야, 내 선원들로부터 지키려면 말이지. 여자 승객이 있는 건 놈들한테 신기한 일이거든. 그렇게 예쁜 아가씨를 그런 식으로 대하는 건 아깝지 않겠냐.";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_6":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 60);
			// <-- legendary edition
			dialog.text = "알겠소, 그러면 당분간 내가 그녀를 돌봐야겠군.";
			link.l1 = "억지로 하진 않겠어, 친구. 네가 정말 싫다면, 그 여자는 내 배에 남겨둘 수 있지. 하지만 그러면 안전을 위해 족쇄를 채워 쥐들과 함께 창고에 가둬야 해. 내 선원들한테는 여자 승객이 생긴 게 처음이라서 말이지. 그렇게 예쁜 아가씨를 그런 식으로 대하는 건 정말 아쉬운 일이겠지.";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_7":
			dialog.text = "알겠소. 좋아, 그녀를 이리 데려오시오. 플리트우드와의 싸움에서 그대를 돕는 것이 내 의무요. 그녀를 이리 데려오면 내가 '귀빈실'을 준비하겠소.";
			link.l1 = "고맙소, John. 자네를 믿을 수 있다는 걸 알고 있었지.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Self = "AbigileInCabin";
			DoQuestCheckDelay("SetAbigileToCabin", 1.0); // fix 180812
			AddQuestRecord("Holl_Gambit", "3-24");
			//поставим табурет
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "SentJons_HouseF3";
			sld.startLocator = "goto2";
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abigile_7_1":
			DelLandQuestMark(npchar);
			dialog.text = "오! 영광입니다. 이렇게 중요한 분, 그리고... 우아한 숙녀를 맞이하게 되어 기쁩니다. 아가씨, 2층으로 올라가 주시겠습니까? 저녁 식사가 준비되어 있고, 침대도 정돈되어 있습니다. 이렇게 긴 여행 끝에 푹 쉬고 싶으실 거라 확신합니다.";
			link.l1 = "그래. 아비게일은 빌렘스타드에서 이렇게 긴 항해를 하고 나서 많이 피곤하겠지.";
			link.l1.go = "Abigile_8";
		break;
		
		case "Abigile_8":
			DialogExit();
			sld = characterFromId("Abigile");
			sld.dialog.currentnode = "Abigile_kidnapping_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_9":
			dialog.text = "이미 계획이 있소?";
			link.l1 = "그래, 맞아. 리처드에게 아비게일 몸값을 요구하는 편지를 써야 해. 사람이 없는 섬, 예를 들면 터크스 같은 곳에서 만남을 잡자고 해. 그리고 만약 그놈이 요구를 들어주지 않으면, 뭐랄까, 그 유대인 애인을 토막내서 보내주면 되겠지.";
			link.l1.go = "Abigile_10";
		break;
		
		case "Abigile_10":
			dialog.text = "사람도 없는 섬에 뭐 그렇게 복잡하게 굴 필요가 있나?";
			link.l1 = "중립 지대다. 그쪽이 더 안전하지. 어차피 아비게일은 데려가지 않을 거야. 플리트우드가 필요해. 앤티가에서는 분명히 매복을 준비할 테지만, 터크스에서는 그런 이점이 없을 거야.";
			link.l1.go = "Abigile_11";
		break;
		
		case "Abigile_11":
			dialog.text = "그럴 만하군. 누가 편지를 전달할 것인가? 매우 위험한 일이오.";
			link.l1 = "낯선 놈을 골라. 선술집에서 믿음직해 보이는 주정뱅이 하나 데려와. 럼주값만 주면 뭐든 시키는 대로 할 거야. 리처드가 분노에 못 이겨 그놈을 죽이면, 또 다른 놈을 보내면 되지. 그리고 편지에 아비 손가락 하나를 동봉해. 그러면 훨씬 더 말을 잘 들을 거야.";
			link.l1.go = "Abigile_12";
		break;
		
		case "Abigile_12":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "걱정 마, John. 그렇게까지는 안 갈 거야. 네가 심부름꾼만 구하면 내가 바로 편지를 쓸게. 종이랑 잉크는 있니?";
			link.l1.go = "Abigile_13";
		break;
		
		case "Abigile_13":
			dialog.text = "그래, 알고 있지. 그리고 마침 적당한 주정뱅이도 하나 알고 있소. 잭 해리슨을 추천하오. 그는 매일 저녁 선술집에서 럼주를 퍼마시며 시간을 보내지. 금방 찾을 수 있을 거요.";
			link.l1 = "좋아, 펜이랑 잉크 가져오너라. 내가 리처드의 몸값 편지를 써주지.";
			link.l1.go = "Abigile_14";
		break;
		
		case "Abigile_14":
			DialogExit();
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.07, 2.57, -2.46, true, -0.08, -0.38, 1.35);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "MC_writeLetter", -1);
		break;
		
		case "Abigile_15":
			dialog.text = "언제 그에게 편지를 건넬 거지? 전달하는 걸 지켜볼 생각이야?";
			link.l1 = "물론이지. 리처드는 바보가 아니지만, 모험을 걸 것 같진 않군. 적어도, 그러길 바란다. 나는 그 아가씨를 다치게 하고 싶지 않지만, 필요하다면 그렇게 할 거야. 자, 이제 네가 말한 그 술주정을 찾아야겠군. 잭... 성명이 뭐였지?\n";
			link.l1.go = "Abigile_20";
		break;
		
		case "Abigile_20":
			dialog.text = "그의 이름은 잭 해리슨이오. 그는 보통 저녁에 선술집에 들르지. 조심하시오!";
			link.l1 = "모든 게 잘 될 거야. 나를 기다려.";
			link.l1.go = "Abigile_22";
		break;
		
		case "Abigile_22":
			DialogExit();
			LAi_SetOwnerType(npchar);
			pchar.questTemp.HWIC.Self = "LetterToDrunkardGo";
			AddDialogExitQuestFunction("CreateDrunckardInTavern");
			AddQuestRecord("Holl_Gambit", "3-25");
		break;
		
		case "Abigile_23":
			DelLandQuestMark(npchar);
			dialog.text = "글쎄, 나는 그렇게 말하지 않겠소. 플리트우드는 교활하고 위험한 자요. 게다가 그는 검술의 달인이자 노련한 선원이기도 하오. 그를 쉽게 잡을 수는 없을 것이오.";
			link.l1 = "카리브에 온 뒤로는 더 이상 쉬운 길만 택하지 않았지. 자, 존, 이제 나는 떠나야겠군. 그런데, 아까 용감한 플리트우드가 좋은 배를 가지고 있다고 했지?";
			link.l1.go = "Abigile_24";
		break;
		
		case "Abigile_24":
			dialog.text = "그 자는 내가 본 것 중 가장 훌륭한 브리그선을 가지고 있지. 나도 배는 꽤 많이 봤거든.";
			link.l1 = "좋군. 나는 훌륭한 배가 마음에 들어. 이제 닻을 올릴 시간이야!";
			link.l1.go = "Abigile_26";
		break;
		
		case "Abigile_26":
			DialogExit();
			pchar.questTemp.HWIC.Self = "FleetwoodToIsland";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1 = "location";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1.location = "Shore56";
			pchar.quest.Fleetwood_meetingShore.function = "InTerksShore";
			AddQuestRecord("Holl_Gambit", "3-28");
			AddMapQuestMarkShore("Shore57", false);
		break;
		
		case "Abigile_27":
			int iVal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
				}
			}//установили признак наличия Валькирии в эскадре.
			if (iVal != 0)
			{
				dialog.text = "할 말을 잃었소! 훌륭한 조합, 빛나는 아이디어, 그리고 완벽한 실행이었소! 축하하오, "+pchar.name+"! 그리고 그의 브리그까지 노획했구나!";
				link.l1 = "감사합니다! 그런데 에르퀼은 어디 있습니까? 그를 만나고 싶군요. 지난번에 만났을 때, 당신의 도움을 받으면 그를 찾을 수 있을 거라고 했거든요.";
				link.l1.go = "Abigile_28";
			}
			else
			{
				dialog.text = "훌륭한 조합, 멋진 아이디어, 그리고 완벽한 실행이오! 축하하오, "+pchar.name+"!";
				link.l1 = "감사합니다! 그런데 에르퀼은 어디 있습니까? 그를 만나고 싶소. 우리가 마지막으로 만났을 때, 당신이 도와주면 그를 찾을 수 있을 거라고 했었지요.";
				link.l1.go = "Abigile_28";
			}
		break;
		
		case "Abigile_28":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "나는 그가 곧 도착할 거라 기대하고 있소. 비밀 통로를 통해 이리로 올 것이오. 그리고 자네는 아비게일에게 해명을 해야 하오. 그녀가 리처드가 없어서 걱정하기 시작했거든.";
			link.l1 = "좋아, 하지만 그녀를 집에 돌려보내야 하지 않아?";
			link.l1.go = "Abigile_29";
		break;
		
		case "Abigile_29":
			dialog.text = "아직이야... 먼저 너와 얘기할 게 있어. 하지만 우선, 에르퀼이 올 때까지 기다려. 가서 아비게일을 위로해 줘. 이야기 하나 지어내서 들려줘. 그다음 지하실로 와. 알겠지?";
			link.l1 = "알겠어, John.";
			link.l1.go = "Abigile_30";
		break;
		
		case "Abigile_30":
			DialogExit();
			npchar.greeting = "merdok_4";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SentJons_TownCave", "item", "berglar1", "", -1);
			pchar.questTemp.HWIC.Self = "AbigileLie";
			sld = characterFromId("Abigile");
			LAi_SetCitizenType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddQuestRecord("Holl_Gambit", "3-34");
		break;
		
		case "Lucas":
			DelLandQuestMark(npchar);
			dialog.text = "자, 이제 본색을 드러낼 때가 왔군. 이미 눈치챘겠지만, 나는 단순한 약장수가 아니야. 내 진짜 이름은 요한 판 메르덴이고, 최근까지 네덜란드 서인도 회사의 요원이자 부사장 루카스 로덴부르크의 오른팔이었지.";
			link.l1 = "정말이군! 흥미로운데...";
			link.l1.go = "Lucas_1";
		break;
		
		case "Lucas_1":
			dialog.text = "이제는 상황이 달라졌소. 루카스는 이 판을 떠나 네덜란드로 돌아가고 싶어 하니, 과거와 연관된 모든 것과 모든 사람을 묻어버릴 필요가 있지\n내가 아직 숨 쉬고 있는 이유는 내 기록보관소 덕분이라 생각하오. 거기엔 루카스의 범죄에 관한 모든 정보가 들어 있지... 예를 들면 '유령선' 이야기처럼 말이오. 사실 그건 무모하고 양심 없는 악당 야코프 판 베르흐가 지휘하는 평범한 해적선일 뿐이오. 로덴부르크가 그자를 고용해 영국 무역선을 약탈하고 침몰시키게 했지\n판 베르흐는 아비게일과 그녀의 아버지가 타고 있던 플라이트를 침몰시킨 장본인이기도 하오. 아비게일은 이 판에서 중요한 인물이오. 로덴부르크 역시 플리트우드처럼 그녀의 마음과 손을 원했으니, 자네가 그녀를 여기 데려왔을 때 꽤 놀랐소...";
			link.l1 = "로덴부르크... 그게 바로 아비게일의 괴짜 아버지가 말하던 사위였군!";
			link.l1.go = "Lucas_2";
		break;
		
		case "Lucas_2":
			dialog.text = "그래, 그래서 그녀를 당분간 여기 머물게 하고 싶네. 그녀는 로덴부르크와의 게임에서 내 마지막 비장의 카드가 될 수도 있지. 하지만 더 이상 그녀를 이용하고 싶지는 않아. 착한 아이라서 고생시키고 싶지 않거든. 만약 선택지가 주어진다면, 루카스는 분명 내 기록보관소를 그녀보다 택할 거야.\n그러니 자네가 루카스와의 게임에서 내 동맹이 되어주길 제안하지. 그를 없애게, 어떤 수단을 써도 좋아. 보상은 충분할 걸세.";
			link.l1 = "흠... 플리트우드와 할 때보다 더 어려울 것 같진 않은데. ";
			link.l1.go = "Lucas_3";
		break;
		
		case "Lucas_3":
			dialog.text = "아니, 그대가 틀렸소. 결국 플리트우드는 혼자 움직이는 외로운 늑대였지. 로덴부르크는 회사의 부사장이오. 그는 매우 영향력 있는 인물이니, 퀴라소 총독만이 그보다 더 큰 권력을 가졌소. 야코프 판 베르흐는 그의 대리인인데, 아주 위험한 자요. 루카스는 윌렘스타트에서 회사 경비병들의 보호 아래 엉덩이나 붙이고 앉아 있지; 그 경비병들은 플리트우드의 부하들만큼이나 강하오.\n이 일, 쉽지 않을 것이오.";
			link.l1 = "게임의 규칙은 똑같아. 호랑이를 굴 밖으로 유인하는 거지... 이미 계획은 있어. 루카스에 대해 더 말해줄 수 있는 게 있나?";
			link.l1.go = "Lucas_4";
		break;
		
		case "Lucas_4":
			dialog.text = "음, 내가 거의 모든 걸 말해줬지. 그는 '메이펑' - 아름다운 바람이라는 빠른 배를 가지고 있어. 그 배의 선장은 롱웨이라는 중국인인데, 로덴부르크에게 충성을 맹세한 자야. 그 역시 상대하고 싶지 않은 적이지. 루카스의 선원 중에 아마추어는 없어. ";
			link.l1 = "우리에겐 처음부터 비장의 카드가 있었지 - 바로 네 기록 보관소 말이야. 만약 그자가 유대 여인보다 자기 목숨을 더 소중히 여긴다면, 기록 보관소의 정보를 지키기 위해 뭐든 할 거야... 하지만... 그 기록 보관소가 정말 존재하긴 하냐, 존? 혹시 허세 부리는 거 아니야?";
			link.l1.go = "Lucas_5";
		break;
		
		case "Lucas_5":
			dialog.text = "기록 보관소는 실제로 있어. 그리고 루카스도 그 사실을 알고 있지. 아직 뭔가 생각해낸 게 있나?";
			link.l1 = "알고 있지. 존, 네가 정말 회사의 대리인이라면 뭔가 알고 있어야 할 텐데.";
			link.l1.go = "Lucas_6";
		break;
		
		case "Lucas_6":
			dialog.text = "무엇을 말이오? 나에게 물어보시오.";
			link.l1 = "나는 회사 소속 배 하나를 가로채야 해. 가능하면 호위 없는 배, 그러니까 연락선이나 비슷한 게 좋겠지. 이 일에 대해 아는 게 있나?";
			link.l1.go = "Lucas_7";
		break;
		
		case "Lucas_7":
			dialog.text = "흠... 그런 정보는 내게 없네. 잠깐! 확실히 아는 게 하나 있지. 회사에서 한 달에 한 번 필립스버그와 빌렘스타트 사이 항로에 패킷선을 띄운다네. 사업 서류를 운송하지. '후프'라는 브리건틴이야.\n오늘이나 내일 필립스버그를 떠날 거야.";
			link.l1 = "그래, 바로 그거야! 이제 세인트 크리스토퍼 해안으로 가기만 하면 돼. 큐라소로 가는 항로가 바로 그 근처를 지나가지.";
			link.l1.go = "Lucas_8";
		break;
		
		case "Lucas_8":
			dialog.text = "행운을 빕니다, "+pchar.name+". 당신의 계획에 대한 자세한 내용은 묻지 않겠소. 돌아오기를 기다리겠소!";
			link.l1 = "모든 게 잘 될 거야, 존. 유대인 여자를 잘 돌보고 친절하게 대해 줘!";
			link.l1.go = "Lucas_9";
		break;
		
		case "Lucas_9":
			DialogExit();
			RemoveItems(PChar, "MC_Letter", 1);
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter2");
			AddQuestRecordInfo("LetterToLucas", "1");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);
			pchar.questTemp.HWIC.Self = "LetterToLucas";
			sld = characterFromId("Tonzag");
			sld.dialog.currentnode = "Tonzag_hired";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddQuestRecord("Holl_Gambit", "3-36");
			//установим таймер на генерацию энкаунтера
			pchar.quest.HWIC_Cureer.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Cureer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Cureer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Cureer.function = "CreateHWICCureerOnMap";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("HWICCureerOnMapOver", 0, 0, 16, false);//таймер
		break;
		
		case "Lucas_10":
			dialog.text = "믿을 수가 없군! 내 귀를 의심하게 만드는군! 어떻게 그런 일이 벌어진 거지?";
			link.l1 = "나는 패킷선을 나포하고 플리트우드를 대신해 루카스에게 편지를 보냈소. 그 편지에는 내가 세인트 존스 출신 약제사의 어떤 문서를 손에 넣었으며, 곧 그의 모든 악행의 증거가 여기서부터 암스테르담과 런던까지 퍼질 것이라고 썼지. 그가 나를 쫓기 시작할 줄 알았는데, 결과는 정반대였소.";
			link.l1.go = "Lucas_11";
		break;
		
		case "Lucas_11":
			dialog.text = "";
			link.l1 = "루카스가 마티아스 벡을 배신과 영국인들과의 내통 혐의로 고발해 감옥에 가두고, 총독 관저에 들어가 살기 시작했소. 아마 브리건틴의 선장도 제거했을 것이오. 그리고 나서 자기에게 충성하는 메이펑 출신 중국인에게 회사의 이사 피터 스타이베선트가 탄 배를 침몰시키라고 명령했소!\n";
			link.l1.go = "Lucas_12";
		break;
		
		case "Lucas_12":
			dialog.text = "로덴부르크는 무자비한 사내다. 하지만 나조차도 그가 이렇게까지 할 줄은 몰랐지...";
			link.l1 = "나는 메이펑을 나포하고 롱웨이를 심문했어. 그는 모든 것을 털어놨어. 나는 스튜이베산트를 찾아가 로덴부르크의 의도를 경고했고, 우리는 함께 빌렘스타트로 항해했지.\n스튜이베산트는 벡을 석방하고 루카스를 체포했어. 그는 지금 감옥에 있어.";
			link.l1.go = "Lucas_13";
		break;
		
		case "Lucas_13":
			dialog.text = "헤헤! 너 진짜 재능 있구나, 친구야... 회사 해군에서 일하거나 네덜란드 본국에서 정치인으로 출세해도 되겠어 – 총독 자리도 노려볼 만하겠는걸! 그런데 롱웨이한테는 무슨 짓을 한 거야?";
			link.l1 = "나는 그를 보내줬어. 그는 명예롭게 항복했으니, 해치지 않았지.";
			link.l1.go = "Lucas_14";
		break;
		
		case "Lucas_14":
			dialog.text = "좋군. 롱웨이는 전 상사와 달리 괜찮은 사람이야. 자,\n "+pchar.name+", 정말 훌륭한 일을 해냈군! 보상은 내가 준비하겠네만, 시간이 좀 필요하네... 그동안...";
			link.l1 = "존, 사실을 말하자면, 좀 꺼림칙한 일이 있어. 롱웨이에 이어 로덴부르크까지 둘 다 야곱 판 베르흐가 나를 쫓고 있다고 하더군. 그거, 얼마나 심각한 거지?";
			link.l1.go = "Lucas_15";
		break;
		
		case "Lucas_15":
			dialog.text = "야콥 판 베르흐? 찰리, 이건 정말 심각해. 그 자는 무자비한 해적이자, 뛰어난 선원이며 싸움꾼이라 플리트우드가 고양이처럼 보일 정도야. 진짜 프로 사냥꾼이지. 로덴부르크의 명령으로 선박들을 파괴한 것도 바로 그 놈이야.\n그가 널 반드시 찾아낼 테니, 준비해야 해. 나도 미리 대비해야겠군.";
			link.l1 = "이 반 베르크를 어떻게 찾을 수 있지?";
			link.l1.go = "Lucas_16";
		break;
		
		case "Lucas_16":
			dialog.text = "모르겠어. 루카스랑 롱웨이만이 그를 어디서 찾을 수 있는지 알았지. 그러니 조심하고 항상 경계해\n여긴 이제 닫을 거야. 나를 만나고 싶으면 비밀 통로로 와. 그리고 그 유대인 여자는 데리고 나가, 여기 있으면 너무 위험해.";
			link.l1 = "걱정 마, 존. 그 자가 나타나면 내가 처리할 테니까. 애비게일은 어디 있지?";
			link.l1.go = "Lucas_17";
		break;
		
		case "Lucas_17":
			dialog.text = "그녀는 교회에 갔어. 불쌍하더라. 요즘 많이 힘들어했거든.";
			link.l1 = "음... 이거 참 반가운 소식이군. 어쩌면 그녀도 자기 민족이 오랫동안 기다려온 메시아가 바로 그리스도라는 걸 깨달았나 보지. 자, 이제 그녀를 아버지에게 데려갈 시간이로군.";
			link.l1.go = "Lucas_18";
		break;
		
		case "Lucas_18":
			dialog.text = "그녀가 당신을 보고 싶어했어. 분명히 집에 데려다 달라고 부탁할 거야.";
			link.l1 = "아비, 흠?";
			link.l1.go = "Lucas_19";
		break;
		
		case "Lucas_19":
			dialog.text = "음, 인정해야겠군. 이제 우리 친구가 되었지. 내 집에서 그녀가 지낸 걸 후회하지 않아, 그리고 신께 감사한 건 그녀가 왜 이곳에 오게 되었는지 영영 모를 거란 사실이야.";
			link.l1 = "알겠소, John. 나는 교회에 가서 Abigail을 만날 것이오. 그다음 Willemstad로 갈 거요.";
			link.l1.go = "Lucas_20";
		break;
		
		case "Lucas_20":
			DialogExit();
			sld = characterFromId("Abigile");
			AddLandQuestMark(sld, "questmarkmain");
			ChangeCharacterAddressGroup(sld, "SentJons_church", "goto", "goto1");//Аби - в церковь
			AddQuestRecord("Holl_Gambit", "3-56");
			pchar.questTemp.HWIC.Self = "AbiReturnHome";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
		break;
		
		case "Final":
			dialog.text = "너... 그의 알을 깼다고? 아, 비유로군. 뭐, 알이 있든 없든, 해냈잖아! 축하한다!";
			link.l1 = "그대에게 거짓말하지 않겠소, 허허. 이제는 마음 놓고 숨 쉬어도 되오, 존.";
			link.l1.go = "Final_1";
		break;
		
		case "Final_1":
			dialog.text = "드디어군! 이제 이런 정치 놀음과 음모는 다 포기하는 게 낫겠어. 이제는 네가 한 일에 대한 보상 이야기를 할 때다.";
			link.l1 = "글쎄, 정말 그렇게 해준다면 고맙겠군.";
			link.l1.go = "Final_2";
		break;
		
		case "Final_2":
			dialog.text = "나는 이제 카리브를 영원히 떠날 생각이오. 그대가 도와주고 로덴부르크에게서 날 구해준 것에 대한 감사의 표시로, 이 집과 내 약국의 소유권 증서를 그대에게 주겠소. 이제 모두 그대의 것이오. 이 열쇠들을 받으시오.";
			link.l1 = "정말 훌륭하군! 나는 아주 기쁘네. 집도 무척 안락하고, 지하 저장고도 아늑하군...";
			link.l1.go = "Final_3";
		break;
		
		case "Final_3":
			GiveItem2Character(pchar, "Drugstore_keys");//ключ
			dialog.text = "그리고 이 보잘것없는 10만 페소와 이 머스킷도 받아주십시오. 한때 나에게 충직하게 쓰였던 무기이니, 당신에게도 큰 도움이 될 것이오.";
			link.l1 = "이런 선물을 마다할 리 없지!";
			link.l1.go = "Final_4";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", false);//открыть аптеку
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", false); // открыть комнату
			pchar.quest.Jino_Door.win_condition.l1 = "locator";
			pchar.quest.Jino_Door.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Jino_Door.win_condition.l1.locator_group = "reload";
			pchar.quest.Jino_Door.win_condition.l1.locator = "reload4";
			pchar.quest.Jino_Door.function = "OpenRoomDoor";//на локатор комнаты Джино
			Achievment_Set("ach_10");
		break;
		
		case "Final_4":
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "mushket2");
			dialog.text = "위층 방에 젊은 자연 철학자가 있을 것이오. 내가 아는 최고의 약제사요. 바로 그가 이 혼합약을 만들어서, 당신이 며칠 만에 회복할 수 있었지. 그의 급여만 잘 챙겨주면, 그의 지식이 모든 비용을 이자까지 더해 보상해 줄 것이오.";
			link.l1 = "내 개인 책벌레라니? 좋아, 내가 그 녀석을 돌보지.";
			link.l1.go = "Final_5";
		break;
		
		case "Final_5":
			dialog.text = "이제 작별을 고해야겠소. 나는 지하실로 가서 내 짐을 챙길 것이오.\n내일은 여기 없을 거요 - 앤티과를 떠나 항해할 생각이오.\n그대와 만나게 되어 기뻤고, 내 적이 아니라 내 편이 되어주어 고맙소.";
			link.l1 = "나도 만나서 반갑네, John. 아마 다시 만날 수도 있겠지...";
			link.l1.go = "Final_6";
		break;
		
		case "Final_6":
			dialog.text = "이번 생에는 아니야, 친구. 난 짐을 싸야겠어. 잘 가라, "+pchar.name+"!";
			link.l1 = "잘 가요, John! 행운을 빌어요!";
			link.l1.go = "Final_7";
		break;
		
		case "Final_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			npchar.lifeday = 0;
			pchar.questTemp.HWIC.Self = "final";
			AddQuestRecord("Holl_Gambit", "3-64");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "self_win";
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = "아, 나리, 그런 어리석은 말은 듣지 마십시오. 거기엔 아무도 없습니다. 저기는 제 실험실이고, 혼합물이 준비되고 있거든요...";
			link.l1 = "농담은 그만하고, John. Gino Gvineili라는 이름 들어본 적 있나?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "흠...";
			link.l1 = "아하! 네 눈을 보니 알겠군 - 내가 맞았어... 거기서 그 자가 살고, 그를 위해 약초를 준비하는 거지!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "나리, 다시 한 번 말씀드리지만 - 여기엔 아무도 없습니다.";
			link.l1 = "변명은 그만두자, John. 나는 네 연금술사에게 해를 끼치지 않을 거야\n하지만 산티아고의 Vincento 신부가 그를 찾는다면, 내가 장담할 수 없어. 이미 종교재판관이 자기 'Domini Canes'들을 앤티과로 보낼 계획을 세우고 있으니...";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "그에게서 뭘 원하지?";
			link.l1 = "그냥 이야기만 하려는 거요. 그가 내게 꽤 중요한 정보를 가지고 있소. 그를 종교재판소에 넘기거나, 어떤 식으로든 해치지 않겠다고 약속하오.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "지노는 착한 친구야. 빈첸초 신부가 지노에 대해 뭐라고 했든 믿지 마. 그리고 기억해―내 연금술사를 내가 지킬 거야.";
			link.l1 = "내가 약속했잖아. 그걸로는 부족해?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "위층으로 올라가시오. 문은 열려 있소. 그리고 약속을 꼭 지키길 바라오.";
			link.l1 = "안심하시오, 반드시 그렇게 하겠소.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "jino1";
			AddQuestRecord("Guardoftruth", "36");
			LocatorReloadEnterDisable(pchar.location, "reload4", false);
		break;
		
		// алхимический набор
		case "alchemy":
			dialog.text = "선장님, 연금술에 대해 익혀보고 싶지 않으십니까? 이게 분명히 선장님께 큰 도움이 될 수 있을 겁니다.";
			link.l1 = "미안하오만, 내 직업은 좀 다르오. 나는 손에 플라스크나 시험관이 아니라 칼자루를 쥐는 데 익숙하오.";
			link.l1.go = "alchemy_exit";
			link.l2 = "'그대의 철학으로는 상상도 못할 일들이 천지간에 더 많다네.' 물론이지, 나도 그러고 싶어. 무엇이 필요하지?";
			link.l2.go = "alchemy_1";
			npchar.quest.alchemy = true;
		break;
		
		case "alchemy_exit":
			dialog.text = "원하시는 대로 하십시오. 나는 방금 제안했을 뿐이오...";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "alchemy_1":
			dialog.text = "직접 손으로 약초를 섞는 법을 배워야 하오. 하지만 연금술사의 도구 없이는 성공할 수 없지. 이 가방을 보시오. 초보 연금술사에게 필요한 모든 것이 들어 있소 – 시험관, 플라스크, 증류기, 주걱, 유리관, 버너, 그리고 그 밖에 비슷한 것들이 많이 있지...\n";
			link.l1 = "아주 흥미롭군! 그런데 이걸로 뭘 만들 수 있지?";
			link.l1.go = "alchemy_2";
		break;
		
		case "alchemy_2":
			dialog.text = "납을 금으로 바꾸지는 못하겠지만, 다양한 조제법에 따라 재료를 섞어서 물약이나 다른 유용한 것들을 만들 수 있을 거야.";
			link.l1 = "조리법?";
			link.l1.go = "alchemy_3";
		break;
		
		case "alchemy_3":
			dialog.text = "맞아. 물약이나 아이템을 만들려면 반드시 조제법을 알아야 하네. 조제법은 상인에게서 살 수도 있고, 어디서든 발견할 수도 있지. 조제법을 익혔다면 필요한 모든 재료를 모으고, 거기에 적힌 대로 정확히 따라야 하네\n 연금술 도구를 사용하고, 절구와 막자를 찾아 사거나 구하고, 도가니도 찾아보게. 안타깝게도 내가 줄 여분은 없네. 약초, 증류주, 물약, 광물, 쓰레기까지—올바른 조제법과 도구만 있다면 뭐든 쓸 수 있지.";
			link.l1 = "매우 흥미롭군. 그런데 이 장비를 얼마에 팔 생각이지?";
			link.l1.go = "alchemy_4";
		break;
		
		case "alchemy_4":
			dialog.text = "이만 페소다. 아주 훌륭한 장비라 금방 본전은 뽑을 거야.";
			link.l1 = "날 놀리는 거지? 유리잔 몇 개 든 손가방을 루거 한 척 값에 팔겠다고? 됐어, 사양할게.";
			link.l1.go = "alchemy_exit";
			if (sti(pchar.money) >= 20000)
			{
				link.l2 = "동의해. 내 손으로 뭔가를 만들어보는 것도 재미있을 것 같아.";
				link.l2.go = "alchemy_5";
			}
		break;
		
		case "alchemy_5":
			AddMoneyToCharacter(pchar, -20000);
			Log_Info("You've got the alchemist's kit.");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "이 구매를 후회하지 않을 거라고 나는 확신하오. 필요한 때마다 직접 물약을 만드는 것이 약초상 노점에서 하나하나 사는 것보다 훨씬 이득이오. 게다가, 필요한 모든 것을 항상 살 수 있는 것도 아니니 말이오. ";
			link.l1 = "배워보자. 내가 할 수 있을 것 같아!";
			link.l1.go = "alchemy_6";
		break;
		
		case "alchemy_6":
			DialogExit();
			PlaySound("interface\notebook.wav");
			Log_Info("In order to make your own herbs and amulets you must have the Alchemy skill!");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("너는 "+GetSexPhrase("도둑이다, 나리! 경비병들, 저 자를 잡아라\n","도둑이다, 저 계집애다! 경비병들, 저년을 잡아라\n")+"!!!","저것 좀 봐! 내가 잠깐 생각에 잠긴 사이에, 네가 내 가슴을 확인하려 들다니! 도둑이다! 도둑 잡아라!!!","경비병들! 도둑이야! 저 도둑 잡아라!!!");
			link.l1 = "젠장!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
