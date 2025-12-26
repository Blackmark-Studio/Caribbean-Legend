// boal 25/04/04 общий диалог мэры
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref aData;
	aref Link, NextDiag, arName;

	DeleteAttribute(&Dialog,"Links");

	ref FortChref; // фортовый командер
	ref arItem;
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Mayor\" + NPChar.City + "_Mayor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    FortChref = GetFortCommander(NPChar.City); // будет или фортовик или сам губернатор

    ref offref;
    int i, cn, iRank, iDay;
    int qty;
    string attrLoc, QuestName, sTemp;
	bool bOk, bOk1, bOk2;
	
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 5000 + (rand(10)+1) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	// генератор ИДХ по кейсу -->
	attrLoc   = Dialog.CurrentNode;
  	if (findsubstr(attrLoc, "GetPrisonerIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	pchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "sell_prisoner_2";
 	}
 	// генератор ИДХ по кейсу <--
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Evime gelip yüzünü gösterecek cesareti bulmuşsun ha?! Bu ya büyük bir cesaret, ya da tam bir aptallık...","Benim aptal muhafızlarım nasıl olur da bir düşmanın sarayıma girmesine izin verdi? Bunun hesabını birine ödeteceğim.","Görünüşe bakılırsa muhafızlarım bir bakır kuruş bile etmiyor, eğer bir alçak konutumda cirit atıp eşyalarımı karıştırabiliyorsa..."),LinkRandPhrase("Ne istiyorsun, "+GetSexPhrase("serseri","şeytan")+"?! Askerlerim zaten peşindeler"+GetSexPhrase(", pis kılıklı korsan","")+"!",+"Katil, derhal konutumdan defol! Muhafızlar!","Senden korkmuyorum, "+GetSexPhrase("alçak","sıçan")+"! Yakında kalemizde asılacaksınız!"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Askerlerin hiçbir işe yaramaz.","Beni yakalamaya çalış."),RandPhraseSimple("Kapa çeneni, "+GetWorkTypeOfMan(npchar,"")+", yoksa senin yerine ben kapatırım!","Sessiz ol dostum, hayatta kalırsın."));
				link.l1.go = "fight";
				break;
			} 
			if (sti(NPChar.nation) == PIRATE)
            {
				if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.PiratesCity") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
				{
					dialog.text = "Ne istiyorsun?";
					link.l1 = "Sizinle önemli bir iş hakkında konuşmak istiyordum.";
					link.l1.go = "quests";
					break;
				}
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && NPChar.city == "LeFransua")
				{
					dialog.text = "Ne istiyorsunuz?";
					link.l1 = "Sizinle önemli bir iş hakkında konuşmak istiyordum.";
					link.l1.go = "quests";
					break;
				}
					dialog.text = "Tartışacak bir şey yok, efendi. Meşgulüm.";
					link.l1 = "Özür dilerim.";
					link.l1.go = "Exit";
            }
			if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
            {
				iTotalTemp = ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0);
                dialog.text = "Ah, bak kim gelmiş! Bu"+GetSexPhrase("","")+" "+GetFullName(pchar)+". Biliyor musun, seni buraya geri getirmeleri için korsan avcılarını daha yeni göndermiştim. Kapımdan böyle elini kolunu sallayarak gireceğini bilseydim, paramı harcamazdım.";
                if (sti(pchar.Money) >= iTotalTemp*6000)
                {
                    link.l1 = "Hesaplarımızı tam da kapatmak üzereydim.";
				    link.l1.go = "arestFree_1";
                }
				link.l2 = "Artık hızlıca ayrılmamın zamanı geldi.";
				link.l2.go = "arest_1";
				break;
            }
			if (false)
			{
    			dialog.text = "Bir soygun! Muhafızlar! Alarm! Cinayet!";
				link.l1 = "Lanet olsun!";
				link.l1.go = "fight"; 
				break;
			}
			//--> Jason, Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && npchar.city == "FortFrance")
			{
    			dialog.text = "Ne istiyorsunuz, monsieur?";
				link.l1 = "Merhaba, Ekselansları. Ben Charles de Maure, Paris'ten yeni geldim. Michel de Montper'i arıyorum.";
                link.l1.go = "Sharlie";
				npchar.quest.meeting = "1"; // patch-6
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && npchar.city == "FortFrance")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
				{
					dialog.text = "Ah, sizsiniz efendim... Kaba davrandığım için özür dilerim. Affınıza sığınıyorum, burada kolonilerde Paris'in nezaketinden çok uzağız.";
					link.l1 = "Elbette, Ekselansları.";
					link.l1.go = "Sharlie_2";
				}
				else
				{
					dialog.text = "Bir şey mi istedin, Charles?";
					link.l1 = "Bir sorum var...";
					link.l1.go = "quests";
					link.l2 = "Hayır, hiçbir şey.";
					link.l2.go = "exit";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
				{
					link.l3 = "Monsieur, ormanda bir haydutun cesedini buldum. Kızılderililer tarafından öldürülmüş. Üzerinde küpeler vardı, sanki Avrupa'dan buraya getirilmiş gibiydi. Belki de kasabanızdaki soylulardan birine aittir?";
					link.l3.go = "Sharlie_junglejew";
				}
				npchar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_TravlyaKrys") && npchar.city == "FortFrance")
			{
    			dialog.text = "Karayipler'e hoş geldiniz, Kaptan de Maure. Bu sefer, gerçekten.";
				link.l1 = "Teşekkür ederim, Ekselansları.";
                link.l1.go = "TK_TravlyaKrys";
				DelLandQuestMark(npchar);
				break;
			}
			// Jason НСО
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.Governor") && npchar.city == "Marigo" && IsUniformEquip())
			{
    			dialog.text = "Sizi görmek güzel, Vali! Nasılsınız? Sint Maarten'de her şey yolunda.";
				link.l1 = "Kalacak vaktim yok. İyi iş çıkarmaya devam et.";
				link.l1.go = "exit";
				link.l2 = "Bir iş hakkında konuşmak istiyordum.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Şansa dayalı bir oyun oynamaya ne dersin?";
				link.l8.go = "Play_Game";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE && IsUniformEquip())
			{
    			dialog.text = "Tanrım, sizi görmek ne güzel, Genel Vali! Bizim bu mütevazı küçük kolonimizde her şey harika! Lütfen, buyurun oturun, hizmetkârlara masayı hazırlatacağım...";
				link.l1 = "Gerek yok. Uzun süre kalmayacağım. İyi iş çıkarmaya devam et.";
				link.l1.go = "exit"; 
				link.l2 = "Biraz iş konuşmak istiyordum.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Şans oyununa ne dersin?";
				link.l8.go = "Play_Game";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") &&  IsUniformEquip())
			{
    			dialog.text = "Burada kimi ağırlıyoruz! Fransız Kolonilerinin Sayın Genel Valisi! Sizi buraya ne getirdi, Ekselansları? Buyurun oturun, hizmetkârlarım size şarap ve taze meyve getirsin.";
				link.l1 = "Endişelenmeyin, buraya sadece adayı ziyaret ettiğim için geldim ve selam vermeden geçip gidemezdim.";
				link.l1.go = "exit"; 
				link.l2 = "Bir iş hakkında konuşmak istiyordum.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Şansa dayalı bir oyun oynamaya ne dersin?";
				link.l8.go = "Play_Game";
				break;
			}		
			//--> Jason, Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernor" && npchar.city == "FortFrance")
			{
    			dialog.text = "Ah, işte buradasınız, kaptan! Doğrusu, sizi beklerken epey zaman geçti.";
				link.l1 = "En kısa sürede geldim, Ekselansları. Acil bir işiniz olduğu söylendi?";
				link.l1.go = "Portugal"; 
				break;
			}			
			//<-- Португалец
            
            if (npchar.quest.meeting == "0")
			{
				dialog.text = "Adamlarım bana, görüşme talebinizde çok ısrarcı olduğunuzu söyledi. Benim adım "+GetFullName(npchar)+". Ben bu kasabanın valisiyim "+GetCityName(NPChar.city)+", konusu "+NationKingsName(npchar)+". Ve şimdi, lütfen, ne istiyorsunuz "+GetAddress_Form(NPChar)+"?";
				link.l1 = "Benim adım "+GetFullName(pchar)+".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_townhall")
				{
					dialog.text = TimeGreeting()+", Bayan MacArthur.";
					link.l1 = TimeGreeting()+", Ekselansları.";
					link.l1.go = "Helen_node_1"
				}
			}
			else
			{
               	//ОСАДЫ homo
				if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
                {

                    makearef(aData, NullCharacter.Siege);
                    
                    if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        dialog.text = "Hepsi bu kadar mı?";
                        link.l1 = "Evet, efendim. Sizi daha fazla oyalamayacağım.";
                        link.l1.go = "exit";

                    }
                    else
                    {
                        dialog.text = "Sizi üzmek istemem ama şu anda sizinle konuşacak vaktim yok. Bildiğiniz gibi, kolonimize saldırıldı "+NationNamePeople(sti(aData.nation))+". Savunmamızla ilgilenmeye devam ediyorum.";
                        link.l1 = "Kalenin savunmasında yardımımı sunmak istiyorum.";
                        link.l1.go = "siege_task";
                        link.l2 = "O halde sizi daha fazla oyalamayacağım.";
            			link.l2.go = "exit";
                    }
                }
                else
                {//->
                    makearef(aData, NullCharacter.Siege);
                    if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                    && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                        ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                        ChangeCharacterComplexReputation(pchar,"nobility", 10);
                        AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                        AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                        AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                        AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                        //--> слухи
                        SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and to defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
			            //<-- слухи
                        DeleteAttribute(aData, "PlayerHelpMayor");
                        DeleteAttribute(aData, "HelpColony");
                        dialog.text = "Ah, sensin demek, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+",   seni   görmekten   memnunum.   Kolonimiz   için   iyi   haberlerim   var   –   saldırıyı   püskürttük. "+NationNameSK(sti(aData.nation))+" işgalciler. Bu işte senin de payın var, bu yüzden ödülün burada - "+(sti(aData.iSquadronPower)*1500)+" sekiz parça. Al bakalım.";
                        link.l1 = "Teşekkür ederim, "+GetAddress_FormToNPC(NPChar)+", sizinle iş yapmak bir zevk!";
                        link.l1.go = "exit";
                    }
                    else
                    {
   						//--> дача квеста найти кольцо в борделе
						if (rand(4) == 4 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questTakeRing") > 365 && sti(pchar.questTemp.HorseQty) > 10)
						{// Addon-2016 Jason
							if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga")
							{
        						dialog.text = "Sana vereceğim bir görev var, ama biraz alışılmışın dışında.";
								link.l1 = "Bunlar benim en iyi yaptığım işler.";
        						link.l1.go = "TakeRing_1";
								SaveCurrentNpcQuestDateParam(npchar, "questTakeRing");
								break;
							}
						}
						//<-- дача квеста найти кольцо в борделе    				
						dialog.text = RandPhraseSimple("Ah, yine sen misin? Bu sefer benden ne istiyorsun?","Beni şehrimin işlerinden alıkoyuyorsun. Ne istiyorsun, "+GetAddress_Form(NPChar)+"?");
						if (npchar.city != "Panama") // Addon-2016 Jason
						{
							link.l1 = "Sizin için çalışmak hakkında konuşmak istiyorum "+NationNameGenitive(sti(NPChar.nation))+".";
							link.l1.go = "work";
						}
						// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
						if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
						{
							link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen")+" Birkaç korsan buldum. Hepsi "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" şu anda gemide. Onları yetkililere teslim etmek istiyorum.";
							link.l11.go = "PiratesOnUninhabited_1";
						}
						
        				link.l2 = "Seninle önemli bir konu hakkında konuşmak istiyordum.";
						if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
						{
							link.l2.go = "ReasonToFast_Mayor1";
						}
						else
						{
							link.l2.go = "quests";   //(перессылка в файл города)
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
						{
							if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
							{
								link.l12 = "Devriyenin başında bir kaptan var "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" named "+pchar.GenQuest.CaptainComission.Name+", onu nasıl görebilirim?";
								link.l12.go = "CapComission_Mayor1";
							}	
							if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
							{
								link.l12 = "Devriye birliğinin eski kaptanı "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"   yetkililere gizli hazinesinin yerini açıklamayı kabul etti.";
								link.l12.go = "CapComission_Mayor9";
							}
							if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
							{
								link.l12 = "Devriye birliğinin eski kaptanı "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" bana gizli hazinesini gösterdi.";
								link.l12.go = "CapComission_Mayor13";
							}
						}
						if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25  && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
						{
							if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
							{
								iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
								if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Kaptanla tanıştım "+pchar.GenQuest.ShipWreck.Name+" ve korsanlar tarafından karaya bırakılan denizcileri "+pchar.GenQuest.ShipWreck.BadName+". "+"Ne yazık ki, gemimde zaten çok fazla adam vardı ve onları alamadım. Ama onlara erzak ve silah bıraktım. Eğer bir kurtarma gemisi onları zamanında almazsa "+(30 - iDay)+" gün, sonra onları hayatta bulup bulamayacağımı bilmiyorum.";
									link.l13.go = "ShipWreck1";
								}
								else
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Gen"))+" Batık gemiden denizcilerle karşılaştım '"+pchar.GenQuest.ShipWreck.ShipTypeName+"  kaptanlarıyla birlikte. "+"Maalesef, gemimde zaten fazlasıyla adam vardı ve onları alamadım. Ama onlara erzak ve silah bıraktım. Bir kurtarma gemisi onları almazsa "+(30 - iDay)+" gün, sonra onları sağ bulup bulamayacağımı bilmiyorum.";
									link.l13.go = "ShipWreck1";							
								}
							}	
						}
        				if (GetPrisonerQty() > 0)
        				{
                            link.l3 = "Bir mahkumu teslim etmek istiyorum.";
        				    link.l3.go = "sell_prisoner";
        				}
        				if (npchar.Default  == npchar.location) // если не в тюрьме
        				{
        					if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
        					{
        						link.l4 = "Sizinle bazı mali meseleleri halletmem gerekiyor.";
        						link.l4.go = "LoanForAll";//(перессылка в кредитный генератор)
        					}
        				}
						//-->> сдача найденного в борделе кольца
						if (CheckCharacterItem(pchar, "MayorsRing"))
						{
							if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
							{
        						link.l5 = "Yüzüğünüzü bulmayı başardım. Buyurun.";
        						link.l5.go = "TakeRing_S1";
							}
							else
							{
        						link.l5 = "Yüzüğünüzü buldum. Genelevde çalışan kızlardan birinin elindeydi.";
        						link.l5.go = "TakeRing_S3";
							}
						}
						//<<-- сдача найденного в борделе кольца 
						
						//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "Şehirden bir mesaj getirdim "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
						//<-- генер почтового курьера 2 уровня
						
						// Warship, 16.05.11. Квест "Правосудие на продажу" -->
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar))+", Muhafızlar tarafından yakın zamanda yakalanan bir kaçakçı çetesini buldum. Şimdi liderlerini kaçırmanın planlarını yapıyorlar. Gemilerinin adı '"+PChar.GenQuest.JusticeOnSale.ShipName+"'   limanda demirli "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+".";
							link.l15.go = "JusticeOnSale_1";
						}
						
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.ShipSink") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar))+", kaçakçı çetesi artık yok!";
							link.l15.go = "JusticeOnSale_7";
						}
						// <--Правосудие на продажу
						//Jason --> Регата
						if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
						{
							link.l16 = "Regata için buradayım. İşte davetiyem.";
							link.l16.go = "Regata";
						}
        				//link.l7 = " Valilik Genel Valisi'nin nerede olduğunu öğrenmek isterim "+NationNameGenitive(sti(NPChar.nation))+"is.";
        				link.l8 = "Belki de biraz şans oyunu oynayarak ara vermek istersiniz?";
        			    link.l8.go = "Play_Game";
        				link.l10 = "Lütfen affedin, ama görevim beni çağırıyor.";
        				link.l10.go = "exit";
                    }
                }//<-
			}
		break;
		
		// Warship Генер "Пираты на необитайке"
		case "PiratesOnUninhabited_1":
			offref = CharacterFromID("PirateOnUninhabited_0");
			qty = makeint(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) * (sti(offref.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(offref, "Leadership") * 500 + GetCharacterSkillToOld(PChar, "commerce") * 500) / 20);
			
			PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates = qty;
			
			dialog.text = "Çok iyi. Bu ortak belaya karşı birlikte mücadele etmeliyiz. Hemen bir gemi gönderip onları aldıracağım. Emin olun, bir haftadan kısa sürede darağacında sallanacaklar. Ah, tabii ki bir ödül de hak ettiniz - "+FindRussianMoneyString(qty)+".";
			link.l1 = "Teşekkür ederim, Ekselansları. Her zaman bir zevk. ";
			link.l1.go = "PiratesOnUninhabited_2";
			link.l2 = "Hayır. Düşününce, bu olmaz.";
			link.l2.go = "exit";
		break;
		
		case "PiratesOnUninhabited_2":
			offref = CharacterFromID("PirateOnUninhabited_0");
			
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates));
			
			RemovePassenger(PChar, offref);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTemp = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTemp, "PiratesOnUninhabited", "12");
			AddQuestUserData(sTemp, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTemp, "mayorName", GetFullName(NPChar));
			CloseQuestHeader(sTemp);
			
			PChar.Quest.PiratesOnUninhabited_OnShore.over = "yes";
			PChar.Quest.PiratesOnUninhabited_OnMayak.over = "yes";
			
			if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
			{
				PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
				
				PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
				Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
			}
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Mayor1":
			dialog.text = "Sizi dinliyorum, kaptan.";
			link.l1 = "Sizin garnizonunuzdaki bir subay ile korsanlar arasında bazı suç ortaklıkları olduğunu size bildirmek istedim... (durumu açıklar).";
			if(sti(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_BMayor";			
			}
			else
			{
				link.l1.go = "ReasonToFast_GMayor";	
			}
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_GMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Teşekkür ederim, "+GetSexPhrase("bayım","miss")+"! O hainin derhal tutuklanmasını emredeceğim.\nBelli ki çok para harcamışsınız, ne yazık ki hazinemiz bomboş...";
				link.l1 = "Bunu para için yapmadım, Ekselansları.";
				link.l1.go = "ReasonToFast_GMayor_11";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}			
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Sana teşekkür ederim! O alçağı hemen tutuklatacağım.\nDüşünsene! Az kalsın ona onuncu hizmet yılı için altın kabzalı bir kılıç verecektim! Beni büyük bir rezillikten kurtardın!";
				link.l2 = "Adalet kendi ödülüdür.";
				link.l2.go = "ReasonToFast_GMayor_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Mis"+GetSexPhrase("ter","s")+" de Maure, tanık olmadan bir şüpheliyi öldüremezsin! Şimdi onun suçlarını kanıtlayacak hiçbir delilimiz yok! Seni adam öldürmekten tutuklatmamayı başarmam bile zor.";
				link.l3 = "Kendimi savunmak için yaptım, Ekselansları.";
				link.l3.go = "ReasonToFast_GMayor_31";
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}			
		break;
		
		case "ReasonToFast_BMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 				
				dialog.text = "Kaptan, ne halt ettiğinin farkında mısın?!! Bu tuzağı bir aydan fazla süredir kuruyordum! Ve şimdi, sadece kendi keyfin için, devriyemizin buluşmasını mahvettin "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" ve şimdi buraya gelip bununla övünüyorsun öyle mi?!! Belki şimdi bana söyleyebilirsin, bu operasyonun tüm masraflarını ve giderlerini nasıl açıklayacağım?!";
				link.l1 = "Majesteleri, sorununuzu az önce çözdüm. Düşününce, bana en başından beri ödeme yapıyor olmalıydınız!";
				link.l1.go = "ReasonToFast_BMayor_1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Haritaya bir bakayım\nŞu anda ciddi misiniz? Bu yıpranmış kağıt parçası kanıt mı olacak?";
				link.l2 = "Hadi ama, Ekselansları, mantıklı olun.";
				link.l2.go = "ReasonToFast_BMayor_1";
				TakeItemFromCharacter(pchar, "mapQuest");				
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Demek devriyemin başına ne geldiğini şimdi öğrendik. En azından buraya gelerek katili arama zahmetinden bizi kurtardın.";
				link.l3 = "Majesteleri! Meseleyi görmekte inat ediyorsunuz...";
				link.l3.go = "ReasonToFast_BMayor_1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_GMayor_11":
			dialog.text = "You may be an idiot but you are at least a useful idiot. Here - take this map; found it on a pirate who we hanged last week. God willing, perhaps you will find his treasure, although I find it quite unlikely...";
			link.l1 = "Teşekkür ederim, bu gerçekten çok cömertçe!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		
		case "ReasonToFast_GMayor_21":
			dialog.text = "Gayretiniz takdire şayan. Lütfen bu kılıcı ödül olarak kabul edin – yapabileceğim en azı bu. Ah, haritayı da kendinize saklayabilirsiniz. Eminim Karayipler'de bu tür sahte haritalardan bolca vardır.";
			link.l1 = "Teşekkür ederim, bu gerçekten çok cömertçe!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_GMayor_31":
			dialog.text = "Belki, belki... Şöyle diyelim, bu anlaşma ilahi adalet ve Rabbimizin iradesiyle karara bağlandı.";
			link.l1 = "Teşekkür ederim, bu gerçekten çok cömertçe!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");
		break;
		
		case "ReasonToFast_BMayor_1":
			dialog.text = "Dilini tut, çocuk! Ya delirdin ya da düşmanlarımızla iş birliği yapıyorsun! Muhafızlar, şu aptalı yakalayın!";
			link.l1 = "Bana elini sürersen, o elinden olursun!";
			link.l1.go = "fight";
		
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";						
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		
		// --------------------------Операция 'Галеон'-----------------------------
		case "CapComission_Mayor1":
			dialog.text = "Şu anda bu imkânsız. Kendisi tutuklu, yargılanmayı bekliyor.";
			link.l1 = "Öyle mi? Peki, neyle suçlanıyor?";			
			link.l1.go = "CapComission_Mayor2";
		break;
		
		case "CapComission_Mayor2":
			dialog.text = "Ne yazık ki, bu bir şüphe değil, kanıtlanmış bir gerçek. Elimizde, devriye bahanesiyle gemilere saldırdığına dair bilgiler var. Tüccarların mallarına el koyup sonra da bunları kaçakçılara ve korsanlara sattı. Ne acı... Bir zamanlar Taç'ın en iyi kaptanlarından biri sayılıyordu...";
			link.l1 = "Ve sana bu kanıtı kim verdi?";
			link.l1.go = "CapComission_Mayor3";				
		break;
		
		case "CapComission_Mayor3":
			dialog.text = "Kurbanlarından biri bir rapor yazdı; olayın ayrıntılarını, tarihi, baskına uğrayan geminin adını ve el konulan malların miktarlarını detaylıca anlattı. "+"Bana güvenin, rakamlar gerçekten etkileyici. O günkü devriyede "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))+" kaptan "+pchar.GenQuest.CaptainComission.Name+" gerçekten görevdeydi. Kaptan bu olayı raporunda bir korsan gemisiyle karşılaşma olarak anlattı, fakat hiçbir yükten bahsetmedi.";
			link.l1 = " Ama hiç yük var mıydı? ";
			link.l1.go = "CapComission_Mayor4";
			pchar.GenQuest.CaptainComission.SpeakMayor = true;
		break;
		
		case "CapComission_Mayor4":
			dialog.text = "Bunda hiç şüphe yok. Mağdur olan kişi çok tanınmış biri ve kendini iftira ya da karalamayla küçük düşürmez. Şu anda devriyelerimiz kaptanın gizli eşyalarını arıyor. "+"Bulunduğunda, kaptan mahkemeye çıkabilir\nEğer bu konuda bize yardımcı olursanız, size minnettar kalırız.";
			link.l1 = "Sanmıyorum. Buradaki bölgeyi bir hazine arayacak kadar iyi tanımıyorum. Affedersiniz, gitmem gerek.";
			link.l1.go = "CapComission_Mayor5";
			link.l2 = "Belki... Ne kadar vaktim var?";
			link.l2.go = "CapComission_Mayor6";	
		break;
		
		case "CapComission_Mayor5":
			AddQuestRecord("CaptainComission2", "49");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			pchar.GenQuest.CaptainComission = "MayorTalkBad";
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor6":
			dialog.text = "Bence iki gün içinde devriyeler senin yardımın olmadan da gizli yeri bulabilir, bu yüzden acele etmelisin."; 
			link.l1 = "Tamam, hallediyorum. Ama kaptana uğramam gerekecek "+pchar.GenQuest.CaptainComission.Name+". Bunu ayarlamak mümkün mü?";
			link.l1.go = "CapComission_Mayor7";
		break;
		
		case "CapComission_Mayor7":
			dialog.text = "Bu sorun olmayacak. Kale komutanına ziyaretinizden bahsedeceğim.";
			link.l1 = "Teşekkür ederim. Şimdi, lütfen beni mazur görün.";
			link.l1.go = "CapComission_Mayor8";
		break;
		
		case "CapComission_Mayor8":
			AddQuestRecord("CaptainComission2", "50");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);			
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			OfficersReaction("good");
			pchar.GenQuest.CaptainComission.MayorTalkGood = true;
			pchar.GenQuest.CaptainComission = "MayorTalkGood";
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			SetFunctionTimerConditionParam("CaptainComission_GetSecretTimeIsOut", 0, 0, 2, MakeInt(24 - GetHour()), false);
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor9":
			dialog.text = "Mükemmel! Hazine nerede?";
			link.l1 = "Henüz bir fikrim yok. Bana tam yerini göstermedi.";
			link.l1.go = "CapComission_Mayor10";
		break;
		
		case "CapComission_Mayor10":
			dialog.text = "Hmm, ne tesadüf! Biliyor musun, o da bana tam yerini 'göstermedi'...";
			link.l1 = "Üzerinde çalışıyorum.";
			link.l1.go = "CapComission_Mayor11";
		break;
		
		case "CapComission_Mayor11":
			dialog.text = "Artık değil\nMuhafızlar! Mahkumu hücreye geri götürün\nSen gidebilirsin, "+GetFullName(pchar)+".";
			link.l1 = "Ama vali...";
			link.l1.go = "CapComission_Mayor12";
		break;
		
		case "CapComission_Mayor12":
			sld = CharacterFromID("CapComission_1");
			sld.lifeDay = 0;
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetActorType(sld);
            LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);			
			pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_DeletePrisonGroup.win_condition = "CaptainComission_DeletePrisonGroup";									
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);			
			AddQuestRecord("CaptainComission2", "23");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CapComission_Mayor13":
			pchar.quest.CaptainComission_SpeakMayorGoods.over = "yes";
			dialog.text = "Mükemmel! Peki, hazinesini nerede arayacağız?";
			link.l1 = "In the "+RandPhraseSimple(RandPhraseSimple("kuzey","western"),RandPhraseSimple("doğu","güneyli"))+" end of "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+" uçurumun dibinde, girişi taşlarla kapatılmış büyük bir oyuk var. Orası saklanma yeri.";
			link.l1.go = "CapComission_Mayor14";
		break;
		
		case "CapComission_Mayor14":
			dialog.text = "Harika bir iş çıkardınız! Peki, nerede "+pchar.GenQuest.CaptainComission.Name+" kendisi mi? Onu kalenin zindanlarından senin aldığını duydum.";
			link.l1 = "Ne yazık ki, kaçakçılarla çıkan bir çatışmada hayatını kaybetti.";
			link.l1.go = "CapComission_Mayor15";
		break;
		
		case "CapComission_Mayor15":
			dialog.text = "Bu kötü... Bu gerçekten çok kötü, "+GetSexPhrase("bayım","özlemek")+" "+GetFullName(pchar)+". Onu halka açık bir şekilde idam edecektim, 'diğerlerine ibret olsun diye.'"+"Her neyse, zaten darağacından kurtulamazdı\nYani, teknik olarak yasaları çiğneyip bir mahkumu yasa dışı şekilde serbest bıraktınız ama onu yine de kurtaramadınız, bu yüzden bunu raporda düzeltemem. Bu nedenle ödül alamıyorsunuz... Ama size şahsen teşekkür etmek isterim. Hediyemi kabul edin – savaşan bir kaptan için oldukça faydalı bir şey.";
			link.l1 = "Teşekkür ederim. Her zaman hizmetinizdeyim.";	
			link.l1.go = "CapComission_Mayor16";
		break;
		
		case "CapComission_Mayor16":
			AddQuestRecord("CaptainComission2", "30");
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			CloseQuestHeader("CaptainComission2");
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			OfficersReaction("good");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		// --------------------------Операция 'Галеон'-----------------------------
		
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		case "ShipWreck1":
			if(iDay > 15)
			{
				dialog.text = RandPhraseSimple("Bunu nasıl yapıyorsun? Oraya rüzgar arkandayken bile gitmek en az on beş gün sürer!","Kaptan "+GetFullName(pchar)+",   sorumsuzluğun beni şaşırtıyor!   Neden bunu bana daha önce söylemedin?");
				link.l1 = "Doğrusu, ne desem bilemiyorum...";
				link.l1.go = "ShipWreck2";
			}
			else
			{
				dialog.text = "Bu harika bir haber! Onu tekrar göreceğimizden umudu kesmiştik "+pchar.GenQuest.ShipWreck.Name+"  tekrar hayatta. Hemen bir kurtarma ekibi göndereceğim. Ayrıca, onları kurtarmadaki hızlı ve etkin çabanız için lütfen bu ödülü kabul edin.";
				link.l1 = "Teşekkür ederim, Ekselansları. Yardımcı olabildiğim için memnunum. Eminim sefer zamanında varacaktır.";
				link.l1.go = "ShipWreck3";	
			}
			pchar.GenQuest.ShipWreck.SpeakMayor = true;
			pchar.quest.ShipWreck_MeetInShore.over = "yes";
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen таймер на 30 дней тоже нужно снять
		break;
		
		case "ShipWreck2":
			dialog.text = "Vay canına... Ne diyebilirim ki? Git Deniz Hukuku'nu öğren, evlat! Neyse, bu insanları kurtarmak için elimden geleni yapacağım.";
			link.l1 = "Majesteleri, ama onlara yeterince erzak bıraktım. Zamanınız var, emin olabilirsiniz...";
			link.l1.go = "ShipWreck4";
		break;
		
		case "ShipWreck3":
			addMoneyToCharacter(pchar, sti(pchar.rank) * 300 + 3000 + rand(3000));
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			AddQuestRecord("ShipWrecked", "14");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen")); // belamour gen просто NPChar.city ничего не даст
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // belamour gen
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;		
		
		case "ShipWreck4":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("ShipWrecked", "13");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen")); // belamour gen просто NPChar.city ничего не даст
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // belamour gen
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		
		// ---------------------- найти кольцо в борделе ----------------------------
		case "TakeRing_1":
			dialog.text = "Biliyorum ki siz, nasıl desem... "+GetSexPhrase("genelevlerin müdavimisiniz","arada sırada genelevlere gitmeyi severim")+" . Bu yüzden yardım için sana başvurmaya karar verdim\n"+"Biliyor musunuz, itiraf etmekten utanıyorum ama ben de yakın zamanda oradaydım...";
			link.l1 = "Peki bunda ne var? Seks gayet doğal bir şey, biliyorsun...";
			link.l1.go = "TakeRing_2";
		break;
		case "TakeRing_2":
			dialog.text = "Ah, hayır, vaaz vermiyorum, hayır. Şöyle ki, bir keresinde fazla içtim ve evlilik yüzüğümü kaybettim...";
			link.l1 = "Bu gerçekten bir sorun. Üzgünüm.";
			link.l1.go = "TakeRing_3";
		break;
		case "TakeRing_3":
			dialog.text = "Kimsenin bana acımasına ihtiyacım yok. Yüzüğümü geri istiyorum. Eğer gece yarısından önce geri getirirsen, çok cömert olacağım. Başaramazsan, karım beni öldürür.";
			link.l1 = "Anlıyorum... Peki tam olarak nerede kaybettiniz? Özellikle hatırladığınız bir şey var mı?";
			link.l1.go = "TakeRing_4";
		break;
		case "TakeRing_4":
			dialog.text = "Maalesef, hayır. Hiçbir şey yok.";
			link.l1 = "Anladım. O halde, hadi arayalım.";
			link.l1.go = "TakeRing_5";
			link.l2 = "Biliyor musun, "+GetAddress_FormToNPC(NPChar)+", sanırım bu seferlik pas geçeceğim. Lütfen beni mazur görün...";
			link.l2.go = "TakeRing_6";
		break;	
		case "TakeRing_5":
			dialog.text = "Mükemmel! Ama unutma - onu gece yarısından önce bulmalısın.";
			link.l1 = "Hatırlıyorum. Yakında döneceğim.";
			link.l1.go = "exit";
			pchar.questTemp.different = "TakeMayorsRing";
			pchar.questTemp.different.TakeMayorsRing = "toBrothel";
			pchar.questTemp.different.TakeMayorsRing.Id = GetFullName(npchar);
			pchar.questTemp.different.TakeMayorsRing.city = npchar.city;	
			pchar.questTemp.different.TakeMayorsRing.price = sti(pchar.rank)*100+1000;
			sld = ItemsFromID("MayorsRing");
			sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
			//ложим кольцо в итем
			if (rand(3) != 2)
			{				
				switch (rand(2))
				{
					case 0: sTemp = "_Brothel_room";  break;
					case 1: sTemp = "_Brothel";  break;
					case 2: sTemp = "_SecBrRoom";  break;
				}
				sld.shown = true;
				sld.startLocation = pchar.questTemp.different.TakeMayorsRing.city + sTemp;
				sld.startLocator = "item" + (rand(4)+1);
				pchar.questTemp.different.TakeMayorsRing.item = true; //флаг кольцо валяется в итемах
				Log_QuestInfo("The ring is at " + sld.startLocation + ", in locator " + sld.startLocator);
			}
			SetTimerFunction("TakeMayorsRing_null", 0, 0, 1); //освобождаем разрешалку на миниквесты 
			ReOpenQuestHeader("SeekMayorsRing");
			AddQuestRecord("SeekMayorsRing", "1");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", pchar.questTemp.different.TakeMayorsRing.Id);
		break;	
		case "TakeRing_6":
			dialog.text = "Öyle mi? Doğrusu bu hiç beklenmedikti... O halde sana bol şans, kaptan.";
			link.l1 = "Elveda.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
		break;

		case "TakeRing_S1":
			dialog.text = "Bu benim yüzüğüm! Hayatımı kurtardınız!";
			link.l1 = "Bir şey değil, efendim.";
			link.l1.go = "TakeRing_S2";
			TakeItemFromCharacter(pchar, "MayorsRing");
		break;
		case "TakeRing_S2":
			dialog.text = "İşte iyi yapılmış bir işin karşılığı olan paranız! Size gerçekten minnettarım!";
			link.l1 = "Yardımcı olmaktan memnuniyet duyarım, efendim. Lütfen bir dahaki sefere daha dikkatli olun.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		case "TakeRing_S3":
			dialog.text = "Tanrım, bana acı! Gerçekten bu kadar içmeyi bırakmalıyım...";
			link.l1 = "Kesinlikle! İşte yüzüğünüz.";
			link.l1.go = "TakeRing_S4";
		break;
		case "TakeRing_S4":
			dialog.text = "Evet, evet, çok teşekkür ederim. Size borçlandım! İşinizi layıkıyla yaptığınız için paranız burada!";
			link.l1 = "Teşekkürler "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "MayorsRing");
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 3);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		// ---------------------- найти кольцо в борделе ----------------------------

		case "node_1":
            //ОСАДЫ homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "Zaten her şeyi konuştuk, değil mi?";
                    link.l1 = "Doğru. Sizi daha fazla oyalamayacağım.";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "Sizi üzmek istemem ama şu anda sizinle konuşacak vaktim yok. Bildiğiniz gibi, kolonimize saldırıldı "+NationNamePeople(sti(aData.nation))+". Savunmamızla ilgilenmem gerek.";
                    link.l1 = "Ben sadece kalenin savunmasında yardımımı teklif etmek istedim.";
                    link.l1.go = "siege_task";
                    link.l2 = "O halde sizi daha fazla oyalamayacağım.";
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterComplexReputation(pchar,"nobility", 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                    //--> слухи
                    SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "Ah, sensin demek, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+",   seni   görmekten   memnun   oldum.   İyi   haberlerim   var – saldırıyı püskürttük "+NationNameSK(sti(aData.nation))+" istilacılar. Sen de bunda rolünü oynadın, işte ödülün - "+(sti(aData.iSquadronPower)*1500)+" sekiz parça. Al bakalım.";
                    link.l1 = "Teşekkür ederim, "+GetAddress_FormToNPC(NPChar)+", sizinle iş yapmak bir zevkti!";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "Peki, seni buraya getiren ve devletin önemli işlerinden beni alıkoyan nedir?";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "Benim için çalışmak istedim "+NationNameGenitive(sti(NPChar.nation))+".";
						link.l1.go = "work";
					}
					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Dat")+" Birkaç korsanla karşılaştım. Hepsi "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" şu anda gemide. Onları yetkililere teslim etmek istiyorum.";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "Sizinle önemli bir konu hakkında konuşmak istiyordum.";
					if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{					
						link.l2.go = "quests";
					}	
					if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
						{
							link.l12 = "Devriyenin başında bir kaptan var "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" named "+pchar.GenQuest.CaptainComission.Name+", onunla nasıl görüşebilirim?";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "Devriye komutasında eski bir kaptan "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"   yetkililere   sakladığı   yeri   açıklamayı   kabul   etti.";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "Devriyenin başındaki eski kaptan "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" bana gizli hazinesini gösterdi.";
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Bir kaptanla tanıştım "+pchar.GenQuest.ShipWreck.Name+" ve korsanlar tarafından karaya bırakılan denizcileri "+pchar.GenQuest.ShipWreck.BadName+". "+"Maalesef, gemimde zaten çok fazla adam vardı, bu yüzden onları alamadım. Ama onlara yiyecek ve silah bıraktım. Kurtarma gemisi onları almazsa "+(30 - iDay)+" gün, sonra onları hala hayatta bulup bulamayacağımı bilmiyorum.";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Bir gemi kazasından kurtulan denizcilerle karşılaştım '"+pchar.GenQuest.ShipWreck.ShipTypeName+" Kaptanlarıyla birlikte. "+"Ne yazık ki, gemimde zaten fazlasıyla adam vardı ve bu yüzden onları alamadım. Ama onlara yiyecek ve silah bıraktım. Eğer kurtarma gemisi onları zamanında almazsa "+(30 - iDay)+" gün, sonra onları hala hayatta bulacak mıyım bilmiyorum.";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "Kasabadan bir mesajım var "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "Efendim, liderleri yakın zamanda muhafızlar tarafından yakalanan bir kaçakçı çetesinin izini buldum. Şimdi onun kaçışını planlıyorlar. Gemileri '"+PChar.GenQuest.JusticeOnSale.ShipName+"'   limanda demirli "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Gen")+".";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "Tutsak kaptanı yetkililere teslim etmem gerekiyor.";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "Regata için buradayım. İşte davetiyem.";
						link.l4.go = "Regata";
					}
        			link.l5 = "Belki biraz ara vermek istersiniz?";
        			link.l5.go = "Play_Game";
        			link.l10 = "Bu sadece bir nezaket ziyaretiydi, "+GetAddress_FormToNPC(NPChar)+".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Helen_node_1":
            //ОСАДЫ homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "Zaten her şeyi konuştuk, değil mi?";
                    link.l1 = "Doğru. Sizi daha fazla oyalamayacağım.";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "Sizi üzmek istemem ama şu anda sizinle konuşacak vaktim yok. Bildiğiniz gibi, kolonimize saldırıldı "+NationNamePeople(sti(aData.nation))+". Savunmamızla ilgilenmem gerek.";
                    link.l1 = "Şey, sadece kalenin savunmasında yardımcı olmak istediğimi belirtmek istemiştim.";
                    link.l1.go = "siege_task";
                    link.l2 = "O halde sizi daha fazla oyalamayayım.";
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterComplexReputation(pchar,"nobility", 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                    //--> слухи
                    SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "Ah, sensin demek, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+",   seni   görmek   güzel.   İyi   haberlerim   var   –   saldırıyı   püskürttük   "+NationNameSK(sti(aData.nation))+" istilacılar. Sen de bunda rolünü oynadın ve işte ödülün - "+(sti(aData.iSquadronPower)*1500)+" sekiz parça. Al bakalım.";
                    link.l1 = "Teşekkür ederim, "+GetAddress_FormToNPC(NPChar)+", sizinle iş yapmak bir zevkti!";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "Seni buraya getiren nedir? Tüm işlerini... hamininle hallettiğini sanıyordum. Ama konuş, seni dinlemekten her zaman memnuniyet duyarım.";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "Benim için çalışmak istedim "+NationNameGenitive(sti(NPChar.nation))+".";
						link.l1.go = "work";
					}
					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Dat")+" Birkaç korsanla karşılaştım. Hepsi "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" şu anda gemide. Onları yetkililere teslim etmek istiyorum.";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "Sizinle önemli bir mesele hakkında konuşmak istiyordum.";
					if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{					
						link.l2.go = "quests";
					}	
					if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
						{
							link.l12 = "Devriyenin başında bir kaptan var "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" named "+pchar.GenQuest.CaptainComission.Name+", onunla nasıl tanışabilirim?";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "Devriye birliğinin eski kaptanı "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"   yetkililere gizli hazinesinin yerini açıklamayı kabul etti.";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "Devriyenin başında olan eski kaptan "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" bana gizli hazinesini gösterdi.";
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Bir kaptanla tanıştım "+pchar.GenQuest.ShipWreck.Name+" ve korsanlar tarafından karaya bırakılan denizcileri "+pchar.GenQuest.ShipWreck.BadName+". "+"Ne yazık ki, gemimde zaten çok fazla adam vardı ve bu yüzden onları alamadım. Ama onlara yiyecek ve silah bıraktım. Eğer kurtarma gemisi onları zamanında almazsa "+(30 - iDay)+" gün, sonra onları hala hayatta bulup bulamayacağımı bilmiyorum.";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Bir gemi kazasından kurtulan denizcilerle karşılaştım '"+pchar.GenQuest.ShipWreck.ShipTypeName+" Kaptanlarıyla birlikte. "+"Ne yazık ki, gemimde zaten fazlasıyla adam vardı, bu yüzden onları alamadım. Ama onlara yiyecek ve silah bıraktım. Eğer kurtarma gemisi onları zamanında almazsa "+(30 - iDay)+" gün, sonra onları hâlâ hayatta bulacak mıyım bilmiyorum.";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "Kasabadan bir mesaj getirdim "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "Efendim, yakın zamanda muhafızlar tarafından ele geçirilen bir kaçakçı çetesinin liderini tespit ettim. Şimdi adamları onun kaçışını planlıyor. Gemileri '"+PChar.GenQuest.JusticeOnSale.ShipName+"'   limanda demirlemiş "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Gen")+".";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "Tutsak kaptanı yetkililere teslim etmem gerekiyor.";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "Regata için buradayım. İşte davetiyem.";
						link.l4.go = "Regata";
					}
        			link.l5 = "Belki biraz ara vermek istersiniz?";
        			link.l5.go = "Play_Game";
        			link.l10 = "Sadece bir nezaket ziyaretiydi, "+GetAddress_FormToNPC(NPChar)+".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Play_Game":
			//==> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "Şimdi olmaz! Denetimimiz var, don de Alamida şehirde. Ah, her yıl aynı şey, ben ne yaptım da bunu hak ettim...";
				link.l1 = "Dediğiniz gibi. Sizi oyalamayacağım.";
				link.l1.go = "exit"; 
				break;
			}
			//<== прибыла инспекция на Святом Милосердии
			dialog.text = "Hmm, peki ne tür oyunları tercih edersiniz?";
			link.l1 = "Biraz ciddi paraya kart oynamak ister misin?";
			link.l1.go = "Card_Game";
   			link.l2 = "Poker-joker'da biraz zar atmaya ne dersin?";
			link.l2.go = "Dice_Game";
			link.l10 = "Lütfen beni mazur görün, ama görevim var.";
			link.l10.go = "exit";
		break;
		
		//  карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(IsUniformEquip()) dialog.text = "Affedersiniz, monsignor, ama şu anda bunun için vaktim yok. Belki bir dahaki sefere."; // Jason НСО
                else dialog.text = "Ben korsanlarla kumar oynamam!";
    			link.l1 = "Nasıl isterseniz.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Card_date_begin"))
				{
					dialog.text = "Neden olmasın! Dinlenmek kalbe iyi gelir, ama cebe pek yaramaz...";
	    			link.l1 = "Mükemmel.";
	    			link.l1.go = "Cards_begin";
	    			link.l2 = "Oyunumuzun kuralları nedir?";
	    			link.l2.go = "Cards_Rule";
    			}
    			else
    			{
					dialog.text = "Hayır, bugünlük bu kadar. Yapacak işlerim var.";
	    			link.l1 = "Nasıl isterseniz.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Pekâlâ, o zaman başlayalım!";
			link.l1.go = "Cards_begin";
			link.l3 = "Hayır, bu bana göre değil...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			dialog.text = "Önce bahiste anlaşalım.";
			link.l1 = "1.000 sekizlik için oynayalım.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "5.000 sekizlik için oynayalım.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "Sanırım gitmem gerekiyor.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckCardsGameSmallRate() && !bOk)
		    {
                dialog.text = "Sen namlı bir hilesin. Seninle kumar oynamam.";
                link.l1 = "Hepsi yalan!";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "Şaka mı yapıyorsun, "+GetAddress_Form(NPChar)+"? Paran yok!";
                link.l1 = "Olur böyle şeyler.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "Bu kadar! Kartlarla işim bitti—beni müsriflikle suçlayıp görevimden uzaklaştırmadan önce.";
                link.l1 = "Yazık.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Pekâlâ, 1.000 sekizlik için oynayalım.";
			link.l1 = "Hadi başlayalım!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckCardsGameSmallRate() && !bOk)
		    {
                dialog.text = "Sen nam salmış bir hilesin. Seninle kumar oynamam.";
                link.l1 = "Hepsi yalan! Neyse, boşver.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckCardsGameBigRate())
		    {
                dialog.text = "Sana çok iyi bir oyuncu olduğunu söylüyorlar. Seninle yüksek bahis oynamayacağım.";
                link.l1 = "Bahsi biraz düşürelim mi, ne dersiniz?";
			    link.l1.go = "Cards_Node_100";
				link.l2 = "Üzgünüm, ama gitmem gerekiyor.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "Şaka mı yapıyorsun, "+GetAddress_Form(npchar)+"? 15.000 sekizliğin yok!";
                link.l1 = "Onları kaldıracağım!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "Hayır, bu bahisler şehrin hazinesini boşaltacak.";
                link.l1 = "Nasıl isterseniz.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Pekâlâ, 5.000 sekizlik için oynayalım.";
			link.l1 = "Hadi başlayalım!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 5000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            SetNPCQuestDate(npchar, "Card_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--

	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(IsUniformEquip()) dialog.text = "Affedersiniz, monsignor, ama şu anda bunun için vaktim yok. Belki bir dahaki sefere."; // Jason НСО
                else dialog.text = "Korsanlarla kumar oynamam!";
    			link.l1 = "Nasıl isterseniz.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "Neden olmasın! Dinlenmek kalbe iyi gelir... ama cebe gelmez...";
	    			link.l1 = "Mükemmel.";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "Oyunumuzun kuralları neler?";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "Hayır, bugünlük bu kadar. Yapacak işlerim var.";
	    			link.l1 = "Nasıl isterseniz.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "Pekâlâ, o zaman başlayalım!";
			link.l1.go = "Dice_begin";
			link.l3 = "Hayır, bu bana göre değil...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			dialog.text = "Önce bahiste anlaşalım.";
			link.l1 = "Her zar için 500 sekizlik oynayalım.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Her zar için 2.000 sekizlik oynayalım.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "Sanırım gitmem gerekiyor.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Sen nam salmış bir hilesin. Seninle kumar oynamam.";
                link.l1 = "Hepsi yalan! Neyse, boşver.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "Şaka mı yapıyorsun, "+GetAddress_Form(NPChar)+"? Paran yok!";
                link.l1 = "Olur böyle şeyler.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "Hepsi bu! Kumarla işim bitti – yoksa beni müsriflikle suçlayıp görevimden almaya kalkacaklar...";
                link.l1 = "Ne yazık.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Pekâlâ, 500 sekizlik için oynayalım.";
			link.l1 = "Hadi başlayalım!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 500;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Sen namlı bir hilesinsin. Seninle kumar oynamam.";
                link.l1 = "Hepsi yalan! Neyse, her neyse.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "Söylentilere göre çok iyi bir oyuncuymuşsunuz. Sizinle yüksek bahis oynamayacağım.";
                link.l1 = "Bahsi biraz düşürelim mi, ne dersiniz?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "Üzgünüm, ama gitmem gerekiyor.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "Şaka mı yapıyorsun, "+GetAddress_Form(NPChar)+"? 15.000 sekizlik altının yok!";
                link.l1 = "Onları büyüteceğim!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "Hayır, bu bahisler şehrin hazinesini kesinlikle boşaltacak.";
                link.l1 = "Nasıl isterseniz.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Pekâlâ, her zar için 2.000 sekizlik oynayalım.";
			link.l1 = "Hadi başlayalım!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 2000;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
		case "node_2":
			dialog.text = "Bu durumda, sizden çalışma odamı terk etmenizi ve işimden beni alıkoymamanızı rica edeceğim";
			link.l1 = "Evet, evet, tabii ki. Rahatsız ettiğim için özür dilerim.";
			link.l1.go = "exit";
		break;

		//---------------------------- генератор квестов мэра -------------------------------
		case "work": 
            dialog.text = "Bu bir hata. Bunu geliştiricilere bildir.";
        	link.l1 = "Teşekkürler, bu harika bir oyun!";
        	link.l1.go = "exit";
			
			//==> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "Şimdi olmaz! Teftiş var, don de Alamida şehirde. Ah, her yıl aynı şey, ben ne yaptım da bunu hak ettim...";
				link.l1 = "Dediğiniz gibi. Sizi oyalamayacağım.";
				link.l1.go = "exit"; 
				break;
			}
			//<== прибыла инспекция на Святом Милосердии
			//==> взят ли какой-либо квест
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{		 				
				//--> Федот, да не тот
				QuestName = pchar.GenQuest.questName;
				if (pchar.GenQuest.(QuestName).MayorId != npchar.id) 
				{					
					dialog.text = RandPhraseSimple("Gördüğüm kadarıyla, zaten valinin size verdiği bir göreviniz var "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Gen")+"Önce elindeki işi bitir, sonra konuşuruz.","Hmm, o sen değil miydin "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Voc")+" yerel valinin emirlerini aldığınız bir görev mi? Evet, doğru. Önce o görevi tamamlayın.");
					link.l1 = RandPhraseSimple("Anlıyorum...","Anlaşıldı..."+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+".");
					link.l1.go = "exit";					
					break;
				}
				//<--Федот, да не тот
				//-------- взят квест уничтожения банды ---------->>
				if (QuestName == "DestroyGang")
				{
					switch (pchar.GenQuest.DestroyGang)
					{
						makearef(arName, pchar.GenQuest.DestroyGang);
						case "":
							dialog.text = LinkRandPhrase("Haydutu bulma görevi "+GetFullName(arName)+" zaten sana verildi. Şimdi yerine getir!","Zaten   adında bir haydutu bulmak için bir göreviniz var "+GetFullName(arName)+". Sonuçları bekliyorum!","Sen burada konutumda boşuna zaman harcarken, "+GetFullName(arName)+" kolonistlerimizi soyuyor! Hemen işe koyulun!");
							link.l1 = RandPhraseSimple("Pekâlâ, "+GetAddress_FormToNPC(NPChar)+".","Onunla meşgulüm, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Sana verilen o haydutu bulup ortadan kaldırma süresi doldu. Ve sence bana ne tür raporlar geliyor? Söyleyeyim - "+GetFullName(arName)+" hâlâ hayatta ve sapasağlam! Şimdi kendini açıkla, "+GetAddress_Form(NPChar)+".","Sana o alçağı ortadan kaldırman için verilen süre "+GetFullName(arName)+", tükendi. Yine de bana hiçbir ilerleme kaydedilmediği söyleniyor. Neler oluyor?");
							link.l1 = "Verdiğiniz işi belirtilen sürede yerine getiremedim, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Peki, ne dersin? Bahsettiğim haydutu ortadan kaldırabildin mi? "+GetFullName(arName)+" nihayet öldü mü?","Bana sadece bir şey söyle - "+GetFullName(arName)+"  Ölü mü, diri mi? ");
							link.l1 = "Maalesef, hâlâ hayattayım, "+GetAddress_FormToNPC(NPChar)+". Onu bulmayı başardım, ama karşısında yetersiz kaldım ve geri çekilmek zorunda kaldım. O haydut tam bir belaymış. Üzgünüm.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Peki, ne dersiniz? Bahsettiğim haydutu ortadan kaldırmayı başardınız mı? "+GetFullName(arName)+" nihayet öldü mü?","Bana sadece bir şey söyle - "+GetFullName(arName)+"   ölü ya da diri mi? ");
							link.l1 = "O öldü, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 180);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контркурьер ---------->>
				if (QuestName == "TakePostcureer")
				{
					switch (pchar.GenQuest.TakePostcureer)
					{
						case "":
							dialog.text = LinkRandPhrase("Sana zaten bir kurye gemisini ele geçirme görevi verildi. Şimdi onu yerine getir!","Zaten bir kurye gemisini ele geçirmek için bir göreviniz var! Sonuçları bekliyorum!","Sen burada evimde boş boş oyalanırken, ihtiyacım olan belgeler düşmanımızın eline geçiyor! Hadi, işine bak!");
							link.l1 = RandPhraseSimple("Pekâlâ, "+GetAddress_FormToNPC(NPChar)+".","Onunla meşgulüm, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Sana verilen o kuryeyi bulup ele geçirme süresi doldu. Ve sence bana ne tür raporlar geliyor, biliyor musun? Söyleyeyim – beklediğim belgeler doğrudan düşmanımızın eline geçti! Şimdi lütfen kendini açıkla, "+GetAddress_Form(NPChar)+".","Sana verilen tüm süre boyunca kuryenin gemisinden belgeleri ele geçirmen gerekiyordu. Ancak hiçbir ilerleme kaydedilmemiş. Bu da ne demek oluyor?");
							link.l1 = "İşi zamanında bitiremedim, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Peki, ne dersin? Belgeleri ele geçirmeyi başardın mı?","Bana sadece bir şey söyle - yazışmaları ele geçirmeyi başardın mı?");
							link.l1 = "Maalesef, hayır, "+GetAddress_FormToNPC(NPChar)+". Gemiyi buldum, fakat belgelerden iz yok.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Peki, ne diyorsun? Belgeleri almayı başardın mı?","Bana sadece bir şey söyle - yazışmaları ele geçirmeyi başardın mı?");
							link.l1 = "Evet, "+GetAddress_FormToNPC(NPChar)+". Onlar bende. Buyurun.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							RemoveItems(pchar, "ContraPostLetters", 1);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контрфрахт - арсенал ---------->>
				if (QuestName == "TakeArsenalship")
				{
					switch (pchar.GenQuest.TakeArsenalship)
					{
						case "":
							dialog.text = LinkRandPhrase("Sana zaten bir askeri nakliye gemisini yok etme görevi verildi. Şimdi bunu yerine getir!","Zaten bir askeri nakliye gemisini yok etme görevin var! Sonuçları bekliyorum!","Sen burada konutumda boş boş oyalanırken, barut ve cephane düşman toplarına doğrudan teslim ediliyor! Hadi işe koyul!");
							link.l1 = RandPhraseSimple("Pekala, "+GetAddress_FormToNPC(NPChar)+".","Onunla meşgulüm, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Sana verilen o askeri nakliye gemisini bulup yok etme süresi doldu. Peki, sence bana ne tür raporlar geliyor? Söyleyeyim - düşman konvoyu hedefine başarıyla ulaşmış! Şimdi lütfen kendini açıkla, "+GetAddress_Form(NPChar)+".","Sana verilen düşman askeri nakliye gemisini yok etme süresi tamamen doldu. Yine de hiçbir ilerleme kaydedilmedi. Neler oluyor?");
							link.l1 = "Verdiğiniz görevi ayrılan sürede yerine getiremedim, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Peki, ne diyorsun? Düşman nakliye gemisini yok etmeyi başardın mı?","Bana sadece bir şey söyle - o düşman yükü şimdi denizin dibinde mi yatıyor?");
							link.l1 = "Maalesef, hayır, "+GetAddress_FormToNPC(NPChar)+". Konvoyu buldum, ancak gereken gemiyi batıramadım.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Peki, ne diyorsunuz? O düşman nakliye gemisini yok etmeyi başardınız mı?","Bana sadece bir şeyi söyle - düşman cephanesi şimdi denizin dibinde mi yatıyor?");
							link.l1 = "Evet, "+GetAddress_FormToNPC(NPChar)+". Düşmanımız o barut ve cephaneyi asla alamayacak.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 220);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- ОЗГ - пират ---------->>
				if (QuestName == "TakePirateship")
				{
					switch (pchar.GenQuest.TakePirateship)
					{
						case "":
							dialog.text = LinkRandPhrase("Sana zaten bir korsanı ortadan kaldırma görevi verildi. Şimdi onu yerine getir!","Zaten bir korsan gemisini yok etme görevin var! Sonuçları bekliyorum!","Sen burada evimde boş boş oyalanırken, o pis korsan başka bir kurbanı daha soyuyor! Hadi işe koyul!");
							link.l1 = RandPhraseSimple("Pekâlâ, "+GetAddress_FormToNPC(NPChar)+".","Bununla meşgulüm, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Sana verilen süre doldu, korsanı bulup ortadan kaldırmak için. Peki, sence bana ne tür raporlar geliyor? Söyleyeyim - o alçak korsan hâlâ gemilerimize saldırıyor! Şimdi lütfen kendini açıkla, "+GetAddress_Form(NPChar)+".","Sana korsan gemisini yok etmen için verilen tüm süre doldu. Yine de hiçbir ilerleme kaydedilmedi. Neler oluyor?");
							link.l1 = "Verdiğiniz işi zamanında bitiremedim, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Peki, ne diyorsun? Korsan gemisini yok etmeyi başardın mı?","Söyle bana tek bir şey - o pis korsan sonunda denizin dibinde mi yatıyor?");
							link.l1 = "Maalesef, hayır, "+GetAddress_FormToNPC(NPChar)+" O alçağı bulmayı başardım, ama gemisini batıramadım.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Peki, ne diyorsun? Korsan gemisini yok etmeyi başardın mı?","Söyle bana tek bir şey - o pis korsan sonunda denizin dibinde mi yatıyor?");
							link.l1 = "Evet, "+GetAddress_FormToNPC(NPChar)+". O alçak artık tüccar gemilerimizi rahatsız edemeyecek.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 250);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
					//-------- ОЗГ - пассажир ---------->>
				if (QuestName == "TakePassenger")
				{
					switch (pchar.GenQuest.TakePassenger)
					{
						case "":
							dialog.text = LinkRandPhrase("Sana zaten bir suçluyu yakalama görevi verildi. Şimdi onu yerine getir!","Zaten bir suçluyu bulmak için bir göreviniz var! Sonuçları bekliyorum!","Sen burada evimde boş boş oyalanırken, o pis hain hâlâ denizlerde dolaşıyor! Sana verilen görevi derhal yerine getir!");
							link.l1 = RandPhraseSimple("Pekâlâ, "+GetAddress_FormToNPC(NPChar)+".","Bununla meşgulüm, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Sana verilen o alçağı bulma süresi doldu. Peki, sence bana ne tür raporlar geliyor? Söyleyeyim - adam hedefine sağ salim ulaşmış ve sonra ortadan kaybolmuş! Şimdi, lütfen bana bir açıklama yap, "+GetAddress_Form(NPChar)+".","Sana suçluyu bulman için verilen tüm süre doldu. Yine de hiçbir ilerleme kaydedilmedi. Neler oluyor?");
							link.l1 = "Belirtilen sürede görevinizi yerine getiremedim, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Peki, ne diyorsun? Suçluyu yakaladın mı?","Bana sadece bir şey söyle - o alçak herif şu anda ambarında, ağzı tıkalı ve zincire vurulmuş halde mi?");
							link.l1 = "Maalesef, hayır, "+GetAddress_FormToNPC(NPChar)+". Kötüyü yakalayamadım. Bulunduğu gemiyle birlikte denize gömüldü.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Peki, ne diyorsun? Caniyi yakaladın mı?","Bana sadece bir şey söyle - o pis alçak şu anda ambarında, ağzı bağlanmış ve zincirlenmiş halde mi?");
							link.l1 = "Evet, "+GetAddress_FormToNPC(NPChar)+". Lütfen askerlerinizi iskeleye gönderin, onu size teslim edeceğim.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 250);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.TakePassenger.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							sld.lifeday = 0;
						break;
					}
				}
				//-------- таможенный патруль ---------->>
				if (QuestName == "CustomPatrol")
				{
					switch (pchar.GenQuest.CustomPatrol)
					{
						case "":
							dialog.text = LinkRandPhrase("Kaçakçıları bulma görevi zaten sana verildi. Şimdi onu yerine getir!","Kaçakçıları bulmak için zaten bir göreviniz var! Sonuçları bekliyorum!","Sen burada konutumda vaktini harcarken, o kaçakçılar yeni bir anlaşma yapmaya hazırlanıyor! Sana verilen görevi derhal yerine getir!");
							link.l1 = RandPhraseSimple("Pekâlâ, "+GetAddress_FormToNPC(NPChar)+".","Onunla meşgulüm, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Sana kaçakçıları bulman için verilen süre doldu. Ve sence bana ne tür raporlar geliyor? Söyleyeyim – mallarını keyifle satmışlar! Şimdi lütfen kendini açıkla, "+GetAddress_Form(NPChar)+".","Sana kaçakçıları bulman için verilen tüm süre doldu. Hâlâ hiçbir ilerleme kaydedilmedi. Neler oluyor?");
							link.l1 = "Verdiğiniz görevi zamanında tamamlayamadım, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Peki, ne diyorsun? Kaçakçılarla ilgilendin mi?","Bana sadece bir şey söyle - kaçakçıların anlaşmasını bozduğun mu?");
							link.l1 = "Maalesef, hayır, "+GetAddress_FormToNPC(NPChar)+". O alçakların planlarını bozmayı başaramadım.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Peki, ne diyorsun? Kaçakçılarla ilgilendin mi?","Bana sadece bir şeyi söyle - o kaçakçıların işini bozmayı başardın mı?");
							link.l1 = "Evet, "+GetAddress_FormToNPC(NPChar)+". Onlara yetiştim ve hem alıcının hem de satıcının gemilerini yok ettim.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 300);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- Дезертир ---------->>
				if (QuestName == "FindFugitive")
				{
					switch (pchar.GenQuest.FindFugitive)
					{
						case "":
							dialog.text = LinkRandPhrase("Kaçak askeri bulma görevi zaten sana verildi. Şimdi onu yerine getir!","Kaçağı bulmak için zaten bir göreviniz var! Sonuçları bekliyorum!","Sen burada konutumda boş boş oyalanırken, o firari devlet sırlarımızı ele veriyor olabilir! Sana verilen görevi derhal yerine getir!");
							link.l1 = RandPhraseSimple("Pekala, "+GetAddress_FormToNPC(NPChar)+".","Onunla meşgulüm, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Sana verilen firariyi bulma süresi doldu. Peki, sence bana ne tür raporlar geliyor? Söyleyeyim – hiçbiri, tamamen hiçbir şey! Şimdi, kendini açıkla bakalım, "+GetAddress_Form(NPChar)+".","Sana firariyi bulman için verilen tüm süre doldu. Yine de hiçbir ilerleme kaydedilmedi. Neler oluyor?");
							link.l1 = "İşinizi zamanında tamamlayamadım, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Peki, ne diyorsunuz? Firariyi yakaladınız mı?","Bana tek bir şey söyle - o firari şu anda ambarında, ağzı bağlı ve zincirlenmiş halde mi?");
							link.l1 = "Maalesef, hayır, "+GetAddress_FormToNPC(NPChar)+". O alçağı yakalayamadım. İzini şu yerleşimde buldum: "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.City)+", ama ben gelmeden bir gün önce bir korsan gemisiyle güneye gitmiş. Sanırım artık o şanslı beyefendilerle birlikte.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Pekâlâ... İşte bizim "+pchar.GenQuest.FindFugitive.Name+"... Harika iş çıkardınız, kaptan! Ararken zorlandınız mı?","Ah, ne misafirlerimiz var! Merhaba, "+pchar.GenQuest.FindFugitive.Name+"Harika iş çıkardınız, kaptan! Aramanız için çok mu çaba harcadınız?");
							link.l1 = "Nasıl söylenir, "+GetAddress_FormToNPC(NPChar)+". Her neyse, göreviniz başarıyla tamamlandı.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 300);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar, "authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.FindFugitive.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							LAi_SetActorType(sld);
							sld.lifeday = 0;
							pchar.quest.FindFugitive_Over.over = "yes"; //снимаем таймер
							chrDisableReloadToLocation = false;//открыть локацию
						break;
					}
				}
				//------ проникновение во враждебный город ------------>>
				if (QuestName == "Intelligence")
				{
					switch (pchar.GenQuest.Intelligence)
					{
						case "":
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								dialog.text = RandPhraseSimple("Sana verilen mektubu teslim etme süresi doldu. Ve anladığım kadarıyla başarısız oldun.","Süre doldu. Yine de hiçbir ilerleme kaydedilmedi. Ne oluyor?");
								link.l1 = "İşinizi tamamlayamadım, "+GetAddress_FormToNPC(NPChar)+".";
								link.l1.go = "All_Late";	
							}
							else
							{
								dialog.text = LinkRandPhrase("Bana bir mektup teslim etme görevi zaten sana verildi. Şimdi bunu yerine getir!","Zaten bana doğrudan bir mektup teslim etme görevin var! Sonuçları bekliyorum, o mektuba en kısa sürede ihtiyacım var!","Sen burada konutumda vaktini boşa harcarken, acilen ihtiyaç duyduğum bilgi hâlâ bana ulaştırması gereken kişinin elinde! Sana verilen görevi derhal yerine getir!");
								link.l1 = RandPhraseSimple("Pekala, "+GetAddress_FormToNPC(NPChar)+".","Hemen halledeceğim, "+GetAddress_FormToNPC(NPChar)+".");
								link.l1.go = "exit";	
							}
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Beklediğim mektubu teslim ettin mi?","Söyle şimdi – o sende mi?!");
							link.l1 = "Evet, biliyorum. Anlaştığımız gibi – şahsen size teslim edildi.";
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								link.l1.go = "Intelligence_ExecuteLate";
								AddCharacterExpToSkill(PChar, "Sneak", 300);
							}
							else
							{
								link.l1.go = "All_Execute";		
								AddCharacterExpToSkill(PChar, "Leadership", 100);
								AddCharacterExpToSkill(PChar, "Sneak", 300);
							}
							TakeItemFromCharacter(pchar, "sicretLetter");
							DeleteAttribute(ItemsFromID("sicretLetter"), "City");
							DeleteAttribute(ItemsFromID("sicretLetter"), "Mayor");
						break;
					}
				}
				break;
			}
			else
			{
				if(sti(pchar.reputation.nobility) > 41) {dialog.text = " Bana emanet edilen topraklarda kanunsuzluğa karşı elimden gelen her şeyi yapıyorum ve sizin gibi onurlu kaptanlar için her zaman görevlerim var. Ne tür görevler üstlenmek istersiniz? ";}
				else {dialog.text = "Yetkim altındaki topraklarda düzeni sağlamak için elimden geleni yapıyorum, Kaptan, sizin gibi ünü büyük biri için bile bir görevim var. Yeteneklerinizi hangi tür görevlerde kullanmak istersiniz?";}
				link.l1 = "Sömürge içindeki ve çevresindeki meselelerle ilgilenmek istiyorum.";
				link.l1.go = "GovQuestGroup1";
				link.l2 = "Bölgenizin dışında yürütülen operasyonlara katılmayı tercih ederim.";
				link.l2.go = "GovQuestGroup2";
				link.l3 = "Uluslararası ilişkileri etkileyebilecek ve   konumunu güçlendirebilecek yüksek riskli görevlerle ilgileniyorum "+NationNameGenitive(sti(NPChar.nation))+".";
				link.l3.go = "GovQuestGroup3";
				link.l4 = "Özür dilerim — şu anda herhangi bir sorumluluk almak istemiyorum.";
				link.l4.go = "exit";
			}
			break;
			
			case "GovQuestGroup1":
			// Группа 1 - Местные
			if (CheckAttribute(npchar, "work_date") && GetNpcQuestPastDayParam(npchar, "work_date") <= 1)
			{
				dialog.text = RandPhraseSimple("Bugün senin için bu tür bir işim yok. Belki yarın tekrar gelirsin...","Maalesef, şu anda bu tür bir görevim yok. Birkaç gün sonra tekrar gelmeyi deneyin.","Bugün sana böyle bir yük veremem. Başka bir zaman seni görmekten memnuniyet duyarım.");
				link.l1 = "Anladım. "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "exit";
				break;
			}
			pchar.GenQuest.Governor.Group1.index = hrand(2);
			i = pchar.GenQuest.Governor.Group1.index;
			switch (i)
			{
				case 0: // Отказ
					dialog.text = RandPhraseSimple("Bugün senin için bu tür bir işim yok. Belki yarın tekrar uğrarsın...","Ne yazık ki, şu anda bu tür bir görevim yok. Bir iki gün sonra tekrar uğramayı deneyin.","Bugün sana böyle bir yük veremem. Başka bir zaman seni görmekten memnuniyet duyarım.");
					link.l1 = RandPhraseSimple("Ne yazık...","Ah, ne yazık, "+GetAddress_FormToNPC(NPChar)+". ");
					link.l1.go = "exit";
				break;
						
				case 1: // Таможенный патруль
					if (CheckAttribute(pchar, "GenQuest.Governor.Group1.day") && sti(pchar.GenQuest.Governor.Group1.day) == GetDataDay())
					{
						dialog.text = "Fikriniz mi değişti, Kaptan? Kaçakçılar hâlâ ortalıkta ve muhtemelen planlarından vazgeçmiş değiller.";
						link.l1 = "Lütfen bana bu görevin detaylarını hatırlatır mısınız, Ekselansları?";
						link.l1.go = "CustomPatrol";
						link.l2 = RandPhraseSimple("Üzgünüm, ama şu anda bu görevi üstlenmeye hazır değilim.","Ne yazık ki şu anda bu görevi yerine getiremiyorum.","Özür dilerim — bu görevi üstlenmeye henüz hazır değilim.");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "Tam zamanında geldiniz, kaptan. Kolonimize kaçak mal sokulmasıyla ilgili acil bir meseleyle ilgilenmem gerekiyor. Geminiz denize elverişli ve savaşa hazır sanırım?";
					link.l1 = "Gemicim her zaman denize uygun ve savaşa hazırdır. Lütfen, yaklaşan görev hakkında daha fazla bilgi verin, ekselansları.";
					link.l1.go = "CustomPatrol";
				break;
						
				case 2: // Уничтожение банды
					if (CheckAttribute(pchar, "GenQuest.Governor.Group1.day") && sti(pchar.GenQuest.Governor.Group1.day) == GetDataDay())
					{
						dialog.text = "Demek sonunda haydutları ortadan kaldırma görevini üstlenmeye karar verdiniz, Kaptan? Ne yazık ki, hâlâ kolonimizin huzuru için tehdit oluşturmaya devam ediyorlar.";
						link.l1 = "Lütfen bana bu görevin ayrıntılarını hatırlatır mısınız, Ekselansları?";
						link.l1.go = "DestroyGang";
						link.l2 = RandPhraseSimple("Üzgünüm, ama şu anda bu görevi üstlenmeye hazır değilim.","Şu anda bu görevi yerine getiremeyeceğim, üzgünüm.","Özür dilerim — bu görevi üstlenmeye henüz hazır değilim.");
						link.l2.go = "exit";
						break;
					}
					pchar.GenQuest.DestroyGang.Terms = hrand(2) + 2;
					pchar.GenQuest.DestroyGang.Money = ((hrand(6)+4)*500)+5000+(sti(pchar.rank)*500);
					makearef(arName, pchar.GenQuest.DestroyGang);
					arName.nation = PIRATE;
					arName.sex = "man";
					SetRandomNameToCharacter(arName);
					dialog.text = "Şu anda senin için bir görevim var. Yakındaki ormanda "+XI_ConvertString("Colony"+npchar.city+"Gen")+" bir grup haydut ortaya çıktı ve liderlerinin adının  [[[VARx]]]  olduğunu biliyorum "+GetFullName(arName)+" . Bu haydut çetesini bulup ortadan kaldırın.";
					link.l1 = "Şartlar konusunda bir şekilde sınırlı mıyım?";
					link.l1.go = "DestroyGang";
				break;
			}
		break;

		case "GovQuestGroup2":
			// Группа 2 - За границами острова, но не государственные
			if (CheckAttribute(npchar, "work_date") && GetNpcQuestPastDayParam(npchar, "work_date") <= 1)
			{
				dialog.text = RandPhraseSimple("Bugün sana bu tür bir işim yok. Belki yarın tekrar gelirsin...","Maalesef, şu anda bu türde bir görevim yok. Bir iki gün sonra tekrar uğramayı deneyin.","Bugün sana böyle bir yük veremem. Başka bir zaman seni görmekten memnun olurum.");
				link.l1 = RandPhraseSimple("Ne yazık...","Ah, ne yazık, "+GetAddress_FormToNPC(NPChar)+". ");
				link.l1.go = "exit";
				break;
			}
			pchar.GenQuest.Governor.Group2.index = hrand(3);
			i = pchar.GenQuest.Governor.Group2.index;
			switch (i)
			{
				case 0: // Нет заданий
					dialog.text = RandPhraseSimple("Bugün sana bu tür bir işim yok. Belki yarın tekrar gel...","Maalesef, şu anda bu tür bir görevim yok. Birkaç gün sonra tekrar uğramayı deneyin.","Bugün sana böyle bir yük veremem. Başka bir zaman seni görmekten memnuniyet duyarım.");
					link.l1 = RandPhraseSimple("Ne yazık...","Ah, ne yazık, "+GetAddress_FormToNPC(NPChar)+". ");
					link.l1.go = "exit";
				break;
						
				case 1:  // ОЗГ - захватить пассажира
					if (CheckAttribute(pchar, "GenQuest.Governor.Group2.day") && sti(pchar.GenQuest.Governor.Group2.day) == GetDataDay())
					{
						dialog.text = "Kendini kanıtlama fırsatını kaçırmamaya mı karar verdin? O alçağı sağ istiyorum — hem de mümkün olan en kısa sürede.";
						link.l1 = "Lütfen bana bu görevin ayrıntılarını hatırlatır mısınız, Ekselansları?";
						link.l1.go = "TakePassenger";
						link.l2 = RandPhraseSimple("Üzgünüm, ama şu anda bu görevi üstlenmeye hazır değilim.","Ne yazık ki bu görevi şu anda yerine getiremiyorum.","Özür dilerim — bu görevi üstlenmeye henüz hazır değilim.");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "Tam zamanında geldiniz, efendim. Size tam uygun acil bir görevim var. Belirli bir kişiyi bulup yakalamanız gerekiyor...";
					link.l1 = "Bir insan avı mı? Benden tam olarak ne beklediğinizi daha ayrıntılı anlatır mısınız?";
					link.l1.go = "TakePassenger";
				break;
						
				case 2: // Найти дезертира
					if (CheckAttribute(pchar, "GenQuest.Governor.Group2.day") && sti(pchar.GenQuest.Governor.Group2.day) == GetDataDay())
					{
						dialog.text = "Fikriniz mi değişti, Kaptan? Sonunda kaçak peşine düşmeye karar verdiniz mi?";
						link.l1 = "Lütfen bana bu görevin ayrıntılarını hatırlatır mısınız, Ekselansları.";
						link.l1.go = "FindFugitive";
						link.l2 = RandPhraseSimple("Üzgünüm, ama şu anda bu görevi üstlenmeye hazır değilim.","Ne yazık ki şu anda bu görevi yerine getiremiyorum.","Özür dilerim — bu görevi üstlenmeye henüz hazır değilim.");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "Karayipler'deki birkaç yerleşimi ziyaret etmeni gerektiren bir görevim var. Uzun bir yolculuğa hazır mısın?";
					link.l1 = "Evet, adamlarım ve ben hemen yola çıkmaya hazırız. Tam olarak ne yapmam gerekecek?";
					link.l1.go = "FindFugitive";
				break;
						
				case 3: // Уничтожить корабль пиратов
					if (CheckAttribute(pchar, "GenQuest.Governor.Group2.day") && sti(pchar.GenQuest.Governor.Group2.day) == GetDataDay())
					{
						dialog.text = " Korsan hâlâ tüccarlara saldırıyor, Kaptan. Bu sefer onunla başa çıkmaya hazır mısınız? ";
						link.l1 = "Lütfen bu görevin ayrıntılarını bana tekrar hatırlatır mısınız, Ekselansları?";
						link.l1.go = "TakePirateship";
						link.l2 = RandPhraseSimple("Üzgünüm, ama şu anda bu görevi üstlenmeye hazır değilim.","Ne yazık ki bu görevi şu anda yerine getiremiyorum.","Özür dilerim — bu görevi üstlenmeye henüz hazır değilim.");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "Evet, senin için önemli bir görevim var. Bunu yerine getirmek için tüm yeteneklerini kullanman gerekecek. Bu iş korsanları ilgilendiriyor...";
					link.l1 = "Korsanlar mı? O halde, benden tam olarak ne beklediğinizi daha ayrıntılı anlatır mısınız?";
					link.l1.go = "TakePirateship";
				break;
			}
		break;

		case "GovQuestGroup3":
			// Группа 3 - Государственные разборки, тяжелые бои
			if (CheckAttribute(npchar, "work_date") && GetNpcQuestPastDayParam(npchar, "work_date") <= 1)
			{
				dialog.text = RandPhraseSimple("Bugün sana bu türden bir işim yok. Belki yarın tekrar gelirsin...","Maalesef, şu anda bu tür bir görevim yok. Birkaç gün sonra tekrar uğramayı deneyin.","Bugün sana böyle bir yük veremem. Başka bir zaman seni görmekten memnuniyet duyarım.");
				link.l1 = RandPhraseSimple("Ne yazık...","Ah, ne yazık, "+GetAddress_FormToNPC(NPChar)+". ");
				link.l1.go = "exit";
				break;
			}
			pchar.GenQuest.Governor.Group3.index = hrand(3);
			i = pchar.GenQuest.Governor.Group3.index;
			switch (i)
			{
				case 0: // Отказ
					dialog.text = RandPhraseSimple("Bugün sana verebileceğim böyle bir işim yok. Belki yarın tekrar gelirsin...","Maalesef, şu anda bu tür bir görevim yok. Bir iki gün sonra tekrar uğramayı deneyin.","Bugün sana böyle bir yük veremem. Seni başka bir zaman görmekten memnuniyet duyarım.");
					link.l1 = RandPhraseSimple("Ne yazık...","Ah, ne yazık, "+GetAddress_FormToNPC(NPChar)+". ");
					link.l1.go = "exit";
				break;
						
				case 1: // Контркурьер
					if (CheckAttribute(pchar, "GenQuest.Governor.Group3.day") && pchar.GenQuest.Governor.Group3.day == GetDataDay())
					{
						dialog.text = "Zaman daralıyor. Var mısın, yoksa yine sadece sohbet etmeye mi geldin?";
						link.l1 = "Lütfen bu görevin ayrıntılarını bana tekrar hatırlatır mısınız, Ekselansları.";
						link.l1.go = "TakePostcureer";
						link.l2 = RandPhraseSimple("Üzgünüm, ama şu anda bu görevi üstlenmeye hazır değilim.","Şu anda bu görevi yerine getiremeyeceğim, üzgünüm.","Özür dilerim — bu görevi üstlenmeye henüz hazır değilim.");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "Evet, senin için bir görevim var. Bunu yerine getirmek için hem çevikliğini hem de deniz savaşındaki yeteneğini göstermen gerekecek. Değerini kanıtlamaya hazır mısın?";
					link.l1 = "Majesteleri, görev hakkında daha fazla ayrıntı verebilir misiniz?";
					link.l1.go = "TakePostcureer";
				break;
						
				case 2: // Контрфрахт - уничтожить корабль с арсеналом
					if (CheckAttribute(pchar, "GenQuest.Governor.Group3.day") && pchar.GenQuest.Governor.Group3.day == GetDataDay())
					{
						dialog.text = "Demek sonunda cesaretini topladın, Kaptan? Düşmanın erzaklarına saldırmaya hazır mısın?";
						link.l1 = "Lütfen bana bu görevin ayrıntılarını hatırlatır mısınız, Ekselansları?";
						link.l1.go = "TakeArsenalship";
						link.l2 = RandPhraseSimple("Üzgünüm, ama şu anda bu görevi üstlenmeye hazır değilim.","Üzgünüm, bu görevi şu anda yerine getiremiyorum.","Özür dilerim — bu görevi üstlenmeye henüz hazır değilim.");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "Evet, senin için bir görevim var. Bunu yerine getirmek için olağanüstü bir cesaret ve deniz savaşında da biraz yetenek göstermen gerekecek. Değerini kanıtlamaya hazır mısın?";
					link.l1 = "Majesteleri, yaklaşan görev hakkında daha fazla ayrıntı paylaşabilir misiniz?";
					link.l1.go = "TakeArsenalship";;
				break;
						
				case 3: // Проникновение во враждебный город
					if (CheckAttribute(pchar, "GenQuest.Governor.Group3.day") && pchar.GenQuest.Governor.Group3.day == GetDataDay())
					{
						dialog.text = "Bu görevi zaten sormuştunuz, Kaptan. Umarım bu sefer sadece meraktan sormuyorsunuzdur?";
						link.l1 = "Lütfen bu görevin ayrıntılarını bana tekrar hatırlatır mısınız, Ekselansları?";
						link.l1.go = "Intelligence";
						link.l2 = RandPhraseSimple("Üzgünüm, ama şu anda bu görevi üstlenmeye hazır değilim.","Ne yazık ki bu görevi şu anda yerine getiremiyorum.","Özür dilerim — bu görevi üstlenmeye henüz hazır değilim.");
						link.l2.go = "exit";
						break;
					}
					sTemp = GetSpyColony(npchar);
					if (sTemp == "none")
					{
						dialog.text = RandPhraseSimple("Bugün senin için bu tür bir işim yok. Belki yarın tekrar gelirsin...","Maalesef, şu anda bu tür bir görevim yok. Bir iki gün sonra tekrar uğrayın.","Bugün sana böyle bir yük veremem. Başka bir zaman seni görmekten memnuniyet duyarım.");
						link.l1 = "Anladım. "+GetAddress_FormToNPC(NPChar)+".";
						link.l1.go = "exit";
						break;
					}
					pchar.GenQuest.Intelligence.Terms = hrand(10) + (42 - MOD_SKILL_ENEMY_RATE);
					pchar.GenQuest.Intelligence.Money = ((hrand(5)+11)*2000)+(sti(pchar.rank)*1500);
					pchar.GenQuest.Intelligence.City = sTemp;
					sTemp = ", which is on " + XI_ConvertString(GetIslandByColony(&colonies[FindColony(pchar.GenQuest.Intelligence.City)])+"Dat");
					dialog.text = "Sana vereceğim bir görev var, ama oldukça ciddi riskler içeriyor. Gizlice girmene ihtiyacım var "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc")+sTemp+", orada belirli bir kişiyle buluş ve sana ne verirse bana getir.";
					link.l1 = "Hmm, sanmıyorum ki o konuda "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat")+" Misafirliğim memnuniyetle karşılanacak...";
					link.l1.go = "Intelligence";
				break;
			}
		break;
		//---------------------------- генератор квестов мэра -------------------------------

		case "sell_prisoner":
            dialog.text = "Kimi fidye ile kurtarmak istersiniz?";

            qty = 1;
            for(i=0; i < GetPassengersQuantity(pchar); i++)
            {
                cn = GetPassenger(pchar,i);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if(CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                            attrLoc = "l"+qty;
                            link.(attrLoc)    = GetFullName(offref) + " - " + NationNameMan(sti(offref.nation)) + ".";
                            link.(attrLoc).go = "GetPrisonerIdx_" + offref.index;
                            qty++;
                        }
                    }
                }
            }
			link.l99 = "Hiç kimse.";
			link.l99.go = "exit";
		break;
		
		case "sell_prisoner_2":
            offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
            attrLoc =  "So, this is captain " + GetFullName(offref) + ", " + NationNameMan(sti(offref.nation))+ ".";
            // цена зависит от губернатора
            qty = makeint(sti(offref.rank)*(800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L)*100) + GetCharacterSkillToOld(offref, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500);
			if(HasShipTrait(pchar, "trait14")) qty = makeint(qty * 1.35);
            if (sti(offref.nation) == sti(NPChar.nation))
            {
                attrLoc = attrLoc + " I am ready to pay the ransom for my compatriot in the amount of  " + FindRussianMoneyString(qty) + ".";
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    qty = qty / 5;
                    attrLoc = attrLoc + " I can give " + FindRussianMoneyString(qty) + "  for this gallowsbird. And then we'll execute the scoundrel at once.";

                }
                else
                {
                    qty = qty / 2;
                    attrLoc = attrLoc + " " + FindRussianMoneyString(qty) + "for that man, not a peso more.";
                }
            }
			dialog.text = attrLoc;
			pchar.PrisonerSellPrice =  qty;
			link.l1 = "Anlaştık. Artık tamamen senin, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "sell_prisoner_3";
			link.l3 = "Hayır. Bu olmaz.";
			link.l3.go = "exit";
		break;


		case "sell_prisoner_3":
			dialog.text = "Bu iyi.";
			link.l1 = "Her şey gönlünüzce olsun.";
			link.l1.go = "exit";
			OfficersReaction("bad");

			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
			AddMoneyToCharacter(pchar, sti(pchar.PrisonerSellPrice));
			if (sti(offref.nation) == sti(NPChar.nation))
            {
                AddCharacterExpToSkill(pchar, "Commerce", 25);
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    ChangeCharacterComplexReputation(pchar,"nobility", -2);
                }
                else
                {
                    AddCharacterExpToSkill(pchar, "Commerce", 5);
                }
            }

        	offref.location = "";
        	ReleasePrisoner(offref); // освободили пленника
		break;
		////   CAPTURE //////////
		case "CAPTURE_Main":
            NextDiag.TempNode = "CAPTURE_Main";
			AfterTownBattle();  // всё, все свободны
			
			// --> Левассер
			if (pchar.location == "Tortuga_townhall" && CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga"))
			{
                dialog.Text = "Arrgh! Bu ne rezalet, de Maure? Fransızlar ne zamandan beri kendi vatandaşlarına saldırıyor?!";
                Link.l1 = "Guvernör-General François Longvilliers de Poincy'nin emriyle, siz, Bay Levasseur, Tortuga valiliği görevinden alındınız ve idama mahkûm edildiniz! Ve bu hükmü yerine getirecek olan kişi benim!";
                Link.l1.go = "levasser";
				break;
			}
			// <-- Левассер
            // fix от грабежа 5 раз на дню -->
            if (!CheckNPCQuestDate(npchar, "GrabbingTownDate"))
			{
                dialog.Text = "Zaten her şeyi aldınız. Daha ne istiyorsunuz?";
                Link.l1 = "Evet, tabii, yanlış şehir.";
                Link.l1.go = "Exit_City";

                NPChar.NoGiveMoney = true;

            	ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 20);
                // вернём диалог после разговора и спрячем
                SetReturn_Gover_Dialog_Exit(NPChar);
				break;
			}
			SetNPCQuestDate(npchar, "GrabbingTownDate");
			// fix от грабежа 5 раз на дню <--

            if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)
            { // а форт-то ЖИВ, значит с суши прошли
                dialog.Text = "Eşi benzeri görülmemiş bir küstahlık! Kaleden takviye kuvvetler yakında gelecek ve bunun bedelini ödeyeceksin!";
                Link.l2 = "Onlar gelene kadar burada kalmayacağım. Sadece paramı ver, bu şehirden gidelim.";
                Link.l2.go = "Summ";
                Pchar.HalfOfPaymentByCity = true; // токо половина денег
            }
            else
            {
				dialog.Text = "Bu sefer kazandın, ama bil ki korsan avcılarımızdan oluşan bir filo seni bulup, o pis korsan bedeninden her bir pesoyu söküp alacak!";
	            if (!bWorldAlivePause || bBettaTestMode)
	            {
	                int iColony = FindColony(npchar.city);
					if (!CheckAttribute(&colonies[iColony], "notCaptured")) //незахватываемые города
					{
						if (CheckAttribute(FortChref, "Default.Prison"))
	    				{
	    					Link.l1 = "Silence! This town belongs to me from now on; as for your piratehunters - I'll send them straight to Davy Jones' Locker. Hey lads, grab this pig and put it behind bars.";
	    				}
	    				else
	    				{
	    					Link.l1 = "Bu şehir artık bana ait. Çocuklar, eski valiyi yeni 'odalarına' kadar eşlik edin, heh heh.";
	    				}
	    				Link.l1.go = "City";
					}
				}
				if (!isCityHasFort(NPChar.City))
	            {
	                Link.l2 = "Kaledeki takviye kuvvetler mi? Bana cömert bir fidye öde, kasandan çekip gideriz.";
				}
				else
				{
	            	Link.l2 = "Bir grup korsan avcısı mı? Hmm... Sadece paramı verin, kasabanızdan çekip gidelim.";
	            }
				Link.l2.go = "Summ";

                bOk = !bWorldAlivePause || bBettaTestMode;
	            if (isMainCharacterPatented() && bOk && !CheckAttribute(&colonies[iColony], "notCaptured")) //не даем захватить колонию
	            {
					// восстановим нацию патента
					PChar.nation = GetBaseHeroNation();
					
					dialog.Text = "Eşi benzeri görülmemiş bir küstahlık!   Nasıl cüret edersin   bir koloniye saldırmaya, üstelik   "+NationNameGenitive(sti(NPChar.nation))+"?! Dökülen kanın ve devletimize verdiğin zarar için ağır bedel ödeyeceksin.";
	                Link.l1 = "Bu andan itibaren, bu koloni bana ait. Otoriteme karşı çıkan herkes doğrudan cehenneme gider.";
	                Link.l1.go = "City_patent";
	                Link.l2 = "Geri çekil.  Ben  adına hareket ediyorum. "+NationNameGenitive(sti(PChar.nation))+". Bundan böyle, bu koloni artık  "+NationKingsCrown(PChar)+"!";
	                Link.l2.go = "City_nation";
	                Link.l3 = "Ne güzel bir kasabanız var. Eğer burası kül olup valiniz de meydanda asılsa gerçekten büyük bir felaket olurdu. Bu felaketi önlemek için ödemeye razı olduğunuz fidyenin miktarını konuşmalıyız. ";
	                Link.l3.go = "Summ_patent";
	            }
            }
        break;
		
		// --> Левассер
		case "levasser":
            dialog.Text = "Poincy mi?! Lanet olsun o papaz herifine! Onunla ben ilgileneceğim... ve sana gelince, alçak, işin bitti! Buradan sağ çıkamayacaksın – sonunu kendi ellerimle getireceğim!";
			Link.l1 = "Bana vaaz verme, kafir. Hugenot ruhunu Cehennem'e gönderdiğimde, Lucifer'e ve Jean Calvin'e selamlarımı ilet. Silahını çek!";
			Link.l1.go = "levasser_1";
        break;
		
		case "levasser_1":
			chrDisableReloadToLocation = true;//закрыть локацию
            DialogExit();
			LAi_SetImmortal(npchar, false);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto6");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LevasserDiedResidence");
			AddDialogExitQuest("MainHeroFightModeOn");	
        break;
		// <-- Левассер
        
        case "City":
            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 40);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 400);

            Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
            AddDialogExitQuest("Residence_Captured_Any");

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            // ремонт
            RepairAllShips();
            Log_Info("All ships have been repaired.");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t3");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
            NextDiag.CurrentNode = "Prison";
			DialogExit();
        break;

        case "City_patent":
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -20); // пираты мы, но у нас патент
            dialog.Text = "Bu sefer kazandın, ama bil ki filomuz yakında gelecek ve senden geriye hiçbir şey bırakmayacak!";
			Link.l1 = "Shut your mouth. This town belongs to me from now on; as for your squadron - I'll send it straight to Hell. Boys, escort the ex-governor to his new 'quarters', heh heh.";
			Link.l1.go = "City";
        break;

        case "Exit_for_pay":
			dialog.Text = "Benden başka ne istiyorsunuz?";
            Link.l1 = "Bir şeyi atladım mı diye kontrol ediyorum...";
            Link.l1.go = "exit";

            NextDiag.TempNode = "Exit_for_pay";
		break;

        case "Exit_City":
		    NextDiag.CurrentNode = "Exit_for_pay";
		    Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
		    if (sti(NPChar.NoGiveMoney) == false) // себе берем
		    {
				// вернём диалог после разговора и спрячем
				SetReturn_Gover_Dialog_Exit(NPChar);
				AddDialogExitQuestFunction("TWN_ExitForPay");
            }
            DialogExit();
        break;

        case "Summ":
            dialog.Text = "Şartlarınıza razı olmaktan başka çarem yok. Alın lanet paranızı ve derhal kolonimizden gidin.";
            Link.l1 = "Sizinle iş yapmak bir zevkti.";
            Link.l1.go = "Exit_City";
            NPChar.NoGiveMoney = false;

            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 30);
            AddCharacterExpToSkill(GetMainCharacter(), SKILL_FORTUNE, 300);
            AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 300);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t2");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
        break;

        case "Summ_patent":
            dialog.Text = "Pekâlâ, şartlarını söyle...";
            Link.l1 = "Evet, vay haline! Paranı saymaya başla.";
            Link.l1.go = "Summ";
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -10); // не на службе
        break;

        case "City_nation":
			dialog.Text = "Pekâlâ, merhametine sığınıyoruz.";
			Link.l1 = "Sana tavsiyem, mümkün olan en kısa sürede kasabadan ayrılman. Yaklaşan değişiklikler sağlığın için pek iyi olmayabilir. Hoşça kal.";
			Link.l1.go = "Exit_City";
			NPChar.NoGiveMoney = true;

            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", 5);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 600);
            AddCharacterExpToSkill(GetMainCharacter(), "Sneak", 400);
            SetNationRelationBoth(sti(PChar.nation), sti(NPChar.nation), RELATION_ENEMY);

            PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
            PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
            SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
            DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
            AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка
            //  СЖ -->
	    	sTemp =  GetNationNameByType(sti(PChar.nation));
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t1");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
			//  СЖ <--
			AddTitleNextRate(sti(PChar.nation), 1);  // счетчик звания
            SetCharacterRelationBoth(sti(FortChref.index), GetMainCharacterIndex(), RELATION_FRIEND);// нечего не даёт, тк работает OtherChar - а это губер, но он и так друг
            UpdateRelations();

            // 22.03.05  fix вернём диалог после разговора и спрячем
            //  внутри диалога не работало
            SetReturn_Gover_Dialog_Exit(NPChar);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
	    break;
	    
	    case "Prison":
			dialog.Text = "Benden başka ne istiyorsun, alçak?";
            Link.l3 = "Majesteleri yeni odasını nasıl buldu? Yeterince geniş mi? Peki, artık gitmeliyim!";
            Link.l3.go = "exit";
            NextDiag.TempNode = "Prison";
		break;
		
		case "arestFree_1":
			dialog.text = "Yerleşmek mi? Bunu nasıl hayal ediyorsun?";
            link.l1 = "Bence bir miktar "+iTotalTemp*6000+" pesos hâlâ beni kurtarabilir, değil mi?";
			link.l1.go = "arestFree_2";
			link.l2 = "Hayır. Ve artık gitme vaktim geldi. En iyi dileklerimle.";
			link.l2.go = "arest_1";
		break;

		case "arestFree_2":
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= hrand(7) && iTotalTemp < 21)
            {
    			dialog.text = "Sanırım olayımızı bu şekilde çözebiliriz. Durumu henüz telafisi imkânsız bir noktaya getirmedin.";
    		    link.l1 = "Mükemmel. Çok memnun oldum. Lütfen, bağışımı kabul edin.";
    		    link.l1.go = "Exit";
    		    AddMoneyToCharacter(pchar, -iTotalTemp*6000);
    		    ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -iTotalTemp);
    		    AddCharacterExpToSkill(pchar, "Fortune", 100);
            }
            else
            {
    			dialog.text = "Bana rüşvet mi teklif ediyorsun? Aman Tanrım! Kötülüklerinin bedeli ancak tek bir şekilde ödenebilir... Muhafızlar! Alın bunu "+GetSexPhrase("onu","onu")+" zincire vurulmuş!";
    		    link.l1 = "Dur bir dakika!";
    		    link.l1.go = "arest_2";
    		    AddCharacterExpToSkill(pchar, "Fortune", 10);
            }
		break;

		case "arest_1":
			dialog.text = "Elbette, zamanı geldi. Seni uğurlayacağız. Muhafızlar! Yakalayın "+GetSexPhrase("onu","onu")+"!";
		    link.l1 = "Olmaz!";
		    link.l1.go = "fight";
		break;

		case "arest_2":
			dialog.text = "Yeterince düşündün! Muhafızlar!";
			link.l1 = "Beni öyle kolay kolay yakalayamazsın!";
		    link.l1.go = "fight";
		break;    
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Уничтожение банды
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "DestroyGang":
			pchar.GenQuest.Governor.Group1.day = GetDataDay();
			dialog.text = "Elbette. Bu görevi yerine getirmen için sana veriyorum "+FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms))+", ve başarılı olursanız ödülünüz de "+FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money))+".";
			link.l1 = "Evet, bu görevi kabul ediyorum.";
		    link.l1.go = "DestroyGang_agree";
			link.l2 = "Hmm... Hayır, sanırım bu sefer pas geçeceğim.";
		    link.l2.go = "All_disagree";
		break;
		case "DestroyGang_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.questName = "DestroyGang"; //тип квеста
			pchar.GenQuest.DestroyGang.Location = GetGangLocation(npchar); //определяем локацию,где банда
			pchar.GenQuest.DestroyGang.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			if (pchar.GenQuest.DestroyGang.Location == "none") //на всякий случай
			{
				dialog.text = "Dur bir dakika, dünün raporu aklıma geldi. Mesele şu ki, bu çete zaten adamızdan ayrılmış. Yani görevi iptal etmek zorundayım.";
				link.l1 = "Anladım. Ne yazık.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
			else
			{
				dialog.text = "Pekâlâ, harika! Sizi ve raporlarınızı konutumda bekliyor olacağım.";
				link.l1 = "Seni fazla bekletmeyeceğim, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "exit";
				pchar.quest.DestroyGang.win_condition.l1 = "location";
				pchar.quest.DestroyGang.win_condition.l1.location = pchar.GenQuest.DestroyGang.Location;
				pchar.quest.DestroyGang.win_condition = "DestroyGang_fight";
				pchar.quest.DestroyGang.again = true; //тупо дожидаться своего часа бандиты не будут
				SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.DestroyGang.Terms), false);
				//==> энкаунтеров в квестовой локации не будет 
				locations[FindLocation(pchar.GenQuest.DestroyGang.Location)].DisableEncounters = true;
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "1");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				makearef(arName, pchar.GenQuest.DestroyGang);
				AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arName));
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)));
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Контркурьер
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePostcureer":
			//установка параметров
			pchar.GenQuest.questName = "TakePostcureer"; //тип квеста
			// belamour legendary edition враждебную нацию квестодателя, а не героя -->
			pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index)); //вражеская нация
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) {
				pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("Bugün size herhangi bir iş teklif edemem.","Bugün senin için başka iş kalmadı.","Bugünlük başka iş yok, üzgünüm. Yarın tekrar gel, bakarız...");
				link.l1 = RandPhraseSimple("Ne yazık...","Ah, ne yazık, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakePostcureer.City = FindQuestCity(npchar, "enemy",sti(pchar.GenQuest.TakePostcureer.Nation), false, false);
			// <-- legendary edition
			pchar.GenQuest.TakePostcureer.Island = GetArealByCityName(pchar.GenQuest.TakePostcureer.City);
			pchar.GenQuest.TakePostcureer.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePostcureer.Island)+5;
			pchar.GenQuest.TakePostcureer.LoginDay = sti(pchar.GenQuest.TakePostcureer.Terms)-1;
			pchar.GenQuest.TakePostcureer.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePostcureer.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePostcureer.Nation));
			pchar.GenQuest.TakePostcureer.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePostcureer.ShipType));
			pchar.GenQuest.TakePostcureer.Money = ((hrand(5)+hrand(6, "1")+42)*600)+(sti(pchar.rank)*1600);
			pchar.GenQuest.Governor.Group3.day = GetDataDay();
			dialog.text = "Elbette.  Bir kurye gemisini bulmanız gerekecek "+NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation))+" adında '"+pchar.GenQuest.TakePostcureer.ShipName+"', gemiye çık ve kaptanın kamarasında bulman gereken evrakları bana getir. Bu gemi şu civardan geçecek "+XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen")+" yaklaşık olarak "+FindRussianDaysString(pchar.GenQuest.TakePostcureer.Terms)+".";
			link.l1 = "Pekâlâ, bu görevi kabul ediyorum. Peki, ne tür belgeler aramam gerekiyor?";
		    link.l1.go = "TakePostcureer_agree";
			link.l2 = "Hmm... Hayır, sanırım bu sefer pas geçeceğim.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePostcureer_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePostcureer.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Posta. Benim için çok önemli bazı evraklar var. Ama belgeleri tek tek aramana gerek yok, paketin tamamını bana getir yeter. Sana ödeme yapacağım "+FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money))+"\nO halde, sizi ve yaptığınız işin sonuçlarını konutumda bekliyor olacağım.";
			link.l1 = "Sizi fazla bekletmeyeceğim, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			pchar.quest.TakePostcureer.win_condition.l1 = "location";
			pchar.quest.TakePostcureer.win_condition.l1.location = pchar.GenQuest.TakePostcureer.Island;
			pchar.quest.TakePostcureer.win_condition.l2 = "Timer";
			pchar.quest.TakePostcureer.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakePostcureer.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.function = "TakePostcureer_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePostcureer.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "3");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePostcureer.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePostcureer.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Контрфрахт - уничтожить корабль с арсеналом
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakeArsenalship":
			//установка параметров
			pchar.GenQuest.questName = "TakeArsenalship"; //тип квеста
			// belamour legendary edition враждебную нацию квестодателя, а не героя -->
			pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) {
				pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("Bugün size herhangi bir iş teklif edemem.","Bugün senin için başka iş kalmadı.","Bugünlük başka iş yok, üzgünüm. Yarın tekrar gel, bakarız...");
				link.l1 = RandPhraseSimple("Ne yazık...","Ah, ne yazık, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakeArsenalship.City = FindQuestCity(npchar, "enemy",sti(pchar.GenQuest.TakeArsenalship.Nation), false, false);
			// <-- legendary edition
			pchar.GenQuest.TakeArsenalship.Island = GetArealByCityName(pchar.GenQuest.TakeArsenalship.City);
			pchar.GenQuest.TakeArsenalship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakeArsenalship.Island)+5;
			pchar.GenQuest.TakeArsenalship.LoginDay = sti(pchar.GenQuest.TakeArsenalship.Terms)-1;
			pchar.GenQuest.TakeArsenalship.ShipType = SelectArsenalShipType(FLAG_SHIP_TYPE_RAIDER);
			pchar.GenQuest.TakeArsenalship.ShipTypeA = SelectArsenalShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
			pchar.GenQuest.TakeArsenalship.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakeArsenalship.Nation));
			pchar.GenQuest.TakeArsenalship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipType));
			pchar.GenQuest.TakeArsenalship.CannonA = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipTypeA)); // Addon 2016-1 Jason пиратская линейка
			pchar.GenQuest.TakeArsenalship.Money = ((hrand(5)+hrand(6, "1")+36)*700)+(sti(pchar.rank)*1600);
			pchar.GenQuest.Governor.Group3.day = GetDataDay();
			dialog.text = "Elbette. Bir askeri nakliye gemisini bulmanız gerekecek "+NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation))+", with gunpowder and ammunition on board; the name of the vessel is '"+pchar.GenQuest.TakeArsenalship.ShipName+"', find and destroy it. We'll weaken our enemy by doing that\nThe transport will sail with an escort to the colony "+XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City)+", and will be approximately in "+FindRussianDaysString(pchar.GenQuest.TakeArsenalship.Terms)+", so you should hurry.";
			link.l1 = "Pekâlâ, kabul ediyorum. Cephane gemisini batırmam mı gerekiyor, yoksa ele geçirmeye mi çalışmalıyım?";
		    link.l1.go = "TakeArsenalship_agree";
			link.l2 = "Hmm... Hayır, sanırım bu sefer pas geçeceğim.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakeArsenalship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakeArsenalship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Umurumda değil, sana kalmış. Önemli olan bu yükün hedefine ulaşmaması. Başarırsan, sana ödeme yapacağım "+FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money))+"... Artık sizi daha fazla oyalamıyorum, kaptan.";
			link.l1 = "Sizi fazla bekletmeyeceğim, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			pchar.quest.TakeArsenalship.win_condition.l1 = "location";
			pchar.quest.TakeArsenalship.win_condition.l1.location = pchar.GenQuest.TakeArsenalship.Island;
			pchar.quest.TakeArsenalship.win_condition.l2 = "Timer";
			pchar.quest.TakeArsenalship.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakeArsenalship.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.function = "TakeArsenalship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakeArsenalship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "8");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakeArsenalship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakeArsenalship.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	ОЗГ - уничтожить корабль пиратов
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePirateship":
			//установка параметров
			pchar.GenQuest.questName = "TakePirateship"; //тип квеста
			pchar.GenQuest.TakePirateship.City = FindQuestCity(npchar, "all", -1, true, true); // belamour legendary edition 
			pchar.GenQuest.TakePirateship.Island = GetArealByCityName(pchar.GenQuest.TakePirateship.City);
			pchar.GenQuest.TakePirateship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePirateship.Island)+5;
			pchar.GenQuest.TakePirateship.ShipType = SelectPirateShipType();
			pchar.GenQuest.TakePirateship.ShipName = GenerateRandomNameToShip(PIRATE);
			pchar.GenQuest.TakePirateship.Name = GenerateRandomName(PIRATE, "man");
			pchar.GenQuest.TakePirateship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePirateship.ShipType));
			pchar.GenQuest.TakePirateship.Money = ((hrand(5) + hrand(6, "1")+4)*800)+13000+(sti(pchar.rank)*1250);
			pchar.GenQuest.Governor.Group2.day = GetDataDay();
			dialog.text = "Elbette. Beni gerçekten öfkelendiren bir korsan kaptan var, adı ise "+pchar.GenQuest.TakePirateship.Name+" O alçak tüccar gemilerimize saldırmaya başladı, bu da koloniler arasındaki ticarete büyük zarar veriyor. Şu an ondan kurtulmak için en uygun zaman, çünkü nerede saklandığını tesadüfen öğrendim. Bu piçi Tanrı'nın huzuruna göndermeye hazır mısın?";
			link.l1 = "Bu benim için bir onur olur! Bu korsanı nerede bulabilirim?";
		    link.l1.go = "TakePirateship_agree";
			link.l2 = "Hmm... Hayır, sanırım bu sefer pas geçeceğim.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePirateship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePirateship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "En yakındaki "+FindRussianDaysString(pchar.GenQuest.TakePirateship.Terms)+"  ' adlı gemisiyle "+pchar.GenQuest.TakePirateship.ShipName+"' kıyılarında dolaşacak "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+". Onu bul ve öldür. Gemisiyle birlikte balıklara yem et, ister gemiye çık - umurumda değil. Tek istediğim, o lanet korsanın varlığıyla denizimizi kirletmeyi bırakması\nBu iş için sana ödeme yapmaya hazırım "+FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money))+". Zaman kaybetmeyin, kaptan: bu alçak sizi beklemeyecek "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+". Git, ve Tanrı yardımcın olsun!";
			link.l1 = "Demir almaya şimdiden başladınız, "+GetAddress_FormToNPC(NPChar)+"! Çok beklemek zorunda kalmayacaksınız.";
			link.l1.go = "exit";
			pchar.quest.TakePirateship.win_condition.l1 = "location";
			pchar.quest.TakePirateship.win_condition.l1.location = pchar.GenQuest.TakePirateship.Island;
			pchar.quest.TakePirateship.function = "TakePirateship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePirateship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "9");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePirateship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePirateship.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePirateship.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	ОЗГ - захватить пассажира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePassenger":
			//установка параметров
			pchar.GenQuest.questName = "TakePassenger"; //тип квеста
			pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index));//вражеская нация
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) {
				pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("Bugün size herhangi bir iş teklif edemem.","Bugün senin için başka iş kalmadı.","Bugünlük başka iş yok, üzgünüm. Yarın tekrar gel, bakarız...");
				link.l1 = RandPhraseSimple("Yazık...","Ah, ne yazık, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakePassenger.City = FindQuestCity(npchar, "enemy", sti(pchar.GenQuest.TakePassenger.Nation), false, false); // belamour legendary edition
			pchar.GenQuest.TakePassenger.CityA = SelectAnyColony(pchar.GenQuest.TakePassenger.City);
			pchar.GenQuest.TakePassenger.Terms1 = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, GetArealByCityName(pchar.GenQuest.TakePassenger.City));
			pchar.GenQuest.TakePassenger.Terms2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.TakePassenger.City), GetArealByCityName(pchar.GenQuest.TakePassenger.CityA))+1;
			pchar.GenQuest.TakePassenger.Terms = sti(pchar.GenQuest.TakePassenger.Terms1)+sti(pchar.GenQuest.TakePassenger.Terms2);
			pchar.GenQuest.TakePassenger.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePassenger.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePassenger.Nation));
			pchar.GenQuest.TakePassenger.Name = GenerateRandomName(sti(pchar.GenQuest.TakePassenger.Nation), "man");
			pchar.GenQuest.TakePassenger.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePassenger.ShipType));
			pchar.GenQuest.TakePassenger.Money = ((hrand(5) + hrand(6, "1")+4)*500)+12500+(sti(pchar.rank)*1000);
			pchar.GenQuest.Governor.Group2.day = GetDataDay();
			string sText = SelectPassText();
			dialog.text = "Elbette. Bahsettiğim kişi adı kötüye çıkmış bir alçak, adı da "+pchar.GenQuest.TakePassenger.Name+". "+sText+" Onu uzun zamandır arıyordum ve sonunda nerede bulunabileceğine dair güvenilir bilgilere ulaştım. O adamı ne pahasına olursa olsun bana canlı olarak getirmeni istiyorum. Onu kasaba meydanımızda halka açık şekilde asmak istiyorum. Bu görevi üstlenmeye hazır mısın?";
			link.l1 = "Hazırım, "+GetAddress_FormToNPC(NPChar)+" . O alçağı nerede bulabilirim?";
		    link.l1.go = "TakePassenger_agree";
			link.l2 = "Hmm... Hayır, sanırım bu sefer pas geçeceğim.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePassenger_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePassenger.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Tam zamanında "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms1)+", o, ' adlı bir gemide yolcu olarak "+pchar.GenQuest.TakePassenger.ShipName+"',   limandan   ayrılacak "+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen")+" ve git "+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc")+". Sende var "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms)+" belirtilen rotada bu gemiyi bul, gemiye çık ve o alçağı ele geçir. Bu talimatlara uyarsan, sana ödeme yapacağım "+FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money))+". Sana bol şanslar, kaptan!";
			link.l1 = "Daha fazla zaman kaybetmeyeceğim, "+GetAddress_FormToNPC(NPChar)+"! Hemen yelken açacağım.";
			link.l1.go = "exit";
			SetFunctionTimerCondition("TakePassenger_CreateShip", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms1), false);
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "10");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sCityA", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc"));
			AddQuestUserData("MayorsQuestsList", "sDay1", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms1)));
			AddQuestUserData("MayorsQuestsList", "sDay2", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePassenger.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePassenger.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Таможенный патруль
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "CustomPatrol":
			//установка параметров
			pchar.GenQuest.questName = "CustomPatrol"; //тип квеста
			pchar.GenQuest.CustomPatrol.Nation = sti(npchar.nation);//нация
			pchar.GenQuest.CustomPatrol.Island = Islands[GetCharacterCurrentIsland(PChar)].id;
			pchar.GenQuest.CustomPatrol.LoginDay = rand(2)+1;
			pchar.GenQuest.CustomPatrol.Loginlocator = rand(3)+3;
			pchar.GenQuest.CustomPatrol.ShipType = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
			pchar.GenQuest.CustomPatrol.ShipTypeA = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_RAIDER);
			pchar.GenQuest.CustomPatrol.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.CustomPatrol.ShipType));
			pchar.GenQuest.CustomPatrol.Money = ((hrand(5)+hrand(6, "1")+4)*450)+8200 + (sti(pchar.rank) * 750);
			pchar.GenQuest.Governor.Group1.day = GetDataDay();
			dialog.text = "Elimde güvenilir bilgiler var; belirli bir kaptan, bazı köleleri satmak için kaçakçılarla bir anlaşma yapmış. Bildiğiniz gibi, kolonilerimizde özel şahısların bu tür ticaretleri kaçakçılık olarak kabul edilir. Sorun şu ki, kaçakçıların buluşacağı tam zamanı, tarihi ya da yeri bilmiyorum. Bildiğimiz tek şey, bu suç teşkil eden alışverişin önümüzdeki üç gün içinde adamızda gerçekleşeceği. Dahası, tüm devriye gemilerim ya tamirde ya da başka görevlerde, bu alçakların peşine düşemiyorlar. Bu görevi üstlenmenizi öneriyorum – kaçakçıların izini sürün ve onlara en kesin şekilde gerekeni yapın, ibret olsunlar. Bu görev için hazır mısınız?";
			link.l1 = "Hazırım, "+GetAddress_FormToNPC(NPChar)+" . Söyleyin, elinizde başka bir bilgi var mı? Mesela kaptanın adı, gemisinin adı ya da türü gibi?";
		    link.l1.go = "CustomPatrol_agree";
			link.l2 = "Hmm... Hayır, sanırım bu sefer pas geçeceğim.";
		    link.l2.go = "All_disagree";
		break;
		
		case "CustomPatrol_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.CustomPatrol.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Kaynağım bana bir anlaşmanın hazırlandığını ve yakında tamamlanacağını söyledi. Hepsi bu. Yani, sularımızdaki şüpheli gemilere daha yakından bak. Başarırsan, sana şu kadar ödeme yapacağım "+FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money))+"\nAyrıca, mevcut koşulları göz önünde bulundurarak, bulabildiğiniz tüm kaçak mallara el koymanıza izin veriyorum. Elbette bu gayriresmî bir yetki; yeter ki malları şehrimizde satmayın.";
			link.l1 = "Oldukça cömert. Peki, koloninizin sularında devriye gezmeye başlayacağım, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 4, false);
			pchar.quest.CustomPatrol.win_condition.l1 = "location";
			pchar.quest.CustomPatrol.win_condition.l1.location = pchar.GenQuest.CustomPatrol.Island;
			pchar.quest.CustomPatrol.win_condition.l2 = "Timer";
			pchar.quest.CustomPatrol.win_condition.l2.date.hour  = sti(GetTime()+rand(8));
			pchar.quest.CustomPatrol.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.function = "CustomPatrol_CreateShip";
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "11");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money)));
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Найти дезертира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "FindFugitive":
			//установка параметров
			pchar.GenQuest.questName = "FindFugitive"; //тип квеста
			pchar.GenQuest.FindFugitive.Startcity = npchar.city;
			pchar.GenQuest.FindFugitive.City = SelectFugitiveCity();
			pchar.GenQuest.FindFugitive.Chance = rand(2);
			pchar.GenQuest.FindFugitive.Name = GenerateRandomName(sti(npchar.Nation), "man");
			pchar.GenQuest.FindFugitive.Money = ((hrand(5)+hrand(6, "1")+4)*600)+9600+(sti(pchar.rank)*900);
			sText = SelectFugitiveText();
			log_testinfo(pchar.GenQuest.FindFugitive.City);
			log_testinfo(FindRussianDaysString(sti(pchar.GenQuest.FindFugitive.Chance)));
			pchar.GenQuest.Governor.Group2.day = GetDataDay();
			dialog.text = "Sana her şeyi ayrıntısıyla anlatacağım. Çok çirkin bir olay yaşandı - "+sText+". Arkadaşları ve meslektaşlarıyla yaptığımız görüşmeler sonucunda, firarinin korsanlardan birinin yerleşiminde saklandığına dair güçlü bir kanaatimiz oluştu.\nSana korsan yuvasına gidip kaçak askeri bulmanı, onu tutuklayıp buraya getirmeni öneriyorum. Firar ciddi bir suçtur ve cezasız kalamaz. Bu görevi üstlenmeye hazır mısın?";
			link.l1 = "Hazırım, "+GetAddress_FormToNPC(NPChar)+". Kaçağın adını bana söyleyebilir misiniz?";
		    link.l1.go = "FindFugitive_agree";
			link.l2 = "Hmm... Hayır, sanırım bu sefer pas geçeceğim.";
		    link.l2.go = "All_disagree";
		break;
		
		case "FindFugitive_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.FindFugitive.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Evet, tabii ki. Adı "+pchar.GenQuest.FindFugitive.Name+". Üniformasını giyeceğinden pek şüpheliyim, bu yüzden her türlü pisliği dikkatlice incele. Arama için sana bir ay veriyorum, çünkü bundan sonra onu aramanın bir anlamı kalmayacak diye korkuyorum. Başarırsan, sana şu miktarı ödeyeceğim "+FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money))+".";
			link.l1 = "Daha fazla zaman kaybetmeyeceğim, "+GetAddress_FormToNPC(NPChar)+"! Hemen yelken açacağım.";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 30, false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "12");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.FindFugitive.Name);
			//создаем дезертира
			sld = GetCharacter(NPC_GenerateCharacter("Fugitive", "citiz_"+(21+rand(9)), "man", "man", sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, sti(npchar.nation), 30, true, "soldier"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
			sld.name = pchar.GenQuest.FindFugitive.Name;
			sld.lastname = "";
			sld.dialog.FileName = "MayorQuests_dialog.c";
			sld.greeting = "marginal";
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Проникновение во враждебный город
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "Intelligence":
			pchar.GenQuest.Governor.Group3.day = GetDataDay();
			dialog.text = "Anladım. Belki de bir ödül olarak "+FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money))+" sizin için iyi bir teşvik olacak.";
			link.l1 = "Evet, fena para değil... Bu görevi alıyorum.";
		    link.l1.go = "Intelligence_agree";
			link.l2 = "Hmm... Hayır, sanırım reddedeceğim. Bu çok tehlikeli.";
		    link.l2.go = "All_disagree";
		break;
		case "Intelligence_agree":
			if (pchar.GenQuest.Intelligence.City == "none" || isBadReputation(pchar, 30)) //на всякий случай
			{
				dialog.text = "Sana tamamen güvendiğimi söyleyemem... Bu görevi sana vermeyeceğim sanırım.";
				link.l1 = "Eh, ne yapalım... Yazık oldu, ama elimden bir şey gelmez.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
			}
			else
			{
				npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
				pchar.GenQuest.questName = "Intelligence"; //тип квеста
				sTemp = pchar.GenQuest.Intelligence.City;
				switch (rand(4))
				{
					case 0:	sTemp += "_Priest";		break;
					case 1:	sTemp += "_trader";		break;
					case 2:	sTemp += "_shipyarder"; break;
					case 3:	sTemp += "_usurer";	    break;
					case 4:	sTemp += "_PortMan";	break;
				}
				pchar.GenQuest.Intelligence.SpyId = sTemp; //Id нашего шпиона в городе
				dialog.text = "Harika! Şimdi, asıl meseleye gelelim. "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat")+" bir yerlisini bulman gerek "+GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)],"Gen")+", adı "+GetFullName(&characters[GetCharacterIndex(sTemp)])+".   Ona   adımı   söyleyeceksin   ve   sana   bir   belge   paketi   verecek.   Bu   paketi   bana   teslim   ettiğinde,   sana   "+FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms))+". Ve unutmayın, her şey gizlilik içinde yapılmalı. Kimliğiniz açığa çıkarsa, ajan temas kurmaya cesaret edemez. Anlaşıldı mı?";
				link.l1 = "Evet, anladım. "+GetAddress_FormToNPC(NPChar)+". Hemen başlayacağım.";
				link.l1.go = "exit";
				pchar.GenQuest.Intelligence.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
				SaveCurrentQuestDateParam("GenQuest.Intelligence"); //запись даты получения квеста
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "6");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc"));
				AddQuestUserData("MayorsQuestsList", "sIsland", XI_ConvertString(GetIslandByColony(&colonies[FindColony(pchar.GenQuest.Intelligence.City)])+"Dat"));
				AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen"));
				AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(sTemp)]));			
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)));
				AddQuestUserData("MayorsQuestsList", "sCity2", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat"));
			}
		break;
		case "Intelligence_ExecuteLate":
			QuestName = pchar.GenQuest.questName;
			pchar.GenQuest.(QuestName).Money = sti(pchar.GenQuest.(QuestName).Money) / 2);
			dialog.text = RandPhraseSimple("Fena değil. Ama teslim tarihini kaçırdın, bu yüzden ödülünü biraz azaltmam gerekecek. Şimdi alacağın ücret "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". Buyurun.","Güzel. Ama teslim tarihine uymadın ve bu mektupları bekliyordum. Planlarımı bozmuş oldun, bu yüzden ödülünü biraz azaltmak zorundayım. Yine de hak ettiğin ödülü vermekten memnunum - "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". Buyurun.");
			link.l1 = "Benim için hoş olduğunu söyleyemem, ama sonuçta teslim tarihleri gerçekten kaçırıldı. Yani şikayetim yok, "+GetAddress_FormToNPC(NPChar)+".";
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(RandPhraseSimple("You know, governor " + GetFullName(npchar) + " are not very pleased with the quickness of a captain " + GetMainCharacterNameGen() + ".", 
				"Governor " + GetFullName(npchar) + " is not very pleased with captain " + GetMainCharacterNameDat() + ", "+ GetSexPhrase("who","who") +" complied with his orders, but did not in due time..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		
		// -------------- общий набор для всех квестов мэра ------------------
		case "All_disagree":
			dialog.text = RandPhraseSimple("Hmm. Demek ki kararlılığınızı fazla abartmışım, Kaptan.","Beni hayal kırıklığına uğrattınız, Kaptan. Görünen o ki, böyle meseleler için gerçekten gerekli niteliklerden yoksunsunuz.","Bir dahaki sefere, Kaptan, boş laflarla vaktimi harcamadan önce iki kere düşünün.");
			link.l1 = "Üzgünüm, "+GetAddress_FormToNPC(NPChar)+", ama bu işi kabul edemem.";
		    link.l1.go = "exit";
			//ChangeCharacterComplexReputation(pchar,"nobility", -2);
			
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{
				QuestName = pchar.GenQuest.questName;
				DeleteAttribute(pchar, "GenQuest." + QuestName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
		break;
		case "All_Late":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Çok kötü, başka ne diyebilirim ki. Sana güvenmiştim, ama görüyorum ki sadece zamanımı boşa harcamışım. Hayal kırıklığına uğradım.","Doğrusu, senden tam anlamıyla hayal kırıklığına uğradım... Konutumda her zaman bu tür işleri benim için yapmaya hazır pek çok insan var - ve ben ise vaktimi sana harcadım. Neyse...");
			link.l1 = "Üzgünüm, "+GetAddress_FormToNPC(NPChar)+", elimden gelen her şeyi yaptım.";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + " is very displeased with captain " + GetMainCharacterNameDat() + ". Just imagine - he failed to fulfill his assignment in time!", 
				"Governor " + GetFullName(npchar) + " is slightly annoyed that a captain " + GetFullName(pchar) + " put his shoulder to the wheel, but fail to fulfill his assignment in time. That's too bad...", 
				"I heard that governor " + GetFullName(npchar) + " is very displeased with you, captain " + GetFullName(pchar) + ", since you failed to meet the deadline while trying to fulfill his assignment."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу ещё один не даем
			CloseQuestHeader("MayorsQuestsList");
		break;
		case "All_Found":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Gerçekten şok oldum! Hedefinizi bulmayı başardınız ama üstünlüğünüzü sağlama almak için hiçbir şey yapmadınız - bu tam anlamıyla pervasızlık. Hayal kırıklığına uğradım!","Doğrusu, senden hayal kırıklığına uğradım... Hedefini bulmak yeterli değil - onu yok edecek güce de sahip olmalısın. Konutumda bu tür işleri benim için yapmaya her zaman hazır birçok haydut var. Sana güvenmekle ne düşündüğümü merak ediyorum.");
			link.l1 = "Üzgünüm, "+GetAddress_FormToNPC(NPChar)+", ama kendi hayatımı düşüncesizce riske atmaya hiç niyetim yok.";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + " is very displeased with captain " + GetMainCharacterNameDat() + ". Imagine, "+ GetSexPhrase("he turned out to be a downright coward","she turned out to be a downright coward") +"!", 
				"Governor " + GetFullName(npchar) + " is slightly annoyed that a captain " + GetFullName(pchar) + " took the job, but failed to carry it out because of their own indecision. Hee-hee, what wilt captains!", 
				"I heard that Governor " + GetFullName(npchar) + " very displeased with you, Captain " + GetFullName(pchar) + ". They say you're nothing but a coward"+ GetSexPhrase("","") +"..."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу ещё один не даем
			CloseQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "21");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		break;
		case "All_Execute":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Harika haber! Şimdi, her şeyi toparlama vakti. Ücretiniz ise "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". Buyurun.","Harika! Bu herkes için en iyisi... Pekâlâ, hak ettiğiniz ödülü size vermekten memnuniyet duyarım - "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". Buyurun.");
			link.l1 = "Teşekkür ederim, "+GetAddress_FormToNPC(NPChar)+", "+RandPhraseSimple("Sizinle iş yapmak bir zevkti!","Yerleşimlerin netliği beni hoş bir şekilde şaşırttı.");
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + "  was praising for diligence"+ GetSexPhrase("a captain","a young lady") +" " + GetMainCharacterNameGen() + ".", 
				"Governor " + GetFullName(npchar) + " is praising captain " + GetMainCharacterNameGen() + ", "+ GetSexPhrase("he","she") +" is always a flawless performer when it comes to governor's assignments. An irreplaceable person for the governor, I say...", 
				"I heard that governor " + GetFullName(npchar) + " is very much pleased with you, captain " + GetFullName(pchar) + ". He defines you as a very careful and thorough officer. That's very nice to hear, captain..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		case "All_Execute_1":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Çok iyi. Yine beni görmeye gelebilirsin – belki sana başka bir iş bulurum.","Pekâlâ, harika! Sanırım sana yine böyle işler teklif edeceğim.");
			link.l1 = RandPhraseSimple("Harika.","Pekala.");
		    link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.(QuestName).Money));
			CloseQuestHeader("MayorsQuestsList");
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(PChar, "Leadership", 180);
			OfficersReaction("good"); // dlc
			
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу ещё один не даем
			// инкремент в базу заданий мэров
			sTemp = npchar.City;
			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;
		break;
