// Джозеф Лодердэйл - английский военный офицер
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
				dialog.text = "꺼져라, 나리! 너는 죄 없는 이들을 공격하고 천한 도적처럼 싸우는구나! 내 눈앞에서 사라져라!";
				link.l1 = "음...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "좋은 하루입니다, 나리. 이곳에서 귀족분을 만나게 되어 기쁩니다.";
				link.l1 = TimeGreeting()+". 사실 카리브 해에서 평민들 사이에서 너무 오래 지내다 보니 내가 귀족이라는 사실조차 잊어버릴 지경이야.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetFullName(pchar)+"! 반갑군! 무슨 일로 왔나?";
				link.l1 = LinkRandPhrase("좋은 하루야, Joseph! 정의의 섬에는 무슨 새 소식이 있지?", "섬에 무슨 새로운 일이 있었나?", "최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "이 섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "그저 인사나 전하려고 왔어. 잘 가!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "오, 게다가 겸손한 귀족이시군! 진정한 신사로군요! 당신과 나는 친구가 될 것 같소 – 당신은 그 거만한 아바 신부와는 다르군... 소개하지요: 연방 해군의 조셉 로더데일 선장입니다.";
			link.l1 = "만나서 반갑소, 선장. "+GetFullName(pchar)+" 명령만 하십시오!";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "여기서는 삶이 꽤 지루하니, 저녁에 선술집에 들러서 우리 신사답게 와인 한 잔 하며 이야기나 나누자고.";
			link.l1 = "명심하겠습니다, 나리. 그럼 이만!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("안녕하시오, Joseph. 요즘 어때?", "섬에 무슨 새로운 일이라도 있었어?", "최근 소문 좀 들려줄래?");
			link.l2.go = "rumours_LSC";
			link.l3 = "이 섬에 대해 몇 가지 물어보고 싶어.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "기꺼이 당신의 질문에 답해 드리겠습니다, 나리.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "여기 어떻게 오게 됐어?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "이 섬에서는 어떤 서비스를 받을 수 있지?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "해군 출신으로서, 여기서 해적들이 지배하는 것에 대해 어떻게 생각하시오?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "섬 여기저기에서 잠긴 궤짝을 많이 봤어. 사람들끼리 서로 믿지 않는 거지, 안 그래?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없습니다. 실례합니다...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "내 임무를 다하다가 그랬지. 나는 스페인 슬루프 오브 워와 싸우고 있었어. 그 배는 우리가 여러 영국 상인을 약탈한 주범이라고 믿었던 놈들이었지. 전투는 몇 시간이나 계속됐어. 거의 잡을 뻔했는데, 갑자기 폭풍이 몰아쳐서 모든 게 엉망이 됐지. 결국 우리 두 배 모두 바깥 고리 근처에서 난파됐어.\n운명도 참 장난이 심하지, 나랑 내 스페인 상대 둘 다 살아남았으니 말이야. 어쩌면 이미 그를 만났을지도 모르겠군. 이름은 로렌소 솔데라, 보기 드문 가톨릭 잡놈이지. 조심하는 게 좋을 거야.";
			link.l1 = "이야기 고맙네, 경고도 새겨두겠어...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "쉬고 싶으면 산초의 선주점에 가 보시오. 거기서 언제든 음식, 술, 잠자리를 제공받을 수 있소. 화약이나 탄환, 냉병기 같은 게 필요하다면 악셀 요스트에게 가시오. 그가 이곳 상점 주인이오. 줄리안 형제는 교회에서 약을 주고 성스러운 부적도 판다오.\n나르발족에는 아주 솜씨 좋은 대장장이가 있는데, 이름이 위르겐 슈미트라 하오. 그가 만드는 칼날은 최고라고들 하더군. 나르발족에 또 다른 재주꾼이 있다지만, 나는 그에 대해선 아무것도 들은 바가 없소.\n만약 해적이나 다른 부족과 마찰이 생기면 주세페 파치오를 찾아가시오. 그는 이곳에서 부족들 사이의 일종의 외교관 역할을 하고 있소.";
			link.l1 = "정보 고마워!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "마음에 들진 않지만, 어쩔 수 없지. 그래도 인정할 건 해야겠어. 해적들이 정의의 섬에 평화를 세운 건 정말 순식간이었으니까. 해적들이 오기 전엔, 이 섬의 두 부족이 거의 매일같이 싸웠어. 그 와중에 애꿎은 사람들이 얼마나 많이 다쳤는지 몰라.\n게다가 해적들은 음식을 공정한 값에 팔아. 시민들은 싼 값에 좋은 식량을 얻지. 하지만 해적들은 예전에 자신들을 공격했던 걸 앙갚음이라도 하듯, 부족들에게는 바가지를 씌워.\n해적들 중에 아주 똑똑한 사람이 있어. 이름은 레이턴 덱스터. 그 사람이 해적 무리의 모든 무역을 책임지고 있지. 나도 한 번 얘기해 본 적 있는데, 전술, 지도 제작, 경제까지 두루 아는 그런 재능 있고 교양 있는 사람이 어쩌다 해적 무리에 들어가게 됐는지 참 궁금하더군.\n알고 있나? 그가 이 섬 전체 지도를 며칠 만에 그려냈다는 걸. 내가 직접 봤는데, 거의 모든 게 다 담겨 있었어. 아마 부족들 사이에 전쟁이 날 걸 미리 예상하고 만든 것 같더군...";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "신중함이야, 친구, 신중함. 예전에는 이 섬에서 도둑질이 흔했다지. 적어도 모든 상자에 새 자물쇠가 달리기 전까지는 말이야.\n그런데도... 아직도 상자를 열 수 있는 누군가가 있어. 하지만 그자는 럼주나 싸구려 장신구만 훔칠 뿐, 금이나 돈은 절대 건드리지 않아.\n모든 자물쇠는 각각 다르고, 복제 열쇠는 없어. 위르겐 슈미트가 그걸 확실히 했거든. 그는 칼뿐만 아니라 자물쇠와 열쇠도 만드는 장인이야. 야외 상자에는 귀중품이 없고, 진짜 중요한 물건은 항상 배 안에 보관된다고 들었어.";
			link.l1 = "흥미롭군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("나는 너를 귀족이라고 생각했는데, 그냥 평범한 도둑이었군!", "나를 털어보겠다고? 정의의 섬 해군에서 도둑을 어떻게 다루는지 보여주지!", "내 바다 상자에서 손 떼, 도둑놈아!!");
			link.l1 = "아, 젠장!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "도둑이다! 누가 저 도둑 좀 잡아라!";
			link.l1 = "입 닥쳐!";
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
			dialog.text = LinkRandPhrase("좋은 나리, 제발 칼을 거두어 주십시오. 소란을 피우고 계십니다.", "칼을 집어넣어라, 누가 대신 집어넣게 만들기 전에.", "남자의 용맹함은 높이 사지만, 지금은 칼을 휘두를 때가 아닌 것 같은데...?");
			link.l1 = LinkRandPhrase("좋아.", "원하시는 대로...", "말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "장난 그만두시오, 나리. 칼 집어넣으시오.", "좋은 나리, 제발 칼을 거두십시오. 소란을 피우고 계십니다.");
				link.l1 = LinkRandPhrase("좋아.", "원하시는 대로...", "말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "좋은 나리, 제발 칼을 거두시오. 소란을 피우고 있소.", "사내의 용맹함은 높이 사지만, 지금은 칼을 휘두를 때가 아닌 것 같소...");
				link.l1 = RandPhraseSimple("미안해.", "나는 그것을 치우고 있어.");
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
