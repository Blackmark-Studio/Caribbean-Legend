// Глэдис МакАртур - приемная мать Элен
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if(pchar.questTemp.Saga == "helena1")
			{
				dialog.text = "아, 선장님! 있잖아요, 제가 헬렌에게 모든 걸 다 말했어요. 마음이 얼마나 홀가분해졌는지 상상도 못 하실 거예요!";
				link.l1 = "맥아더 양, 모든 걸 제대로 하셨소. 그 아가씨는 진실을 알아야 하오. 그리고 내가 여기 있는 것도 그녀 때문이오.";
				link.l1.go = "Helena_hire";
			}
			else
			{
				dialog.text = "안녕하시오, "+pchar.name+"! 다시 만나서 반갑네! 럼 한잔 할래?";
				link.l1 = "감사합니다, 맥아더 양, 하지만 지금은 너무 바쁩니다.";
				link.l1.go = "exit";			
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "FindHelena":
			dialog.text = "무슨 일이오, 나리?";
			link.l1 = "당신이 글래디스 맥아더인가?";
			link.l1.go = "FindHelena_1";
		break;
		
		case "FindHelena_1":
			dialog.text = "그렇소. 나는 자네를 기억하지 못하겠구만, 젊은이. 그러니 내게 무슨 볼일인지 설명해 주겠나?";
			link.l1 = "맥아더 양, 따님의 실종 이야기에 관심이 있습니다. 따님이 사라졌다고 생각하게 된 이유가 무엇입니까? 헬렌에게는 아주 능숙한 선원들이 있었다고 들었는데요...";
			link.l1.go = "FindHelena_2";
		break;
		
		case "FindHelena_2":
			dialog.text = "아, 저는 정말 확신합니다! 보세요, 제 남편의 기일이 다섯 날 전이었어요. 헬렌은 아버지를 무척 사랑해서 이 날을 절대 잊지 않을 겁니다. 그녀는 친절한 미스키토 인디언들에게서 레드우드 목재를 받으러 며칠만 떠났을 뿐이에요.\n인디언들은 우리 후견인 얀 스벤손을 존경하고 두려워합니다. 그들이 헬렌을 해칠 리 없지요. 스벤손 나리께서 이미 그들과 이야기하셨고, 목재도 그날 바로 실었습니다. 그 뒤로 헬렌을 본 사람은 아무도 없습니다.";
			link.l1 = "혹시 해적들이 그녀를 공격한 건가?";
			link.l1.go = "FindHelena_3";
		break;
		
		case "FindHelena_3":
			dialog.text = "말도 안 돼! 자네도 이미 스벤손 나리가 다섯 해적 남작 중 한 명이자 해안의 형제단 평의회 일원이라는 걸 알 텐데. 그의 허락 없이는 어떤 해적도 여기서 사냥할 수 없어. 하지만 신참일 수도 있지...";
			link.l1 = "그럼 스페인 놈들은? 혹시 스페인 순찰대를 만난 건 아닐까?";
			link.l1.go = "FindHelena_4";
		break;
		
		case "FindHelena_4":
			dialog.text = "나는 정치에는 별로 밝지 않지만, 이곳의 금광과 은광이 완전히 고갈되어 이제 귀한 히달고들이 목숨을 걸 만큼 남은 보물이 많지 않다고들 하오. 그래서 그들은 이곳에 드물게 찾아오는 손님이지. 게다가 인디언들은 그들에게 적대적이오.\n스페인 순찰대와 우연히 마주쳤다고 해도 헬렌에게 나쁘게 끝날 일은 없었을 것이오. 그들의 관점에서 헬렌은 불법적인 일을 한 적이 없으니까. '레인보우'는 네덜란드 국기를 달고 있었고, 헬렌의 서류들도 모두 정상이었소. 무역 허가증까지 포함해서 말이오.";
			link.l1 = "그녀가 가장 최근에 항해하기 전에 특별한 일이 있었소? 혹시 놓쳤을지도 모를 이상한 사건 같은 건 없었소?";
			link.l1.go = "FindHelena_5";
		break;
		
		case "FindHelena_5":
			dialog.text = "아, 아니오! 신께 감사드리오, 우리는 여기서 평화롭게 살고 있소. 하지만 몇 주 전에 헬렌이 또 다른 원치 않는 구혼자로부터 데이트를 청하는 편지를 받았소. 헬렌은 예쁘지만 부자는 아니오.\n그래서 구혼자가 많지만, 그 중 누구도 좋아하지 않고 결혼도 원치 않소. 이런 식으로 이미 많은 사람들을 속였지. 참으로 경박하오, 그녀의 어머니처럼!";
			link.l1 = "그런 부류의 여자로는 안 보이는데, 맥아더 양...";
			link.l1.go = "FindHelena_6";
		break;
		
		case "FindHelena_6":
			dialog.text = "뭐라고? 아, 됐어, 나 지금 상심했어. 내가 뭐라고 했지? 아, 맞다, 그 편지. 아무튼, 그 편지는 지미 히긴스가 쓴 거야. 그는 잭맨의 부하 중 한 명이고 마룬 타운에 살아. 우리 마을에도 자주 오지. 잭맨도 해적 남작이긴 한데, 스벤손 나리가 그를 싫어해. 왜 그런지는 나도 몰라.";
			link.l1 = "그럼 헬렌은?";
			link.l1.go = "FindHelena_7";
		break;
		
		case "FindHelena_7":
			dialog.text = "오, 그녀는 크게 웃었지. 하루 전에 영국 코르벳함 선장에게 청혼을 받았는데, 그 사람도 거절했거든. 그런데 이제 해적의 낡은 배에서 온 평범한 보선이 청혼을 한다니... 말도 안 되지, 션 맥아더의 딸은 훨씬 더 위엄 있는 남편을 원한다고!";
			link.l1 = "그 영국 선장의 이름이 뭐였지?";
			link.l1.go = "FindHelena_8";
		break;
		
		case "FindHelena_8":
			dialog.text = "오, 내가 어떻게 알겠어? 진짜 신사들은 여기선 드문 손님이야. 미안해, 기분 상하게 하려던 건 아니었어. 히긴스한테 물어봐. 그 사람은 이름을 기억할 거야. 지미가 헬렌 때문에 그 선장이랑 결투하려고 했거든. 친구들이 간신히 말렸지. 하지만 둘 다 헬렌이 떠나기 며칠 전에 블루웰드를 떠났어.";
			link.l1 = "음, 이야기해 주셔서 감사합니다. 당신의 사랑하는 이를 찾아보도록 하겠습니다. 무언가 알게 되면 당신이나 스벤손 나리에게 알려드리겠습니다. 따님이 무사히 살아 있기를 바랍니다.";
			link.l1.go = "FindHelena_9";
		break;
		
		case "FindHelena_9":
			dialog.text = "그녀를 찾으러 가시겠습니까? 신께서 함께하시고, 당신의 손을 인도하고 강하게 해주시길! 내가 당신을 위해 기도하겠소! 존경하는 분, 성함이 어떻게 되십니까?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+"곧 좋은 소식을 들고 돌아오길 바라오, 맥아더 양. 안녕히 계시오!";
			link.l1.go = "FindHelena_10";
		break;
		
		case "FindHelena_10":
			DialogExit();
			NextDiag.CurrentNode = "FindHelena_wait";
			AddQuestRecord("Saga", "1");
			pchar.questTemp.Saga = "maruntown";//идем к Джекману
			SetFunctionTimerCondition("Gladis_SetHome", 0, 0, 1, false);
			int iTime = 25-MOD_SKILL_ENEMY_RATE;
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime*2, false);
			}
			else SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime, false);
		break;
		
		case "FindHelena_wait":
			dialog.text = "내 불쌍한 딸에 대해 새로운 소식이 있소, "+pchar.name+"?";
			link.l1 = "죄송합니다, 맥아더 양, 아직 새로 드릴 소식이 없습니다만, 너무 낙심하지 마십시오. 계속해서 찾아보겠습니다. 나쁜 소식이 없다는 것만으로도 좋은 소식이지요.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FindHelena_wait";
		break;
		
		case "Helena_die":
			dialog.text = "너무 늦으셨소, 선장님. 내 불쌍한 딸의 시신이 앤티과 해안에서 발견되었소. 주여, 죽기 전에 저들이 얼마나 끔찍하게 고문했는지! 나는 내 아름다운 딸을 지키지 못했소...";
			link.l1 = "죄송하오. 내가 할 수 있는 일이 없었소...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_exit":
			dialog.text = "아, 젊은이, 제발, 내 슬픔과 함께 있게 내버려 두게...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_regard":
			dialog.text = "딸을 구해주신 것에 대해 어떻게 감사드려야 할지 모르겠습니다, 선장님. 딸에게 모든 이야기를 들었고, 당신의 용기와 명예에 감탄했습니다. 자, 이 금화들을 받으십시오. 많지는 않지만 진심을 담아 드리는 것입니다. 그리고 거절할 생각은 하지도 마십시오!";
			link.l1 = "좋아요, 글래디스, 안 할게. 하지만 나는 돈 때문에 당신 딸을 구한 게 아니오, 그것만은 알아주길 바라오.";
			link.l1.go = "Gladis_regard_1";
			link.l2 = "이 돈은 네가 가지렴, 글래디스. 나보다 네가 더 필요하잖아.";
			link.l2.go = "Gladis_regard_2";
			sld = characterFromId("Helena");
			LAi_SetStayType(sld);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			// открыть город
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
		break;
		
		case "Gladis_regard_1":
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "그대의 고귀한 행동에 조금이나마 보답할 수 있어 기쁩니다. 내 집의 문은 언제나 그대에게 열려 있소. 헬렌과 나는 언제든 그대를 뵙게 되어 기쁠 것이오.";
			link.l1 = "감사합니다, 맥아더 양. 기회가 되면 당신과 헬렌을 찾아뵙겠습니다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_regard_2":
			dialog.text = "아, 제발... 나는 그저 당신의 고귀한 행동에 보답하고 싶었을 뿐이오. 내 집의 문은 언제나 당신에게 열려 있다는 것을 알아두시오. 헬렌과 나는 언제든 당신을 반길 것이오.";
			link.l1 = "감사합니다, 맥아더 양. 기회가 되면 당신과 헬렌을 찾아뵙겠습니다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
			pchar.questTemp.Saga.Helena_friend = "true";//атрибут поведения Элен в будущем
		break;
		
		case "Gladis_wait":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys")) {
				dialog.text = "선장님, 우리 집에 언제든 환영입니다! 헬렌을 찾으러 오셨나요? 안타깝게도 헬렌이 자기 방에 틀어박혀 있어요. 지난 며칠 동안 너무 지쳐서 그런 것 같아요. 걱정하지 마세요, 가끔 저런 일이 있답니다.";
				link.l1 = "정말이야? 그녀가 정말 괜찮은 거 확실해?";
				link.l1.go = "after_drinking";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys");
				break;
			}
		
			dialog.text = "아, 드 모르 나리! 제 딸을 구해주신 은인을 저희 집에서 다시 뵙게 되어 언제나 기쁩니다. 엘렌을 만나고 싶으신가요? 위층 자기 방에 있습니다. '레인보우'를 잃고 극적으로 구조된 뒤로는 바깥출입을 꺼리고 있지요. 저도 저런 혼란스러운 모습의 아이는 처음 봅니다...\n";
			link.l1 = "감사합니다, 맥아더 양.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_history":
			dialog.text = "아, 드 모르 나리! 제 딸의 구원자를 저희 집에서 다시 뵙게 되어 항상 기쁩니다. 엘렌을 만나고 싶으신가요?";
			link.l1 = "아니오. 당신에게 몇 가지 질문을 하고 싶소. 솔직하게 대답해 주길 진심으로 바라오. 헬렌의 안전이 여기에 달려 있소. 이 반지, 본 적 있소?";
			link.l1.go = "Gladis_history_1";
		break;
		
		case "Gladis_history_1":
			RemoveItems(pchar, "bucher_ring", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "맙소사! 이건... 그녀 아버지의 반지야!";
			link.l1 = "맥아더 나리의 것인가?";
			link.l1.go = "Gladis_history_2";
		break;
		
		case "Gladis_history_2":
			dialog.text = "아니오. 엘렌은 우리 양딸이지만, 그 아이는 그 사실을 몰라요. 그녀의 부모가 세상을 떠나서 제가 제 자식처럼 데려왔지요. 션이 그녀를 입양했지만, 그조차도 엘렌이 제 딸이 아니라는 걸 몰랐어요.";
			link.l1 = "그럼 그녀의 진짜 부모는 누구지?";
			link.l1.go = "Gladis_history_3";
		break;
		
		case "Gladis_history_3":
			dialog.text = "그녀의 아버지는 '네프튠' 프리깃에서 '도살자'라 불리던 해적이었다는 걸 알아. 나는 그를 두 번밖에 본 적 없어. 그리고 그녀의 어머니는 아름다운 젊은 여자였지, 빨간 머리에 남자 옷을 입고 다녔어. 그녀에 대해 내가 말할 수 있는 건 그 정도야, 나쁜 어머니였다는 것 빼고는.\n나는 그런 아기를 남의 손에 맡기고 떠나지 않았을 거야. 두 사람 모두 비극적으로 죽었지. 그리고 약속된 심부름꾼이 스무 해가 지나 나타났고, 그게 바로 너였어. 도살자가 너를 보냈나? 그는 살아 있나?";
			link.l1 = "진정하세요, 글래디스 아가씨! 도살자가 돌아왔다는 의심을 할 이유는 없습니다. 하지만 이런 생각을 한 사람이 당신이 두 번째군요. 최근에 이 반지를 당신에게 보여주기로 한 남자를 만났습니다...";
			link.l1.go = "Gladis_history_4";
		break;
		
		case "Gladis_history_4":
			dialog.text = "...";
			link.l1 = "사소한 사건 때문에 제때 그렇게 하지 못했고, 평생 선장의 마지막 명령을 지키지 못한 죄책감에 시달렸지. 얼마 전에 세상을 떠났고... 뭐, 슬픈 이야기는 이쯤 하자꾸나. 글래디스, 헬렌 어머니께서 아이에게 남기신 유품 같은 게 있느냐? 작은 것이라도 말이야?";
			link.l1.go = "Gladis_history_5";
		break;
		
		case "Gladis_history_5":
			dialog.text = "그 여자는 내게 오래된 지도 조각 하나를 남겼어. 자기 유산이라며 농담하더군. 그 종이 쪼가리가 무슨 소용이 있겠어? 난 그냥 시시한 농담일 뿐이라고 생각했지. 그녀는 지나치게 흥분했고, 정신이 좀 나간 상태였어. 그래도 난 그 '선물'을 간직했지.\n누가 알겠어... 원한다면, 언젠가 내게 전부 이야기해 주겠다고 약속하면 그걸 줄 수도 있어.";
			link.l1 = "물론이죠, 맥아더 양. 이 놈은 잠시 내가 데려가겠소. 스벤손 나리와 얘기할 일이 있소.";
			link.l1.go = "Gladis_history_6";
		break;
		
		case "Gladis_history_6":
			GiveItem2Character(pchar, "map_half_beatriss"); //половинка карты
			PlaySound("interface\important_item.wav");
			dialog.text = "다시 한 번 도와주셨군요, 드 모르 나리! 어떻게 감사드려야 할지 모르겠습니다. 제발, 남편의 권총이라도 받아주세요. 남편은 항상 이 권총을 자랑스럽게 여겼고 아주 희귀한 것이라고 했어요. 오랫동안 여기 그냥 놓여 있었습니다. 이제 나리께 도움이 되길 바랍니다! 받아주세요, 제발, 받아주세요!";
			link.l1 = "고마워, 글래디스. 이 권총은 정말 훌륭하군. 고맙고, 잘 있어.";
			link.l1.go = "Gladis_history_7";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l2 = "이 권총은 엘렌이 쓰게 하시오. 내 무기는 충분하오.";
				link.l2.go = "Gladis_history_8_1";
			}
		break;
		
		case "Gladis_history_7":
			DialogExit();
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol5");
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			AddQuestRecord("Saga", "22");
			AddCharacterExpToSkill(pchar, "Leadership", 50);
		break;
		
		case "Gladis_history_8_1":
			dialog.text = "그런데 왜 자꾸 내 선물을 거절하는 거지? 나 속상하게 하잖아...";
			link.l1 = "이제 당신을 행복하게 해줄 수 있을 것 같소. 나는 원래 배달원이 선장 부처의 딸을 안전하게 보호한 대가로 당신에게 전달하려 했던 금화를 돌려주려 하오.\n물론 이 더블룬이 당신의 모든 사랑과 충성에 대한 보답이 될 수는 없겠지만, 이 금화는 당신이 마땅히 받아야 할 것이오. 원하는 대로 쓰시오.";
			link.l1.go = "Gladis_history_8";
		break;
		
		case "Gladis_history_8":
			dialog.text = "아, 선장님! 뭐라고 말씀드려야 할지 모르겠군요... 이런... 고결한 분들이 세상에 존재한다는 건 상상도 못 했소! 제 딸에게 가서 이 기쁜 소식을 전해 주십시오!";
			link.l1 = "가고 있습니다, 맥아더 양.";
			link.l1.go = "Gladis_history_9";
		break;
		
		case "Gladis_history_9":
			DialogExit();
			RemoveItems(pchar, "chest", 1);
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Saga", "22");
			sld = characterFromId("Helena");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterbyItem(sld, "pistol5");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
		break;
		
		case "Helena_hire":
			dialog.text = "진심이오? 무슨 뜻이오?";
			link.l1 = "스벤손 나리의 요청에 따라 나는 헬렌을 내 배의 장교로 임명할 생각이오. 헬렌은 지금 큰 위험에 처해 있소. 얀과 내가 이 문제를 처리하는 동안 헬렌에게는 확실한 보호가 필요하오. 내가 그 보호를 제공할 수 있기를 바라오.";
			link.l1.go = "Helena_hire_1";
		break;
		
		case "Helena_hire_1":
			dialog.text = "아, 정말 고맙소! 내가 직접 이런 부탁을 하기는 감히 어려웠을 것이오. 내 딸을 지키는 데 최고의 보호가 될 거요. 헬렌도 다시 항해하게 되어 무척 기뻐할 것이오!";
			link.l1 = "칭찬해 주셔서 감사합니다, 맥아더 양. 이제 당신의... 양녀를 만나봐야겠군요.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "Helena_hire";
			pchar.questTemp.Saga = "helena2";
		break;
		
		case "saw_sex":
			dialog.text = "오, 하느님! 내 딸아!";
			link.l1 = "글래디스, 노크도 못 하냐?!";
			link.l1.go = "saw_sex_1";
		break;
		
		case "saw_sex_1":
			dialog.text = "오, 용서하게, 젊은이들! 나는 이만 가겠네! 헬렌, 내가 한 말 기억하게!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysTalk");
		break;
		
		case "after_drinking":
			dialog.text = "이번에는 그냥 너무 무리한 것 같아요. 그녀가 전부 말해줬어요, 선장님! 어제 새 배를 고를 때 도와주셔서 감사합니다!";
			link.l1 = "어? 음, 천만에요. 안녕히 가세요, 맥아더 부인.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
