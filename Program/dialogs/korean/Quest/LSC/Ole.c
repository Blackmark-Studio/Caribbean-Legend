// Оле Кристиансен - Белый Мальчик
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
			dialog.text = "뭘 원하지?";
			link.l1 = "아무것도 아니야.";
			NextDiag.TempNode = "First time";
		break;
		
		// в магазине - первая встреча
		case "store":
			dialog.text = "이런... 안녕하세요, 아저씨. 흰 구슬 있으세요? 흰 구슬 주세요...";
			link.l1 = "흠. 좋은 날이군. 너... 백색 소년이냐?";
			link.l1.go = "store_1";
		break;
		
		case "store_1":
			dialog.text = "구슬! 하얀 소년을 위한 하얀 구슬이야! 아저씨, 하얀 구슬 있어?";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "흠, 나는 염주가 없지만 이 진주는 줄 수 있어. 하얗고 염주처럼 생겼거든. 그걸로 괜찮겠어?";
				link.l1.go = "store_2";
			}
			link.l2 = "아니, 나는 구슬이 없어, 흰 것도, 빨간 것도. 나는 여자도 아니고, 인디언도 아니라서 구슬 따위 차지 않아. 말해 봐...";
			link.l2.go = "pearl";
			sld = characterFromId("Axel");
			sld.quest.ole_pearl = "true";
		break;
		
		case "pearl":
			dialog.text = "구슬! 하얀 구슬! 구슬 없으면 말 안 해. 나쁜 아저씨... 구슬 줘!";
			link.l1 = "젠장! 저놈 완전 미쳤군! 스네이크 아이랑 치미세트 말이 맞았어 – 머리가 제대로 돌아가지 않는 놈이야... 도대체 무슨 구슬이 필요하다는 거지?";
			link.l1.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "pearl_repeat":
			dialog.text = "구슬 하나 줘요, 아저씨. 좋은 아저씨... 하얀 구슬!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "여기, 구슬 가져가. 그게 원하는 거야?";
				link.l1.go = "store_2";
			}
			link.l2 = "아, 젠장...";
			link.l2.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "store_2":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "그래, 그래! 맞아! 아저씨가 구슬을 줬어! 고마워요, 착한 아저씨! 이제 올레한테 구슬이 하나 더 생겼어. 곧 엄마를 볼 수 있겠지...";
			link.l1 = "기쁘구나. 자, 이제 이야기할 수 있겠나?";
			link.l1.go = "store_3";
			sld = characterFromId("Axel");
			DeleteAttribute(sld, "quest.ole_pearl");
		break;
		
		case "store_3":
			dialog.text = "그래, 좋은 사람이군. 삼촌, 당신도 좋은 사람인가? 우리 친구 하자. 올레가 이야기 나누는 걸 기뻐할 거야. 이름이 뭐야?";
			link.l1 = "내 이름은 "+pchar.name+". 올레, 예전에 어떤 남자가 너에 대해 말해줬는데, 이제 그는 여기 없어. 그가 그러더군, 네가 그를 도왔고, 나도 도와줄 수 있을 거라고.";
			link.l1.go = "store_4";
		break;
		
		case "store_4":
			dialog.text = "삼촌이 올레에게 구슬을 주셨어 - 좋은 삼촌이야. 올레는 좋은 사람을 돕는 걸 좋아해. 좋은 사람은 많지 않아 - 나쁜 삼촌들이 사방에 있지. 나는 꼭 도와줄 거야. 돕는 게 좋아.";
			link.l1 = "좋아! 이제 우리 친구다. 올레, 그런데 말인데, 붉은 피부에 화려한 깃털 모자를 쓴 남자를 기억하나? 그가 나한테 오래전에 네가 그를 구해줬다고 하더군.";
			link.l1.go = "store_5";
		break;
		
		case "store_5":
			dialog.text = "그 아저씨 기억나. 좋은 사람이야. 내가 그를 구했어. 동상까지 데려갔지. 그리고 최근에는 식량이 있는 화물칸에서 또 다른 좋은 사람을 구했어. 나쁜 제독의 아저씨들한테서 그를 구했지. 그들이 그를 죽였을 거야. 나도 그를 동상까지 데려가고 싶었는데, 완전히 거절했어.";
			link.l1 = "화물창에서 온 자 말인가? 허, 누군지 알 것 같군... 그리고 그 아저씨도 알아. 말해 봐, 올레, 네가 구한 그 남자는 누구지?";
			link.l1.go = "store_6";
		break;
		
		case "store_6":
			dialog.text = "그의 이름은 네이선 아저씨야. 아주, 아주 많이 아프셔. 올레가 그를 발견했을 때 거의 걷지도 못하셨지.";
			link.l1 = "그래... 그가 그런 일을 할 수 있었다는 게 참 이상하지.";
			link.l1.go = "store_7";
		break;
		
		case "store_7":
			dialog.text = "아니, 이상하지 않아. 내가 그를 찾아서 불 럼을 좀 줬어. 그 배에 먹을 게 있어서 구멍 안으로 헤엄쳐 들어갔지. 나쁜 놈들이 문을 잠그지만, 나는 항상 열 수 있어. 히히히... 멍청한 나쁜 놈들. 걔네가 게를 유인하는 거, 나도 알아. 거기서 나쁜 놈들을 따돌리고 나서 네이선도 찾았어. 그는 몸이 안 좋아 보였지. 내가 불 럼을 가지고 있어서 마시라고 줬더니 좀 나아졌어. 그 다음엔 팅크처도 줬지, 나는 항상 그런 걸 하나씩 들고 다녀. 무서운 게가 올레를 물면 대비하려고 말이야. 좋은 삼촌 치미셋이 그렇게 하라고 했거든...";
			link.l1 = "해독제랑 럼을 그에게 줬어? 헤, 다들 생각하는 것만큼 너 바보는 아니구나. 잘했어, 올레.";
			link.l1.go = "store_8";
		break;
		
		case "store_8":
			dialog.text = "나쁜 삼촌들은 올레를 바보라고 생각해서 놀려대지. 바보 올레... 올레는 바보가 아니야, 그냥 하얀 구슬을 다 모아야 해. 안 그러면 엄마가 그를 쫓아낼 거거든. 나중에 구슬 하나 더 줄 수 있어?";
			link.l1 = "흠... 그래, 올레, 우린 친구지. 말해 봐, 넌 어떻게 호크... 아니, 네이선 아저씨를 동상 쪽으로 보낼 생각이었어? 치미셋 아저씨가 그 동상은 배랑 같이 가라앉았다고 하던데...";
			link.l1.go = "store_9";
		break;
		
		case "store_9":
			dialog.text = "조각상은 바닥에 있어. 올레가 알아. 하지만 깊지 않고, 좋은 헨릭 아저씨가 네이선 아저씨를 거기로 보낼 수 있어. 헨릭 아저씨는 물속을 걷는 법을 알아. 하지만 무서운 게들이 많아. 올레는 그게 무서워. 게들이 아프게 물어.";
			link.l1 = "헨릭 아저씨? 그게 누구야?";
			link.l1.go = "store_10";
		break;
		
		case "store_10":
			dialog.text = "헨리크 아저씨는 사악한 나르발 아저씨들 사이에서 살고 있어요. 모두가 그분을 알아요. 그분은 물속을 걸을 수 있고, 나르발 아저씨들에게 거기서 잠수하는 법을 가르쳐줘요. 헨리크 아저씨는 친절해서 올레에게 하얀 구슬을 주셨죠.";
			link.l1 = "그런데 너를 나르발들이 들여보내 주더냐? 아니면 그놈들 땅이 너한테는 그냥 열려 있나?";
			link.l1.go = "store_11";
		break;
		
		case "store_11":
			dialog.text = "히히... 나쁜 아저씨들은 올레가 들어오지 못하게 하지만, 올레는 밤이면 그들의 배 안 어떤 방이든 들어갈 수 있어. 그 아저씨들은 크고 시끄럽지만, 올레는 조용하고 조심스럽지. 그리고 올레는 헨리크 아저씨가 다이빙할 때 쓰는 배 주변을 헤엄치다가 헨리크 아저씨를 만났어. 헨리크 아저씨가 올레에게 하얀 구슬을 줬고, 이제 우리는 친구야.";
			link.l1 = "흥미롭네... 나도 Henrik 아저씨랑 친구가 되고 싶어.";
			link.l1.go = "store_12";
		break;
		
		case "store_12":
			dialog.text = "동상까지 잠수하고 싶어? 거기, 오래된 배의 난파선 안에 있어. 거기엔 크고 무서운 게들이 많아. 그놈들 안 무서워? 물 수도 있다구.";
			link.l1 = "아니, 나는 그놈들이 두렵지 않아. 이미 한 놈을 죽였으니, 이제는 그놈들이 나를 두려워해야지.";
			link.l1.go = "store_13";
		break;
		
		case "store_13":
			dialog.text = "오, "+pchar.name+" 아주 용감하구나! 그럼 헨릭 아저씨한테 가 봐, 그분이 바닥을 걷는 법을 가르쳐 줄 거야. 그러면 거기 있는 게들은 전부 네가 잡을 수 있을 거야. 그리고 올레를 위해 큰 구슬도 하나 더 찾을 수 있을 거고. 맞지?";
			link.l1 = "알겠어, 그렇게 할게. 하지만 먼저 헨릭 아저씨부터 찾아야 해.";
			link.l1.go = "store_14";
		break;
		
		case "store_14":
			dialog.text = "왜 그를 찾으려는 거지? 그는 '산 가브리엘'이라는 배, 작업장에 살고 있어. 하지만 사악한 나르발 아저씨들이 널 반기지 않을 수도 있어.";
			link.l1 = "나쁜 아저씨들은 내가 직접 처리할 거야. 그리고 마지막으로 한 가지 더 묻지. 지금 네이선 아저씨는 어디에 있지? 내가 그를 찾고 있었고, 그가 바로 내가 여기 온 이유야.";
			link.l1.go = "store_15";
		break;
		
		case "store_15":
			dialog.text = "나는 '페르난다'에 있는 내 은신처에 나단 아저씨를 숨겼어. 거긴 멀리 떨어져 있고 아무도 살지 않아. 모두 곧 침몰할 거라고 생각하지만, 올레는 다르게 알고 있지. 내가 나단 아저씨를 구해서 그곳에 데려갔어\n아저씨는 아직도 많이 아프고 계속 불럼만 마셔. 거의 걷지도 못하고 다섯 파운드보다 무거운 것도 못 들어. 나단 아저씨가 안쓰러워서, 나는 상자에서 불럼을 가져다주고, 제독의 나쁜 놈들 창고에서 음식을 훔쳐다 줘. 내가 잡은 쥐도 요리해 드려. 아주 맛있는 쥐야!";
			link.l1 = "맛있는 쥐라니? 그렇군. 그럼 네이선이 탄 배가... 뭐라고 했지, '페르난다'였나? 나는 그 배는 모르겠어...";
			link.l1.go = "store_16";
		break;
		
		case "store_16":
			dialog.text = "Uncle "+pchar.name+", 방금 여기서 멀지 않다고 말했잖아. 그녀에게 가려면 헤엄쳐야 해. 뒤쪽에 문이 있는데, 네이선 아저씨는 그 문을 열지 않아. 올레가 열지 말라고 했거든. 하지만 네가 네이선 아저씨의 친구라면, 그 문을 여는 방법을 알려줄게. 이렇게 문을 두드려: 똑똑... 똑똑. 그러면 그가 열어줄 거야.";
			link.l1 = "그걸 기억할게. 고마워, Ole! 정말 큰 도움이 됐어! 어떻게 고마움을 제대로 표현해야 할지 모르겠어.";
			link.l1.go = "store_17";
		break;
		
		case "store_17":
			dialog.text = "하얀 구슬 하나만 더 가져와. 물론 찾으면 말이지.";
			link.l1 = "아, 그래! 흰 구슬이군! 좋아. 잘 가라, Ole!";
			link.l1.go = "store_18";
		break;
		
		case "store_18":
			DialogExit();
			LAi_SetLoginTime(npchar, 12.0, 21.99);
			LAi_SetCitizenType(npchar);
			LAi_group_MoveCharacter(npchar, "LSC_CITIZEN");
			sld = characterFromId("Nathaniel");
			sld.dialog.currentnode = "diffindoor";
			sld.greeting = "Nathaniel_ill"; // ноду и вякалку Натану
			pchar.questTemp.LSC.DiffIndoor = "true"; //атрибут прохода к Натану
			pchar.questTemp.LSC = "mechanic"; // флаг на разговор с Механиком
			NextDiag.CurrentNode = "ole";
			AddQuestRecord("LSC", "6");
		break;
		
		case "ole":
			dialog.text = "아, 삼촌 "+pchar.name+"! 반갑네! 잘 지내고 있나?";
			link.l1 = "고마워, 올레, 난 괜찮아. 너를 다시 보게 되어 나도 기뻐.";
			link.l1.go = "exit";
			link.l2 = "들어봐, 올레. 네가 말하길, 제독의 해적들이 화물창 문을 닫아두면 네가 항상 그걸 연다고 했잖아... 거기 있는 모든 궤짝은 잠겨 있는데, 넌 또 그 궤짝에서 나탄 아저씨 줄 럼주를 챙긴다고 했지. 그걸 어떻게 하는 거야?";
			link.l2.go = "lock";
			NextDiag.TempNode = "ole";
		break;
		
		case "lock":
			dialog.text = "올레는 멋진 열쇠 꾸러미를 가지고 있어. 그 열쇠들은 어떤 문이나 상자든 열 수 있지. 뭐, 전부는 아니야. 어떤 건 열 수 없지만, 대부분은 열 수 있어. 올레는 그 열쇠들을 사악한 삼촌 위르겐의 선실에서 찾았어. 위르겐은 매일 자신의 화덕 옆에서 망치질을 하지. 자물쇠랑 열쇠를 만들고, 또 사악한 나르발들을 위해 크고 무서운 머스킷도 만들어.";
			link.l1 = "알겠어. 올레, 그 열쇠들 나한테 팔 수 있어? 돈은 줄 수 있어...";
			link.l1.go = "lock_1";
		break;
		
		case "lock_1":
			dialog.text = "좋아요, 아저씨 "+pchar.name+", 내가 열쇠를 팔게. 내 것 하나만 남겨둘 거야. 그건 제독 방 열쇠야. 나단 아저씨를 위한 음식과 럼주가 잔뜩 있지. 어차피 상자엔 더 이상 구슬이나 럼주도 남아 있지 않아.";
			link.l1 = "그 사람들한테 얼마를 원하는 거지?";
			link.l1.go = "lock_2";
		break;
		
		case "lock_2":
			dialog.text = "먼저 말씀해 주세요, 아저씨 "+pchar.name+", 큰 배가 있나?";
			link.l1 = "그래, 봤어. 하지만 그녀는 여기 없고, 바깥쪽 구역에 있어. 하지만 나 곧 정의의 섬을 떠날 거야. 그리고 큰 배를 타고 나서 다시 여기로 돌아올 거야, 나단 아저씨를 위해서.";
			link.l1.go = "lock_3";
		break;
		
		case "lock_3":
			dialog.text = "나탄 아저씨 때문에? 오, 정말 멋지다! 있잖아, 약속해 줘. 네가 타고 온 큰 배로 나를 여기서 데려가 주고, 내가 필요할 때까지 같이 항해하게 해줘. 나 쓸모 있을 수 있어. 쥐도 잡고 요리도 할 수 있어... 그리고, 흰 구슬 다섯 개 줘. 그러면 내가 열쇠 줄게.";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "물론이지! 여기 구슬이야. 가져가.";
				link.l1.go = "lock_4";
			}
			link.l2 = "쥐를 잡아서 요리한다고? 허! 흥미로운 솜씨구만. 좋아, 올레, 약속하지. 내가 구슬 다섯 개와 내 말을 가져올게.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_1";
		break;
		
		case "ole_1":
			dialog.text = "아, 아저씨 "+pchar.name+"! 반갑구나! 잘 지냈어?";
			link.l1 = "고마워, 올레, 나 괜찮아. 너도 만나서 반가워.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "네 열쇠에 쓸 하얀 구슬 다섯 개를 가져왔어.";
				link.l2.go = "lock_4";
			}
			NextDiag.TempNode = "ole_1";
		break;
		
		case "lock_4":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			dialog.text = "구슬이다! 하얀 구슬! 아저씨 "+pchar.name+"  올레에게 구슬을 주었어! 곧 엄마를 볼 수 있겠지!... 삼촌 "+pchar.name+", 돌아올 때 나를 여기서 데려가겠다고 약속할 수 있어?";
			link.l1 = "그래, 올레. 난 아직 쥐는 안 먹어봤어. 너도 같이 데려갈게.";
			link.l1.go = "lock_5";
		break;
		
		case "lock_5":
			GiveItem2Character(pchar, "keys_skel");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			dialog.text = "감사합니다, 감사합니다, 사랑하는 아저씨 "+pchar.name+"! 자, 열쇠들 가져가. 사용하기 쉽다네, 하나씩 꽂아서 시도해 보면 돼. 결국 필요한 자물쇠를 열 수 있는 게 있을 거야. 만약 안 된다면, 그 자물쇠는 너무 까다로운 거라서 특별한 열쇠가 꼭 필요할 거야.";
			link.l1 = "알겠소. 내가 처리하겠소.";
			link.l1.go = "lock_6";
		break;
		
		case "lock_6":
			dialog.text = "잠깐만요, 아저씨 "+pchar.name+"! 나 또 다른 열쇠를 얻었어. 꽤 예쁘고 똑똑하게 생겼지. 나쁜 유르겐 삼촌은 이런 열쇠는 못 만들어. 어디에 쓰는 건지 모르겠지만, 아마 네가 알아낼 수 있을 거야. 봐, 정말 예쁜 열쇠야. 이런 건 분명 처음 보지?";
			link.l1 = "보여 줘... 그래, 열쇠가 아주 흥미롭군. 하지만 그게 뭘 여는지 모르면 무슨 소용이 있겠어?";
			link.l1.go = "lock_7";
		break;
		
		case "lock_7":
			dialog.text = "Uncle "+pchar.name+", , 너 참 이상한 사람이구나. 무슨 소용이 있겠어? 열쇠가 있다면 어딘가에 자물쇠도 있겠지. 자물쇠가 있다면 어딘가에 동전도 있을 거고. 나는 정의의 섬에서 열쇠를 찾았어. 그 말은 자물쇠도 여기 있다는 뜻이지. 의심할 여지가 없어. 영리한 열쇠고, 그런 열쇠로 잠그는 건 아주 귀중한 물건뿐이야. 올레가 알고 있어.";
			link.l1 = "솔직히 말해서, 너 웃기다, 올레. 좋아, 내가 살게. 그 대신 구슬 줄까?";
			link.l1.go = "lock_8";
		break;
		
		case "lock_8":
			dialog.text = "그래, 올레는 구슬 다섯 개를 원해. 줄 거야, 아저씨 "+pchar.name+"?";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "여기, 네 염주 가져가.";
				link.l1.go = "key";
			}
			link.l2 = "지금은 없지만, 꼭 구슬을 가져다줄게.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_2";
		break;
		
		case "key":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "sant_anna_key");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "구슬이요! 하얀 소년을 위한 하얀 구슬이요! 그의 엄마를 위해서! 여기요, 아저씨\n "+pchar.name+", 열쇠를 가져가. 그리고 자물쇠도 찾게 될 거야, 올레가 알고 있지. 너는 용감하구나, 사나운 게도 두렵지 않으니.";
			link.l1 = "아, 웃기지 마, 올레! 열쇠 고맙다. 또 보자!";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "ole_2":
			dialog.text = "아, 삼촌 "+pchar.name+"! 만나서 반갑소! 잘 지내시오?";
			link.l1 = "고마워, 올레. 나도 잘 지내. 너를 다시 보게 되어 기뻐.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "열쇠 대신 흰 구슬 다섯 개를 가져왔어.";
				link.l2.go = "key";
			}
			NextDiag.TempNode = "ole_2";
		break;
		
		case "ole_3":
			dialog.text = "아, 아저씨 "+pchar.name+"! 반갑다! 잘 지냈어?";
			link.l1 = "고마워, 올레, 난 괜찮아. 나도 너를 보게 되어 기뻐.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "return":
			dialog.text = "아, 삼촌 "+pchar.name+", 돌아왔구나! 큰 배로 돌아왔네! 나도 여기서 데려가 줄 거야? 아저씨 "+pchar.name+", 나한테 약속했잖아, 기억하지?";
			link.l1 = "그래, 알아, 올레. 배에 온 걸 환영해! 쥐들이 곤란하게 생겼겠군, 하하!";
			link.l1.go = "return_1";
			link.l2 = "정말이야? 내가 너한테 언제 약속했지? 그런 약속 한 기억 없는데...";
			link.l2.go = "return_3";
		break;
		
		case "return_1":
			dialog.text = "고마워요, 아저씨! 올라가 분명 도움이 될 거예요, 곧 알게 되실 거예요! 아, 어쩌면 엄마도 볼 수 있을까요? 이제 가볼게요!";
			link.l1 = "이렇게 서두르지 마, 올레. 짐 챙겨도 돼. 당장 출항할 생각은 없으니까.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LSC_SetOlePassenger", 10.0);
		break;
		
		case "return_3":
			dialog.text = "나한테 약속했잖아, 정말로! 올레를 여기서 데려가겠다고 약속했잖아! 나쁜 삼촌! 올레를 속였어! 나쁜 삼촌!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload45", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			if (GetCharacterIndex("Mary") != -1) // Мэри
			{
				sld = characterFromId("Mary");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else // иначе завершение
			{
				chrDisableReloadToLocation = false;
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			}
		break;
		
		// Блудный сын
		case "givemepearl":
			dialog.text = "아저씨, 아저씨... 하얀 구슬 하나만 더 필요해요. 제발, 올레에게 하얀 구슬 하나만 주세요!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "네가 그럴 줄 알았지. 자, 구슬 가져가. 이제 만족했냐?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "아, 정말 골치 아프네... 더 이상 구슬 없어, 올레, 진짜 없어!";
			link.l2.go = "givemepearl_no";
			DeleteAttribute(npchar, "pearl_date");
		break;
		
		case "givemepearl_yes":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			dialog.text = "고마워! 그래, 그래, 좋은 아저씨 "+pchar.name+"! 올레가 구슬을 하나 더 가졌고, 남은 구슬도 얼마 없어! 그리고 나는 엄마한테 갈 거야...";
			link.l1 = "오, 그런데 왜 그렇게 이상하지...";
			link.l1.go = "givemepearl_yes_1";
		break;
		
		case "givemepearl_yes_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			SaveCurrentNpcQuestDateParam(npchar, "pearl_date");
			npchar.quest.pearlqty = sti(npchar.quest.pearlqty)+1;
			NextDiag.CurrentNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_repeat":
			dialog.text = "구슬 주셔서 감사합니다, 좋은 아저씨 "+pchar.name+"!";
			link.l1 = "천만에...";
			link.l1.go = "exit";
			NextDiag.TempNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_no":
			dialog.text = "구슬이 없다고? 그럴 리가 있나, 아저씨 "+pchar.name+"?! 구슬이 몇 개만 더 있으면 돼... 반드시 다 모아야 해. 그렇다면, 상륙해야겠군. 구슬을 찾아볼게...";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "그리고 어디로 갈 건데? 혼자서 뭘 할 거야? 아니, 네 운명까지 내가 책임지고 싶지 않아. 잠깐만, 주머니 좀 확인해 볼게... 여기! 구슬 가져가고 나랑 같이 있어. 이제 됐지?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "그건 네 권리야, 올레. 나랑 같이 항해하는 게 지겹다면, 나는 널 막지 않겠어. 우리 약속했잖아. 그래도 네가 그 쥐새끼들 잘 잡아왔지...";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "givemepearl_no_1":
			dialog.text = "안녕히 계세요, 아저씨 "+pchar.name+". 올레가 흰 구슬이 필요해, 그렇지 않으면 절대 어머니에게 돌아갈 수 없어...";
			link.l1 = "아이고, 참 안됐구나. 하지만 내가 뭘 할 수 있겠니? 가거라, 올레. 행운을 빈다.";
			link.l1.go = "givemepearl_exit";
		break;
		
		case "givemepearl_exit": // Оле уходит - квест не довели до конца
			DialogExit();
			RemovePassenger(Pchar, npchar);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(pchar, "GenQuest.Ole");
		break;
		
		case "mother":
			dialog.text = "Uncle "+pchar.name+"! 흰 구슬이 하나만 더 필요해. 마지막 거야. 제발, 올레에게 그걸 줘!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "네가 그럴 줄 알았지. 자, 구슬 가져가. 이제 만족했냐?";
				link.l1.go = "mother_1";
			}
			link.l2 = "아, 정말 골치 아프네... 올레, 더 이상 구슬이 없어, 진짜 없어!";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "mother_1":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "감사합니다, 감사합니다, 사랑하는 아저씨 "+pchar.name+"! 이제 올레가 구슬을 전부 가졌어. 그래, 하나도 빠짐없이 다! 이제 올레가 엄마한테 가져다드릴 수 있으니, 엄마가 올레를 쫓아내지 않으실 거야...";
			link.l1 = "이봐, 네가 맨날 말하는 그 엄마라는 사람은 도대체 누구야? 그리고 마지막으로, 왜 그 진주... 하얀 구슬이 필요하다고 하는 거지? 그리고 그걸 다 가졌다는 건 무슨 뜻이야?";
			link.l1.go = "mother_2";
		break;
		
		case "mother_2":
			dialog.text = "좋은 아저씨 "+pchar.name+" 올레가 엄마를 위해 구슬을 모으는 걸 도왔지... 올레는 어렸을 때 엄마의 흰 구슬 목걸이를 끊어버렸어. 구슬이 전부 물에 빠졌지. 엄마는 올레에게 무척 화가 났고, 올레는 잃어버린 구슬을 전부 모으기 전에는 집에 돌아갈 수 없었어\n몇 개였는지 기억나. 다섯 번 열 개, 그러니까 쉰 개였지. 이제 올레는 전부 모았어. 삼촌 "+pchar.name+", 제발, 집에 데려가 줘! 엄마를 기쁘게 해드리고 싶어, 구슬도 돌려드려야 해. 집에 데려가 줘!";
			link.l1 = "세상에, 정말 믿기 힘든 이야기네... 어릴 때 정의의 섬까지 오게 됐다니. 엄마 진주 목걸이를 끊어서 집에서 쫓겨난 거야? 소름 돋는데...";
			link.l1.go = "mother_3";
		break;
		
		case "mother_3":
			dialog.text = "좋은 아저씨, 저를 어머니께 데려다 주세요 "+pchar.name+". 나는 그녀를 보고 싶어. 구슬을 보면 그녀도 기뻐할 거야.";
			link.l1 = "나도 그러고 싶지만, 네 집이 어디 있는지 아니? 네 어머니는 어디에 사시지?";
			link.l1.go = "mother_4";
		break;
		
		case "mother_4":
			dialog.text = "그녀는 정의의 섬에 살아, 빨간 지붕이 있는 집에서.";
			link.l1 = "정말이냐! 여기 섬이 몇 개인지, 빨간 지붕이 있는 집이 몇 채나 되는지나 알고 하는 말이냐? 그 섬 이름이 뭐지? 자세히 말해 봐...";
			link.l1.go = "mother_5";
		break;
		
		case "mother_5":
			dialog.text = "이름은 몰라. 섬이었던 건 알아, 엄마가 아빠한테 우리가 섬에 있다고 말했으니까! 그리고 우리는 빨간 지붕이 있는 집에서 살았어. 예쁜 집이었고, 아주 컸어. 엄마한테 데려다줘, 아저씨\n "+pchar.name+". 제발...";
			link.l1 = "그래, 알겠다. 우리는 모든 섬에서 그런 집을 찾아보고 네 어머니를 물어볼게. 어머니 성함이 어떻게 되시지?";
			link.l1.go = "mother_6";
		break;
		
		case "mother_6":
			dialog.text = "그녀 이름? 참 이상하네, 아저씨\n "+pchar.name+". 우리 어머니 이름은 어머니야. 너희 어머니 이름은 달라?";
			link.l1 = "오, 신이시여, 제발 저에게 인내심을 주소서... 좋아, 올레. 네 집을 찾아보도록 하마. 이제 배로 가거라.";
			link.l1.go = "mother_7";
		break;
		
		case "mother_7":
			dialog.text = "고마워요, 아저씨 "+pchar.name+". 당신은 정말, 정말 친절하고 좋은 분이에요! 곧 올라가 엄마를 보게 될 거예요!";
			link.l1 = "오...";
			link.l1.go = "mother_8";
		break;
		
		case "mother_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(npchar, "pearl_date");
			// ставим Агнес Кристиансен и открываем ее дом в Мариго
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", false);
			sld = GetCharacter(NPC_GenerateCharacter("Agnes", "women_18", "woman", "towngirl", 10, HOLLAND, -1, true, "quest"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Agnes";
			sld.lastname = "Christiansen";
			sld.dialog.FileName = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "agnes";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Marigo_houseSp2", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		break;
		
		case "home":
			dialog.text = "어머니... 어머니, 엄마! 나 돌아왔어요!";
			link.l1 = "아들아...";
			link.l1.go = "home_1";
		break;
		
		case "home_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestFunctionDelay("LSC_OleReturnHome", 18.0);
		break;
		
		case "home_2":
			dialog.text = "엄마, 하얀 구슬을 가져왔어요! 전부 모았어요! 엄마는 다시 목걸이를 갖게 될 거예요. 아직도 저한테 화나셨어요?";
			link.l1 = "신이시여... (울음) 올레! 아들아, 왜? 왜 떠난 거냐? 그 진주 따위는 필요 없어!";
			link.l1.go = "home_3";
		break;
		
		case "home_3":
			sld = characterFromId("Blaze");
			dialog.text = "엄마, 여기... 받아요. 오랫동안 모았어요. 착한 아저씨들이 도와줬어요, 특히 아저씨\n "+sld.name+". 그는 나를 자기 큰 배에 태우고, 구슬을 모으는 걸 도와줬으며, 집까지 데려다줬어...";
			link.l1 = "오... 정말 많이 컸구나, 그래도 아직 어린아이야... 안아보자, 아들아! 미안하다, 그 빌어먹을 목걸이 때문에 용서해다오! 다시는 널 혼자 두지 않을게, 절대! 우리 함께 살면서 내가 돌봐줄 거야... 반드시 속죄할게, 약속한다!...";
			link.l1.go = "home_4";
		break;
		
		case "home_4":
			dialog.text = "엄마, 보고 싶었어... 엄마랑 같이 있고 싶어. 아직도 나한테 화났어? 왜 울고 있어?";
			link.l1 = "(울면서) 아니야, 아니야... 정말 미안하다, 용서해다오, 아들아!...";
			link.l1.go = "home_5";
		break;
		
		case "home_5": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Agnes");
			sld.dialog.currentnode = "agnes_11";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "final":
			dialog.text = "Uncle "+pchar.name+"! 와줘서 정말 기뻐요! 저를 어머니께 데려다 주셔서 감사합니다. 이렇게 어머니와 함께 있을 수 있다니 정말 좋아요... 집에 돌아오니 참 좋지 않으세요, 아저씨? "+pchar.name+"?";
			link.l1 = "그래. 올레. 맞아. 네가 기뻐하니 나도 기쁘다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "final";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("이봐, 무기는 집어넣는 게 좋겠어. 그거 보면 신경이 곤두서거든.","여기서는 칼 들고 돌아다니는 거 용납 안 해. 집어넣어.","이봐, 중세 기사처럼 칼 들고 설치지 마. 집어넣어, 너한테 안 어울리니까...");
			link.l1 = LinkRandPhrase("좋아.","좋아.","말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"이봐, 나는 이 도시의 시민이야. 그러니 칼 좀 내려줘.","이봐, 나는 이 도시의 시민이야. 그러니 칼 좀 내려줘.");
				link.l1 = LinkRandPhrase("좋아.","좋아.","말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"조심해, 친구. 무기 들고 돌아다니면 내가 긴장할 수도 있으니까...","사람들이 무기를 뽑은 채 내 앞을 지나가는 건 싫어. 무섭거든...");
				link.l1 = RandPhraseSimple("알겠어.","내가 가져간다.");
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
