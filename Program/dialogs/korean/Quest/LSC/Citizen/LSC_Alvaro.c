// Альваро Гомец - капитан
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
				dialog.text = "나리, 나는 당신에게 아무 말도 하지 않겠소! 당신은 아무 이유 없이 평화로운 사람들을 공격하잖소. 지옥이나 꺼지시오!";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "아, 새로운 얼굴이군! 반갑다! 언제 여기 온 거야? 최근에 난파된 배는 기억이 안 나는데.";
				link.l1 = TimeGreeting()+". 내 이름은 "+GetFullName(pchar)+". 그리고 내 배는 밤중에 조용히, 순식간에 가라앉았지. 내 선원들 중에서 오직 나만이 이 섬까지 헤엄쳐 왔어...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, "+GetFullName(pchar)+"! "+TimeGreeting()+"! 뭐라도 원하는 거야?";
				link.l1 = LinkRandPhrase("나한테 해줄 만한 흥미로운 이야기라도 있나?", "섬에 무슨 새로운 일이라도 있었나?", "최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "이 섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "그냥 어떻게 지내는지 궁금해서 왔어. 잘 있어!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "알겠소. 아, 내가 자기소개를 깜빡했군. 실례하오, 나리. 내 이름은 알바로 고메스요, 한때는 브리그의 선장이었소. 에휴, 이제 내 멋진 배는 바깥 고리 너머 바다 밑바닥에 누워 있지... 그때 이후로 많은 세월이 흘렀소. 아, 인생이란 그런 거지. 만나서 반갑소!\n";
			link.l1 = "나도 반갑소, 고메스 나리.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("나한테 해줄 만한 재미있는 이야기라도 있어?", "섬에 무슨 새로운 일이라도 있었어?", "최근 소문 좀 들려줄래?");
			link.l2.go = "rumours_LSC";
			link.l3 = "이 섬에 대해 몇 가지 물어보고 싶어.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "듣고 있소, 나리.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "한때 선장이었다고 했지. 어떻게 정의의 섬에 오게 된 거야?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "이 섬에서의 삶에 대해 뭐 말해줄 수 있지?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "말해 봐, 여기 주민들끼리는 평화롭게 지내나? 물론 클랜들끼리는 빼고 말이야.";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "여기 주민들은 식량을 어디서 구하지?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없습니다. 실례...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "다른 사람들과 마찬가지로, 폭풍에 휘말렸지. 나는 돛대와 키를 잃었고, 조류에 휩쓸려 암초에 내던져졌어. 내 배는 바깥 고리에도 닿지 못하고 산산조각나 버렸지. 살아남은 건 몇 명뿐이야, 나도 그중 하나고.";
			link.l1 = "슬픈 이야기로군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "뭐라고 해야 할까? 살아가는 데 필요한 건 다 있어. 하지만 가끔은 여기서 정말 지루해지고, 그 우울함이란... 첫 해는 정말 힘들었지. 그래도 이제는 정의의 섬에 익숙해졌어. 불쌍한 내 아내 사브리나가 안쓰러워. 분명 내가 죽은 줄 알겠지. 다시 결혼해서 행복하게 살고 있길 바랄 뿐이야.\n너도 네 처지에 너무 낙담하지 마, 친구야. 곧 익숙해질 거야. 선술집, 상점, 교회도 들러보고, 사람들도 만나 봐. 하지만 정말 필요하지 않으면 나르발이나 리바도스 쪽엔 가지 마! 걔네들은 영악한 놈들이거든.";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "꽤 평화롭게 지내고 있어. 우리에겐 문서로 된 법은 없지만, 특별한 이유 없이 누군가를 때리거나, 하느님 맙소사, 살인을 저지르면 격리당하게 돼. 심하면 밤중에 바다에 던져질 수도 있지.\n예전에 이 섬엔 소속 없는 싸움꾼들이 몇 명 있었어. 정말 악질 놈들이었지. 첫 번째는 사라졌고, 두 번째는 타르타로스 감방에서 몇 달 썩다가 죽었어.\그렇다고 폭력적인 공격에 스스로를 지키지 말라는 건 아니야. 대체로 이곳 사람들은 꽤 평화로워. 애벗은 으스대긴 해도 공격적이진 않고, 카셀은 진짜 개자식이지만 손은 깨끗이 해. 프랫은 전과자지만 해를 끼치진 않아.\n여기엔 해군 장교 출신이 둘 있어. 로더데일과 솔데라. 둘 다 이 섬 근처에서 해전하다가 여기 오게 됐지. 둘 다 살아남았고, 서로를 향한 피비린내 나는 계획을 계속 꾸미고 있어.";
			link.l1 = "흥미롭군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "난파선의 창고에서 가져온 거지, 그렇지. 예전에는 모든 식량을 산 아우구스틴에 보관하고 모두가 똑같이 나눠 썼어. 그런데 해적들이 와서 산 아우구스틴을 빼앗아 갔지. 이제는 우리가 원래 갖고 있던 식량을 사려고 돈을 쥐어짜고 있어, 정의의 섬 전체를 말이야!\n우리는 우리만의 은닉처가 있어서 굶지는 않아. 또, 물고기도 잡고 새도 쏘지만, 제일 맛있는 고기는 거대한 게에서 나와. 그 고기는 아주 맛있고 영양도 풍부하지. 다만, 그놈들은 좀처럼 바깥 고리 가까이로 오지 않아.\n게를 사냥하려고 잠수하는 건 너무 위험해. 예전에 물속에서 게를 사냥할 만큼 용감한 남자가 한 명 있었는데, 결국 운이 다했지. 그 뒤로는 아무도 게 고기를 얻으려고 잠수하지 않아.";
			link.l1 = "흥미롭군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("도둑놈! Thief!", "네 멋대로 가져갈 수 있다고 생각해?! 칼을 맞이해라!", "impudently 내 물건을 훔치다니! 내 칼맛을 봐라!");
			link.l1 = "젠장!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "뭐?! 내 상자를 털기로 했다고? 가만두지 않겠어!";
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
			dialog.text = LinkRandPhrase("아이, 카람바! 무기 집어넣어, 이봐!", "여기 사람들은 칼을 뽑고 돌아다니는 자들을 곱게 보지 않아.", "이봐, 나리, 칼을 뽑고 돌아다니는 건 위험하니까 집어넣어...");
			link.l1 = LinkRandPhrase("좋아.", "그래.", "말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "이 도시의 시민으로서, 칼을 거두어 주시길 부탁드립니다.", "이 도시 시민으로서, 칼을 거두어 주시길 부탁드립니다.");
				link.l1 = LinkRandPhrase("좋아.", "뭐, 그러든가.", "말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "조심해, 친구야, 그런 무기를 들고 돌아다니면 말이야. 나까지 불안해지잖아...", "내 앞에서 그렇게 무기를 휘두르지 마. 무섭단 말이야...");
				link.l1 = RandPhraseSimple("알겠소.", "치우고 있어.");
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
