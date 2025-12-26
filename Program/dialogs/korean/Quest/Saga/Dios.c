// Хосе Диос - картограф
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "뭐 원하는 거라도 있나?";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "dios")
			{
				link.l3 = TimeGreeting()+"! 말해 봐, 너 호세 디오스, 지도 제작자 맞지?";
				link.l3.go = "island";
			}
			link.l1 = "아니, 아무것도 없어.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;
		
		case "island":
			dialog.text = "그래, 나다. 난 너를 모른다, 나리. 나에게서 뭘 원하는 거지?";
			link.l1 = "내 이름은 "+GetFullName(pchar)+" 그리고 나는 얀 스벤손이 보냈어. 그를 기억하지?";
			link.l1.go = "island_1";
		break;
		
		case "island_1":
			dialog.text = "아, 스벤손 나리! 물론 기억하지요! 이리 와서 편히 쉬시오... 존경하는 얀은 어떻게 지내는가?";
			link.l1 = "고맙소, 그는 잘 지내고 있소. 디오스 나리, 당신의 도움이 필요하오. 당신 직업상 잘 알고 있을 문제에 대해 상담하고 싶소. 얀은 당신을 카리브 지역의 지리 전문가로 추천했소...";
			link.l1.go = "island_2";
		break;
		
		case "island_2":
			dialog.text = "듣고 있소, 나리. 군도 지리에 대해 무엇을 알고 싶으시오?";
			link.l1 = "아바나 북서쪽, 쿠바와 멕시코만 사이에 섬이나 다른 지형이 있다고들 하오. 그 섬은 어떤 지도에도 표시된 적이 없다 하오. 이 소문이 얼마나 믿을 만한지 알고 싶군.";
			link.l1.go = "island_3";
		break;
		
		case "island_3":
			dialog.text = "흠... 자네가 물은 것은 수년간 내 마음속을 뒤흔들던 일이네. 자네가 말한 그곳은 오랫동안 지리학자들의 호기심을 자극해왔지만, 그 지역을 탐험할 만큼 용감한 이는 아무도 없었지.";
			link.l1 = "왜?";
			link.l1.go = "island_4";
		break;
		
		case "island_4":
			dialog.text = "문제는, 그곳이 일종의 자연 이상 현상이라는 거야. 그 지역에서 폭풍이 일어날 확률이 다른 곳보다 훨씬 높지. 아마도 그 이유는 차가운 해류 때문일지도 모르지만, 그건 내 추측일 뿐이야. 그곳에서 많은 배들이 사라졌고, 그 사실만으로도 선원들이 그 지역을 피하기에 충분했지. 어차피 모든 주요 항로는 그 지역에서 멀리 떨어져 있어.";
			link.l1 = "그대도 진실을 모르는 것 같군...";
			link.l1.go = "island_5";
		break;
		
		case "island_5":
			dialog.text = "정확합니다, 나리. 하지만 역사적 문서 몇 개와 물증도 있으니, 그 장소가 실제로 존재할 가능성이 높다고 의심할 만한 충분한 근거가 있소.";
			link.l1 = "더 말해 줄 수 있나?";
			link.l1.go = "island_6";
		break;
		
		case "island_6":
			dialog.text = "물론입니다. 가장 중요한 증거는 1620년에 그 섬을 방문한 알바라도 선장의 일지에서 발췌한 내용을 담은 역사적 문서입니다. 꽤 흥미로운 이야기임을 장담하지요!";
			link.l1 = "알바라도 선장? 그 이름은 두 번째로 듣는군...";
			link.l1.go = "island_7";
		break;
		
		case "island_7":
			dialog.text = "놀랍지도 않소. 알바라도 선장의 이야기는 수년간 민담의 일부였지. 시간이 흐르며 소문과 거짓, 꿈으로 가득 차 전해졌고, 그래서 지금의 버려진 배들의 섬 전설이 된 것이오.\n소문은 변할 수 있지만, 종이와 잉크는 변하지 않소. 수백 년이 지나도 그대로 남아 있지. 자, 이 이야기를 읽어보시오. 어쩌면 그대가 찾는 것을 밝히는 데 도움이 될지도 모르오.";
			link.l1 = "고마워! 또 뭐 있어?";
			link.l1.go = "island_8";
		break;
		
		case "island_8":
			dialog.text = "그 지역의 바닷속이 높이 솟아 거대한 얕은 바다가 형성된다는 설이 있소. 그리고 조류에 대해서는 이미 언급했지. 선원들 말로는 갈매기와 다른 바닷새들도 많이 모인다고 하오. 알보라도는 프란시스코 베탕쿠르트 제독의 함대에 속했던 선박들의 이름을 언급했는데, 그 함대는 오십 년도 더 전에 사라진 함대요. 이것이 단순한 우연이라고는 생각하지 않소...\n";
			link.l1 = "나는 내 배로 돌아가서 알바라도의 기록을 꼼꼼히 읽어보겠소. 도스 나리, 도와주셔서 감사합니다!";
			link.l1.go = "island_9";
		break;
		
		case "island_9":
			dialog.text = "천만에요. 사실 나는 당신을 전혀 도와주지 않았소; 당신도 그 장소의 좌표를 갖고 있지 않고, 나 역시 마찬가지요. 거기에 사람이 사는 섬이 있다는 것도 증명할 수 없소. 하지만 내 이해로는, 당신이 그 지역을 탐험할 생각인 것 같군요?\n그렇다면, 어떤 정보라도, 특히 물질적 증거가 뒷받침된다면 나는 진심으로 감사할 것이오. 당신이 부유한 분인 것 같지만, 반드시 보답할 방법을 찾겠소.";
			link.l1 = "좋아. 그럼 거래가 성사된 거요, 디오스 나리. 어쩌면 내 기록도 언젠가 누군가 읽게 되겠지... 그리고 누군가는 전설을 쓸지도 모르고...";
			link.l1.go = "island_10";
		break;
		
		case "island_10":
			dialog.text = "왜 안 되겠소? 나리\n "+pchar.name+", 보아하니 당신은 여기저기 많이 다니는 모험심 강한 사람이군요. 그래서 부탁드릴 일이 있습니다.";
			link.l1 = "예? 듣고 있소.";
			link.l1.go = "island_11";
		break;
		
		case "island_11":
			dialog.text = "나는 지도 제작자라는 걸 알고 있겠지. 그래서 카리브 제도의 지도를 2년 동안 그려왔고, 누에바 그라나다 부왕의 대회를 위해 제독의 지도집을 만들고 있었어. 그런데 내가 해적들에게 붙잡혀 있을 때, 바로 스벤손 나리가 구해준 그 해적들한테 내 집에서 내 스물네 장의 지도가 모두 뻔뻔하게 도둑맞았지.\n난 분명 내 경쟁자 중 한 명이 내 지도를 손에 넣으려고 이 공격을 꾸몄다고 생각해. 시간이 꽤 흘렀지만, 내 지도 세트 중 한 장도 다시 본 적이 없어.";
			link.l1 = "알겠소. 당신은 내가 지도를 돌려주길 바라는군.";
			link.l1.go = "island_12";
		break;
		
		case "island_12":
			dialog.text = "정확하오. 아마 앞으로의 모험 중에 그 지도들을 찾게 될지도 모르지. 모두 내 표식이 있으니 쉽게 알아볼 수 있을 것이오. 만약 기적적으로 스물네 장의 지도를 모두 모은다면 후하게 보상해 주겠소.";
			link.l1 = "좋아. 이제부터 군도에서 찾는 모든 지도를 꼼꼼히 살펴보겠소. \n그럼, 이만 가보겠소. 흥미로운 대화와 문서에 감사하오.";
			link.l1.go = "island_13";
		break;
		
		case "island_13":
			DialogExit();
			AddQuestRecordInfo("LSC_Alvorado", "1");
			AddQuestRecord("SharkHunt", "4");
			pchar.questTemp.Saga.SharkHunt = "LSC";
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			pchar.questTemp.AdmiralMap = "true";
		break;
		
		case "Dios":
			dialog.text = "아-아, 너였군, 나리 "+GetFullName(pchar)+"뭐? 나한테 재미있는 얘기라도 있어?";
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 0 && CountAdmiralMapFromCharacter() < 24 && !CheckAttribute(npchar, "quest.mapinfo"))
			{
				link.l3 = TimeGreeting()+"! 신이시여, 제발, 제가 찾은 이 지도를 좀 봐주세요. 표식으로 보아 분명 당신의 지도 중 하나인 것 같습니다.";
				link.l3.go = "map_info";
			}
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 23)
			{
				link.l3 = TimeGreeting()+"! 신이시여, 좋은 소식이 있습니다. 원하신 대로 당신의 특별한 지도 전체 세트를 모을 수 있었소. 여기 스물네 장의 지도가 모두 있습니다.";
				link.l3.go = "amap";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Dios")) // был в LSC
			{
				link.l4 = TimeGreeting()+"! 그래, 있었지. 우리가 얘기하던 그 신비로운 곳에 있었어.";
				link.l4.go = "LSC";
			}
			link.l9 = "아직 아무 소식도 없습니다, 나리. 그냥 어떻게 지내시는지 궁금해서 왔습니다.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Dios";
		break;
		
		case "map_info":
			dialog.text = "보여줘... (살펴보며) 물론이지! 이건 제독님의 지도첩에 들어가는 내 지도 중 하나야! 선장, 내 부탁이니 나머지 지도들도 꼭 찾아줘! 거의 불가능한 일인 건 알지만... 그래도 희망을 잃고 싶지 않아.";
			link.l1 = "잃어버리지 마시오, 나리. 내가 이 지도를 찾았으니, 나머지도 찾을 수 있을 가능성이 있소. 아직 그들은 카리브 해에 있소.";
			link.l1.go = "map_info_1";
		break;
		
		case "map_info_1":
			dialog.text = "선장 나리의 낙관적인 태도가 정말 힘이 됩니다. 어쩌면 아직도 돈 후안 데 코르도바에게 이 군도 최고의 지도 제작자가 누구인지 보여줄 기회가 있을지도 모르겠군요!";
			link.l1 = "경쟁하는 모든 악의적인 자들을 이길 수 있을 것이오. 지도들은 정말 훌륭하구려... 안녕히 가시오, 나리!";
			link.l1.go = "exit";
			npchar.quest.mapinfo = "true";
			NextDiag.TempNode = "Dios";
		break;
		
		case "amap":
			Achievment_Set("ach_CL_110");
			dialog.text = "내 눈을 믿을 수가 없어! 정말로 그들을 찾은 거야? 전부 다?";
			link.l1 = "그래. 쉽지는 않았지만, 이번 일에서는 운이 내 편이었지. 자, 카드들을 가져가게 — 정말 훌륭하군. 내가 전에 본 어떤 카드보다도 훨씬 뛰어나네.";
			link.l1.go = "amap_1";
		break;
		
		case "amap_1":
			RemoveAllAdmiralMap()
			Log_Info("You have given the complete set of admiral's maps");
			PlaySound("interface\important_item.wav");
			dialog.text = "믿을 수 없어! 이건 정말 너무 놀라워! 솔직히 말해서, 이런 순간이 올 거라고는 한 번도 믿지 않았어.";
			link.l1 = "숨 쉬는 한, 희망이 있나이다, 디오스 나리. 이제 돈 코르도바를 만나러 가셔도 됩니다. 분명 그분께서 당신의 재능을 높이 평가하실 것이오.";
			link.l1.go = "amap_2";
		break;
		
		case "amap_2":
			dialog.text = "감사합니다, 선장님! 당신이 내게 얼마나 큰 은혜를 베풀었는지조차 모를 거요. 약속한 대로 보상을 드리겠소. 그리고 선물도 하나 준비했소. 선장이시니 분명 유용하게 쓰실 거라 생각하오.";
			link.l1 = "흥미롭게 하는군, 나리!";
			link.l1.go = "amap_3";
		break;
		
		case "amap_3":
			GiveItem2Character(pchar, "spyglass5"); 
			Log_Info("You have received a ship telescope");
			PlaySound("interface\important_item.wav");
			dialog.text = "여기 있소! 이것은 내가 직접 설계한 배용 망원경이오. 세상에 단 하나뿐인 물건이라 다른 곳에서는 절대 구할 수 없소. 렌즈는 스페인 최고의 장인이 유럽에서 만든 것이오. 망원경 케이스는 친한 총기장이가 만들어 주었지. 특별한 삼각대 덕분에 배가 아무리 흔들려도 정확히 조준할 수 있소. 배든 요새든, 필요한 것은 뭐든 다 볼 수 있을 것이오.";
			link.l1 = "정말 멋진 선물이군요! 감사합니다, 디오스 나리.";
			link.l1.go = "amap_4";
		break;
		
		case "amap_4":
			dialog.text = "쓰시오, 선장 나리. 내 망원경이 도움이 되길 바라오.";
			link.l1 = "의심할 여지 없지! 내 배 갑판에 그걸 설치하고 들여다볼 생각에 기대가 되는군.";
			link.l1.go = "amapcopy_01";
		break;
		
		case "amapcopy_01":
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 1000); // харизма
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность (раз телескоп дали)
			ChangeCharacterComplexReputation(pchar, "nobility", 10);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 5);// репутация-авторитет
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			ChangeOfficersLoyality("good_all", 5);
			DeleteAttribute(pchar, "questTemp.AdmiralMap");
			dialog.text = "게다가, 일이 이렇게 된 김에 당신께 또 하나 작은 제안을 드리고 싶소.";
			link.l1 = "무슨 일이오? 아주 주의 깊게 듣고 있소.";
			link.l1.go = "best_map";
		break;
		
		case "best_map":
			dialog.text = "이 지도들은 탐험가에게는 훌륭하지만, 선장에게 필요한 모든 것을 제공하지는 않는다는 생각이 들었소. \n잘 생각해 보시오. 만과 곶, 석호가 아주 정밀하게 그려져 있지만, 이 지도만으로는 섬들 사이의 항로를 짤 수 없소.";
			link.l1 = "맞아, 그걸로는 항해를 할 수 없지.";
			link.l1.go = "best_map_01";
		break;
		
		case "best_map_01":
			dialog.text = "하지만 내가 군도 지도를 직접 만들어 줄 수도 있어! 네덜란드 서인도 회사에서 살 수 있는 그런 평범한 지도가 아니라, 유일무이하고 훌륭한 지도지.";
			link.l1 = "감사합니다, 디오스 나리, 하지만 그런 지도는 필요 없소. 그래도 제안해 주셔서 정말 고맙소!";
			link.l1.go = "best_map_02";
			link.l2 = "장난해?! 세뇨르 디오스, 내가 어떻게 거절할 수 있겠어? 필요한 게 뭔지만 말해. 돈이든 도구든 아끼지 않을 테니까!";
			link.l2.go = "best_map_04";
		break;
		
		case "best_map_02":
			dialog.text = "뭐, 제안은 해봐야 했지. 어쨌든, 당신과 거래해서 즐거웠소, 나리 "+pchar.lastname+"!";
			link.l1 = "나도 마찬가지야! 행운을 빌어!";
			link.l1.go = "best_map_03";
		break;
		
		case "best_map_03":
			DeleteAttribute(pchar, "questTemp.AdmiralMapCopy");
			DialogExit();
			NextDiag.CurrentNode = "Dios";
		break;
		
		case "best_map_04":
			dialog.text = "악기는 이미 가지고 있으니, 고맙소. 군도 표준 지도와 나침반, 그리고 등급이 매겨진 크로노미터가 필요하오 — 지도는 반드시 정확해야 하오, 그렇지 않으면 그건 방해 행위나 다름없소. 그리고 대가는 두블룬 한 상자요.";
			if(CheckAMapItems())
			{
				link.l1 = "네가 말한 건 이미 전부 가지고 있어. 자, 가져가.";
				link.l1.go = "best_map_07";
			}
			link.l2 = "제도 일반 지도, 나침반, 등급이 매겨진 크로노미터, 그리고 두블룬이 든 상자 한 개. 알겠어! 최대한 빨리 가져다줄 테니 기다려!";
			link.l2.go = "best_map_07e";
		break;
		
		case "best_map_07e":
			DialogExit();
			NextDiag.CurrentNode = "best_map_waititems";
		break;
		
		case "best_map_waititems":
			dialog.text = "안녕하시오, 나의 친애하는 친구여! 군도 표준 지도, 나침반, 정밀 크로노미터, 그리고 두블룬 상자를 가져왔는가?";
			link.l1 = "아직 아닙니다, 디오스 나리. 하지만 곧 하겠습니다, 약속드려요!";
			link.l1.go = "best_map_07e";
			if(CheckAMapItems())
			{
				link.l2 = "예, 디오스 나리. 여기, 전부 다 있습니다 — 가져가십시오.";
				link.l2.go = "best_map_07";
			}
		break;
		
		case "best_map_07":
		    Log_Info("You handed over a regular map of the archipelago, a boussole, a tariffed chronometer, and a chest with doubloons.");
			TakeNItems(pchar,"chest", -1);
			TakeNItems(pchar,"map_normal", -1);
			TakeNItems(pchar,"bussol", -1);
			TakeNItems(pchar,"clock2", -1);
			dialog.text = "좋아, 그럼 일 시작하지. 일주일 후에 다시 오면, 절대 후회하지 않을 거야!";
			link.l1 = "의심하지 않소, 나리. 일주일 후에 보지!";
			link.l1.go = "best_map_08";
		break;
		
		case "best_map_08":
			SetTimerFunction("AdmAtlas_comlete", 0, 0, 7);
			NextDiag.CurrentNode = "best_map_wait";
			pchar.questTemp.AdmiralAtlas = true;
			DialogExit();
		break;
		
		case "best_map_wait":
			if(CheckAttribute(pchar,"questTemp.AdmiralAtlas") && pchar.questTemp.AdmiralAtlas == "complete")
			{
				dialog.text = "아, 나리 "+pchar.lastname+", 거기 있었군! 군도 지도를 완성했다는 소식을 전하게 되어 기쁘네! 감히 말하건대, 자네가 준 지도보다 훨씬 뛰어나네.";
				link.l1 = "내 친구여... 이 지도는 정말 놀랍구나! 감히 말하건대, 걸작이야! 나를 위해 이렇게까지 해준 것에 어떻게 감사해야 할지 모르겠네!";
				link.l1.go = "best_map_09";
			}
			else
			{
				dialog.text = "안녕하시오, 나리! 미안하오만, 지도가 아직 준비되지 않았소.";
				link.l1 = "그래, 일주일이 필요하다고 했던 거 기억하네. 그냥 네가 잘 지내는지 확인하러 왔어.";
				link.l1.go = "best_map_wait_01";
			}
		break;
		
		case "best_map_wait_01":
			NextDiag.CurrentNode = "best_map_wait";
			DialogExit();
		break;
		
		case "best_map_09":
			dialog.text = "아, 이보게, 친구. 진정 지도를 감상할 줄 아는 고귀한 선장을 위해 이런 지도를 만드는 건 내게도 즐거움이었네. 아, 그리고 여기 자네의 원본 해도도 돌려주지. 바다가 자네에게 너그러이 대하길 바라네!";
			link.l1 = "정말 감사합니다! 맞아요 — 이 지도는 저에게 정말로 값진 보물이에요. 안녕히 계세요, 디오스 나리!";
			link.l1.go = "best_map_10";
		break;
		
		case "best_map_10":
			TakeNItems(pchar,"Map_Best", 1);
			TakeNItems(pchar,"map_normal", 1);
			Log_Info("You received an excellent archipelago map!");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "Dios";
			DialogExit();
		break;
		
		case "LSC":
			dialog.text = "정말이야?! 찾았어? 편하게 앉아, 앞으로 할 이야기가 좀 길어질 것 같은데, 맞지?";
			link.l1 = "섬에 대해 정말 할 말이 많아. 하지만 먼저, 내게 한 가지 약속을 해 줬으면 해. 당신이 명예로운 사람이라는 걸 알기에, 분명 약속을 지킬 거라 믿어...";
			link.l1.go = "LSC_1";
		break;
		
		case "LSC_1":
			dialog.text = "무슨 말씀이십니까, 선장님?";
			link.l1 = "그곳에는 사람들이 살고 있어... 누가 그들의 삶에 간섭하면 좋아하지 않을 거야. '조사' 함대가 올지도 모른다는 소식이 환영받을 것 같지는 않아.";
			link.l1.go = "LSC_1_1";
		break;
		
		case "LSC_1_1":
			dialog.text = "";
			link.l1 = "그러니 내게 명예를 걸고 약속해 주었으면 하오. 우리가 이 대화를 나눈 후 십 년 동안은 섬을 찾는 데 쓸 수 있는 어떤 정보도 공개하지 않겠다고 말이오. 현지인들이나 그들의 삶에 관한 정보는 얼마든지 공개해도 좋으나, 섬의 위치만은 절대 밝히지 마시오.";
			link.l1.go = "LSC_2";
		break;
		
		case "LSC_2":
			dialog.text = "동의하오, 선장. 나는 귀족으로서 맹세하오, 앞으로 10년 동안 그 섬의 위치나 거주민들에게 해가 될 수 있는 어떤 정보도 누구에게도 절대 말하지 않겠소.";
			link.l1 = "그럼 내 이야기를 들어봐. 원하면 적어도 좋아. 자, 그 섬은 넓은 모래톱 위에 선체가 널브러진 수많은 난파선들로 이루어져 있지...\n";
			link.l1.go = "LSC_3";
		break;
		
		case "LSC_3":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later...", "LSC_FinalDiosStory", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "LSC_4":
			dialog.text = "믿을 수 없군! 정말 귀중한 정보를 주셨소, 선장님! 베탕쿠르 제독의 자손들이 그 섬에 살고 있다니! 이제 그의 함대에 무슨 일이 있었는지 알게 되었군. 그리고 카리브 제도 지도에서 미지의 영역이 하나 줄었소... 이야기를 들려주셔서 진심으로 감사하오, "+pchar.name+"!";
			link.l1 = "이제 내가 왜 내 정보를 전할 때 그렇게 조심하라고 했는지 알겠지?";
			link.l1.go = "LSC_5";
		break;
		
		case "LSC_5":
			dialog.text = "알겠소. 내 약속은 반드시 지키겠소. 말해 보시오... 그 섬에서 가져온 물건이 있소?";
			if (CheckCharacterItem(pchar, "LSC_navigation_map"))
			{
				link.l1 = "나는 버려진 배들의 섬으로 가는 항해 지침서를 가지고 있네. 여기, 한번 보게나.\n이 지침서가 있으면 작은 배로 암초와 잔해 사이를 지나 안전하게 섬에 상륙할 수 있지.\n이 지침서 없이는 그 섬에 도달하는 건 불가능하네.";
				link.l1.go = "LSC_6";
			}
			else
			{
				link.l1 = "유감스럽게도, 나는 아무것도 없어.";
				link.l1.go = "LSC_7_1";
			}
		break;
		
		case "LSC_6":
			Log_Info("You have given sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "(쳐다보며) 정말 훌륭한 문서군! 지도 제작에 능한 사람이 그린 게 분명하오. 나조차도 이보다 잘 그릴 수는 없었을 것이오. 대단하군! 선장, 이 항해 지침을 내게 주는 게 어떻겠소? 이야기는 이야기고, 이 문서는 반드시 구세계에서 가장 유명한 지리학자들에게 보여줘야 하오!";
			link.l1 = "나리 디오스, 유감스럽게도 이 문서는 제가 직접 필요하오. 이미 말씀드렸듯이, 이 문서 없이는 섬을 둘러싼 암초를 통과하는 것이 불가능하오. 하지만 원하신다면 지침의 사본을 만드셔도 되오, 그리고 그 사본을 갖게 되신다면 저로서도 매우 기쁠 것이오.";
			link.l1.go = "LSC_10";
			//link.l2 = "신이시여, 유감스럽게도 이 물건은 제가 직접 필요합니다. 이미 말씀드렸듯이, 이 섬 주변의 암초를 이 물건 없이는 절대 지나갈 수 없습니다. 과학을 위해서라면 희생하겠지만... 제 뜻을 이해하시리라 믿습니다.";
			//link.l2.go = "LSC_7";
		break;
		
		case "LSC_7":
			Log_Info("You received sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "물론이지요. 당신의 권리이니 아쉽기는 하지만... 아무튼, 이야기 들려주셔서 감사합니다! 지리학자, 지도 제작자, 그리고 다른 호기심 많은 이들에게 큰 도움을 주셨소.";
			link.l1 = "천만에요, 나리. 자, 이제 가봐야겠소. 안녕히 계시오.";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_7_1":
			dialog.text = "정말 안타깝군... 어쨌든, 이야기 들려줘서 고맙네! 자네 덕분에 지리학자, 지도 제작자, 그리고 다른 호기심 많은 이들에게 큰 도움이 되었어.";
			link.l1 = "천만에요, 나리. 자, 이제 가봐야겠소. 안녕히 계시오.";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_8":
			dialog.text = "물론이지, "+pchar.name+". 저에게 많은 시간을 내주셨군요. 스벤손 나리께 안부 전해 주십시오!";
			link.l1 = "안녕히 가십시오, Dios 나리.";
			link.l1.go = "LSC_9";
		break;
		
		case "LSC_9":
			DialogExit();
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 400);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 500); // харизма
			ChangeCharacterComplexReputation(pchar, "nobility", 5);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 2);// репутация-авторитет
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 5);
			DeleteAttribute(pchar, "questTemp.LSC.Dios");
			LAi_SetOwnerType(npchar);
		break;
		
		case "LSC_10":
			Log_Info("You received sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "정말 감사합니다! 참 친절하시군요. 잠시만 기다려 주십시오...";
			link.l1 = "...";
			link.l1.go = "LSC_11";
		break;
		
		case "LSC_11":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 0);
			npchar.dialog.currentnode = "LSC_12";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LSC_12":
			//RemoveItems(pchar, "LSC_navigation_map", 1);
			dialog.text = "정말 감사합니다! 참 친절하셨군요. 이제 우리는 구두 증언뿐만 아니라 물증도 갖게 되었소... 보답 없이 그냥 넘기지 않겠소, 선장. 작은 선물을 준비했으니 받아주시오.";
			link.l1 = "무슨 선물?";
			link.l1.go = "LSC_13";
		break;
		
		case "LSC_13":
			sld = characterFromId("Pirates_shipyarder");
			sld.quest.sextant = "true"; // атрибут Алексу на хронометр
			GiveItem2Character(pchar, "sextant1"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "나는 지도 제작과 지리학뿐만 아니라 수학과 천문학도 좋아하오. 위도와 경도를 측정할 수 있는 만능 도구를 만들기 위해 1년 동안 시도했소. 그리고 어느 정도 성과를 거두었지. 자, 한번 보시오:\n이것이 내 육분의요. 내가 직접 설계했소. 문제는, 이게 작동하지 않는다는 거요. 극도로 정밀한 크로노미터가 필요하오. 최고의 장인들이 만든 것조차 시간이 지나면 용납할 수 없는 오차를 내지. 그래서 지금은 내 도구가 쓸모가 없소.\n하지만 자네는 여행을 많이 하니, 어쩌면 육분의가 제대로 작동할 만큼 정확한 크로노미터를 찾을 수 있을지도 모르지. 그런 시계를 찾는다면, 부솔, 나침반, 아스트롤라베, 모래시계, 그리고 다른 믿을 수 없는 시계들은 더 이상 필요 없을 거요—내 도구 하나면 모두 대체할 수 있소.";
			link.l1 = "감사합니다, 디오스 나리. 당신의 발명이 제대로 작동하게 해 줄 크로노미터를 찾을 수 있길 바라지요. 저도 그런 장치가... 제대로 작동하는 상태로 있었으면 좋겠군요. 자, 이제 가봐야겠습니다. 안녕히 계십시오.";
			link.l1.go = "LSC_8";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("너는 "+GetSexPhrase("도둑이로군! 경비병들, 저 자를 잡아라","도둑이군! 경비병들, 저 여자 잡아라\n")+"!!!","믿을 수가 없군! 잠깐 한눈판 사이에 내 물건을 뒤지고 있다니! 멈춰, 도둑놈아!!!","경비병들! 도둑이야! 도둑을 잡아라!!!");
			link.l1 = "아아악, 악마다!!!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

bool CheckAMapItems()
{
	return GetCharacterItem(pchar,"chest")      && 
		   GetCharacterItem(pchar,"map_normal") &&
		   GetCharacterFreeItem(pchar,"bussol") &&
		   GetCharacterFreeItem(pchar,"clock2");
}