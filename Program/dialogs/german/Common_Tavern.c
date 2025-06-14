#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
#include "interface\ship.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	int iTest, iTemp;
	string sTemp;
	string NPCCity = NPChar.City;
    iTest = FindColony(NPChar.City); // город 
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;
	
	if(!CheckAttribute(pchar, "questTemp.TavernVisit."+(NPCCity) )) 
	{
		pchar.questTemp.TavernVisit.(NPCCity) = true;
		pchar.questTemp.TavernVisit.counter = sti(pchar.questTemp.TavernVisit.counter) + 1;
		notification("Erster Tavern-Besuch " + XI_ConvertString(NPCCity + "TavernName"), "Drunk");
		AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 10.0);
	}	
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Der Alarm wurde in der Stadt ausgelöst und jeder sucht nach dir. Wäre ich du, würde ich nicht hier bleiben.","Alle Stadtwachen durchkämmen die Stadt auf der Suche nach dir. Ich bin kein Narr und werde nicht mit dir sprechen!","Lauf, "+GetSexPhrase("Kamerad","Lass")+", bevor die Soldaten dich zu Hackfleisch verarbeiten..."),LinkRandPhrase("Was brauchst du, "+GetSexPhrase("Schurke","Stinker")+"?! Die Stadtwachen haben deine Witterung aufgenommen, du wirst nicht weit kommen"+GetSexPhrase(", dreckiger Pirat!","")+"","Mörder, verlasse sofort meinen Platz! Wachen!","Ich habe keine Angst vor dir, "+GetSexPhrase("Schuft","Ratte")+"! Bald wirst du in unserem Fort gehängt werden, du kommst nicht weit..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, ein Alarm ist für mich nie ein Problem...","Sie werden mich nie kriegen."),RandPhraseSimple("Halt den Mund, "+GetWorkTypeOfMan(npchar,"")+", oder ich reiße dir die Zunge heraus!","Heh, "+GetWorkTypeOfMan(npchar,"")+", und alle da - um Piraten zu fangen! Das sage ich dir, Kumpel: sitz ruhig und du wirst nicht sterben..."));
				link.l1.go = "exit";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("Und du bist es, Bastard! Denkst du, wir schenken dir hier Rum ein? Sicherlich nicht! Jungs! Zu den Waffen! Tötet diesen Schurken!","Möchtest du einen Drink, Pirat? Ha! Nein! Jetzt zeigen wir dir, was Sache ist! Jungs, zieht eure Klingen!");
				link.l1 = RandPhraseSimple("Hä? Was?","Halt!");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//Jason, Бремя гасконца
			if(NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
				{
					link.l1 = "Herr, ich suche Arbeit. Haben Sie irgendwelche Jobs?";
					link.l1.go = "Sharlie_rum";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
				{
					link.l1 = "Ich habe Ihren Auftrag erfüllt. Das Langboot mit dem Rum wurde zur Bucht von Le Francois geliefert und Ihren Leuten übergeben.";
					link.l1.go = "Sharlie_rum_5";
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "crew" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Haben Sie etwas gewünscht, Monsieur?";
				Link.l1 = "Hallo Wirt, ich muss eine Crew für mein Schiff anheuern. Kannst du mir dabei helfen?";
				Link.l1.go = "Sharlie_crew";
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "skiper" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Hallo nochmal. Was gibt's diesmal, Monsieur?";
				Link.l1 = ""+npchar.name+", Ich weiß, dass ich Sie belästige, aber nur noch eine Frage. Ich brauche einen Navigator - eine Idee, wo ich einen finden kann?";
				Link.l1.go = "Sharlie_skiper";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
    			dialog.text = "Was wünschen Sie, Monsieur?";
				Link.l1 = "Ich hatte gehofft, du könntest ein paar Fragen beantworten.";
				Link.l1.go = "quests";
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l2 = "Ich möchte ein Zimmer mieten.";
					link.l2.go = "room";
				}
				break;
			}			
			//Бремя гасконца
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "tavern" && npchar.city == "Tortuga")
			{
				dialog.text = "Ich freue mich, Sie zu sehen, mein Herr! Wie kann ich Ihnen behilflich sein? Rum, Brandy, schottischer Whisky?";
				Link.l1 = "Ich möchte eine Flasche Ihres besten französischen Weins und einen Zimmerschlüssel.";
				Link.l1.go = "mtraxx_tortuga";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "room" && npchar.city == "Tortuga")
			{
				dialog.text = "Sie haben bereits bezahlt, Monsieur, Ihr Zimmer befindet sich oben.";
				Link.l1 = "Danke.";
				Link.l1.go = "exit";
				break;
			}
			
			// Sinistra - Квест "Длинные тени старых грехов" ==>	
			if (CheckAttribute(pchar, "questTemp.DTSG_BasTerTavern") && npchar.city == "BasTer")
			{
				dialog.text = "Wie kann ich Ihnen dienen, Kapitän? Sie möchten wahrscheinlich ein Trinken nach dem, was passiert ist.";
				Link.l1 = "Das kann warten. Ich möchte eigentlich darüber sprechen, was passiert ist.";
				Link.l1.go = "DTSG_BasTerTavern_1";
				DelLandQuestMark(npchar);
				break;
			}
			// <== Квест "Длинные тени старых грехов" - Sinistra
			
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Start") && !CheckAttribute(pchar, "questTemp.TPZ_Tavern_1") && npchar.city == "BasTer")
			{
				dialog.text = "Verzeihen Sie, "+GetAddress_Form(NPChar)+", aber heute kann ich Ihnen keinen Tropfen Alkohol anbieten.";
				Link.l1 = "Was? Was ist das für eine Taverne, in der man nicht einmal einen Tropfen Rum bekommt? Habe ich etwa ein großes Fest verpasst, das Ihre Vorräte geleert hat?";
				Link.l1.go = "TPZ_Tavern_1";
				pchar.questTemp.TPZ_Tavern_1 = true;
				DelLandQuestMark(npchar);
				break;
			}
			//<-- Торговля по закону
			
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("Willkommen in meiner bescheidenen Taverne '"+XI_ConvertString(NPChar.City+"TavernName")+"', Herr. Ich bin froh, Sie zu sehen.","Zu Ihren Diensten, Herr! In unserer Taverne '"+XI_ConvertString(NPChar.City+"TavernName")+"' wir freuen uns immer, neue Besucher zu begrüßen.","Erstes Mal hier, Herr? Zögern Sie nicht, hier bei '"+XI_ConvertString(NPChar.City+"TavernName")+"' du fühlst dich immer wie zu Hause!"),LinkRandPhrase("Kommen Sie herein, Monsieur Kapitän. Ich erkenne Sie nicht, also muss dies Ihr erstes Mal bei '"+XI_ConvertString(NPChar.City+"TavernName")+".'","Noch nie zuvor getroffen, Herr. Lassen Sie uns bekannt machen: Ich bin "+GetFullName(npchar)+", der Wirt von '"+XI_ConvertString(NPChar.City+"TavernName")+"'. ","Ich freue mich, unseren neuen Gast, Monsieur Kapitän, begrüßen zu dürfen! In meiner Taverne '"+XI_ConvertString(NPChar.City+"TavernName")+"' erstes Getränk geht immer aufs Haus! Ich bin der Besitzer dieses Ortes, "+GetFullName(npchar)+", begrüßt Sie."),LinkRandPhrase("Herr Kapitän! Willkommen in der Taverne '"+XI_ConvertString(NPChar.City+"TavernName")+"'!","Oh, welch glänzender Hidalgo hat unsere Taverne besucht '"+XI_ConvertString(NPChar.City+"TavernName")+"'! Ist es Ihr erstes Mal hier, Herr?","Guten Tag, Herr! Ich bin "+GetFullName(npchar)+", bescheidener Besitzer von '"+XI_ConvertString(NPChar.City+"TavernName")+"', wir freuen uns, Sie hier zu begrüßen!"),LinkRandPhrase("Hallo, Mynheer Kapitän. Ich bin der Besitzer der Taverne '"+XI_ConvertString(NPChar.City+"TavernName")+"'. Erster Aufenthalt bei uns?","Guten Tag, Herr. Willkommen in der Taverne '"+XI_ConvertString(NPChar.City+"TavernName")+"'. ","Sehr gut, Sie zu sehen, mein Herr Kapitän! Unsere ganz eigene Taverne '"+XI_ConvertString(NPChar.City+"TavernName")+"' grüßt dich! Rum, Wein, oder wenn ich dich verführen könnte, haben wir einen frechen neuen kleinen holländischen Geist namens Gin?"));
				Link.l1 = LinkRandPhrase("Eine gemütliche Stätte habt Ihr hier... Erlaubt mir, mich vorzustellen - "+GetFullName(pchar)+", es ist ein Vergnügen, Sie zu treffen.",""+GetFullName(pchar)+", es ist eine Freude, dich zu treffen. Was kannst du mir also anbieten?","Mein Name ist "+GetFullName(pchar)+" und ich bin neu in diesem Hafen. Sag mir, wofür ist diese Taverne am besten bekannt?");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_tavern")
				{
					dialog.text = "Ahoi, Rumba! Zurück von einer Reise oder auf dem Weg zu einer neuen?";
					link.l1 = "Hallo, "+npchar.name+". Hab einfach beschlossen, vorbeizuschauen.";
					Link.l1.go = "Helen_meeting";
					NPChar.quest.meeting = "1";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				// Квестовый генератор священника. Квест №1. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
		        {
		            if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToBarmen"))
		            {
		            	iTemp = sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen);
		            	dialog.Text = "Also, Kapitän, haben Sie mir gebracht "+FindRussianMoneyString(iTemp)+".";
		            	if(sti(PChar.Money) >= iTemp)
		            	{
							link.l1 = "Ja, habe ich. Hier sind sie...";
							link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
						}
						else
						{
							link.l1 = "Nein, ich habe noch nicht...";
							link.l1.go = "exit";
						}
		            }
		            else
		            {
		            	dialog.Text = "Was möchtest du, mein Guter "+GetSexPhrase("Herr","Dame")+"?";
						link.l1 = "Eine Flasche Rum für meinen Kumpel an jenem Tisch dort drüben.";
						link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
					}
					break;
				}
				// <-- Квестовый генератор священника. Квест №1.
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, ehrenwerte Gäste! Hey, du - rück mal ein Stück und mach Platz für einen galanten Kapitän! Und mach schnell, bevor ich dich rauswerfe, haha!","Barmherziger Gott oben! Wenn es nicht "+GetFullName(pchar)+"! Ich habe gerade eine neue Lieferung erlesener Weine bekommen, bitte komm rein!","Ach, "+GetAddress_Form(NPChar)+", hast du Probleme? Darf ich dich behandeln? Diese Flasche geht aufs Haus. Vertrau mir, das ist der beste Wein in der Gegend..."),LinkRandPhrase("Oh, es ist Kapitän "+GetFullName(pchar)+"! Hey, du! Zeig etwas Respekt vor dem guten Kapitän! Das ist kein Stall! Entschuldigen Sie mich, Kapitän, ihre Mütter haben ihnen offensichtlich nie Manieren beigebracht.","Nun, nun, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Wir haben eine lange Nacht vor uns, haha! Mädels, ihr solltet eure besten Kleider tragen!","Guten Nachmittag, "+GetFullName(pchar)+", Ich freue mich, Sie zu sehen! Bitte mein Herr, ich habe eine Bitte. Ich habe gerade neue Tische gekauft, also bitte heute Abend keinen Streit."),LinkRandPhrase("Hallo, Kapitän. Machen Sie es sich bequem, aber denken Sie daran, dass sogar Kapitän Sharp selbst in meinem Etablissement Manieren hat.","O-ho-ho! Schau mal wer da ist? Es ist "+GetFullName(pchar)+" selbst! Und wir haben gerade angefangen, uns in deiner Abwesenheit zu langweilen! Wie wäre es, wenn du die Kameraden mit einem Abenteuer unterhältst, während ich ein neues Fass Rum öffne, Kapitän?","O-ho-ho! Es ist "+GetFullName(pchar)+" selbst! Ich hoffe, du wirst meine Kunden nicht wieder mit den Geschichten deiner großartigen Abenteuer auf hoher See stehlen?")),LinkRandPhrase(LinkRandPhrase(""+GetFullName(pchar)+"! Dieser alte Seebär freut sich immer, Sie in seiner Einrichtung zu sehen! Bitte Herr, nehmen Sie Platz und die Mädchen werden sich um Sie kümmern!","Bitte Kapitän, machen Sie es sich bequem! Immer froh, meinen Lieblingsgast zu begrüßen. Was ist dein Gift?","Schön dich wieder zu sehen, "+GetFullName(pchar)+"! Möchten Sie einen Tisch für sich allein? Oder möchten Sie an der Bar sitzen?"),LinkRandPhrase("Guten Nachmittag, Kapitän. Es ist kalt in der Luft, lassen Sie mich Ihnen etwas ausgezeichneten Glühwein anbieten, den ich gerade gemacht habe, auf Kosten des Hauses!","Hallo, Kapitän "+GetFullName(pchar)+"! Ich bin froh, dass du wieder zu Besuch gekommen bist. Was möchtest du?","Ich bin froh, dich zu haben, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Ich freue mich, dass Sie mein bescheidenes Etablissement besuchen! Wir tun alles, um zu gefallen."),LinkRandPhrase("Kapitän! Willkommen, willkommen! Ich habe einige prächtige d'Anjou, würdig für König Louis selbst und habe sie speziell für dich aufgehoben!",""+GetFullName(pchar)+"! Ich bin so froh, dass du gekommen bist. Soll ich all diese Seeratten vertreiben oder würdest du es vorziehen, dass sie bleiben? Vertrau mir, ich würde gerne die ganze Taverne für dich räumen!","Mein Gott, hier ist der Kapitän "+GetFullName(pchar)+"! He, Charmeure - bringt das allerbeste Tischtuch zum Kapitänstisch!")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Oh, ich sehe, man erinnert sich hier an mich... Halt, füll mein Glas, Kumpel, während ich mich hier umsehe...","Beruhige dich, Kumpel, heute bin ich gut gelaunt. Lass uns mit Rum anfangen, sollen wir nicht?..."),RandPhraseSimple("Oh... du bist nicht allzu glücklich, mich hier zu haben? Ich hoffe, ich habe dich falsch verstanden, ha!","Ahoi. Ich hoffe, dein Wein ist besser als deine Begrüßung? Sonst kann ich wütend werden, weißt du...")),RandPhraseSimple(RandPhraseSimple("Immer froh, dich zu besuchen, Kumpel. Was hast du, um einen salzigen Hund aufzuwärmen?","Ahoi Kamerad, deine Einrichtung wird mit jedem Tag besser! Es ist immer ein Vergnügen, hier zu besuchen..."),RandPhraseSimple("Du hast einen alten Wanderer nicht vergessen? Ich bin geschmeichelt, Kumpel.","Gut, einen alten Freund wieder zu sehen... Hast du noch etwas Rum übrig?")));
				Link.l1.go = "step_node";
			}
			break;
				
			case "step_node":
				dialog.Text = LinkRandPhrase("Ich höre zu, Kapitän.","Meine Taverne '"+XI_ConvertString(NPChar.City+"TavernName")+"', zu Ihren Diensten, Kapitän!","Zu Befehl, Käpt'n! Was darf's heute sein?");
				Link.l1 = "Gibt es Jungen auf der Insel, die bereit sind, ihr Glück auf See zu versuchen?";
				Link.l1.go = "crew hire";
				Link.l2 = "Ich hoffte, Sie könnten ein paar Fragen beantworten.";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "Ich würde gerne über finanzielle Angelegenheiten sprechen.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		            	{
					link.l10 = LinkRandPhrase("Können Sie mir etwas über den jüngsten Raub in der Kirche erzählen?","Was wissen Sie über den jüngsten Raub in der Kirche?","Haben Sie etwas über den jüngsten Raub in der Kirche gehört?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Leute sagen, dass du so ziemlich alles in dieser Kolonie weißt. Ich möchte kaufen "+pchar.GenQuest.Device.Shipyarder.Type+", und mir wurde gesagt, dass es in Ihrer Stadt verkauft wurde. Nun, jemand hat es auf dem Straßenmarkt verkauft. Können Sie mir dazu etwas sagen?";
					link.l16.go = "Device_Tavern";
				}
				// <-- генератор Неудачливый вор
			
				//Jason --> генератор Место под солнцем
				if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
				{
					link.l17 = "Suche nach einem Schwindler namens "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Wo kann ich ihn finden?";
					link.l17.go = "Sunplace_Tavern";
				}
				// <-- генератор Место под солнцем
			
				// --> Голландский гамбит
				if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Hallo, "+npchar.name+". Ich muss Jacob van Berg finden - wo ist er? Ich sehe ihn nicht in deiner Taverne...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Hallo, "+npchar.name+". Ich suche einen Caballero namens Fernando Rodriguez. Ist er in Ihrer Stadt aufgetaucht?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				// <-- Голландский гамбит
			
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "Ich bin gekommen, um meine Gewinne abzuholen, die bei dir sicher aufbewahrt wurden. "+npchar.name+".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
			
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "Ich habe mich gefragt, wo ich einen Mann namens  finden kann"+pchar.GenQuest.Marginpassenger.q2Name+"? Er lebt in deiner Stadt.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l3 = pcharrepphrase("Hast du ein freies Zimmer, Kumpel?","Haben Sie ein freies Zimmer, ich würde hier für eine Weile bleiben.");
					link.l3.go = "room";
				}
				Link.l4 = "Ach, ich gehe schon, "+NPChar.name+". Bis dann.";
				Link.l4.go = "exit";
		break;
		
		case "Helen_meeting":
			dialog.Text = "Ach, na gut, komm rein, komm rein. Du bist hier immer willkommen.";
			link.l1 = "Ja, danke. Es war gut, dich zu sehen. Lebewohl.";
			link.l1.go = "exit";
			Link.l2 = "Ich könnte ein paar neue Hände gebrauchen. Stellen Sie nur sicher, dass sie fähig sind, in Ordnung?";
			Link.l2.go = "crew hire";
			link.l3 = "Ich würde gerne auf festem Boden ruhen und meine Gedanken sammeln, nicht wenn meine Mutter im Haus herumwuselt.";
			link.l3.go = "Helen_room";
			Link.l4 = "Könnte ich Sie etwas fragen? ";
			Link.l4.go = "quests";
			link.l5 = " Ich habe eine Angelegenheit, die ich mit Ihnen besprechen möchte, "+NPChar.name+".";
			link.l5.go = "Helen_rumours_tavern";
		break;
		
		case "Meeting":
			// Квестовый генератор священника. Квест №1. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
	        {
	            dialog.Text = "Was möchtet Ihr, gnädige "+GetSexPhrase("Herr","Dame")+"?";
				link.l1 = "Eine Flasche Rum für meinen Kameraden an jenem Tisch dort drüben.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
				break;
			}
			// <-- Квестовый генератор священника. Квест №1.
			dialog.Text = LinkRandPhrase("Ich höre zu, Kapitän.","Was kann ich Ihnen anbieten, Kapitän?","Also Kapitän, was wird es sein?");
			Link.l1 = "Ich brauche eine Mannschaft, "+NPChar.name+".";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name+", lass uns reden...";
			Link.l2.go = "int_quests";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = "Ich möchte über finanzielle Angelegenheiten sprechen.";
				link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
			}
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	        {
				link.l10 = LinkRandPhrase("Können Sie mir etwas über den jüngsten Raub in der Kirche erzählen?","Was wissen Sie über den jüngsten Raub in der Kirche?","Haben Sie etwas über den jüngsten Raub in der Kirche gehört?");
				link.l10.go = "Tavern_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Die Leute sagen, du weißt so ziemlich alles in dieser Kolonie. Ich möchte kaufen "+pchar.GenQuest.Device.Shipyarder.Type+", und mir wurde gesagt, dass es in Ihrer Stadt verkauft wurde. Nun, jemand hat es auf den Straßen verkauft. Können Sie mir etwas darüber erzählen?";
				link.l16.go = "Device_Tavern";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
			{
   				link.l17 = "Erzähl mir von einem Erpresser namens "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Wo kann ich ihn finden?";
				link.l17.go = "Sunplace_Tavern";
			}
			// <-- генератор Место под солнцем
			
			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Hallo, "+npchar.name+". Ich muss Jacob van Berg finden - wo ist er? Ich sehe ihn nicht in deiner Taverne...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Hallo, "+npchar.name+". Ich suche einen Caballero namens Fernando Rodriguez. Ist er in eurer Stadt aufgetaucht?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				//<-- Голландский гамбит
				
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "Ich bin gekommen, um meine Gewinne abzuholen, die bei dir sicher aufbewahrt werden. "+npchar.name+".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "Ich habe mich gefragt, wo ich einen Mann namens finden kann "+pchar.GenQuest.Marginpassenger.q2Name+"? Er wohnt in deiner Stadt.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
			if(!CheckAttribute(pchar,"questTemp.TimeLock"))
			{
				link.l3 = pcharrepphrase("Hast du ein freies Zimmer, Kumpel?","Haben Sie ein freies Zimmer, ich würde hier für eine Weile bleiben.");
				link.l3.go = "room";
			}
			Link.l4 = "Ich denke, ich komme später wieder.";
			Link.l4.go = "exit";
		break;
		
		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;
			
			if (!ok)
			{
				Dialog.text = "Und wofür brauchen Sie Matrosen, Kapitän? Ich sehe Ihr Schiff nicht im Hafen.";
				link.l1 = RandPhraseSimple("Genau ... Ich hatte am falschen Ort angelegt.","Ich habe vergessen, den Hafen zu betreten...");
				link.l1.go = "exit";
				break;
			}
			
            if (makeint(environment.time) > 22.0 || makeint(environment.time) < 7.0)
			{
				Dialog.text = "Normalerweise gibt es viele Männer, die Seefahrer werden wollen, aber jetzt ist es zu spät - sie werden erst am Morgen auftauchen. Vielleicht möchtest du ein Zimmer mieten und auf sie warten?";
				link.l1 = "In Ordnung. Haben Sie freie Zimmer?";
				link.l1.go = "room";
				link.l2 = "Ich bin momentan nicht an einem Zimmer interessiert. Bis dann.";
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = "Denkst du, wir bedienen hier gesuchte Verbrecher? Sei dankbar, dass ich nicht die Wachen rufe.";
					link.l1 = "Danke.";
					link.l1.go = "exit";
                }
                else
                {
					if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
					{
						Dialog.text = "Kapitän, heute ist keine Seele in der Taverne. Alle Freiwilligen sind mit Kapitän Blackwood gegangen.";
						link.l1 = "Das ist schade!";
						link.l1.go = "exit";
						break;
					}
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 3 && GetCrewQuantity(rColony) == 0)
					{
						Dialog.text = "Ach, entschuldigung Kapitän, Sie sind einfach ein bisschen zu spät. Alle Kameraden, die sich verabschieden wollten, sind gerade mit dem tapferen Kapitän abgesegelt "+GetFullName(CharacterFromID(NPChar.CrewHired.PGGId))+".";
						link.l1 = "Das ist schade!";
						link.l1.go = "exit_crew";
					}
					else
					{						
						if(bPartitionSet)
						{		
							if(GetPartitionAmount("CrewPayment") > 0)
							{
								if(IsEquipCharacterByArtefact(pchar, "totem_07"))
								{
									DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
									NextDiag.CurrentNode =  NextDiag.TempNode;
									DialogExit();
									LaunchHireCrew();							
								}
								else
								{
									dialog.text = "Kapitän, die Leute sagen, dass Sie ziemlich geizig sind. Wir haben hier niemanden, der Ihrer Besatzung beitreten möchte.";
									link.l1 = "Ich sehe...";
									link.l1.go = "exit";
								}
							}
							else
							{
								DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
								NextDiag.CurrentNode =  NextDiag.TempNode;
								DialogExit();
								LaunchHireCrew();	
							}
						}	
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
							NextDiag.CurrentNode =  NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();							
						}						
					}
				}
			}
		break;
		
		case "exit_crew" :
			DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
			NextDiag.CurrentNode =  NextDiag.TempNode;
			DialogExit();
			LaunchHireCrew();
		break;
	////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////	
        case "int_quests":
			dialog.text = "Ich bin ganz Ohr.";
			//link.l1 = "Ich suche Arbeit. Können Sie mir helfen?";
			//link.l1.go = "work";
			//homo 15/06/06 слухи
			link.l2 = LinkRandPhrase("Können Sie mir die neuesten Nachrichten erzählen?","Was geht in diesen Landen vor?","Was gibt's Neues an Land?");
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = "Ich bin wegen einer anderen Angelegenheit gekommen.";
			link.l3.go = "quests";
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "EncGirlFack_fighted")
				{
					link.l5 = "Weißt du, wo ich finden kann "+pchar.GenQuest.EncGirl.name+"?";
					link.l5.go = "EncGirl_1";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					link.l6 = "Können Sie mir sagen, wo ich suchen könnte "+pchar.GenQuest.EncGirl.sLoverId+"?";
					link.l6.go = "EncGirl_3";
				}
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "tavern_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = "Ahoi, ich kam auf Einladung Eures Sohnes."; 
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.City && CheckAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern"))
			{
				if(pchar.GenQuest.CaptainComission.variant == "A0")
				{												
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Also, hast du gesehen  "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = "Können Sie mir sagen, wo ich suchen sollte  "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_1";
					}
				}	

				if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					link.l9 = "Wissen Sie, wo ich den Kapitän einer Patrouille finden kann "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Konto"))+" "+pchar.GenQuest.CaptainComission.Name+"?";
					link.l9.go = "CaptainComission_Tavern7";					
				}				
				if(pchar.GenQuest.CaptainComission.variant == "A3" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Also, hast du gesehen "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.CanoneerName,NAME_NOM)+"?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{					
						link.l9 = "Kennen Sie etwas über den Kapitän einer Patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Akk"))+" "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_Tavern1";
						if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
						{
							pchar.GenQuest.CaptainComission.GetRumour = true;
							SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
						}	
					}	
				}					
			}
			if(CheckAttribute(pchar,"GenQuest.Hold_GenQuest") && NPChar.city == pchar.GenQuest.Hold_GenQuest.City && pchar.GenQuest.Hold_GenQuest.Speak_Tavern == false )
			{
				link.l10 = "Könnten Sie mir sagen, wo ich einen Mann namens finden kann "+pchar.GenQuest.Hold_GenQuest.Name+"?";
				link.l10.go = "hold_genquest1";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakTavern") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l11 = "Ich habe zufällig nicht weit von hier einige Schiffsunterlagen gefunden....";
				link.l11.go = "ShipLetters_4";			
			}

			// Jason --> квест губера на поиск дезертира
			if(CheckAttribute(pchar, "GenQuest.FindFugitive") && pchar.GenQuest.FindFugitive != "Late" && sti(NPChar.nation) == PIRATE)
			{
				link.l12 = "Hör zu, ich suche einen alten Freund von mir, "+pchar.GenQuest.FindFugitive.Name+" ist sein Name. Ein befreundeter Kapitän hat mir erzählt, dass er auf den Weg zu eurer Siedlung war. Habt ihr ihn zufällig getroffen?";
				link.l12.go = "FindFugitiveTav";
			}
			//<-- поиск дезертира

			link.l15 = "Nichts, danke, .";
			link.l15.go = "exit";
		break;
		
		case "hold_genquest1":
			switch(sti(pchar.GenQuest.Hold_GenQuest.TavernVariant))
			{
				case 0:
					dialog.text = LinkRandPhrase("Was hast du gesagt? "+pchar.GenQuest.Hold_GenQuest.Name+"? Hmm... Nie von ihm gehört.","Bist du sicher, dass er aus unserer Stadt stammt? Ich habe noch nie von so einer Person gehört.","Es gab niemanden wie ihn in unserer kleinen Kolonie. Habe in all meiner Zeit hier noch nie von ihm gehört.");
					link.l1 = "Bist du sicher?";
					link.l1.go = "hold_genquest2";					
				break;
				
				case 1: 
					switch (hrand(3))
					{
						case 0:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
							pchar.GenQuest.Hold_GenQuest.found = "church";
						break;
						case 1:
							if (npchar.city != "Panama")
							{
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shipyard";						
							pchar.GenQuest.Hold_GenQuest.found = "shipyard";
							}
							else
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
								pchar.GenQuest.Hold_GenQuest.found = "church";
							}
						break;
						case 2:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the usurer";												
							pchar.GenQuest.Hold_GenQuest.found = "bank";
						break;
						case 3:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shop";						
							pchar.GenQuest.Hold_GenQuest.found = "store";
						break;
					} 
					dialog.text = "Schau mal "+pchar.GenQuest.Hold_GenQuest.foundStr+", er kann dort ziemlich oft gefunden werden.";
					link.l1 = "Danke, das werde ich tun.";
					link.l1.go = "hold_genquest3";				
				break;
				
				case 2:
					dialog.text = LinkRandPhrase(RandPhraseSimple("Was hast du gesagt? "+pchar.GenQuest.Hold_GenQuest.Name+"? Hmm... Noch nie von ihm gehört. Sind Sie sicher, dass er aus unserem Dorf stammt? Ich habe noch nie von einer solchen Person gehört.","He-he... Nun, jetzt weiß nur der Herr selbst, wo man ihn suchen soll - in der Hölle oder im Himmel. Er starb vor über einem Jahr, aber die Leute fragen immer noch nach ihm... Keine Ruhe für den armen Bastard..."),RandPhraseSimple("Du wirst ihn dort nicht finden - zumindest nicht im Land der Lebenden. Er ist vor nicht allzu langer Zeit gestorben - Gelbfieber... Gott schone seine Seele... Was für ein kräftiger Mann er doch war! Als er jung war, war er ein großes Abenteurer! Aber wenn der Tod nach dir kommt, gibt es nicht viel, was du tun kannst...","Oh, hast du ihn vermisst? Er hat diese Orte vor langer Zeit verlassen. Niemand weiß, wohin er gegangen ist - vielleicht in die nordamerikanischen Kolonien, vielleicht nach Hause nach Europa. Er hat einfach seine Sachen gepackt und ist fort."),"Oh, suchst du das "+pchar.GenQuest.Hold_GenQuest.Name+"wer wurde reich und kaufte sich ein Haus in Neuengland? Weißt du, es gab Zeiten, da verkaufte ich ihm Rum auf Kredit - er schuldet mir immer noch. Die Leute sind so undankbar, weißt du.");
					link.l1 = "Ich verstehe. Nun, danke trotzdem.";	
					link.l1.go = "hold_genquest4";
				break;
				
				case 3:
					dialog.text = "Nun, wo sonst sollte man nach ihm suchen, wenn nicht in der Taverne? Er ist dort ein häufiger Besucher - er ertränkt seine Sünden im Wein, he-he. Komm ein bisschen später zurück - wenn er auftaucht, werde ich ihm sagen, dass er auf dich warten soll.";	
					link.l1 = "Danke, das werde ich tun.";
					link.l1.go = "hold_genquest5";
				break;
			}
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;
		break;
		
		case "hold_genquest2":
			dialog.text = "Wie kann ich nicht sicher sein, wenn ich hier jeden persönlich kenne. Es ist nicht das erste Jahr, dass ich hier die Taverne leite. "+"Ich habe sie alle in allen möglichen Zuständen gesehen. Manchmal kam eine Frau, um ihren Mann abzuholen, manchmal gingen sie von selbst, und manchmal musste ich sie rausschmeißen. 'Bin ich sicher?!' Natürlich bin ich das!";
			link.l1 = "Nun, danke trotzdem...";	
			link.l1.go = "exit";
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			AddQuestRecord("HoldQuest", "7");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "hold_genquest3":
			Hold_GenQuest_GenerateChar();		
			AddQuestRecord("HoldQuest", "8");
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Gen")); 			
			AddQuestUserData("HoldQuest", "sFoundChar", pchar.GenQuest.Hold_GenQuest.foundStr);
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			SetFunctionTimerConditionParam("Hold_GenQuest_FindCharTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
		break;
		
		case "hold_genquest4":
			AddQuestRecord("HoldQuest", "13");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");			
			DialogExit();
		break;
		
		case "hold_genquest5":
			SetFunctionTimerConditionParam("Hold_GenQuest_GetMapTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_GenerateMapChar");			
		break;
		
		case "CaptainComission_1":
			dialog.text = LinkRandPhrase("Er ist hier oft zu Gast, aber gerade jetzt ist er nicht da. Komm ab und zu vorbei - wenn er auftaucht, werde ich ihm sagen, dass er hier auf dich warten soll.","Er ist ein häufiger Besucher hier. Wenn Sie später zurückkommen, werden Sie ihn sicher dort finden.","Kommen Sie von Zeit zu Zeit zurück - er ist ein häufiger Besucher hier. Ich werde ihm sagen, dass Sie nach ihm gesucht haben.");
			link.l1 = "Danke, ich komme später wieder...";
			link.l1.go = "CaptainComission_2";
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
		break;
		
		case "CaptainComission_2":
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromTavern.function = "CaptainComission_GenerateChar";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_3":
			dialog.text = "Er ist bereits hierher gekommen, also sollte er irgendwo in der Nähe sein...";
			link.l1 = "Danke.";
			link.l1.go = "exit";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
		break;
		
		case "CaptainComission_Tavern1":
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
			dialog.text = "Gibt es einen Mann, der ihn nicht kennt? Die ganze Siedlung spricht seit Tagen über ihn.";
			link.l1 = "Könnten Sie mir mehr erzählen?";
			link.l1.go = "CaptainComission_Tavern2";
		break;
		
		case "CaptainComission_Tavern2":
			dialog.text = "Ein bisschen, der Kapitän wurde hingerichtet, dasselbe kann man von einigen seiner Crew sagen. Der Rest wurde über die Karibik verstreut, ihrer Ränge und Positionen beraubt... Wofür? Laut einem Richter hatte er während einer Patrouille einen Piraten versenkt und die Beute für sich selbst versteckt\n"+"Hier ist die Sache, weder der Besitzer dieses Schiffes noch die Güter wurden gefunden ... sie haben die örtlichen Buchten und Einlässe durchsucht, aber ohne Erfolg.";
			link.l1 = "Was, keiner der Besatzung hat den Standort des Verstecks verraten?";	
			link.l1.go = "CaptainComission_Tavern3";	
		break;
		
		case "CaptainComission_Tavern3":
			dialog.text = "Nicht einen einzigen! Selbst unter Folter! Ich kann immer noch nicht verstehen, warum der Gouverneur diesem Verleumdung so begierig glauben würde. Kapitän "+pchar.GenQuest.CaptainComission.Name+" hatte einen guten Ruf, und seine Crew war gut ausgebildet und diszipliniert, dass jeder Admiral ihn beneiden würde.";
			link.l1 = "Und wo sollte ich nach den überlebenden Besatzungsmitgliedern suchen?";
			link.l1.go = "CaptainComission_Tavern4";
		break;
		
		case "CaptainComission_Tavern4":
			dialog.text = "Das weiß ich nicht - sie haben sich in alle vier Winde zerstreut... Obwohl... es ist noch einer von ihnen übrig, aber ich bezweifle, dass du viel von ihm lernen wirst. Er hat eine schwere Gehirnerschütterung. Wissen Sie, er diente als Kanonier unter "+pchar.GenQuest.CaptainComission.Name+". Er wurde zwei Tage nach dem Unfall bewusstlos in einer Bucht gefunden. Zuerst wurde er ins Krankenhaus gebracht und wie ein Held behandelt, aber als die Handlung sich verdichtete, warfen sie ihn ins Verlies und versuchten ihn zu verhören, entschieden dann aber, dass er zuerst medizinisch behandelt werden sollte, sowieso.";
			link.l1 = "Ist er immer noch hier?";
			link.l1.go = "CaptainComission_Tavern5";
		break;
		
		case "CaptainComission_Tavern5":
			pchar.GenQuest.CaptainComission.CanoneerName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Ja, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.CanoneerName,NAME_NOM)+" ist sein Name. Er taucht von Zeit zu Zeit auf, gibt die Pfennige, die er beim Betteln verdient, für Rum aus. Arme Seele. Wenn ich ihn sehe, werde ich ihm sagen, dass er hier auf dich warten soll.";
			link.l1 = "Danke, ich komme später wieder.";
			link.l1.go = "CaptainComission_Tavern6";
		break;
		
		case "CaptainComission_Tavern6":
			AddQuestRecord("CaptainComission2", "39");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			SetFunctionExitFromLocationCondition("CaptainComission_GenerateCanoneer", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_Tavern7":
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
			dialog.text = "Kenne ich ihn? Natürlich kenne ich ihn. Und was brauchst du ihn für?";
			link.l1 = "Ich habe Geschäfte mit ihm...";
			link.l1.go = "CaptainComission_Tavern8";
		break;
		
		case "CaptainComission_Tavern8":
			dialog.text = ""+GetAddress_Form(pchar)+", Sie sollten vorsichtig mit diesem 'Geschäft' sein. "+pchar.GenQuest.CaptainComission.Name+" wird wegen des Verdachts auf Piraterie festgehalten, und die Männer des Gouverneurs durchkämmen jetzt die Insel auf der Suche nach seinen Komplizen.";
			link.l1 = "Das sagst du nicht! Und was hat er gemacht?";
			link.l1.go = "CaptainComission_Tavern9";
		break;
		
		case "CaptainComission_Tavern9":
			dialog.text = "Ich weiß nicht, ob es wahr ist oder nicht, aber es wird gesagt, dass er die Ladung, die von einem vorbeifahrenden Piratenschiff konfisziert wurde, versteckt hat und sie nicht abgeliefert hat. Und trotzdem hat niemand den Pirat noch die Ladung gefunden. Ich kann immer noch nicht verstehen, warum der Gouverneur diesem Rufmord so begierig glauben würde. Kapitän "+pchar.GenQuest.CaptainComission.CapName+"  hatte einen anständigen Ruf, und er war ein großartiger Soldat, du kannst meinem Wort vertrauen, "+GetAddress_Form(pchar)+".";
			link.l1 = "Nun, danke für die Warnung. Wir sehen uns.";
			link.l1.go = "CaptainComission_Tavern10";
		break;
		
		case "CaptainComission_Tavern10":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				pchar.GenQuest.CaptainComission.GetRumour = true;
				SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
				SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
				AddQuestRecord("CaptainComission2", "19");
				AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
				AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			}			
			DialogExit();
		break;
				
		case "EncGirl_1":
			dialog.text = "Und wofür brauchst du sie?";
			link.l1 = "Ich habe Geschäfte mit ihr ...";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Die Hälfte der Männer in unserer Siedlung scheint Geschäfte mit ihr zu haben. Wenn unsere Frauen sie erwischt hätten, würden sie sie nackt vor die Stadttore werfen.";
			link.l1 = "Ach, na gut... "+GetSexPhrase("Es scheint, dass ich dann in eine lange Schlange geraten bin. Nun, wenn noch jemand herumkommt und nach ihr fragt, sag ihnen, sie sollen sich hinter mich in die Schlange stellen.","Ich sehe")+"..., Freund.";
			link.l1.go = "exit";
			pchar.quest.EncGirl_SpeakTavernKeeper.over = "yes";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		
		case "EncGirl_3":
			dialog.text = "Er ist ein häufiger Besucher hier - er kommt normalerweise auf der Suche nach Arbeit vorbei, aber jetzt ist er nicht da. Komm ab und zu zurück - ich werde ihm sagen, dass er hier auf dich warten soll, wenn er auftaucht.";
			link.l1 = "Danke, ich komme später wieder...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "FindingLover";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitTavern.function = "EncGirl_GenerateLover";
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ach, also bist du "+GetSexPhrase("jener Kapitän, der gebracht hat","das Mädel, das gebracht hat")+" mein verlorener Sohn mit einer jungen Braut?";
				link.l1 = "Ja, ich war es, der geholfen hat.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, dort "+GetSexPhrase("er ist es, unser Wohltäter","sie ist es, unsere Wohltäterin")+". Erwarten Sie eine Belohnung, nehme ich an?";
				link.l1 = "Nun, ich komme auch ohne eine Belohnung aus, aber ein Dankeschön wäre nett.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Ich bin Ihnen sehr dankbar, dass Sie meinen Sohn in seiner Not nicht im Stich gelassen und ihm geholfen haben, einen Ausweg aus einer heiklen Situation zu finden. Lassen Sie mich Ihnen danken und nehmen Sie bitte diese bescheidene Summe und ein Geschenk von mir persönlich an.";
			link.l1 = "Danke. Es war mir ein Vergnügen, diesem jungen Paar zu helfen.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Dankeschön? Welches Dankeschön?! Es ist ein halbes Jahr her, dass dieser Dummkopf ohne Arbeit herumlungerte - und schau ihn dir an, er hat genug Zeit für eine Affäre! Als ich in seinem Alter war, hatte ich bereits mein eigenes Geschäft! Pfft! Ein Gouverneur hat eine heiratsfähige Tochter - und dieser Tölpel hat eine Hure ohne Sippe oder Verwandtschaft in mein Haus gebracht und gewagt, um meinen Segen zu bitten!";
			link.l1 = "Ich nehme an, Sie glauben nicht an Liebe auf den ersten Blick?";
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
			dialog.text = "Liebe? Liebe!? Machst du dich über mich lustig oder bist du dumm? Schande über dich, dass du den Jungen in ihren Launen verwöhnst und dich wie ein Kuppler benimmst! Du hast nicht nur ein Mädchen aus ihrem Zuhause genommen, sondern auch das Leben meines Jungen ruiniert. Es wird kein Dank an dich geben. Lebewohl.";
			link.l1 = "Dann auch für dich.";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
				
		case "ShipLetters_4":
			pchar.questTemp.different.GiveShipLetters.speakTavern = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Lass mich mal schauen! Hmm... Aber du bist ja selbst ein Kapitän. Ich denke, du solltest dich mit dem Hafenmeister über das reden.";
				link.l1 = "Danke für Ihren Rat.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Lass mich mal sehen! Oh! Nach dem Namen zu urteilen, gehört dies einem meiner Gönner, einem sehr geachteten Herrn. Ich selbst kann diese Dokumente dem Besitzer übergeben. Wirst du sie mir geben?";
				link.l1 = "Bei näherer Überlegung...";
				link.l1.go = "exit";
				link.l2 = "Nimm sie. Ich bin froh, dass ich dienen konnte.";
				link.l2.go = "ShipLetters_end";				
			}	
		break;
		
		case "ShipLetters_end":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "3");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//zagolski. переделка
		case "work":
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("Ich kümmere mich nicht darum, wem ich diene, da Geld keine Nationalität hat. Aber ich werde Ihnen nicht helfen, da Sie unter der Flagge von "+NationNameGenitive(sti(pchar.nation))+".","Ich bin nur ein einfacher Wirt, aber die Zusammenarbeit mit "+NationNameAblative(sti(pchar.nation))+" scheint mir nicht reizvoll zu sein.");
				link.l1 = RandPhraseSimple("Nun, wie du willst...","Nun, wie du magst...");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("Wir haben hier normalerweise viele Passagiere. Trotzdem glaube ich nicht, dass es auch nur einen Dummkopf unter ihnen gibt, der bereit wäre, auf Ihrem Schiff zu reisen. Ihr schlechter Ruf eilt Ihnen voraus, nur ein Narr würde mit solch einem Schurken in See stechen.","Ich werde ziemlich oft von Händlern angesprochen, die eine Eskorte brauchen. Aber dein schlechter Ruf geht dir voraus und ich werde dich niemandem empfehlen. Ich kümmere mich um meinen eigenen Ruf, weißt du. Niemand stellt einen Wolf ein, um seine Schafe zu bewachen.");
				link.l1 = RandPhraseSimple("Oh, wirklich, du solltest nicht all diesem Gerede glauben...","Ich verstehe. Es ist schwierig, alle zum Schweigen zu bringen.","Die Leute sind heutzutage einfach zu weich...");
				link.l1.go = "exit";
				break;
			}
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
        	{
				dialog.text = "Und wo ist dein Schiff? Oder hast du vor, die Passagiere auf deinem Rücken zu tragen und zu schwimmen?";
				link.l1 = "He, du hast einen Punkt...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Ich könnte einen Job für dich haben, wenn du dich nicht scheust, zu Piratensiedlungen oder zu den Häfen feindlicher Nationen zu kommen. Suchst du etwas Bestimmtes?";
			link.l1 = "Das sollte kein Problem sein. Ich denke, ich könnte Geleitschutz bieten.";
			link.l1.go = "work_1";
			link.l2 = "Haben Sie irgendwelche Passagiere? Ich kann sie überall hinbringen, wo sie wollen, wenn sie dafür bezahlen.";
			link.l2.go = "work_2";
			link.l3 = "Nein, solche Arbeit ist nichts für mich. Danke.";
			link.l3.go = "exit";
		break;

		case "work_1":
				dialog.text = "Man fragt mich normalerweise nicht nach Eskortdiensten. Frag die Händler in der Taverne - vielleicht könnten sie deine Dienste gebrauchen.";
				link.l1 = "Gut, wie du sagst.";
                link.l1.go = "exit";
		break;

		case "work_2":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2 || bBettaTestMode)
    		{					
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
				{
					dialog.text = "Es tut mir leid, aber ich habe niemanden, der bereit ist, mit Ihnen zu reisen.";
					link.l1 = "Ich verstehe.";
					link.l1.go = "exit";
					break;
				}
		         // пассажир
				if (hrand(6) > 1)
				{
					dialog.Text = "Da ist ein Mann, der gerade hereingekommen ist - er hat kürzlich nach einem vorbeifahrenden Schiff gefragt. Du kannst mit ihm reden, wenn du möchtest.";
					link.l1 = RandPhraseSimple("Wer ist er? Vielleicht ist er ein Schurke? Oder, noch schlimmer, ein gesuchter Pirat?","Und wer ist er? Wird es Ärger mit ihm geben?");
					Link.l1.go = "PassangerAreYouSure";
				}
				else
				{
					dialog.text = "Nein, heute hat niemand danach gefragt. Vielleicht ein anderer Tag.";
					link.l1 = RandPhraseSimple("Nun, wenn es nicht da ist, ist es nicht...","Nur mein Glück... Na gut, dann bis später.");
					link.l1.go = "exit";
				}
            }
    		else
    		{
				dialog.text = "Heute ist niemand da. Komm in ein paar Tagen wieder.";
				link.l1 = "Gut, wie du sagst.";
                link.l1.go = "exit";
    		}
        break;

        case "ConvoyAreYouSure":
		    dialog.text = LinkRandPhrase("Wer könnte das wissen? Du hast gefragt - ich habe geantwortet.","Nun, das ist für dich zu lösen. Ich würde für niemanden dort bürgen.","Alle möglichen Leute kommen hierher. Dies ist eine Taverne, Käpt'n, nicht das Herrenhaus des Gouverneurs.");
			Link.l1 = "Danke, wir werden dann handeln.";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

        case "PassangerAreYouSure":
		    dialog.text = LinkRandPhrase("Wer könnte das wissen? Du hast gefragt - ich habe geantwortet.","Nun, das ist für dich zu lösen. Ich würde für niemanden dort bürgen.","Alle möglichen Leute kommen hierher. Das ist eine Taverne, Käpt'n, kein Gouverneursanwesen.");
			Link.l1 = "Ich verstehe. Lassen wir herausfinden, wer dieser Mann ist...";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

		 case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Helen_room":
			dialog.text = "Natürlich, Helen. Wie lange bleibst du? Und was, hast du dich mit der alten Gladys gestritten?";
			if(!isDay())
			{
				link.l1 = "Nur um bis zum Morgen zu schlafen. Wenn ich jetzt nach Hause gehe, werde ich sie sicherlich wecken.";
				link.l1.go = "Helen_room_day";
			}
			else
			{
				link.l1 = "Nein, nein, ich muss nur nachts in See stechen, und ich möchte sie nicht wecken.";
				link.l1.go = "Helen_room_night";
				link.l2 = "Ich möchte gut und lange schlafen und mir Zeit lassen, aufzustehen. Ich nehme ein Zimmer für einen Tag.";
				link.l2.go = "Helen_room_day_next";
			}
		break;

		case "room":
   			if (chrDisableReloadToLocation || CheckAttribute(pchar, "GenQuest.TavernClose")) //кто-то должен подойти к ГГ.
			{
				dialog.text = "Das Zimmer ist besetzt, "+GetAddress_Form(NPChar)+", da kann ich nichts für dich tun.";
				link.l1 = "Nun, das ist schade...";
				link.l1.go = "exit";
				break;
			}
			// суп из черепахи
			if (CheckAttribute(pchar, "questTemp.Terrapin.Room_close") && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "Herr Henri Thibaut mietet derzeit das Zimmer, und er hat einen Monat im Voraus bezahlt, also kann ich nichts für Sie tun, Kapitän.";
				link.l1 = "Nun, das ist schade...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "cave" && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "Das Zimmer ist besetzt, "+GetAddress_Form(NPChar)+", es gibt nichts, was ich für dich tun kann.";
				link.l1 = "Nun, das ist eine Schande...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore" && npchar.location == "Baster_tavern") // 070712
			{
				dialog.text = "Das Zimmer ist besetzt, "+GetAddress_Form(NPChar)+", da gibt es nichts, was ich für dich tun könnte.";
				link.l1 = "Nun, das ist eine Schande...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
			{
				Dialog.text = "Leider, nein, Kapitän. Alle Zimmer sind von Blackwood und seinen Leuten belegt.";
				if (CheckAttribute(pchar, "questTemp.LadyBeth_TavernRoomDialog"))
				{
					link.l1 = "Ach, schade!";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Alle Zimmer? Gibt es hier mehr als ein Zimmer?";
					link.l1.go = "LadyBeth_Room";
				}
				break;
			}
			//-->> квест официантки
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = "Möchten Sie ein Zimmer mieten? Kein Problem. 100 Achtel und es gehört Ihnen.";
				if (sti(pchar.money) >= 100)
				{
					link.l1 = "Hier ist dein Geld.";
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = "Hmm... Ich denke, ich komme später wieder...";
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//квест официантки
			{
				dialog.text = "Das Zimmer gehört ganz Ihnen. Kommen Sie rein und entspannen Sie sich.";
				link.l1 = "Danke, Kumpel.";
				link.l1.go = "exit";
				break;
			}
			//<<-- квест официантки
			// --> квест "A damsel in the jungle"
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && npchar.city == pchar.GenQuest.EncGirl.city)
			{
				if(pchar.GenQuest.EncGirl == "EncGirl_ToTavern")
				{
					dialog.text = "Sie möchten ein Zimmer mieten? Kein Problem. 100 Achtelstücke und es gehört Ihnen.";
					if (sti(pchar.money) >= 100)
					{
						link.l1 = "Hier ist dein Geld.";
						link.l1.go = "exit";
						AddMoneyToCharacter(pchar, -100);
						LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
						pchar.GenQuest.EncGirl = "EncGirl_toRoomUp";
					}
					else
					{
						link.l1 = "Hmm... Ich denke, ich komme später wieder...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.GenQuest.EncGirl == "EncGirl_toRoomUp")//квест  по спасению тетки в пампасах
				{
					dialog.text = "Der Raum gehört ganz Ihnen. Komm rein und entspann dich.";
					link.l1 = "Danke, Kumpel.";
					link.l1.go = "exit";
					break;
				}
			}
			// <-- квест "A damsel in the jungle"

			// belamour постоялец -->
			if (CheckAttribute(pchar, "GenQuest.Unwantedpostor") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && abs(50-sti(pchar.reputation.nobility)) > 20)
			{
				if(pchar.GenQuest.Unwantedpostor == "start")
				{
					SetFunctionTimerCondition("Unwantedpostor_OneDay", 0, 0, 1, false);
					pchar.GenQuest.Unwantedpostor = "timer";
				}
				dialog.text = "Entschuldigung, Kapitän, leider ist kein Platz verfügbar. Der Gast will nicht gehen. Und hat mir immer noch nicht bezahlt...";
				link.l1 = "Sieht so aus, als müssten wir die Nacht im Gemeinschaftsraum verbringen...";
				link.l1.go = "Unwantedpostor_hall_day_wait";
				link.l2 = "Entschuldigung. Lass uns über etwas anderes sprechen.";
				link.l2.go = "int_quests";
				if(pchar.GenQuest.Unwantedpostor != "Lose")
				{
					link.l3 = "Also ruft die Wachen. Was für ein Gast ist das: er zahlt kein Geld, er will nicht ausziehen...";
					link.l3.go = "Unwantedpostor";
				}
				break;
			}
			//<-- постоялец

			dialog.text = "Wie lange planen Sie hier zu bleiben?";
			if(!isDay())
			{
				link.l1 = "Bis zum Morgen.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Bis zur Nacht.";
				link.l1.go = "room_night";
				link.l2 = "Bis zum nächsten Morgen.";
				link.l2.go = "room_day_next";
			}
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				pchar.questTemp.MarySexBlock = true;
				SetTimerFunction("Mary_DeleteSexBlock", 0, 0, 1);
			}
		break;

		case "room_day":
			dialog.text = "Das wird Sie 5 Achtel kosten.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Abgemacht. Hier, bitte.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase("Bei diesem Preis? Vermietest du königliche Gemächer? Ich würde lieber kostenlos im Gemeinschaftsraum bleiben.","Ach, es scheint, dass der Luxus, in einem Bett zu schlafen, über meine derzeitigen Mittel hinausgeht. Ich werde wohl im Gemeinschaftsraum auf einer Bank schlafen müssen.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Nicht jetzt. Lass uns das Thema wechseln.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_day_next":
			dialog.text = "Das kostet dich 10 Achtelstücke.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Abgemacht. Hier, bitte.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase("Zu diesem Preis? Vermietest du königliche Kammern? Ich würde lieber kostenlos im Gemeinschaftsraum übernachten.","Ach, der Luxus, auf einem Bett zu schlafen, liegt anscheinend über meinen derzeitigen Möglichkeiten. Ich werde wohl im Gemeinschaftsraum auf einer Bank schlafen müssen.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Nicht jetzt. Lass uns das Thema wechseln.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night":
			dialog.text = "Das wird Sie 5 Achtelstücke kosten.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Abgemacht. Hier, nimm das.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase("Zu diesem Preis? Vermietest du königliche Gemächer? Ich würde lieber kostenlos im Gemeinschaftsraum übernachten.","Ach, der Luxus auf einem Bett zu schlafen, liegt anscheinend über meinen derzeitigen Möglichkeiten. Ich denke, ich werde wohl im Gemeinschaftsraum auf einer Bank schlafen müssen.");
			link.l2.go = "hall_night_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Nicht jetzt. Wechseln wir das Thema.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night_wait":
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (hRand(3) == 1)
            {
                Dialog.text = "Verschwinde zum Teufel, du Schurke! Das Gemeinschaftszimmer mag zwar kostenlos sein, aber wir haben Erwartungen an anständiges Verhalten!";
				link.l1 = "In Ordnung, in Ordnung, ich gehe.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "Verschwinde zum Teufel, du Schurke! Der Gemeinschaftsraum mag frei sein, aber wir erwarten anständiges Benehmen!";
				link.l1 = "In Ordnung, in Ordnung, ich gehe schon.";
				link.l1.go = "exit";
            }
            else
            {
				// belamour прерывание ночной приключенец -->
				if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
					SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
				}
				// <-- прерывание ночного приключенца
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = "Hör sofort auf mit diesem skandalösen Verhalten in meiner Taverne, sonst rufe ich die Wachen!";
			link.l1 = "In Ordnung, in Ordnung, ich gehe jetzt.";
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		//******************* ноды квеста священника. поиск грабителей (квест № 2)**********************
		case "Tavern_GenQuest_Church_2_1":
			dialog.text = "Ich weiß nicht viel darüber... Du solltest besser die Stammgäste fragen.";
			link.l1 = "Ich verstehe, danke.";
			link.l1.go = "exit";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		break;
			
		//******************* ноды квеста священника. вернуть рукописи (квест № 1)**********************
		case "Tavern_ChurchGenQuest1_Node_1":
			dialog.text = "Wir bieten keine Dienstleistungen auf Kredit an, "+GetSexPhrase("Herr","Fräulein")+".";
			link.l1 = "Ich zahle in guter Münze. Akzeptierst du kein Gold oder Silber mehr?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_2":
			dialog.text = "Es tut mir leid, "+GetSexPhrase("Herr","Fräulein")+" Kapitän, aber Ihr Freund hatte eine Schuld, und ich dachte...";
			link.l1 = "Denk weniger und arbeite schneller, Kumpel. Nun, wie viel schuldet dir mein tapferer Freund?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_3":
			iTemp = (rand(3)+1)*100;
			PChar.GenQuest.ChurchQuest_1.MoneyToBarmen = iTemp;
			if(rand(1) == 0) // "If he's a simple one and pays right away"
			{
				dialog.text = FindRussianMoneyString(iTemp)+", verdammt"+GetSexPhrase("ter","s")+" Kapitän, und er verpfändete auch einige Kirchenbücher - das ist alles, was er bei sich hatte, was einen Wert hatte.";
				if(sti(PChar.money) >= iTemp)
				{
					link.l1 = "Hier sind deine Münzen. Übergib die Handschriften. Und sei vorsichtig damit - das ist keine Sammlung von anzüglichen Holzschnitten, sondern Heilige Schrift!";
					link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
				}
				else
				{
					link.l1 = "Warte ein bisschen... Ich komme gleich mit dem Geld zurück";
					link.l1.go = "exit";
					PChar.GenQuest.ChurchQuest_1.NoMoneyToBarmen = true;
				}
			}
			else // "If he's not a simple one"
			{
				dialog.text = FindRussianMoneyString(iTemp)+", fehl"+GetSexPhrase("ter","s")+" Kapitän.";
				link.l1 = "Ich werde seine Schulden begleichen und alles nehmen, was er zur Sicherung hinterlassen hat.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2";
			}
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_1":
			DialogExit();
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "8");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", GetFullName(CharacterFromID("ChurchGenQuest1_Cap")));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2":
			dialog.text = "Nein, Miss"+GetSexPhrase("ter","s")+", das wird so nicht funktionieren.";
			link.l1 = "Was meinst du mit 'das wird so nicht funktionieren'? Eine Kapitänschuld ist bezahlt - er ist gut. Du hast dein Geld zurück - du bist gut. Ich nehme sein Versprechen - ich bin gut. Alles ist gut - also warum 'das wird so nicht funktionieren'?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_1";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_1":
			dialog.text = "Weil, Fräulein"+GetSexPhrase("ter","s")+"Kapitän, ich brauche das Geld nicht. Weil ich diesen Kapitän nur allzu gut kenne, habe ich also nie wirklich erwartet, dass er zurückzahlt und diese Manuskripte von mir nimmt.";
			link.l1 = "Was meinst du damit - du brauchst kein Geld? Also hast du vor, diese Bücher von Anfang an zu behalten? Aber warum, um Himmels willen?!";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_2":
			dialog.text = "Im Namen Gottes - genau, deshalb, Miss"+GetSexPhrase("ter","s")+". Mein kleiner Junge war sehr krank, und ich und meine Frau haben ein Gelübde abgelegt, eine Spende an die Kirche zu machen, wenn unser gesegneter Herr das Kind vom Fieber heilte. Die Barmherzigkeit unseres Herrn ist ohne Ende, mein Junge ist lebendig und gesund, und jetzt müssen wir unser Gelübde halten. Und genau zur rechten Zeit, Kapitän "+PChar.GenQuest.ChurchQuest_1.CapFullName+" taucht auf und versetzt diese Kirchenbücher. Ich konnte solche Obszönität nicht zulassen - für Getränke mit dem Wort zu zahlen - und deshalb beschloss ich, diese Bücher dem Pfarrer unserer Gemeinde zu übergeben.";
			link.l1 = "Nun, sicherlich ist dies eine gute Tat, aber Sie sollten auch wissen, dass diese Bücher eigentlich einem anderen Priester gehören - tatsächlich nicht nur einem Priester, sondern einem Bischof und meinem geistlichen Hirten. Und er könnte wütend werden und sogar diejenigen verfluchen, die es wagen würden, gestohlenes Kircheneigentum zu spenden. Ich möchte sie von Ihnen kaufen und sie sicher nach Hause bringen. Sie können das Geld Ihrer Gemeinde spenden, ich bin sicher, Gott wird es trotzdem zu schätzen wissen.";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_3":
			dialog.text = "Fehl"+GetSexPhrase("ter","s")+"... Mis"+GetSexPhrase("ter","s")+" Kapitän... Natürlich, ich hatte keine Ahnung! Ich werde sie zurückgeben und verlange kein Geld dafür. Sie setzen nur ein gutes Wort für uns beim Bischof ein - vielleicht könnte er uns segnen und uns von unserem Gelübde entbinden...";
			link.l1 = "Natürlich wird Ihr Gelübde als gehalten betrachtet! Schließlich haben Sie Ihren Profit aufgegeben, um die Bücher ihrem rechtmäßigen Besitzer zurückzugeben. Die bestimmte Kirche spielt keine Rolle, denn es gibt nur einen Gott und eine Heilige Katholische Apostolische Kirche, nicht wahr? Gut, geben Sie sie mir und viel Glück für Sie...";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_4";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_4":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "9");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Tavern":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Noch nie davon gehört... Was ist das eigentlich? Ich habe in meiner ganzen Zeit noch nie von so etwas gehört.";
			link.l1 = "Nun, es ist ein Schiffbauerwerkzeug, "+pchar.GenQuest.Device.Shipyarder.Describe+". Hat dir jemand so etwas angeboten?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 6)
			{
				dialog.text = "Hmm... Ja, tatsächlich hat mir so ein merkwürdiger Kerl das Ding gebracht. Er hat mir allerdings nicht gesagt, was es war - er wollte es nur gegen Schnaps eintauschen. Natürlich habe ich abgelehnt - ich hatte keine Verwendung für diesen Tand.";
				link.l1 = "Und wie sah er aus und wo ging er hin? Ich brauche dieses Instrument dringend.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Nein, nichts dergleichen. Entschuldigung, ich kann Ihnen nicht helfen. Frag herum.";
				link.l1 = "Ich verstehe. Nun, es ist Zeit, herumzufragen!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		//Jason --> генератор Место под солнцем
		case "Sunplace_Tavern":
			if (makeint(environment.time) > 12.0 && makeint(environment.time) < 17.0)//в магазине
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Er war kürzlich dort und müsste jetzt zu seinem Kumpel - dem Ladenbesitzer - gekommen sein. Versuche, ihn im Laden zu suchen - sicher muss er dort sein.";
				link.l1 = "Danke! Du hast mir sehr geholfen!";
				link.l1.go = "Sunplace_Tavern_1";
			}
			else//ушел на рыбалку
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Heute früh am Morgen ist er auf seiner Logger für eine Seereise ausgelaufen. Ich wette, dass er jetzt am Bug steht und die Aussicht bewundert. Wenn du ihn brauchst, kannst du versuchen, ihn auf See zu finden oder warten, bis er in ein paar Tagen zurückkommt...";
				link.l1 = "Danke! Ich denke, ich werde nicht warten - es wird einfacher sein, ihn auf See zu finden. Viel Glück!";
				link.l1.go = "Sunplace_Tavern_2";
			}
		break;
		
		case "Sunplace_Tavern_1"://магазин
			pchar.quest.Sunplace_Store.win_condition.l1 = "location";
			pchar.quest.Sunplace_Store.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.CityT + "_store";
			pchar.quest.Sunplace_Store.function = "Sunplace_CreateTrader";
			AddQuestRecord("Sunplace", "6");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		
		case "Sunplace_Tavern_2"://рыбалка
			pchar.GenQuest.Sunplace.Trader.IslandID = GetCharacterCurrentIslandId(npchar);
			pchar.GenQuest.Sunplace.Trader.EnemyNation = npchar.nation;
			pchar.quest.Sunplace_Sea.win_condition.l1 = "location";
			pchar.quest.Sunplace_Sea.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.IslandID;
			pchar.quest.Sunplace_Sea.function = "Sunplace_CreateTraderLugger";
			AddQuestRecord("Sunplace", "7");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		// <-- генератор Место под солнцем	
		
		// Jason --> Голландский гамбит
		case "HWICHollJacob_Tavern":
			dialog.text = "Psssst... Warum schreist du? Er hat schon eine Weile auf dich gewartet. Er hat bereits eine volle Quartflasche Rum getrunken. Geh nach oben in das Zimmer, du wirst ihn dort finden.";
			link.l1 = "Ach, ich verstehe. Hoffentlich ist er noch wach.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern", "reload2_back", false);
			pchar.questTemp.HWIC.Holl = "JacobInRoom";
			AddDialogExitQuestFunction("Create_JacobVanBerg");
			DelLandQuestMark(npchar);
		break;
		
		case "HWICSelfFernando_Tavern":
			if (NPChar.location == pchar.questTemp.HWIC.Self.SpainCity +"_tavern")
			{
				//DelMapTonzagAllQM();
				dialog.text = "Ja, ich kenne diesen Herrn. Er sollte irgendwo in der Stadt sein - ich habe ihn erst kürzlich an meinem Fenster vorbeigehen sehen.";
				link.l1 = "Danke! Ich werde nach ihm suchen!";
				link.l1.go = "Fernando_Land";
				/* if (makeint(environment.time) > 10.0 && makeint(environment.time) < 18.0)//на улице
				{
					dialog.text = "Ja, ich kenne diesen Herrn. Er sollte irgendwo in der Stadt sein - ich habe ihn erst kürzlich an meinem Fenster vorbeigehen sehen.";
					link.l1 = "Danke! Ich werde nach ihm suchen!";
					link.l1.go = "Fernando_Land";
				}
				else //в море
				{
					dialog.text = "Ja, er besucht gerade unsere Stadt. Im Moment ist er nicht hier - er ist mit seiner Brigantine gesegelt. Er ist wahrscheinlich nicht weit von hier, innerhalb der Gewässer unserer Insel.";
					link.l1 = "Danke Kumpel! Du hast mir sehr geholfen!";
					link.l1.go = "Fernando_Sea";
				} */
				pchar.questTemp.HWIC.Self = "KillFernando";
			}
			else
			{
				dialog.text = "Fernando Rodriguez? Noch nie von ihm gehört. Nein, ich weiß nichts über diesen Mann.";
				link.l1 = "Ich sehe... Nun, die Suche geht weiter....";
				link.l1.go = "exit";
			}
			npchar.quest.HWICTalked = "true";
		break;
		
		case "Fernando_Land":
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.SpainCity +"_town";
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnLand";
			AddQuestRecord("Holl_Gambit", "3-2");
			DialogExit();
		break;
		
		case "Fernando_Sea":
			pchar.questTemp.HWIC.Self.FernandoIslandID = GetCharacterCurrentIslandId(npchar);
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.FernandoIslandID;
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnSea";
			AddQuestRecord("Holl_Gambit", "3-3");
			DialogExit();
		break;
		//<-- Голландский гамбит
		
		//Jason --> гонки на гидропланах
		case "Race_Advantage":
			dialog.text = "Ja, natürlich. Herzlichen Glückwunsch Kapitän. Ich bin bereits über Ihren Sieg informiert. Hier ist Ihr Geld.";
			link.l1 = "Danke, "+npchar.name+".";
			link.l1.go = "Race_Advantage_1";
		break;
		
		case "Race_Advantage_1":
			DialogExit();
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Racing.Go.Money)*2);
			AddQuestRecord("Racing", "4");
			AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Gen"));
			CloseQuestHeader("Racing");
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
		break;
		//<-- гонки на гидропланах
		
		//Jason --> захват пассажиров
		case "Marginpassenger":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.lose"))
			{
				dialog.text = "Äh, Herr, "+pchar.GenQuest.Marginpassenger.q2Name+" starb vor etwa "+LinkRandPhrase("ein Monat","drei Wochen","zwei Monate")+" vor. "+LinkRandPhrase("Plötzlich dem Fieber erlegen","Er wurde am Stadttor erstochen - Banditen oder diese rot-häutigen Wilden","Er wurde in einem Duell erschossen")+". Gott hab seiner Seele Erbarmen...";
				link.l1 = "Verdammt!.. Und was soll ich mit seinem... Na ja, egal. Danke für die Information. Wir sehen uns, "+npchar.name+".";
				link.l1.go = "Marginpassenger_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.Marginpassenger.q2Name+"? Ja, er sollte irgendwo in der Stadt sein. Such ihn auf den Straßen. Aber denk daran, dass er jeden Tag bis Mittag im Gouverneursbüro ist und sich nach neun Uhr abends in seinem Haus einschließt.";
				link.l1 = "Danke! Ich werde nach ihm suchen...";
				link.l1.go = "Marginpassenger_2";
			}
		break;
		
		case "Marginpassenger_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "7");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Puerto Principe, to the Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Le Francois, to Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "Marginpassenger_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "8");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			pchar.GenQuest.Marginpassenger = "street";
		break;
		//<-- захват пассажиров
		
		//Jason --> поиск дезертира
		case "FindFugitiveTav":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 0)
			{
				dialog.text = NPCStringReactionRepeat("Es scheint, dass dein Skipper die Wahrheit gesagt hat. "+pchar.GenQuest.FindFugitive.Name+" ist tatsächlich kürzlich in unserer Siedlung angekommen. Suchen Sie ihn tagsüber auf den Straßen - er vertreibt normalerweise seine Zeit.","Du hast mich schon einmal nach diesem Mann gefragt, und ich habe dir alles erzählt, was ich wusste!","Bist du ein Narr oder wirklich ein Idiot?! Du fragst schon zum dritten Mal das Gleiche!","Nur zu denken, wie so ein Idiot zum Kapitän werden konnte...","Block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Danke, Freund, du hast mir sehr geholfen!","Ja, ja, gut.","Wow, Wow, beruhige dich. Ich habe es einfach vergessen.","Nun, er hat es getan, wie du sehen kannst...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveTav_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("Nein, Kumpel, diesen Namen habe ich noch nie gehört. Frag herum - vielleicht kennt ihn jemand...","Du hast mich schon nach diesem Mann gefragt, und ich habe dir gesagt: Ich weiß es nicht!","Bist du bei Sinnen oder bist du wirklich ein Idiot?! Du fragst schon zum dritten Mal dasselbe!","Nur zu denken, wie so ein Idiot Kapitän werden konnte...","Block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Ich verstehe. Nun, danke trotzdem.","Ja, ja, gut.","Woah, Woah, reg dich nicht so auf. Ich habe es nur vergessen.","Nun, wie du sehen kannst, hat er es getan...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveTav_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-1");
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_city";
			LAi_SetLoginTime(sld, 11.0, 18.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_town", "goto", "goto"+(rand(9)+1));
		break;
		//<-- поиск дезертира
		
		//--> Бремя гасконца
		case "Sharlie_crew":
			dialog.text = "Leider kann ich Ihnen im Moment nicht helfen - keiner von den Leuten, die ich kenne, würde unter Ihnen dienen. Aber ich kann Ihnen einen Rat geben - sprechen Sie mit dem Seemann, der gerade den Tisch hinter Ihnen eingenommen hat. Er und seine Kumpels haben gerade ein Handelsschiff verlassen. Vielleicht stimmen sie zu, mit Ihnen zu kommen.";
			link.l1 = "In Ordnung, das werde ich tun! Vielen Dank!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "sailor";
			//усадим матроса Алонсо
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSailor" , "Alonso", "man", "man", 10, FRANCE, -1, true, "quest"));
			sld.name 	= StringFromKey("HollandGambit_23");
			sld.lastname = "";
			FantomMakeCoolFighter(sld, 10, 20, 20, "blade_05", "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Sharlie_sailor";
			sld.greeting = "town_sailor";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator("FortFrance_tavern", "sit7");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");
			AddQuestRecord("Sharlie", "6-1"); // mitrokosta
		break;
		
		case "Sharlie_skiper":
			dialog.text = "Ich kann dir nichts Konkretes sagen, Freund. Im Moment kommen keine Navigator zu meinem Ort. Versuche im Hafen herumzufragen - vielleicht wissen die Leute mehr.";
			link.l1 = "Ich verstehe. Also gut, ich werde mit den Leuten sprechen.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "findskiper";
			//сгенерим наводчика
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSkiperTalker", "citiz_"+(rand(19)+21), "man", "man", 10, FRANCE, -1, true, "marginal"));
			FantomMakeCoolFighter(sld, 10, 20, 20, RandPhraseSimple("blade_04","blade_06"), "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "skipertalker";
			sld.greeting = "marginal";
			LAi_SetWarriorType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "patrol", "patrol"+(rand(13)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Бремя гасконца
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_tortuga":
			sld = characterFromId("Tortuga_waitress");
            dialog.text = "Sofort, Monsieur!.. Der allerbeste französische Wein! "+sld.name+"! Mach das beste Gästezimmer fertig! Das werden 1000 Pesos sein, Monsieur.";
			link.l1 = "Hier.";
			link.l1.go = "mtraxx_tortuga_1";
		break;
		
		case "mtraxx_tortuga_1":
			AddMoneyToCharacter(pchar, -1000);
            DialogExit();
			pchar.questTemp.Mtraxx.Retribution = "room";
			pchar.quest.mtraxx_retribution_room.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.location = "Tortuga_tavern";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.mtraxx_retribution_room.function = "Mtraxx_RetributionToRoom";
		break;
		// belamour постоялец -->
		case "Unwantedpostor_hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "Raus, Schurke! Du nimmst wertvollen Platz für zahlende Kunden ein!";
				link.l1 = "Gut, gut... Ich gehe.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "Unwantedpostor":
				dialog.text = "Ja - und alle meine Kunden erschrecken mit der Tatsache, dass meine Wachen Leute aus der Taverne schleifen? Und einige meiner Kunden mögen es nicht, bei Soldaten zu sein. Macht sie nervös, verstehst du? Ich will meinen Ruf nicht ruinieren...";
				link.l1 = "Hmm, was wäre, wenn ich dein Problem löse?";
				link.l1.go = "Unwantedpostor_1";
		break;
		
		case "Unwantedpostor_1":
				dialog.text = "Haben Sie sich entschieden? Er ist bewaffnet, er ist eine Art professioneller Söldner...";
				link.l1 = "Hmm, du hast recht, ich habe keine Lust, mich mit einem bewaffneten Söldner zu streiten...";
				link.l1.go = "Exit";
				link.l2 = "Nun, ich bin auch keine eingemauerte Nonne... Und ich möchte immer noch ein Zimmer mieten.";
				link.l2.go = "Unwantedpostor_2";
		break;
		
		case "Unwantedpostor_2":
				dialog.text = "Nun, wenn du ihn, ähem... überzeugen kannst auszuziehen, dann gehört das Zimmer bis zum Morgen dir. Natürlich kostenlos.";
				link.l1 = "Weißt du, ich habe meine Meinung geändert. Ich habe keine Lust, irgendjemanden zu überzeugen.";
				link.l1.go = "Exit";
				link.l2 = "Sie werden das sehen wollen. Ihr unerwünschter Gast wird gleich aus Ihrer Taverne fliegen wie eine riesige Möwe.";
				link.l2.go = "Unwantedpostor_kikcoff";
		break;
		
		case "Unwantedpostor_kikcoff":
				DialogExit();
				chrDisableReloadToLocation = true; //закрыть локацию
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location+"_upstairs")], true); //запретить драться
				iTemp = sti(pchar.rank) + rand(5);
				sld = GetCharacter(NPC_GenerateCharacter("Berglar_Unwantedpostor", "citiz_5"+(rand(3)+1), "man", "man", iTemp, PIRATE, -1, true, "quest")); // "mercen_"+(rand(14)+14)
				FantomMakeCoolFighter(sld, iTemp, 50 + rand(30), 50 + rand(30), "topor_04", "", "bullet", 50);
				sld.dialog.filename = "GenQuests_Dialog.c";
				sld.dialog.currentnode = "Unwantedpostor_room";	
				sld.greeting = "Enc_Raiders"; 
				if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
				{
					DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
					ChangeCharacterAddressGroup(sld, pchar.location+"_upstairs", "quest", "quest3");
				} 
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		// <-- belamour постоялец
		
		case "Helen_room_night":
			dialog.text = "Ich verstehe. Das werden fünf Silber sein.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Natürlich, hier bitte.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = "Eigentlich, weißt du was... Vielleicht ein anderes Mal. Ich werde den Rest des Tages auf den Beinen verbringen.";
			link.l2.go = "Helen_night_exit";
		break;
		
		case "Helen_room_day":
			dialog.text = "Weise Entscheidung. Das macht fünf Silber, und gute Nacht für Sie.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Hier, bitte und danke - gute Nacht.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = "Bei näherer Überlegung, habe ich keine Lust zu schlafen. Ich werde durch die Stadt streifen, etwas Nachtluft schnappen.";
			link.l2.go = "Helen_day_exit";
		break;
		
		case "Helen_room_day_next":
			dialog.text = "Natürlich, Helen. Das werden zehn Pesos sein.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Natürlich, hier bitte.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = "Eigentlich ... könnte ich mit einem ganzen Tag etwas Nützliches anfangen. Vielleicht ein andermal.";
			link.l2.go = "Helen_Next_day_exit";
		break;
		
		case "Helen_night_exit":
			dialog.text = "Wie du wünschst, Helen.";
			link.l1 = "Mhm.";
			link.l1.go = "exit";
		break;
		
		case "Helen_day_exit":
			dialog.text = "Vielleicht fühlen Sie sich sogar schläfrig nach einem guten Spaziergang.";
			link.l1 = "Ha-ha, vielleicht.";
			link.l1.go = "exit";
		break;
		
		case "Helen_next_day_exit":
			dialog.text = "Wie es Euch beliebt.";
			link.l1 = "Nun, bis zum nächsten Mal.";
			link.l1.go = "exit";
		break;
		
		case "Helen_rumours_tavern":
			dialog.text = "Natürlich, Helen, ich bin ganz Ohr.";
			link.l1 = "Welche sind die neuesten Nachrichten oder interessante Gerüchte in der Stadt?";
			link.l1.go = "rumours_tavern";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Room":
			dialog.text = "Er zahlt das Dreifache des normalen Preises, also... Sie verstehen schon. Und ich würde nicht empfehlen, ihm etwas zu verweigern - er hat eine schwierige Art. Besonders in letzter Zeit.";
			link.l1 = "Was ist mit ihm los?";
			link.l1.go = "LadyBeth_Room_2";
		break;
		
		case "LadyBeth_Room_2":
			dialog.text = "Besessenheit, das ist es. Anfangs war er ein großzügiger, netter Kerl. Seine Matrosen warfen in den Tavernen mit Geld um sich, kauften den Mädchen Geschenke. Ein echtes Fest begann, wenn die 'Lady Beth' im Hafen anlegte. Und jetzt? Jetzt kaufen sie nur noch Vorräte und heuern Leute an, wahllos. Als ob sie keine Seeleute, sondern einfach nur Arbeitskräfte brauchen. Aber Sie können selbst mit ihm reden.";
			link.l1 = "Vielleicht schaue ich mal vorbei. Danke.";
			link.l1.go = "exit";
			pchar.questTemp.LadyBeth_TavernRoomDialog = true;
		break;
		// Леди Бет <--
	}
}

string findTraderCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}
