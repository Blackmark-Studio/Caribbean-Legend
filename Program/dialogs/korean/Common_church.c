// boal 25/04/04 общий диалог церковь
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Church\" + NPChar.City + "_Church.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    
    string iDay, iMonth, lastspeak_date, eggStr;
    string sTemp, sTitle;

	iDay           = environment.date.day;
	iMonth         = environment.date.month;
	lastspeak_date = iday + " " + iMonth;
	int iMoneyToCharacter;

	if (!CheckAttribute(npchar, "quest.HealthMonth"))
    {
        npchar.quest.HealthMonth = "";
    }
	
    if (!CheckAttribute(npchar, "quest.BadMeeting"))
    {	
        npchar.quest.BadMeeting = "";
    }
    if (!CheckAttribute(npchar, "quest.GhostShipMonth"))
    {
        npchar.quest.GhostShipMonth = "";
    }
    
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = "";
	}
	
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = "";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase(""+GetSexPhrase("아들아","딸아")+", 유감이지만 당신에게 피신처를 제공할 수 없어. 도망쳐!","도시 경비대가 너를 찾으려고 도시를 샅샅이 뒤지고 있어, "+GetSexPhrase("아들아","내 딸")+". 내 교회의 문은 언제나 고통받는 이들에게 열려 있지만, 당신에게는 피난처를 제공할 수 없소...",""+GetSexPhrase("아들아","딸아")+", 도망쳐야 해! 망설이지 말고, 제발 부탁이야!"),LinkRandPhrase("교회에서 뭐 하는 거냐, 길 잃은 영혼아? 당장 나가라! 병사들이 널 여기서 발견하면 학살이 벌어질 테니!","지금 당장 성전을 떠나라, 이 불경한 자야! 너 같은 악당을 내가 결코 보호하지 않을 것이다!","지금 당장 우리 주님의 성전을 떠나라! 여기엔 살인자가 필요 없다!"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("아이고, 좀 그러지 마요, 신부님...","어차피 네 도움이 필요하지도 않아..."),LinkRandPhrase("내 길을 막지만 마십시오, 신부님...","내가 갈게, 걱정하지 마...","신부님, 그만 좀 호들갑 떠세요 - 난 정말 이럴 시간 없어요"));
				link.l1.go = "fight";
				break;
			} 
            if (npchar.quest.BadMeeting != lastspeak_date)
			{
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_2.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && NPChar.location != "LosTeques_church" && rand(5) == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // 280313
				{
					dialog.text = "...그들은 영원히 불타는 지옥에서 고통받을 것이다! 결코 그들은...";
					link.l1 = RandPhraseSimple("에헴! 방해가 됐습니까, 신부님?","바로 그 말이야!");
					link.l1.go = "GenQuest_Church_2_Start_1";
					NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestTown") && PChar.GenQuest.ChurchQuest_2.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete"))
				{
					Dialog.Text = ""+GetSexPhrase("아들아","딸아")+", 다시 보게 되어 기쁘구나!";
					link.l1 = "건강한 모습으로 다시 뵈어 기쁩니다, 신부님 "+NPChar.name+"...";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1";
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.QuestTown") && PChar.GenQuest.ChurchQuest_1.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
				{
					Dialog.Text = ""+GetSexPhrase("아들아","딸아")+"! 다시 건강하고 기운 넘치는 모습으로 뵙게 되어 기쁩니다. 주님께서 우리의 일에 도움을 주신 게 틀림없지요?";
					link.l1 = "그래, "+RandPhraseSimple("신부","성부님")+", 바람이 항상 내 편은 아니었고, 더 많은 시간과 노력, 돈을 들였지만 - 당신의 임무는 완수되었습니다.";
					link.l1.go = "GenQuest_Church_1_Complete_1";
					break;
				}
				Dialog.Text = "우리의 신성한 거처에 오신 것을 환영합니다, "+GetSexPhrase("아들아","내 딸")+".";
				link.l1 = "안녕하세요, 신부님.";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
				{
					dialog.text = "안녕, Ellen, 내 아이야.";
					link.l1 = "신부님께도 평안이 있기를.";
				}
				link.l1.go = "node_3";
				Link.l2 = "넌 내 아버지가 아니야. 그리고 다시는 그런 식으로 나한테 말하지 마.";
				Link.l2.go = "node_2";
				NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}
			else
			{
				Dialog.Text = "주님의 성전을 떠나라, 불경한 자여! 우리 사이에 나눌 말은 없다!";
				Link.l1 = "나도 원하지 않았어.";
				Link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "node_2":
			dialog.text = "이런 불경한 자야! 썩 꺼져라! 감히 네 따위가 우리 주님의 성전을 더럽히려 들지 마라!";
			link.l1 = "나 여기 머물 생각도 없었어.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -0.25);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "node_3":
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
			{
				dialog.text = "자네가 얀과 어울려 다니는 와중에도 우리 주님과 그분의 집을 잊지 않아 기쁘네. 무엇을 도와주면 되겠나?";
			}
			else
			{
				dialog.text = "주님께서 당신과 당신의 일에 축복을 내리시길... 특별한 이유로 저를 찾아오셨습니까?";
			}
    		link.l1 = RandPhraseSimple("기부를 하고 싶습니다.","좋은 일에 기부하고 싶어.");
    		link.l1.go = "donation";
    		link.l2 = RandPhraseSimple("고해할 때가 된 것 같군.","고해하고 싶소, "+RandPhraseSimple("신부님.","성부님."));
    		link.l2.go = "ispoved";
    		link.l3 = RandPhraseSimple("너와 볼 일이 있다, "+RandPhraseSimple("신부님.","거룩하신 아버지."),"업무 때문에 왔소, "+RandPhraseSimple("신부님.","거룩하신 신부님."));
    		link.l3.go = "work";
			
			//--> Сага
			// Картахена, Чика Гонсалес
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && pchar.location == "Cartahena_church" && sti(pchar.money) >= 1000)
			{
				link.l4 = "한 숙녀의 영혼을 위한 기도 예배를 부탁드리고 싶습니다.";
				link.l4.go = "saga";				
			}
			// поиски исцеления от заклятий
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location != "Bridgetown_church" && !CheckAttribute(npchar, "quest.seektreatment"))
			{ // все церкви, кроме Бриджтауна
				link.l4 = "신부님, 도와주십시오. 저 정말 아픕니다. 사악한 이교도의 저주가 저에게 내렸어요. 제발, 부탁드리니 저를 도와주십시오!";
				link.l4.go = "seektreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location == "Bridgetown_church")
			{ // попал в Бриджтаун
				link.l4 = "신부님, 도움이 필요합니다. 저 정말 아픕니다. 어떤 사악한 이교도의 저주가 저에게 내렸어요. 제발, 도와주세요, 부탁드립니다!";
				link.l4.go = "findtreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessFindTreatment") && pchar.location == "Bridgetown_church")
			{ // пришёл в Бриджтаун по направлению
				link.l4 = "아버지, 도움이 필요해요. 저 정말 아파요. 어떤 사악한 이교도의 저주가 저를 덮쳤어요. 저를 도와주실 수 있는 분이 바로 아버지라고 들었어요. 제발 부탁드려요...";
				link.l4.go = "findtreatment";
			}
			// исцеление от заклятий Джесс
			if(CheckAttribute(pchar, "questTemp.Saga.JessTreatment") && pchar.location == "Bridgetown_church")
			{
				link.l4 = "아버지, 도움이 필요해요. 저 정말 아파요. 무슨 사악한 이교도의 저주가 저에게 내렸어요. 저를 이곳으로 보낸 사람은... 제시카 로즈예요. 당신이라면 저를 도와줄 수 있다고 그녀가 말했어요.";
				link.l4.go = "treatment";
			}
			if(CheckAttribute(npchar, "quest.candle"))
			{
				link.l4 = "촛불에 대해서 말인데...";
				link.l4.go = "candle";
			}
			if(CheckAttribute(npchar, "quest.prayer") && GetNpcQuestPastDayParam(npchar, "prayer_date") >= 1 && stf(environment.time) >= 22.0)
			{
				link.l4 = "기도할 준비가 되었습니다, 신부님.";
				link.l4.go = "prayer";
			}
			//<-- Сага
			
			// Warship, 30.05.11. Миниквест из дел чести "Divine justice".
			if(CheckAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest") && AffairOfHonor_GetCurQuest() == "GodJudgement" &&
				NPChar.city == PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId)
			{
				link.l5 = "끔찍한 일들이 벌어지고 있습니다, 신부님.";
				link.l5.go = "AffairOfHonor_GodJudgement_1";
			}
			
			link.l6 = "실례하지만, 이제 가봐야겠소.";
			link.l6.go = "exit";
		break;

		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "걱정하지 말아라, 아들아. 주님께서 네 고통을 보고 계시니 반드시 도와주실 것이다. 믿음을 굳건히 하려면 항상 십자가를 지니고 다녀라.";
			Link.l1 = "감사합니다, 신부님.";
			Link.l1.go = "exit";
			AddItems(PChar, "amulet_3", 15);
			DeleteAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest");
		break;

