//Jason общий диалог дворянок
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//первая встреча
            if(NPChar.quest.meeting == "0")
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
				{
					dialog.text = "흠. 그대는 ~의 깃발 아래 항해하고 있군 "+NationNameGenitive(sti(pchar.nation))+", 선장. 나는 우리 나라의 적과 말하고 싶지 않소. 흠!";
					link.l1 = "아, 그렇지. 진정한 애국자군...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = RandPhraseSimple("나에게서 뭘 원하는 거지, "+GetAddress_Form(NPChar)+"? 평민 선원이 귀족 아가씨와 말하는 건 예의가 아니지만, 말씀을 듣고 있소.","오, 그런데 이렇게 용감한 선장님께서 저에게 무엇을 원하시는지요?");
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". 시간을 많이 뺏지 않겠소, 그냥 한 가지만 묻고 싶어서...";
					link.l1.go = "question";
					link.l2 = RandPhraseSimple("당신네 식민지에서 무슨 일이 벌어지고 있는지 알아야겠소.","정보가 좀 필요해.");
					link.l2.go = "quests";//(перессылка в файл города)
				}
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("도시 전체가 긴장하고 있어 - 돈 페르난도 데 알라미다, 왕실 감찰관이 도착했거든. 여기서 별별 일을 다 봤지만, 이번 일은... 사람을 바꾸는 건 슬픔 자체가 아니라, 그걸 어떻게 극복하느냐지. 그의 아버지가 돌아가신 뒤로 완전히 달라졌다고들 해. 이제 군도 전체를 뒤져도 그보다 더 청렴하고... 무자비한 국왕의 하수인은 없을 거야.","'홀리 머시'를 좀 봐! 왕이 직접 특별한 설계로 만들라고 명령했다더군. 그리고 봐, 흠집 하나 없어. 마치 성모 마리아께서 직접 지켜주시는 것 같아. 하지만 소문도 들었지... 어쩌면 성모가 아닐 수도 있다더군.","도니 페르난도를 죽이려고 몇 번이나 시도한 줄 아시오? 지난 1년 동안만 해도 공해상에서 열두 번이나 습격을 받았소!\n하지만 저렇게 충성스럽고 잘 훈련된 선원들, 그리고 주님의 가호가 있다면... 열세 번째도 무사히 넘길 것이오!"),LinkRandPhrase("들었어? 돈 페르난도 데 알라미다가 우리 도시에 도착했대. 지금 어딘가 거리에서 돌아다닌다던데. 나도 직접 한 번 보고 싶다...","복잡한 사람이오, 이 돈 페르난도는. 어떤 이들은 그가 조국을 더러운 것들로부터 정화하는 구세주라 말하지. 또 다른 이들은 그의 아버지가 죽은 뒤 무언가 그 안에서 부서졌고, 곧 우리 모두가 눈물을 흘리게 될 거라 속삭이오. 하지만 내가 한마디 하겠소: 그를 두려워하지 마시오. 그를 그렇게 만든 자들을 두려워하시오.","이렇게 잘생긴 남자라니, 이 돈 페르난도! 그런데 이상한 게 뭔지 알아? 마치 아무도 눈에 들어오지 않는 것 같아. 오직 의무와 봉사뿐이지. 어떤 아가씨가 있었다고 들었는데... 그런데 어떤 신부를 만난 뒤로는 세속의 즐거움을 완전히 끊었다더라. 마치 서약이라도 한 것처럼."),RandPhraseSimple(RandPhraseSimple("젠장할 감찰관 놈! 저 자가 있는 동안엔 도시가 죽은 거나 마찬가지야. 장사도, 재미도 없어. 숨 쉬는 것조차 조용히 해야 할 판이지. 그리고 제일 무서운 게 뭔지 알아? 모든 항구가 똑같다는 거야. 마치 시계처럼 정확하게. 국왕 폐하께서 우리 모두를 고문하려고 일부러 이런 짓을 꾸민 게 아닐까 싶을 정도라니까!\n","돈 페르난도께서 다시 고아원을 방문하셨소. 후하게 기부하시고, 몇 시간씩 기도도 하시지. 저런 훌륭한 분을 본보기로 삼아야 하오, 저 빌어먹을 횡령꾼들한테!"),RandPhraseSimple("하! '성자' 페르난도 놈이 또다시 모든 사창가를 닫아버렸군. 뭐, 상관없지. 곧 저놈이 떠나면 다시 문 열 테니까.","그 검... 검사관이 도착했지, 그거야! 돈 페르난도 데 알메이다, 아니면 뭐더라, 알라미다! 얼마나 대단한지 총독조차도 그 앞에선 살금살금 걷는다더군. 사람들 말로는 그가 네 눈을 들여다보면 네 모든 죄를 한눈에 꿰뚫어본다지. 무섭다니까!")));
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "내가 다시 말해야겠나? 나는 ~의 친구로 의심받고 싶지 않소 "+NationNameAblative(sti(pchar.nation))+"나가! 안 그러면 경비병을 부를 거야! 그들은 너와 한마디 하고 싶어할 테니.";
					link.l1 = "좋아, 좋아, 진정해. 나 간다.";
					link.l1.go = "exit";
				}
				else
				{
				dialog.text = NPCStringReactionRepeat("뭐라고? 또 너냐? 가서 딴 사람이랑 얘기해라. 여기 돌아다니는 평민들이 많으니, 네 취향엔 그쪽이 더 맞겠지. 나는 이제 가봐야 하네, 오늘 밤 총독 저택에서 연회가 있는데 내 폼파두르가 아직 준비가 안 됐거든!\n","아니, 이제 정말 짜증나게 구는군! 아직도 모르겠어? 아니면 머리가 둔한 거야?","나리, 이제 보니 그대는 그냥 바보가 아니라, 악당이자 무례한 자 같군요. 그만 멍청한 질문으로 나를 귀찮게 하지 않으면 남편을 부를 거라고 경고합니다!","한 마디만 더 하면 사령관에게 네 놈을 처리하라고 할 거야!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("알겠소. 안녕히 가시오.","그래, 그래, 기억나. 그냥 물어보는 걸 깜빡했을 뿐이야...","오해하셨군요...","진정하시오, 세뇨라, 나는 이미 나가고 있소...",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				}
			}
			NextDiag.TempNode = "First time";
		break;

		//сюда вставляем любые проверки и направления на квесты
		case "question":
			dialog.text = LinkRandPhrase("좋아, 들어보자.","아, 좋아. 뭐 원하는 거야?","질문 있나? 좋아, 뱃사람, 듣고 있지.");
			link.l1 = LinkRandPhrase("이 마을의 최신 소문 좀 들려줄 수 있나?","최근에 여기서 흥미로운 일이 있었나?","카리브에서 소식이 있습니까, 부인?");
			link.l1.go = "rumours_noblegirl";
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"미쳤어?! 나를 겁주잖아! 무기를 집어넣지 않으면 내가 사령관에게 말해서 요새에서 목을 매달게 할 거야!","미쳤소?! 나를 겁주고 있잖소! 무기를 집어넣으시오, 아니면 내가 사령관에게 말해서 요새에서 교수형에 처하게 할 것이오!");
			link.l1 = LinkRandPhrase("좋아.","원하시는 대로 하겠습니다.","좋아.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
