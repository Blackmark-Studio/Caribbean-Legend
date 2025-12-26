// Адольф Барбье - авантюрист
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "너랑은 아무 상관도 없거든. 너희들은 아무 이유 없이 평화로운 주민들을 공격하고 싸움을 걸잖아. 썩 꺼져!";
				link.l1 = "음...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "안녕, 안녕... 너 처음 보는 얼굴이네. 새로 온 거야?";
				link.l1 = "정의의 섬에 처음 왔냐고? 그래, 맞아. 내 이름은 "+GetFullName(pchar)+", 선원이자 모험가.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, "+GetFullName(pchar)+"! "+TimeGreeting()+"! 뭐 필요해?";
				link.l1 = LinkRandPhrase("나한테 해줄 만한 흥미로운 얘기라도 있어?", "섬에 무슨 새로운 일이 있었나?", "최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "이 섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "그냥 어떻게 지내는지 궁금했어. 잘 가!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "하, 나도 그래. 난 뱃사람은 아니지만, 모험에 대한 열정 때문에 여기까지 오게 됐지. 이제 다른 사람들처럼 이 배들의 무덤에서 썩어갈 거야. 그런데, 내 이름은 아돌프 바르비에야.";
			link.l1 = "만나서 반가웠어, Adolf. 안녕히 가.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("나한테 해줄 만한 재미있는 얘기라도 있어?", "섬에 무슨 새로운 일이 있었나?", "최근 소문 좀 들려줄래?");
			link.l2.go = "rumours_LSC";
			link.l3 = "이 섬에 대해 몇 가지 물어보고 싶어.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		//----------------------------------Адольф Барбье----------------------------------------
		case "Adolf":
			dialog.text = "도대체 왜 허락도 없이 내 집에 들어온 거야?!";
			link.l1 = "아돌프, 손님에게 너무 불친절하군. 너와 볼 일이 있어.";
			link.l1.go = "Adolf_1";
		break;
		
		case "Adolf_1":
			dialog.text = "나는 모르는 놈이랑 거래 안 해! 나가!";
			link.l1 = "그냥 그렇게? 그러니까 너는 나하고는 거래 안 하고, 나르발 녀석들이랑은 한다는 거야? 참 한심하군...";
			link.l1.go = "Adolf_2";
		break;
		
		case "Adolf_2":
			dialog.text = "무슨 소리야, 어릿광대 녀석? 너랑 나발족이 무슨 상관인데? 내가 내쫓기 전에 마지막으로 나갈 기회 줄게!";
			link.l1 = "간도 없는 놈이... 이제 내 말 잘 들어! 제독을 쏘려고 쓸 스투첸은 어디 있지? 자진해서 말할 거냐, 아니면 내가 더 강하게 나와야 하냐?";
			link.l1.go = "Adolf_3";
		break;
		
		case "Adolf_3":
			dialog.text = "뭐? 너 미쳤냐, 이 친구야? 내 슈투첸은 이미 팔았어 - 이제 더는 없어! 그리고 누구한테 팔았는지는 네 알 바 아니야; 그걸로 뭘 하든 난 신경 안 써. 그리고 난 아무도 쏘지 않을 거야 - 제독이든, 장군이든, 아무도! 알겠어, 이 개자식아?";
			link.l1 = "네가 거짓말쟁이이자 살인자라는 걸 알고 있어, 아돌프. 네가 그걸 판 게 아니라 되찾았다는 것도 알아. 그리고 네가 빚을 갚고 이 선실을 사기 위해 거액을 받았다는 것도 알고 있지--";
			link.l1.go = "Adolf_4";
		break;
		
		case "Adolf_4":
			dialog.text = "이건 내 돈이야! 내가 번 돈이라고! 그리고 내 슈투첸도 팔았어!";
			link.l1 = "거짓말하지 마, 아돌프. 너는 나르발 놈들한테 고용돼서 제독을 쏘라고 했잖아. 그놈들이 네 슈투첸을 되찾으라고 돈도 줬고, 이 자리도 마련해줬지. 이 문 뒤에 있는 선수대가 상어의 저택 뒷발코니를 쏠 수 있는 정의의 섬 유일한 곳이라는 거, 나보다 네가 더 잘 알잖아.";
			link.l1.go = "Adolf_5";
		break;
		
		case "Adolf_5":
			dialog.text = "너 미쳤구나, 이 친구야! 정신병원에 가야 할 거야! 나는 세실이 이 선실에서 나가길 반년이나 기다렸어--";
			link.l1 = "그만해! 내가 너와 네 선실을 수색할 거야. 슈투첸도 찾아낼 거고, 그 외의 증거도 더 찾을 거다! 확신해. 그리고 나서 우리 둘이 함께 샤크를 만나러 갈 거야. 그가 네 눈을 보고 진실을 알아낼 테니까.";
			link.l1.go = "Adolf_6";
		break;
		
		case "Adolf_6":
			dialog.text = "이런, 너 미친 놈아! 미친 쓰레기가 내 물건에 손대게 하느니 차라리 죽겠다!";
			link.l1 = "좋아, 그럼. 네가 죽으면 네 허락 따윈 필요 없지.";
			link.l1.go = "Adolf_7";
		break;
		
		case "Adolf_7":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "barmen", "stay");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_AdolfDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
	case "int_quests":
			dialog.text = "자, 이야기나 해보자. 뭘 알고 싶은데?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "여기 어떻게 오게 됐어?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "이곳 토착 클랜들에 대해 뭐 좀 말해줄 수 있나?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "배 바깥쪽 고리를 탐험해 봤어?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "이 섬이 쿠바나 본토와 어떤 연관이 있나?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없습니다. 실례합니다...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "나는 스페인 선원 이그나시오 알바라도의 연대기를 발견했어. 그는 이 섬을 아주 자세하게 묘사했지. 몇몇 특정한 배들—산 아우구스틴, 산 헤로니모, 그리고 타르타로스—도 언급했어. 이 배들은 모두 데 베탕쿠르트의 함대 소속이었고, 50년도 더 전에 사라졌지.\n나는 그 원정대를 조사했어. 알고 보니 네 번째 배가 있었는데, 이름은 산타 안나였고, 함대의 금고—즉, 두블론 더미—를 싣고 있었어! 게다가 배들 창고에는 금광석도 실려 있었지. 그래서 나는 이 섬을 찾기로 결심했어.\n내가 아는 선장과 거래를 해서 그의 스쿠너를 타고 출항했지. 어떻게 끝났을지 짐작할 수 있을 거야: 우리는 섬을 찾았고, 데 베탕쿠르트의 배들도 찾았고, 심지어 그의 손자인 안토니오 데 베탕쿠르트도 만났어. 그 이후로 나는 쭉 여기 있었지.\n스쿠너는 암초에 부서졌고, 내 동료는 죽었어. 나와 다른 생존자들은 겨우 헤엄쳐서 여기까지 왔지. 가장 안타까운 건, 내가 찾던 걸 결국 못 찾았다는 거야—산타 안나의 금고도, 금광석도 말이야.";
			link.l1 = "흥미로운 이야기군. 나도 알바라도의 연대기를 읽어봤어.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "리바도스 놈들은 저주받은 이교도 쓰레기야. 걔네는 드 베탕쿠르가 아프리카에서 데려온 흑인 노예들의 후손이지. 우리 백인들한테 칼이랑 머스킷 쓰는 법을 배웠다지만, 여전히 야만인일 뿐이야.\n나르발들은 괜찮은 사람들이야. 똑똑하고, 싸움도 제법 하지. 장인들도 많고. 나도 아는 사람이 많아. 언젠가 그들 클랜에 들어갈지도 모르지.\n해적들은 진짜 골칫거리야, 젠장할 놈들! 쳐들어오더니 우리 보급품을 빼앗고, 이제는 우리 음식까지 우리한테 팔아먹으려고 해! 개자식들 아니냐? 우리가 숫자도 실력도 부족해서 쫓아낼 수 없는 게 한탄스럽지. 결국 저 피투성이 놈들이랑 같이 살아야 해.";
			link.l1 = "흥미롭군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "그래. 사람이라면 돈을 벌어야지. 젠장할 해적놈들이 음식값으로 금이든 페소든 값진 걸 요구하거든. 나 같은 섬 주민한테는 클랜들보다 좀 싸게 팔긴 하지만, 자선은 아니야. 다행히 바깥 고리에 난파선이 많아서 약탈할 게 넘쳐나지; 아직 손도 안 댄 배들도 많아, 잔해 속에 그대로 남아 있거든.\n재미있는 일이긴 한데, 위험하지. 침수된 창고에 빠질 수도 있고, 뼈가 부러지거나 밧줄에 휘말릴 수도 있고, 나무 들보에 맞아 죽거나, 아니면 거대한 게한테 잡아먹힐 수도 있어 — 그놈들은 저 난파선 근처를 자주 돌아다니거든.";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "안타깝게도 그렇지 않아. 예전에는 쿠바에서 온 버커니어와 밀수꾼들이 이곳에 자주 들러 식량을 금과 난파선 물품으로 교환했다고 해. 그리고 때때로 나르발들이 식민지로 떠나기도 했지. 하지만 이제 그런 일은 다 끝났어. 요즘은 누구도 외곽 고리 너머로 작은 허술한 배를 타고 나가려 하지 않아 – 폭풍에 산산조각 날 테니까. 여기엔 더 나은 배도 없고.";
			link.l1 = "안타깝군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("거기서 뭐 하는 거야, 어? 도둑놈!", "저것 좀 봐! 내가 등만 돌리면 바로 내 상자를 뒤지려고 하잖아!", "내 상자를 털기로 했군, 응? 그냥 넘어가지 않을 거야!");
			link.l1 = "젠장!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "뭐?! 내 상자를 털기로 했나? 그냥 넘어가지 않을 거야!";
			link.l1 = "저주받을 계집애!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("이봐, 무기는 집어넣는 게 좋겠어. 그거 보면 신경이 곤두서거든.", "여기서는 칼 들고 돌아다니는 거 용납 안 돼. 집어넣어.", "이봐, 칼 들고 돌아다니는 기사 흉내 내지 마라, 너한테 안 어울려. 집어넣어...");
			link.l1 = LinkRandPhrase("좋아.", "좋아.", "말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "이봐, 나는 이 도시의 시민이니 칼을 거둬 줘.", "이봐, 나는 이 도시의 시민이니 칼을 거둬 주게.");
				link.l1 = LinkRandPhrase("좋아.", "좋아.", "말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "조심해, 친구. 그런 무기를 들고 돌아다니면 내가 불안해지잖아...", "난 남자들이 내 얼굴 앞에서 무기를 휘두르는 거 싫어. 무섭거든...");
				link.l1 = RandPhraseSimple("알겠어.", "나는 이걸 치우고 있어.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
