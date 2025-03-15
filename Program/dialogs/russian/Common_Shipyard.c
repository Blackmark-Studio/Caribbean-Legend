// boal 08/04/06 общий диалог верфи
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	string s2;
	
	int iShipClass = GetCharacterShipClass(PChar); // Если корабля нет, вернет 7 (лодка)
	int iRank = sti(PChar.rank);
	int iSumm, iType;
	
	ref rRealShip;
	ref shTo;
	aref refShip;
	string attr;
	float fTmp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Shipyard\" + NPChar.City + "_Shipyard.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int Material, WorkPrice;
	int amount;
	int	iCannonDiff;
	
	// генератор парусов по кейсу -->
	string attrLoc   = Dialog.CurrentNode;
	int i;
  	if (findsubstr(attrLoc, "SailsColorIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsColorIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsColorDone";
 	}
 	if (findsubstr(attrLoc, "SailsTypeChooseIDX_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsTypeChooseIDX = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsTypeChoose2";
 	}
	
	
 	// генератор парусов по кейсу <--
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "ship_tunning_not_now":  // аналог выхода, со старых времён, много переделывать.
            LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  // выход для тюнинга, нужно тут из-за LoadSegment
		break;
		
		case "ship_tunning_not_now_1":  
			LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":
            if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("В городе поднята тревога, тебя всюду ищут! На твоём месте я бы не стал здесь задерживаться.", "Вся городская стража рыщет по городу в поисках тебя. Я не идиот и разговаривать с тобой не буду!", "Беги, "+ GetSexPhrase("приятель","подруга") +", пока солдаты не сделали из тебя решето..."), 
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","мерзавка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти"+ GetSexPhrase(", грязный пират","") +"!", "Грязн"+ GetSexPhrase("ый","ая") +" убийца, вон из моего дома! Стража!!", "Я не боюсь тебя, мерзав"+ GetSexPhrase("ец","ка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."), 
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Хех, " + GetWorkTypeOfMan(npchar, "") + ", а всё туда же - пиратов ловить! Вот что я тебе скажу, приятель: сиди тихо и будешь жить..."));
				link.l1.go = "fight";
				break;
			}
			
//Jason ---------------------------------------Бремя гасконца------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_shipyard")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
				{
					dialog.text = "Вы что-то хотели, месье?";
					Link.l1 = "Я пришёл посмотреть корабли, какие у вас есть... Но сейчас я немного занят - дело одно незаконченное осталось. Я ещё загляну попозже, как только разберусь с ним.";
					Link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
				{
					dialog.text = "Вы что-то хотели, месье?";
					Link.l1 = "Послушайте, я бы хотел приобрести у вас корабль.";
					Link.l1.go = "Sharlie";
					break;
				}
				dialog.text = "Вы что-то ещё хотели, месье?";
				Link.l1 = "Нет, пожалуй, ничего.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				NPChar.quest.meeting = "1";
				break;
			}
	//<-- Бремя гасконца
			// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
			if (CheckAttribute(pchar, "questTemp.FMQM.Oil") && pchar.location == "Fortfrance_shipyard")
			{
				if (pchar.questTemp.FMQM == "remove_oil")
				{
					dialog.text = "Ну вот, капитан, дело сделано. Теперь самый приятный для вас момент - звон полновесной монеты. Одну минутку...";
					link.l1 = "...";
					link.l1.go = "FMQM_oil_1";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil1")
				{
					dialog.text = "Господин офицер, постойте! Это какая-то ошибка. Месье капитан тут совершенно ни при чём - он просто задержался, пока мы заканчивали ремонт его судна, рассчитался и собрался уходить. Что за бочки? О чём идёт речь?";
					link.l1 = "";
					link.l1.go = "FMQM_oil_2";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil2")
				{
					dialog.text = "Господин офицер, я ещё раз повторяю: капитан пришёл заплатить деньги за ремонт судна. А бочки эти в подсобке - мои, и предназначены они для дела! Я мастер-корабел, и эта смола используется в моём производстве!";
					link.l1 = "";
					link.l1.go = "FMQM_oil_3";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil3")
				{
					dialog.text = "О, месье капитан! Вы даже не представляете, какое для меня это было испытание - два дня на охапке соломы на полу, среди крыс, мышей, вони и гнусных личностей! Мне пришлось напрячь все мои связи, чтобы внести залог и выйти наконец на свежий воздух...";
					link.l1 = "Сочувствую, мастер. Что с нашими смолами? Моими деньгами?";
					link.l1.go = "FMQM_oil_4";
					DelLandQuestMark(npchar);
					break;
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_13" && pchar.location == "PortRoyal_shipyard")
			{
				dialog.text = "О! Это снова вы! Молодой человек, я вас узнал. Ведь это вы недавно поднимали вопрос об... улучшении ходовых качеств корабля при помощи шёлка?";
				link.l1 = "У вас хорошая память, мастер."; 
				link.l1.go = "mtraxx_x";
				break;
			}
	
			if(NPChar.quest.meeting == "0") // первая встреча
			{
				dialog.Text = GetNatPhrase(npchar, LinkRandPhrase("Ха! В мою скромную мастерскую заглянул"+GetSexPhrase("","а")+" настоящ"+GetSexPhrase("ий","ая")+" морск"+GetSexPhrase("ой","ая")+" "+GetSexPhrase("волк","волчица")+"! Недавно в здешних водах, капитан?","Добро пожаловать, "+GetAddress_Form(NPChar)+"! Если вы имеете отношение к морю и у вас есть корабль - вы не зря зашли ко мне!","Приветствую вас, "+GetAddress_Form(NPChar)+"! Вам повезло - вы зашли в лучшую корабельную мастерскую Английского Нового Света."), LinkRandPhrase("Здравствуйте, "+GetAddress_Form(NPChar)+". Я не ошибусь, предположив, что вижу перед собой лихого капитана? Если да, то и вы не ошиблись, посетив мою скромную верфь!","Впервые у нас, "+GetAddress_Form(NPChar)+" капитан? Заходите, не побрезгуйте знакомством со скромным корабелом.","Будем знакомы, "+GetAddress_Form(NPChar)+"! Кораблю, как и женщине, нужна ласка, а кто лучше француза знает толк в ласках? Поверьте, вы не зря завернули именно ко мне!"), LinkRandPhrase("Никогда не встречал вас раньше, "+GetAddress_Form(NPChar)+". Рад новому знакомству!","Я приветствую "+GetSexPhrase("отважного покорителя","отважную покорительницу")+" морей! Вы ведь "+GetSexPhrase("моряк, друг мой","морячка, верно")+"? А я здешний мастер корабельных дел, нам следует познакомиться.","Здравствуйте, "+GetSexPhrase("кабальеро","сеньорита")+"! Приветствую вас в своей мастерской!"),LinkRandPhrase("Добрый день, "+GetAddress_Form(NPChar)+". Я не встречал вас раньше, вы ко мне по делу?","Здравствуйте, "+GetAddress_Form(NPChar)+" капитан. Не удивляйтесь, я видел столько капитанов, что без труда распознаю ещё одного!","Прошу вас, "+GetAddress_Form(NPChar)+". Я здешний корабельный мастер, будем знакомы."));
				Link.l1 = LinkRandPhrase("Очень рад"+GetSexPhrase("","а")+" знакомству. Меня зовут "+GetFullName(pchar)+", и я здесь совсем недавно. Вот, решил"+GetSexPhrase("","а")+" заглянуть на огонёк.","Не смог"+GetSexPhrase("","ла")+" пройти мимо вашей двери - так пахнуло свежей доской. Я - "+GetFullName(pchar)+", капитан корабля '"+pchar.ship.name+"'.","Позвольте представиться - "+GetFullName(pchar)+", капитан корабля '"+pchar.ship.name+"', рад"+GetSexPhrase("","а")+" знакомству. А вы, значит, строите и ремонтируете корабли?");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_shipyard")
				{
					dialog.text = "Здравствуйте, капитан МакАртур.";
					link.l1 = "Можно просто Элен, мистер "+npchar.lastname+". "+TimeGreeting()+".";
					Link.l1.go = "Helen_meeting";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("О! К нам пожаловал гроза здешних вод, капитан "+GetFullName(pchar)+"! Чем могу быть полезен?","Сразу к делу, "+GetAddress_Form(NPChar)+", некогда мне болтать. Нужен ремонт или хотите сменить посудину?","Ба, да нас изволил посетить "+GetFullName(pchar)+"! Что случилось, "+GetAddress_Form(NPChar)+"? Беда постигла вашу лоханку?"),LinkRandPhrase("А вам что тут нужно, капитан? Ни минуты покоя от этих проходимцев, что за день такой...","Здравствуйте, "+GetAddress_Form(NPChar)+". Должен заметить, что ваш визит распугал мне всех клиентов. Будем надеяться, ваш заказ покроет мои убытки?","С делом ко мне, "+GetAddress_Form(NPChar)+"? Что же, давайте, излагайте свои дела, да побыстрее."),LinkRandPhrase("Что за дела привели вас ко мне, "+GetSexPhrase("господин","госпожа")+" "+GetFullName(pchar)+"? Понимаю, при вашем образе жизни кораблю приходится нелегко...","Рад приветствовать благородн"+GetSexPhrase("ого","ую")+"... о, простите, "+GetAddress_Form(NPChar)+", я обознался. С чем пожаловали?","Я не очень привечаю людей вашего склада, капитан, но и выгонять, конечно, не стану. Что вам нужно?")),LinkRandPhrase(LinkRandPhrase("Очень рад вам, "+GetSexPhrase("господин","госпожа")+" "+GetFullName(pchar)+"! Как бегает ваша ласточка? Не нужен ли ремонт или кренгование?","Добро пожаловать, "+GetAddress_Form(NPChar)+"! Капитан "+GetFullName(pchar)+" всегда желанный гость в моей мастерской!","О, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Вы снова посетили меня! Надеюсь, с вашим красавцем всё в порядке?"),LinkRandPhrase("О, "+GetAddress_Form(NPChar)+", как же я рад видеть вас снова! Как поживает ваш прекрасный корабль? Не нужна ли моя помощь?","О, "+GetAddress_Form(NPChar)+", приветствую вас! Как ваши дела? Не скрипят ли мачты, не нужно ли очистить днище? Для вас мои ребята расстараются!","Добрый день, капитан "+GetFullName(pchar)+". Я рад, что вы снова заглянули ко мне и всегда готов помочь вам."),LinkRandPhrase("Очень рад вашему визиту, капитан! Вы очень хороший клиент, "+GetAddress_Form(NPChar)+", и я желаю вам таковым и оставаться.","А-а, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Бесконечно рад вашему визиту! Чем могу быть полезен?","Капитан, вы снова посетили "+XI_ConvertString("Colony"+npchar.City+"Acc")+"! Поверьте, мы будем рады вам помочь.")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Доставай инструменты, мастер, да помалкивай. Я сегодня не в духе.","Хорош трепаться, приятель. Мне нужна твоя помощь, а не пустая болтовня."),RandPhraseSimple("Я плачу - ты работаешь. Молча. Уяснил?","Давай, дружище, гони всех подальше - прибыл твой главный клиент!")),RandPhraseSimple(RandPhraseSimple("Я тоже рад"+GetSexPhrase("","а")+" вас видеть, мастер. Увы, времени у меня немного, так что давайте перейдём к делу.","И я приветствую вас, дружище. Готовы уделить внимание постоянному клиенту?"),RandPhraseSimple("Добрый день, любезный. Сразу перейдём к делам. Но обещаю в следующий раз обязательно просто посидеть с бутылочкой.","Очень рад"+GetSexPhrase("","а")+" вам, мастер. К вам всегда приятно заглянуть, но сейчас мне нужна ваша помощь.")));
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l11 = "Мне нужны орудия на корабль.";
					link.l11.go = "Cannons";					
				}	
				
				if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "Charles" || NPChar.city == "PortoBello")
				{
					link.l22 = "Вы не могли бы мне предложить что-то особенное, то что больше не предложат ни на одной верфи?";
					link.l22.go = "ship_tunning";
				}
				
				link.l15 = "Нет ли у вас дела, требующего сторонней помощи?";
			    link.l15.go = "Tasks";
				// Jason Исла Мона 
				if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "tools" && !CheckAttribute(npchar, "quest.IslaMonaTools"))
				{
					link.l20 = "Я хочу купить набор инструментов для строительства, ковки и измерений европейского качества. Поможешь?";
					link.l20.go = "IslaMona";
				}
				if (CheckAttribute(npchar, "quest.IslaMonaMoney"))
				{
					link.l20 = "Я принес дублоны для набор инструментов для строительства.";
					link.l20.go = "IslaMona_7";
				}
				//Jason --> генератор Призонер
				if (CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && NPChar.location == pchar.GenQuest.Findship.Shipyarder.City + "_shipyard")
				{
					ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
					if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
					{
						for(i = 1; i < COMPANION_MAX; i++)
						{
							int iTemp = GetCompanionIndex(PChar, i);
							if(iTemp > 0)
							{
								sld = GetCharacter(iTemp);
								if(GetRemovable(sld) && sti(RealShips[sti(sld.ship.type)].basetype) == sti(pchar.GenQuest.Findship.Shipyarder.ShipType))
								{
									pchar.GenQuest.Findship.Shipyarder.CompanionIndex = sld.Index;
									pchar.GenQuest.Findship.Shipyarder.OK = 1;
									pchar.GenQuest.Findship.Shipyarder.ShipName = sld.Ship.Name;
									pchar.GenQuest.Findship.Shipyarder.Money = makeint(GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder"))*1.5);
								}
							}
						}
					}
					if (sti(pchar.GenQuest.Findship.Shipyarder.OK) == 1)
					{
						link.l16 = "Я доставил вам "+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+", как вы просили.";
						link.l16.go = "Findship_check";
					}// <-- генератор Призонер
				}
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && CheckCharacterItem(pchar, "Tool") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_shipyard")
				{
					link.l17 = "Мне удалось разыскать вора и добыть "+pchar.GenQuest.Device.Shipyarder.Type+".";
					link.l17.go = "Device_complete";
				}
				// <-- генератор Неудачливый вор
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "Хочу изменить внешний вид парусов.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "Я только хочу поговорить.";
				Link.l2.go = "quests"; //(перессылка в файл города)
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Я хотел"+ GetSexPhrase("","а") +" бы поговорить с вами о делах финансовых.";
					link.l3.go = "LoanForAll";
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && CheckAttribute(pchar, "GenQuest.Intelligence.SpyId") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Я здесь по поручению одного человека. Его зовут губернатор " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " прислал меня к вам. Я долж"+ GetSexPhrase("ен","на") +" кое-что забрать...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "Я доставил"+GetSexPhrase("","а")+" чертёж корабля из города "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				} // patch-6
				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l7 = "Здравствуйте, я приш"+ GetSexPhrase("ёл","ла") +" по приглашению вашего сына."; 
						link.l7.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l8 = "Я по поводу вашей дочери...";
							link.l8.go = "EncGirl_1";
						}
					}
				}								
				Link.l9 = "Мне нужно идти.";
				Link.l9.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Meeting":
				dialog.Text = "Я рад встрече с новым клиентом. Моя верфь к вашим услугам.";
				Link.l1 = "Великолепно, " + GetFullName(NPChar) + ". Давайте посмотрим то, что вы можете мне предложить.";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "Мне нужны орудия на корабль.";
					link.l13.go = "Cannons";
				}									
				link.l15 = "Нет ли у вас дела, требующего сторонней помощи?";
			    link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "Хочу изменить внешний вид парусов.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "Я только хочу поговорить.";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Я хотел"+ GetSexPhrase("","а") +" бы поговорить с вами о делах финансовых.";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Я здесь по поручению одного человека. Его зовут губернатор " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " прислал меня к вам. Я долж"+ GetSexPhrase("ен","на") +" кое-что забрать...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "Я доставил чертёж корабля из города "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "Здравствуйте, я приш"+ GetSexPhrase("ёл","ла") +" по приглашению вашего сына."; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "Я по поводу вашей дочери...";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "Что вы можете сказать о владельце этих документов?";
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = "Я долж"+ GetSexPhrase("ен","на") +" идти. Благодарю вас.";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;
		
		case "Helen_Meeting":
				dialog.Text = "Конечно, капитан МакАртур, как скажете. Что именно вам сегодня требуется?";
				Link.l1 = "Великолепно, " + GetFullName(NPChar) + ". Давайте посмотрим то, что вы можете мне предложить.";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "Мне нужны орудия на корабль.";
					link.l13.go = "Cannons";
				}									
				link.l15 = "Нет ли у вас дела, требующего сторонней помощи?";
			    link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "Хочу изменить внешний вид парусов.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "Я только хочу поговорить.";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Я хотел"+ GetSexPhrase("","а") +" бы поговорить с вами о делах финансовых.";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Я здесь по поручению одного человека. Его зовут губернатор " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " прислал меня к вам. Я долж"+ GetSexPhrase("ен","на") +" кое-что забрать...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "Я доставил чертёж корабля из города "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "Здравствуйте, я приш"+ GetSexPhrase("ёл","ла") +" по приглашению вашего сына."; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "Я по поводу вашей дочери...";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "Что вы можете сказать о владельце этих документов?";
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = "Я долж"+ GetSexPhrase("ен","на") +" идти. Благодарю вас.";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;

		case "ship_tunning":
			dialog.text = "Наша верфь занимается улучшением кораблей. Вам это интересно, капитан?";
			Link.l1 = LinkRandPhrase("Замечательно! Может взглянете на моё судно, что с ним можно сделать?",
			          "Очень интересно, мастер! Что вы сумеете изменить в моём корабле?",
					  "Хм. Я привык"+GetSexPhrase("","ла")+" к своему судну, но если вы сможете предложить что-либо интересное, обещаю подумать. Что скажете?");
			Link.l1.go = "ship_tunning_start";
		break;
				
		case "ship_tunning_start" :		
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{				
				if (sti(RealShips[sti(pchar.Ship.Type)].Class) >= 6)
				{
					dialog.Text = "Эээ.. Лодками я не занимаюсь. Корыто корытом и останется, сколько над ним ни колдуй.";
					Link.l1 = "Понятно...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// belamour legendary edition -->
				if(!TuningAvailable())
				{
					dialog.Text = "Так-так... посмотрим, что тут у нас есть... Ага - " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ". Ваше судно уже имеет максимальное количество улучшенных характеристик, боюсь, дальнейшая работа над ним лишена всякого смысла и может только навредить.";
					Link.l1 = "Понятно...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// <-- legendary edition
				if(GetHullPercent(pchar) < 100 || GetSailPercent(pchar) < 100)
				{
					dialog.Text = "Перед улучшением корабль необходимо полностью отремонтировать. Это можно сделать на моей верфи.";
					Link.l1 = "Понятно...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				
				s2 = "Так-так... посмотрим, что тут у нас есть... Ага " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
				// belamour legendary edition -->			
				if(NPChar.city == "PortRoyal")
				{
					s2 = s2 + " Наша верфь славится работой с ходовыми качествами: мы можем увеличить максимальную скорость и угол хода к ветру.";
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					s2 = s2 + " На моей верфи можно увеличить количество орудийных портов в бортовых батареях и грузоподъёмность судна.";
				}
				if(NPChar.city == "Villemstad")
				{
					s2 = s2 + " Мои ребята усилят корпус вашего судна, или же могут увеличить вместительность (максимальную численность) экипажа.";
				}
				if(NPChar.city == "Charles")
				{
					s2 = s2 + " На этой верфи можно улучшить манёвренность и уменьшить минимальную численность экипажа.";
				}	
				
				dialog.Text = s2;
				
				if(NPChar.city == "PortRoyal")
				{
					// belamour legendary edition -->
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"));
					if(ok)
					{
						Link.l1 = "Увеличить скорость.";
						Link.l1.go = "ship_tunning_SpeedRate";
						Link.l2 = "Увеличить угол хода к ветру.";
						Link.l2.go = "ship_tunning_WindAgainst";
						Link.l3 = "Постойте! Я передумал"+ GetSexPhrase("","а") +".";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate"))
						{
							Link.l1 = "Увеличить скорость.";
							Link.l1.go = "ship_tunning_SpeedRate";
							Link.l2 = "Постойте! Я передумал"+ GetSexPhrase("","а") +".";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"))
						{
							Link.l1 = "Увеличить угол хода к ветру.";
							Link.l1.go = "ship_tunning_WindAgainst";
							Link.l2 = "Постойте! Я передумал"+ GetSexPhrase("","а") +".";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("О! Моё судно уже улучшено по профилю ваших работ. Спасибо, что уделили мне время!",
												 "Спасибо, мастер, но у меня уже есть улучшение, и как раз из перечисленных вами. Удачи с другими судами и их владельцами!",
												 "Хех! Мой корабль уже переделывался прежним владельцем, не иначе, как на этой верфи. Спасибо ему за заботу, а вам и вашим умельцам за отличную работу!");
						Link.l1.go = "ship_tunning_not_now_1";		
					}
					// <-- legendary edition
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"));
					if(ok)
					{	
						if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
						{	
							Link.l1 = "Увеличить максимальное количество орудий.";
							Link.l1.go = "ship_c_quantity";
						}	
						// belamour legendary edition -->
						Link.l2 = "Увеличить дедвейт.";
						Link.l2.go = "ship_tunning_Capacity";
						Link.l3 = "Постойте! Я передумал"+ GetSexPhrase("","а") +".";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon"))
						{
							if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
							{	
								Link.l1 = "Увеличить максимальное количество орудий.";
								Link.l1.go = "ship_c_quantity";
								Link.l2 = "Постойте! Я передумал"+ GetSexPhrase("","а") +".";
								Link.l2.go = "ship_tunning_not_now_1";	
								break;
							}
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"))
						{
							Link.l1 = "Увеличить дедвейт.";
							Link.l1.go = "ship_tunning_Capacity";
							Link.l2 = "Постойте! Я передумал"+ GetSexPhrase("","а") +".";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("О! Моё судно уже улучшено по профилю ваших работ. Спасибо, что уделили мне время!",
						                         "Спасибо, мастер, но у меня уже есть улучшение, и как раз из перечисленных вами. Удачи с другими судами и их владельцами!",
												 "Хех! Мой корабль уже переделывался прежним владельцем, не иначе, как на этой верфи. Спасибо ему за заботу, а вам и вашим умельцам за отличную работу!");
						Link.l1.go = "ship_tunning_not_now_1";	
					// <-- legendary edition
					}						
				}
				if(NPChar.city == "Villemstad")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"));
					if(ok)
					{
						Link.l1 = "Увеличить прочность корпуса.";
						Link.l1.go = "ship_tunning_HP";
						Link.l2 = "Прибавить место для экипажа.";
						Link.l2.go = "ship_tunning_MaxCrew";
						Link.l3 = "Постойте! Я передумал"+ GetSexPhrase("","а") +".";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						// belamour legendary edition -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP"))
						{
							Link.l1 = "Увеличить прочность корпуса.";
							Link.l1.go = "ship_tunning_HP";
							Link.l2 = "Постойте! Я передумал"+ GetSexPhrase("","а") +".";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"))
						{
							Link.l1 = "Прибавить место для экипажа.";
							Link.l1.go = "ship_tunning_MaxCrew";
							Link.l2 = "Постойте! Я передумал"+ GetSexPhrase("","а") +".";
							Link.l2.go = "ship_tunning_not_now_1";
							break;	
						}
						Link.l1 = LinkRandPhrase("О! Моё судно уже улучшено по профилю ваших работ. Спасибо, что уделили мне время!",
						                         "Спасибо, мастер, но у меня уже есть улучшение, и как раз из перечисленных вами. Удачи с другими судами и их владельцами!",
												 "Хех! Мой корабль уже переделывался прежним владельцем, не иначе, как на этой верфи. Спасибо ему за заботу, а вам и вашим умельцам за отличную работу!");
						Link.l1.go = "ship_tunning_not_now_1";	
						// <-- legendary edition
					}
				}
				if(NPChar.city == "Charles")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"));
					if(ok)
					{		
						Link.l1 = "Увеличить манёвренность.";
						Link.l1.go = "ship_tunning_TurnRate";
						if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
						{
							Link.l2 = "Уменьшить минимальную численность экипажа.";
							Link.l2.go = "ship_tunning_MinCrew";
						}	
						Link.l3 = "Постойте! Я передумал"+ GetSexPhrase("","а") +".";
						Link.l3.go = "ship_tunning_not_now_1";
						break;						
					}
					else
					{
						// belamour legendary edition -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate"))
						{
							Link.l1 = "Увеличить манёвренность.";
							Link.l1.go = "ship_tunning_TurnRate";
							Link.l2 = "Постойте! Я передумал"+ GetSexPhrase("","а") +".";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"))
						{
							if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
							{
								Link.l1 = "Уменьшить минимальную численность экипажа.";
								Link.l1.go = "ship_tunning_MinCrew";
								Link.l2 = "Постойте! Я передумал"+ GetSexPhrase("","а") +".";
								Link.l2.go = "ship_tunning_not_now_1";
								break;
							}	
						}
						// <-- legendary edition		
					}
					Link.l1 = LinkRandPhrase("О! Моё судно уже улучшено по профилю ваших работ. Спасибо, что уделили мне время!",
						                         "Спасибо, мастер, но у меня уже есть улучшение, и как раз из перечисленных вами. Удачи с другими судами и их владельцами!",
												 "Хех! Мой корабль уже переделывался прежним владельцем, не иначе, как на этой верфи. Спасибо ему за заботу, а вам и вашим умельцам за отличную работу!");
					Link.l1.go = "ship_tunning_not_now_1";			
				}						
			}
			else
			{
				dialog.Text = "Корабль-то где? Что вы мне тут голову морочите?!";
			    Link.l1 = "И то правда.. что это я... Извиняюсь";
			    Link.l1.go = "ship_tunning_not_now_1";
			}			
		break;
		
		////////////////////////////////////////// Capacity ////////////////////////////////////////////////////
		case "ship_tunning_Capacity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Давайте посмотрим, что можно сделать. Сейчас дедвейт вашего судна - " + sti(RealShips[sti(pchar.Ship.Type)].Capacity);			
			s2 = s2 + ". Для облегчённых переборок мне понадобится: бакаута - " + Material + ".";
			s2 = s2 + " В оплату за свою работу я возьму: " + WorkPrice + " сундуков с дублонами - на рабочие расходы. Вроде бы всё. Ах да - деньги вперёд.";		
            dialog.Text = s2;
			Link.l1 = "Годится. Я принимаю условия. Всё оговоренное будет доставлено.";
			Link.l1.go = "ship_tunning_Capacity_start";
			Link.l2 = "Нет. Меня это не устраивает.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_Capacity_start":
		    amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Сундуки с дублонами были взяты из каюты: " + iSumm+ " шт.");
				}
				// <-- legendary edtion
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;			    
				NextDiag.TempNode = "ship_tunning_Capacity_again";
                dialog.text = "Вот и славно. Жду материалы.";
			    link.l1 = LinkRandPhrase("Уверяю, ждать долго не придётся. Я умею решать такие задачки, смекаете?",
										 "Считайте, что они уже у вас и придержите док, я буду скор"+GetSexPhrase("","а")+", как ветер.",
										 "Не вопрос. Вот только навещу пару-тройку владельцев затребованного, ха-ха-ха!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "За свою работу по увеличению дедвейта на " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'"+
				" мастер-корабел требует: бакаута - " + NPChar.Tuning.Matherial + ". В качестве задатка было уплачено " + NPChar.Tuning.Money + " сундуков с дублонами.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Не вижу задатка...";
				link.l1 = "Я позже зайду.";
				link.l1.go = "Exit";								
			}
		break;
				
		case "ship_tunning_Capacity_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "Время идёт, а судно ждёт. Вы всё доставили, что я попросил?";
			    Link.l1 = "Да. Кое-что удалось достать.";
			    Link.l1.go = "ship_tunning_Capacity_again_2";
			    Link.l2 = "Нет. Ещё добываю.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
			    dialog.Text = "Судар"+ GetSexPhrase("ь","ыня") +", вы поменяли корабль со времени нашего уговора? Напрасно.";
			    Link.l1 = "Увы, всему виной обстоятельства! Обидно, что задаток пропал...";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_Capacity_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Замечательно, теперь всё в наличии. Начинаю работу...";
			    link.l1 = "Жду.";
			    link.l1.go = "ship_tunning_Capacity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "За вами осталось: бакаута - " + sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Хорошо.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Мне осталось довезти: бакаута - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_Capacity_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_Capacity"))
			{
				shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
			}
			else
			{
				shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
			}			
	        shTo.Tuning.Capacity = true;
	        // finish <--
            NextDiag.TempNode = "First time";
			dialog.Text = "...Вроде бы всё... Можно грузиться по полной, качество работы гарантирую.";
			Link.l1 = "Спасибо! Проверю обязательно.";
			Link.l1.go = "Exit";
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// SpeedRate ////////////////////////////////////////////////////
		case "ship_tunning_SpeedRate":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar,  1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar,  2 );
			s2 = "Давайте посмотрим, что можно сделать. Сейчас скорость вашего корабля " + stf(RealShips[sti(Pchar.Ship.Type)].SpeedRate);	
			s2 = s2 + " узлов. Для новых парусов мне понадобится: корабельного шёлка - "+ Material + ".";
			s2 = s2 + " В оплату за свою работу я возьму: " + WorkPrice + " сундуков с дублонами на рабочие расходы. Вроде бы всё. Ах да - деньги вперёд.";						
            dialog.Text = s2;
			Link.l1 = "Годится. Я принимаю условия. Всё оговоренное будет доставлено.";
			Link.l1.go = "ship_tunning_SpeedRate_start";
			Link.l2 = "Нет. Меня это не устраивает.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
			
		case "ship_tunning_SpeedRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Сундуки с дублонами были взяты из каюты: " + iSumm+ " шт.");
				}
				// <-- legendary edtion			
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType   	= Pchar.Ship.Type;
			    NPChar.Tuning.ShipName   	= RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
                dialog.text = "Вот и славно. Жду материалы.";
				link.l1 = LinkRandPhrase("Уверяю, ждать долго не придётся. Я умею решать такие задачки, смекаете?",
										 "Считайте, что они уже у вас и придержите док, я буду скор"+GetSexPhrase("","а")+", как ветер.",
										 "Не вопрос. Вот только навещу пару-тройку владельцев затребованного, ха-ха-ха!");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "За свою работу по увеличению скорости на " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" мастер-корабел требует: корабельного шёлка - " + NPChar.Tuning.Matherial + ". В качестве задатка было уплачено " + NPChar.Tuning.Money + " сундуков с дублонами.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Не вижу задатка...";
				link.l1 = "Я позже зайду.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_SpeedRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "Время идёт, а судно ждёт. Вы всё доставили, что я попросил?";
			    Link.l1 = "Да. Кое-что удалось достать.";
			    Link.l1.go = "ship_tunning_SpeedRate_again_2";
			    Link.l2 = "Нет. Ещё добываю.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Судар"+ GetSexPhrase("ь","ыня") +", вы поменяли корабль со времени нашего уговора? Напрасно.";
			    Link.l1 = "Увы, всему виной обстоятельства! Обидно, что задаток пропал...";
			    Link.l1.go = "Exit";		
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_SpeedRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Замечательно, теперь всё в наличии. Начинаю работу...";
			    link.l1 = "Жду.";
			    link.l1.go = "ship_tunning_SpeedRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "За вами осталось: корабельного шёлка - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Хорошо.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "Мне осталось довезти: корабельного шёлка - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_SpeedRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
			{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
			}
			else
			{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
			}		
	        shTo.Tuning.SpeedRate = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
	        // finish <--
            NextDiag.TempNode = "First time";
			dialog.Text = "... Вот и всё, капитан. Можете ловить ветер полными парусами. Хотите - проверьте!";
			Link.l1 = "Спасибо! Проверю обязательно.";
			Link.l1.go = "Exit";		
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// TurnRate ////////////////////////////////////////////////////
		case "ship_tunning_TurnRate":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			s2 = "Давайте посмотрим, что можно сделать. Сейчас манёвренность этого корабля - " + stf(RealShips[sti(Pchar.Ship.Type)].TurnRate);			
			s2 = s2 + " Для дополнительных парусов, чтоб его расшевелить, мне понадобится: канатов - "+ Material + ".";
			s2 = s2 + " В оплату за свою работу я возьму: " + WorkPrice + " сундуков с дублонами на рабочие расходы. Вроде бы всё. Ах да - деньги вперёд.";										
            dialog.Text = s2;
			Link.l1 = "Годится. Я принимаю условия. Всё оговоренное будет доставлено.";
			Link.l1.go = "ship_tunning_TurnRate_start";
			Link.l2 = "Нет. Меня это не устраивает.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_TurnRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Сундуки с дублонами были взяты из каюты: " + iSumm+ " шт.");
				}
				// <-- legendary edtion			
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
                dialog.text = "Вот и славно. Жду материалы.";
				link.l1 = LinkRandPhrase("Уверяю, ждать долго не придётся. Я умею решать такие задачки, смекаете?",
										 "Считайте, что они уже у вас и придержите док, я буду скор"+GetSexPhrase("","а")+", как ветер.",
										 "Не вопрос. Вот только навещу пару-тройку владельцев затребованного, ха-ха-ха!");			    
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "За свою работу по увеличению манёвренности на " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" мастер-корабел требует: канатов - " + NPChar.Tuning.Matherial + ". В качестве задатка было уплачено " + NPChar.Tuning.Money + " сундуков с дублонами.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Не вижу задатка...";
				link.l1 = "Я позже зайду.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_TurnRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "Время идёт, а судно ждёт. Вы всё доставили, что я попросил?";
			    Link.l1 = "Да. Кое-что удалось доставить.";
			    Link.l1.go = "ship_tunning_TurnRate_again_2";
			    Link.l2 = "Нет. Ещё добываю.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Судар"+ GetSexPhrase("ь","ыня") +", вы поменяли корабль со времени нашего уговора? Напрасно.";
			    Link.l1 = "Увы, всему виной обстоятельства! Обидно, что задаток пропал...";
			    Link.l1.go = "Exit";	
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_TurnRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Замечательно, теперь всё в наличии. Начинаю работу...";
			    link.l1 = "Жду.";
			    link.l1.go = "ship_tunning_TurnRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "За вами осталось: канатов - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Хорошо.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Мне осталось довезти: канатов - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_TurnRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_TurnRate"))
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/5.0);
			}
			else
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
			}	
	        shTo.Tuning.TurnRate = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4") && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Вроде всё... Оцените, каково теперь крутить штурвал, капитан!";
			Link.l1 = "Спасибо! Проверю обязательно.";
			Link.l1.go = "Exit";
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// MaxCrew ////////////////////////////////////////////////////
		case "ship_tunning_MaxCrew":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "Давайте посмотрим, что можно сделать. Сейчас максимальный экипаж вашего судна с учётом перегруза  " + sti(RealShips[sti(Pchar.Ship.Type)].MaxCrew) + " человек.";			
			s2 = s2 + " Мне понадобится: бакаута - "+ Material + ".";
			s2 = s2 + " В оплату за свою работу я возьму: " + WorkPrice + " сундуков с дублонами на рабочие расходы. Вроде бы всё. Ах да - деньги вперёд.";									
            dialog.Text = s2;
			Link.l1 = "Годится. Я принимаю условия. Всё оговоренное будет доставлено.";
			Link.l1.go = "ship_tunning_MaxCrew_start";
			Link.l2 = "Нет. Меня это не устраивает.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MaxCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Сундуки с дублонами были взяты из каюты: " + iSumm+ " шт.");
				}
				// <-- legendary edtion						
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
                dialog.text = "Вот и славно. Жду материалы.";
				link.l1 = LinkRandPhrase("Уверяю, ждать долго не придётся. Я умею решать такие задачки, смекаете?",
										 "Считайте, что они уже у вас и придержите док, я буду скор"+GetSexPhrase("","а")+", как ветер.",
										 "Не вопрос. Вот только навещу пару-тройку владельцев затребованного, ха-ха-ха!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "За свою работу по увеличению экипажа на " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" мастер-корабел требует: бакаута - " + NPChar.Tuning.Matherial + ". В качестве задатка было уплачено " + NPChar.Tuning.Money + " сундуков с дублонами.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Не вижу задатка...";
				link.l1 = "Я позже зайду.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MaxCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "Время идёт, а судно ждёт. Вы всё доставили, что я попросил?";
			    Link.l1 = "Да. Кое-что удалось достать.";
			    Link.l1.go = "ship_tunning_MaxCrew_again_2";
			    Link.l2 = "Нет. Ещё добываю.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Судар"+ GetSexPhrase("ь","ыня") +", вы поменяли корабль со времени нашего уговора? Напрасно.";
			    Link.l1 = "Увы, всему виной обстоятельства! Обидно, что задаток пропал...";				
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MaxCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Замечательно, теперь всё в наличии. Начинаю работу...";
			    link.l1 = "Жду.";
			    link.l1.go = "ship_tunning_MaxCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "За вами осталось: бакаута - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Хорошо.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Мне осталось довезти: бакаута - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MaxCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    
	        shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);
	        shTo.Tuning.MaxCrew = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
            TuningAvailable();
	       
            NextDiag.TempNode = "First time";
			dialog.Text = "... Исполнено, капитан. Набирайте матросов, всем места хватит.";
			Link.l1 = "Спасибо! Проверю обязательно.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;

		
		////////////////////////////////////////// MinCrew ////////////////////////////////////////////////////
		case "ship_tunning_MinCrew":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "Давайте посмотрим, что можно сделать. Сейчас минимальный экипаж вашего судна " + sti(RealShips[sti(Pchar.Ship.Type)].MinCrew) + " человек.";			
			s2 = s2 + " Для улучшения управляемости корабля и сокращения численности экипажа я возьму : канатов - "+ Material + ".";
			s2 = s2 + " В оплату за свою работу я возьму: " + WorkPrice + " сундуков с дублонами на рабочие расходы. Вроде бы всё. Ах да - деньги вперёд.";									
            dialog.Text = s2;
			Link.l1 = "Годится. Я принимаю условия. Всё оговоренное будет доставлено.";
			Link.l1.go = "ship_tunning_MinCrew_start";
			Link.l2 = "Нет. Меня это не устраивает.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MinCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Сундуки с дублонами были взяты из каюты: " + iSumm+ " шт.");
				}
				// <-- legendary edtion						
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
                dialog.text = "Вот и славно. Жду материалы.";
				link.l1 = LinkRandPhrase("Уверяю, ждать долго не придётся. Я умею решать такие задачки, смекаете?",
										 "Считайте, что они уже у вас и придержите док, я буду скор"+GetSexPhrase("","а")+", как ветер.",
										 "Не вопрос. Вот только навещу пару-тройку владельцев затребованного, ха-ха-ха!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "За свою работу по уменьшению минимальной численности экипажа на " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" мастер-корабел требует: канатов - " + NPChar.Tuning.Matherial + ". В качестве задатка было уплачено " + NPChar.Tuning.Money + " сундуков с дублонами.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Не вижу задатка...";
				link.l1 = "Я позже зайду.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MinCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "Время идёт, а судно ждёт. Вы всё доставили, что я попросил?";
			    Link.l1 = "Да. Кое-что удалось достать.";
			    Link.l1.go = "ship_tunning_MinCrew_again_2";
			    Link.l2 = "Нет. Ещё добываю.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Судар"+ GetSexPhrase("ь","ыня") +", вы поменяли корабль со времени нашего уговора? Напрасно.";
			    Link.l1 = "Увы, всему виной обстоятельства! Обидно, что задаток пропал...";
			    Link.l1.go = "Exit";	
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MinCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Замечательно, теперь всё в наличии. Начинаю работу...";
			    link.l1 = "Жду.";
			    link.l1.go = "ship_tunning_MinCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "За вами осталось: канатов - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Хорошо.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Мне осталось довезти: канатов - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MinCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
	        shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew)/5);
			if(sti(shTo.MinCrew) < 1) shTo.MinCrew = 1;
	        shTo.Tuning.MinCrew = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4")  && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Готово, капитан! Судно управляется меньшим числом матросов, да с тем же результатом.";
			Link.l1 = "Спасибо! Проверю обязательно.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// HP ////////////////////////////////////////////////////
		case "ship_tunning_HP":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Давайте посмотрим, что можно сделать. Корпус судна сейчас " + sti(RealShips[sti(Pchar.Ship.Type)].HP);			
			s2 = s2 + ". Чтобы укрепить обшивку, мне понадобится: смол - "+ Material + ".";
			s2 = s2 + " В оплату за свою работу я возьму: " + WorkPrice + " сундуков с дублонами - на рабочие расходы. Вроде бы всё. Ах да - деньги вперёд.";									
            dialog.Text = s2;
			Link.l1 = "Годится. Я принимаю условия. Всё оговоренное будет доставлено.";
			Link.l1.go = "ship_tunning_HP_start";
			Link.l2 = "Нет. Меня это не устраивает.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_HP_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Сундуки с дублонами были взяты из каюты: " + iSumm+ " шт.");
				}
				// <-- legendary edtion						
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_HP_again";
                dialog.text = "Вот и славно. Жду материалы.";
				link.l1 = LinkRandPhrase("Уверяю, ждать долго не придётся. Я умею решать такие задачки, смекаете?",
										 "Считайте, что они уже у вас и придержите док, я буду скор"+GetSexPhrase("","а")+", как ветер.",
										 "Не вопрос. Вот только навещу пару-тройку владельцев затребованного, ха-ха-ха!");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "За свою работу по увеличению прочности корпуса на " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" мастер-корабел требует: смол - " + NPChar.Tuning.Matherial + ". В качестве задатка было уплачено " + NPChar.Tuning.Money + " сундуков с дублонами.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Не вижу задатка...";
				link.l1 = "Я позже зайду.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_HP_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "Время идёт, а судно ждёт. Вы всё доставили, что я попросил?";
			    Link.l1 = "Да. Кое-что удалось достать.";
			    Link.l1.go = "ship_tunning_HP_again_2";
			    Link.l2 = "Нет. Ещё добываю.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Судар"+ GetSexPhrase("ь","ыня") +", вы поменяли корабль со времени нашего уговора? Напрасно.";
			    Link.l1 = "Увы, всему виной обстоятельства! Обидно, что задаток пропал...";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_HP_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_OIL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Замечательно, теперь всё в наличии. Начинаю работу...";
			    link.l1 = "Жду.";
			    link.l1.go = "ship_tunning_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "За вами осталось: смол - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Хорошо.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Мне осталось довезти: смол - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_HP"))
			{
				shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
			}
			else
			{
				shTo.HP        = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
			}	
	        shTo.Tuning.HP = true;
			shTo.BaseHP = sti(shTo.HP);
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
			TuningAvailable();
            
            NextDiag.TempNode = "First time";
			
			dialog.Text = "... Вроде бы всё... Гарантирую, что развалить этот кораблик теперь будет очень непросто!";
			Link.l1 = "Хех, верю на слово! Спасибо, мастер.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// WindAgainst ////////////////////////////////////////////////////
		case "ship_tunning_WindAgainst":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			fTmp = 180.0 - (stf(RealShips[sti(Pchar.Ship.Type)].WindAgainstSpeed) * 90.0);
			s2 = "Давайте посмотрим, что можно сделать. Курсовой угол " + makeint(fTmp) + " градусов.";
			// belamour legendary edition если спускать курс по ветру, то это даунгрейд
			s2 = s2 + " Чтобы привести к ветру преимущественный курс судна мне понадобится: корабельного шёлка - "+ Material + ",";
			s2 = s2 + " В оплату за свою работу я возьму: " + WorkPrice + " сундуков с дублонами на рабочие расходы. Вроде бы всё. Ах да - деньги вперёд.";									
            dialog.Text = s2;
			Link.l1 = "Говоря по-простецки, судно станет ходить быстрее против ветра? Годится. Я принимаю условия. Всё оговоренное будет доставлено.";
			Link.l1.go = "ship_tunning_WindAgainst_start";
			Link.l2 = "Нет. Меня это не устраивает.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;

		case "ship_tunning_WindAgainst_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Сундуки с дублонами были взяты из каюты: " + iSumm+ " шт.");
				}
				// <-- legendary edtion						
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial    	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.text = "Вот и славно. Жду материалы.";
				link.l1 = LinkRandPhrase("Уверяю, ждать долго не придётся. Я умею решать такие задачки, смекаете?",
										 "Считайте, что они уже у вас и придержите док, я буду скор"+GetSexPhrase("","а")+", как ветер.",
										 "Не вопрос. Вот только навещу пару-тройку владельцев затребованного, ха-ха-ха!");
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "За свою работу по изменению курсового угла на " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" мастер-корабел требует: корабельного шёлка - " + NPChar.Tuning.Matherial + ". В качестве задатка было уплачено " + NPChar.Tuning.Money + " сундуков с дублонами.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Не вижу задатка...";
				link.l1 = "Я позже зайду.";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_WindAgainst_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_WindAgainst_again";
			    dialog.Text = "Время идёт, а судно ждёт. Вы всё доставили, что я попросил?";
			    Link.l1 = "Да. Кое-что удалось доставить.";
			    Link.l1.go = "ship_tunning_WindAgainst_again_2";
			    Link.l2 = "Нет. Ещё добываю.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Судар"+ GetSexPhrase("ь","ыня") +", вы поменяли корабль со времени нашего уговора? Напрасно.";
			    Link.l1 = "Увы, всему виной обстоятельства! Обидно, что задаток пропал...";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_WindAgainst_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Замечательно, теперь всё в наличии. Начинаю работу...";
			    link.l1 = "Жду.";
			    link.l1.go = "ship_tunning_WindAgainst_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.Text = "За вами осталось: корабельного шёлка - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Хорошо.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Мне осталось довезти: корабельного шёлка - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;

		case "ship_tunning_WindAgainst_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим			
			// belamour legendary edtion чем больше WindAgainstSpeed, тем круче к ветру
	        shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) + 0.20 * stf(shTo.WindAgainstSpeed);	
			if (stf(shTo.WindAgainstSpeed) > 1.985) shTo.WindAgainstSpeed = 1.985;
	        shTo.Tuning.WindAgainst = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
	        // finish <--
            NextDiag.TempNode = "First time";
			dialog.Text = "... Сделано, кэп! Теперь это судно будет ходить против ветра куда как сноровистей.";
			Link.l1 = "Спасибо! Проверю обязательно.";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
						
		////////////////////////////////////////// только количество орудий  ////////////////////////////////////////////////////	
		case "ship_c_quantity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Давайте посмотрим, что можно сделать. Сейчас орудий на вашем корабле " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantity) + ", максимально возможное количество - " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax) + ".";			
			s2 = s2 + " Вам это дело обойдётся недёшево, мне понадобится: смол - "+ Material + ",";
			s2 = s2 + " В оплату за свою работу я возьму: " + WorkPrice + " сундуков с дублонами на рабочие расходы. Вроде бы всё. Ах да - деньги вперёд.";						
			dialog.Text = s2;		
			Link.l1 = "Годится. Я принимаю условия. Всё оговоренное будет доставлено.";
			Link.l1.go = "ship_c_quantity_start";		
			Link.l2 = "Нет. Меня это не устраивает.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_c_quantity_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Сундуки с дублонами были взяты из каюты: " + iSumm+ " шт.");
				}
				// <-- legendary edtion									
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Cannon 		= true;				
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 				
				NPChar.Tuning.ShipType      = Pchar.Ship.Type;
				NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;											    
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.text = "Вот и славно. Жду материалы.";
				link.l1 = LinkRandPhrase("Уверяю, ждать долго не придётся. Я умею решать такие задачки, смекаете?",
										 "Считайте, что они уже у вас и придержите док, я буду скор"+GetSexPhrase("","а")+", как ветер.",
										 "Не вопрос. Вот только навещу пару-тройку владельцев затребованного, ха-ха-ха!");
				link.l1.go = "Exit";			    
				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "За свою работу по увеличению количества орудий на " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +						
				" мастер-корабел требует: смол - " + NPChar.Tuning.Matherial + ". В качестве задатка было уплачено " + NPChar.Tuning.Money + " сундуков с дублонами.");				
			}		
			else
			{ 
				NextDiag.TempNode = "ship_tunning_not_now_1";
				dialog.text = "Не вижу задатка...";
				link.l1 = "Я позже зайду.";
				link.l1.go = "Exit";
			}
		break;		
		
		case "ship_c_quantity_again":	
			if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "Время идёт, а судно ждёт. Вы всё доставили, что я попросил?";
				Link.l1 = "Да. Кое-что удалось достать.";
				Link.l1.go = "ship_c_quantity_again_2";
				Link.l2 = "Нет. Ещё добываю.";
				Link.l2.go = "Exit";
			}		
			else
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.Text = "Судар"+ GetSexPhrase("ь","ыня") +", вы поменяли корабль со времени нашего уговора? Напрасно.";
			    Link.l1 = "Увы, всему виной обстоятельства! Обидно, что задаток пропал...";
				Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
				AddQuestRecord("ShipTuning", "Lose");
				CloseQuestHeader("ShipTuning");
			}		
		break;
		
		case "ship_c_quantity_again_2":		
			checkMatherial(Pchar, NPChar, GOOD_OIL);
			if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.text = "Замечательно, теперь всё в наличии. Начинаю работу...";
				link.l1 = "Жду.";
				link.l1.go = "ship_c_quantity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "Тебе осталось привезти: смол - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Хорошо.";
				link.l1.go = "Exit";
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Мне осталось довезти: смол - "+ sti(NPChar.Tuning.Matherial) + ".");
			}		
		break;
		
		case "ship_c_quantity_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			DeleteAttribute(NPChar, "Tuning");		
			makearef(refShip, pchar.Ship);
			
			iCannonDiff = sti(refShip.CannonDiff);
			iCannonDiff -= 1;
								
			for (i = 0; i < sti(shTo.cannonr); i++)
			{
				attr = "c" + i;										
					
				if(i < (sti(shTo.cannonr) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonr.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonr.damages.(attr) = 1.0; 
					}	
				}					
			}	
			for (i = 0; i < sti(shTo.cannonl); i++)
			{
				attr = "c" + i;
				if(i < (sti(shTo.cannonl) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonl.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonl.damages.(attr) = 1.0; 
					}	
				}										
			}	
			
			if(CheckAttribute(shTo,"CannonsQuantityMax")) 	shTo.Cannons = sti(shTo.CannonsQuantityMax) - iCannonDiff * 2;
			else										    shTo.Cannons = sti(shTo.CannonsQuantity) - iCannonDiff * 2;
			
			shTo.CannonsQuantity = sti(shTo.Cannons);
		
			refShip.Cannons = sti(shTo.Cannons);
			refShip.CannonDiff = iCannonDiff;			

			shTo.Tuning.Cannon = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			NextDiag.TempNode = "First time";
			dialog.Text = "...Вот и делу конец. Можете выкатывать дополнительные орудия. Если они есть, хе-хе...";
			Link.l1 = "Спасибо!";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		case "Tasks":
			//--> Jason генератор Поиск корабля
			if (drand(4) == 2 && !CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && sti(pchar.rank) < 19)
			{
				if (!CheckAttribute(npchar, "Findship") || GetNpcQuestPastDayParam(npchar, "Findship") >= 60) 
				{
					SelectFindship_ShipType(); //выбор типа корабля
					pchar.GenQuest.Findship.Shipyarder.ShipBaseName =  GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Findship.Shipyarder.ShipType), "Name") + "Acc")); // new
					pchar.GenQuest.Findship.Shipyarder.City = npchar.city; //город квестодателя
					dialog.text = "У меня есть проблема, требующая решения. Мне поступил заказ на корабль - "+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+". Однако у меня на верфи сейчас такого корабля нет, сделать его за два месяца у меня тоже нет возможности\nЕсли вы сможете доставить мне такой корабль - буду очень благодарен, и заплачу сумму, в полтора раза превышающую его продажную стоимость.";
					link.l1 = "Интересное предложение. Я соглас"+GetSexPhrase("ен","на")+"!";
					link.l1.go = "Findship";
					link.l2 = "Мне это не интересно.";
					link.l2.go = "Findship_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Findship");
					break;
				}
				
			}//<-- генератор Поиск корабля
			//Jason --> генератор Неудачливый вор
			if (drand(6) == 1 && !CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && sti(pchar.rank) < 10 && npchar.city != "Charles")
			{
				if (!CheckAttribute(npchar, "Device")) 
				{
					switch (crand(4))
					{
						case 0:  
							pchar.GenQuest.Device.Shipyarder.Type = "нутромер";
							pchar.GenQuest.Device.Shipyarder.Describe = "две кованые полоски, соединённые шарниром, расклёпанным на концах";
						break; 
						case 1:  
							pchar.GenQuest.Device.Shipyarder.Type = "потёс";
							pchar.GenQuest.Device.Shipyarder.Describe = "топор на длинной круглой прямой рукояти с тонким полукруглым лезвием";
						break; 
						case 2:  
							pchar.GenQuest.Device.Shipyarder.Type = "пазник";
							pchar.GenQuest.Device.Shipyarder.Describe = "небольшой такой топор, похожий на крестьянскую мотыгу";
						break; 
						case 3:  
							pchar.GenQuest.Device.Shipyarder.Type = "стапельный уровень";
							pchar.GenQuest.Device.Shipyarder.Describe = "выглядит, как две деревянных перекладины равной длины, соединённые такой же третьей, в центре которой находится вращающаяся плашка с пузырьком";
						break;
						case 4:  
							pchar.GenQuest.Device.Shipyarder.Type = "барсик";
							pchar.GenQuest.Device.Shipyarder.Describe = "похож на обычный цеп, только цепь у него особенная, стержневая, и двигается в одном направлении";
						break; 
					}
					dialog.text = "Вы очень вовремя. Быть может, вы сможете мне помочь. У меня буквально вчера украли ценный инструмент - "+pchar.GenQuest.Device.Shipyarder.Type+". Второго такого у меня нет, и изготовить возможности нет - я заказывал его в Европе за немалые деньги. А без него я не могу нормально строить корабли, понимаете?\nИ что самое обидное - эта штука никому, кроме корабелов, не нужна, а я в колонии единственный корабел. Этот вор никому её не продаст и просто выбросит. Может, вы попробуете разыскать вора, поспрашиваете в городе, а мне просто некогда отлучаться с верфи - надо срочно доводить до ума спецзаказ.";
					link.l1 = "Хорошо. Я попробую. Только опишите мне, как выглядит этот ваш... Прибор.";
					link.l1.go = "Device";
					link.l2 = "Мне это не интересно.";
					link.l2.go = "Device_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Device");
					break;
				}//<-- генератор Неудачливый вор
			}
			dialog.text = "Ничего такого у меня нет.";
			link.l1 = "Как скажете.";
			link.l1.go = "exit";
		break;
		
		case "Findship_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		
		case "Device_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		
		//--> Jason генератор Поиск корабля
		case "Findship":
			pchar.GenQuest.Findship.Shipyarder = "begin";
			pchar.GenQuest.Findship.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Findship.Shipyarder.City = npchar.city;
			ReOpenQuestHeader("Findship");
			AddQuestRecord("Findship", "1");
			AddQuestUserData("Findship", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Findship.Shipyarder.City+"Gen"));
			AddQuestUserData("Findship", "sName", pchar.GenQuest.Findship.Shipyarder.Name);
			AddQuestUserData("Findship", "sShip", pchar.GenQuest.Findship.Shipyarder.ShipBaseName);
			SetFunctionTimerCondition("Findship_Over", 0, 0, 60, false);
			DialogExit();
		break;
		
		case "Findship_check":
			dialog.text = "Отлично! Рад, что вы так быстро управились. Где этот корабль?";
			link.l1 = "Судно стоит на рейде, называется '"+pchar.GenQuest.Findship.Shipyarder.ShipName+"'.";
				link.l1.go = "Findship_complete";
				break;
		
		case "Findship_complete":
			pchar.quest.Findship_Over.over = "yes";//снять прерывание
			sld = GetCharacter(sti(pchar.GenQuest.Findship.Shipyarder.CompanionIndex));
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			dialog.text = "Вот ваши деньги - "+FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money))+". Спасибо за проделанную работу. Не забывайте заглядывать ко мне. До свидания!";
			link.l1 = "До свидания, " + npchar.name + ".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Findship.Shipyarder.Money));
			AddQuestRecord("Findship", "3");
			AddQuestUserData("Findship", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money)));
			CloseQuestHeader("Findship");
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		//<-- генератор Поиск корабля
		
		//Jason --> генератор Неудачливый вор
		case "Device":
			pchar.GenQuest.Device.Shipyarder.Chance1 = rand(6);
			pchar.GenQuest.Device.Shipyarder.Chance2 = rand(3);
			pchar.GenQuest.Device.Shipyarder.Chance3 = rand(2);
			pchar.GenQuest.Device.Shipyarder.Chance4 = rand(4);
			pchar.GenQuest.Device.Shipyarder.Money = 12000+rand(8000);
			//генерируем тип корабля для бонуса сейчас, чтобы не сливали
			if (sti(pchar.rank) < 2) iType = SHIP_SCHOONER; 
			if (sti(pchar.rank) >= 2 && sti(pchar.rank) < 5) iType = SHIP_BRIGANTINE; 
			if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 7) iType = SHIP_BRIG; 
			if (sti(pchar.rank) >= 7) iType = SHIP_CORVETTE + rand(makeint(SHIP_GALEON_H - SHIP_CORVETTE)); 
			pchar.GenQuest.Device.Shipyarder.Bonus = iType;
			dialog.text = "Да, конечно, постараюсь объяснить понятнее. Это "+pchar.GenQuest.Device.Shipyarder.Describe+". Этот прибор единственный в своём роде, так что узнать его будет легко. Если вернёте инструмент - я хорошо заплачу вам.";
			link.l1 = "Понятно. Приступаю к поискам!";
			link.l1.go = "exit";
			pchar.GenQuest.Device.Shipyarder = "begin";
			pchar.GenQuest.Device.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Device.Shipyarder.City = npchar.city;
			pchar.GenQuest.Device.Shipyarder.Nation = npchar.Nation;
			ReOpenQuestHeader("Device");
			AddQuestRecord("Device", "1");
			AddQuestUserData("Device", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Device.Shipyarder.City+"Voc"));
			AddQuestUserData("Device", "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			AddQuestUserData("Device", "sDesc", pchar.GenQuest.Device.Shipyarder.Describe);
			SetFunctionTimerCondition("Device_Over", 0, 0, 30, false);
		break;
		
		case "Device_complete":
			pchar.quest.Device_Over.over = "yes";//снять прерывание
			dialog.text = "Вы сделали это! Как же я вам благодарен! А то я уже отчаялся когда-либо вернуть свой инструмент.";
			link.l1 = "Вот, держите.";
			link.l1.go = "Device_complete_1";
		break;
		
		case "Device_complete_1":
			RemoveItems(PChar, "Tool", 1);
			dialog.text = "Я заплачу вам за работу "+FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money))+". Надеюсь, это достойная награда за ваши труды.";
			link.l1 = "Спасибо!";
			link.l1.go = "Device_complete_2";
		break;
		
		case "Device_complete_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Device.Shipyarder.Money));
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddQuestRecord("Device", "10");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money)));
			CloseQuestHeader("Device");
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance4) == 3)
			{
				dialog.text = "Кроме того, я хочу сделать вам предложение, в качестве дополнительной благодарности.";
				link.l1 = "Интересно! Давайте послушаем, я люблю приятные сюрпризы.";
				link.l1.go = "Device_complete_3";
			}
			else
			{
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
		break;
		
		case "Device_complete_3":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			dialog.text = "Я только что спустил со стапелей на воду новый корабль - "+ GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(iType, "Name") + "Acc")) +". На это судно уже есть несколько покупателей, но я предоставляю вам право первой очереди. Если вам понравится это судно, и не испугает цена - вы можете его приобрести.";
			link.l1 = "Хех! Конечно, давайте посмотрим!";
			link.l1.go = "Device_complete_4";
			link.l2 = "Спасибо, но меня более чем устраивает мой нынешний корабль, и менять я его пока не намерен"+GetSexPhrase("","а")+".";
			link.l2.go = "Device_complete_5";
		break;
		
		case "Device_complete_4":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_TARTANE, NPChar), "ship1");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship2");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship3");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(iType, NPChar), "ship10");
			DialogExit();
			LaunchShipyard(npchar);
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			SaveCurrentNpcQuestDateParam(npchar, "shipyardDate"); // лесник , митрокоста
		break;
		
		case "Device_complete_5":
			dialog.text = "Ну, как знаете. Ещё раз спасибо и всего доброго!";
			link.l1 = "И вам удачи!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		// <-- генератор Неудачливый вор
		
		case "ShipLetters_6":
			pchar.questTemp.different.GiveShipLetters.speakShipyard = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Дайте-ка взглянуть ! Нет, таковой у меня не был. Думаю, Вам стоит зайти к начальнику порта.";
				link.l1 = "Несомненно....";
				link.l1.go = "exit";
			}
			else
			{
				sTemp = "Дайте-ка взглянуть, капитан! Ага! Это же судовые документы моего хорошего друга, можно сказать, самого любимого клиента. Я уверен, он будет несказанно рад находке, и даже выплатит премиальные.";
				sTemp = sTemp + "Думаю, что могу Вам предложить " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " песо от его имени";
				dialog.text = sTemp;
				link.l1	= "Пожалуй, не стоит ...";
				link.l1.go = "exit";
				link.l2 = "Благодарю, " + GetFullName(NPChar) + "! Передавайте поклон Вашему другу.";
				link.l2.go = "ShipLetters_7";				
			}	
		break;

		case "ShipLetters_7":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "4");		
			AddQuestUserData("GiveShipLetters", "sSex", GetSexPhrase("","а"));		
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = "Слушаю вас внимательно.";
			link.l1 = "Я привёл"+ GetSexPhrase("","а") +" вашу беглянку.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Ах, капитан, спасибо вам большое! Как она? здорова, не пострадала? Уж скоро сутки, как убежала, негодница. Разве ж я ей плохого желаю? Замуж отдать собрался... Жених богатый, молодой, а что собою не пригож, так ведь с лица воду не пить. Нет! она всё по-своему норовит - вся в мать, чтоб её...\nХотя, и она бы на свет не появилась, если бы её мамаша в своё время не сбежала с одним предприимчивым оболтусом... ну да что вспоминать... Молодость наивна, глупа... и жестока.";
			link.l1 = "Конечно, вы отец и решать вам, но я бы не торопил"+ GetSexPhrase("ся","ась") +" со свадьбой...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Да что вы понимаете?.. У вас свои дети есть? Нету? Вот, когда будут - заходите, тогда и поговорим...\nДа... я обещал вознаграждение тому, кто её вернет - примите пожалуйста.";
			link.l1 = "Спасибо. И держите её покрепче. Что-то мне подсказывает, что она на этом не остановится.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;		
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "А, так вы и есть "+ GetSexPhrase("тот капитан, который привёз","та девушка, которая привезла") +", моего блудного сына с молодой невестой?";
				link.l1 = "Да, это я помог"+ GetSexPhrase("","ла") +" им сбежать.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "А-а, явил"+ GetSexPhrase("ся, благодетель","ась, благодетельница") +". Небось награды ждёшь?";
				link.l1 = "Ну, не то, чтобы награды, но благодарность услышать не мешало бы.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Я очень вам благодарен, что не оставили моё чадо в затруднительном положении и помогли ему с честью выйти из столь щекотливой ситуации. Разрешите отблагодарить вас - примите эту скромную сумму и подарок от меня лично.";
			link.l1 = "Благодарю вас, мне было приятно помогать этим молодым людям.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Какая благодарность?! за что благодарность?! Мало того, что этот оболтус уже полгода слоняется без работы, так ещё и любезничать время нашёл! Да я в его годы уже своё дело держал. А он, ишь, разохотился! У губернатора, вон, дочка на выданье, а этот приволок какую-то шалаву безродную, прости Господи, и благословения родительского испрашивает!";
			link.l1 = "Хм, значит вы не верите в искренние чувства?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Какие такие чувства?! О каких чувствах вы говорите? Взрослый, вроде человек, а туда же... чувства! Стыдно вам должно быть молодежи в таких делах потакать, да в сводни подряжаться. Девчонку из родительского гнезда вырвали и моему молокососу жизнь сломали. Не будет вам никакой благодарности. Прощайте.";
			link.l1 = "Что ж, и вам не хворать...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ёл","ла"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("","а"));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		case "shipyard":
			if(CheckAttribute(npchar, "TrialDelQuestMark"))
			{
				DeleteAttribute(npchar, "TrialDelQuestMark");
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("PortRoyal");
			}
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchShipyard(npchar);
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Дуришь меня? А где же твой корабль? У пирса его нет!",
				                                                     "Клянусь дьяволом, тебе не обмануть меня! У пирса нет твоего корабля!"),
													  pcharrepphrase("Я не вижу вашего корабля в порту, капитан " +GetFullName(pchar)+ ". Надеюсь, это не 'Летучий голландец'?",
													                 "Капитан, удобнее грузить товар с пирса. Пришвартуйте корабль и приходите."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"Какая неприятность!!! Ладно, старый проныра, ещё увидимся!",
				                                                 "Я не хотел"+ GetSexPhrase("","а") +" вас обмануть " +GetFullName(npchar)+ ", корабль на другой стороне острова."),
												  pcharrepphrase("Нет. Мой корабль называется Black Perl. Что это ты побелел? Ха-ха! Шутка!",
												                 "Спасибо за совет, обязательно им воспользуюсь."));
			    link.l1.go = "exit";
			}
		break;
		
		case "Cannons":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
    			LaunchCannons(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Дуришь меня? А где же твой корабль? У пирса его нет!",
				                                                     "Клянусь дьяволом, тебе не обмануть меня! У пирса нет твоего корабля!"),
													  pcharrepphrase("Я не вижу вашего корабля в порту, капитан " +GetFullName(pchar)+ ". Надеюсь, это не 'Летучий голландец'?",
													                 "Капитан, удобнее грузить товар с пирса. Пришвартуйте корабль и приходите."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"Какая неприятность!!! Ладно, старый проныра, ещё увидимся!",
				                                                 "Я не хотел"+ GetSexPhrase("","а") +" вас обмануть " +GetFullName(npchar)+ ", корабль на другой стороне острова."),
												  pcharrepphrase("Нет. Мой корабль называется Black Perl. Что это ты побелел? Ха-ха! Шутка!",
												                 "Спасибо за совет, обязательно им воспользуюсь."));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsGerald":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    dialog.text = "Сменить цвет парусов стоит " +
				              FindRussianDublonString(GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE)/100)+
							  ", поставить новый герб стоит " +
							  FindRussianDublonString(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE)/100) +
							  ", сменить паруса - зависит от того, какой у вас корабль.";
							  
			    link.l1 = "Выбрать новый цвет.";
			    link.l1.go = "SailsColorChoose";
			    link.l2 = "Изобразить новый герб.";
			    link.l2.go = "SailsGeraldChoose";
				link.l3 = "Установить уникальные паруса."; 
				link.l3.go = "SailsTypeChoose";
			    Link.l9 = "Я передумал"+ GetSexPhrase("","а") +".";
				Link.l9.go = "exit";
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Дуришь меня? А где же твой корабль? У пирса его нет!","Клянусь дьяволом, тебе не обмануть меня! У пирса нет твоего корабля!"),pcharrepphrase("Я не вижу вашего корабля в порту, капитан " +GetFullName(pchar)+ ". Надеюсь, это не 'Летучий голландец'?","Капитан, удобнее грузить товар с пирса. Пришвартуйте корабль и приходите."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"Какая неприятность!!! Ладно, старый проныра, ещё увидимся!","Я не хотел"+ GetSexPhrase("","а") +" вас обмануть " +GetFullName(npchar)+ ", корабль на другой стороне острова."), pcharrepphrase("Нет. Мой корабль называется Black Pearl. Что это ты побелел? Ха-ха! Шутка!","Спасибо за совет, обязательно им воспользуюсь."));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsTypeChoose":
			dialog.text = "Какие паруса ставим? У тебя сейчас " + GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+".";
            Link.l6 = "Я хочу поставить "+GetSailsType(6) + ".";
			Link.l6.go = "SailsTypeChooseIDX_6";
			Link.l7 = "Я хочу поставить "+GetSailsType(7)  + ".";
			Link.l7.go = "SailsTypeChooseIDX_7";
			Link.l8 = "Я хочу поставить "+GetSailsType(8)  + ".";
			Link.l8.go = "SailsTypeChooseIDX_8";
			Link.l9 = "Я хочу поставить "+GetSailsType(9)  + ".";
			Link.l9.go = "SailsTypeChooseIDX_9";
			Link.l10 = "Я хочу поставить "+GetSailsType(10)  + ".";
			Link.l10.go = "SailsTypeChooseIDX_10";
			Link.l11 = "Я хочу поставить "+GetSailsType(11)  + ".";
			Link.l11.go = "SailsTypeChooseIDX_11";
			attrLoc = "l" + sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails);
			DeleteAttribute(Link, attrLoc);
		    Link.l99 = "Я передумал"+ GetSexPhrase("","а") +".";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChoose2":
            NPChar.SailsTypeMoney = GetSailsTypePrice(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails),
			                                          sti(NPChar.SailsTypeChooseIDX),
													  stf(NPChar.ShipCostRate),
													  sti(RealShips[sti(Pchar.Ship.Type)].Price));
													  
			dialog.text = "У тебя сейчас "+GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+", ты выбрал"+GetSexPhrase("","а")+" "+ GetSailsType(sti(NPChar.SailsTypeChooseIDX))+". Стоимость замены "+ FindRussianDublonString(sti(NPChar.SailsTypeMoney)/100) +". Меняем?";

			if (sti(NPChar.SailsTypeMoney)/100 <= PCharDublonsTotal())
			{
	            Link.l1 = "Да.";
				Link.l1.go = "SailsTypeChooseDone";
			}
		    Link.l99 = "Нет.";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChooseDone":
			RemoveDublonsFromPCharTotal(sti(NPChar.SailsTypeMoney)/100);
			dialog.text = "Замечательно! Всё сделаем в лучшем виде.";
		    Link.l9 = "Спасибо.";
			Link.l9.go = "exit";

			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = sti(NPChar.SailsTypeChooseIDX);
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsColorChoose":
			if (GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE)/100 <= PCharDublonsTotal())
			{
				dialog.text = "Какой цвет ставим? Цена " + FindRussianDublonString(GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE)/100) + ".";
				for (i = 0; i < SAILS_COLOR_QUANTITY; i++)
				{
					if (CheckSailsColor(Pchar, i))
					{
						attrLoc = "l" + i;
						Link.(attrLoc) = XI_ConvertString(SailsColors[i].name);
						Link.(attrLoc).go = "SailsColorIdx_" + i;
					}
				}
			    Link.l99 = "Я передумал"+ GetSexPhrase("","а") +".";
				Link.l99.go = "exit";
			}
			else
			{
				dialog.text = "Приходи, когда деньги будут.";
			    Link.l9 = "Хорошо.";
				Link.l9.go = "exit";	
			}
		break;
		
		case "SailsColorDone":
			RemoveDublonsFromPCharTotal(GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE)/100);
			dialog.text = "Договорились. Красим паруса в "+ GetStrSmallRegister(XI_ConvertString(SailsColors[sti(NPChar.SailsColorIdx)].name)) +" цвет.";
		    Link.l9 = "Спасибо.";
			Link.l9.go = "exit";
			
			SetSailsColor(Pchar, sti(NPChar.SailsColorIdx));
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsGeraldChoose":
			if(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE)/100 <= PCharDublonsTotal())
			{
				if(CheckSailsGerald(Pchar) && CanSetSailsGerald(PChar)) // Warship fix 04.06.09
				{
					NextDiag.CurrentNode = NextDiag.TempNode;
					DialogExit();
					LaunchSailsGeraldScreen(npchar);
				}
				else
				{
				    dialog.text = "К сожалению, на твой корабль нельзя установить герб.";
				    Link.l9 = "Жаль.";
					Link.l9.go = "exit";
				}
			}
			else
			{
				dialog.text = "Приходи, когда деньги будут.";
			    Link.l9 = "Хорошо.";
				Link.l9.go = "exit";	
			}
		break;