// Jason-------------------------------------------------Сага----------------------------------------------
		//--> Чика Гонсалес
		case "saga" :
			dialog.text = "1,000페소에 나리의 뜻을 겸손히 따르겠습니다.";
			Link.l1 = "여기 있습니다, 신부님 - 이 동전들을 받아 주십시오.";
			Link.l1.go = "saga_1";
		break;
		
		case "saga_1" :
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "고맙다, 아들아. 내가 기도할 그 세뇨라의 이름이 무엇이냐?";
			Link.l1 = "그녀의 이름은 치카 곤살레스이며, 그녀는 여러 해 전에 이 세상을 떠났어.";
			Link.l1.go = "saga_2";
		break;
		
		case "saga_2" :
			dialog.text = "이상하군... 알바레스에게 무슨 일이 있었나, 그리고 그가 이 일에 대해 자네에게 물었나?";
			Link.l1 = "그런데 이 알바레즈라는 자가 누구지, 그리고 내 부탁이 뭐가 그렇게 이상하단 말이오?";
			Link.l1.go = "saga_3";
		break;
		
		case "saga_3" :
			dialog.text = "오, 이런! 매달 우리 등대를 20년 동안 지켜온 알바레즈가 이 부인의 영혼의 평화를 위해 기도 예배를 주문하지. 그를 제외하면 아무도 곤살레스 부인을 신경 쓴 적이 없어. 그런데 이제 당신이 여기 왔군. 그래서 그런 생각을 했지. 하지만 내 일이 아니야. 물론, 떠도는 영혼이 평화와 천국으로 가는 길을 찾을 수 있도록 당신의 뜻을 겸손히 따르겠소.";
			Link.l1 = "감사합니다, 신부님.";
			Link.l1.go = "saga_4";
		break;
		
		case "saga_4" :
			DialogExit();
			if(CheckAttribute(pchar,"questTemp.Saga7"))
			{
				AddQuestRecord("Saga", "151");
				DeleteAttribute(pchar,"questTemp.Saga7");
			}
			else AddQuestRecord("Saga", "15");
			Saga_SetOrtega();
			pchar.questTemp.Saga = "ortega";
			pchar.quest.Saga_Gonsales1.over = "yes"; //снять возможное прерывание
			if (GetCharacterIndex("SagaGonsalesB") != -1)
			{
				sld = characterFromId("SagaGonsalesB");
				sld.lifeday = 0;
			}
		break;
		
		// belamour участвовал в событиях Картахены
		case "saga_5" :
			dialog.text = "다른 누군가의 영혼을 위해서도 진혼곡을 주문하고 싶은가?";
			Link.l1 = "음... 아니, 아닌 것 같은데. 다른 사람 것도 주문해야 하나?";
			Link.l1.go = "saga_6";
		break;
		
		case "saga_6" :
			dialog.text = "글쎄, 당신이나 당신의 무신앙 동료들이 이 불운한 도시를 약탈할 때 당신 손이나 칼에 쓰러진 수백 명의 무고한 사람들을 위해서라면?.. 하지만 겸손한 신부가 죄 없는 평범한 시민들을 아무런 양심의 가책도 없이 죽인 자의 양심에 닿기를 바라는 건 어리석은 일이겠지...";
			Link.l1 = "아버지, 이해하지 못하시는군요... 그건 다 지난 일이에요. 지금 여기서는 누구에게도 해를 끼칠 생각 없어요.";
			Link.l1.go = "saga_7";
		break;
		
		case "saga_7" :
			pchar.questTemp.saga7 = true;
			dialog.text = "네 말을 믿어도 되겠나...? 하지만, 어쨌든 여기는 피로 더럽혀져서는 안 될 성스러운 땅이네. 그러니 경비병을 부르진 않겠네. 평안히 가게. 어쩌면 신의 심판을 받기 전에, 적어도 몇 가지 죄는 속죄할 시간이 있을지도 모르지.";
			Link.l1 = "그럴지도. 신의 뜻이 이루어지길.";
			Link.l1.go = "saga_4";
		break;
		// <-- Чика Гонсалес
		
		// --> исцеление от заклятий
		case "treatment":
			dialog.text = "제시카? 기억나지. 불쌍한 죄인이지. 하지만 죽지 않았나?";
			link.l1 = "그녀는 세상을 떠났습니다, 신부님. 이제 그녀는 죽었으니, 주님께서 그녀의 영혼을 편히 쉬게 해주시길. 하지만 그녀는 분명히 신부님께서 저를 도와주실 수 있다고 했습니다.";
			link.l1.go = "treatment_1";
			DeleteAttribute(pchar, "questTemp.Saga.JessTreatment");
		break;
		
		case "treatment_1":
			dialog.text = "누가 너에게 이런 주문을 걸었느냐, 아들아? 솔직히 말해 보거라.";
			link.l1 = "그녀가... 그녀가 했어. 제시카.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "신이시여, 우리를 구하소서! 나도 그렇게 생각했지. 이교도의 의식에 빠지면 아무리 강한 영혼이라도 어둠의 나락에 떨어질 수 있어... 하지만... 그녀가 정말 죽은 건가? 아니면... 완전히 죽지는 않은 건가?";
			link.l1 = "아주 통찰력이 깊으시군요, 신부님. 이제 그녀는 정말로 죽었습니다.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			dialog.text = "이 불쌍한 죄인은 내게 여러 번 고해를 했소. 증오가 그녀를 완전히 안에서부터 파괴했지. 나는 그녀가 무슨 일을 꾸미는지 알고 있었소. 그녀를 막아보려 했고, 올바른 길로 이끌려고도 했지만, 내 모든 노력은 헛수고였소. 나는 그녀에게 그 사악한 행위가 불러올 끔찍한 위험과 참담한 결과에 대해 경고했었소...";
			link.l1 = "예, 신부님. 제가 본 것은 정말 끔찍했습니다. 하지만... 어떻게 하면 치유될 수 있습니까?";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "기도의 힘으로다, 아들아. 우리 성전에서 드리는 거룩한 정화의 기도의 힘으로다. 아주 오랜 시간 기도해야 할 것이네, 그리고 자네 자신만을 위해서가 아니라네. 그녀를 위해서도 기도해야 하네.";
			link.l1 = "제시카를 위해서?";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "그래. 너 자신과 그녀의 영혼을 위해서지. 밤 열 시까지 여기로 오너라, 아무도 방해하지 않게. 밤새도록 기도해야 할 거다. 두꺼운 밀랍초 스무 개를 가져와서 모두 켜고, 다 탈 때까지 기도하거라.";
			link.l1 = "그러면 내가 치료받을 수 있는 거야?";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "모든 것은 주님의 손에 달려 있습니다. 내가 기도하는 법을 가르쳐 드리고 성경도 남겨드리겠습니다. 거룩한 기도의 힘이 당신에게 내린 사악한 마법을 파괴하고, 불쌍한 제시카의 영혼도 정화해 줄 것입니다.";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "나는 밀랍 양초 스무 개를 가지고 있다네. 사원에 머물며 기도를 시작할 준비가 되어 있지.";
				link.l1.go = "treatment_9";
			}
			else
			{
				link.l1 = "아직 촛불 스무 개가 없어. 내가 구해올게!";
				link.l1.go = "treatment_7";
			}
		break;
		
		case "treatment_7":
			dialog.text = "알겠다, 아들아. 기다리고 있겠다. 시간 낭비하지 마라!";
			link.l1 = "곧 여기 도착할 거야...";
			link.l1.go = "treatment_8";
		break;
		
		case "treatment_8":
			DialogExit();
			npchar.quest.candle = "true";
		break;
		
		case "candle":
			dialog.text = "스무 개의 양초를 가져왔니, 내 아이?";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "네, 신부님. 저는 밀랍 양초 스무 개를 가지고 있습니다. 성전에 머물며 기도를 시작할 준비가 되어 있습니다.";
				link.l1.go = "treatment_9";
				DeleteAttribute(npchar, "quest.candle");
			}
			else
			{
				link.l1 = "아직 아니야 - 하지만 무슨 수를 써서라도 반드시 손에 넣을 거야.";
				link.l1.go = "exit";
			}
		break;
		
		case "treatment_9":
			dialog.text = "음, 아들아. 그것들을 내게 주고 내일 밤 열 시 이후에 다시 오너라. 내가 필요한 기도문을 가르쳐주고, 밤에는 교회에 머물게 해주마.";
			link.l1 = "감사합니다, 신부님. 내일 뵙겠습니다!";
			link.l1.go = "treatment_10";
		break;
		
		case "treatment_10":
			DialogExit();
			RemoveItems(pchar, "mineral3", 20);
			LAi_RemoveLoginTime(npchar);
			LAi_SetLoginTime(npchar, 6.0, 22.99);
			npchar.quest.prayer = "true";
			SaveCurrentNpcQuestDateParam(npchar, "prayer_date");
		break;
		
		case "prayer":
			dialog.text = "기도문을 준비해 두었네, 아들아. 네 스무 개의 촛불과 성서도 두고 갔지. 촛불을 켜고 기도를 시작하게. 쉬지 말고 기도하게나; 네 회복과 이 가엾은 죄인 제시카의 영혼을 위해 기도하게. 뭔가를 잊거나 이해하지 못해도 상관없네. 마음에서 우러나오는 기도를 드리게. 진심 어린 바람이야말로 우리 주님께 중요한 것이니라.";
			link.l1 = "감사합니다, 신부님. 알겠습니다.";
			link.l1.go = "prayer_1";
		break;
		
		case "prayer_1":
			dialog.text = "아침에 다시 오겠소. 당신을 위해서도 기도하겠소...";
			link.l1 = "감사합니다, 신부님.";
			link.l1.go = "prayer_2";
		break;
		
		case "prayer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_BarbadosTreatment", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "seektreatment":
			dialog.text = "어떤 이교도의 주술이 너를 괴롭히고 있느냐, 아들아?";
			link.l1 = "나는 그들이 뭐라고 불리는지 몰라. 나는 힘도 없고 몸도 둔해서 뛰어다니지도 못하고, 싸우는 것도 정말 힘들어.";
			link.l1.go = "seektreatment_1";
		break;
		
		case "seektreatment_1":
			if (sti(pchar.questTemp.Saga.JessSeekTreatment) == 3)
			{
				dialog.text = "그 자들에 대해 들어본 적이 있소... 그들은 이 붉은 피부의 이교도 마녀들에 의해 우리 세계로 끌려왔지. 브리지타운 교회의 주임 신부를 찾아가 보라고 권하겠소\n그분은 인디언 저주의 해로운 영향이 기독교인의 몸과 영혼에 미치는 것에 대해 수년간 연구하셨소.";
				link.l1 = "그리고 그가 나를 도와줄 수 있다고?!";
				link.l1.go = "seektreatment_4";
			}
			else
			{
				dialog.text = "나는 그들에 대해 들은 적이 있네... 그들은 이 붉은 피부의 이교도들의 사악한 마녀들에 의해 우리 세계로 불려왔지. 안타깝게도 내가 줄 수 있는 유일한 조언은 더 많이 기도하고, 아들아, 우리 주님의 자비에 희망을 거는 것뿐이네.";
				link.l1 = "하지만 정말로 방법이 없는 겁니까, 신부님?! 저는 이렇게... 평생을 살아야만 합니까?";
				link.l1.go = "seektreatment_2";
			}
		break;
		
		case "seektreatment_2":
			dialog.text = "절망하지 마라, 아들아. 주님께서 네 기도를 들으시고 도와주실 것이다. 하지만 내 생각에는 다른 성스러운 곳에서도 물어보는 것이 좋겠구나\n어쩌면 이교도의 저주를 푸는 방법을 아는 신부가 있을지도 모른다.";
			link.l1 = "감사합니다, 신부님! 저는 반드시 치유될 거예요 – 군도에 있는 모든 교회를 다 찾아가더라도요!";
			link.l1.go = "seektreatment_3";
		break;
		
		case "seektreatment_3":
			dialog.text = "가거라, 아들아, 주님께서 너를 지켜주시길.";
			link.l1 = "안녕히 계세요, 신부님.";
			link.l1.go = "exit";
			npchar.quest.seektreatment = "true";
			pchar.questTemp.Saga.JessSeekTreatment = sti(pchar.questTemp.Saga.JessSeekTreatment)+1;
		break;
		
		case "seektreatment_4":
			dialog.text = "오직 주님만이 너를 도울 수 있지 – 그리고 네 자신도, 아들아. 신부는 네가 무엇을 어떻게 해야 하는지 가르쳐줄 뿐이다. 그를 찾아가 보아라.";
			link.l1 = "감사합니다, 신부님! 저를 구해주셨군요! 저는 즉시 바베이도스로 항해하겠습니다!";
			link.l1.go = "seektreatment_5";
		break;
		
		case "seektreatment_5":
			dialog.text = "이제 가시오, 주님께서 그대를 지켜주시길.";
			link.l1 = "안녕히 계세요, 신부님.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment");
			pchar.questTemp.Saga.JessFindTreatment = "true";
		break;
		
		case "findtreatment":
			dialog.text = "어떤 이교도의 저주가 너에게 내렸느냐, 아들아? 내가 맞혀 보마. 달릴 수 없고, 군도는 너무 무겁고, 몸놀림이 느리고 둔하지?";
			link.l1 = "어떻게 아셨습니까, 신부님?";
			link.l1.go = "findtreatment_1";
		break;
		
		case "findtreatment_1":
			dialog.text = "네가 내게 다가오는 걸음걸이만 봐도 알 수 있었지, 아들아. 주님께서 우리의 죄 많은 영혼을 불쌍히 여기시길... 말해보거라, 아들아, 솔직하게 - 누가 네게 이런 마법을 걸었느냐?";
			link.l1 = "신부님, 이름이 필요하십니까?";
			link.l1.go = "findtreatment_2";
		break;
		
		case "findtreatment_2":
			dialog.text = "이름을 안다면 말해 보시오.";
			link.l1 = "그녀의 이름은... 제시카 로즈였어.";
			link.l1.go = "findtreatment_3";
		break;
		
		case "findtreatment_3":
			dialog.text = "신이시여, 우리를 구하소서! 이교도의 의식에 손을 대면 아무리 강한 영혼이라도 어둠의 심연에 빠질 수 있소... 그녀에게, 이 불쌍한 영혼에게 무슨 일이 있었던 것이오?";
			link.l1 = "그녀는 죽었습니다, 신부님.";
			link.l1.go = "findtreatment_4";
		break;
		
		case "findtreatment_4":
			dialog.text = "하지만... 그녀가 정말 죽은 건가? 아니면... 완전히는 아닌가?";
			link.l1 = "정말 통찰력이 대단하시군요, 신부님. 이제 그녀는 정말 죽었습니다.";
			link.l1.go = "treatment_3";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment"); // если было
			DeleteAttribute(pchar, "questTemp.Saga.JessFindTreatment"); // если было
		break;
		//<-- Сага
		
		// Church GenQuest_2 -->	
		case "GenQuest_Church_2_Start_1":
			dialog.text = "...그리고 주님의 자비를! 그들의 죄악 때문에 만천하의 어둠이 그 영혼들을 삼키게 하소서...";
			link.l1 = LinkRandPhrase("성부님","Padre","Father")+", 너무 열정적인 거 아니야? 있잖아, 그러다 쓰러질 수도 있어...";
			link.l1.go = "GenQuest_Church_2_Start_2";
			link.l2 = "음... 젠장. 그럼 잘 가라.";
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_2":
			dialog.text = "오, "+GetSexPhrase("아들아","내 딸")+", 끔찍한 신성모독이요, 가장 사악한 범죄가 방금 일어났소! 교회에서 도둑질을 하다니!!! 그건 마치 주님의 주머니에 손을 넣는 짓과 다름없소!";
			link.l1 = "아, 그렇군... 어떻게 된 일이야?";
			link.l1.go = "GenQuest_Church_2_Start_3";
			link.l2 = LinkRandPhrase("정말 슬프고 뭐 그렇긴 한데, 난 이제 정말 가봐야겠어...","애도합니다, 신부님, 하지만 저는 이만 가봐야겠군요...","너무 전능하신 분만 믿은 것 같군. 더 안전한 자물쇠를 썼어야지. 뭐, 난 이만 가봐야겠다...");
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_3":
			dialog.text = "밤의 어둠을 틈타 어떤 악당들이 본당에서 모은 모든 것을 훔쳐 갔소! 이 불경한 자들은 제물용 성배마저 가져갔소!";
			link.l1 = "오 템포라, 오 모레스... 하지만 아직 흔적이 남아 있을 때 뭔가 조치를 취하셨기를 바라오?";
			link.l1.go = "GenQuest_Church_2_Start_4";
		break;
			
		case "GenQuest_Church_2_Start_4":
			dialog.text = "물론이지! 나는 이 신성 모독의 도둑들을 파문했고, 이제 그들에게 저주를 내리고 있네!";
			link.l1 = "그것이 매우 효과적인 조치임에는 의심의 여지가 없소. \n하지만 나는 좀 더 실질적인 것을 말한 것이오. 예를 들어, 추격대를 조직하는 것 말이오.";
			link.l1.go = "GenQuest_Church_2_Start_5";
		break;
			
		case "GenQuest_Church_2_Start_5":
			dialog.text = "아, 악에 저항하지 않겠다는 서약에 묶인 한낱 신부가 무엇을 할 수 있겠소? 저 악당들은 분명 벌써 이곳에서 멀리 떠나, 강탈한 전리품으로 선술집에서 술을 마시거나 타락한 여자들과 방탕과 타락에 빠져 있겠지! 그곳에서 그들의 최후를 맞이하길 바랄 뿐이오!";
			link.l1 = RandPhraseSimple("나는 그런 최후가 교수형을 당하는 것보다 훨씬 매력적이라고 확신하오. 하지만 더 이상 방해하지 않겠소. 행운을 빌겠소.","뭐, 언젠가는 우리 모두 조상들 곁으로 가게 되겠지. 하지만 저놈들은 좀 더 빨리 끝장났으면 좋겠군. 아무튼, 난 이만 가봐야겠다. 행운을 빌지.");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("성부님","Padre","Father")+", 하지만 나는 어떤 서약에도 얽매이지 않았으니, 기꺼이 주님께서 심판의 때를 이루시도록 돕겠소.";
			link.l2.go = "GenQuest_Church_2_Start_5_1";
		break;
		
		case "GenQuest_Church_2_Start_5_1": //выше - выход из диалога без подтверждения - странно, однако
			dialog.text = "너를 위해 기도하겠다, 아들아! 이제 가서 저 사기꾼들에게 마땅한 대가를 안겨 주거라!";
			link.l1 = "의심 마십시오, 신부님";
			link.l1.go = "GenQuest_Church_2_Start_6";
		break;
			
		case "GenQuest_Church_2_Start_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_2.StartQuest = true;
			PChar.GenQuest.ChurchQuest_2.QuestTown = NPChar.City;	// Город, в котором спрашиваем
			PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_2.IslandId = locations[FindLocation(NPChar.location)].islandId; // На каком острове опрашиваем бандюков
			PChar.GenQuest.ChurchQuest_2.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_2.AskPeople = true;
			PChar.GenQuest.ChurchQuest_2.AskBarmen = true;
			PChar.GenQuest.ChurchQuest_2.AskAlcash = true;
			PChar.GenQuest.ChurchQuest_2.MoneyCount = (sti(pchar.rank)+8)*543+3210;
			PChar.GenQuest.ChurchQuest_2.MoneyToCharacter = makeint(sti(PChar.GenQuest.ChurchQuest_2.MoneyCount)/3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
		break;
			
		case "GenQuest_Church_2_Thief_2":
			dialog.text = "글쎄, 어쩌면 자비로운 창조주께서 어리석은 자식들에게 그들의 죄를 벌하시려고 역병과 기근을 내리시는 것일지도 모르지...";
				link.l1 = "자존심 때문이든, 아니면 탐욕 때문이든... 왜 얼굴이 창백해졌소, 신부님?";
				link.l1.go = "GenQuest_Church_2_Thief_3";
			break;
			
		case "GenQuest_Church_2_Thief_3":
			if(rand(1) == 0) // Священник искренне раскаивается...
			{
				dialog.text = "예수님, 주님이시여, 죄 많은 이 종을 불쌍히 여겨주소서... 혹시... 혹시 도둑들을 찾으셨습니까? 그들을 죽이셨나요?";
					link.l1 = "십계명을 떠올려 봅시다. 모든 선량한 그리스도인은 어릴 때부터 알고 있지요. 살인하지 말라, 도둑질하지 말라, 거짓 증언하지 말라. 신을 두려워하는 사람이 이 계명을 어길 수 있겠습니까—더구나 영적인 신부가...?!";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_1";
			}
			else
			{
				dialog.text = "여긴 공기가 정말 답답하군... 그래서, 도둑들을 찾았나? 놈들을 죽였나?";
					link.l1 = "십계명을 기억합시다. 모든 선량한 그리스도인은 어릴 적부터 알고 있지요. 살인하지 말라, 도둑질하지 말라, 거짓 증언하지 말라. 하나님을 두려워하는 자가 이 계명을 어길 수 있겠습니까? 하물며, 영적인 신부가 말입니까?..";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_1";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_1_1":
			dialog.text = ""+GetSexPhrase("아들아","딸아")+"... 신이시여, 용서하소서... 저런 돈, 저런 유혹... 인간은 약하오, 정말 약하오! 나는 견딜 수 없었소... 정신이 나갔었지... 밤낮으로 기도하고, 참회하며, 엄격하게 금식하고, 내 육신을 괴롭혔소... 자격 없는 내가, 내 탐욕에 이끌려 유혹했던 불쌍한 이들만이라도 살려 달라고 하늘에 간절히 빌었소...";
			link.l1 = LinkRandPhrase("Father","Padre","Father")+", 진정하게. 그들은 그 일에 대해 아무 말도 하지 않았어... 그리고 앞으로도 절대 말하지 않을 거야. 그런데, 그들이 자발적으로 내게 성찬잔을 돌려줬고, 내가 그것을 다시 당신께 가져왔네.";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_2":
			dialog.text = "주님, 감사합니다! 저의 하나님, 주께서 이 비천한 종, 더럽고 죄악에 빠진 타락한 죄인의 기도를 들어주셨나이다...";
			link.l1 = "누구나 실수할 수 있지... 하지만 당신의 참회가 진심으로 보이니, 이렇게 말하겠소: 당신은 훌륭한 사람이며 좋은 신부요. 법정에 선다면 좋은 일이 일어나지 않을 거요. 그리고 주님의 일을 계속할지 말지는 당신이 결정해야 하오 – 오직 그분만이 당신에게 말씀하시고 인도하실 수 있소...";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_3":
			if(rand(1) == 0) // Священник хочет всучить ГГ бабло
			{
				dialog.text = ""+GetSexPhrase("아들아","딸아")+"... 회개의 눈물과 감사의 마음으로, 이 잔을 당신에게서 받겠습니다. 당신 영혼의 순수함과 고귀함에 진심으로 감동받았습니다. 온 마음을 다해 축복을 내리며, 부디 이 작은 정표를 받아주시기를 간청합니다. "+FindRussianMoneyString(iMoneyToCharacter)+"... 이걸로 경비가 충분히 충당되길 바라오?";
				// ГГ не берёт деньги. Плюсанем репу
				link.l1 = "이건 불필요합니다, 신부님 "+NPChar.name+". 나는 그렇게 가난한 사람이 아니니, 이 돈은 당신 교구를 위해 잘 쓰는 게 좋겠소.";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				// ГГ берёт деньги
				link.l2 = "감사합니다, "+LinkRandPhrase("Father","신부","성부님")+", 그 정도면 충분해.";
				link.l2.go = "GenQuest_Church_2_Thief_4_1_5";
			}
			else
			{
				dialog.text = ""+GetSexPhrase("아들아","딸아")+"... 회개와 감사의 눈물로, 주님의 자비와 용서를 상징하는 이 성배를 당신에게서 받겠나이다. 당신 영혼의 순수함과 고귀함에 진심으로 감동받았습니다. 온 마음을 다해 축복하나이다!";
				link.l1 = "축복해 주셔서 감사합니다, "+LinkRandPhrase("신부님.","아버지.")+".";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				link.l1 = "축복이야 물론 필요하지. 하지만 내가 들인 막대한 비용을 생각하면, 좀 더 실질적인 지원이 있어도 나쁠 건 없겠지...";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_6";
			}
			ChurchGenQuest2_RemoveCup();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_2");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6":
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = "아이고, 아이야, 정말 미안하구나... 이 작은 보탬이 "+FindRussianMoneyString(iMoneyToCharacter)+" 네 비용을 충당하기에 충분하겠나?";
			link.l1 = "그래, "+LinkRandPhrase("신부님.","아버지.")+", 이제 됐으니, 고맙소.";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_6_1";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_3");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_1":
			dialog.text = "당신의 암시를 잘 이해하지 못하겠군, "+GetSexPhrase("아들아","내 딸")+", 무슨 소리를 하는 거야?!";
			link.l1 = "나는 탐욕이 한 인간을 얼마나 끔찍하게 만들 수 있는지에 대해 이야기하고 있소, 그리고 내가 당신 교회를 털었다는 소문이 도는 거렁뱅이들에게서 그런 이야기를 들었지... 혹시 하고 싶은 말이라도 있소?";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_2":
			dialog.text = "내가 말해주마, 아이야. 지금 성직자와 이야기하고 있으니 조금 더 예의를 갖추는 게 좋을 거다. 그렇지 않으면 후회하게 될지도 몰라. 이 성배에 관해서라면, 나는 처음 보는 것이지만, 만약 본당에 기증할 생각이 있다면...";
			link.l1 = "진정하시지, 신부님. 설명하기 전엔 못 받아.";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_3":
			if(rand(1) == 0) // Просто несколько разные варианты диалога
			{
				dialog.text = "설명할 게 뭐가 있어?! 이제 봐 - 너는 "+GetSexPhrase("영리한 남자","영리한 아가씨")+", 그리고 분명히 이해하셔야 합니다. 저 불한당들이 무슨 말을 했든, 즉 제가 그들을 고용했다는 둥 떠든 것은 새빨간 거짓말입니다! 주님께서 이 불경한 자들을 신성모독뿐 아니라 거짓 증언을 한 죄까지도 벌하실 것입니다!";
				link.l1 = "주님은 내버려 두시오! 그 불쌍한 영혼들이 나한테 무슨 말을 했는지, 자네가 나를 맞서게 만든 그 사람들이 뭘 얘기했는지 자네가 어떻게 알겠소? 어쩌면 내가 자네에 대해 나쁜 말을 할 틈도 없이 그들을 죽였을지도 모르지 않소?";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1";
			}
			else
			{
				dialog.text = "나 너랑 더 이상 얘기할 게 없어! 너는 우리 주님 앞에서 네 의무를 다하지도 않았고, 성전에서 욕설이나 하고, 신부를 협박하려 들고, 교회 성물을 내보이고 있잖아. 그걸 어떻게 손에 넣었는지도 아직 밝혀지지 않았지! 내가 지금 시종들을 불러 너를 현행범으로 잡게 하지 않는 걸 신께 감사해라!";
				link.l1 = "흠... 이제는 인간의 심판도 두려워하지 않을 만큼 죄에 깊이 빠졌군. 하지만 신의 정의는 여전히 남아 있고, 우리 모두는 언젠가 반드시 그 앞에 서게 될 것이오. '성물'을 가져가시오, 신부님. 과연 그것을 만질 자격이 있는지 곰곰이 생각해 보시오. "+NPChar.name+".";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_2_1";
				link.l2 = "제 의심을 용서해 주십시오, 신부님. 인간의 마음은 약하고, 영혼은 혼란스럽습니다. 성배를 받아 주시고 축복을 내려 주십시오.";
				link.l2.go = "GenQuest_Church_2_Thief_4_2_4_2_2";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1":
			dialog.text = "으음... "+GetSexPhrase("아들아... 나리... 선생님...","내 딸아... 아가씨... 숙녀여...")+" "+PChar.name+"... 저는 당신 앞에 머리를 숙일 준비가 되어 있습니다... 그리고 우리의 의견 차이에 대해, 그러니까... 이 소박한 금액으로 당신의 손해를 보상해 드리겠습니다 "+FindRussianMoneyString(iMoneyToCharacter)+"... 물론, 이 일에 다른 사람들을 끌어들이지 않을 생각이라면...";
			// При этом варианте репу плюсуем
			link.l1 = "나는 아무도 끌어들이지 않을 거야. 성배를 가져가! 그리고 네가 신도들 주머니에서 몰래 훔친 금을 내가 받을 거라고는 꿈도 꾸지 마!";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1_1";
			// При этом - минусуем
			link.l2 = "나는 아무도 끌어들이지 않을 거야. 성배를 가져가! 내가 이 금을 받는 건 너한테 시간과 돈을 많이 썼기 때문이야.";
			link.l2.go = "GenQuest_Church_2_Thief_4_2_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex2", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoneyToCharacter));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1":
			// ничего не принесли священнику.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Without_All"))
			{
				link.l1 = "끔찍한 소식이오, "+LinkRandPhrase("Father","Padre","Father")+": 도둑들이 너무 교활하고 수완이 좋아서, 교회 금을 되찾는 데 실패했소...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_1";
				break;
			}
			// Принесли священнику только чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Only_With_Cup"))
			{
				link.l1 = "끔찍한 소식이오, "+LinkRandPhrase("Father","Padre","Father")+": 도둑들을 따라잡는 데는 성공했지만, 내 유일한 전리품은 이 성배뿐이었소.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Принесли священнику и деньги и чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.With_All"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "분명히 이 소식이 마음에 들 거요 - 내가 도둑들을 제대로 벌주고, 그들에게서 교구의 돈과 이 성배까지 되찾았소.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = LinkRandPhrase("Father","Padre","Father")+", 나쁜 소식을 가져왔소... 그 악당들을 쫓는 데 시간과 노력, 자원을 많이 들였지만, 결국 찾아냈을 때는 이 성배만 빼고 전부 마시고 탕진해 버렸더이다...";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Священник - вор.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.PriestIsThief"))
			{
				dialog.text = "오, "+GetSexPhrase("아들아","내 딸")+", 나에게 무슨 일이 일어날 수 있겠소? 위험과 불안으로 가득한 것은 바로 그대의 길이지, 내 평화로운 수도실은 명상과 기도의 공간이며, 인간의 격정이 소용돌이치는 바다 속의 조용한 섬이오...";
					link.l1 = "그리고 아무것도 그대의 평온한 고독을 방해할 수 없다는 말인가?";
					link.l1.go = "GenQuest_Church_2_Thief_2";
				break;
			}
			// Короткий вариант прохождения квеста.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Short_With_Mon"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "그 소식이 당신을 기쁘게 할 거라 확신합니다 - 제가 도둑들을 벌하고 본당의 돈을 되찾아왔습니다.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = LinkRandPhrase("Father","Padre","Father")+"... 유감스럽게도 실망시켜 드려야겠군요. 저는 도적들을 쫓아 군도 전체를 헤매며 수많은 위험과 장애물을 극복했고, 거의 몸을 망칠 뻔도 했지만 결국 그들을 따라잡았습니다. 하지만 안타깝게도... 그놈들은 이미 교회의 돈을 다 탕진해 버렸더군요.";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1": // ГГ решил заныкать деньги...
			if(rand(1) == 0)	// Священник верит ГГ но не даёт денег...
			{
				if(rand(4) == 3) // Более "мягкий" исход событий.
				{
					dialog.text = "오, "+GetSexPhrase("아들아","내 딸")+". 그대의 말에 나는 깊은 슬픔에 잠겼소 - 하지만 절망하지는 않겠소, 절망은 치명적인 죄이니! 주님께서 우리의 믿음을 굳건히 하시려고 또 다른 시련을 내리신 것이오.";
						link.l1 = "아멘, 신부님...";
						link.l1.go = "exit";
						sQuestTitle = NPChar.City + "ChurchGenQuest2";
						AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_9");
						AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
						CloseQuestHeader(sQuestTitle);
						ChangeCharacterComplexReputation(PChar,"nobility", -2);
						DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
						NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
				}
				else
				{
					dialog.text = ""+GetSexPhrase("아들아","딸아")+", 네 영적 목자에게 거짓말하지 마라.";
						link.l1 = "정말 죄송합니다, 신부님. 하지만 맹세코 진실을 말씀드리는 것입니다.";
						link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3";
				}
			}
			else
			{
				// Священник даёт деньги ГГ...
				iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
				dialog.text = "오, "+GetSexPhrase("아들아","내 딸")+". 그대의 말에 나는 깊은 슬픔에 잠겼소 - 하지만 절망하지는 않겠소, 절망은 큰 죄이니! 주님께서 우리의 믿음을 굳건히 하시려 또 다른 시련을 내리신 것이오. 그러나 그대의 수고와 비용은 헛되었더라도 보상받아야 하오. 부디, 이 소박한 금액을 받아주시오 - "+FindRussianMoneyString(iMoneyToCharacter)+" - 그리고 당신의 올바른 길을 계속 가십시오!";
					link.l1 = "흠!... 고맙소, 신부님. 이 돈은 선한 일에 쓰겠소.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_1";
					link.l2 = LinkRandPhrase("Father","Padre","Father")+"... 내가 하지도 않은 일에 대한 보상은 받을 수 없어. 이 돈은 제단을 복구하는 데 쓰는 게 좋겠어.";
					link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1_2";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3":
			if(rand(6) == 3)
			{
				dialog.text = "좋아, 믿을게, "+GetSexPhrase("아들아","내 딸")+". 주님께서 우리의 믿음을 굳건히 하시려고 또 다른 시련을 내리셨소.";
				link.l1 = "아멘...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_1"
				break;
			}
				dialog.text = "비열하군! 네가 정말 우리 주님을 속일 수 있다고 생각했느냐?! 저주받을 자여"+GetSexPhrase(", 이 악당아",", 계집")+"! 나가라, 그리고 이 돈이 너에게 아무런 이득도 가져다주지 않을 거라는 걸 명심해라!";
				link.l1 = "그게 무슨 말씀이십니까?! 신부님!..";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_2";
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			ChangeCharacterComplexReputation(PChar,"nobility", -3);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			ChangeCharacterComplexReputation(PChar, "nobility", -6);
			AddCharacterExpToSkill(PChar, "Leadership", -50);
			AddCharacterExpToSkill(PChar, "Fortune", -70);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			npchar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1":
			if(rand(1) == 0) // Поверил.
			{
				dialog.text = "오, "+GetSexPhrase("아들아","내 딸")+". 그대의 말에 나는 깊은 슬픔에 잠겼소 - 그러나 절망하지는 않소, 절망은 치명적인 죄이니! 주님께서 우리의 믿음을 굳건히 하시려 또 다른 시련을 내리신 것이오.";
				link.l1 = "아멘, 신부님...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2"; // Переход сюда, т.к. одно и тоже.
			}
			else
			{
				dialog.text = "그래, 바로 그 돈과 함께 도둑맞은 성배야... 하지만... 그걸 가지고 있다면, 왜 돈은 아직 안 가져왔지? 꽤 큰 금액이었는데, 그 놈들이 그렇게 빨리 다 써버릴 수는 없었을 텐데... "+GetSexPhrase("아들아","딸아")+", 영적 목자에게 거짓말하고 하나님의 성전에서 거짓 증언을 하는 것보다 더 큰 죄는 없다는 것을 기억하시오!";
				link.l1 = "성부님 "+NPChar.name+", 이 항아리를 구하려다 목숨을 잃을 뻔했소, 당신을 기쁘게 해주고 싶어서였지. 이 모든 것에 얼마를 썼는지는 말도 안 하겠소!";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2";
			}
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2":
			dialog.text = "나가서 전능하신 분께 감사해라. 내게 온유한 마음을 주신 덕분이지. 그렇지 않았다면 넌 이미 도둑이자 악당으로 낙인찍혔을 거다!";
			link.l1 = "그게 무슨 소리야?! "+LinkRandPhrase("성부님","Padre","Father")+"!..";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2_1";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -5);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_12");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, iMoneyToCharacter);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -1);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_11");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_1":
			dialog.text = "오, "+GetSexPhrase("아들아","내 딸")+". 그대의 말에 나는 깊은 슬픔에 잠겼소 - 하지만 절망하지는 않겠소, 절망은 치명적인 죄이니! 주님께서 우리의 믿음을 더욱 굳건히 하시려 또 다른 시련을 내리신 것이오.";
			link.l1 = "아멘, 신부님...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_8");
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_1":
			dialog.text = "주님, 감사합니다! 정말로, 너는 그분의 도구였구나, 내 아이야! 나는 우리 하늘 아버지께서 너에게 길을 보여주시고 필요한 모든 도움을 주실 거라 믿고 있었단다. 나는 쉬지 않고 기도했었고, 그리고...";
			link.l1 = "알다시피, 신부님, 이런 일에는 기도보다는 무기가 훨씬 더 쓸모 있지요. 하지만, 분명히 당신의 기도가 들린 모양입니다.";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_2":
			dialog.text = ""+GetSexPhrase("아들아","딸아")+", 제대로 보상해 주고 싶어, 너"+GetSexPhrase(", 진정한 모교회의 기사처럼,","")+" 내 힘이 닿는 데까지 모든 것을 했지...";
			link.l1 = "신부님, 제 보잘것없는 업적을 너무 과장하시는군요. 이제 신부님께서 우리 주님을 찬양하실 수 있도록 자리를 비키겠습니다...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_3";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_2.MoneyCount));
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
		// <-- квесты церкви

		case "donation":
			dialog.Text = "물론이지, "+GetSexPhrase("아들아","내 딸")+". 성스러운 교회에 얼마나 헌금하시겠습니까?";
			Link.l1 = "죄송합니다, 신부님, 하지만 마음이 바뀌었습니다.";
			Link.l1.go = "No donation";
			if(makeint(PChar.money)>=100)
			{
				Link.l2 = "내 기부는 소박할 거요 - 겨우 100페소뿐이오.";
				Link.l2.go = "donation paid_100";
			}
			if(makeint(PChar.money)>=1000)
			{
				Link.l3 = "1000페소. 이 정도면 충분할 거라 생각해.";
				Link.l3.go = "donation paid_1000";
			}
			if(makeint(PChar.money)>=5000)
			{
				Link.l4 = "나는 돈복이 있으니 5,000페소를 기부하겠소.";
				Link.l4.go = "donation paid_5000";
			}
			//-->> квест пожертвования хозяйки борделя
			if(pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
			{
				Link.l5 = "신부님, 이번에는 제 이름이 아니라 다른 사람의 부탁으로 헌금을 드리고 싶습니다.";
				Link.l5.go = "HostessChurch";
			}
			//<<-- квест пожертвования хозяйки борделя
		break;

		case "No donation":
			dialog.Text = "흠... 뭐, 이건 네 결정이니 마음이 바뀌어도 괜찮다. 그리고 심판의 날에 이것이 모두 기록된다는 걸 잊지 마라.";
			Link.l1 = "다른 많은 일들도 그렇게 될 거야. 화제를 바꾸자.";
			Link.l1.go = "node_3";
			Link.l2 = "죄송합니다, 신부님, 이제 떠나야 할 시간입니다.";
			Link.l2.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = "성스러운 교회를 대표하여 감사드립니다, "+GetSexPhrase("아들아","내 딸")+", 선물에 대해.";
			Link.l1 = "신부님, 드릴 말씀이 있습니다.";
			Link.l1.go = "node_3";
			Link.l2 = "죄송합니다, 신부님, 이제 떠날 시간입니다.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = "성스러운 교회를 대표하여 감사드립니다.";
            Link.l1 = "신부님, 드릴 말씀이 있습니다.";
			Link.l1.go = "node_3";
			Link.l2 = "죄송합니다, 신부님, 이제 떠나야 할 시간입니다.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = "성스러운 교회를 대표하여, 당신의 선물에 감사드립니다.";
            Link.l1 = "신부님, 드릴 말씀이 있습니다.";
			Link.l1.go = "node_3";
			Link.l2 = "죄송합니다, 신부님, 이제 떠나야 할 시간입니다.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "ispoved":
			dialog.text = "물론이지, "+GetSexPhrase("아들아","내 딸")+", 듣고 있소.";
			link.l1 = "생각이 바뀌었어. 다음에 하자.";
			link.l1.go = "exit";
			link.l2 = "저는 죄가 너무 많습니다, 신부님. 제 모든 악행을 다 나열하려면 하루도 부족할 것입니다...";
			link.l2.go = "ispoved_1";
		break;

		case "ispoved_1":
			dialog.text = "우리 모두는 죄인이란다, 내 아이야...";
			link.l1 = "그래, 하지만 내 양심에 수천 명의 죽음이 짓누르는구나. 나는 배를 약탈하고 침몰시켰지...";
			link.l1.go = "ispoved_2";
		break;

		case "ispoved_2":
			dialog.text = "그 깃발 아래 항해한 자들 중에는 아무도 없었기를 바라오 "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "아니요, 당연히 아닙니다, 신부님.";
			link.l1.go = "ispoved_3";
			link.l2 = "별의별 사람들이 다 있습니다, 신부님...";
			link.l2.go = "ispoved_4";
		break;

		case "ispoved_3":
			dialog.text = "그러면 주님께서 그 죄들을 용서해 주실 것이오. 이 시대는 잔혹하니, 주군의 적들을 무찌름으로써 충성스러운 백성들의 생명을 구하는 셈이오.";
			link.l1 = "감사합니다, 신부님, 큰 위로가 되었습니다... 이제 가보겠습니다.";
			link.l1.go = "exit";
		break;

		case "ispoved_4":
			dialog.text = "주님께서 이런 죄를 용서하지 않으실 것이오! 기도하고 회개하시오, 회개하고 기도하시오! 이제 그대에게 남은 길은 하나뿐이오 – 수도원으로 가는 것뿐이오!";
			link.l1 = "수도원 생활은 미뤄야겠군. 적어도 이번 생에는 말이야. 잘 가라...";
			link.l1.go = "exit";
			npchar.quest.BadMeeting = lastspeak_date;
		break;

        case "work":
        	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner") && NPChar.location == PChar.GenQuest.ChurchQuest_1.ToColony + "_church")
        	{
        		dialog.text = "미안하오, "+GetSexPhrase("아들아","내 딸아")+", 하지만 지금은 모든 고해소가 사용 중입니다. 아무리 빨라도 30분 후에야 당신의 고해성사를 들을 수 있습니다.";
				link.l1 = "실례합니다, "+RandPhraseSimple("신부","Father")+", 이건 다른 문제요. 신부님 "+PChar.GenQuest.ChurchQuest_1.PriestName+", 출신, "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+", 한때 당신에게 신학 도서관의 귀중한 보물을 맡겼던 분입니다. 그분이 저더러 그것들을 돌려달라고 하셨습니다.";
				link.l1.go = "GenQuest_Church_1_Dialog_1";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner");
				break;
        	}
			dialog.text = "무슨 일로 여기 오셨소, "+GetSexPhrase("아들아","내 딸")+"?";
			link.l1 = "신부님, 한 가지 묻고 싶은 게 있습니다...";
			link.l1.go = "quests"; // ссылка к НПС
            link.l2 = RandPhraseSimple("나는 "+XI_ConvertString("ChurchGen")+"의 이익을 위해 일하는 것에 대해 이야기하고 싶었소 "+NationNameGenitive(sti(NPChar.nation))+".","본당 사정은 어떻습니까? 도움이 필요하신가요?");
			link.l2.go = "prihod";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
	            link.l3 = RandPhraseSimple("Padre","Father")+", 재정 문제에 대해 당신과 이야기하고 싶소."; //(пересылка в кредиты)
	            link.l3.go = "LoanForAll";
            }
			// -->
            if (stf(pchar.Health.HP) < 60.0)
            {
                link.l4 = "치료가 필요해.";
                link.l4.go = "healthAdd_1";
            }
            
			//квест мэра - на связь с нашим шпионом
			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
			{
	            link.l7 = RandPhraseSimple("Padre","성부님")+", 나는 어떤 남자의 부탁을 받고 여기 왔소. 그의 이름은 총독이오 "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".";
	            link.l7.go = "IntelligenceForAll";
            }
			//--> Jason Церковная депеша
			if (CheckAttribute(pchar, "GenQuest.Monkletter") && npchar.city == pchar.GenQuest.Monkletter.City)
			{
	            link.l10 = "신부님, 제가" +XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity)+".";
	            link.l10.go = "Monkletter";
            }
			//<-- Церковная депеша
			//--> Jason Доставка молитвенников
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "go" && sti(npchar.nation) == sti(pchar.GenQuest.Churchbooks.Nation) && npchar.city != pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "신부님, 저는 식민지에서 왔습니다 "+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity)+". 이 지역 교회에 기도서가 더 필요하다고 하더군요, 그리고 이곳 수도사가 이 일로 당신을 찾아가 보라고 했습니다.";
	            link.l11.go = "Churchbooks";
            }
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "return" && npchar.city == pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "신부님, 신도들을 위한 기도서를 가져왔습니다.";
	            link.l11.go = "Churchbooks_2";
            }
			//<-- Доставка молитвенников
			link.l99 = "생각이 바뀌었어, 할 일이 많거든.";
			link.l99.go = "exit";
		break;

		case "prihod":
			if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && rand(5) == 1)
		    {
		        dialog.text = "좋군. 그래도 이런 암울한 시대에, "+GetSexPhrase("아들아","내 딸")+", 성전을 찾는 모든 이가 우리 성모 교회에 도움이 되는 것은 아니오.";
				link.l1 = LinkRandPhrase("Father","Padre","Father")+", 나는 진정한 그리스도인이며, 우리 성모 교회를 섬기려는 나의 의도는 매우 진실하다."+GetSexPhrase(" 누가 그녀를 지지하겠소, 나 같은 충직한 기사 아니면?","")+"";
				link.l1.go = "GenQuest_Church_1_Start_1";
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
		    }
			else
			{
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}	
            dialog.text = "아직까지 본당은 조용합니다, "+GetSexPhrase("아들아","내 딸")+". 제안해 주셔서 감사합니다.";
    		link.l2 = "음, 별일 없으면 내 일이나 보러 가야겠군.";
    		link.l2.go = "exit";
			DeleteAttribute(npchar, "quest.add");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
		break;
		
		// Church GenQuest_1 -->
		case "GenQuest_Church_1_Start_1":
			dialog.text = "음, 나는 섬세한 임무를 맡았소. 이 일에는 순수한 의도뿐만 아니라 큰 용기와 상당한 신중함도 필요하오...";
			link.l1 = LinkRandPhrase("Father","Padre","Father")+", 당신께 어떤 일이든 기꺼이 해드리겠습니다. 설령 그 일로 지옥으로 곧장 들어가야 한다 해도 말입니다! 신께서 제 불경한 말을 용서해 주시길 바랍니다.";
			link.l1.go = "GenQuest_Church_1_Start_2";
		break;
			
		case "GenQuest_Church_1_Start_2":
			PChar.GenQuest.ChurchQuest_1.QuestTown = NPChar.City;
			Church_GenQuest1_InitStartParam(NPChar);
			dialog.text = "오! 좋아... 하지만, 다시 말하지만, 이건 아주 민감한 문제야... 얼마 전에, 신부님께서 "+PChar.GenQuest.ChurchQuest_1.ToName+" 에서 온 "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Gen")+" 켜짐 "+XI_ConvertString(PChar.GenQuest.ChurchQuest_1.ToIsland+"Voc")+"잠시 동안 교회 도서관에서 신학 서적과 고문서를 몇 권 빌려주었습니다. 대주교께서 아름다운 지식의 빛이 퍼지는 것을 막지 말라는 간곡한 요청을 하셨기에 거절할 수 없었지요. 바다 항해의 고난 때문에 그가 제때에 원고를 돌려주지 못할 거라는 걸 알면서도 말입니다... 이 문제를 해결하는 데 도와주실 수 있겠습니까?";
			link.l1 = "두렵소, "+LinkRandPhrase("Father","신부","거룩하신 신부님")+", 그건 당신을 위해 해줄 수 없소. 이 일은 매우 민감한 사안이라 진정한 외교관만이 해결할 수 있소.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Father","Padre","Father")+", 네 임무는 내게 그리 복잡해 보이지 않아. 바로 그리로 가겠다.";
			link.l2.go = "GenQuest_Church_1_Start_3";
		break;
			
		case "GenQuest_Church_1_Start_3":	// Квест взят
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.StartQuest = true;
			PChar.GenQuest.ChurchQuest_1.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_1.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_1.AskOwner = true;
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sOwnerCity", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"));
		break;
			
		case "GenQuest_Church_1_Dialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2A_Scene"))	// Сцена 2а
			{
				dialog.text = "오! 그래... 맞아, 이제 기억났어... 하지만, "+GetSexPhrase("아들아","내 딸")+", 이 보물들은 물질적인 것보다 영적인 가치가 더 큽니다! 이미 제 신도들에게 큰 도움이 되었고, 앞으로도 그럴 수 있을 것입니다!";
				link.l1 = "하지만, "+LinkRandPhrase("Father","Padre","Father")+", 신부의 신도들 "+PChar.GenQuest.ChurchQuest_1.PriestName+" 구원도 필요하며, 이러한 행위 없이는 신학의 기둥들의 지지를 받지 못할 것이고, 그의 설교에는 영감이 부족할 것입니다.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_1";
			}
			else	// Сцена 2б-а и 2б-б
			{
				dialog.text = "아, 그래!.. 정말이야... "+GetSexPhrase("아들아","딸아")+", 이 보물들은 물질적인 것보다 영적인 가치가 더 큽니다! 이미 제 신도들에게 큰 도움이 되었기에, 부끄럽게도 정당한 주인에게 돌려주는 것을 '깜빡'하고 말았지요...";
				link.l1 = "정말이지, "+RandPhraseSimple("Father","Padre","Father")+", 그렇소. 그래서 신부님이 "+PChar.GenQuest.ChurchQuest_1.PriestName+" 이 책들을 직접 그에게 전해 달라고 부탁했소.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_1": // Сцена 2а
			dialog.text = "알겠구나, 내 아이야. 하지만 우리가 매일 주님께 기도하지 않느냐? '우리가 우리에게 죄 지은 자를 용서하듯이 우리 죄를 용서하소서'라고 말이다. 그리고 교회는\n "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" 내 소박한 교구보다 더 부유하군.";
			link.l1 = "신부님 말씀도 옳으시지만, 방금 성경의 다른 구절이 떠올랐습니다. '쉬운 길을 찾지 말라, 그 길에 악마가 우리를 기다리고 있으니, 그의 목소리는 더욱 교묘하고 유혹은 길이 쉬울수록 더욱 강해진다!' 그리고 신부님 "+PChar.GenQuest.ChurchQuest_1.PriestName+" 당신의 건망증에 대해 대주교께 편지를 보내려던 참이었소 - 내가 가까스로 그만두게 했소.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_1":
			dialog.text = "대, 대, 대주교님께요?! 이런 사소한 일로!.. 왜죠? 정말입니까? 어차피 이 작품들은 그리스도 안에서 사랑하는 형제에게 보낼 생각이었어요 - 다만 그에게 전해줄 마땅한 기회가 없었을 뿐입니다. 그런데 당신에게서,  "+GetSexPhrase("아들아","내 딸")+", 나는 진정으로 주님의 충실한 종을 보는구나. 여기 있다 - 이 책들과 필사본을 받아서 꼭 신부님께 전해 주게 "+PChar.GenQuest.ChurchQuest_1.PriestName+" 무사히 돌아왔군. 그리고 이에 진심으로 감사의 뜻을 더하오.";
			link.l1 = "물론이지, "+LinkRandPhrase("Father","Padre","Father")+"... 물론이지...";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.Complete.Short = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			// Предмет "рукопись" -->
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			// <-- Предмет "рукопись"
		break;
			
		case "GenQuest_Church_1_Dialog_1_2":	// Сцена 2б-а и 2б-б
			// Генерим кэпа -->
			sld = GetCharacter(NPC_GenerateCharacter("ChurchGenQuest1_Cap", "mercen_" + (rand(14)+14), "man", "man", 15, NPChar.nation, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 40, 35, "blade_13", "pistol3", "grapeshot", 30);
			FantomMakeCoolSailor(sld, 7 + rand(2), "", CANNON_TYPE_CANNON_LBS16, 75, 70, 65);
			sld.Abordage.Enable = false;
			sld.ShipEnemyDisable  = true; // флаг не обижаться на выстрелы
			LAi_SetImmortal(sld, true);
			sld.Dialog.FileName = "GenQuests_Dialog.c";
			sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			Group_FindOrCreateGroup("ChurchGenQuest1_CapGroup");
			Group_AddCharacter("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetType("ChurchGenQuest1_CapGroup", "trade");
			Group_SetGroupCommander("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetTaskNone("ChurchGenQuest1_CapGroup");
			Group_LockTask("ChurchGenQuest1_CapGroup");
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = "";
			PChar.GenQuest.ChurchQuest_1.CapFullName = GetFullname(sld);
			PChar.GenQuest.ChurchQuest_1.CapShipName = sld.Ship.Name;
			PChar.GenQuest.ChurchQuest_1.NoCapColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			// <-- Генерим кэпа
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2BA_Scene")) // Сцена 2б-а
			{
				dialog.text = "하지만, "+GetSexPhrase("아들아","내 딸")+"... 있잖아, 지난주에 내가 '라는 배의 선장을 만났거든\n"+sld.Ship.Name+"', 죽어가는 선원에게 성찬식을 집전하러 불려갔습니다. 대단히 기쁘게도, 선장님 "+GetFullName(sld)+" 나에게 그가 ~에 갈 거라고 말했다 "+XI_ConvertString("Colony"+GetColonyExpect2Colonies(NPChar.city,PChar.GenQuest.ChurchQuest_1.QuestTown))+". 그리고 그는 어떤 조건도 받을 자격이 없었지만, 그래도 도와주기로 동의했고 나에게 그 항구가 "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" 그가 분명히 방문할 것이오. 그래서 나는 이 기회를 이용해, 그 친절한 분에게 책들을 맡겨 보냈고, 그들의 앞날을 주님께 맡겼소.";
				link.l1 = "흠, 저 선장을 정말 믿을 수 있다고 확신하오? 그가 자신에게 맡겨진 작품들의 가치와 이 임무의 중요성을 제대로 알고 있소?";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_1";
			}
			else // Сцена 2б-б
			{
				dialog.text = "오, "+GetSexPhrase("아들아","내 딸")+"! 너 몇 시간이나 늦었어! 나는 이미 아버지의 책을 보냈다 "+PChar.GenQuest.ChurchQuest_1.PriestName+" 선장과 함께 "+PChar.GenQuest.ChurchQuest_1.CapFullName+". 오늘 아침, 그 신실한 사내가 고해성사를 하러 와서는 오늘 자기 배가 출항한다고 말했소 "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.CapColony)+". 그리고 선장은 아무 조건도 요구할 자격이 없었지만, 그래도 도와주겠다고 했고, 그 항구가\n "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" 그가 반드시 방문할 거야.";
				link.l1 = LinkRandPhrase("Father","Padre","Father")+"... 정말 이 선장을 믿을 수 있는지 확실합니까? 그리고 그의 배 이름도 알고 싶소.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_1";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1":	// 2б-а
			dialog.text = "나는 사람들을 믿어. "+GetSexPhrase("아들아","내 딸")+", 우리 모두는 주님의 형상과 모양대로 창조되었으며, 그분의 성스러운 불꽃이 모든 영혼에 타오르고 있소!";
			link.l1 = "으, 정말 무거운 말씀이군요. 음... 그럼 신부님, 제게 축복을 내려 주시고 그 선장을 찾는 여정에 행운을 빌어 주십시오.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true; // Полная инфа о кэпе
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_1");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_1":
			dialog.text = "사람들을 믿어야 해, "+GetSexPhrase("아들아","내 딸")+". 그의 배에 대해서는 할 말이 없어.";
			link.l1 = "그리고 당신은 그의 배 이름조차 알아보지도 않고 어떤 선장에게 귀중한 원고를 넘겼단 말이오?!!";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_2":
			dialog.text = "있잖아, "+GetSexPhrase("아들아","내 딸")+", 선장님 "+PChar.GenQuest.ChurchQuest_1.CapFullName+" 매우 신을 두려워하는 사람...";
			link.l1 = "음, 그건 이미 들었어.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_3";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_3":
			dialog.text = "인내심을 가져, "+GetSexPhrase("젊은이","아가씨")+"! 선장님 "+PChar.GenQuest.ChurchQuest_1.CapFullName+" 매우 신을 두려워하는 사람인데, 오늘날까지 그의 배는 어느 성직자도 입에 담아서는 안 될, 심지어 마음속으로조차 생각해서는 안 될 이름을 달고 있었소! 오늘 고해성사 중에 내가 그 점을 지적했지. 성경에도 나와 있듯이, 영혼의 순수함은 육체의 순수함보다도 더 죄인인 우리가 지켜야 하는 법이오. 우리 주님께서는 입이 더러운 자들에게는 그분의 왕국을 허락하지 않으시니...";
			link.l1 = "알겠어. "+LinkRandPhrase("Father","Padre","Father")+", 그렇군! "+PChar.GenQuest.ChurchQuest_1.CapFullName+", 카리브 전역에 악명 높은 도박꾼이자 주정뱅이인 그가, 당신의 제안으로 자기 낡은 배의 이름을 바꾸기로 했다고?";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_4";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_4":
			dialog.text = "눈썰미가 아주 좋군, "+GetSexPhrase("아들아","내 딸")+". 이 배의 새 이름은 모르겠지만, 분명 대단한 이름일 거라고 확신해.";
			link.l1 = "오, "+RandPhraseSimple("Father","Padre","Father")+"... 모든 것에 감사드립니다. 그리고 제 죄 많은 영혼을 위해 기도해 주십시오...";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_5";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_2");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
		break;
			
		case "GenQuest_Church_1_Complete_1":
			dialog.text = "오, 내 아이야! 내가 간절히 기도했더니 모든 일이 가장 좋은 방향으로 해결된 것 같구나! 네 도움과 믿음에, "+GetSexPhrase("아들아","내 딸")+", 천국과 천사의 노래가 분명히 기다리고 있을 것이오...";
			link.l1 = RandPhraseSimple("신부님.","신부님.")+", 나는 아직 성 베드로를 만날 생각이 없소, 하느님 부디 막아주소서. 살아 있는 이들은 천국의 약속 말고도 많은 물질적인 것이 필요하니까...";
			link.l1.go = "GenQuest_Church_1_Complete_2";
		break;
			
		case "GenQuest_Church_1_Complete_2":
			dialog.text = "그래, 그래, "+GetSexPhrase("아들아","내 딸")+", 물론이지. 마땅한 보상을 주겠소. 자, 이것을 받아두고, 세상 복을 지나치게 탐하거나 황금 악마를 숭배하는 어리석은 영혼들은 주님께서 벌하신다는 것을 기억하시오!";
			link.l1 = "감사합니다, "+LinkRandPhrase("Father","Padre","성부님")+". 오래 기다리던 책과 필사본을 받아 주시고, 제 죄 많은 영혼을 위해 기도해 주십시오... 안녕히 계십시오!";
			link.l1.go = "GenQuest_Church_1_Complete_3";
		break;
			
		case "GenQuest_Church_1_Complete_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			RemoveItems(PChar, "Bible", 1);
			items[FindItem("Bible")].Name = "itmname_bible";
			BackItemDescribe("Bible");
			DeleteAttribute(items[FindItem("Bible")], "City");
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddCharacterExpToSkill(PChar, "Leadership", 50); // Бонус в авторитет
			AddCharacterExpToSkill(PChar, "Fortune", 50); // Бонус в удачу
			TakeNItems(pchar, "chest", 3+hrand(1));
			PlaySound("interface\important_item.wav");
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			characters[GetCharacterIndex("ChurchGenQuest1_Cap")].LifeDay = 0;
			Group_DeleteGroup("ChurchGenQuest1_CapGroup"); // Трем кэпа
			PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = true; // Завершаем, если вдруг осталось
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSumm", FindRussianMoneyString(sti(PChar.GenQuest.ChurchQuest_1.AwardSumm)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
			break;
		// <-- Church GenQuest_1

        case "healthAdd_1":
            if (stf(pchar.Health.maxHP) == 60.0) // отлично
            {
                dialog.text = "당신의 건강은 "+GetHealthNameMaxSmall(pchar)+", 그리고 상처는 저절로 나을 거야. 피를 흘리지 않도록 조심하고 건강을 잘 챙기면 돼.";
    			link.l1 = "감사합니다, 정말 안심이 되는군요. 당분간은 싸움을 자제해 보겠습니다.";
    			link.l1.go = "exit";
            }
            else
            {
    			dialog.text = "당신의 건강은 "+GetHealthNameMaxSmall(pchar)+", 그리고 상처가 저절로 낫긴 하겠지만, 그래도 신경 써야 하오.";
    			link.l1 = "그것에 무엇이 필요하지?";
    			link.l1.go = "healthAdd_2";
			}
			link.l2 = "그런데 왜 내 건강이 점점 나빠지는 거지?";
    		link.l2.go = "healthAdd_info";
		break;

		case "healthAdd_info":
			dialog.text = "그건 아주 간단해, "+GetSexPhrase("아들아","내 딸")+". 부상당할 때마다 피해를 입는다. 그건 그냥 지나가지 않는다. 상처가 늘어날수록 건강이 악화되고, 그 결과 점점 약해진다. 약해진 선장을 본 선원들은 너를 덜 존경하게 된다. 하지만 너는 더 신중해지고, 스스로를 방어하는 능력이 일시적으로 증가한다. 휴식을 취하고 부상을 피하면 강인함을 유지할 수 있다.";
			link.l1 = "깨우쳐 주셔서 감사합니다.";
			link.l1.go = "exit";
		break;

		case "healthAdd_2":
			dialog.text = "기도와 폭력 자제, "+GetSexPhrase("아들아","내 딸")+". 그러면 주님께서 당신이 잃어버린 것을 되돌려주실 것입니다.";
			link.l1 = "하지만 저를 위해 기도해 주실 수 있습니까?";
			link.l1.go = "healthAdd_3";
			link.l2 = "그럼 방법이 없는 건가? 흠... 정말 마음이 놓였어, 고마워.";
			link.l2.go = "exit";
		break;

		case "healthAdd_3":
            if (npchar.quest.HealthMonth != iMonth)
            {
    			dialog.text = "나? 그럴 수도 있지. 하지만 우리 교구에 헌금을 해야 할 거야.";
    			link.l1 = pcharrepphrase("얼마야?","기꺼이! 얼마지?");
    			link.l1.go = "healthAdd_4";
    			link.l2 = "나 혼자서도 어떻게든 해내겠지...";
    			link.l2.go = "exit";
			}
			else
			{
                dialog.text = ""+GetSexPhrase("아들아","딸아")+", 이미 당신의 안녕을 위해 기도하고 있습니다. 이 기도는 이달 말까지 제 모든 시간을 차지할 것입니다.";
    			link.l1 = "감사합니다, "+RandPhraseSimple("신부님.","성부님.");
    			link.l1.go = "exit";
			}
		break;

		case "healthAdd_4":
			dialog.text = "치유의 기적에 대한 대가로 10만 페소면 충분할 것이오.";
			link.l1 = pcharrepphrase("뭐라고?!! 완전히 미쳤어? 그런 돈은 교회 몇 군데 털고 나서야 줄 수 있겠는데!","그건 나한텐 너무 비싸. 돈으로 건강을 살 수 없다는 말이 사실이라더군.");
			link.l1.go = "exit";
            if (sti(pchar.Money) >= 100000)
            {
    			link.l2 = "동의해!";
    			link.l2.go = "healthAdd_5";
			}
		break;

		case "healthAdd_5":
            AddMoneyToCharacter(pchar, -100000);
            AddCharacterMaxHealth(pchar, 4); // можно не проверять, тк явно меньше 51
            npchar.quest.HealthMonth = iMonth;
			dialog.text = "좋습니다. 건강이 조금 나아질 것입니다. 하지만 여전히 싸움을 피하고 몸조리를 잘해야 이 효과가 유지됩니다. 당신의 썩어 없어질 육신을 위해 한 달 내내 기도해야 하겠군요.";
			link.l1 = "고마워. 무슨 일 생기면 한 달 뒤에 다시 찾아올게.";
			link.l1.go = "exit";
		break;
		
		//квест пожертвования хозяйки борделя
		case "HostessChurch":
			dialog.text = "그리고 그 돈을 내놓는 착한 영혼이 누구요?";
			link.l1 = "흠... 저 사람은 이 동네 사창가의 마담이야.";
			link.l1.go = "HostessChurch_call";
			link.l2 = "이름은 비밀로 하고 싶소. 익명으로 기부할 수도 있지 않소?";
			link.l2.go = "HostessChurch_notCall";
			pchar.questTemp.different = "HostessChurch_return"; //флаг на возвращение
		break;
		
		case "HostessChurch_call":
			if (isBadReputation(pchar, 5)) 
			{
				if (rand(100) < GetCharacterSkill(pchar, "Fortune")) //рендом вешаем на удачу
				{
					dialog.text = "너도 죄인인데, 또 다른 죄인을 찾는단 말이오? 먼저 네 영혼부터 생각하는 게 좋을 거요; 사실 우리 모두가 주님 앞에 서게 될 것이오!";
					link.l1 = "그렇소. 주님께서 제게 자비를 베푸시길 바라오... 그런데, 헌금은 어떻게 하실 생각이오?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "사탄아, 내 뒤로 물러가라!!! 네 더러운 돈 챙기고 당장 꺼져라!";
					link.l1 = "어찌 그런 말씀을, 신부님?! 저희는 열린 마음으로 찾아왔는데, 신부님께서는...";
					link.l1.go = "HostessChurch_bad";
				}
			}
			else
			{
				if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma")) //рендом вешаем на харизму
				{
					dialog.text = "죄인들이 주님께로 돌아올 수 있도록 도와주고 있으니 기쁘구나. 그 대가로 천국에서 합당한 보상을 받게 될 것이네!";
					link.l1 = "그거 정말 좋지! 그런데, 기부금은 어떻게 할 건데?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "나는 죄로 얻은 돈을 받을 수 없다. 그 타락한 여자에게 돌려주게. "+GetSexPhrase("아들아","내 딸")+". 돈으로는 누구도 신께 다가갈 수 없다.";
					link.l1 = "그녀를 거절하다니 안타깝군. 정말 유감이야.";
					link.l1.go = "HostessChurch_bad_1";
				}
			}
		break;
		
		case "HostessChurch_notCall":
			if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				dialog.text = "이 돈이 어디서 온 건지도 모르고 가져가다니...";
				link.l1 = "네, 신부님, 맞습니다. 부디 이 마음에서 우러나온 헌금을 받아 주십시오!";
				link.l1.go = "HostessChurch_ok_1";
			}
			else
			{
				dialog.text = "이 돈이 어디서 온 건지도 모르면서 가져가겠다고? 미쳤어?! 이 돈에 피가 묻어 있다면 어쩔 건데!";
				link.l1 = "아버지, 모든 돈에는 피가 묻어 있습니다...";
				link.l1.go = "HostessChurch_bad_2";
			}
		break;

		case "HostessChurch_ok":
			dialog.text = "나는 받아들이겠다. "+GetSexPhrase("아들아","내 딸")+". 가서 그걸 네 타락한 여자한테나 말해.";
			link.l1 = "알겠소, 신부님. 감사합니다.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_ok_1":
			dialog.text = "나는 받아들이겠다. "+GetSexPhrase("아들아","내 딸")+". 그 은인에게 이 사실을 전하시오.";
			link.l1 = "알겠소, 신부님. 고맙소.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_bad":
			dialog.text = "꺼져라, 지옥에서 온 놈아! 다시는 여기 얼굴 내밀 생각도 하지 마라!";
			link.l1 = "헤, 좋을 대로 해.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_1":
			dialog.text = "이것이 내 결정이오. 평안히 가시오, "+GetSexPhrase("아들아","내 딸")+".";
			link.l1 = "안녕히 계십시오, 신부님.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_2":
			dialog.text = "그게 네 생각이냐, 불경한 놈아?! 당장 이 사원을 떠나고 다시는 여기 나타나지 마라!";
			link.l1 = "아, 정말이야? 됐다, 난 간다...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;

		//--> Jason Церковная депеша
		case "Monkletter":
			if (CheckAttribute(pchar, "GenQuest.Monkletter.Late"))
			{
				dialog.text = "이 서류들을 다시 볼 희망을 거의 잃을 뻔했구나. 왜 이렇게 오래 걸렸느냐, 아들아?";
				link.l1 = "예상치 못한 전개였습니다, 신부님.";
				link.l1.go = "Monkletter_1";
			}
			else
			{
				dialog.text = "이 서류를 기다리고 있었단다, 아들아. 신속하게 가져다줘서 고맙구나. 이 동전을 받아 가거라, 내 축복도 함께하니.";
				link.l1 = "감사합니다, 신부님. 성스러운 교회를 돕게 되어 기뻤습니다!";
				link.l1.go = "Monkletter_3";
			}
		break;
		
		case "Monkletter_1":
			dialog.text = "우리는 모두 신의 손 안에 있단다, 아들아... 사람이 계획하나, 신이 결정하신다. 그 서류들을 내게 주고 평안히 가거라.";
			link.l1 = "자, 여기 있습니다, 신부님. 행운을 빕니다!";
			link.l1.go = "Monkletter_2";
		break;
		
		case "Monkletter_2":
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "2");
			CloseQuestHeader("Monkletter");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter_3":
			dialog.text = "신의 축복이 있기를, 아들아. 전능하신 분께서 네 여행을 지켜주시길!";
			link.l1 = "안녕히 계십시오, 신부님.";
			link.l1.go = "Monkletter_4";
		break;
		
		case "Monkletter_4":
			pchar.quest.Monkletter_Over.over = "yes"; //снять таймер
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "3");
			CloseQuestHeader("Monkletter");
			TakeNItems(pchar, "gold_dublon", 10+rand(5));
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
			addLiberMisBonus();
		break;
		//<-- Церковная депеша
		
		//--> Jason Доставить молитвенники
		case "Churchbooks":
			dialog.text = "너는 우리에게서 기도서를 가져가라고 보냈군 - 그 교회를 위해서 "+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity+"Gen")+"음? 좋아. 나는 기도서 서른 권이 들어 있는 꾸러미가 있다. 가져가거라, 아들아.";
			link.l1 = "감사합니다, 신부님. 안녕히 계십시오!";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			dialog.text = "주님께서 당신의 여정에 함께하시길! 평안히 가십시오...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Churchbooks", "2");
			pchar.GenQuest.Churchbooks = "return";
			GiveItem2Character(pchar, "prayer_book");//поставить соотв.предмет
		break;
		
		case "Churchbooks_2":
			if (CheckAttribute(pchar, "GenQuest.Churchbooks.Late"))
			{
				dialog.text = "도와줘서 고맙다, 아들아, 비록 조금 늦게 도착했지만.";
				link.l1 = "예상치 못한 일들 때문에 늦었습니다, 신부님.";
				link.l1.go = "Churchbooks_3";
			}
			else
			{
				dialog.text = "도와줘서 고맙다, 아들아. 네가 이 책들을 적시에 가져왔구나. 자, 이 성스러운 부적을 보상으로 받아라 – 가장 어두운 순간에 너를 위험에서 지켜줄 것이다.";
				link.l1 = "감사합니다, 신부님. 성스러운 교회를 돕게 되어 저도 기뻤습니다!";
				link.l1.go = "Churchbooks_4";
			}
		break;
		
		case "Churchbooks_3":
			dialog.text = "모든 것은 신의 뜻에 달려 있단다, 아들아. 평안히 가거라!";
			link.l1 = "안녕히 계십시오, 신부님.";
			link.l1.go = "exit";
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			AddQuestRecord("Churchbooks", "3");
			CloseQuestHeader("Churchbooks");
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;
		
		case "Churchbooks_4":
			dialog.text = "신의 축복이 있기를, 아들아. 전능하신 분께서 네 길에 해가 없도록 지켜주시길!";
			link.l1 = "안녕히 계세요, 신부님.";
			link.l1.go = "Churchbooks_5";
		break;
		
		case "Churchbooks_5":
			pchar.quest.Churchbooks_Over.over = "yes"; //снять таймер patch-5
			DialogExit();
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			GiveItem2Character(pchar, pchar.GenQuest.Churchbooks.Item);
			Log_Info("You have received '"+XI_ConvertString(pchar.GenQuest.Churchbooks.Item)+"'");
			AddQuestRecord("Churchbooks", "4");
			CloseQuestHeader("Churchbooks");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
			addLiberMisBonus();
		break;
	}
}

