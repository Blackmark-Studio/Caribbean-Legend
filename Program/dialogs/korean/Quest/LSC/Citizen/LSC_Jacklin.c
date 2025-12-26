// Жаклин Тьюрам - торговый капитан
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
				dialog.text = "너랑 얘기하고 싶지 않아. 너는 아무 이유 없이 평화로운 민간인들을 공격하고 싸움을 부추기잖아. 잘 가라!";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "안녕하십니까, 나리. 여기 처음 오셨지요?";
				link.l1 = TimeGreeting()+"그래, 그런 것 같군. 내 이름은 "+GetFullName(pchar)+". 그리고 너는 누구냐?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, 봉주르 "+GetFullName(pchar)+"! "+TimeGreeting()+"! 오늘은 무엇을 도와줄까?";
				link.l1 = LinkRandPhrase("안녕하세요, Turam 나리! 요즘 소식 좀 들려주시오.", "섬에서 새로운 일이 있었나?", "최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "그냥 어떻게 지내는지 궁금해서 왔어. 잘 있어!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "자크 튀람이오. 2년 전만 해도 나는 존경받는 부유한 상인이었고, 내 플라이트의 선주이자 선장이었소. 하지만 지금은 교회 쥐만큼이나 가난해졌고, 내 처지가 달라질 희망도 없소.\n여기서 운 좋은 사람들은 금이나 보석, 보물로 가득 찬 배를 찾기도 하지만, 나는 그런 사람이 아니오. 내가 찾은 건 두블룬이 든 작은 상자 하나와 잡동사니 몇 개뿐이었지.\n그래도 그걸로 음식은 살 수 있으니 굶지는 않겠지... 만나서 반갑소, 나리. 이야기 나누는 건 괜찮으니 편하게 말하시오.";
			link.l1 = "나도 만나서 반갑네, 자크. 오 르부아!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("안녕하세요, Turam 나리! 최근 소식 좀 들려주시오.", "섬에 무슨 새로운 일이 있었나?", "최근 소문 좀 들려줄래?");
			link.l2.go = "rumours_LSC";
			link.l3 = "이 섬에 대해 몇 가지 물어보고 싶어.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "귀 기울이고 있네.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "여기엔 어떻게 오게 됐어?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "여기서 뭐 하고 있지?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "말해 봐... 섬에 여인들도 있는 것 같은데...";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "넓은 세상으로 돌아가고 싶어?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "별거 아니야.";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "내 이야기를 듣고 싶다고? 좋아. 이미 알다시피, 나는 상인이었어. 어느 날, 나는 내 오래된 플루이트선을 타고 토르투가에서 벨리즈로 항해했지. 선창에는 흑단과 카카오가 가득했어 – 화물에 내 전 재산을 쏟아부었지.\n화물을 엄청난 가격에 사겠다는 사람과 아주 이익이 남는 거래를 약속해놨었어. 한몫 크게 잡을 기회였지. 모든 게 순조로웠고, 하늘엔 구름 한 점 없었으며, 내 배는 새처럼 빨랐어. 그런데 문제가 닥쳤지.\n쿠바 근처를 항해하며 스페인 순찰선을 피해가고 있었는데, 갑자기 해적 갤리온에게 습격당했어. 스페인 영토 한가운데서 대체 뭘 하고 있었던 걸까? 도망치려 했지만, 그 갤리온은 뜻밖에도 빨랐어.\n해적들은 우리를 따라잡아 공격했지. 그놈들의 쿨브린에는 산탄이 장전되어 있었고, 첫 일제 사격에 내 선원 절반이 죽고 나머지는 완전히 사기가 꺾였어. 제대로 싸워보고 싶었지만, 내 선원들과 장교들이 나를 말렸지. 우리는 항복했어.\n해적들은 우리 화물을 가져가고 대포도 바다에 던져버렸어. 이게 끝이 아니길 바랐지; 화물을 잃은 건 큰 타격이었지만, 화물 운송 계약으로 다시 일어설 수 있을 거라 생각했어.\n하지만 운명은 달랐지. 해적 놈들은 무방비 상태인 내 플루이트선을 향해 포격을 시작했어 – 대포도 없는 우리는 그야말로 먹잇감이었지. 아직도 해적들의 웃음소리가 귀에 맴도는군...\n갤리온은 떠나고 우리는 난파선 잔해에 매달려 있었어. 그러다 거센 돌풍이 불어와 파도가 나를 바다로 쓸어버렸지. 부러진 돛대에 몸을 묶고 겨우 떠 있었어.\n상어와의 아찔한 사연은 생략할게. 끝없는 시간이 흐른 뒤 해류가 나를 이 정의의 섬으로 데려왔지. 그렇게 살아남았어.";
			link.l1 = "그래, 정말로 슬픈 이야기야.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "나도 다른 주민들처럼 살아. 바깥쪽에서 귀중품을 찾아서 음식과 바꿔 먹지. 인디언 추장의 보물이나 스페인 금화로 가득 찬 갈레온선을 찾는 게 꿈이야...\n소금에 절인 소고기나 생선 말고 다른 걸 먹는 게 소원이지. 여기 거대한 게를 사냥하던 남자가 있었는데, 나는 집게 하나에 두블론 다섯 닢씩 주고 며칠 동안 그걸로 식사를 하곤 했어.\n안타깝게도 그가 죽었지... 뭐, 아무도 놀라진 않았어. 그 게 사냥이 워낙 위험한 일이거든.";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "네가 뭘 암시하는지 알겠어. 그래, 이곳에도 사랑과 음모가 있지. 왜 없겠어? 남자는 여자를 위해, 여자는 남자를 위해 태어난 거니까. 그게 자연의 이치야. 질리안이나 타네케에게 시도해봐도 돼. 둘 다 젊고 예쁘고 연애에 열려 있거든.\n나는 이미 여자를 찾았어. 나탈리아라는 사람이야. 산초 선술집에서 일하는 웨이트리스지. 정말 멋진 여자야. 솔직히 말해서, 내가 이곳에서 처음 몇 달 동안 미치지 않고 버틸 수 있었던 건 오직 그녀 덕분이라고 생각해. 그녀가 나를 많이 도와줬고, 지금은 우리가 함께하고 있어.";
			link.l1 = "아, 낭만적이군!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "좋은 질문이군. 나도 물론 그러고 싶지. 하지만 생각해 보면... 난 빈털터리야. 가진 돈 전부를 화물에 투자했는데, 이제 그 화물도, 내 배도 다 가라앉았지. 남은 게 아무것도 없어. 지금 돈을 벌 수 있는 유일한 방법은 네덜란드 서인도 회사에서 일하는 것뿐이야. 물론 그들이 날 고용해 준다면 말이지.\n슈너 한 척이랑 약간의 보급품을 살 돈만 있었어도... 하지만 없으니, 그냥 섬에 머무르는 게 낫겠어. 적어도 여기선 빵 한 조각을 위해 새벽부터 해질 때까지 일할 필요는 없으니까.";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("누가… 아, 도둑이야!", "내 물건에서 손 떼, 이 악마야!", "저건 내 궤짝이야! 저리 비켜!");
			link.l1 = "젠장!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "감히 내 서랍을 뒤지다니!";
			link.l1 = "조용히 해!";
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
			dialog.text = LinkRandPhrase("나리, 제발 무기를 거두어 주십시오. 저를 겁주고 계십니다.", "있잖아, 무기를 뽑은 채로 뛰어다니다가 다칠 수도 있겠어.", "여자들한테 기사인 척 잘난 척하지 마라. 집어넣어...");
			link.l1 = LinkRandPhrase("좋아.", "좋아.", "어, 그렇지...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "나리, 이 섬의 시민으로서 검을 거두어 주시길 부탁드립니다.", "무기를 뽑은 채로 돌아다니는 건 위험하오, 나리. 제발 무기를 거두시오.");
				link.l1 = LinkRandPhrase("좋아.", "좋아, 그럼.", "말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "나리, 제발 무기를 거두어 주십시오. 저를 겁주고 계십니다.", "나는 남자들이 해적처럼 행동하면서 무기를 들고 돌아다니는 게 마음에 들지 않아.");
				link.l1 = RandPhraseSimple("미안하오, 이제 치우겠소.", "나는 그것을 치우고 있다.");
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