//--> -------------------------------------------Бремя гасконца---------------------------------------------------
		case "Sharlie":
			dialog.text = "Вынужден вас огорчить, месье. У меня на данный момент совсем нет кораблей на продажу.";
			link.l1 = "Это очень странно, так как мне сказали, что у вас на верфи сейчас есть новый люггер.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
			{
				dialog.text = "Вы это сейчас наверное про люггер, за который внёс залог в три тысячи песо Мишель де Монпе? Так этот корабль уже продан, потому что согласно договору, полная сумма должна была быть выплачена не позднее, чем за неделю после спуска корабля на воду\nВсе сроки прошли, денег я так и не увидел, поэтому люггер был продан. Так что не обессудьте, сударь.";
				link.l1 = "Да, вот как неудачно-то вышло... А другого корабля у вас точно нет?";
				link.l1.go = "Sharlie_6";
			}
			else
			{
			dialog.text = "Хм. Да, действительно. Но...";
			link.l1 = "И за него внесён залог - пять тысяч песо. Мишель де Монпе, внесший эти деньги, передаёт все права на этот корабль мне.";
			link.l1.go = "Sharlie_2";
			}
		break;
		
		case "Sharlie_2":
			int iDay = 3-sti(GetQuestPastDayParam("questTemp.Sharlie_ship"));
			sTemp = "У вас осталось "+FindRussianDaysString(iDay)+"";
			if (iDay == 0) sTemp = "Сегодня - последний день";
			dialog.text = "Ну, раз такое дело, тогда продолжим нашу беседу, месье. Как вы правильно заметили, было внесено за корабль пять тысяч песо. Но полную стоимость корабля я оцениваю в пятнадцать тысячи песо, вместе с боеприпасом. Так что с вас ещё десять тысяч - и корабль ваш\nПричём, согласно договору, вы должны выплатить эти деньги не позднее, чем через неделю после спуска корабля на воду. "+sTemp+", после чего я имею право продать этот корабль другому лицу. Кстати, покупатель уже есть, так что вам следует поторопиться.";
			if (sti(Pchar.money) >= 10000)
			{
				link.l1 = "Никуда мне торопиться не надо. У меня есть нужная сумма прямо сейчас. Вот, держите.";
				link.l1.go = "Sharlie_4";
			}
			link.l2 = "Хорошо. Будут у вас эти деньги, месье. Я не заставлю себя долго ждать.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
			{
				dialog.text = "Вы что-то хотели, месье?";
				Link.l1 = "Я пришёл посмотреть корабли, какие у вас есть... Но сейчас я немного занят - дело одно незаконченное осталось. Я ещё загляну попозже, как только разберусь с ним.";
				Link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
			{	
				if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
				{
					dialog.text = "Месье, я же предупреждал, что у вас всего три дня. Они истекли, денег вы не принесли, договор утратил силу. Я продал корабль другому человеку, так что не обессудьте.";
					link.l1 = "Да, вот как неудачно-то вышло... А другого корабля у вас точно нет?";
					link.l1.go = "Sharlie_6";
				}
				else
				{
					dialog.text = "Вы принесли десять тысяч, месье?";
					if (sti(Pchar.money) >= 10000)
					{
						link.l1 = "Да, конечно. Вот, держите.";
						link.l1.go = "Sharlie_4";
					}
					link.l2 = "Нет, я ещё работаю над этим.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Sharlie_3";
				}
			}
		break;
		
		case "Sharlie_4":
			AddMoneyToCharacter(pchar, -10000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "Тогда поздравляю вас с удачной покупкой. Корабль ваш. Думаю, он послужит вам верой и правдой.";
			link.l1 = "Спасибо!";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "lugger";
			pchar.questTemp.Sharlie = "crew";
			//стартовый люггер
			pchar.Ship.Type = GenerateShipHand(pchar, SHIP_LUGGER, 6, 800, 40, 610, 16000, 15.2, 58.8, 1.42);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			/* UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew");
			UpgradeShipParameter(pchar, "Capacity");
			//UpgradeShipParameter(pchar, "Cannons");
			pchar.ship.HP = 732; */
			//UpgradeShipFull(pchar);
			UpgradeShipParameter(pchar, "Capacity");
			RealShips[sti(pchar.Ship.Type)].ship.upgrades.hull  = "q"; // belamour особый скин
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddCharacterGoods(pchar, GOOD_BALLS, 100);
			AddCharacterGoods(pchar, GOOD_GRAPES, 100);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			AddCharacterGoods(pchar, GOOD_BOMBS, 100);
			AddCharacterGoods(pchar, GOOD_POWDER, 220);
			pchar.Ship.name = "Аделина";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS6;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_6":
			if (sti(Pchar.money) >= 15000)
				{
					dialog.text = "Хм. В общем-то, есть, да только не знаю, устроит ли он вас.";
					link.l1 = "Сейчас мне не до капризов. Говорите, что там у вас?";
					link.l1.go = "Sharlie_7";
				}
				else
				{
					dialog.text = "Послушайте, месье, вы сначала деньгами разживитесь, а потом о кораблях спрашивайте. За бесплатно вам тут никто ничего не предоставит, надеюсь, это понятно?";
					link.l1 = "Понятно, хотя грубить было вовсе и не обязательно. Хорошо, я вернусь, когда будут деньги.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Sharlie_shipwait";
				}
		break;
		
		case "Sharlie_7":
			dialog.text = "Тогда смотрите. Недавно я приобрёл по сходной цене шлюп. Это бывшая пиратская посудина, её прежних владельцев уже благополучно вздернули за многочисленные прегрешения. Корабль, прямо скажу, не ах, да и повреждён прилично, но в море выйти сможет\nМне некогда им сейчас заниматься - все мои работники заняты постройкой под заказ брига, так что можете купить его у меня в том состоянии, в каком он есть. Учитывая сказанное, уступлю дешевле обычного - пятнадцать тысяч песо, и это вместе с содержимым трюма.";
			link.l1 = "Я согласен. Главное - что сможет выйти в море, а до Гваделупы здесь рукой подать. Там и починю его, раз у вас нет возможности.";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			AddMoneyToCharacter(pchar, -15000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "Тогда поздравляю с покупкой. Корабль ваш. Думаю, он ещё послужит вам верой и правдой.";
			link.l1 = "Спасибо!";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "sloop";
			pchar.questTemp.Sharlie = "crew";
			//стартовый шлюп
			pchar.Ship.Type = GenerateShipHand(SHIP_SLOOP, 6, 800, 50, 790, 20000, 13.1, 50.1, 1.25);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew");
			UpgradeShipParameter(pchar, "Capacity");
			AddCharacterGoods(pchar, GOOD_BALLS, 51);
			AddCharacterGoods(pchar, GOOD_GRAPES, 39);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 54);
			AddCharacterGoods(pchar, GOOD_BOMBS, 36);
			AddCharacterGoods(pchar, GOOD_POWDER, 231);
			pchar.Ship.name = "Чёрный пёс";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS3;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_shipwait":
			dialog.text = "Ну, месье, вы всё-таки вернулись с деньгами?";
			if (sti(Pchar.money) >= 15000)
			{
				link.l1 = "Да, думаю, у меня есть достаточная сумма для покупки хоть какого-то захудалого корабля.";
				link.l1.go = "Sharlie_7";
			}
			else
			{
				link.l1 = "У меня ещё нет достаточной суммы. Просто зашёл посмотреть...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_shipwait";
			}
		break;
//<-- -----------------------------------------Бремя гасконца-----------------------------------------------------
		// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
		case "FMQM_oil_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto5", "FMQM_Looking", -1);
			pchar.questTemp.FMQM = "remove_oil1";
		break;
		
		case "FMQM_oil_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil2";
		break;
		
		case "FMQM_oil_3":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil3";
		break;
		
		case "FMQM_oil_4":
			dialog.text = "Увы, монсеньор, но тут мы с вами погорели оба. Смолы конфискованы, и я впридачу потерял кругленькую сумму, дабы откупиться от тюрьмы. И откуда только эта чёртова солдатня пронюхала? Наверняка, кто-то из моих работников подсмотрел и донёс. Но я с этим ещё разберусь, и если отыщу негодяя - мало ему не покажется!";
			link.l1 = "Значит, все мои старания были напрасны...";
			link.l1.go = "FMQM_oil_5";
		break;
		
		case "FMQM_oil_5":
			dialog.text = "Мне очень жаль, капитан. Но что же теперь сделать - это превратности судьбы.";
			link.l1 = "Ясно. Ладно, мастер, тогда я пойду. Всего доброго!";
			link.l1.go = "FMQM_oil_6";
		break;
		
		case "FMQM_oil_6":
			DialogExit();
			AddQuestRecord("FMQ_Martinique", "12");
			pchar.questTemp.FMQM = "officer";
			pchar.quest.FMQM_advice.win_condition.l1 = "location";
			pchar.quest.FMQM_advice.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FMQM_advice.function = "FMQM_GuideAdvice";
			DeleteAttribute(pchar, "questTemp.FMQM.Oil");
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_x":
            dialog.text = "Я бы хотел вернуться к нашему разговору. Я готов предоставить вам очень большую скидку на работу над вашим судном... очень большую скидку в песо... если вы предоставите для работы неколько... больше шёлка...";
			link.l1 = "Мастер, не будем вилять. Я клянусь вам, что я не шпион, и не человек полковника д'Ойли. Более того - я работаю с Маркусом Тираксом, а это имя наверняка вам что-то да и говорит. Поэтому давайте начистоту. Я знаю, что вам постоянно нужен корабельный шёлк, а Маркус Тиракс готов вам его поставлять. Тоже постоянно. Однако только в том случае, если мы сойдёмся в цене. Так что давайте обсудим денежный вопрос, мастер.";
			link.l1.go = "mtraxx_x_1";
		break;
		
		case "mtraxx_x_1":
            dialog.text = "Хорошо. Мне всё равно деваться некуда - или в тюрьму, если вы человек д'Ойли, или на паперть, если срочно не найду большую партию шёлка. Я готов платить за шёлк золотом, по 25 дублонов за рулон. Но это при учёте крупных партий, по 100 рулонов или около того.";
			link.l1 = "Такая цена меня устраивает. Думаю, Тиракс сможет поставлять объёмы не менее 100 рулонов ежемесячно.";
			link.l1.go = "mtraxx_x_2";
		break;
		
		case "mtraxx_x_2":
            dialog.text = "Это было бы просто замечательно! Первую партию я готов принять хоть сегодня.";
			link.l1 = "Сегодня не получится, а вот в ближайшее время - будет. Судно с товаром стоит в Капстервиле. Я сейчас отплываю туда и отправлю его к вам. Где проведём перегрузку?";
			link.l1.go = "mtraxx_x_3";
		break;
		
		case "mtraxx_x_3":
            dialog.text = "Давайте сделаем так. Каждый месяц, между 10 и 15 числом, по ночам, мои люди будут ждать ваших визитов в бухте... нет, лучше на мысе Негрил. Далеко, конечно, но и патрулей поменьше... Пароль - 'Лионский купец'.";
			link.l1 = "По рукам, мастер. Не будем терять времени - я поспешу в Капстервиль, отправлять вам первую партию.";
			link.l1.go = "mtraxx_x_4";
		break;
		
		case "mtraxx_x_4":
            dialog.text = "Надеюсь, ваше судно прибудет в срок. Мне катастрофически не хватает шёлка.";
			link.l1 = "Не беспокойтесь, всё будет в порядке. Всего доброго!";
			link.l1.go = "mtraxx_x_5";
		break;
		
		case "mtraxx_x_5":
			DialogExit();
            AddQuestRecord("Roger_2", "21");
			pchar.questTemp.Mtraxx = "silk_10"; // покупатель найден
			sld = characterFromId("Jeffry");
			sld.DeckDialogNode = "Jeffry_9";
		break;
		// Jason Исла Мона
		case "IslaMona":
			if (CheckAttribute(pchar, "questTemp.IslaMona.Shipyarder") && pchar.questTemp.IslaMona.Shipyarder == npchar.id)
			{
				if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
				{
					dialog.text = "Нет, "+pchar.name+". Я против вас ничего не имею, но решите сначала свои проблемы с моей страной. Продажа такого ценного инвентаря врагу Короны может быть неправильно воспринята.";
					link.l1 = "Ага, а как корабли допиливать контрабандными товарами неясного происхождения - так сразу лучшие друзья? Жди, решу я это недоразумение.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Допустим. А что? Что-то строите?";
					link.l1 = "Нет, выполняю очень особенный фрахт. Для управляющего плантацией.";
					link.l1.go = "IslaMona_1";
				}
			}
			else
			{
				npchar.quest.IslaMonaTools = "true";
				dialog.text = "Ничем помочь не могу.";
				link.l1 = "А жаль!";
				link.l1.go = "exit";
			}
		break;
		
		case "IslaMona_1":
            dialog.text = "Понятно. Надеюсь, этот управляющий достаточно вас обеспечил, поскольку я возьму за такой набор очень дорого. Вам очень повезло, что недавно был завоз из метрополии.";
			link.l1 = "Сколько?";
			link.l1.go = "IslaMona_2";
		break;
		
		case "IslaMona_2":
			pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
            dialog.text = "Одна тысяча золотых дублонов.";
			link.l1 = "Да ты перегрелся, я смотрю. Ладно. Согласен.";
			link.l1.go = "IslaMona_7";
			link.l2 = "Это слишком много. Сомневаюсь, что найдётся ещё такой же покупатель на весь набор, как я. Часть распродашь, часть сопрут местные бродяги. Как насчёт скидки?";
			link.l2.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				notification("Недостаточно развит навык (60)", SKILL_COMMERCE);
				dialog.text = "Гарантирую, что найдётся. Цену не меняю. Ну так как? Ждать долго не буду.";
				link.l1 = "Ладно-ладно. Согласен.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
			else
			{
				notification("Проверка пройдена", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 900;
				dialog.text = "Ладно, отнимем соточку. Девятьсот. Ниже не скину. И не проси.";
				link.l1 = "И не буду. Согласен.";
				link.l1.go = "IslaMona_7";
				link.l2 = "Может скинешь ещё? Ну как оптовику. А я у тебя потом и ремонт с покраской закажу, и носовую фигуру самую сочную.";
				link.l2.go = "IslaMona_4";
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
		break;
		
		case "IslaMona_4":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 85)
			{
				notification("Недостаточно развит навык (85)", SKILL_COMMERCE);
				dialog.text = "Да хоть живую бабу туда закажи. Девятьсот.";
				link.l1 = "Ладно-ладно. Согласен.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				notification("Проверка пройдена", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 800;
				dialog.text = "Точно? Не забудешь? Ладно, давай ещё сотню срежем. Но на этом все!";
				link.l1 = "Не забуду. Договорились!";
				link.l1.go = "IslaMona_7";
				link.l2 = "Ну как сказать...";
				link.l2.go = "IslaMona_5";
				AddCharacterExpToSkill(pchar, "Fortune", 200);
			}
		break;
		
		case "IslaMona_5":
            dialog.text = "Немыслимо! "+pchar.name+", у тебя из черепа кусок картечи забыли вытащить? Жаден как скорпион! Мы все наслышаны о твоих недавних похождениях! Ты уже заработал свою кучу золота, так что теперь не мешай другим зарабатывать свою. Ещё одно слово, и ниже тысячи не продам.";
			link.l1 = "Ладно-ладно! Не кипятись. Согласен.";
			link.l1.go = "IslaMona_7";
			link.l2 = "Но, "+npchar.name+", у меня же детишки малые! Мне надо и о них думать! За честный фрахт и так мало платят, тебе ли не знать!";
			link.l2.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 100)
			{
				notification("Недостаточно развит навык (100)", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
				dialog.text = "Дети от бордельных девок в зачет не идут, "+pchar.name+". Ты меня достал. Тысячу дублонов на бочку, или мы прощаемся.";
				link.l1 = "То есть как это, не идут? Эх... Согласен, хапуга.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 800);
			}
			else
			{
				notification("Проверка пройдена", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 700;
				dialog.text = "Не знал, что у тебя дети есть... И что у тебя всё так плохо. Ладно, не жалостись. Семьсот. Почти себе в убыток.";
				link.l1 = "Не забуду. Договорились!";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Fortune", 400);
				Achievment_SetStat(106, 1);
			}
		break;
		
		case "IslaMona_7":
            dialog.text = "Итак, с тебя "+sti(pchar.questTemp.IslaMona.Shipyarder.Money)+" дублонов.";
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.questTemp.IslaMona.Shipyarder.Money))
			{
				link.l1 = "Держи, последнее отдаю, больше ни гроша не осталось.";
				link.l1.go = "IslaMona_8";
			}
			else
			{
				if (GetCharacterItem(pchar, "gold_dublon") < 1)
				{
					link.l1 = "Жди, сейчас пойду к ростовщику в долги влезать.";
					link.l1.go = "IslaMona_money_exit";
				}
				else
				{
					link.l1 = "У меня с собой только "+FindRussianDublonString(GetCharacterItem(pchar, "gold_dublon"))+". Держи это, а я пошёл по ростовщикам побираться.";
					link.l1.go = "IslaMona_money";
				}
			}
		break;
		
		case "IslaMona_money":
			pchar.questTemp.IslaMona.Shipyarder.Money = sti(pchar.questTemp.IslaMona.Shipyarder.Money)-GetCharacterItem(pchar, "gold_dublon");
			Log_Info("Вы отдали "+FindRussianDublonString(GetCharacterItem(pchar, "gold_dublon"))+"");
			RemoveItems(pchar, "gold_dublon", GetCharacterItem(pchar, "gold_dublon"));
			PlaySound("interface\important_item.wav");
            dialog.text = "Не дави на жалость, у тебя рундук в каюте ломится от золота, небось. С тебя ещё "+FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money))+".";
			link.l1 = "";
			link.l1.go = "IslaMona_money_exit";
		break;
		
		case "IslaMona_money_exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			npchar.quest.IslaMonaMoney = "true";
			pchar.questTemp.IslaMona = "dublon";
		break;
		
		case "IslaMona_8":
			Log_Info("Вы отдали "+FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money))+"");
			RemoveItems(pchar, "gold_dublon", sti(pchar.questTemp.IslaMona.Shipyarder.Money));
			PlaySound("interface\important_item.wav");
            dialog.text = "Отлично. Вся сумма на месте. Инструменты будут доставлены на твой корабль. Это несколько тяжёлых ящиков.";
			link.l1 = "Спасибо, "+npchar.name+"!";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			GiveItem2Character(pchar, "islamona_toolbox");
			DeleteAttribute(pchar, "questTemp.IslaMona.Shipyarder");
			DeleteAttribute(npchar, "quest.IslaMonaMoney");
			AddQuestRecord("IslaMona", "2");
			pchar.questTemp.IslaMona = "get_tools";
		break;
	}
}

string findShipyardCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (sti(colonies[n].nation) != PIRATE && colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_shipyarder") != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[rand(howStore-1)];
	return colonies[nation].id;
}

// проверка какой уже цвет есть
bool CheckSailsColor(ref chr, int col)
{
	int    st = GetCharacterShipType(chr);
	ref    shref;
	
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st); 
		st = -1;
		if (!CheckAttribute(shref, "ShipSails.SailsColor"))  st = 0; // нету - это белый
		if (CheckAttribute(shref, "SailsColorIdx"))  st = sti(shref.SailsColorIdx);
		if (st == col) return false;
	}
	return true;		
}

bool CheckSailsGerald(ref chr)
{
    int    st = GetCharacterShipType(chr);
	ref    shref;
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		if (CheckAttribute(shref, "GeraldSails"))  return true;
	}
	return false;
}

string GetSailsType(int _type)
{
	string sSail;
	
	switch (_type)
	{
	    case 1 : sSail = ""+XI_ConvertString("sails_1")+""; break;
	    case 2 : sSail = ""+XI_ConvertString("sails_2")+""; break;
	    case 3 : sSail = ""+XI_ConvertString("sails_3")+""; break;
		case 4 : sSail = ""+XI_ConvertString("sails_4")+""; break;
		case 5 : sSail = ""+XI_ConvertString("sails_5")+""; break;
		case 6 : sSail = ""+XI_ConvertString("sails_6")+""; break;
		case 7 : sSail = ""+XI_ConvertString("sails_7")+""; break;
		case 8 : sSail = ""+XI_ConvertString("sails_8")+""; break;
		case 9 : sSail = ""+XI_ConvertString("sails_9")+""; break;
		case 10 : sSail = ""+XI_ConvertString("sails_10")+""; break;
		case 11 : sSail = ""+XI_ConvertString("sails_11")+""; break;
	}
	return sSail;
}