void ChurchGenQuest2_RemoveCup()
{
	RemoveItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	DeleteAttribute(rItem, "City");
	rItem.Weight = 2;
	rItem.Name = "itmname_Bible";
	rItem.picIndex = 6;
	rItem.picTexture = "ITEMS_9";
	BackItemDescribe("Bible");
}

void Church_GenQuest1_InitStartParam(ref chr)
{
	string sColony = SelectNotEnemyColony(chr); 
	PChar.GenQuest.ChurchQuest_1.IslandId = colonies[FindColony(PChar.GenQuest.ChurchQuest_1.QuestTown)].Island;
	PChar.GenQuest.ChurchQuest_1.ToColony = sColony;
	PChar.GenQuest.ChurchQuest_1.ToIsland = colonies[FindColony(sColony)].Island;
	PChar.GenQuest.ChurchQuest_1.ToName = characters[GetCharacterIndex(sColony + "_Priest")].Name;
	
	// Чтоб жизнь медом не казалась... Какие сцены будут в квесте, определяем в самом начале.
	int iRand = Rand(2);
	switch(iRand)
	{
		case "0":
			PChar.GenQuest.ChurchQuest_1.2A_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2A (just pick up the manuscript from the priest)."); 
		break;
		
		case "1":
			PChar.GenQuest.ChurchQuest_1.2BA_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2B-A (search for a cap. There is full information about him).");
		break;
		
		case "2": // Этот флаг уже не проверяем, т.к. если нет тех, что выше, по-любому есть этот
			PChar.GenQuest.ChurchQuest_1.2BB_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2B-B (search for a cap. The name of the ship is unknown)."); 
		break;
	}
}
