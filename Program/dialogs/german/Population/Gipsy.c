//Jason общий диалог цыганок
// ugeen <-- добавил продажу мышьяка из под полы
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int poison_price;

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
			dialog.text = "Ach hallo, Liebling. Was wünschst du dir?";
			link.l1 = "Nichts, nehme ich an.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("Ich habe eine Frage an dich.","Ich brauche Informationen.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Liebling, würdest du so freundlich sein, etwas Gold zu teilen? Ich werde dir deine Zukunft erzählen.","He, Matrose, beeil dich nicht so! Willst du die Zukunft wissen?","Gib mir etwas Tabak und ein paar Silbermünzen, tapferer junger Mann. Und ich werde einen Blick auf deine Zukunft werfen. (zwinkern) Möchtest du etwas von der geheimen Zigeunermagie hören?");
				link.l1 = "Entschuldigung, aber ich muss gehen.";
				link.l1.go = "exit";
				// --> мангароса
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Hör zu, Tüftlerin, ich weiß, dass dein Volk Experten für Tränke und Gifte ist. Mir wurde gesagt, dass du dich für diese Pflanze interessieren könntest. Schau mal. Was denkst du?";
					link.l5.go = "mangarosa";
				}
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy_trade" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Hallo, Dunkelaugen, ich habe etwas für dich... Das ist Mangarosa. Möchtest du etwas kaufen??";
					link.l5.go = "mangarosa_trade1";
				}
				// <-- мангароса
				link.l2 = "Kannst du mir das Schicksal vorhersagen?";
				link.l2.go = "guess";
				link.l3 = RandPhraseSimple("Ich habe eine Frage an dich.","Ich brauche Informationen.");
				link.l3.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
			}
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_Start") && !CheckAttribute(pchar, "questTemp.DWH_gipsy") && npchar.city == "SentJons")
			{
				link.l6 = "Ich suche die Zigeunerin, die Kranke heilt. Bist du das??";
				link.l6.go = "dwh_gypsy_1";
			}
			// <-- Тёмные воды исцеления
			if (!CheckAttribute(npchar, "quest.poison_price") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && rand(2) == 0)
			{
				link.l4 = "Hallo, dunkeläugiger, hast du irgendwelche Rattengifte? Sie sind eine verdammt lästige Plage auf meinem Schiff.";
				link.l4.go = "get_poison_1";
			}
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------------гадание-------------------------------------------------
		case "guess":
			dialog.text = "Natürlich, hübscher Mann. Gib mir ein paar Münzen und zeig mir deine rechte Hand. Ich werde dir von deiner Zukunft erzählen und dir helfen, Unheil zu vermeiden. Ich betrüge nie! Geld-zurück-Garantie!";
			link.l1 = "Ich habe das Gefühl, dass dies der Teil ist, in dem dein Kamerad meine Tasche ausraubt...Ich habe meine Meinung geändert. Ich bin nicht in der Stimmung.";
			link.l1.go = "exit";
			link.l2 = "Wie viel Geld willst du?";
			link.l2.go = "guess_1";
		break;
		
		case "guess_1":
			dialog.text = "Ach Liebchen, so viel wie deine Geldbörse erlaubt und dein Herz begehrt. Je mehr Dublonen, desto weiter in die Zukunft kann ich sehen!";
			link.l1 = "100 Pesos";
			link.l1.go = "guess_rate_1";
			link.l2 = "500 Pesos";
			link.l2.go = "guess_rate_2";
			link.l3 = "1000 Pesos";
			link.l3.go = "guess_rate_3";
			link.l4 = "5000 Pesos";
			link.l4.go = "guess_rate_4";
		break;
		
		sTemp = GuessText();
		case "guess_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Ach, danke dir für deine Wohltätigkeit, mein hübscher junger Falke! Nun hör zu:  "+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! Das ist sehr interessant. Ich werde das in Betracht ziehen...","Wirklich? Ich werde das in Betracht ziehen...","Ach wirklich? Meinst du das ernst? Ich werde mich daran erinnern...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Das hässlichste und unvermeidlichste Unglück wartet auf dich. Verfluche den Spötter! Lass dunkle Wolken über dir zusammenziehen und die Strafe dich finden!";
				link.l1 = "Ha-ha! Hast du wirklich gedacht, ich würde dir Geld geben, du Zigeunerhexe? Geh mir aus dem Weg! Ich hoffe, die Inquisition nimmt dich!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_2"://немного в везение или скрытность
			if (sti(pchar.money) >= 500)
			{
				AddMoneyToCharacter(pchar, -500);
				dialog.text = "Ach, danke dir, mein hübscher junger Falke! Nun hör zu:"+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! Das ist sehr interessant. Ich werde das in Betracht ziehen...","Wirklich? Das werde ich in Betracht ziehen...","Oh, wirklich? Meinst du das ernst? Nun, das werde ich mir merken...","He, ich fühle mich schon besser!");
				link.l1.go = "exit";
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 30+rand(10));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 30+rand(10));//скрытность
			}
			else
			{
				dialog.text = "Das hässlichste und unvermeidliche Unglück wartet auf dich. Verfluche den Spötter! Lass dunkle Wolken sich über dir zusammenziehen und lass die Strafe dich finden!";
				link.l1 = "Ha-ha! Dachtest du wirklich, ich würde dir Geld geben, du Zigeunerhexe? Geh mir aus dem Weg! Ich hoffe, die Inquisition nimmt dich!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_3"://здоровье + везение или скрытность, харизма
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Ach, danke für dein Silber, mein hübscher junger Falke! Jetzt hör zu:"+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! Das ist sehr interessant. Ich werde das in Betracht ziehen...","Wirklich? Ich werde darüber nachdenken...","Ach wirklich? Meinst du das ernst? Nun, das werde ich mir merken...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 1);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 50+rand(20));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 50+rand(20));//скрытность
			}
			else
			{
				dialog.text = "Das hässlichste und unvermeidliche Unglück wartet auf dich. Verfluche den Spötter! Lass dunkle Wolken sich über dir versammeln und lass die Bestrafung dich finden!";
				link.l1 = "Ha-ha! Hast du wirklich gedacht, ich würde dir Geld geben, du Zigeunerhexe? Geh mir aus dem Weg! Ich hoffe, die Inquisition nimmt dich!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_4"://умения в оружие, везение+скрытность, здоровье, харизма
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "Oh la la! Danke für deine Großzügigkeit, mein hübscher junger Falke! Nun hör zu:"+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! Das ist sehr interessant. Ich werde darüber nachdenken...","Wirklich? Das werde ich in Betracht ziehen...","Oh, wirklich? Meinst du das ernst? Nun, das werde ich mir merken...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 2);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCharacterExpToSkill(pchar, "Fortune", 50+rand(100));//везение
				AddCharacterExpToSkill(pchar, "Sneak", 50+rand(50));//скрытность
				AddComplexSelfExpToScill(20, 20, 20, 20);
			}
			else
			{
				dialog.text = "Das hässlichste und unvermeidliche Unglück wartet auf dich. Verfluche den Spötter! Lass dunkle Wolken sich über dir sammeln und lass die Strafe dich finden!";
				link.l1 = "Ha-ha! Dachtest du wirklich, ich würde dir Geld geben, du Zigeunerhexe? Geh mir aus dem Weg! Ich hoffe, die Inquisition nimmt dich!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_exit":
			DialogExit();
			AddCharacterHealth(pchar, -10);
			LAi_CharacterDisableDialog(npchar);
		break;
//<-- гадание

// --> продажа мышьяка
		case "get_poison_1" :
			npchar.quest.poison_price = (hrand(3) + 1) * 10;
			if(hrand(10) == 3 || IsCharacterPerkOn(pchar, "Trustworthy"))
			{				
				dialog.text = LinkRandPhrase("Oh, ich bin mir nicht sicher, schöner Mann! Vor nicht allzu langer Zeit bat ein Kerl um Hilfe beim Ratten töten und dann hat jemand die Soldaten in der Festung vergiftet. Es wurde ziemlich heiß für meine Leute auf der Insel, während die Wachen uns zwei Wochen lang verhörten, bis sie den Mörder fanden. Er war ein feindlicher Spion.","Und wie kann ich mir Ihrer Absichten sicher sein? Vielleicht wollen Sie nur einen Adligen vergiften, gegen den Sie zu feige sind, um in einem ehrenhaften Duell zu kämpfen??","Mir wurde erzählt, dass jemand einen Händler in der Taverne vergiftet und all seine Habseligkeiten gestohlen hat. Der Mann hat lange gelitten, bevor er starb. Schaum kam aus seinem Mund und er wurde lila wie eine Aubergine.. Bist du dafür verantwortlich, mein Liebling?");
				link.l1 = "Du Zigeunerweiber teilt sicherlich gerne eure Meinungen! Mach dir keine Sorgen, Mädchen, ich werde die Leute nicht vergiften. Das ist eine weibische Art zu töten, nicht mein Stil. Für Männer habe ich mein Schwert, aber ich kann diese verfluchten Ratten nicht ertragen.";
				link.l1.go = "get_poison_2";
				if (IsCharacterPerkOn(pchar, "Trustworthy")) notification("Trustworthy", "Trustworthy");
			}
			else
			{
				dialog.text = "Sie versuchen mich in eine Falle zu locken! Nein, Herr, ich habe kein Gift. Ich habe Pflanzen und Tränke, aber keine Gifte.";
				link.l1 = "Na schön dann. Leg mir nicht den bösen Blick auf.";
				link.l1.go = "exit";
				notification("Perk Check Failed", "Trustworthy");
			}	
		break;
		
		case "get_poison_2" :
			dialog.text = "Oh, stattlicher so ein tapferer Mann! (flüstert) Bezahle mich "+sti(npchar.quest.poison_price)+" Dublonen.";
			if (PCharDublonsTotal() >= sti(npchar.quest.poison_price))
			{				
				link.l1 = "Teuer... Das Zeug sollte besser funktionieren.";
				link.l1.go = "get_poison_4";
			}
			else
			{
				link.l1 = "Keine Chance! Ich habe das gleiche zu Hause für fünf Pistolen gekauft! Für so viel Geld könnte ich jede Ratte selbst fangen!";
				link.l1.go = "get_poison_3";
			}
		break;
		
		case "get_poison_3" :
			dialog.text = "Fang sie dann selbst und belästige mich nicht. Beim nächsten Mal rufe ich die Wache.";
			link.l1 = "Keine Notwendigkeit für die Wachen Hexe, ich gehe.";
			link.l1.go = "exit";
		break;
		
		case "get_poison_4" :
			PlaySound("interface\important_item.wav");
			RemoveDublonsFromPCharTotal(sti(npchar.quest.poison_price));
			TakeNItems(pchar, "rat_poison", 1);
			DialogExit();
		break;
// <-- продажа мышьяка

	// --> Мангароса
		case "mangarosa":
			dialog.text = LinkRandPhrase("Zeig mir die Pflanze, Liebes... Hm... Ich vermute, dass ich sie dir abkaufen kann. Dreihundert Achtstücke, einverstanden?","Zeig es mir, Schönling... Heh... Nun, ich kann zweihundertfünfzig dafür zahlen.","Lass uns sehen... Oh! Ein interessantes Exemplar! Zweihundert Pesos! Abgemacht?")"";
			link.l1 = LinkRandPhrase("Oh Herr... dunkeläugig, ich bin kein Landei. Ich kenne diese Pflanze. Es ist Mangarosa...","Oh, wirklich?! Das ist ein perfektes Exemplar von Mangarosa. Versuch nicht, mich zu betrügen, Zigeuner.","Aha, und du nimmst an, dass ich dir diese Mangarosa für so einen lächerlichen Betrag gebe.");
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			dialog.text = "Gut, gut, attraktiv. Ich sehe, dass du etwas über diese Pflanze weißt. Fünfzig Dublonen. Gib es mir.";
			link.l1 = "Haltet ein! Ich will wissen, wie es verwendet werden kann und wofür. Könnt ihr mir das sagen? All eure Leute sind bereit, viel Gold für diesen kleinen Strauch zu zahlen!";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			// тут работает харизма
			if (sti(pchar.questTemp.Mangarosa.g_count) == 5 || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 10+hrand(25)+hrand(30, "1"))
			{
				dialog.text = "Hm... Ich vermute, es ist nicht zu schlimm, wenn ich Ihnen ein bisschen darüber erzähle. Ohne besondere Fähigkeiten werden Sie mit dieser Pflanze nichts anfangen können.";
				link.l1 = "Ich höre zu.";
				link.l1.go = "mangarosa_3";
			}
			else
			{
				dialog.text = LinkRandPhrase("Meine Leute könnten viel Gold zahlen, aber sie würden niemals ihre Geheimnisse preisgeben.","Gold ist Gold und Geheimnisse sind Geheimnisse, junger Mann... ","Ja, wir sind bereit zu zahlen, aber nicht zu erzählen.")+"Also, wirst du mir deine Mangarosa verkaufen? Fünfzig Dublonen ist unser üblicher Preis dafür, niemand wird dir mehr bezahlen.";
				link.l1 = "Oh, gut ... Es funktioniert sowieso für mich. Fünfzig Dublonen. Nimm es";
				link.l1.go = "mangarosa_trade";
				link.l2 = "Versteh mich, ich will es nicht verkaufen. Ich will wissen, warum du es brauchst. Teile dein Wissen mit mir und ich gebe es dir umsonst.";
				link.l2.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_trade":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Nimm deine Münzen, junger Falke. Und noch etwas, bring uns mehr von diesen Pflanzen. Aber wir können sie nur einzeln kaufen, weil wir keine großen Summen bei uns tragen. Die Wachen vertrauen unserer Art nicht und ärgern uns gerne...";
			link.l1 = "Gut. Wenn ich mehr finde, bringe ich es.";
			link.l1.go = "mangarosa_trade_exit";
		break;
		
		case "mangarosa_trade_exit":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "gipsy_trade";
			AddQuestRecord("Mangarosa", "3");
		break;
		
		case "mangarosa_exit":
			dialog.text = LinkRandPhrase("Unmöglich! Wenn du es nicht verkaufen willst - dann tu es nicht. Ich werde dir nichts erzählen.","Ich werde unsere Geheimnisse nicht einem Gorger-Außenseiter aussetzen! (spuckt) Willst es nicht verkaufen? Zur Hölle mit dir.","Freund, das ist nichts für deine Ohren. Willst du es nicht für fünfzig Dublonen verkaufen? Geh und verkaufe es an das Handelsmädchen für zweihundert Pesos.");
			link.l1 = LinkRandPhrase("Schade für dich! Ein anderer deiner Leute wird mir sowieso davon erzählen. Und sie wird diese Pflanze als Geschenk bekommen. Bis dann!","Warum so stur? Wenn du es mir nicht sagst, dann tut es der andere. Und sie wird diese Mangarosa als Geschenk bekommen. Lebewohl.","Dein Atem stinkt nach Knoblauch. Ich werde schließlich bekommen, was ich will. Ein anderer deines Volkes wird gesprächiger sein und die Pflanze umsonst bekommen. Wir sehen uns.");
			link.l1.go = "exit";
			npchar.quest.mangarosa = "true";
			pchar.questTemp.Mangarosa.g_count = sti(pchar.questTemp.Mangarosa.g_count)+1;
		break;
		
		case "mangarosa_trade1":
			dialog.text = "Und warum fragst du, Falke?! Sicher! Gib es mir.";
			link.l1 = "Gib mir fünfzig Dublonen.";
			link.l1.go = "mangarosa_trade1_1";
			link.l2 = "Ach du meine Güte! Es scheint, dass ich es verloren habe oder auf meinem Schiff vergessen habe. Was für ein Jammer. Tschüss...";
			link.l2.go = "exit";
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_trade1_1":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Mach dir keine Sorgen, ich werde dich nicht betrügen. Nimm deine Münzen.";
			link.l1 = "Nimm deine Mangarosa. Ich bringe mehr, wenn ich finde.";
			link.l1.go = "exit";
		break;
		
		case "mangarosa_3":
			dialog.text = "Wir mahlen die Knospen auf diese besondere Weise, dann trocknen wir sie, picken die Samen und Stiele heraus, dann mischen wir sie mit Tabak, stopfen unsere Pfeifen und rauchen die Mischung. Und wir bekommen einen... unvergesslichen Effekt. Wie eine Vergiftung mit Alkohol, aber ohne Kopfschmerzen danach. Eine Pflanze reicht für zwei Dutzend Pfeifenfüllungen.";
			link.l1 = "Ich sehe jetzt! Können Sie mir diese geheime Technik beibringen? Ich kann Sie gut bezahlen...";
			link.l1.go = "mangarosa_4";
		break;
		
		case "mangarosa_4":
			dialog.text = "Junger Falke, glaub mir, du brauchst das nicht. Lass dich nicht ein, die Pflanze wird dich ruinieren. Sie stumpft das Gehirn ab und macht dich fett. Frag mich nicht einmal. Aber... Ich sehe einen tapferen Mann vor mir, mit einem Schwert, einen Seemann...vielleicht sogar einen Kapitän?";
			link.l1 = "Du hast recht.";
			link.l1.go = "mangarosa_5";
		break;
		
		case "mangarosa_5":
			dialog.text = "Hört hier zu. Mangarosa kann für viel edlere Dinge genutzt werden und ihr könntet es nützlich finden. Eine Heilerin von uns kennt all ihre Geheimnisse. Sie ist diejenige, die ihr braucht\nGebt mir die Pflanze und ich sage euch ihren Namen und wo ihr sie finden könnt. Sie jedoch zu überzeugen, ihre Geheimnisse mit euch zu teilen, wird euer Problem sein.";
			link.l1 = "Gut. Nimm die Pflanze und sag mir, wie ich deinen Zigeunerzauberer finde.";
			link.l1.go = "mangarosa_6";
		break;
		
		case "mangarosa_6":
			RemoveItems(pchar, "cannabis7", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ihr Name ist Amelia. Sie lebt alleine in einem kleinen Haus unter den Dünen, nicht weit vom Meer entfernt, irgendwo an der Südwestküste des Spanischen Hauptlandes, wie die klugen Leute sagen.";
			link.l1 = "Ach du lieber Himmel, könntest du bitte etwas genauer sein?";
			link.l1.go = "mangarosa_7";
		break;
		
		case "mangarosa_7":
			dialog.text = "Du bist ein Seemann, mutiger Falke, und ich bin es nicht. Such sie dort, wo ich es gesagt habe. Ihr Zuhause ist wirklich nahe an der Küste. Es liegt in der Nähe einer Bucht genau im Südwesten der Spanischen Haupt - Seeleute müssen es kennen.";
			link.l1 = "In Ordnung, ich werde versuchen, es zu finden...";
			link.l1.go = "mangarosa_8";
		break;
		
		case "mangarosa_8":
			dialog.text = "Nimm eine Mangarosa für sie mit oder sie wird nicht einmal mit dir sprechen. Und vergiss nicht, Dublonen mitzubringen, denk nicht einmal daran, dass sie dich umsonst unterrichten wird!";
			link.l1 = "Solche Habgier. Ich werde das in Betracht ziehen. Danke für deine Geschichte!";
			link.l1.go = "mangarosa_9";
		break;
		
		case "mangarosa_9":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "amelia";
			pchar.questTemp.Mangarosa.Tell = "true"; // калеуче
			AddQuestRecord("Mangarosa", "4");
			// создаем и ставим Амелию
			sld = GetCharacter(NPC_GenerateCharacter("Amelia", "gipsy_3", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Amelia";
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Mangarosa.c";
			sld.dialog.currentnode = "amelia";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Amelia_house", "barmen", "stay");
		break;
		
		// --> Тёмные воды исцеления
		case "dwh_ne_ta":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "Nein, " + GetSexPhrase("mein Lieber", "meine Schöne") + ", ich bin nicht diejenige, die du suchst, es ist " + sld.name + ". Sie ist gerade hier in der Stadt. Ich habe sie kürzlich gesehen.";
			link.l1 = "Danke.";
			link.l1.go = "exit";
		break;
		// <-- Тёмные воды исцеления
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Hört mir zu, tapferer Falke, ich mag ein Zigeuner sein, aber selbst wir verurteilen offene Gewalt. Bitte steckt euer Schwert weg.","Hör mir zu tapferer Falke, als Bürger dieser Stadt bitte ich dich, dein Schwert zu scheiden.");
			link.l1 = LinkRandPhrase("Gut.","Wie du wünschst.","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string GuessText()
{
	string sText;
	switch (hrand(19))
	{
		case 0: sText = "you will have luck, brave young falcon, tomorrow you'll be lucky with cards!" break;
		case 1: sText = "the fortune will be kind with you in your mercantile business, captain!" break;
		case 2: sText = "there is a misfortune awaiting you in the open sea, it's waiting just for you, wait for three days!" break;
		case 3: sText = "I see that you need to seek help from your closest ones, you won't make it alone in your next fight!" break;
		case 4: sText = "go and light a candle in a church, you have been cursed by your enemy. You won't make it without God's help!" break;
		case 5: sText = "you are going to lose a lot soon, my falcon, but don't despair and hope for yourself, seek help from you friends..." break;
		case 6: sText = "a heavy loss is waiting for you in the sea, but I see, that you, captain, will be able to ride it out even if you don't get what you want." break;
		case 7: sText = "you have entered the aim of misfortune, captain! Visit a brothel and have some rest." break;
		case 8: sText = "you will get what you want, captain, but don't expect anything good from it. All what you've wanted so passionately, captain, will bring only bad things so you'd better change your plans away." break;
		case 9: sText = "I see that there is a sign on that face of yours, the sign of ultimate luck. You will get more than you're expecting to get, young man!" break;
		case 10: sText = "you need to evaluate your wish once again and decide. Do you really need it? Your fate is giving you a chance to rethink." break;
		case 11: sText = "it's rare luck, not everyday we've getting a chance to rethink. Take a rest for a few days, bright-eyed, think about things. Don't hurry to your death!" break;
		case 12: sText = "though all of your efforts won't give you the expected result, don't despair, young falcon, great luck is waiting for you in the most unexpected day, don't lose it!" break;
		case 13: sText = "your problem won't be solved in a positive way but you are a stubborn one and you'll get what you want but, perhaps, not from the place you've expected." break;
		case 14: sText = "you'd better forget about the business you are up to. You will never be lucky in this and if you'll be continuing in it than, perhaps, your closest people will be hurt or killed." break;
		case 15: sText = "there is an event which is waiting for you, captain, and it will completely change your life. Your recent concerns will lose all of their meaning to you after that." break;
		case 16: sText = "there is danger on your way to your dream, captain, and you must be really lucky if you will be able to get what you want without heavy losses. It's better to turn away and forget your unachievable dream. Or perhaps, this fate could be tricked if you lose in cards or dice right now..." break;
		case 17: sText = "I see a strong power in you like a rock and a light as bright as the north star which leads people. Good news is waiting for you!" break;
		case 18: sText = "a bad sign is rising on your way, fear the evil eye and keep loyal men close to you." break;
		case 19: sText = "a lucky event is rising on your way right behind your own back. Look for the good which is coming right to your hands and don't chase the unachievable." break;
	}
	return sText;
}