int GetSailsTypePrice(int _asis, int _tobe, float _shipCostRate, int _price)
{
	int ret;
	ret = _tobe - _asis;
	
	if (ret < 0) ret = 0;
	
	return makeint((ret*_price*0.05 + _price*0.05)*_shipCostRate / 10) * 10;
}

void SelectFindship_ShipType()
{
	int iRank;
	if (sti(pchar.rank) == 1) iRank = 0;
	if (sti(pchar.rank) > 1 && sti(pchar.rank) <= 2) iRank = 1;
	if (sti(pchar.rank) > 2 && sti(pchar.rank) <= 4) iRank = 2;
	if (sti(pchar.rank) > 4 && sti(pchar.rank) <= 7) iRank = 3;
	if (sti(pchar.rank) > 7 && sti(pchar.rank) <= 10) iRank = 4;
	if (sti(pchar.rank) > 10 && sti(pchar.rank) <= 18) iRank = 5;
	
	int iClassFlag = FLAG_SHIP_CLASS_5;
	int iTypesFlag = FLAG_SHIP_TYPE_MERCHANT;
	switch (iRank)
	{
		case 0:  
			iClassFlag = FLAG_SHIP_CLASS_5;
		break; 		
		case 1:  
			iClassFlag = FLAG_SHIP_CLASS_4;
		break;
		case 2:  
			iClassFlag = FLAG_SHIP_CLASS_4;
		break;
		case 3: 
			iClassFlag = FLAG_SHIP_CLASS_3;
		break;
		case 4:  
			iClassFlag = FLAG_SHIP_CLASS_3;
			iTypesFlag = or(FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_TYPE_WAR);
		break;
		case 5: 
			iClassFlag = FLAG_SHIP_CLASS_2;
			iTypesFlag = or(FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_TYPE_WAR);
		break;
	}
	
	pchar.GenQuest.Findship.Shipyarder.ShipType = GetRandomShipType(iClassFlag, iTypesFlag, FLAG_SHIP_NATION_ANY);
}