//<-- осады homo
		case "siege_task":
            makearef(aData, NullCharacter.Siege);
            aData.HelpColony = true;
			dialog.text = "Bu zor zamanlarda, her türlü yardıma çok ihtiyacımız var. Yardımınızı kabul ediyoruz – kolonimizi savunmamıza yardımcı olun, karşılığında ödüllendirileceksiniz.";
			link.l1 = "O halde vakit kaybetmeyelim.";
		    link.l1.go = "exit";
		break;
		
		//Jason --> Бремя гасконца
		case "Sharlie":
			dialog.text = "Michel de Monper'i mi arıyorsunuz? İlginç... Peki, ona neden ihtiyacınız var?";
			link.l1 = "Ben onun kardeşiyim. Babam Michel’in başı dertte, yardıma ihtiyacı var dedi, bu yüzden ben...";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
			DelLandQuestMark(sld);
			dialog.text = "Öyle mi? Monsieur de Monper'in hiç kardeşi olduğunu hatırlamıyorum... Biliyor musunuz, monsieur, bana çok şüpheli görünüyorsunuz... bu yüzden sizi daha fazla soruşturmak için tutukluyorum. Teğmen! Bu adamı gözaltına alın!";
			link.l1 = "Ama Ekselansları!";
			link.l1.go = "exit";
			if (GetCharacterIndex("SharlieKnown") != -1)
			{
				sld = characterFromId("SharlieKnown");
				sld.lifeday = 0;
			}	
			AddDialogExitQuestFunction("Sharlie_enterSoldiers");
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Sharlie_2":
			QuestPointerDelLoc("Fortfrance_town", "reload", "reload3_back");
			dialog.text = "Ve yine de, kendimi affettirmek istiyorum. Buyurun - lütfen bu kılıcı, bu tabancayı ve bu hafif zırhı alın - bunlar size hediyemdir. Bunların size oldukça faydalı olacağına inanıyorum.";
			link.l1 = "Teşekkür ederim, monsieur. Muhafızlarınız sahip olduğum her şeyi aldığından, bu bana çok iyi gelecek.";
			// belamour legendary edition -->
			link.l1.go = "Sharlie_5";		
			link.l2 = "Teşekkür ederim, monsieur. Bana başka bir şekilde yardımcı olmanız mümkün mü? İki centilmen arasında? İçinde bulunduğum bu korkunç durumu kendiniz de görebilirsiniz!";
			link.l2.go = "Sharlie_3";	
		break;
		
		case "Sharlie_3":
			dialog.text = "Pekâlâ, Charles... (masada bir şeyler arar) Al, bu kutsal tılsımı yanında taşı, sana şans getirsin. Artık daha fazla yardımcı olamam, üzgünüm. Burada, kolonilerde, yalnızca kendine güvenmek zorundasın.";
			link.l1 = "Pekâlâ, en azından bu da bir şey. Hediye için teşekkür ederim, efendim.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Commerce", 10);
			Log_Info("You'have received equipment");
			Log_Info("You have received the 'Holy Water' amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7");
			TakeNItems(pchar, "blade_08", 1);
			if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "")
			{
				EquipCharacterbyItem(pchar, "blade_08");
			}
			TakeNItems(pchar, "pistol1", 1);
			TakeNItems(pchar, "cirass5", 1);
			pchar.quest.Sharlie_PardonOver.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				DelLandQuestMark(npchar);
			}
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Sharlie_5":
			// <-- legendary edition
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 10);
			Log_Info("You'have received equipment");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "blade_08", 1);
			if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "")
			{
				EquipCharacterbyItem(pchar, "blade_08");
			}
			TakeNItems(pchar, "pistol1", 1);
			TakeNItems(pchar, "cirass5", 1);
			pchar.quest.Sharlie_PardonOver.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		//<-- Бремя гасконца
		
		//Sinistra --> Травля крысы		
		case "TK_TravlyaKrys":
			dialog.text = "Kaderin cilvesi, Charles... Bizim dünyamızda birinin bu kadar hızlı yükseldiğini pek sık görmeyiz. Sanırım seninle gayet iyi anlaşacağız.";
			link.l1 = "Memnuniyetle. Belki bana verecek bir göreviniz vardır?";
			link.l1.go = "TK_TravlyaKrys_2";
			DeleteAttribute(pchar, "questTemp.TK_TravlyaKrys");
			PChar.quest.TK_Timer.over = "yes";
		break;
		
		case "TK_TravlyaKrys_2":
			dialog.text = "Kesinlikle! Özellikle de Le François yakınlarında Barbazon'un korsanlarından biriyle başarılı bir şekilde karşılaştıktan sonra...";
			link.l1 = "O karşılaşmayı hoş bir anı olarak hatırladığım söylenemez. Barbazon tam olarak kim?";
			link.l1.go = "TK_TravlyaKrys_3";
		break;
		
		case "TK_TravlyaKrys_3":
			dialog.text = "Jacques Barbazon, nam-ı diğer İyi Adam Jacques, Le François’daki haydut yuvasının başında. Sözde korsan baronlarından biri; Küçük Antiller’de korsanlık ve kaçakçılıkla başımıza bela oluyor. Kötü şöhretli bir suçlu; unutma sözümü, bir gün St. Pierre’de darağacında can verecek!";
			link.l1 = "Affedersiniz, ama Martinique'te asıl otorite siz değil misiniz? O yuvayı ortadan kaldıramaz mısınız? Orada bulundum, inanın bana, görülecek pek bir şey yok.";
			link.l1.go = "TK_TravlyaKrys_4";
		break;
		
		case "TK_TravlyaKrys_4":
			dialog.text = "Sana tavsiyem, adamım Charles, adamdaki karanlık köşeleri bildiğinle övünmekten kaçın. Bir asilzade için hiç hoş bir davranış değil. Soruna gelince\nDünyamızdaki her şey kaba kuvvetle çözülemez. Söz konusu olan siyaset ve ticari çıkarlar var. Ama gereksiz ayrıntılara girmeyelim: Benim için kaba kuvvet gerektiren özel bir iş var.";
			link.l1 = "Lütfen devam edin.";
			link.l1.go = "TK_TravlyaKrys_5";
		break;
		
		case "TK_TravlyaKrys_5":
			dialog.text = "Barbazon, kolay para peşinde koşan küçük çaplı tayfaları kendine çeker. Bazen onlara bir kemik atar, sırf birbirleriyle kapışmalarını izlemek için. Ara sıra hayatta kalanı işe koşar, ama çoğu zaman onları kapı dışarı eder. Bana güven, ortalıkta çaresizce dolaşan bir korsandan daha tehlikelisi yoktur.";
			link.l1 = "Sanırım anladım, ama buna hazır olup olmadığımı bilmiyorum. Gemimin komutasını daha yeni devraldım ve hâlâ işin inceliklerini öğreniyorum, tabiri caizse...";
			link.l1.go = "TK_TravlyaKrys_6";
		break;
		
		case "TK_TravlyaKrys_6":
			dialog.text = "Saçmalık! Zaferin tadına zaten vardın – benim subaylarımın çoğu tembelken sen onlardan fazlasını başardın! Şehri bir Barbazon sıçanını daha batırdığın için sana beş bin peso ödeyecek, vergisiz. Korsanı canlı getirirsen sekiz bin – tabii ki düzgün bir infaz için.";
			link.l1 = "Paraya kesinlikle ihtiyacım var. Bu korsanı nerede bulabilirim?";
			link.l1.go = "TK_TravlyaKrys_7";
			link.l2 = "Üzgünüm, ama sanırım henüz böyle bir göreve hazır değilim.";
			link.l2.go = "TK_TravlyaKrys_Otkaz";
		break;
		
		case "TK_TravlyaKrys_Otkaz":
			dialog.text = "Bu üzücü, Charles. O halde, seni daha fazla tutmayacağım.";
			link.l1 = "Hoşça kalın, Ekselansları.";
			link.l1.go = "exit";
		break;
		
		case "TK_TravlyaKrys_7":
			dialog.text = "Aramıza katılmana sevindim, Charles. İstihbaratımıza göre Hater adında bir lugger şu anda Le François'dan ayrılmaya hazırlanıyor. Gecikmeye tahammülümüz yok, hemen yola çıkıp müdahale et. Merak etme dostum, başaracaksın.";
			link.l1 = "Tanrı'nın lütfuyla, Ekselansları.";
			link.l1.go = "TK_TravlyaKrys_8";			
		break;
		
		case "TK_TravlyaKrys_8":
			DialogExit();
			SetQuestHeader("TravlyaKrys");
			AddQuestRecord("TravlyaKrys", "1");
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, true, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
			FantomMakeSmallSailor(sld, SHIP_LUGGER, "Hater", CANNON_TYPE_CANNON_LBS3, 20, 40, 20, 25, 35);
			SetCharacterGoods(sld, GOOD_GOLD, 1);
			sld.AlwaysEnemy = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			
			Group_FindOrCreateGroup("HeiterAttack");
			Group_SetType("HeiterAttack", "pirate");
			Group_AddCharacter("HeiterAttack", "TK_Heiter");

			Group_SetGroupCommander("HeiterAttack", "TK_Heiter");
			Group_SetTaskAttack("HeiterAttack", PLAYER_GROUP);
			Group_SetAddress("HeiterAttack", "Martinique", "Quest_Ships", "Quest_Ship_6");
			Group_LockTask("HeiterAttack");
			
			PChar.quest.TK_Potopil.win_condition.l1 = "Character_sink";
			PChar.quest.TK_Potopil.win_condition.l1.character = "TK_Heiter";
			PChar.quest.TK_Potopil.win_condition = "TK_Potopil";
		break;
		//<-- Травля крысы
		
		//Jason --> Португалец
		case "Portugal":
			dialog.text = "Elbette yapabilirsiniz, kaptan! Zaten bu yüzden sizi rahatsız ettim.";
			link.l1 = "O halde kulak kesildim.";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Dün gece adanın yakınlarında yerel balıkçılar tuhaf bir gemi gördüler. Büyük bir savaş gemisiymiş, sanki bir hat gemisi gibi, ne bayrağı varmış ne de işaret fenerleri. Böyle bir geminin gerçekten bir fırkateynden büyük olacağına inanmıyorum ama öyle bile olsa bu zaten fazlasıyla endişe verici!";
			link.l1 = "Korku, küçük sorunları dağ gibi gösterir, orası kesin... ama ne anlamı var?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Sana güveniyorum, kaptan. Ticaret ortaklarım bu söylentilerden korkmuş durumda – bunun korsanlar ya da İspanyol özel donanması olduğuna inanıyorlar ve bu ticaret için kötü. En kötüsü de – şu anda kolonide savaş gemisi yok, sadece koruma için birkaç küçük tekne ve kaçakçı avlamaktan başka işe yaramayan eski bir şalopa var.\nBunu göz ardı edemem... Her neyse, artık bu gizemli gemi hakkındaki söylenti şehrin yarısına yayıldı! Lütfen, geminle bize katıl ve onu bulmamıza yardım et – seni dürüst bir kaptan olarak tanıyorum ve eğer gerçekten sadece bir fırkateynse bile, topların onu başka av aramaya ikna edebilir!";
			link.l1 = "Monsieur... Aslında başka planlarım vardı...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Lütfen, kaptan! Sadece birkaç günlüğüne, şu huzursuz edici söylentiler yatışana kadar! Elbette zamanınız için ödeme alacaksınız. 10.000 sekizlik sizin için uygun olur mu?";
			link.l1 = "Hmm... ama Ekselansları, ben...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "Ve eğer gerçekten bu gemiyle çatışırsanız, ödülü iki katına çıkaracağız, batırırsanız üç katına! Şimdi, ne dersiniz?";
			link.l1 = "Pekâlâ, zaten burada birkaç gün kalmayı planlıyordum.";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "Harika, aslında sana hiç şüpheyle bakmadım, monsieur kaptan! Unutma - sularımızda sadece iki gün kalacaksın ve para senin olacak. Eğer savaşa girmek zorunda kalırsan, ödemen sonucu göre yapılacak.";
			link.l1 = "Anladım, Ekselansları. Anlaştık, şimdi gemime dönüyorum.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "Dönüşünü bekliyor olacağım, kaptan!";
			link.l1 = "Müsaadenizle ayrılıyorum.";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			DialogExit();
			AddQuestRecord("Portugal", "10");
			NextDiag.CurrentNode = "Portugal_8";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", false);//открыть выходы из города
			bDisableFastReload = true;//закрыть быстрый переход
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.Portugal_Seapatrol.win_condition.l1 = "location";
			pchar.quest.Portugal_Seapatrol.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_Seapatrol.function = "PortugalSeapatrolGo";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1 = "location";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Portugal_SeapatrolAvendel.function = "AvendelSpeach";
		break;
		
		case "Portugal_8":
			dialog.text = "Kaptan, kıyı sularımızda iki gün devriye gezeceğiniz konusunda bir anlaşmamız olduğunu sanıyordum!";
			link.l1 = "Evet, tabii ki. Bunu hatırlıyorum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Portugal_8";
		break;
		
		case "Portugal_9":
			dialog.text = "Pekâlâ, anlaşmanın sana düşen kısmını yerine getirdin. İşte ödülün - anlaştığımız gibi 10.000 peso.";
			link.l1 = "Teşekkür ederim! Gördüğünüz gibi, endişeleriniz yersizmiş. Size bol şans dilerim!";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			DialogExit();
			AddMoneyToCharacter(pchar, 10000);
			NextDiag.CurrentNode = "First time";
			pchar.quest.MartiniqueGovernorOver.over = "yes"; //снять таймер
		break;
		//<-- Португалец
		
		// Warship, 16.05.11. Генер "Правосудие на продажу".
		case "JusticeOnSale_1":
			dialog.text = "Oh "+GetAddress_Form(NPChar)+", beni şaşırttınız! O alçaklar gerçekten bu kadar cüretkâr mı oldular? Hemen komutanı bilgilendirmeli ve oraya bir sahil devriyesi göndermeliyim!";
			link.l1 = "Yardımcı olduğum için memnun oldum. Şimdi izninizi isteyebilir miyim?";
			link.l1.go = "JusticeOnSale_2";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
			
			DeleteQuestCondition("JusticeOnSale_MapEnter");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "Elbette, kaptan. Buyurun – lütfen, benden size şahsen küçük bir ödül kabul edin.";
			link.l1 = "Teşekkür ederim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("JusticeOnSale_DlgExitAfterMayor_1");
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Haklısınız, kaptan! Bunu böyle bırakamayız! Sizden ricam, hemen şuraya gitmeniz: "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+", gemilerini bul ve tüm çeteyi tutukla! Direnirlerse güç kullan ve tereddüt etme!";
			link.l1 = "Müsaadenizle ayrılıyorum.";
			link.l1.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "Şimdi git. Oraya yelken aç ve kimsenin adaletten kaçmadığından emin ol. Önce kıyıya çıkman gerekecek, sonra gemiyle ilgilenebilirsin.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("JusticeOnSale_DlgExitAfterMayor_2");
		break;
		
		case "JusticeOnSale_7":
			dialog.text = "Yardımınız için teşekkür ederim. O alçaklar hak ettiklerini buldu. Lütfen, size şahsen sunmak istediğim bu mütevazı ödülü kabul edin. Kasabamda düzeni ve huzuru çok takdir ediyorum.";
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			AddMoneyToCharacter(PChar, sti(PChar.rank) * 300 + hrand(1000));
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			DialogExit();
		break;
		//<-- Правосудие на продажу
		
			//--> Jason регата
		case "Regata":
			// belamour legendary edition -->
			if(sti(pchar.rank) < 15)
			{
				Notification_Level(false, 15);
				dialog.text = "Ah, harika, sizi görmek güzel, kaptan! Yeteneklerinizden haberdarım, ama gerçekten hazır olduğunuzda geri gelin.";
				link.l1 = "Evet, elbette. Nasıl isterseniz.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Oh, harika, seni görmek ne güzel kaptan! Tam zamanında geldin – regatta birkaç gün içinde başlayacak. Sana bir görevli tarafından verilmiş olması gereken regatta kurallarını okudun mu?";
				link.l1 = "Evet, efendim, yaptım.";
				link.l1.go = "Regata_1";
				RemoveItems(PChar, "letter_open", 1);//уберем письмо
				DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
			}
		break;
		
		case "Regata_1":
			dialog.text = "Ve 50.000 peso - giriş ücretinizi, ödül havuzuna katkınız olacak olan parayı - hazırladınız mı?";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Evet, elbette. Lütfen ücretimi kabul edin.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "Şu anda biraz nakit sıkıntısı çekiyorum. Ama gereken miktarı mutlaka bulacağım.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "Very good. If you win, you'll get your money back fivefold. Now you need to become better acquainted with the rules of the regatta.\nYou can learn all the details from Sir Henry Stivenson; he should be in one of the rooms in the residence. Go to him—he'll explain everything.";
			link.l1 = "Pekâlâ. Tam da bunu yapacağım.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "Pekâlâ, ama lütfen fazla oyalanmayın, Kaptan. Regatta çok yakında başlıyor.";
			link.l1 = "Anladım. Parayı en kısa zamanda getirmeye çalışacağım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "Aha! Ve işte burada regatta'nın galibi! İyi günler, Kaptan "+GetFullName(pchar)+" ! Bu hak edilmiş başarınız için sizi tebrik etmeme izin verin! İngiliz kolonilerinde regatta kazananları her zaman popüler olmuştur – ve bu hiç de şaşırtıcı değil.";
			link.l1 = "Teşekkür ederim, efendim!";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "Şimdi en keyifli kısma geçelim - ödül töreni. Birincilik ödülü 250.000 peso. Tebrikler!";
			link.l1 = "Teşekkürler!";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			// belamour legendary edition в регате только один приз -->
			GiveItem2Character(pchar, "blade_26");
			GiveItem2Character(pchar, "cirass4");
			GiveItem2Character(pchar, "bussol");
			
			dialog.text = "Ayrıca, sana değerli ödüller de verilecek: efsanevi Toledo çeliğinden 'Asoleda' rapieri, bir Milan zırhı ve kaliteli bir pusula. Hepsi senin olacak.";
			// <-- legendary edition
			link.l1 = "Çok memnun oldum, efendim. Gerçekten, böyle bir cömertliği beklemezdim.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "İngiliz kolonilerinin tüm tebaası adına, regattaya katıldığınız için teşekkür eder, bir kez daha zaferinizi kutlarım! Eğer bahis oynadıysanız, Sir Henry Stevenson'a gidip henüz yapmadıysanız kazancınızı alın. Size bol şanslar, kaptan!";
			link.l1 = "Nezaketiniz için teşekkür ederim efendim! Buna karşılık, beni böyle büyük bir etkinliğe katılma fırsatıyla onurlandırdığınız için size teşekkür etmek isterim. Şimdi izninizle müsaadenizi isteyeyim.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}

