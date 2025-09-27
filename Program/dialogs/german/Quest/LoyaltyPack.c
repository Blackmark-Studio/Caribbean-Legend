void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		case "Alonso":
			NextDiag.TempNode = "Alonso";
			
			if (GetDLCenabled(DLC_APPID_1))
			{
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FirstStage", "ready"))
				{
					dialog.text = "Darf ich was sagen, Käpt'n?";
					link.l1 = "Später, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Nur zu.";
					link.l2.go = "Alonso_1";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.SecondStage", "ready"))
				{
					dialog.text = "Darf ich was sagen, Käpt'n?";
					link.l1 = "Später, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Nur zu.";
					link.l2.go = "Alonso_Lvl_8_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.ThirdStage", "ready"))
				{
					dialog.text = "Darf ich was sagen, Käpt'n?";
					link.l1 = "Später, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Nur zu.";
					link.l2.go = "Alonso_Lvl_12_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FourthStage", "ready"))
				{
					dialog.text = "Darf ich was sagen, Käpt'n?";
					link.l1 = "Später, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Nur zu.";
					link.l2.go = "Alonso_Lvl_16_Start";
					break;
				}
			}
			
			dialog.text = "Nichts zu melden, Käpt'n.";
			link.l1 = "Weitermachen, Alonso.";
			link.l1.go = "exit";
		break;
		
		case "Alonso_1":
			DelLandQuestMark(npchar);
			dialog.text = "Wie geht's Euch, Käpt'n?";
			link.l1 = "Was meinst du?";
			link.l1.go = "Alonso_2";
		break;
		
		// Основная развилка стадии 1
        case "Alonso_2":
            dialog.text = "Ihr segelt nun schon seit Monaten durch die Karibik, während manche hier keine Woche überleben. Die Mannschaft respektiert Euch, keine Frage, aber ich? Ich mache mir Sorgen um Eure Zukunft.\n"+
                          "Teilt doch Eure Gedanken mit uns, tut der Mannschaft den Gefallen. Wohin steuert die "+pchar.ship.name+"?";
                          
            link.l1 = "Ich habe keinen Plan. Will erstmal diese Gewässer kennenlernen. Das Abenteuer findet uns schon von selbst.";
            link.l1.go = "Alonso_Choice_1";
            
            link.l2 = "Diese Gewässer sind voller Raubtiere, Alonso. Und die "+pchar.ship.name+" ist das kleinste von ihnen. Noch.";
            link.l2.go = "Alonso_Choice_2";
            
            link.l3 = "Ich verdiene gern Geld. Am liebsten legal. Aber mal sehen, wie's läuft.";
            link.l3.go = "Alonso_Choice_3";
			
            if (!SandBoxMode)
            {
                link.l4 = "Du weißt doch Bescheid. Nach unserem denkwürdigen Gespräch auf der Ulysses wurde alles nur noch komplizierter…";
                link.l4.go = "Alonso_Choice_4";
            }
        break;
        
        case "Alonso_Choice_1":
            dialog.text = "Das nenne ich Freiheit! Hauptsache, es reicht für den Unterhalt des Schiffes und etwas bleibt für schlechte Zeiten in der Kiste.\n"+
                          "Wohin auch immer Laune, Auftrag oder Schatzkarte Euch führen - nehmt Passagiere mit, Frachtaufträge, jeden kleinen Job, der sich anbietet.\n"+
                          "Ein bisschen Kleinhandel schadet auch nicht - billig kaufen, wo es sich lohnt, verkaufen, wo man kann.\n"+
                          "Und wenn Ihr unterwegs einen einsamen Händler seht… Hehe. Ihr habt recht, Käpt'n. Das Abenteuer findet uns tatsächlich von selbst.";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 50);
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            
            link.l1 = "Danke für den guten Rat, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_2":
            dialog.text = "Einträgliches Geschäft, wenn das Schiff es hergibt. Sucht einsame Händler und zeigt ihnen, was 'Geiz ist nicht geil' wirklich bedeutet.\n"+
                          "Leider gilt dann auch: 'Nichts bleibt ewig verborgen.' Es findet sich immer eine Plaudertasche in der Mannschaft, die im ersten Hafen von euren Taten erzählt.\n"+
                          "Also entweder raubt alle Flaggen ein bisschen aus, oder sucht euch einen Feind fürs Leben.\n"+
                          "Wobei, ich übertreibe vielleicht. Wenn's wirklich eng wird, gibt's in Port Royal einen Anwalt, der für klingende Münze alle Probleme mit den Behörden regelt. Nennen wir's Piratensteuer, hehe!";
            
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_ACCURACY, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", -1);
            
            link.l1 = "Danke für den guten Rat, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_3":
            dialog.text = "Äh, da kann ich Euch nicht viel helfen, Käpt'n. Ihr braucht ein richtiges Handelsschiff - eine Barkentine oder besser noch eine Bark. Ich werd's wohl noch bereuen, aber nehmt leichtere Kanonen oder werft sie ganz über Bord.\n"+
                          "Nehmt Frachtaufträge von Ladenbetreibern, handelt unterwegs auf eigene Rechnung und befördert Passagiere.\n"+
                          "Wenn Ihr genug gespart habt, investiert in Läden und Banken. Glaubt mir, Käpt'n - eines Tages wird Euer Geld Geld verdienen, und Ihr könnt Euch ein großes Schiff mit zweihundert Mann leisten.\n"+
                          "Für das übrigens nicht Ihr zahlt, sondern Euer Geschäft.";
            
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            AddCharacterExpToSkill(pchar, SKILL_SAILING, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "Danke für den guten Rat, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_4":
            dialog.text = "Ich seh das anders, Käpt'n. Auf der Ulysses wart Ihr nur Passagier - diese armen Seelen haben keine Kontrolle über ihr Schicksal. Jetzt seid Ihr Kapitän, der sich seinen Hut verdient hat, also könnt Ihr jedes Problem lösen. Ich hab's Euch schon mal gesagt - es gibt keinen höheren Stand in unserer Welt.\n"+
                          "Mein Bauch sagt mir, diese Geschichte mit Eurem Bruder wird noch Jahre dauern, also kümmert Euch erstmal um Euch selbst. Monsieur Michel läuft nicht weg, hehe…\n"+
                          "Ihr seid nicht der Einzige mit Problemen in der Karibik. Perfekte Zeit, anderen zu helfen und dabei Geld, Ausrüstung und Verbindungen zu verdienen. Ihr lernt unterwegs alles, was Ihr für diese Familienangelegenheit braucht…";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 100);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "Danke für den guten Rat, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
		
        case "Alonso_Common_End":
            dialog.text = "Legt Euch nicht auf eine Rolle fest, Käpt'n. Macht nur, was Ihr wollt. Nehmt alles und gebt nichts zurück. Dann wird alles gut.";
            link.l1 = "Und danke auch für die weisen Worte.";
            link.l1.go = "Alonso_Common_End_2";
        break;
        
        case "Alonso_Common_End_2":
            dialog.text = "Äh, dafür bezahlt Ihr mich ja, Käpt'n. Glaubt Ihr, der Mannschaft reicht der kärgliche Sold, um Eure Befehle zu befolgen?\n"+
                          "Dutzende Männer eingepfercht auf engstem Raum, niemand weiß, wann sie wieder Land sehen, oder ob überhaupt. Und ein Schiff zu versenken? Kinderleicht.";
            link.l1 = "Ja, ja, kenne ich schon, Alonso. Was hast du vorhin über Schiffe gesagt?";
            link.l1.go = "Alonso_Common_End_3";
        break;
        
        case "Alonso_Common_End_3":
            dialog.text = "Hehe! Ein Schiff ist Gefängnis, Militärlager und Kloster in einem. Ein Männerhaufen, kurz gesagt. Also werden Probleme entweder mit Worten oder mit der Peitsche gelöst. In Eurem Fall ist Letzteres, hehe, keine Option, also dachte ich, wir plaudern mal. Damit's Euch leichter fällt, sozusagen.";
            link.l1 = "Warst du selbst jemals im Gefängnis? In der Armee? Im Kloster, Gott bewahre? Und überhaupt, Alonso, erzähl mal von dir. Ich weiß ja fast nichts über dich.";
            link.l1.go = "Alonso_Story_1";
        break;
        
        // История Алонсо
        case "Alonso_Story_1":
            dialog.text = "Also in Klöstern war ich nicht, da lüg ich nicht. Allerdings hab ich mal bei der Heiligen Inquisition gedient…";
            link.l1 = "Wie zum Teufel kam das denn?";
            link.l1.go = "Alonso_Story_2";
        break;
        
        case "Alonso_Story_2":
            dialog.text = "Oh! Das war so. Ich hab als Söldner im europäischen Krieg gedient. Der Teufel weiß, wie's angefangen hat oder wer gegen wen kämpfte. Wir wussten nur, der Krieg lief schon dreißig Jahre und welcher Kommandant halbwegs regelmäßig zahlte. Das war vielleicht ein Abenteuer!\n"+
                          "Das war '42… oder war's '41? Egal. Zwei Kompanien, beide im Dienst des Kaisers, trafen sich im Wald. Im Nebel. Und hackten sich gegenseitig in Stücke! Drei Tage Gemetzel!";
            link.l1 = "Wie ist das möglich?";
            link.l1.go = "Alonso_Story_3";
        break;
        
        case "Alonso_Story_3":
            dialog.text = "Versuch mal im Nebel Freund von Feind zu unterscheiden. Außerdem wurden wir seit drei Monaten nicht bezahlt, also dachte jeder an Beute.\n"+
                          "Wir haben uns gegenseitig zur Hälfte niedergemacht. Als wir's merkten, war's zu spät. Da hab ich diesen Moskowiter kennengelernt. Groß wie ein Bär, aber ein Herz aus Gold!";
            link.l1 = "Was passierte dann?";
            link.l1.go = "Alonso_Story_4";
        break;
        
        case "Alonso_Story_4":
            dialog.text = "Ihr wisst ja, wie's im Krieg ist? Wer zuerst berichtet, ist der Held. Also dachten wir uns - machen wir aus dieser Schande einen Vorteil!\n"+
                          "Haben uns mit den Jungs abgesprochen, sind zum Zahlmeister, meldeten eine 'glorreiche Schlacht'. Tote bekamen keinen Sold mehr, Überlebende wurden bezahlt, ich und mein Kumpel bekamen Prämien, und der Kommandant seinen Anteil.";
            link.l1 = "Also bist du reich, Alonso.";
            link.l1.go = "Alonso_Story_5";
        break;
        
        case "Alonso_Story_5":
            dialog.text = "Ha! Dann haben wir eine Woche Wein getrunken und Karten gespielt. Zum Glück hatte mein neuer Freund aus dem fernen Moskauer Reich eine Schwäche für seltene Stücke, sonst wär ich im Schuldturm gelandet. Kaufte mir eine Trophäe ab - eine prächtige dreiläufige Pistole, und zu einem guten Preis. Hat meine Not nicht ausgenutzt.";
            link.l1 = "Eine fantastische Geschichte, Alonso. Klingt für mich, als hättest du sie gerade erfunden.";
            link.l1.go = "Alonso_Gift";
        break;
        
        // Вручение подарка
        case "Alonso_Gift":
            dialog.text = "Ihr verletzt mich, Käpt'n. Hier, nehmt dieses kleine Geschenk.";
            link.l1 = "Was ist das?";
            link.l1.go = "Alonso_Gift_2";
        break;
        
        case "Alonso_Gift_2":
            // Выдаем Берендейку
            GiveItem2Character(pchar, "talisman20");
			SetAlchemyRecipeKnown("talisman20");
            
            dialog.text = "Ein Patronengurt für den Musketenkampf. In der Heimat meines moskauer Freundes trägt das jeder. Hat er jedenfalls gesagt.\n"+
                          "Möge es Euch gute Dienste leisten, Käpt'n. Seht es als Geschenk von der Mannschaft.";
            link.l1 = "Unerwartet! Danke, Alonso. Also was war das mit deinem Dienst bei der Inquisition?";
            link.l1.go = "Alonso_Escape";
        break;
        
        case "Alonso_Escape":
            PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Äh…\n"+
                          "Die Glocken läuten, Käpt'n! Zeit, an die Arbeit zu gehen. Ein andermal weiter.";
            link.l1 = "Wir werden dieses Gespräch definitiv fortsetzen. Danke für das Geschenk!";
            link.l1.go = "exit";
            
			AddDialogExitQuestFunction("LoyaltyPack_FirstStage_DlgExit");
        break;
		
		// (Уровень 8) - Продолжаем историю
        case "Alonso_Lvl_8_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Ihr habt viel erreicht seit unserem letzten Gespräch, und niemand - weder die Mannschaft noch ich - zweifelt mehr an Euren Talenten.";
			link.l1 = "Es gab Zweifel?";
			link.l1.go = "Alonso_Lvl_8_1";
        break;

        case "Alonso_Lvl_8_1":
            dialog.text = "Natürlich gab's die. Wir sind einfache Leute - gewohnt, uns auf das Schlimmste vorzubereiten. Genießt Eure Freiheit, Käpt'n. Macht so weiter und Ihr werdet eine ganz andere Seite der Karibik sehen.";
            link.l1 = "Schön zu hören. Jetzt erzähl mir von deinem Dienst bei der Inquisition. Letztes Mal hast du mit einer Armeegeschichte angefangen und auch damit aufgehört.";
            link.l1.go = "Alonso_Lvl_8_2";
        break;

        case "Alonso_Lvl_8_2":
            dialog.text = "Was gibt's da zu erzählen? Nach dem sinnlosen aber sehr profitablen Waldgemetzel wurden ich und der Moskowiter dicke Freunde und haben noch einige Dinger gedreht.\n"+
                          "Ich erinnere mich, wir beschlossen mal einen kaiserlichen Tross zu überfallen. Kundschafter meldeten - sie transportieren Trophäen, Gold, Waffen...";
            link.l1 = "Und, habt ihr's geschafft?";
            link.l1.go = "Alonso_Lvl_8_3";
        break;

        case "Alonso_Lvl_8_3":
            dialog.text = "Kinderspiel. Griffen von zwei Seiten an, verjagten die Wachen, öffneten die Wagen - und fanden Kohl! Verfaulter, stinkender Kohl für irgendeine Garnison! Aber wisst Ihr was? Wir hatten seit einer Woche nichts gefressen, also waren wir sogar darüber froh!";
            link.l1 = "Als ob das Essen auf meinem Schiff besser wäre.";
            link.l1.go = "Alonso_Lvl_8_4";
        break;

        case "Alonso_Lvl_8_4":
            dialog.text = "Nun, jetzt bin ich's gewohnt. Aber damals... Nach einer Woche vom Land leben - da würdest du Baumrinde abnagen!\n"+
                          "Aber mein Freund verlor nicht den Mut. Holte seinen Flachmann mit seinem speziellen Gebräu raus - Moskauer Rezept, sagte er. War uns egal, Hauptsache kein Essig! Nach ein paar Schlucken schmeckte sogar der Kohl wie eine Delikatesse!";
            link.l1 = "Widerlich.";
            link.l1.go = "Alonso_Lvl_8_5";
        break;

        case "Alonso_Lvl_8_5":
            dialog.text = "Widerlich ist der Zustand unserer Wasserfässer, aber dieser Moskauer Fusel hat mir an dem Tag das Leben gerettet.";
            link.l1 = "Wie das?";
            link.l1.go = "Alonso_Lvl_8_6";
        break;

        case "Alonso_Lvl_8_6":
            dialog.text = "Wir haben uns bis zur Besinnungslosigkeit besoffen, direkt im Straßenschlamm mit schwimmenden Kohlköpfen. Naja, eins führte zum anderen, und ich geriet in Streit mit so einem Adeligen. Ein Deutscher, ganz fein und aufgeblasen. Zu vornehm, um mit uns zu trinken, putzte nur seine Muskete und machte bissige Bemerkungen.\n"+
                          "Also sitzen wir da, ruhen uns aus, ertränken unseren Kummer über dem Kohl. Und er fängt an, uns über militärische Weisheit zu belehren. Unsere treuen Säbel und Piken würden bald vergessen sein, aber das Bajonett - das sei die Zukunft und der Schlüssel zu allem.\n"+
                          "Also hab ich mit ihm gestritten, und irgendwie einigten wir uns darauf, bis zum Tod zu kämpfen - ausgerechnet mit Bajonetten. Fragt nicht, wie's dazu kam, ich erinnere mich selbst nicht.\n"+
                          "Aber Bajonette hatten wir in der ganzen Kompanie nur zwei. Eins gehörte diesem Offizierchen, das andere Fox, einem Engländer. Ich lieh mir seine Flinte und prügelte den Deutschen damit tot, dann machte ich mich aus dem Staub.";
            link.l1 = "Du warst doch hungrig und betrunken.";
            link.l1.go = "Alonso_Lvl_8_7";
        break;

        case "Alonso_Lvl_8_7":
            dialog.text = "Später hab ich kapiert, dass das Gebräu meines Freundes die Hand wirklich stabilisiert, wenn man mit einer schweren Muskete herumfuchtelt. Da hatte der tote Deutsche wohl doch recht mit seinen Ideen.";
            link.l1 = "Und was hat das mit deinem Dienst bei der Inquisition zu tun?";
            link.l1.go = "Alonso_Lvl_8_Gift";
        break;

        case "Alonso_Lvl_8_Gift":
            dialog.text = "Ihr glaubt mir schon wieder nicht, Käpt'n! Hier, nehmt das.";
            link.l1 = "Eine Flasche und ein Stück Papier?";
            link.l1.go = "Alonso_Lvl_8_Gift_2";
        break;

        case "Alonso_Lvl_8_Gift_2":
            // Даём игроку настойку и рецепт
            GiveItem2Character(pchar, "vodka");
            SetAlchemyRecipeKnown("vodka");

            dialog.text = "Das ist das Gebräu, von dem ich erzählt hab. Und das Rezept. Falls es Euch gefällt, hehe.";
            link.l1 = "Tut mir leid, mein Freund, aber Gekritzel und irgendein trübes Gebräu sind nicht…";
            link.l1.go = "Alonso_Lvl_8_Gift_3";
        break;

        case "Alonso_Lvl_8_Gift_3":
            // Даём игроку мушкет с багинетом
            GiveItem2Character(pchar, "mushket10");

            dialog.text = "Schon gut, schon gut, Käpt'n. Wollte es Euch sowieso schenken. Mir steht so eine Waffe nicht, aber Euch wird sie nützen. Bajonette sind seltene Biester. Aber wenn Ihr's gelernt habt, vergesst Ihr das Säbelschwingen.";
            link.l1 = "Warte, ist das die Muskete von diesem kaiserlichen Offizier? Den du getötet hast?";
            link.l1.go = "Alonso_Lvl_8_Gift_4";
        break;

        case "Alonso_Lvl_8_Gift_4":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Genau die. Wie Ihr seht, hab ich Euch die Wahrheit erzählt, Käpt'n.";
            link.l1 = "Aber danach hab ich nicht gefragt.";
            link.l1.go = "Alonso_Lvl_8_Escape";
        break;

        case "Alonso_Lvl_8_Escape":
            dialog.text = "Die Glocken läuten, Käpt'n! Zeit, an die Arbeit zu gehen. Ein andermal weiter.";
            link.l1 = "Wir werden dieses Gespräch definitiv fortsetzen. Danke für die Muskete!";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_SecondStage_DlgExit");
        break;

        // (Уровень 12)
        case "Alonso_Lvl_12_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Kapitän, wegen der neuen Rekruten...";
			link.l1 = "Ist etwas passiert?";
			link.l1.go = "Alonso_Lvl_12_1";
        break;

        case "Alonso_Lvl_12_1":
            dialog.text = "Wollte Euch berichten, dass beim Abendessen einer der Neuen erwähnte, er wollte unbedingt auf Euer Schiff anheuern.";
            link.l1 = "Und was bedeutet das genau?";
            link.l1.go = "Alonso_Lvl_12_2";
        break;

        case "Alonso_Lvl_12_2":
            dialog.text = "Dass es bald mehr solche Leute geben könnte. Ihr habt Euch einen Namen gemacht, Käpt'n.";
            link.l1 = "Komisch, dass ich immer noch nicht weiß, was hinter deinem Namen steckt. Die Geschichte mit der Inquisition hast du nie zu Ende erzählt.";
            link.l1.go = "Alonso_Lvl_12_3";
        break;

        case "Alonso_Lvl_12_3":
            dialog.text = "Oh, wo war ich... Richtig! Dann versuchten wir uns als Militärlieferanten. Der Krieg neigte sich dem Ende zu, man musste an die Zukunft denken. Und mein Freund hatte immer einen Kopf voller Zukunftspläne.";
            link.l1 = "Das ist ein großer Karrieresprung. Gerade noch habt ihr euch bei einem geplünderten Kohlwagen besoffen.";
            link.l1.go = "Alonso_Lvl_12_4";
        break;

        case "Alonso_Lvl_12_4":
            dialog.text = "Na und? Wir bekamen einen Auftrag für hundert Helme für irgendein Regiment. Gute Anzahlung gab's auch. Wir freuten uns, gingen feiern... Spielten Karten.\n"+
                          "Morgens wachen wir auf --- das Geld ist weg, die Armee marschiert in zwei Tagen ab, und wir haben keinen einzigen Helm!";
            link.l1 = "Und was habt ihr gemacht?";
            link.l1.go = "Alonso_Lvl_12_5";
        break;

        case "Alonso_Lvl_12_5":
            dialog.text = "Gingen zum frischen Schlachtfeld, sammelten Hüte von den Toten. Dann nagelten wir allerlei Metallstücke dran, befestigten Platten... Sah lächerlich aus, aber es funktionierte! Vor einem Säbelhieb schützte es definitiv. Na ja, einmal sicher. So gut wie jeder Helm, oder?!";
            link.l1 = "Hat der Quartiermeister eure Findigkeit geschätzt?";
            link.l1.go = "Alonso_Lvl_12_6";
        break;

        case "Alonso_Lvl_12_6":
            dialog.text = "Schickte uns vors Kriegsgericht wegen Unterschlagung und Betrug. Aber wisst Ihr was? Die Soldaten sagten später, diese Hüte hätten ihnen mehr als einmal das Leben gerettet. Und uns auch, wie sich herausstellte.";
            link.l1 = "Wie das?";
            link.l1.go = "Alonso_Lvl_12_7";
        break;

        case "Alonso_Lvl_12_7":
            dialog.text = "Nun, wir landeten beide im Gefängnis. Und unsere Kompanie wurde auf einen Einsatz geschickt. Weiß nicht, wohin oder gegen wen, und sie wussten es wahrscheinlich auch nicht. Sie kamen nie zurück.\n"+
                          "...\n"+
                          "Entschuldigt, Käpt'n. Ein andermal weiter. Nehmt diesen Hut und die Anleitung. Hab ihn gestern gebastelt, um Euch aufzuheitern... Aber hab mich nur selbst umsonst traurig gemacht.";
            link.l1 = "Natürlich, Alonso. Danke für das Geschenk.";
            link.l1.go = "Alonso_Lvl_12_Gift";
        break;

        case "Alonso_Lvl_12_Gift":
            // Даём игроку шляпу
            GiveItem2Character(pchar, "hat10");
            SetAlchemyRecipeKnown("Hat10");

            DialogExit();
			AddDialogExitQuestFunction("LoyaltyPack_ThirdStage_DlgExit");
        break;

        // (Уровень 16) - Финальный
        case "Alonso_Lvl_16_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Kapitän, wollte nur berichten, dass Eure Mannschaft jetzt in Tavernen und Bordellen königlich behandelt wird. Unter Eurer Flagge zu dienen bedeutet heutzutage was!";
			link.l1 = "Danke, Alonso... Schade nur, dass ich von dieser \"königlichen Behandlung\" selbst noch nicht viel sehe.";
			link.l1.go = "Alonso_Lvl_16_1";
        break;

        case "Alonso_Lvl_16_1":
            dialog.text = "Das kommt noch. Die Karibik ist ein Kuchen, den sich nur ein paar Dutzend Kapitäne teilen. Bald werdet Ihr am Tisch sitzen und Euer Stück abbekommen.\n"+
                          "Und wer weiß? Vielleicht werdet Ihr die Karibik-Legende, die den ganzen Kuchen nimmt.";
            link.l1 = "Also erzählst du deine Geschichte zu Ende? Wir waren bei dem Punkt, wo du ins Gefängnis kamst.";
            link.l1.go = "Alonso_Lvl_16_2";
        break;

        case "Alonso_Lvl_16_2":
            dialog.text = "Ha! Der Fall der großen Hutdiebe. Ein Moskowiter und ein Portugiese in einer winzigen Zelle irgendwo in Flandern. Warten auf das Urteil. Todesstrafe, natürlich.\n"+
                          "Ein wichtiger Herr rettete uns - stellte sich als Moskauer Botschafter heraus! Alter Freund von Fadey. War auf der Durchreise, hörte von unserer Not, kaufte uns frei!";
            link.l1 = "Fadey? DER Fadey? Und du hast das verschwiegen?!";
            link.l1.go = "Alonso_Lvl_16_3";
        break;

        case "Alonso_Lvl_16_3":
            dialog.text = "Jep. Da trennten sich unsere Wege - er ging zurück nach Moskau, entweder um gegen die Polen zu kämpfen oder große Geschäfte zu machen. Ich trieb mich noch etwas in der alten Heimat herum, und hier bin ich.";
            link.l1 = "Beeindruckend, Alonso. Nach all der Zeit hast du es geschafft, mir alles zu erzählen, nur nicht über dich selbst. Seltsam, wie ein cleverer Kerl wie du sich über die Inquisition verplappert hat.";
            link.l1.go = "Alonso_Lvl_16_4";
        break;

        case "Alonso_Lvl_16_4":
            dialog.text = "Und ich hab die reine Wahrheit erzählt, Käpt'n! Glaubt mir nicht - fragt Fadey selbst. Er ist nicht schwer zu finden in Basse-Terre.";
            link.l1 = "Vielleicht werde ich das. Und wo ist mein Geschenk?";
            link.l1.go = "Alonso_Lvl_16_5";
        break;

        case "Alonso_Lvl_16_5":
            dialog.text = "Hä?";
            link.l1 = "Du hast mir am Ende jeder Geschichte ein Geschenk gemacht.";
            link.l1.go = "Alonso_Lvl_16_Escape";
        break;

        case "Alonso_Lvl_16_Escape":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Hört Ihr das? Die Glocken läuten. Zeit, an die Arbeit zu gehen.";
            link.l1 = "Weitermachen, Alonso.";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_FourthStage_DlgExit");
        break;
	}
} 