// Дональд Гринспи - лидер нарвалов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "뭐야? 뭘 원하는 거야?";
				link.l1 = TimeGreeting()+". 내 이름은 "+GetFullName(pchar)+". 나는 그 클랜의 우두머리를 만나고 싶었어.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, "+GetFullName(pchar)+"! 뭐 필요해?";
				link.l5 = "그냥 인사나 하려고 왔어. 또 보자!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "이제 나를 알겠지. 내 이름은 도널드 그린스펜이야, 그리고 나나 내 부하들을 화나게 하지 마라. 암호 없이는 '산 가브리엘'에 들어가려고도 하지 마. 상점은 모두에게 열려 있어. 누구나 거래가 필요하니까. 질문 있나?";
			link.l2 = "아니, 알겠어. 또 보자.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
	// ----------------------------------после разгрома Чада и Мэри на Каролине---------------------------
		case "shark":
			dialog.text = "나에게 무슨 볼일이 있지?";
			link.l1 = "아주 불쾌한 소식이야, 도널드. 어젯밤 스티븐의 목숨을 노린 시도가 있었어. 네 클랜의 싸움꾼들이 연루됐지.";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "그건 잘 모르겠군. 왜 그들이 내 부하들이라고 생각하지?";
			link.l1 = "내가 거기 있었으니까. 우리는 네 놈들, 해적들, 그리고 리바도스의 차이를 알아볼 수 있지. 그 무리는 메리 캐스퍼와 차드 카퍼가 이끌고 있었어. 더 증거가 필요해?";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "내 부하들과 나는 그 일과 아무런 관련이 없다는 것만은 확실히 말씀드릴 수 있소.";
			link.l1 = "그 점에 대해서는 제독에게 직접 확신을 줘야 할 거요, 그리고 그게 쉽지 않을 거요. 도드슨은 공격 이후로 모든 나르발들에게 몹시 화가 나 있소. 그는 자네들에게 전쟁을 선포할 생각이오 – 식량 공급을 끊고, 기회만 있으면 자네 부하들을 쏴 죽일 거요. 그리고 그건 말뿐이 아니오.";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "제독이 자기가 뭘 하는지 알길 바란다. 내 부하들도 사격 실력이 뒤지지 않는다는 걸 의심하는 건가?";
			link.l1 = "내 생각엔 그가 맞아. 그는 '산 아우구스틴'을 요새로 만들고 너희 모두가 굶어 죽을 때까지 싸울 준비가 되어 있어. 게다가, 도드슨이 리바도스와 협상해서 협력을 제안할 거야. 너희가 제독과 리바도스가 힘을 합치면 절대 이길 수 없어.";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "젠장! 하지만 우리는 이번 시도에 관여하지 않았어! 왜 우리 전체 클랜이 그 멍청한 년 메리랑 내 선원들 중 쓰레기 몇 놈이 저지른 일 때문에 대가를 치러야 하지?\n게다가 논리적으로 생각해 봐, 말로우를 죽인 건 도드슨 자신이야. 그게 바로 그런 비열한 짓을 하면 벌어지는 일이거든.";
			link.l1 = "너는 아무것도 모르는구나. 완전히 속았어. 왜 그렇게 도드슨이 앨런을 죽였다고 확신하지? 사실 도드슨은 네가 그의 자리를 차지하려고 앨런을 죽였다고 생각하고 있어...";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "나는 그 자가 무슨 생각을 하든 신경 안 써. 모든 증거가 그놈을 가리키고 있어. 감옥에 들어갈 수 있었던 건 그와 그의 부하들뿐이었지. 앨런은 그의 손아귀에 있었어. 레드 메리가 나한테 많은 걸 말해줬지. 앨런이 살해되기 전에, 도드슨이 직접 감옥을 방문했어. 그 자가 그렇게 자주 오는 것도 아니거든.";
			link.l1 = "그가 죽는 걸 봤어?";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "헛소리 마! 당연히 안 그랬지.";
			link.l1 = "치미세도 그래. 그래, 그래, 리바도스의 마법사, 알란 옆에 앉아 있던 그 사람 말이야. 그도 최근에 거기서 살해당했어. 나는 그가 죽기 전날 감옥에 있었고, 그와 이야기를 나눴지. 밀로우는 상어호의 보선장인 챈드 캐퍼에게 살해당했어.";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "정말이야?";
			link.l1 = "생각해 봐. 치미셋은 네가 제독과 어떤 사이인지 신경도 안 썼어. 거짓말할 이유도 없었지. 그 늙은 마법사는 차드를 두려워했어, 자기가 다음 차례일 거라고 생각했지. 결국 맞았어, 차드는 제독이 그를 풀어주려 한다는 걸 알자마자 그를 죽였으니까.";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "하지만 왜 카퍼가 앨런의 죽음을 원했지?";
			link.l1 = "젠장, 정말 이해 못 하겠어? 내가 카퍼가 레드 메리랑 손잡았다고 말했잖아. 그 자식은 샤크의 자리를 빼앗으려고 교활한 계획을 세웠지. 앨런 밀로우를 죽이고 샤크가 그 죽음에 연루됐다는 소문을 퍼뜨려서, 결국 나르발 클랜이 제독에게 적대적으로 만들었어...";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			dialog.text = "";
			link.l1 = "멍청한 소녀 메리는 그를 믿고 자기 남자친구의 진짜 살인범 편에 섰지. 그들은 몇몇 나르발들을 설득해서 자기 편으로 끌어들였어; 메리한테는 쉬운 일이었겠지. 그리고 나서 파지오의 선실에서 제독을 공격하는 일을 꾸몄어, 거기서 제독은 억지로 초대장을 쓰게 되었지...";
			link.l1.go = "shark_10";
		break;
		
		case "shark_10":
			dialog.text = "";
			link.l1 = "파지오에게서 모든 걸 설명하는 편지를 받았어. 치미셋은 위험한 증인이라서 챠드가 죽였지. 그는 나르발들과 협력하고 있었고, 리바도스는 샤크와의 대화 중에 이 소식을 들으면 무척 기뻐할 거야.\n이 편지를 보여주면 챠드가 네 편이 되었다는 걸 블랙 에디에게 쉽게 증명할 수 있어.";
			link.l1.go = "shark_11";
		break;
		
		case "shark_11":
			dialog.text = "흠. 네가 모든 패를 쥐고 있는데, 그럼 여기서 뭐 하는 거지? 나한테 뭔가 원하는 게 있지?";
			link.l1 = "그래, 그렇다고 생각해. 이 모든 게 전부 챈드의 계획이었고, 너는 관련이 없다고 믿으니까. 챈드는 메리를 속였고, 메리는 네 클랜 친구들에게 도움을 청했지, 그게 전부야. 적어도, 나는 너나 다른 나르발에 불리한 증거는 아직 못 찾았어...";
			link.l1.go = "shark_12";
		break;
		
		case "shark_12":
			dialog.text = "";
			link.l1 = "하지만 그렇다고 해서 다른 음모꾼들이 남아 있지 않다는 뜻은 아니야.\n그놈들을 찾아줬으면 해. 그러면 아마 피바람 없이 일을 마무리할 수 있을 거야.";
			link.l1.go = "shark_13";
		break;
		
		case "shark_13":
			dialog.text = "이미 말했지만 내 부하들 중 누구도 관여하지 않았어. 말로우가 죽은 뒤, 메리는 사실상 클랜을 떠나 자기 선실에 틀어박혔지. 솔직히 어떻게 그녀가 다른 이들을 설득해서 그 일에 가담하게 만들었는지는 나도 몰라. 하지만 결국 성공한 것 같군. 맹세컨대, 나도 내 클랜 사람들도 제독을 해치려는 행동은 하지 않았어. 최근에 너무 많은 사람을 잃어서, 지금은 더러운 일에 휘말리고 싶지 않아. 설령 제독이 리바도스와 손을 잡고 공격해 온다 해도 두렵지 않아. 나르발들은 진정한 전사들이고, 마지막 전투에서 그걸 증명할 거야. 하지만 그건 의미 없는 짓이지. 우리는 이미 제독과 평화를 유지하기로 결정했으니까. 리바도스는 별개의 문제야; 우리는 흑인들과는 협상하지 않아. 나는 제독에게 직접 사과할 준비가 되어 있어. 밀로우의 죽음 때문에 생긴 내 의심과 그를 공격한 일에 대해 용서를 구할 거야. 내 진심을 증명하기 위해 성경에 맹세하겠어. 너와 도드슨도 그걸로 괜찮겠나?";
			link.l1 = "그래. 네 부하들이 속임수를 쓰지 않을 거라는 확신이 있나?";
			link.l1.go = "shark_14";
		break;
		
		case "shark_14":
			dialog.text = "물론이지. 나는 내 부족에게 앨런 밀로우의 진짜 살인범에 대해 알릴 거야. 내 부하들과 제독과의 관계도 곧바로 달라질 거라고 장담하지. 그런데, 그 다음엔 학살이 필요하겠나?";
			link.l1 = "아니, 그렇게 되지 않을 거야. 내가 막으러 왔으니까. 나는 너를 믿어, 도널드, 그리고 샤크를 설득해 볼게. 아직 남은 논리가 좀 있어... 또 보자, 도널드!";
			link.l1.go = "shark_15";
		break;
		
		case "shark_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "narval"; // ноду Акуле
			AddQuestRecord("SharkHunt", "26");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "narval_wait":
			dialog.text = "이미 제독과 이야기해 봤어? 무슨 결과라도 있었어?";
			link.l1 = "진전이 있군. 나중에 보자...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "shark_16":
			dialog.text = "이미 제독과 이야기해 봤어? 무슨 성과라도 있었나?";
			link.l1 = "그래, 들었네. 사과는 받아들이겠고, 자네 부족의 고소도 철회하겠네. 더 있어: 샤크가 자네를 만나고 싶어 하네. 앞으로 있을 나르발과 해적들 사이의 평화 협정 조건에 대해 논의하자고 하네.";
			link.l1.go = "shark_17";
		break;
		
		case "shark_17":
			dialog.text = "솔직히 말해서, 나는 예상하지 못했어... 정말 좋은 소식이군. 어쩌면 우리 클랜의 식량 가격도 다시 생각해볼 수 있겠고, 리바도스에 관한 새로운 정책도 세울 수 있겠어.";
			link.l1 = "그건 너와 제독만의 문제야.";
			link.l1.go = "shark_18";
		break;
		
		case "shark_18":
			dialog.text = "물론이지. 너는 쓸데없는 유혈 사태를 막아줬고, 어쩌면 내 부하들이 전멸하는 것도 막아줬으니, 너는 나와 우리 나르발 클랜에 큰 은혜를 베풀었어. 내 감사의 표시로 이 타워 머스킷을 가져가라. 이런 무기는 다른 데서 구할 수 없을 거다\n게다가 이제 너도 다른 클랜원들처럼 우리 제한 구역을 자유롭게 드나들 수 있다.";
			link.l1 = "고마워! 그럼 이만, 할 일이 많거든.";
			link.l1.go = "shark_19";
		break;
		
		case "shark_19":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower mousqueton");
			PlaySound("interface\important_item.wav");
			dialog.text = "행운을 빌지. 궁금한 게 있으면 나한테 와.";
			link.l1 = "알겠어. 또 보자!";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("They say that you are a friend of Donald, Greenspen, the leader of Narwhals. Well, Rivados hate you now...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are Narwhal now. Or do you serve under admiral's command? I don't get it...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I've heard that you have made peace between admiral and Narwhals. Hm, Rivados must be insane about that...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("So Chad Kapper was a murderer of Alan Milrow! That is surprising!", "LostShipsCity", 5, 2, "LSC", "");
		break;
		
		case "grinspy_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "이봐! "+GetFullName(pchar)+"! 너는... 아니, 그럴 리가! 살아 있었던 거야?!";
				link.l1 = "내 죽음에 대한 소문은 좀 과장됐더군, 도널드. 하하, 다시 보게 되어 반갑다!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "아, 친구야 "+GetFullName(pchar)+"! 뭐 필요해?";
			link.l1 = "아니, 없어. 그냥 인사나 하려고 왔어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "grinspy_wait";
		break;
		
		case "negotiations":
			dialog.text = "나한테 무슨 볼일이 있지?";
			link.l1 = "아주 불쾌한 소식이야, 도널드. 스티븐의 목숨을 노린 시도가 있었어. 네 클랜의 전사들이 연루됐지.";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			dialog.text = "그건 잘 모르겠군. 왜 내 부하들이 연루됐다고 생각하지?";
			link.l1 = "내가 직접 몇 놈을 죽였거든, 이 모든 난장판의 주범인 제독의 보선장 챈드 캐퍼와 함께 말이야. 혼자서는 못 했으니 네 부하들이 그를 많이 도왔지. 제독도 그 사실을 알고 있고, 아주, 아주 화가 나 있지.";
			link.l1.go = "negotiations_2";
		break;
		
		case "negotiations_2":
			dialog.text = "내 부하들? 누구 말이지? 이름을 댈 수 있나?";
			link.l1 = "자기소개도 안 했어. 그냥 총 쏘고 칼질만 했지. 네 동료들은 무모하더군. 자기 편까지도 공격할 수 있다니. 나나 제독한테 덤비는 건 그렇다 쳐도, 그 아가씨를 죽이려고 하다니?";
			link.l1.go = "negotiations_3";
		break;
		
		case "negotiations_3":
			dialog.text = "흠. 누구에 대해 말하는 거지?";
			if (pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "내가 누구에 대해 말하고 있는지 아나? 나는 레드 메리에게 일어난 습격에 대해 말하고 있지. 두 명의 나르발이 그녀를 죽이려고 했어. 나는 정말 우연히 결정적인 순간에 그녀의 선실에 도착했지. 내가 조금만 늦었어도 그녀는 죽었을 거야. 그놈들 이름은 묻지 못했어, 미안하지만, 그들과 얘기할 시간이 없었거든. 하지만 메리가 그들이 나르발이라고 했어.";
				link.l1.go = "negotiations_4";
			}
			else
			{
				link.l1 = "내가 누구에 대해 말하는지 아나? 나는 레드 메리를 공격하고 그녀를 죽인 그 두 명의 나르발에 대해 말하고 있지."link.l1.go ="negotiations_6";
			}
		break;
		
		case "negotiations_4":
			dialog.text = "뭐라고? 왜 나한테 말하지 않았지?! 바로 행동했을 텐데!";
			link.l1 = "그녀는 최근에 자기 선실에서 나오는 것조차 두려워했어. 얼마 전에 너랑 다투기도 했는데, 그런 그녀가 왜 너한테 달려가서 도움을 청해야 하지?";
			link.l1.go = "negotiations_5";
		break;
		
		case "negotiations_5":
			dialog.text = "나 그 여자랑 말다툼한 거 아니야! 그 여자가 나한테 말도 안 되는 걸 요구해서, 심하게 말다툼했고 내가 내쫓았지. 하지만 그게 내가...\n";
			link.l1 = "좋아, 뭐 어쩌겠어. 어쨌든 이제 모든 문제가 해결됐으니까. 하지만 네 놈들 중에 개자식들이 있다는 건 사실이야.";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_6":
			dialog.text = "뭐라고? 그녀가 나르발들에게 죽었어? 왜?";
			link.l1 = "채드 카퍼의 명령이었어, 도널드. 그 여자는 너무 많은 걸 알고 있었고, 채드를 돕는 걸 거부했지. 그래서 이제 그 불쌍한 아가씨는 죽었어!";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_7":
			dialog.text = "맹세코, 난 그 일에 대해 몰랐어!";
			link.l1 = "그래, 네가 그런 건 아니지... 하지만 제독 얘기를 해보자. 차드 카퍼가 그 시도를 조직했고 네 부하들이 그를 도왔어. 그들은 도드슨을 독살하려 했고, 내가 간신히 막았지.";
			link.l1.go = "negotiations_8";
		break;
		
		case "negotiations_8":
			dialog.text = "나는 그런 걸 주문한 적 없어. 도드슨도 내가 고 앨런의 정책을 지지하지 않는다는 걸 알아, 그리고 나는 살찐 소송보다는 마른 타협이 낫다고 생각해.";
			link.l1 = "제독을 설득해야 할 거야, 쉽지 않을 거다. 그 시도 이후로 도드슨은 모든 나르발들에게 분노하고 있어. 그는 너희에게 전쟁을 선포하려 하고 있지.";
			link.l1.go = "negotiations_9";
		break;
		
		case "negotiations_9":
			dialog.text = "제독이 자기 행동을 이해하길 바라지. 내 부하들이 반격할 수 있다는 걸 의심하는 건가?";
			link.l1 = "그렇지. 그는 너희 클랜이 도적 떼라고 생각해서, 네놈들이 모두를 죽이기 전에 반드시 없애야 한다고 믿고 있어. 게다가, 우리는 리바도스와도 끈끈한 관계가 있지. 나는 그냥 블랙 에디한테 가서 동맹을 제안할 수 있어. 우리 모두를 상대로 너희는 버틸 수 없을 거다.";
			link.l1.go = "negotiations_10";
		break;
		
		case "negotiations_10":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Call Red Mary if you don't believe me and ask her! She will confirm.";
			else sTemp = "I have a letter from Chad to Mary which proves everything.";
			dialog.text = "젠장! 왜 몇몇 멍청이들 때문에 우리 전체 클랜이 대가를 치러야 하지? 내가 겁먹었다고 생각하지 마. 우리는 전사들이고, 마지막 전투에서도 그걸 증명할 거야. 하지만 나는 정의를 원해. 사실, 감옥에서 앨런 밀로우를 죽인 책임은 바로 제독에게 있어.";
			link.l1 = "어떻게 네가 우두머리가 될 수 있지, 도널드... 너는 메리나 앨런에 대해 아무것도 모르잖아. 채드 카퍼가 그를 죽였어. "+sTemp+" 그자는 나르발들을 제독에게 반감 갖게 만들고, 일부를 자기 편으로 끌어들이려고 그렇게 한 거야.";
			link.l1.go = "negotiations_11";
		break;
		
		case "negotiations_11":
			dialog.text = "알겠어. 좋아. 다른 식으로 얘기해 보자. 여기 온 이유가 있겠지? 뭘 원하는 거야?";
			link.l1 = "나는 이 섬에서 피비린내 나는 난장판이 벌어지는 걸 원하지 않아. 누구도 죽는 걸 바라지 않지. 나 또한 모든 나르발 놈들을 없애버린다는 생각이 마음에 들지 않아, 하지만 리바도스와 우리라면 그럴 힘이 있다는 건 분명히 말할 수 있어. 그리고 몇몇 개자식들 때문에 전체 클랜이 책임을 져야 한다고도 생각하지 않아...";
			link.l1.go = "negotiations_12";
		break;
		
		case "negotiations_12":
			dialog.text = "";
			link.l1 = "하지만 내 표만으론 부족해 – 공식적으로 제독에게 그 시도는 너와 네 클랜이 승인한 것이 아니며, 도드슨을 죽일 계획도 없다는 점을 확실히 밝혀야 해.";
			link.l1.go = "negotiations_13";
		break;
		
		case "negotiations_13":
			dialog.text = "내가 뭘 할 수 있겠소? 시도한 것과 말로우의 죽음에 대해 의심한 것 모두 사과할 준비가 되어 있소. 내가 그에게 나르발들이 그를 상대로 아무것도 꾸미지 않고 있다는 걸 확신시켜 줄 수 있소, 그리고 성경에 맹세하겠소. 당신과 도드슨은 그 정도면 충분하겠소?";
			link.l1 = "그러지. 도드슨에게 직접 찾아가면 분명 통할 거라 생각해. 하지만 먼저 네 의도를 도드슨에게 알리고, 결과를 가지고 다시 찾아오겠네.";
			link.l1.go = "negotiations_14";
		break;
		
		case "negotiations_14":
			dialog.text = "좋아. 기다릴게.";
			link.l1 = "곧 돌아올게...";
			link.l1.go = "negotiations_15";
		break;
		
		case "negotiations_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "peace"; // ноду Акуле
			sld = characterFromId("Dexter");
			sld.dialog.currentnode = "First time"; 
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto11");
			AddQuestRecord("SharkHunt", "56");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "negotiations_17":
			dialog.text = "이미 제독과 얘기해 봤어? 무슨 결과라도 있었나?";
			link.l1 = "그래, 봤지. 그에게 공식적으로 찾아가면 문제가 해결될 거야.";
			link.l1.go = "negotiations_18";
		break;
		
		case "negotiations_18":
			dialog.text = "솔직히 말해서, 나는 기대하지 않았어... 정말 좋은 소식이군.";
			link.l1 = "그래, 있잖아, 나도 기뻐.";
			link.l1.go = "negotiations_19";
		break;
		
		case "negotiations_19":
			dialog.text = "의미 없는 학살, 어쩌면 우리 민족의 완전한 멸종까지도 막아줌으로써 너는 나르발 클랜에 큰 은혜를 베풀었어. 이 탑 머스킷을 주겠다 - 이런 무기는 또 없을 거다. 그리고 우리 배들도 아무 제한 없이 방문해도 된다.";
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				link.l1 = "고맙네. 정말 귀중한 선물이야. 그리고 도널드, 한 가지 더 있네: 레드 메리와 화해하게. 그녀는 성미가 급하지만, 진심이고 정직한 사람이야. 자네와의 다툼 때문에 그녀가 클랜을 떠났고, 그 일로 그녀가 거의 목숨을 잃을 뻔했지.";
				link.l1.go = "negotiations_20";
			}
			else
			{
				link.l1 = "고맙소. 정말 귀한 선물이군. 그리고 이렇게 잘 끝나서 진심으로 기쁘오.";
				link.l1.go = "negotiations_21";
			}
		break;
		
		case "negotiations_20":
			dialog.text = "그녀에게 내가 그녀를 다치게 한 것과 감히 그녀를 공격한 그 두 놈에 대해 용서해 달라고 전해 줘. 너희 둘은... 친구 맞지?";
			link.l1 = "맞아, 도널드. 내가 그녀에게 말할게. 그리고 이렇게 모든 일이 잘 끝나서 정말 기뻐.";
			link.l1.go = "negotiations_21";
		break;
		
		case "negotiations_21":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower musket");
			PlaySound("interface\important_item.wav");
			dialog.text = "행운을 빌어. 궁금한 게 있으면 나한테 와.";
			link.l1 = "좋아. 잘 가!";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			sld = characterFromId("Mary");
			sld.quest.donald = "true";
			LocatorReloadEnterDisable("CeresSmithy", "reload3", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload4", false); // открываем Церес изнутри
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			// здесь почищу весь хлам, который накопился
			DeleteAttribute(pchar, "questTemp.LSC.Donald_enter"); // атрибут гардов
			DeleteAttribute(pchar, "questTemp.LSC.Florentina");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_poison");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_warning");
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			DeleteAttribute(pchar, "questTemp.LSC.CapperDie_Aeva");
			AddSimpleRumourCityTip("They say that you are a friend of Donald, Greenspen, the leader of Narwhals. Well, Rivados hate you now...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are Narwhal now. Or do you serve under admiral's command? I don't get it...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I've heard that you have made peace between admiral and Narwhals. Hm, Rivados must be insane about that...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("So Chad Kapper was a murderer of Alan Milrow! That is surprising!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("Take care of Red Mary cause you are lucky to be with her - she is so reckless! She always gets in trouble...", "LostShipsCity", 20, 5, "LSC", "");
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("거기서 뭐 하는 거야, 응? 도둑놈!","저것 좀 봐! 내가 잠깐 생각에 잠긴 사이에, 네가 내 상자를 뒤지기로 했군!","내 상자를 뒤지려고 했나? 그냥 넘어가지 않을 거야!");
			link.l1 = "젠장!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "뭐?! 내 상자들을 뒤지려고? 그냥 넘어가지 않을 거야!";
			link.l1 = "어리석은 계집애!";
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
			dialog.text = LinkRandPhrase("이봐, 무기는 집어넣는 게 좋겠어. 그거 보면 신경이 곤두서거든.","여기서는 칼을 들고 뛰는 건 용납되지 않아. 집어 넣어.","이봐, 중세 기사처럼 칼 들고 설치지 마. 집어넣어, 너한테 안 어울리거든...");
			link.l1 = LinkRandPhrase("좋아.","그래.","말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"이봐, 나는 이 도시의 시민이야. 그러니 칼 좀 내려줘.","이봐, 나는 이 도시의 시민이니 칼을 거둬 주겠나.");
				link.l1 = LinkRandPhrase("좋아.","그래.","말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"조심해, 친구. 무기 들고 돌아다니면 신경이 곤두서거든...","사내들이 무기를 뽑은 채 내 앞을 지나가는 건 싫어. 무섭단 말이야...");
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