string GetGangLocation(ref npchar)
{
    int n;
	string island = GetArealByCityName(npchar.city);
	string LocationId, sAreal;
	int storeArray[2];
	SetArraySize(&storeArray, MAX_LOCATIONS);  
    int howStore = 0;

	for(n=0; n<MAX_LOCATIONS; n++)
	{				
		if (GiveArealByLocation(&locations[n]) == island)
		{			
			//==> на всякий случай
			if (CheckAttribute(&locations[n], "DisableEncounters") && locations[n].DisableEncounters == true) continue;
			LocationId = locations[n].id;
			if (findsubstr(LocationId, "jungle" , 0) != -1 || findsubstr(LocationId, "Shore" , 0) != -1 || findsubstr(LocationId, "CaveEntrance" , 0) != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	n = storeArray[hrand(howStore-1)];
	return locations[n].id;
}

string GetSpyLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId")) //если взят квест по доставке малявы
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[hrand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GetSpyColony(ref NPChar)
{
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;
	string sChrId;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		// Rebbebion, чуть изменил функцию, чтобы условно испанцы не просили пробраться к испанцам, французы к французам и т.д
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetRelation2BaseNation(sti(colonies[n].nation)) == RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].id != npchar.City && colonies[n].nation != npchar.nation)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[Rand(howStore-1)]].id;
}

int SelectCureerShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 4 - rand(1);
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY);
}

int SelectPirateShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 5;
	if(iRank >= 12 && iRank < 21) iClass = 4;
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL + FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
}

int SelectCustomPatrolShipType(int iFlagType)
{
	if(CheckAttribute(pchar, "questTemp.StatusCity"))
	{
		return SHIP_CAREERLUGGER;
	}
	
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 4 - rand(1);
	
	return GetRandomShipType(GetClassFlag(iClass), iFlagType, FLAG_SHIP_NATION_ANY);
}

int SelectArsenalShipType(int iFlagType)
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), iFlagType, FLAG_SHIP_NATION_ANY);
}

string SelectPassText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "That Judas, using his position, sold an important state secret to an enemy power."; break;
		case 1: sText = "That foul scoundrel killed his relative, a well-known and noble man, in order to inherit his fortune."; break;
		case 2: sText = "That foul scoundrel insulted my family and me personally."; break;
		case 3: sText = "This thieving rogue stole a decent sum of money from our city's treasury."; break;
		case 4: sText = "That villain is guilty of deaths of nearly a dozen of our citizens."; break;
		case 5: sText = "That rogue used his connection to take possession of a merchant vessel, and then he stole it and sold at the neighboring shipyard."; break;
	}
	return sText;
}

string SelectFugitiveCity()
{
	string sCity;
	switch (rand(3))
	{
		case 0: sCity = "LaVega"; break;
		case 1: sCity = "PuertoPrincipe"; break;
		case 2: sCity = "LeFransua"; break;
		case 3: sCity = "FortOrange"; break;
	}
	return sCity;
}

string SelectFugitiveText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "one of the junior officers in our garrison has deserted and left the colony on board of a merchant ship."; break;
		case 1: sText = "one of our officers deserted right on duty and escaped on board of a smuggler ship."; break;
		case 2: sText = "one of our naval officers serving on a patrol brig deserted for unknown reason, hijacked a long boat and disappeared on it."; break;
		case 3: sText = "one of our prison guards threw up his service for  unknown reason and left our colony aboard a private vessel."; break;
		case 4: sText = "one of the soldiers in our garrison abandoned his post while keeping guard, went to the cove and left this place aboard an unknown vessel."; break;
		case 5: sText = "one of our military officers, captain of a patrol lugger, abandoned his ship in the open sea and went south on a fishing long boat."; break;
	}
	return sText;
}