// проверка количества материалов для корабельного тюнинга
void checkMatherial(ref Pchar, ref NPChar, int good)
{
    int amount;

    amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Tuning.Matherial);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial);
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Tuning.Matherial = sti(NPChar.Tuning.Matherial) - amount;
}

/*
  _chr 		- ГГ
  NPChar 	- верфист
  MaterialNum -  номер материала для апгрейда 
	 1 - товар	 
	 2 - цена в дублонах(сундуки)
  Функция возвращает кол-во материала необходимого для данного типа апгрейда	  
*/

int GetMaterialQtyUpgrade( ref _chr, ref _nchar, int MaterialNum )
{
	if ( sti(_chr.Ship.Type) == SHIP_NOTUSED) return 0;
	
	float fQuestShip 	= 1.0;
	float LEcoeff       = 1.0; // legendary edition
		
	int   	shipClass     		= sti(RealShips[sti(_chr.Ship.Type)].Class);	
	int   	shipMinCrew   		= sti(RealShips[sti(_chr.Ship.Type)].MinCrew);	
	int 	shipPrice			= sti(RealShips[sti(_chr.Ship.Type)].Price);	
		
    if(shipClass == 4) LEcoeff = 0.38;
    if(shipClass > 4) LEcoeff = 0.25;	
	if(CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip")) 	fQuestShip = 1.3;	

	if(MaterialNum == 1) 
	{
	int Material 	= makeint((40 * (7 - shipClass) + 25 * MOD_SKILL_ENEMY_RATE + drand(shipMinCrew)) * fQuestShip * LEcoeff);
	if(Material < 1) 		Material 	= 1;
		return Material;
	}
	if(MaterialNum == 2)
	{
		int WorkPrice 	= 1;
		switch (shipClass)
		{
			case 1: 
				WorkPrice = 10;
			break;
			case 2: 
				WorkPrice = 7;
			break;
			case 3: 
				WorkPrice = 5;
			break;
			case 4: 
				WorkPrice = 3;
			break;
			case 5: 
				WorkPrice = 1;
			break;
		}
		return WorkPrice;
	}
	
	return 0;
}
// belamour legendary edition тюнинг - проверка на сделанное
bool TuningAvailable()
{
	int num = 0;
    ref shTo = &RealShips[sti(Pchar.Ship.Type)];

	if(CheckAttribute(shTo, "Tuning.SpeedRate"))    num++;
	if(CheckAttribute(shTo, "Tuning.WindAgainst"))  num++;
	if(CheckAttribute(shTo, "Tuning.Cannon"))       num++;
	if(CheckAttribute(shTo, "Tuning.Capacity"))     num++;
	if(CheckAttribute(shTo, "Tuning.HP"))           num++;
	if(CheckAttribute(shTo, "Tuning.MaxCrew"))      num++;
	if(CheckAttribute(shTo, "Tuning.TurnRate"))     num++;
	if(CheckAttribute(shTo, "Tuning.MinCrew"))      num++;
	
	if(sti(shTo.Class) > 4 && num == 7 && !CheckAttribute(shTo, "Tuning.MinCrew"))
	{
		if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Радуга") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
            Log_Info("Корабль " + pchar.ship.name + " получает +5% к скорости движения на глобальной карте!");
        }
        return false;
	}
	
	if(num < 8) return true;
	else
    {
        if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Радуга") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
            Log_Info("Корабль " + pchar.ship.name + " получает +5% к скорости движения на глобальной карте!");
        }
        return false;
    }
}