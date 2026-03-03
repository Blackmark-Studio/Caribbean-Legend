void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "뭘 원하지?";
			link.l1 = "아무것도 아니다.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "AlonsoNaPalube":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube"))
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube2 = true;
				dialog.text = "결정하셔야죠, 선장님? 우리 이러지 않는 게 좋지 않을까요?";
				link.l1 = "그 일에 쓸 자원자를 더 모았나?";
				link.l1.go = "AlonsoNaPalube_StrongGroup";
			}
			else
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube = true;
				dialog.text = "선장님, 잠시 말씀 좀.";
				link.l1 = "보고하라, 알론소.";
				link.l1.go = "AlonsoNaPalube_2";
			}
			locCameraFromToPos(-10.33, 9.69, -22.16, true, -5.22, 7.19, -21.06);
		break;
		
		case "AlonsoNaPalube_2":
			dialog.text = "선원들이 당신이 케이맨에서 무슨 계획을 갖고 있는지 궁금해하고 있어. 사람들이 걱정하고 있네.";
			link.l1 = "아직 결정하지 않았어. 그리고 왜 선원들이 걱정하고 있지, 알론소?";
			link.l1.go = "AlonsoNaPalube_3";
		break;
		
		case "AlonsoNaPalube_3":
			dialog.text = "이 섬은 블랙우드 선장의 영역이야. 선원들 말로는 그가 미친 사람처럼 이 섬 구석구석을 파헤치고 있다더군. 발굴 때문에 수십 명이 망가졌다고도 하고... 그를 떠난 자들은 기이한 이야기들을 전하지.";
			link.l1 = "어떤 이야기들인데?";
			link.l1.go = "AlonsoNaPalube_4";
		break;
		
		case "AlonsoNaPalube_4":
			dialog.text = "블랙우드는 더 이상 예전의 그 사람이 아니야. 지금은 어떤 콘키스타도르의 보물에 집착하고 있지. 그걸 위해서라면 뭐든, 누구든 다 희생할 각오야. 너 멋진 이야기 속에 뛰어들고, 혼자 상륙해서 함정에 빠지는 거 얼마나 좋아하는지 우리도 잘 알지... 하지만 이번에는 못 빠져나올 거다.";
			link.l1 = "보고와 경고 고맙다. 내가 상륙하기로 결정하면, 반드시 선봉과 최고의 전사들 일부를 데리고 갈 거다.";
			link.l1.go = "AlonsoNaPalube_5";
		break;
		
		case "AlonsoNaPalube_5":
			dialog.text = "그건 쉽지 않을 겁니다, 선장님. 배에 오르는 건 그렇다 쳐도, 블랙우드가 소앤틸리스의 구멍마다 긁어모았다는 잡놈들과 해병들의 총알, 칼날 아래 상륙하는 건 완전히 다른 일이죠. 그리고 케이맨에 관한 안 좋은 소문도 돌고 있습니다... 아니, 그런 일에 자원할 사람은 많지 않을 겁니다.";
			link.l1 = "그럼 가능한 사람으로 버텨야겠군. 알론소, 너는 반드시 참여해야 해.";
			link.l1.go = "AlonsoNaPalube_LiteGroup";
			link.l2 = "내 생각엔, 내가 증명할 수 있는 건 이미 모두에게 다 증명했지. 실력 있는 싸움꾼과 사수들은 전부 간다. 이건 명령이다.";
			link.l2.go = "AlonsoNaPalube_StrongGroup";
			link.l3 = "흠... 음, 이 모든 걸 곰곰이 생각해봐야겠군. 아마 나중에 이 문제로 다시 돌아오게 될 거야.";
			link.l3.go = "AlonsoNaPalube_Exit";
		break;
		
		case "AlonsoNaPalube_Exit":
			SetFunctionLocationCondition("LadyBeth_CaimanSea", "Caiman", false);
			EndQuestMovie();
			bQuestDisableMapEnter = false;
			chrDisableReloadToLocation = false;
			if(UnloadLocation(loadedLocation) == true)
			{
				pchar.Ship.Pos.x = 0;
				pchar.Ship.Pos.z = 0;
				pchar.Ship.Ang.y = 0;
				Land_MapLoad();
				pchar.location = "";
			}
		break;
		
		case "AlonsoNaPalube_LiteGroup":
			dialog.text = "예, 선장님!";
			link.l1 = "블랙우드의 배는 어쩔 건데? 문제 생기지 않겠어?";
			link.l1.go = "AlonsoNaPalube_Vpered";
			pchar.questTemp.LadyBeth_LiteGroup = true;
		break;
		
		case "AlonsoNaPalube_StrongGroup":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 40 || sti(pchar.rank) >= 12)
			{
				dialog.text = "예, 선장님!";
				link.l1 = "블랙우드의 배는 어쩔 건데? 문제 안 생기겠어?";
				link.l1.go = "AlonsoNaPalube_Vpered";
				pchar.questTemp.LadyBeth_StrongGroup = true;
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 40) Notification_Skill(true, 40, SKILL_LEADERSHIP);
				if (sti(pchar.rank) >= 12) Notification_Level(true, 12);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube2"))
				{
					dialog.text = "아직 아닌 것 같습니다, 선장님.";
				}
				else
				{
					dialog.text = "나나 당신의 장교들에게 증명할 건 아무것도 없소. 우리는 명령대로 어디든 따라가겠지만, 평범한 선원들은 생각이 다르오. 문제가 생길까 두렵소, 선장.";
				}
				link.l1 = "그럼 할 수 있는 사람으로 버텨야겠군. 알론소, 너는 반드시 참여해야 해.";
				link.l1.go = "AlonsoNaPalube_LiteGroup";
				link.l2 = "흠... 그래, 이 모든 걸 좀 더 생각해봐야겠어. 아마 이 질문은 나중에 다시 이야기하게 될 거야.";
				link.l2.go = "AlonsoNaPalube_Exit";
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 40) Notification_Skill(false, 40, SKILL_LEADERSHIP);
				if (sti(pchar.rank) < 12) Notification_Level(false, 12);
			}
		break;
		
		case "AlonsoNaPalube_Vpered":
			dialog.text = "스노우선 말이지. 성질이 사나운 진짜 미인이라더군. 난 그녀는 걱정 안 해. 아마 선원 전부가 육지에서 노역 중이고, 배는 해안 어딘가에 잘 숨겨져 있을 거야. 우리가 이기면, 그때 가서 해안에서 그 배를 노획하면 되지.";
			link.l1 = "사람들 모아라. 오늘은 좋은 날이다 - 행운이 우리 편일 거다.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_AlonsoNaPalube_Vpered");
		break;
		
		// Диалог в таверне с Блеквудом
		case "LadyBeth_DialogInCity": // главное меню
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Fourth"))
			{
				dialog.text = "만나서 반갑소, 선장. 이미 모든 이야기는 끝난 것 같군..";
				link.l1 = "정말이지. 잘 가라.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LadyBeth_DialogInCity_again";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Third"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", "+npchar.name+"";
				link.l1.go = "LadyBeth_DialogInCity_Third_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", 블랙우드 선장.";
				link.l1.go = "LadyBeth_DialogInCity_Second_1";
				break;
			}
			if (startHeroType == 4)
			{
				dialog.text = "...";
				link.l1 = "안녕하세요. 블랙우드 선장이십니까?";
				link.l1.go = "LadyBeth_DialogInCity_First_Helena_1";
			}
			else
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+". 당신이 알버트 블랙우드 선장 맞지?";
				link.l1.go = "LadyBeth_DialogInCity_First_1";
			}
		break;
		
		case "LadyBeth_DialogInCity_again": // повтор
			dialog.text = "만나서 반갑소, 선장. 이미 모든 이야기는 다 나눈 것 같군.";
			link.l1 = "정말이지. 안녕히 가시오.";
			link.l1.go = "exit";
			NextDiag.TempNode = "LadyBeth_DialogInCity_again";
		break;
		
		case "LadyBeth_DialogInCity_First_1": // первый диалог
			dialog.text = "그래, 나야. 너는?";
			link.l1 = "Captain "+GetFullName(pchar)+". 나는 '" + PChar.Ship.Name + "'.";
			link.l1.go = "LadyBeth_DialogInCity_First_2";
		break;
		
		case "LadyBeth_DialogInCity_First_2":
			dialog.text = "선장... 케이맨에 가본 적 있소?";
			link.l1 = "방금 지나갔어.";
			link.l1.go = "LadyBeth_DialogInCity_First_3";
		break;
		
		case "LadyBeth_DialogInCity_First_3":
			dialog.text = "거기서 보물에 대해 들은 게 있나?";
			link.l1 = "아니, 특별한 건 없어.";
			link.l1.go = "LadyBeth_DialogInCity_First_4";
		break;
		
		case "LadyBeth_DialogInCity_First_4":
			dialog.text = "스페인 놈들의 흔적? 오래된 무기? 정복자 시대의 동전들?";
			link.l1 = "그런 건 못 찾았어.";
			link.l1.go = "LadyBeth_DialogInCity_First_5";
		break;
		
		case "LadyBeth_DialogInCity_First_5":
			dialog.text = "이 근처 전설 말이오? 코르테스에 관한 이야기? 매장지에 대한 건 없소?";
			link.l1 = "죄송합니다, 선장님, 하지만 그런 정보는 없습니다. 그리고 이건 점점 심문처럼 느껴지기 시작하는군요.";
			link.l1.go = "LadyBeth_DialogInCity_First_6";
		break;
		
		case "LadyBeth_DialogInCity_First_6":
			dialog.text = "미안하오... 예전 장교 버릇이 남아서 그만. 그냥... 이건 내게 정말로 중요한 일이오.";
			link.l1 = "왜 하필 케이맨에 그렇게 관심이 많은 거지?";
			link.l1.go = "LadyBeth_DialogInCity_First_7";
		break;
		
		case "LadyBeth_DialogInCity_First_7":
			dialog.text = "중요하지 않아. 다시 한 번 사과하지.";
			link.l1 = "알겠소. 수색에 행운이 있기를 바라오.";
			link.l1.go = "LadyBeth_DialogInCity_First_8";
		break;
		
		case "LadyBeth_DialogInCity_First_8":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Good night";
			else sStr = "Wishing you a good day";
			dialog.text = "쓸 만한 걸 찾으면 나한테 와. 또 다른 선장하고 얘기하는 건 즐거운 일이니까... 바다를 아는 사람과 말이지. " + sStr + ".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "LadyBeth_DialogInCity_First_9";
		break;
		
		case "LadyBeth_DialogInCity_First_9":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_1": // первый диалог с Элен
			dialog.text = "실제로 보니 반갑군. 그리고 너... 헬렌 맥아더 선장 맞지? 얀 스벤손의 제자라면서? 네 소문 들었어.";
			link.l1 = "정보가 빠르군, 블랙우드 선장. 하지만 영국 장교가 나에 대해 알고 있다 해도 놀랍지는 않지.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_2":
			dialog.text = "전직 장교. 그리고 모든 붉은 군복 놈들이 자네와 자네의... 왕실에서 받은 독특한 취향에 대해 다 알고 있지. 쇠목은 냄새가 나지 않는다더군. 그리고 자네 아버지 션 맥아더가 어릴 때부터 자네를 바다로 데려가 선장으로 만든 이야기는 함대에서 전설처럼 퍼졌지.";
			link.l1 = "이 전설을 직접 만나보니 어떤 기분이 드나?";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_3";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_3":
			dialog.text = "나로서는 솔직히 감탄하고 있네. 하지만 내 옛 동료들 중 상당수는, 인정하건대, 이 점을 꽤나 못마땅해하지. \n하지만 선장이 되려면 단순히 귀족 혈통이나 왕의 임명장만으로는 부족하지 않나?";
			link.l1 = "맞아. 지식과 경험, 그리고 끊임없이 자신의 실력을 증명할 준비가 필요하지. 특히 내 경우엔 더 그래.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_4";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_4":
			dialog.text = "정확히 그렇지! 바다에서든 인생에서든 중요한 건 직함이 아니라 결과야. 만나서 반갑네, MacArthur 선장. 또 만날 수 있길 바라지. 내가 원정에서 돌아오면 와인 한 잔 하러 들르겠나?";
			link.l1 = "그럴지도. 행운을 빕니다, 선장.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_5_harizma";
			link.l2 = "흥미 없어. 그래도 수색 잘 하길 바라, 선장.";
			link.l2.go = "LadyBeth_DialogInCity_First_Helena_5_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_harizma":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_oruzhie":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_1": // второй диалог
			dialog.text = "아, 선장님 "+pchar.lastname+"! 만나서 반갑군. 앉을래?";
			link.l1 = "기꺼이.";
			link.l1.go = "LadyBeth_DialogInCity_Second_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_2":
			dialog.text = "선장... 진짜 보물은 당신에게 어떤 의미인가?";
			link.l1 = "진짜 보물은 사랑이지. 곁에 있어 줄 사람이야말로 소중한 거야. 혼자인 것만큼 끔찍한 건 없어.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love";
			link.l2 = "돈이지, 당연히. 보물이라면 또 뭐가 있겠어?";
			link.l2.go = "LadyBeth_DialogInCity_Second_3_sokrovisha";
			link.l3 = "귀하고 독특한 장비지. 좋은 검이나 권총은 금보다 더 값지다.";
			link.l3.go = "LadyBeth_DialogInCity_Second_3_oruzhie";
			link.l4 = "지식. 가장 값진 보물은 네 머릿속에 있는 거다.";
			link.l4.go = "LadyBeth_DialogInCity_Second_3_znania";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love":
			if (startHeroType == 4)
			{
				dialog.text = "사랑? 흠... 해적의 딸에게서 그런 대답이 나올 줄은 몰랐지. 나... 나도 약혼자가 있었어. 엘리자베스라고, 바베이도스의 플랜테이션 주인의 딸이었지. 하지만 그녀의 아버지가... 내가 가진 돈이 부족하다고 생각했어. 내가 그의 딸에게 사랑 말고 뭘 줄 수 있었겠나? 당신은 운이 좋았어, 맥아더 선장. 당신의 아버지는 지참금보다 당신의 능력을 더 높이 평가했으니까.";
				link.l1 = "어쩌면 운이 아니라, 진정한 사랑은 금으로 재는 게 아니라는 사실 때문일지도 몰라. 내 아버지는 그걸 이해하셨지. 네 약혼녀는 어때? 그녀도 아버지의 생각에 동의하나?";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_1";
			}
			else
			{
				dialog.text = "사랑? 그래... 어쩌면 네 말이 맞아. 나... 나 약혼했었어. 바베이도스에서. 서로 사랑했지만... 그녀 아버지가 나를 신랑감으로 부족하다고 생각했지. 하! 돈이 부족했거든. 그래서 내가 여기 있는 거야 - 모두 틀렸다는 걸 증명하려고 보물을 찾으러 왔지. 어쩌면 헛된 짓일지도 모르겠네?";
				link.l1 = "그냥 그녀랑 직접 얘기해 보는 게 어때? 그 플랜테이션 주인 놈은 신경 끄고.";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_2";
			}
			AddComplexLandExpToScill(100, 100, 0);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_2":
			dialog.text = "말해보라... 그래, 어쩌면. 하지만 내가 무슨 말을 하겠나? '미안하다, 너에게 제대로 된 삶을 주지 못했다'고? 아니. 나는 반드시 승리자로 돌아가야 해. 아니면 아예 돌아가지 않겠다.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_1":
			dialog.text = "엘리자베스? 아니... 그녀는 나를 사랑해. 하지만 나는... 그녀를 가난 속에 살게 할 수는 없었어. 그녀는 더 나은 삶을 누릴 자격이 있어. 그리고 나는 그녀에게 어울리는 사람임을 증명해야 해.";
			link.l1 = "가난보다도 자존심이 행복을 더 방해할 때가 있소, 선장.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_2":
			dialog.text = "빈손으로 돌아갈 수는 없어. 정말 못 하겠어. 미안하지만, 할 일이 많아. 대화 즐거웠어, MacArthur 선장.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha":
			dialog.text = "참 뻔한 대답이군. 하지만 반박하기도 어렵지. 사실 브리스톨 빈민가에서 자라면서, 남은 음식을 두고 싸워야 했던 시절을 겪어 보면... 돈의 진짜 가치를 알게 되지. 그건 사치가 아니야. 자유지. 그 더러운 곳에서 간신히 기어나온 뒤, 다시는 돌아가지 않아도 되는 힘이란 말이다.";
			link.l1 = "동의해. 돈이면 대부분의 문제가 해결되지. 그리고 만약 해결이 안 된다면, 그건 단순히 돈이 부족해서야.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_sokrovisha_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha_2":
			dialog.text = "정확해! 네가 이해하는군. 돈이 행복을 주진 않지만, 없으면 확실히 불행해지지. 나도 그걸 뼈저리게 알아...";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie":
			dialog.text = "흥미롭군. 실용적이야. 나는 아르케부스를 가지고 있지... 진짜야, 정복자 시대의 물건이지. 어떤 신부가 준 선물이야. 가끔은 내가 찾은 모든 금보다 더 가치 있다고 생각해. 하지만... 내 문제를 해결해 주진 않지.";
			link.l1 = "좋은 무기는 많은 문제를 해결할 수 있지. 그리고 절대 너를 배신하지 않아.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie_2":
			dialog.text = "그 말에 일리가 있지. 하지만 어떤 전투는 무력으로는 이길 수 없어.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_znania":
			dialog.text = "지식... 그래, 이해하지. 나는 정복자들에 대해, 보물에 대해 할 수 있는 모든 것을 공부했어. 보물 사냥에 관한 완전한 지침서도 만들었지. 함선 소총 부대를 위한 정기 훈련과 물질적 보상 체계도 고안했어. 어느 선장이든 내 지침서를 갖고 싶어할 거야. 하지만 이런 모든 지식도... 결과로 이어지지 않으면 아무 소용 없어. 진짜 결과로 말이야.";
			link.l1 = "하지만 결과를 이루게 해주는 건 지식이지. 지식이 없으면 어떤 탐색도 그저 어둠 속을 헤매는 것일 뿐이야.";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "LadyBeth_DialogInCity_Second_4":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Well, it's already late, and I have a lot of work to do";
			else sStr = "Well, I have a lot of work to do";
			dialog.text = "" + sStr + ". 대화해 주셔서 감사합니다, 선장님. 정말 흥미로웠습니다.";
			link.l1 = "너도 고마워. "+Goodbye(true)+".";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_5":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Third = true;
		break;
		
		case "LadyBeth_DialogInCity_Third_2": // третий диалог
			dialog.text = "아, "+pchar.name+"! 반갑군. 아주 좋은 소식이 있어. 드디어 내 문제를 해결할 방법을 찾았어. 곧 원정에 나설 거고, 이번에는 진짜 보물을 들고 돌아올 거야! 그런데 한 가지 충고하자면, 케이맨에는 얼씬도 하지 마. 이제 거긴 내 구역이거든.";
			link.l1 = "케이맨은 네 것이 아니야, 알버트. 너한테는 왕실 권한이 없어. 그건 해적질이야.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma";
			link.l2 = "블랙우드, 나를 협박하는 거냐?";
			link.l2.go = "LadyBeth_DialogInCity_Third_3_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma":
			dialog.text = "왕의 권리라고? 브리스톨 빈민가에서 살아봤어야지, "+pchar.name+", 그러면 이 서류들이 얼마나 값진지 알게 될 거야. 배고플 때는 법 따위 아무 의미 없어. 하지만... 네 말이 맞아. 형식적으로는 내가 그 섬에 대한 권리가 없어. 하지만 나는 그곳에서 수년간 찾아 헤맨 것을 발견했지. 그리고 그 누구에게도 빼앗기게 두지 않을 거야.";
			link.l1 = "네가 위험한 길을 걷고 있다는 걸 이해하길 바란다.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma_2":
			dialog.text = "나는 내 길이 결코 쉽지 않을 거라는 걸 항상 알고 있었지. 작별이야, "+pchar.name+". 어쩌면 다시 만날 수도 있겠군.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie":
			dialog.text = "위협한다고? 전혀 아니야. 그냥 선장끼리 하는 우정 어린 충고지. 카이만은 위험한 곳이야... 특히 내 일에 끼어드는 자들에게는 더더욱.";
			link.l1 = "네 '충고' 기억하지. 카이만에서 행운을 빌어.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie_2":
			dialog.text = "행운을 빕니다, 선장님. 그 행운이 필요 없기를 바라오. 안녕히 가시오.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_4":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Fourth = true;
		break;
		
		// Ловушка, абордаж в каюте
		case "LadyBeth_abordage":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "너라고?! 내가 항복할 거라 생각해? 다시 가난으로 돌아갈 거라 생각해? 차라리 빈민가에서 굶어 죽느니 여기서 죽겠다! 자비도 없고, 보상도 없고, 승리도 없다! 침대 밑에 화약통이 있다... 우리 전부 바다 밑으로 가는 거다!\n";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
			else
			{
				dialog.text = "누구길래 나를 공격하는 거야?! 내가 항복할 것 같아? 천만에! 다시 빈민가에서 굶주리느니 차라리 죽겠다! 자비도 없고, 보상도 없고, 승리도 없다! 침상 밑에 화약통이 있다... 우리 모두 바다 밑으로 가게 될 거다!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
		break;
		
		// Блеквуд разговаривает с ГГ перед битвой на Каймане
		case "LadyBeth_BlackWood_Boss":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "선장! 내가 경고했지. 이제 네 호기심에 대한 대가를 치르게 될 거다.";
			}
			else
			{
				dialog.text = "너 누구야, 감히 내 땅을 침범하다니?! 이 섬은 내 거다!";
			}
			link.l1 = "두고 보자, Blackwood. 오늘 이 세상에서 집착에 사로잡힌 놈이 한 명 줄게 될 거다.";
			link.l1.go = "LadyBeth_BlackWood_Boss_oruzhie_1";
			link.l2 = "평화롭게 끝내자, Blackwood. 내가 나가면 되잖아.";
			link.l2.go = "LadyBeth_BlackWood_Boss_torgovlya_1";
			link.l3 = "블랙우드, 너는 이성적인 사람이잖아! 너는 장교고! 네 진영 위에는 왕실 깃발까지 펄럭이고 있잖아, 제발! 우리 합의 좀 볼 수 없는 거냐?";
			link.l3.go = "LadyBeth_BlackWood_Boss_harizma_1";
		break;
		
		case "LadyBeth_BlackWood_Boss_oruzhie_1":
			dialog.text = "집착한다고? 하! 나는 내가 원하는 게 뭔지 아는 남자일 뿐이야!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_1":
			dialog.text = "떠난다고? 네가 본 걸 보고도? 안 돼, 안 돼, 절대 안 돼! 내가 여기서 발견한 걸 아무도 알아선 안 돼. 아무도!";
			link.l1 = "아무에게도 말하지 않겠다고 맹세하지. 선장의 명예를 걸고 맹세한다.";
			link.l1.go = "LadyBeth_BlackWood_Boss_torgovlya_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_2":
			dialog.text = "이 세상엔 명예란 없어, 선장. 오직 더러움과 가난, 그리고 멸시만 있을 뿐이지. 유감이지만, 넌 여기서 죽어야 해.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
		break;
		
		case "LadyBeth_BlackWood_Boss_harizma_1":
			dialog.text = "나는 생각했어. 정말 많이 생각했지. 그리고 깨달았어 - 이게 내 유일한 기회라는 걸. 코르테스의 금을 찾든가, 아니면... 아무것도 없는 거야. 알겠어? 아무것도! 예전 삶으로는 돌아가지 않아! 더러운 가난으로는 절대 돌아가지 않아! 차라리 여기서 죽는 게 낫지!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_2":
			dialog.text = "전투다! 불록, 프레이저 - 놈들이 다가오면 산탄을 쏴라! 홉킨스, 돌격해!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_CaimanKino_11");
		break;
		
		// Диалоги с офицерами
		case "LadyBeth_Helena_1": // Элен
			dialog.text = "괜찮아?";
			link.l1 = "그래, 다 괜찮아. 너는?";
			link.l1.go = "LadyBeth_Helena_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Helena_2":
			dialog.text = "살아 있지. 하지만 이런 육지 전투는 내 체질이 아니야. 내 발밑에 갑판만 있으면 어떤 배라도 박살낼 수 있는데, 여기서는... 이상한 곳이야. 백 명의 바다늑대들을 상륙시켜 곡괭이 휘두르고, 요새를 짓게 하다니... 난 그런 건 못 해.";
			link.l1 = "블랙우드는 선원들을 고무할 줄 알았지.";
			link.l1.go = "LadyBeth_Helena_3";
		break;
		
		case "LadyBeth_Helena_3":
			dialog.text = "나는 블루필드에서 그에 대해 들었어. 많은 영국 선원들이 그를 존경하며 이야기했지. 함대에서 최고의 장교였고, 뛰어난 경력을 쌓았는데... 그런데 갑자기 모든 걸 내던지고 보물을 찾아 나섰다네.";
			link.l1 = "그에 대해 어떻게 생각해?";
			link.l1.go = "LadyBeth_Helena_4";
		break;
		
		case "LadyBeth_Helena_4":
			dialog.text = "블랙우드의 사례가 우리가... 아니, 자네가 부하들 앞에서 짊어져야 할 책임의 무게를 분명히 보여준다고 생각하네.\n제발, 그 사람처럼 변해버린 선장이 되지는 말게.";
			link.l1 = " 해보겠어, Helen.";
			link.l1.go = "LadyBeth_Helena_5";
		break;
		
		case "LadyBeth_Helena_5":
			dialog.text = "감사합니다, 선장님. 반드시 성공하실 거라고 믿습니다.";
			link.l1 = "그러지.";
			link.l1.go = "LadyBeth_Helena_6";
		break;
		
		case "LadyBeth_Helena_6":
			dialog.text = "그러지.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Helena_7";
		break;
		
		case "LadyBeth_Helena_7":
			DialogExit();
			ReturnOfficer_Helena();
		break;
		
		case "LadyBeth_Mary_1": // Мэри
			dialog.text = "찰스... 여기 정말 끔찍하구나.";
			link.l1 = "괜찮아, 메리? 진짜 군인처럼 잘 버텼어.";
			link.l1.go = "LadyBeth_Mary_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Mary_2":
			dialog.text = "아니, 나 하나도 괜찮지 않아, 알겠어. 이 사람들 좀 봐! 지칠 때까지 일하고, 굶주림에 시달리며, 병으로 죽어 갔지... 그런데 그게 다 뭐 때문이었는지 알아? 존재할지도 모를 금 때문이야.";
			link.l1 = "블랙우드는 여기에 있다고 믿었지.";
			link.l1.go = "LadyBeth_Mary_3";
		break;
		
		case "LadyBeth_Mary_3":
			dialog.text = "이 빨간 코트... 내 거랑 똑같아. 영국 장교잖아... 있지, 갑자기 부모님 생각이 났어. 내 뿌리에 대해서도... 내가 한 번도 몰랐던 것들 말이야. 어쩌면 나도 그런 사람 중 하나일지도?";
			link.l1 = "그 중 하나인가?";
			link.l1.go = "LadyBeth_Mary_4";
		break;
		
		case "LadyBeth_Mary_4":
			dialog.text = "존재하지도 않을지 모르는 것을 찾으려는 자들. 그리고 그 탐색 속에서 자신을 잃어버리는 자들. 나도... 나중에 이 얘기를 하고 싶어. 우리가 이 끔찍한 곳을 떠나면 말이야.";
			link.l1 = "물론이지, Mary.";
			link.l1.go = "LadyBeth_Mary_5";
		break;
		
		case "LadyBeth_Mary_5":
			dialog.text = "먼저 저 사람부터 묻자, 제발. 자격이 없어도. 한때 사람이었던 그를 위해서라도.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Mary_6";
		break;
		
		case "LadyBeth_Mary_6":
			DialogExit();
			ReturnOfficer_Mary();
		break;
		
		case "LadyBeth_Tichingitu_1": // Тичингиту
			dialog.text = "선장, 티칭기투가 여기 나쁜 곳이라고 봤어. 아주 나쁜 곳이야.";
			link.l1 = "무슨 뜻이야?";
			link.l1.go = "LadyBeth_Tichingitu_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Tichingitu_2":
			dialog.text = "이 섬은 이제 저주받았지. 땅이 피와 눈물을 너무 많이 빨아들였어. 여기서 땅을 파는 놈들은 모두, 이 저주를 들이마시게 될 거야.";
			link.l1 = "블랙우드가 빙의됐다고 생각해?";
			link.l1.go = "LadyBeth_Tichingitu_3";
		break;
		
		case "LadyBeth_Tichingitu_3":
			dialog.text = "단순히 빙의된 게 아니야. 그는... 뭐랄까... 텅 빈 그릇이야. 무언가가 그 안에 들어와서 영혼을 밀어냈지. 나 이거 전에 본 적 있어. 우리 부족의 주술사가 영혼들에게 인간 제물을 바칠 때 말이야. 그 주술사도 똑같은 눈빛이었어.";
			link.l1 = "하지만 무엇이 그런 집착을 불러올 수 있지?";
			link.l1.go = "LadyBeth_Tichingitu_4";
		break;
		
		case "LadyBeth_Tichingitu_4":
			dialog.text = "속이 빈 사람은 다른 생각으로 채우기 쉽지. 누군가 그의 약점을 찾아 이용한 거야. 티칭이투는 이 남자가 좀 불쌍하다고 느낄 정도야.";
			link.l1 = "거의?";
			link.l1.go = "LadyBeth_Tichingitu_5";
		break;
		
		case "LadyBeth_Tichingitu_5":
			dialog.text = "그래, 거의 다 왔지. 모든 전사는 자기 선택에 책임을 져야 해. 설령 악마가 귓가에 속삭인다 해도.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Tichingitu_6";
		break;
		
		case "LadyBeth_Tichingitu_6":
			DialogExit();
			ReturnOfficer_Tichingitu();
		break;
		
		case "LadyBeth_Irons_1": // Томми
			dialog.text = "젠장, 선장님! 이것 좀 보세요! 예전 좋았던 시절 그대로군요!";
			link.l1 = "너는 육지에서의 전쟁이 어떤지 잘 알지.";
			link.l1.go = "LadyBeth_Irons_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Irons_2":
			dialog.text = "나스비 전투가 떠오르는군. 우리 기병대가 루퍼트의 기병들과 맞붙었지. 그들도 자기 왕을 위해 똑같이 맹렬하게 싸웠어.";
			link.l1 = "블랙우드에 대해 어떻게 생각해?";
			link.l1.go = "LadyBeth_Irons_3";
		break;
		
		case "LadyBeth_Irons_3":
			dialog.text = "이 블랙우드는 천재이거나 완전 미친놈이었지. 아니, 둘 다였던 것 같아. 뭔지 아냐? 나를 놀라게 한 건 그놈의 부하들이야. 그들 중 상당수가 전직 군인이거든. 그냥 길거리 양아치가 아니라 진짜 군인들이었지. 그런데도 전부 그 미친 짓을 따라갔어. 폭스의 해병대까지도 말이야. 하! 오늘의 학살에 제일 신나할 놈이 바로 그거다! 그놈은 자기 부하들이 탈영한 걸 절대 용서하지 않았거든.";
			link.l1 = "혹시 돈 때문인가?";
			link.l1.go = "LadyBeth_Irons_4";
		break;
		
		case "LadyBeth_Irons_4":
			dialog.text = "아니, 뭔가 더 있어. 이 녀석은 그놈들을 지배하는 힘이 있었지. 진짜 힘 말이야. 그리고 바베이도스의 부잣집 아가씨랑 약혼했다는 소문도 들었어. 그렇게 많은 보물을 손에 넣고도 결혼을 안 했다니 이상하지. 전형적인 군인이지, 전쟁을 언제 끝내야 할지 모르는 놈.";
			link.l1 = "고맙다, 토미. 너 정말 머리 잘 쓰는구나.";
			link.l1.go = "LadyBeth_Irons_5";
		break;
		
		case "LadyBeth_Irons_5":
			dialog.text = "응?";
			link.l1 = "아무것도 아니다.";
			link.l1.go = "LadyBeth_Irons_6";
		break;
		
		case "LadyBeth_Irons_6":
			DialogExit();
			ReturnOfficer_Irons();
		break;
		
		case "LadyBeth_Knippel_1": // Книппель
			dialog.text = "이걸 보니 참 쓰리군요, 선장님. 우리가 대체 어디까지 떨어진 거죠?!";
			link.l1 = "우리?";
			link.l1.go = "LadyBeth_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Knippel_2":
			dialog.text = "영국 함대다! 저기 좀 봐라, 저 죽은 쓰레기 더미 위에 빨간 군복들이 조그맣게 뒹굴고 있잖아!";
			link.l1 = "그 '쓰레기' 중에는 우리 사람들도 있어, 찰리. 네 기분은 이해하지만...";
			link.l1.go = "LadyBeth_Knippel_3";
		break;
		
		case "LadyBeth_Knippel_3":
			dialog.text = "좆까, 나리!";
			link.l1 = "네 마음은 이해하지만, 분노와 실망은 블랙우드에게 돌리는 게 좋을 거다. 네가 그렇게 아끼던 영국 함대를 배신하고 이곳으로 이끈 놈이 바로 그 녀석이니까.";
			link.l1.go = "LadyBeth_Knippel_4";
			link.l2 = "그래. 가자, 아직 하루가 끝나지 않았으니까.";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_4":
			dialog.text = "걔네들은 그냥 자기 지휘관을 따랐을 뿐이야!";
			link.l1 = "너도 플리트우드를 따라갔던 것처럼?";
			link.l1.go = "LadyBeth_Knippel_5";
			link.l2 = "그래. 가자, 아직 하루가 끝나지 않았으니까.";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_5":
			dialog.text = "내가 너를 왜 따라가겠어!";
			link.l1 = "블랙우드랑 플리트우드보다 내가 더 나은 선장이란 걸 보여주고 싶군. 가자, 아직 하루가 끝난 게 아니니까.";
			link.l1.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_6":
			dialog.text = "그래, 선장. 그리고 끝나면 다음 전투가 끝날 때까지 마셔줄 거야.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Knippel_7";
		break;
		
		case "LadyBeth_Knippel_7":
			DialogExit();
			ReturnOfficer_Knippel();
		break;
		
		case "LadyBeth_Alonso_1": // Алонсо
			dialog.text = "마드레 데 디오스, 선장님! 괜찮으십니까?";
			link.l1 = "그건 두고 봐야지. 우리 쪽에서 몇 명이나 잃었나?";
			link.l1.go = "LadyBeth_Alonso_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Alonso_2":
			
			dialog.text = "죽었냐? 이번 일에서 우리가 잃은 건 "+sti(pchar.SailorDiedInBattleInfo)+" 놈들. 참견하고 싶진 않소, 선장, 하지만... 내가 경고했잖소!";
			link.l1 = "오늘은 네가 실력을 증명했으니 그 말은 넘어가겠다, Alonso. 그런데 그 많은 재능은 어디서 얻은 거냐?";
			link.l1.go = "LadyBeth_Alonso_3";
		break;
		
		case "LadyBeth_Alonso_3":
			dialog.text = "언젠가 그 이야기를 해드리겠소, 선장님 - 물론 우리가 오래 살아남는다면 말이오.";
			link.l1 = "더 귀중한 조언이라도 있나?";
			link.l1.go = "LadyBeth_Alonso_4";
		break;
		
		case "LadyBeth_Alonso_4":
			dialog.text = "여기에 보물이 있었다면 진작에 누가 찾아냈겠지. 그래도 섬을 수색해서 생존자가 있는지 확인해야 해. 그리고 그들을 어떻게 할지 결정해야지. 블랙우드의 배도 잊지 말아야 해. 그 멋진 스노우에 대해선 좋은 소문만 들었거든. 그런 전리품을 놓치면 아깝잖아, 선장. 물론, 이건 선원들의 입장을 전하는 것뿐이야.";
			link.l1 = "물론이지. 가자. 전리품이 우리를 기다리고 있어!";
			link.l1.go = "LadyBeth_Alonso_5";
		break;
		
		case "LadyBeth_Alonso_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		// Диалог с матросом в гроте Каймана
		case "LadyBeth_MatrosyInGrot":
			dialog.text = "쏘지 마! 항복할게!";
			link.l1 = "너 누구야?";
			link.l1.go = "LadyBeth_MatrosyInGrot_2";
		break;
		
		case "LadyBeth_MatrosyInGrot_2":
			dialog.text = "우... 우리는 '레이디 베스'에서 왔어. 블랙우드 선장의 선원이야. 그분... 그분 살아 계셔?";
			link.l1 = "아니. 네 선장은 죽었어.";
			link.l1.go = "LadyBeth_MatrosyInGrot_3";
		break;
		
		case "LadyBeth_MatrosyInGrot_3":
			dialog.text = "이제 다 끝난 건가... 신께 감사하네.";
			link.l1 = "선장을 애도하는 것 같지 않군.";
			link.l1.go = "LadyBeth_MatrosyInGrot_4";
		break;
		
		case "LadyBeth_MatrosyInGrot_4":
			dialog.text = "너는 이해 못 해. 블랙우드는 위대한 사람이었어. 내가 알던 최고의 선장이었지. 하지만 최근 몇 달 사이에... 변했어. 집착하게 됐고, 잔인해졌지. 우리를 밤낮없이 일하게 만들었어, 존재하지도 않을 무언가를 찾으라고 하면서.";
			link.l1 = "내가 널 우리 선원으로 데려간다. 경험 많은 선원이 필요하거든.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda";
			link.l2 = "패배한 자에게는 화가 따르지, 이 녀석들아. 이제 너희 자리는 내 선창이다. 운이 좋으면 바베이도스의 플랜테이션에서 살아남을지도 모르지.";
			link.l2.go = "LadyBeth_MatrosyInGrot_PlusRaby";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda":
			dialog.text = "정말이야? 너... 너 우리한테... 이 모든 일 끝나고 나서 뭔가 잘못된 거 아닐까봐 두렵지 않아?";
			link.l1 = "모든 사람은 두 번째 기회를 받을 자격이 있지.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda_1";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda_1":
			dialog.text = "감사합니다, 선장님. 맹세컨대, 후회하지 않으실 겁니다. 우리는 훌륭한 선원들이에요. 그리고... 이제 악몽도 멈추겠죠.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 30;
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusRaby":
			dialog.text = "고맙습니다, 정말 고마워요! 적어도 우리는 살아남겠네요. 제발 여기서 데려가 주세요. 이 섬... 마치 저주받은 것 같아요.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+30);
		break;
		
		case "LadyBeth_MatrosyInGrot_exit":
			DialogExit();
			for (i=1; i<=8; i++)
			{
				sld = CharacterFromID("LadyBeth_MatrosyPryachutsya_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		break;
		
		// Диалог с матросом на Леди Бет
		case "LadyBeth_EnemyMatros_1":
			dialog.text = "뭐야, 이게?! 감히 '레이디'를 공격하고 제레미까지 죽이다니? 너희 악당들, 여기서 살아나갈 생각 마라, 선장님이 돌아오시면...";
			link.l1 = "네 선장은 죽었다. 제러미가 먼저 쐈고, 나는 피로 값을 치른 대가로 네 '레이디'를 정당한 전리품으로 가져간다.";
			link.l1.go = "LadyBeth_EnemyMatros_2";
		break;
		
		case "LadyBeth_EnemyMatros_2":
			dialog.text = "선장님이... 죽었다고? 거짓말하지 마, 이 개자식아! 너 따위가 그분 제복의 단추 하나만도 못해!";
			link.l1 = "저 제복이 의미가 있었다면, 이미 사라진 블랙우드에게나 그랬겠지. 선택은 너희 몫이다 - 죽은 자를 위해 싸울 건지, 아니면 목숨을 구할 건지.";
			link.l1.go = "LadyBeth_EnemyMatros_3";
		break;
		
		case "LadyBeth_EnemyMatros_3":
			if (CharacterIsHere("Helena"))
			{
				StartInstantDialog("Helena", "LadyBeth_EnemyMatros_Helena_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Knippel"))
			{
				StartInstantDialog("Knippel", "LadyBeth_EnemyMatros_Knippel_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Irons"))
			{
				StartInstantDialog("Irons", "LadyBeth_EnemyMatros_Irons_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			dialog.text = "싸우지 않고는 이 배를 넘겨주지 않겠다!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		case "LadyBeth_EnemyMatros_Helena_1":
			dialog.text = "들어봐, 얘들아. 너희가 선장에게 충성심이 있다는 거 알아. 그건 존경받을 만한 일이야. 하지만 그는 죽었고, 너희는 살아 있지. 이제 어떻게 살아갈지 너희가 결정해야 해. 우리는 너희에게 새롭게 시작할 기회를 주고 있어.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_Knippel_1":
			dialog.text = "선장님, 이 자들은 적이 아닙니다. 그저 명령을 따랐을 뿐입니다. 이들 중 많은 이가 예전 왕실 해군 출신으로, 훈련도 잘 받았고 규율도 있습니다. 그들의 실력을 써먹지 않는 건 낭비입니다. 얘들아, 나도 함대에서 오래 복무하면서 너희 입장에 여러 번 처해봤다. 그리고 나는 옳은 선택을 했지. 너희도 그렇게 해라.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
		break;
		
		case "LadyBeth_EnemyMatros_Irons_1":
			dialog.text = "자, 이봐, 선원 놈들아! 선택은 간단하다. 선창에 갇힌 죄수로 살든, 아니면 우리 선원이 되어 밥도 잘 먹고 월급도 받으며 살든, 둘 중 하나지. 아니면... (목을 가로지르며) 나라면 첫 번째를 고르겠다!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_10";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_5":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_6", "Quest\ShipsPack\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_6":
			dialog.text = "...";
			link.l1 = "넌 내 선원이 될 거야.";
			link.l1.go = "LadyBeth_EnemyMatros_7";
			link.l2 = "패배한 자에게 화가 있으리라, 이 녀석들아. 이제 너희 자리는 내 선창이다. 운이 좋으면 바베이도스의 어느 플랜테이션까지 살아남을지도 모르지.";
			link.l2.go = "LadyBeth_EnemyMatros_9";
		break;
		
		case "LadyBeth_EnemyMatros_7":
			dialog.text = "우릴 네 선원으로 받아준다고? 이 모든 일 후에?";
			link.l1 = "좋은 선원은 언제나 소중하지. 그리고 블랙우드 선장은 자기 부하를 고를 줄 알았지.";
			link.l1.go = "LadyBeth_EnemyMatros_8";
		break;
		
		case "LadyBeth_EnemyMatros_8":
			dialog.text = "감사합니다, 선장님. 실망시키지 않겠습니다.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 12;
		break;
		
		case "LadyBeth_EnemyMatros_9":
			dialog.text = "음... 적어도 이 모험이 끝날 수 있는 유일한 방법이었지. 용서해 주시오, 블랙우드 선장. 우리가 당신을 지키지 못했소.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+12);
		break;
		
		case "LadyBeth_EnemyMatros_10":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_11", "Quest\ShipsPack\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_11":
			dialog.text = "싸우지 않고는 이 배를 내줄 수 없어!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		// Диалог с Элизабет Бишоп
		case "LadyBeth_Elizabeth_1":
			dialog.text = "...";
			link.l1 = "실례합니다. 당신이 엘리자베스인가요?";
			if (pchar.sex == "man") link.l1.go = "LadyBeth_Elizabeth_2";
			if (pchar.sex == "woman") link.l1.go = "LadyBeth_Elizabeth_Woman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Elizabeth_2":
			dialog.text = "그래, 나야. 그런데 너는 누구지?";
			link.l1 = "Captain "+GetFullName(pchar)+". 나... 알버트 블랙우드를 알았어.";
			link.l1.go = "LadyBeth_Elizabeth_3";
		break;
		
		case "LadyBeth_Elizabeth_3":
			dialog.text = "내 알버트? 오, 맙소사... 걔... 걔 괜찮은 거야?";
			link.l1 = "유감이지만, 아니오. 그는 전투에서 죽었소. 마지막까지 싸웠지.";
			link.l1.go = "LadyBeth_Elizabeth_4";
		break;
		
		case "LadyBeth_Elizabeth_4":
			dialog.text = "나... 나도 그럴 줄 알았어. 그렇게 오랜 세월 동안 아무 소식도 없이... 있잖아, 난 그를 기다렸어. 정말 오래 기다렸지. 아버지는 알베르트가 승진만 기다리면 된다고 하셨어. 총독이 이미 다 결정했다면서, 몇 달만 참으면 된다고 했지. 그런데 알베르트는... 그 말을 전혀 다르게 받아들였어. 부자가 되어 돌아와 내 손을 잡을 자격을 얻겠다고 했지. 그리고 떠났어. 그냥... 떠나버렸어.";
			link.l1 = "그는 마지막 날까지 너를 생각했어.";
			link.l1.go = "LadyBeth_Elizabeth_5";
		break;
		
		case "LadyBeth_Elizabeth_5":
			dialog.text = "어리석었지. 나는 그의 보물이 필요하지 않았어. 나는 그의 돈이 아니라 그를 사랑했거든. 그와 함께 도망칠 준비도 되어 있었어... 하지만 그는 너무 자존심이 셌지. 나는 편지를 기다렸어, 어떤 소식이라도... 그런데 도착한 건 이 이상한 설명서뿐이었어. 너무 차갑고 계산적인 문서였지... 내가 알던 알베르트와는 전혀 달랐어. 그때 나는 그를 잃었다는 걸 깨달았어.";
			link.l1 = "그의 소지품 중에서 이걸 발견했어.";
			link.l1.go = "LadyBeth_Elizabeth_6";
		break;
		
		case "LadyBeth_Elizabeth_6":
			dialog.text = "내 집으로 가는 지도라고? 내가 그의 가장 큰 보물이었다고? 참 아이러니하군. 그는 카리브 해 전역을 돌아다니며 보물을 찾았지만, 정작 그에게 가장 소중한 건 항상 여기 있었지... 잠깐. 너에게 줄 게 있어. 이건 알버트의 매뉴얼이야. 1년 전에 나한테 보냈지. 이걸로 보물을 찾고 나에게 돌아올 수 있다고 했어. 이제 이게 너한테 더 쓸모 있을 거야.";
			link.l1 = "고마워, 엘리자베스. 이렇게 되어 미안해.";
			link.l1.go = "LadyBeth_Elizabeth_7";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_7":
			dialog.text = "그리고 저 결혼했어요, 선장님. 비숍 씨와요. 아버지가 강권하셨어요. 선장님은 이 사람을 모르시죠... 그리고 알고 싶지도 않으실 거예요. 매일 생각해요. 알버트가 그냥... 돌아오기만 했더라면 내 인생이 어땠을까 하고요.";
			link.l1 = "이제 나도 그것에 대해 생각해 보겠다.";
			link.l1.go = "LadyBeth_Elizabeth_8";
		break;
		
		case "LadyBeth_Elizabeth_8":
			dialog.text = "안녕히 가십시오, 선장님. 그리고... 몸조심하십시오. 유령을 쫓지 마십시오.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
		
		case "LadyBeth_Elizabeth_Woman_2":
			dialog.text = "그래, 나야.";
			link.l1 = " 헬렌 맥아더 선장. 나는... 앨버트 블랙우드를 알았어.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_3";
		break;
		
		case "LadyBeth_Elizabeth_Woman_3":
			dialog.text = "내 알버트? 오, 맙소사... 그가... 그런데 너는 누구냐?";
			link.l1 = "헬렌 맥아더 선장, 방금 말했다. 나는 내 배를 직접 지휘한다.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_4";
		break;
		
		case "LadyBeth_Elizabeth_Woman_4":
			dialog.text = "선장? 여자 선장이라고? 너... 너 알베르와 함께 있었던 거야? 어떤 의미로... 그를 알았던 거지?";
			link.l1 = "선장으로서만 그렇지. 미안하지만, 알버트는 죽었어. 그의 마지막 전투를 내가 직접 봤다.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_5";
		break;
		
		case "LadyBeth_Elizabeth_Woman_5":
			dialog.text = "알겠소. 내 의심을 용서하시오. 그저... 블랙우드 선장은 언제나 여자들의 관심을 끌었으니까. 여기 바베이도스에서도. 아니, 특히 여기서 말이오.";
			link.l1 = "너는 그를 사랑했지.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_6";
		break;
		
		case "LadyBeth_Elizabeth_Woman_6":
			dialog.text = "진심으로 그랬어. 아버지는 알버트에게 승진만 기다리면 된다고 하셨어. 몇 달만 참으면 될 일이었지. 하지만 알버트는 아버지의 말을 가난해서 거절한 거라고 받아들였어. 보물을 가지고 돌아오겠다고 했지. 그리고 떠났어.";
			link.l1 = "남자들과 그 자존심이지!";
			link.l1.go = "LadyBeth_Elizabeth_Woman_7";
		break;
		
		case "LadyBeth_Elizabeth_Woman_7":
			dialog.text = "운이 좋군, MacArthur 선장. 넌 자유야. 원하는 곳 어디든 항해할 수 있지. 농장주도 없고, 네 운명을 결정하는 아버지도 없어. 널 자기 소유물로 여기는 남편도 없고.";
			link.l1 = "자유는 큰 대가를 치러야 얻을 수 있지. 그리고 매일 그 자유를 지켜내야 해.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_8";
		break;
		
		case "LadyBeth_Elizabeth_Woman_8":
			dialog.text = "이 일에 도움이 될 만한 게 있을지도 모르겠군. 자, 받아. 이건 그의 보물 사냥 매뉴얼이야. 알베르트가 약 1년 전에 나한테 보냈지. 자기 인생 최고의 작품이라고 했어. 이걸로 부자가 돼서 내게 돌아올 수 있을 거라고도 했고. 하지만 페이지를 넘길수록, 그는 점점 내가 알던 알베르트와는 달라졌지.";
			link.l1 = "고맙다. 내가 가지고 있을게.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_9";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_Woman_9":
			dialog.text = "제발요, 선장님... 자유를 소중히 여기세요. 저는 비숍 대령과 결혼했어요. 우리 아버지조차 두려워하는 남자예요. 만약 저도 선장님처럼 자유로웠다면... 모든 게 달라졌을 거예요.";
			link.l1 = "알고 있어.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_10";
		break;
		
		case "LadyBeth_Elizabeth_Woman_10":
			dialog.text = "안녕히 가십시오, 선장님. 순풍이 함께하길 바랍니다.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
	}
} 