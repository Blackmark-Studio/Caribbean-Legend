// диалоги НПС по квесту НСО
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	
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
			dialog.text = "Wonach suchst du?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";
		break;
		
		// инспектор Ноэль Форже
		case "noel":
			dialog.text = "Freut mich, Sie kennenzulernen, Kapitän!";
			link.l1 = "Es freut mich auch, Sie kennenzulernen, Monsieur Forget. Es ist eine seltene Gelegenheit, einen Gast aus der Metropole hier in der Wildnis zu treffen...";
			link.l1.go = "noel_1";
		break;
		
		case "noel_1":
			DialogExit();
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_3";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "noel_2":
			dialog.text = "Es freut mich, dass ich während dieser Reise auf Ihrem Schiff sein werde, Kapitän. Chevalier de Poincy hat mir viele interessante Geschichten über Sie erzählt. Ich bin sicher, dass wir nach dem Abendessen in der Messe viele Themen zur Diskussion haben werden. Ein Glas Wein könnte auch gelegen kommen.";
			link.l1 = "Ich bin ganz für ein gemütliches Gespräch, besonders wenn ich satt bin. Ich würde mich freuen, Ihr Begleiter zu sein, Baron. ";
			link.l1.go = "noel_3";
		break;
		
		case "noel_3":
			dialog.text = "Perfekt. Wenn wir zu einer Kolonie gehen, würde ich dich bitten, mich zum Gouverneur zu führen, und ich werde ihm persönlich erklären, was zu tun ist. Du wartest einfach, bis ich meine Angelegenheiten beendet habe. Abgemacht?";
			link.l1 = "Aye, Monsieur Forget. Willkommen an Bord!";
			link.l1.go = "noel_4";
		break;
		
		case "noel_4":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 12.0);
		break;
		
		case "noel_5":
			dialog.text = "Tortuga ist eine kleine Kolonie, Kapitän. Ich schätze, es wird mich etwa drei Tage kosten, alles zu inspizieren, was ich auf dieser Insel brauche.";
			link.l1 = "Verstanden, Baron. Also werde ich in drei Tagen hierher kommen, um Sie abzuholen. Viel Glück!";
			link.l1.go = "noel_6";
		break;
		
		case "noel_6":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "Patria_VisiterTortuga");
		break;
		
		case "noel_7":
			dialog.text = "Meine Arbeit auf Tortuga ist erledigt, es ist Zeit, den Anker zu lichten.";
			link.l1 = "Verstanden, Baron. Wir werden sofort aufbrechen.";
			link.l1.go = "noel_8";
		break;
		
		case "noel_8":
			DialogExit();
			Patria_VisiterTortugaSail();
		break;
		
		case "noel_9":
			dialog.text = "Ja-ja, wir werden dies definitiv in Capsterville melden. Die Bedrohung, dass eine so wichtige Kolonie erobert wird... undenkbar, ich werde persönlich dafür sorgen, dass Chevalier de Poincy strenge und rücksichtslose Maßnahmen ergreift! Kapitän, ich werde eine Woche auf dieser Insel bleiben, es gibt hier viele Plantagen, das wird einige Zeit in Anspruch nehmen.";
			link.l1 = "Verstanden, Baron. Ich werde auf dich beim Gouverneurspalast in sieben Tagen warten. Viel Spaß und überarbeite dich nicht!";
			link.l1.go = "noel_10";
		break;
		
		case "noel_10":
			DialogExit();
			DoQuestReloadToLocation("PortPax_town", "reload", "reload3", "Patria_VisiterPortPax");
		break;
		
		case "noel_11":
			dialog.text = "Da bist du ja, Kapitän. Meine Arbeit auf Hispaniola ist erledigt, es ist Zeit, den Anker zu lichten.";
			link.l1 = "Verstanden, Baron. Wir werden sofort aufbrechen.";
			link.l1.go = "noel_12";
		break;
		
		case "noel_12":
			DialogExit();
			Patria_VisiterPortPaxSail();
		break;
		
		case "noel_13":
			dialog.text = "Kapitän, diese Insel kommt mir bekannt vor. Ist es nicht Sankt Christophorus?";
			link.l1 = "Ja, Baron, genau. Wir sind fast da.";
			link.l1.go = "noel_14";
		break;
		
		case "noel_14":
			dialog.text = "Fast da?! Sollten wir nicht auch Saint-Martin besuchen? Es gehört auch zu den französischen Kolonien.";
			link.l1 = "Meinen Sie Sint Maarten? Es ist eine niederländische Kolonie, Monsieur Forget.";
			link.l1.go = "noel_15";
		break;
		
		case "noel_15":
			dialog.text = "Ist das so? In Paris wurde es als Französisch betrachtet. Wie kommt's?";
			link.l1 = "Keine Ahnung, Baron. Seit ich zum ersten Mal im Archipel ankam, war Sint Maarten eine holländische Kolonie. Vielleicht weiß ich etwas nicht. Sie sollten in dieser Angelegenheit mit Chevalier de Poincy sprechen.";
			link.l1.go = "noel_16";
		break;
		
		case "noel_16":
			dialog.text = "Also gut, Kapitän, sei es so. Wir sind ohnehin fast in Capsterville.";
			link.l1 = "...";
			link.l1.go = "noel_17";
		break;
		
		case "noel_17":
			DialogExit();
			Island_SetReloadEnableGlobal("Nevis", true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			pchar.quest.Patria_visiter_fin.win_condition.l1 = "location";
			pchar.quest.Patria_visiter_fin.win_condition.l1.location = "Charles_Roomtownhall";
			pchar.quest.Patria_visiter_fin.function = "Patria_VisiterFin";
			pchar.questTemp.Patria = "epizode_2_return";
		break;
		
		case "noel_18":
			dialog.text = TimeGreeting()+", Kapitän. Ich freue mich, Sie zu sehen. Ich habe gehört, dass Sie befördert wurden, bitte nehmen Sie meine Glückwünsche an! Um Ihnen die Wahrheit zu sagen, Sie sind wirklich einer der vernünftigsten und begabtesten Offiziere im Dienst von de Poincy.";
			link.l1 = "Danke, Monsieur.";
			link.l1.go = "noel_19";
		break;
		
		case "noel_19":
			dialog.text = "Endlich bleibt nur noch eine Kolonie übrig, Saint-Martin. Um ehrlich zu sein, ich bin dieser Reisen überdrüssig. Ich werde froh sein, diese Inspektion abzuschließen und mit der Organisation der nächsten französischen Westindien-Handelskampagne zu beginnen. Sind wir bereit, den Anker zu lichten?";
			link.l1 = "Jawohl, Baron. Komm an Bord.";
			link.l1.go = "noel_20";
		break;
		
		case "noel_20":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBaron", 5.0);
		break;
		
		case "noel_21":
			dialog.text = "Kapitän, könnten Sie mir sagen, was gerade passiert ist? Bedeutet das Krieg? Warum zum Teufel wurden wir fast von den Holländern versenkt?";
			link.l1 = "Baron, ich verstehe selbst nichts! Das muss ein Missverständnis sein, zweifellos.";
			link.l1.go = "noel_22";
		break;
		
		case "noel_22":
			dialog.text = "Kapitän, ich wette, dass dieses 'Missverständnis' einen Namen hat! Peter Stuyvesant, der so genannte 'Mieter' von Saint-Martin und ein Geschäftspartner unseres lieben Chevalier de Poincy!";
			link.l1 = "Ich habe keine Ahnung, Baron. Wir sollten uns besser beeilen und diese Angelegenheit dem Gouverneur General in Capsterville melden.";
			link.l1.go = "noel_23";
		break;
		
		case "noel_23":
			dialog.text = "Ohne Zweifel, das werden wir genau tun! Und ich werde Erklärungen fordern! Ich wusste, dass es ein großer Fehler war, eine Insel an die Holländer zu vermieten! Lassen wir diesen Ort so schnell wie möglich, Kapitän, bevor sich jemand entscheidet, uns zu verfolgen!";
			link.l1 = "Genau, Monsieur ...";
			link.l1.go = "noel_24";
		break;
		
		case "noel_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBack", 5.0);
		break;
		
		case "noel_25":
			dialog.text = "Herr, lassen Sie mich zuerst Ihnen zu Ihrer Beförderung gratulieren! Ich habe die Entscheidung von Monseigneur de Poincy, Ihnen den Rang eines Vizeadmirals zu verleihen, eifrig unterstützt. Sie verdienen diesen Titel! Nun, ich bin kürzlich aus Saint-Martin zurückgekehrt. In den Lagern von Philipsburg haben wir eine Revision durchgeführt, alle holländischen Waren wurden beschlagnahmt und gehören nun der Schatzkammer Frankreichs. Ihnen als Kommandeur einer Kampfoperation wurde ein Anteil an den Trophäen gewährt. Ich stimme dem Chevalier zu, dass dies gerecht ist. Ihre Waren wurden ins Lager des St. Christopher Ladens überführt, und Sie können sie abholen, wann immer Sie wollen.";
			link.l1 = "Danke Ihnen, Baron. Lassen Sie die Waren eine Weile dort liegen. Bei meiner Rückkehr aus Curacao werde ich sie nehmen.";
			link.l1.go = "noel_26";
		break;
		
		case "noel_26":
			dialog.text = "Viel Glück in Ihrer nächsten Kampagne, Vizeadmiral! Ich bin zuversichtlich, dass Sie mit dem Sieg zurückkehren und diesen Schurken Stuyvesant gerecht bestrafen werden.";
			link.l1 = "...";
			link.l1.go = "noel_27";
		break;
		
		case "noel_27":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_start";
			AddQuestRecord("Patria", "58");
			pchar.questTemp.Patria.GoodsSM = "true";
		break;
		
		case "noel_28":
			dialog.text = "Wen haben wir denn hier! Vizeadmiral Charles de Maure! Schön, Sie zu sehen! Was führt Sie nach Port-au-Prince?";
			link.l1 = "Es freut mich auch, Sie kennenzulernen, Baron. Ich bin hier wegen meiner Pflicht, ich musste monsieur Jeremy Deschamps du Mussaca einen Höflichkeitsbesuch abstatten...";
			link.l1.go = "noel_29";
		break;
		
		case "noel_29":
			dialog.text = "Dieses Treffen ist in der Tat sehr glücklich, denn ich habe lange darauf gewartet, Sie persönlich zu treffen. Ich möchte mit Ihnen sprechen, aber nicht hier.";
			link.l1 = "Lass uns dann zur Taverne gehen, oder?";
			link.l1.go = "noel_30";
		break;
		
		case "noel_30":
			DialogExit();
			FreeSitLocator("PortPax_tavern", "sit_base1");
			DoQuestReloadToLocation("PortPax_tavern", "sit", "sit_base1", "Patria_CondotierTavern");
		break;
		
		case "noel_31":
			LAi_SetSitType(pchar);
			dialog.text = "Hier gibt es keine unerwünschten Ohren, wir können sicher sprechen...";
			link.l1 = "Ich höre, Baron.";
			link.l1.go = "noel_32";
		break;
		
		case "noel_32":
			dialog.text = "Vizeadmiral, Sie scheinen ein Mann von Ehre zu sein. Ein so tapferer Marineoffizier muss einfach so sein...";
			link.l1 = "Hmm... Ich glaube, ich verstehe Sie nicht ganz, Monsieur...";
			link.l1.go = "noel_33";
		break;
		
		case "noel_33":
			dialog.text = "Herr de Maure, ich wollte Sie fragen: Was halten Sie von Ihrem Lehnsherrn, Gouverneur General Philippe de Poincy?";
			link.l1 = "Die Pflicht eines Offiziers besteht nicht darin, über seinen Kommandanten nachzudenken, sondern seinen Befehlen zu folgen.";
			link.l1.go = "noel_34";
		break;
		
		case "noel_34":
			dialog.text = "Oh, lass es, Vizeadmiral, wir sind nicht in der Kaserne und nicht im Saal de Poincys. Ich sage es so: Glaubst du nicht, dass Monsieur de Poincy... seine Macht missbraucht? Ich kann immer noch nicht vergessen, wie wir fast unter den Kanonen des Forts von Saint-Martin den Bach runtergingen. Ich bin sicher, dass der Verrat der Holländer einen Grund hatte.";
			link.l1 = "Sie wollten die Insel erobern.";
			link.l1.go = "noel_35";
		break;
		
		case "noel_35":
			dialog.text = "Ja, ja, aber warum genau in dem Moment, als ich beschloss, es zu inspizieren? Warum nicht einen Monat früher? Oder zwei Monate später? Ich glaube nicht, dass das ein Zufall war, Monseigneur. Haben Sie keine Verdächtigungen? Wir beide hatten dort unser Leben auf dem Spiel.";
			link.l1 = "Ich riskiere jeden Tag mein Leben, Monseigneur Forget. Ich denke, Sie verstehen das...";
			link.l1.go = "noel_36";
		break;
		
		case "noel_36":
			dialog.text = "Ihr Mut steht außer Zweifel. Aber das ist nicht, was ich sagen wollte. Sehen Sie... Als ich meine Arbeit auf dem von Ihnen befreiten Saint-Martin machte, hörte ich immer wieder von Einheimischen Flüstereien über eine Mine in den Tiefen der Insel. Ich versuchte, die Leute danach zu fragen, aber sie stellten sich nur dumm. Sie hatten Angst... Es war offensichtlich, dass ich nicht sehr vertrauenswürdig wirkte, aber das verstärkte nur meine Vermutungen: Könnte diese geheimnisvolle Mine der Grund für all das sein, Monsieur de Maure? Kriege werden wegen Gold geführt, habe ich recht?";
			link.l1 = "Es gibt zahlreiche Minen im Archipel. Die meisten von ihnen sind erschöpft und wertlos geworden. Ich kenne eine große, noch betriebene Goldmine, sie gehört den Spaniern auf South Main. Aber ich habe noch nie von Goldabbau auf Saint-Martin gehört.";
			link.l1.go = "noel_37";
		break;
		
		case "noel_37":
			dialog.text = "Sie sind geschickt in der Redekunst, Vizeadmiral! Ich verstehe: Sie vertrauen mir nicht. Ich bin neu hier... Monsieur de Maure, aber ich bin eine einflussreiche Person in Paris. Der Finanzminister ist mein enger Freund. Ich besuche den König regelmäßig. Meine Autorität ist weitaus größer als die von Philippe de Poincy, formal natürlich, denn hier ist der Generalgouverneur die am meisten berechtigte Person. Aber um die Wahrheit zu sagen, hier, in den Kolonien, gilt nur das Gesetz des Stärksten.";
			link.l1 = "Ich stimme Ihnen dort voll und ganz zu.";
			link.l1.go = "noel_38";
		break;
		
		case "noel_38":
			dialog.text = "Aber nicht in Paris. Dort sind die einflussreichsten Personen der König und der Finanzminister... mein enger Freund. Monsieur de Maure, Sie sind ein brillanter Militärmann, aber ich glaube, dass Phillip de Poincy Sie für seine eigenen persönlichen Zwecke benutzt. Sie sind intelligent, daher müssen Sie Verdachtsmomente haben. Sie können mir vertrauen. Ich garantiere Ihnen vollständige Anonymität und Unterstützung der Behörden von Paris. Ich schwöre bei meinem Titel.";
			link.l1 = "***BLEIBE POINCY TREU***";
			link.l1.go = "noel_39"; // развилка
			link.l2 = "***SEITE MIT BARON VERGISS***";
			link.l2.go = "noel_53";
		break;
		
		case "noel_39":
			dialog.text = "";
			link.l1 = "Ich verstehe Sie, Monsieur Forger. Für einen Mann, der mit den lokalen Denkweisen nicht vertraut ist, mögen de Poincys Handlungen tatsächlich seltsam erscheinen. Als ich zum ersten Mal im Archipel ankam, war ich buchstäblich schockiert über das, was hier geschah. Ich erinnere mich noch an die allerersten Worte, die mir gesagt wurden: 'Wenn du auf ein ungeschütztes spanisches Schiff triffst, kannst du versuchen, es zu entern.' Verrat, Betrug, Täuschung - sie sind hier an jeder Ecke präsent. Piraterie, Plünderung, Raub...";
			link.l1.go = "noel_40";
		break;
		
		case "noel_40":
			dialog.text = "";
			link.l1 = "Wir sind in Europa im Frieden mit Spanien. Aber hier sind wir erbitterte Feinde. Die Holländer scheinen heute freundlich und harmlos zu sein, und morgen konfisziert der Beamte der Kompanie deine Waren einfach, weil sie plötzlich verkündet haben, dass sie trotz deiner Unkenntnis verboten wurden. Der englische Offizier betreibt offen Piraterie, versenkt die Schiffe der Kompanie, und die Kompanie stellt einen Kehlenschlitzer ein, der sich als Geisterschiff tarnt und britische Händler erschreckt...";
			link.l1.go = "noel_41";
		break;
		
		case "noel_41":
			dialog.text = "";
			link.l1 = "In diesem Wolfsbau müssen wir manchmal seltsame Entscheidungen treffen, die für jemanden, der mit all dem nicht vertraut ist, nicht ganz offensichtlich sind. Und was dir verdächtig erscheint, ist in der Tat die einzig richtige Handlung. Es ist schwierig, auf mehreren Stühlen gleichzeitig zu sitzen und trotzdem Gewinne an den Mutterstaat zu senden. Chevalier de Poincy meistert dies perfekt, er ist ein erfahrener Manager und visionärer Politiker. Natürlich kann er Fehler machen, aber wir alle machen sie irgendwann in unserem Leben...";
			link.l1.go = "noel_42";
		break;
		
		case "noel_42":
			dialog.text = "";
			link.l1 = "Und du musst mit allem und jedem rechnen. Mit den Ambitionen der Spanier, die glauben, dass die ganze Neue Welt ihnen gehört, mit der Gier der niederländischen Händler, mit der kühlen Klugheit und rücksichtslosen Brutalität der Engländer. Und sogar mit Piraten.";
			link.l1.go = "noel_43";
		break;
		
		case "noel_43":
			dialog.text = "Mit Piraten?!";
			link.l1 = "Ja, du hast richtig gehört. Die Niederländer und die Briten kooperieren aktiv mit Piraten... natürlich inoffiziell. Die Bruderschaft der Küste ist eine ernstzunehmende Kraft, die jede Nation in der Region herausfordern kann, sie stehen in ständigem Konflikt mit jedem, dem sie begegnen, und niemand ist in der Lage, sie zu stoppen. Das einzige, was sie etwas weniger gefährlich macht, ist die Tatsache, dass sie verstreut sind und in ihrem eigenen Interesse handeln. Wusstest du, dass der ehemalige Gouverneur von Tortuga, Levasseur, tatsächlich einen Staat im Staat geschaffen hat, der sich vollständig auf Piraten stützt?";
			link.l1.go = "noel_44";
		break;
		
		case "noel_44":
			dialog.text = "Ich glaube, ich habe etwas davon gehört...";
			link.l1 = "Einige mächtige Kaperfahrer, die die Insel schützten, lagen ständig im Hafen von Tortuga. Levasseur hat Frankreich verraten und wurde zu einer Art lokaler Autorität. Und jetzt, nach der Zerstörung des Piratennestes auf Tortuga zusammen mit ihrem Meister, sind die Piraten furchtbar wütend auf die Franzosen...";
			link.l1.go = "noel_45";
		break;
		
		case "noel_45":
			dialog.text = "Das sagst du nicht!";
			link.l1 = "Ja. Wir mussten es tun, sonst wäre Tortuga für uns verloren, obwohl das Ergebnis, das wir erhielten, nicht das Beste war. Kein französisches Handelsschiff kann sich jetzt in der Karibik sicher fühlen. Die Spanier, die auch keine Vereinbarungen mit Piratenbaronen haben, verfügen zumindest über Flotten von starken Galeonen und mächtigen Kriegsschiffen, die in der Lage sind, die Filibuster abzuwehren. Wie die Holländer mit ihren Ostindischen und Xebecs. Aber wir können uns leider nicht mit so etwas rühmen. Und französische Piraten rauben oft französische Kaufleute aus.";
			link.l1.go = "noel_46";
		break;
		
		case "noel_46":
			dialog.text = "Das ist Wahnsinn! Gibt es keinen Weg, diesem ein Ende zu setzen?";
			link.l1 = "Viele haben es versucht. Am Ende kaufen sie sich ihre Loyalität mit Gold, anstatt zu kämpfen. Sie stellen Freibeuterpatente aus, meine ich.";
			link.l1.go = "noel_47";
		break;
		
		case "noel_47":
			dialog.text = "Hmm...";
			link.l1 = "Aus Erfahrung kann ich sagen, dass es eine sehr schlechte Idee wäre, hier im Archipel eine französische Handelsgesellschaft zu gründen. Verstehst du jetzt, welche Schwierigkeiten du wirst bewältigen müssen? Wie viele Bastarde wollen hier ihren Anteil am Einkommen bekommen? Und sie werden es nicht leicht aufgeben. Und Piraten, sie sind zu unvorstellbaren Dingen fähig, nenne sie verrückt wenn du willst, aber sie erreichen fast immer ihre schmutzigen Ziele. Um Handelsschiffe zu schützen, müsstest du eine massive Militärflotte unterhalten, aber wäre das aus finanzieller Sicht rentabel?";
			link.l1.go = "noel_48";
		break;
		
		case "noel_48":
			dialog.text = "Aber französische Händler kommen hier irgendwie zurecht?";
			link.l1 = "Genau, irgendwie. Besonders jetzt, wo Levasseurs Piratenfestung auf Tortuga erobert wurde...";
			link.l1.go = "noel_49";
		break;
		
		case "noel_49":
			dialog.text = "Deine Worte stimmen mit dem überein, was de Poincy gesagt hat.";
			link.l1 = "Es ist die Wahrheit. So ist es hier im Archipel, es war schon immer so.";
			link.l1.go = "noel_50";
		break;
		
		case "noel_50":
			dialog.text = "Sie sind so eifrig in dem, was Sie sagen. Sogar ich wusste nicht viel davon und, Sie haben recht: Ich weiß es immer noch nicht. Ich vermute, meine Verdächtigungen gegenüber Poincy waren ungültig. Sie haben mir die Augen geöffnet. Ich danke Ihnen, Vizeadmiral. Aber der französische Minister setzt auf die Gründung der Gesellschaft. Der König braucht das Geld...";
			link.l1 = "Ich verstehe. Aber bitte berücksichtigen Sie, was ich gerade gesagt habe, wenn die Gründung der französischen Westindischen Inseln unvermeidlich ist, dann stellen Sie bitte sicher, dass wir eine starke Militärflotte haben, um sie zu schützen.";
			link.l1.go = "noel_51";
		break;
		
		case "noel_51":
			dialog.text = "Eure Gnade ist wirklich bewundernswert, Vizeadmiral! Ein solch edler Gemütszustand! Es überrascht mich nicht, dass Ihr so lange hier gewesen seid und es nicht eilig hattet, nach Hause zurückzukehren. Aber wir werden uns wiedersehen: Ich werde in einem halben Jahr hierher zurückkehren. Die Französische Handelsgesellschaft wird aufsteigen. Und was Piraten betrifft, denke ich, Ihr übertreibt ein wenig. Alles in allem haben wir doch Kriegsschiffe und tapfere Kapitäne, wie Ihr.";
			link.l1 = "Es tut mir leid, Baron, aber ich bin nur ein Mann, und neben mir hat Frankreich nur ein starkes Schiff im Archipel 'Eclatant', es wird nicht genug sein, wir werden viel mehr verlieren als wir gewinnen werden... Eh, was auch immer, es ist was es ist, ich schätze, wir werden in der Zwischenzeit an etwas denken... Wann werden Sie nach Frankreich aufbrechen?";
			link.l1.go = "noel_52";
		break;
		
		case "noel_52":
			dialog.text = "In zwei Wochen kehre ich nach Saint Christopher zurück und von dort aus geht es nach Hause. Monsieur de Poincy hat mir ein gutes Schiff gegeben - eine Brigg namens 'Favory' und einen glorreichen Kapitän. Das Schiff ist schnell und der Kapitän ist erfahren, aber natürlich war ich bei dir sicherer. Ich erinnere mich an unsere Reisen durch den Archipel, Vizeadmiral, es war wirklich eine wunderbare Erfahrung.";
			link.l1 = "Danke für Ihre freundlichen Worte, Baron. Nun, ich denke, es ist Zeit für uns zu gehen...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierToPirates");
		break;
		
		case "noel_53":
			dialog.text = "";
			link.l1 = "Hier benutzt jeder jeden. Chevalier benutzte mich in seinen Machenschaften lange bevor ich ein Offizier der Marine wurde.";
			link.l1.go = "noel_54";
		break;
		
		case "noel_54":
			dialog.text = "Und ist das akzeptabel? Was denkst du?";
			link.l1 = "Nein. Aber der Chevalier ließ mir keine Wahl: entweder seinen Befehlen folgen, oder mein Bruder würde bis zum Ende seiner Tage hinter Gittern bleiben und der gute Name meiner Familie wäre ruiniert.";
			link.l1.go = "noel_55";
		break;
		
		case "noel_55":
			dialog.text = "Schrecklich! Das ist purer Terrorismus! Hatte er irgendeinen Grund für solche Drohungen?";
			link.l1 = "Mein Bruder hatte das Unglück, sein vertrauter Mann zu sein. Genau wie ich jetzt.";
			link.l1.go = "noel_56";
		break;
		
		case "noel_56":
			dialog.text = "Wo ist dein Bruder jetzt?";
			link.l1 = "Ich habe es geschafft, ihn zu befreien, aber ich habe ihn am nächsten Tag verloren, er hat sich entschieden, unter niemandem mehr zu dienen.";
			link.l1.go = "noel_57";
		break;
		
		case "noel_57":
			dialog.text = "Ich wusste, dass Poincy nicht der war, für den er sich ausgab! Wolf im Schafspelz! Vizeadmiral, Sie können mir vertrauen. Ich bin ein Mann der Ehre. Und ich werde Sie von diesem Joch Ihres 'Patrons' retten, wenn wir handfeste Beweise für seine kriminellen Aktivitäten finden können. Wissen Sie etwas über diese langweilige Geschichte mit Stuyvesant? Sprechen Sie offen, und machen Sie sich keine Sorgen, Sie sind nur ein Militär und mussten Ihren Befehlen folgen.";
			link.l1 = "Ich weiß. Es gibt tatsächlich eine Mine in Saint-Martin. Nur holen sie dort kein Gold, sondern Salz. Es ist bei den Spaniern sehr gefragt. Poincy konnte nicht direkt mit den Spaniern handeln, also trat Stuyvesant als Zwischenhändler auf.";
			link.l1.go = "noel_58";
		break;
		
		case "noel_58":
			dialog.text = "So sind Poincy und Stuyvesant Geschäftspartner?";
			link.l1 = "War früher so. Nachdem du den Wunsch geäußert hast, die Saint-Martin zu inspizieren, hat sich Stuyvesant entschlossen, Poincy aus dem Spiel zu werfen und alle Gewinne aus dem Salzbergwerk selbst einzunehmen. Poincy konnte niemandem etwas sagen... Aber wie wir sehen, hat Stuyvesant sich verrechnet.";
			link.l1.go = "noel_59";
		break;
		
		case "noel_59":
			dialog.text = "Glaubst du, dass die Mine weiterhin in Betrieb ist?";
			link.l1 = "Ich bin mir sicher. Es scheint, dass Poincy jetzt einen neuen Handelsverbündeten hat. Es ist niemand anderes als Oberst Doily selbst.";
			link.l1.go = "noel_60";
		break;
		
		case "noel_60":
			dialog.text = "Können wir dem Ministerium irgendwelche Beweise vorlegen?";
			link.l1 = "Hmm. Während der Stürmung der Mine, die übrigens von Spaniern und nicht von Holländern durchgeführt wurde, haben wir den Besitzer gefangen genommen. Er ist noch auf meinem Schiff. Du kannst mit ihm sprechen. Es besteht die Chance, dass er im Austausch für Freiheit viele interessante Dinge erzählen wird.";
			link.l1.go = "noel_61";
		break;
		
		case "noel_61":
			dialog.text = "Lass uns sofort zu deinem Schiff gehen. Befiehl, dass dein Gefangener in deine Kabine gebracht wird. Ich werde mit ihm reden.";
			link.l1 = "Gut, lass uns gehen.";
			link.l1.go = "exit";
			npchar.greeting = "noel_4";
			AddDialogExitQuestFunction("Patria_CondotierToCabin");
		break;
		
		case "noel_62":
			dialog.text = "Großartig, Vizeadmiral. Ich werde ein Gespräch mit ihm führen. Bleiben Sie bitte hier.";
			link.l1 = "Natürlich...";
			link.l1.go = "noel_63";
		break;
		
		case "noel_63":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "rld", "aloc1", "", -1);
			DoQuestFunctionDelay("Patria_CondotierInCabinTalk", 3.0);
		break;
		
		case "noel_64":
			dialog.text = "Ich habe alle Beweise deiner Gefangenen aufgeschrieben und er hat sie unterschrieben. Jetzt müssen wir erfüllen, was ich ihm versprochen habe, wann immer sich eine günstige Gelegenheit bietet, stoppe in Cartagena und lasse ihn aussteigen. Aber du hast selbst alles gehört\nWas für ein Schurke unser Poincy ist! Hatte eine Insel an die Holländer vermietet, dort illegale Aktivitäten durchgeführt und den Spaniern erlaubt, dort zu gehen und die Mine zu verwalten! Ich wage nicht zu denken, wie viel Geld der königlichen Schatzkammer wegen seiner Selbstsucht fehlt!";
			link.l1 = "Wird dieses Beweismaterial ausreichen, um Poincy anzuklagen?";
			link.l1.go = "noel_65";
		break;
		
		case "noel_65":
			dialog.text = "Leider fürchte ich, es wird nicht klappen. Die Beweise sind sehr wichtig, aber sie reichen nicht aus. Aber ich möchte nicht, dass du aus Gründen, die wir beide verstehen, in all das verwickelt bist.";
			link.l1 = "Der Spanier stimmte zu, vor deiner Kommission auszusagen, wenn sie hier eintrifft.";
			link.l1.go = "noel_66";
		break;
		
		case "noel_66":
			dialog.text = "Dies wird nicht früher als in sechs Monaten geschehen, und wer weiß, was aus diesem Spanier wird, und ob wir ihn später in Cartagena finden können... Wir brauchen noch wertvollere Beweise. Nämlich - einen Beweis dafür, dass die Mine ihre geheimen Aktivitäten fortsetzt und immer noch die Taschen unseres lieben Gouverneursgenerals füllt.";
			link.l1 = "Also schlägst du vor, dass wir nach Saint-Martin reisen?";
			link.l1.go = "noel_67";
		break;
		
		case "noel_67":
			dialog.text = "Ja. Wissen Sie, wie man zur Mine kommt?";
			link.l1 = "Ich tue es.";
			link.l1.go = "noel_68";
		break;
		
		case "noel_68":
			dialog.text = "Dann, nachts, werden wir dort hineinschleichen, leise, sodass niemand uns sieht, und wir werden überprüfen, was dort vor sich geht.";
			link.l1 = "Sehr gut.";
			link.l1.go = "noel_69";
		break;
		
		case "noel_69":
			dialog.text = "Aber was ist mit dem Chevalier, hm? Jetzt verstehe ich, warum er mir mit solchem Mut angedeutet hat, dass die Gründung der Französischen Handelsgesellschaft auf dem Archipel unrentabel wäre... Natürlich, es wäre sehr unrentabel für ihn!";
			link.l1 = "Da wir nun Verbündete sind, Baron, werde ich Ihnen die ganze Wahrheit sagen, Poincy hat mich gebeten... Sie davon zu überzeugen, dass Sie hier keine Handelsgesellschaft gründen.";
			link.l1.go = "noel_70";
		break;
		
		case "noel_70":
			dialog.text = "So ist das also! Ich hoffe, dass er dich zumindest nicht gebeten hat, mich mit einem Schwert oder einer Pistole zu beseitigen?";
			link.l1 = "Nein. Du musstest auf eine andere Weise überzeugt werden.";
			link.l1.go = "noel_71";
		break;
		
		case "noel_71":
			dialog.text = "Poincy wird dafür bezahlen, aber jetzt müssen wir sofort nach Saint-Martin segeln. Der Spanier wird danach nach Main geliefert. Wir brechen auf, Vizeadmiral!";
			link.l1 = "Es wird ein bisschen seltsam erscheinen, dass du die Insel auf meinem Schiff verlassen wirst, denkst du nicht?";
			link.l1.go = "noel_72";
		break;
		
		case "noel_72":
			dialog.text = "Glaube nicht. Solltest du mich nicht überzeugen? Genau das hast du getan, haha! Ja, bevor ich nach Europa segeln, werde ich dem Chevalier sagen, dass ich seinen Punkten zustimme und die Handelsgesellschaft wird nicht gegründet. Lass ihn in seliger Frieden einer Lüge leben, für jetzt... Los geht's!";
			link.l1 = "...";
			link.l1.go = "noel_73";
		break;
		
		case "noel_73":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierToSMartin", 5.0);
		break;
		
		case "noel_74":
			dialog.text = "Führen Sie den Weg, Vizeadmiral. Die Nacht wird uns mit ihrem Schleier der Dunkelheit verbergen.";
			link.l1 = "Folge mir...";
			link.l1.go = "noel_75";
		break;
		
		case "noel_75":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.Patria_Condotier_inMine.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_inMine.win_condition.l1.location = "Location_reserve_03";
			pchar.quest.Patria_Condotier_inMine.function = "Patria_CondotierInMine";
		break;
		
		case "noel_76":
			dialog.text = "(flüstert) Ich habe es gesehen! Ich habe es gesehen! Hast du es gesehen? Rotröcke! Das sind englische Soldaten!";
			link.l1 = "Ich habe es dir gesagt - Poincy macht jetzt Geschäfte mit Oberst Doily.";
			link.l1.go = "noel_77";
		break;
		
		case "noel_77":
			dialog.text = "Du hattest recht. Ich habe genug gesehen. Jetzt lass uns hier so schnell wie möglich raus, bevor wir entdeckt werden!";
			link.l1 = "Einverstanden...";
			link.l1.go = "noel_78";
		break;
		
		case "noel_78":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload2_back", "Patria_CondotierToBeach", -1);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		case "noel_79":
			dialog.text = "Sie sehen, wohin die 'kommerziellen Projekte' unseres lieben Chevaliers führen! Die Engländer benehmen sich wie Gastgeber auf einer französischen Insel! Das ist empörend!";
			link.l1 = "Wir müssen uns bewegen, oder jemand wird definitiv hierher kommen. Wir können es uns nicht leisten, erkannt zu werden.";
			link.l1.go = "noel_80";
		break;
		
		case "noel_80":
			dialog.text = "Vizeadmiral, während unserer Reise nach Saint-Martin habe ich die ganze Zeit nachgedacht und mich für etwas entschieden: könnten Sie mir ein Treffen mit Peter Stuyvesant arrangieren?";
			link.l1 = "Mit Stuyvesant? Aber warum?";
			link.l1.go = "noel_81";
		break;
		
		case "noel_81":
			dialog.text = "Ein ehemaliger Geschäftspartner könnte einige ernsthafte Hinweise und ernsthafte Beweise für die Beteiligung der Chevaliers haben. Ich bin mir sicher, dass Stuyvesant mit Poincy nicht sehr zufrieden ist und Rache suchen wird, insbesondere nach diesen jüngsten Ereignissen...";
			link.l1 = "Ich glaube schon, Baron. Ich persönlich würde es nicht wagen, zum Palast der Stuyvesants zu gehen. Es ist mir zu riskant, nach allem, was ich ihnen angetan habe...";
			link.l1.go = "noel_82";
		break;
		
		case "noel_82":
			dialog.text = "Ich habe bereits darüber nachgedacht. Wir werden nach Curacao gehen, in einer Bucht weit entfernt von der Stadt anlanden und unseren gefangenen Spanier aus der Mine mit einem Brief an Stuyvesant schicken. Ich werde dich dort nicht erwähnen, stattdessen werde ich ihm mitteilen, dass ich eine Untersuchung gegen Poincy oder so etwas in der Art führe. Ich denke, der Holländer wird zum Rendezvous kommen.";
			link.l1 = "Hmm. Ich denke nicht, dass das eine gute Idee ist. Der Stuyvesant ist kein Narr, er nimmt, was er kann, er könnte sogar versuchen, dich zu inhaftieren und ein riesiges Lösegeld zu verlangen, aber wenn wir ihn glauben lassen, dass all das wegen Poincy passiert ist, könnte er sich auf unsere Seite stellen. Nun, wenn du so entschlossen bist, lass es uns versuchen.";
			link.l1.go = "noel_83";
		break;
		
		case "noel_83":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Shore40", "reload1_back", false);
			LocatorReloadEnterDisable("Shore40", "boat", false);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_LocationDisableOfficersGen("shore40", false);
			LAi_LocationDisableOfficersGen("Location_reserve_01", false);
			LAi_LocationDisableOfficersGen("Location_reserve_03", false);
			pchar.quest.Patria_CondotierCuracao.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCuracao.win_condition.l1.location = "shore22";
			pchar.quest.Patria_CondotierCuracao.function = "Patria_CondotierOnCuracao";
			AddQuestRecord("Patria", "81");
		break;
		
		case "noel_84":
			dialog.text = "Herr de Maure, bitte verzeihen Sie meine Dummheit. Sie hatten recht mit Stuyvesant. Ich hätte ahnen müssen, dass nur ein noch größerer Schurke de Poincy herausfordern könnte!";
			link.l1 = "Hah! Eine Million... Poincy wollte eine Million, Stuyvesant will eine Million... Es scheint, als würden wir uns im Kreis bewegen...";
			link.l1.go = "noel_85";
		break;
		
		case "noel_85":
			dialog.text = "Wovon sprechen Sie, Vizeadmiral?";
			link.l1 = "Als ich in die Karibik kam, wollte Poincy, dass ich eine Million als Lösegeld für meinen Bruder zahle.";
			link.l1.go = "noel_86";
		break;
		
		case "noel_86":
			dialog.text = "Und du hast so viel bezahlt?";
			link.l1 = "Ich habe es verdient und ich habe es bezahlt. Nicht in einem Monat, natürlich. Ehrlich gesagt, war ich damals nur ein Landratte. Trotzdem ließ Chevalier Michel nicht gehen.";
			link.l1.go = "noel_87";
		break;
		
		case "noel_87":
			dialog.text = "Und danach hast du dich verpflichtet, für Poincy zu arbeiten? Ich verstehe dich wirklich nicht.";
			link.l1 = "Ich trat in den Dienst Frankreichs und derer, die ich liebe, ich verneige mich vor niemandem außer dem König.";
			link.l1.go = "noel_88";
		break;
		
		case "noel_88":
			dialog.text = "Entschuldigen Sie, Monsieur de Maure. Natürlich dienen Sie Frankreich und dem König! Poincy wird für alles zur Rechenschaft gezogen werden! Einschließlich all des Schmerzes, den er Ihnen zugefügt hat.";
			link.l1 = "Sehr gut, Baron, ich werde eine Million finden, die ich entbehren kann. Steigen Sie an Bord ... Ich werde dieses Problem lösen.";
			link.l1.go = "noel_89";
		break;
		
		case "noel_89":
			DialogExit();
			//chrDisableReloadToLocation = false; //17-add
			LAi_LocationFightDisable(&Locations[FindLocation("shore22")], false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 10.0);
			pchar.questTemp.Patria = "epizode_12_stivesant";
			AddQuestRecord("Patria", "83");
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Patria_CondotierStivesantTimeOver", 0, 0, 30, false); // таймер на месяц
		break;
		
		case "noel_90":
			dialog.text = "Sie wollten mich treffen, Vizeadmiral?";
			link.l1 = "Ja. Ich hatte ein Treffen mit Stuyvesant. Hier ist sein Hauptbuch.";
			link.l1.go = "noel_91";
		break;
		
		case "noel_91":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Ich kann es nicht glauben! Hmm, lass uns sehen... (liest)";
			link.l1 = "...";
			link.l1.go = "noel_92";
		break;
		
		case "noel_92":
			LAi_Fade("", "");
			dialog.text = "Das ist es! Unser lieber Chevalier ist verloren. Sobald all diese Buchführung vom Finanzminister gesehen wird... Ich kann mir gar nicht vorstellen, was mit ihm passieren wird. Wir werden nicht einmal den Spanier aus Cartagena suchen müssen. Monsieur de Maure, haben Sie wirklich eine Million für dieses Buch bezahlt?";
			link.l1 = "Ich habe es getan. Wenn ich etwas anderes versuchen würde, könnte Frankreich aufgrund eines Bürgerkriegs seine Kolonien in der Karibik verlieren, den ich gewinnen könnte, aber was für ein Admiral wäre ich, wenn ich gegen mein eigenes Volk kämpfen würde.";
			link.l1.go = "noel_93";
		break;
		
		case "noel_93":
			dialog.text = "Sie sind wirklich Ihrer Name würdig. Ich schwöre Ihnen, Vizeadmiral, dass Sie ihn zurückbekommen werden. Ich bin sicher, dass wir in Poincys Kisten und bei seinen Wucherern einen beachtlichen Geldbetrag finden werden. Ich bitte Sie nur, sechs Monate zu warten, bis ich mit einer Kommission aus Europa zurückkehre.";
			link.l1 = "Und vergiss nicht, ein Regiment gut ausgebildeter und bewaffneter Soldaten mitzubringen. Und ein Schiff wie das 'Eclatant'. Ich glaube auch, dass der Kapitän des 'Eclatant' auf unserer Seite stehen wird, wenn die Zeit gekommen ist.";
			link.l1.go = "noel_94";
		break;
		
		case "noel_94":
			dialog.text = "Zweifeln Sie nicht daran, er ist auch ein ehrenhafter Mann. Ich habe erkannt, dass moralische Werte bei der Entscheidungsfindung eine große Rolle spielen. Sie haben hervorragende Arbeit geleistet, dass Sie mir vertraut und diesen Staatsverbrecher entlarvt haben. Jetzt bringen Sie mich nach Capsterville, wo ich Poincy über den Erfolg Ihrer Mission berichten werde - Sie haben es geschafft, mich zu überzeugen, und ich werde die Idee der Gründung der Handelsgesellschaft aufgeben. Vielleicht wird Poincy Sie sogar dafür belohnen - nehmen Sie die Belohnung mit reinem Gewissen an und sorgen Sie sich um nichts, Sie von allen Menschen haben es verdient. Sie werden nicht in dies hineingezogen, und Ihr Name wird nicht mit den Vergehen Ihres Vorgesetzten befleckt sein, tatsächlich werde ich nur das Beste über Sie sagen, wenn ich den König treffe. Baron Forget ist ein Mann der Ehre und ein Mann seines Wortes.";
			link.l1 = "Ich bin froh, Baron. Lass uns aufbrechen!";
			link.l1.go = "noel_95";
		break;
		
		case "noel_95":
			DialogExit();
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;//открыть карту
			Island_SetReloadEnableGlobal("Curacao", true);
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
			pchar.questTemp.Patria = "epizode_12_baronwin";
			AddQuestRecord("Patria", "85");
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_CondotierBaron_win.function = "Patria_CondotierBaronWin";
		break;
		
		case "noel_96":
			dialog.text = "So, Vizeadmiral, wir sind endlich angekommen. Ihre Mission ist vorbei, jetzt liegt es an mir. Kümmern Sie sich um Ihre eigenen Angelegenheiten, verteidigen Sie die Interessen Frankreichs, wie Sie es bisher getan haben. In etwa sechs Monaten wird diese abscheuliche Geschichte ein Ende finden. Ich werde den Kurier schicken, um Sie zu finden, wenn Sie gebraucht werden. Lebewohl, Monsieur de Maure, ich hatte großes Glück, hier einen ehrenhaften Mann zu treffen! Der Minister und der König werden von Ihnen hören, das verspreche ich. Und sie werden nur das Beste hören.";
			link.l1 = "Danke, Baron. Gute Reise!";
			link.l1.go = "noel_97";
		break;
		
		case "noel_97":
			DialogExit();
			AddQuestRecord("Patria", "86");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		case "noel_98":
			dialog.text = "Freut mich, Sie zu sehen, Vizeadmiral. Ich bin wie versprochen wieder hier. Und mit mir - der erste Assistent des Finanzministers, Baron Olivier Bourdin.";
			link.l1 = "Wo ist Chevalier de Poincy?";
			link.l1.go = "noel_99";
		break;
		
		case "noel_99":
			dialog.text = "Wo er hingehört, im Gefängnis. Er wurde verhaftet und wird zur Untersuchung und Prozess nach Frankreich gebracht. Aufgrund seiner Position wird er sicherlich der Hinrichtung entgehen, aber einer hohen Geldstrafe, Degradierung und wahrscheinlich Gefängnis kann er nicht entkommen.";
			link.l1 = "War die Verhaftung friedlich?";
			link.l1.go = "noel_100";
		break;
		
		case "noel_100":
			dialog.text = "Nicht wirklich. Der Chevalier hatte hier, in der Residenz, eine ganze Garde treuer Soldaten. Aber wir waren im Voraus auf eine solche Eskalation vorbereitet.";
			link.l1 = "Nun, dann gratuliere ich Ihnen, Baron! Vielleicht werden Sie sich jetzt mit der französischen Handelsgesellschaft befassen?";
			link.l1.go = "noel_101";
		break;
		
		case "noel_101":
			dialog.text = "Ich? Ja. Seine Gnade Monsieur Bourdin - wird zusammen mit Chevalier de Poincy nach Frankreich zurückkehren. Und Sie, Vizeadmiral, sollten auch einige Änderungen erwarten. Jetzt haben Sie eine neue Position. Seine Gnade wird Ihnen mehr erzählen.";
			link.l1 = "...";
			link.l1.go = "noel_102";
		break;
		
		case "noel_102":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Finansist");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_103":
			dialog.text = "Herr de Maure! Warten Sie eine Minute!";
			link.l1 = "Ja, Baron. Ich höre.";
			link.l1.go = "noel_104";
		break;
		
		case "noel_104":
			dialog.text = "Was die Million betrifft, die Sie den Stuyvesant bezahlt haben... Ich habe dem Ministerium nichts davon erzählt, um... Fragen zu vermeiden, wie ein französischer Offizier zu so viel Geld gekommen ist. Dies könnte Ihnen geschadet haben, da sie Sie wahrscheinlich bitten würden, die königliche Schatzkammer mit Ihrem eigenen zu erhöhen.";
			link.l1 = "Ich verstehe, danke.";
			link.l1.go = "noel_105";
		break;
		
		case "noel_105":
			dialog.text = "Das gesamte Geld, das sich im Besitz von Poincy in Casterville befand, wurde vom Baron Bourdin beschlagnahmt. Aber wie sich herausstellt, hatte Poincy auch ein Versteck, das die englischen Geldverleiher für ihn verbargen. Ich werde mit ihm über die Rückgabe der Investitionen sprechen und dann einen Weg finden, Sie zu entschädigen.";
			link.l1 = "Ich fürchte, es wird nicht leicht für dich sein, etwas aus den Händen der englischen Geldverleiher zu nehmen.";
			link.l1.go = "noel_106";
		break;
		
		case "noel_106":
			dialog.text = "Ich stimme zu. Aber wir werden daran arbeiten, und ich werde Sie über die Ergebnisse auf dem Laufenden halten.";
			link.l1 = "Wie du wünschst.";
			link.l1.go = "noel_107";
		break;
		
		case "noel_107":
			dialog.text = "Vizeadmiral, Sie sehen nicht so gut aus, oder bilde ich mir das nur ein? Sie haben gerade erst den höchsten Posten in den Kolonien erhalten!";
			link.l1 = "Nein-nein, überhaupt nicht... Es ist nur so, dass alles so unerwartet passiert ist, und ich bin ein wenig verloren.";
			link.l1.go = "noel_108";
		break;
		
		case "noel_108":
			dialog.text = "Mach dir keine Sorgen. Du wirst dich an deine neue Position gewöhnen. Und außerdem, du warst ein halbes Jahr lang recht erfolgreich als Gouverneur von Saint-Martin, also wird es nichts Neues für dich sein.";
			link.l1 = "Oh, ich bin sicher, dass ich mich daran gewöhnen werde. Ich war schon in schlimmeren Situationen während meiner Zeit hier in der Karibik. Ich denke, ich werde auch diese Situation meistern.";
			link.l1.go = "noel_109";
		break;
		
		case "noel_109":
			// belamour legendary edition -->
			dialog.text = "Nun, gut. Außerdem habe ich noch eine Überraschung für dich. Ich bin sicher, es wird dir gefallen. Aber zuerst bitte ich dich, zur Residenz zurückzukehren. Ich glaube, dort wartet jemand auf uns.";
			link.l1 = "Sie haben mich fasziniert, Monsieur Forget. Nun, lass uns zurückgehen.";
			link.l1.go = "noel_110";
		break;
		
		case "noel_110":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "ToEcliatonAward", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "noel_111":
			dialog.text = "Es ist alles in Ordnung, Marquis. Ein echter Kapitän sollte immer zuerst auf sein Schiff achten, nicht wahr? Charles, erinnerst du dich an Marquis Hubert Dassier, Kapitän des Schlachtschiffs 'Eclatant'?";
			link.l1 = "Natürlich erinnere ich mich! Ohne ihn wäre ich heute nicht mehr am Leben. Die stärkste Freundschaft zwischen Seeoffizieren entsteht durch gemeinsam geschlagene Schlachten. Und Monsieur Dassier stellte sich als unglaublich erfahrener Kapitän heraus.";
			link.l1.go = "noel_112";
		break;
		
		case "noel_112":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_113":
			dialog.text = "Vizeadmiral, ich habe die Ehre, Ihnen folgendes mitzuteilen. Neben Ihrer Ernennung zum amtierenden Generalgouverneur der französischen Kolonien im Archipel habe ich auch die Frage Ihres Flaggschiffs angesprochen.";
			link.l1 = "Flaggschiff?";
			link.l1.go = "noel_114";
		break;
		
		case "noel_114":
			dialog.text = "Genau. Soweit ich weiß, haben Sie bei Ihrem Eintritt in den Dienst Frankreichs die leichte Fregatte 'Gryffondor' zur Verfügung gestellt bekommen. Zweifellos ist dies ein wunderbares Schiff, aber es ist nur für einen Offizier und nicht für einen Vizeadmiral und jetzt einen Generalgouverneur geeignet. Sie sind das Gesicht Frankreichs hier. Und Ihr Flaggschiff sollte angemessen sein. Daher haben wir beschlossen, dass das Schiff, das hier in der Karibik seine ersten Schlachten geschlagen hat, in Ihr Geschwader aufgenommen wird...";
			link.l1 = "Herr Forget, versuchen Sie zu sagen...";
			link.l1.go = "noel_115";
		break;
		
		case "noel_115":
			dialog.text = "Von nun an steht Ihnen der Stolz der französischen Marine, das 66-Kanonen-Kriegsschiff 'Eclatant', zur Verfügung! Diese Entscheidung wird vom König gebilligt!";
			link.l1 = "Aber Baron, ich kann nicht einfach nehmen...";
			link.l1.go = "noel_116";
		break;
		
		case "noel_116":
			dialog.text = "Du kannst, Charles. Darüber wird nicht diskutiert. In Frankreich wurde die 'Eclatant' speziell für dich ein wenig aufgerüstet, weil sich herausstellte, dass es in der Karibik keine so großen Seeschlachten gibt wie in Europa, und daher sind die Anforderungen an einzelne Schiffe höher. Hier wird alles durch die Eigenschaften des Schiffes und die Erfahrung seines Kapitäns entschieden. Die 'Eclatant' hatte ihren Rumpf verstärkt, das Gewicht erhöht und die Besatzungsgröße erhöht, das Segelrigging leicht umgerüstet, um schärfere Kurse zu ermöglichen, und auch alle Kanonen vollständig durch zweiundvierzig Kaliber ersetzt, das sind die stärksten Kanonen, die wir haben.";
			link.l1 = "Ja, jetzt ist dieses Schiff einfach der Herr der Meere... Aber Monsieur Forget, denn der Kapitän dieses Schiffes ist Marquis Hubert Dassier. Ich kann es ihm nicht wegnehmen...";
			link.l1.go = "noel_117";
		break;
		
		case "noel_117":
			dialog.text = "Es ist nur so, dass ich Ihnen noch nicht erzählt habe, dass der Marquis selbst den starken Wunsch geäußert hat, unter Ihrem Kommando zu dienen... Monsieur Dassier?";
			link.l1 = "...";
			link.l1.go = "noel_118";
		break;
		
		case "noel_118":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_119":
			dialog.text = "Ja, Monsieur Dassier, ich glaube, wir werden Sie nicht länger aufhalten.";
			link.l1 = "..., Freund.";
			link.l1.go = "noel_120";
		break;
		
		case "noel_120":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			sld = characterFromId("Ecliaton_Cap");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "EcliatonAwardNoelTalk", -1);
		break;
		
		case "noel_121":
			dialog.text = "Zwischen uns, Charles, würde ich Ihnen dringend raten, den Marquis in Ihren Diensten zu lassen. Ich versichere Ihnen, Sie werden keinen so erfahrenen Kapitän finden.";
			link.l1 = "Glauben Sie mir, Baron, ich hatte die Ehre, dies persönlich während der Kämpfe gegen Spanien und Holland zu sehen. Monsieur Dassier ist in der Tat ein ausgezeichneter Kampfoffizier und auch mein Freund.";
			link.l1.go = "noel_122";
		break;
		
		case "noel_122":
			dialog.text = "Nun, erlauben Sie mir nun, Eure Gnaden, Generalgouverneur! Dinge können nicht warten: die Arbeit an einer Handelsgesellschaft beginnt am ersten Tag ihrer Gründung. Bis bald!";
			link.l1 = "Viel Glück, Monsieur Forget. Und viel Glück bei Ihren Handelsbemühungen!";
			link.l1.go = "noel_123";
		break;
		
		case "noel_123":
			DialogExit();
			// ставим Эклятон после апгрейда в Европе
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_24";
			sld.DeckDialogNode = "ecliaton_cap_24";
			sld.Ship.Type = GenerateShipExt(SHIP_ECLIATON, true, sld);
			SetBaseShipData(sld);
			sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS42;
			UpgradeShipFull(sld);
			/* UpgradeShipParameter(sld, "SpeedRate");
			UpgradeShipParameter(sld, "TurnRate");
			UpgradeShipParameter(sld, "WindAgainstSpeed");
			UpgradeShipParameter(sld, "HP");
			UpgradeShipParameter(sld, "MaxCrew");
			sld.ship.HP = 11880; */
			sld.Ship.name = "Ecliaton";
			SetCrewQuantityFull(sld);
			AddCrewMorale(sld, 100);
			ChangeCrewExp(sld, "Sailors", 100);
			ChangeCrewExp(sld, "Cannoners", 100);
			ChangeCrewExp(sld, "Soldiers", 100);
			SetCharacterGoods(sld, GOOD_BALLS, 6000);
			SetCharacterGoods(sld, GOOD_GRAPES, 2000);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 2000);
			SetCharacterGoods(sld, GOOD_BOMBS, 5000);
			SetCharacterGoods(sld, GOOD_FOOD, 4000);
			SetCharacterGoods(sld, GOOD_POWDER, 12000);
			SetCharacterGoods(sld, GOOD_WEAPON, 900);
			SetCharacterGoods(sld, GOOD_MEDICAMENT, 900);
			SetCharacterGoods(sld, GOOD_RUM, 200);
			SetCharacterGoods(sld, GOOD_PLANKS, 100);
			SetCharacterGoods(sld, GOOD_SAILCLOTH, 100);
			Group_AddCharacter("Ecliaton_group", "Ecliaton_Cap");
			Group_SetGroupCommander("Ecliaton_group", "Ecliaton_Cap");
			Group_SetAddress("Ecliaton_group", "Nevis", "quest_ships", "quest_ship_1");
			Group_SetTaskNone("Ecliaton_group");
			Group_LockTask("Ecliaton_group");
			
			bDisableFastReload = false;//открыть переход
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Patria", "90");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.GenGovernor = "true"; // Шарль генерал-губернатор
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			DoQuestReloadToLocation("Charles_Town", "reload", "reload3", "OpenTheDoors");
		break;
		// <-- legendary edition
		
		case "noel_final":
			dialog.text = "Erlauben Sie mir, meine aufrichtigste Wertschätzung für Sie, Vizeadmiral, auszudrücken! Sie haben mein Leben gerettet, indem Sie mich von diesen verdammten Piraten befreit haben. Ich danke Ihnen, sowie Philippe de Poincy. Ich muss zugeben, ich lag völlig falsch in meinem Urteil über ihn, und ich bitte Sie, mir das zu vergeben. Sie und der Ritter hatten recht: die französische Handelsgesellschaft wird hier viele Probleme haben, und es sieht so aus, als würden wir hier nur Geld verlieren.\nNur erfahrene Leute, wie Poincy, und so mutige Soldaten wie Sie, können diesen Wölfen widerstehen, die auf jeder Insel hier leben. Ich muss zum Palast gehen, und danach werde ich so schnell wie möglich nach Europa abreisen und diesen Alptraum vergessen.";
			link.l1 = "Ich freue mich, dass alles gut ausgegangen ist, Baron. Auf Wiedersehen!";
			link.l1.go = "noel_final_1";
		break;
		
		case "noel_final_1":
			DialogExit();
			AddQuestRecord("Patria", "76");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		// капитан Эклятона
		case "ecliaton_cap":
			dialog.text = TimeGreeting()+", Monsieur. Was bringt Sie an Deck der 'Eclatant'?";
			link.l1 = TimeGreeting()+", Monsieur. Lassen Sie mich mich vorstellen - Kapitän Charles de Maure, ich komme vom Generalgouverneur der französischen Kolonien im Archipel, Chevalier de Poincy. Mir wurde befohlen, Ihr Schiff in meine Staffel und unter mein Kommando zu nehmen. Hier ist der Brief...";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) link.l1.go = "ecliaton_cap_1";
			else link.l1.go = "ecliaton_cap_no";
		break;
		
		case "ecliaton_cap_no":
			dialog.text = "Es handelt sich um einen Irrtum, Monsieur. Sie befinden sich auf einem Linienschiff der französischen Marine, und ich höre nur auf Befehle von denen, die der Königlichen Marine dienen. Und Sie scheinen keine Anzeichen oder Zugehörigkeit zu dieser Flotte zu haben. Vielleicht verwechseln Sie unser Schiff mit einem anderen.";
			link.l1 = "Aber...";
			link.l1.go = "ecliaton_cap_no_1";
		break;
		
		case "ecliaton_cap_no_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_no_2";
		break;
		
		case "ecliaton_cap_no_2":
			if(IsUniformEquip())
			{
				dialog.text = "Huch, ich habe Sie nicht einmal in dieser Uniform erkannt, Kapitän. Nun, lassen Sie mich Ihren Brief sehen, ich möchte den Inhalt durchsehen.";
				link.l1 = "Hier.";
				link.l1.go = "ecliaton_cap_1";
			}
			else
			{
				dialog.text = "Wir haben bereits alles besprochen, Monseigneur...";
				link.l1 = "Hmm...";
				link.l1.go = "ecliaton_cap_no_1";
			}
		break;
		
		case "ecliaton_cap_1":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Nun, mal sehen... (liest) Interessant. Also, ich und mein Schiff sollen unter deinem Kommando stehen, Kapitän de Maure?";
			link.l1 = "Das ist der Befehl des Generalgouverneurs.";
			link.l1.go = "ecliaton_cap_2";
		break;
		
		case "ecliaton_cap_2":
			dialog.text = "Ja-ja, Befehle sind nicht zu hinterfragen. Sehr wohl. Lassen Sie mich mich vorstellen: Ich bin Marquis Hubert Dassier, Kapitän des 66-Kanonen-Linienschiffs der französischen Marine namens 'Eclatant', zusammen mit dieser gut ausgebildeten Besatzung, und ich schwöre auf meine Ehre, es ist eines der besten Schiffe, die Frankreich je hatte.";
			link.l1 = "Froh das zu hören, da die Aufgabe, die uns vom Generalgouverneur zugewiesen wurde, gute Kenntnisse in Navigation und Artillerie erfordern wird.";
			link.l1.go = "ecliaton_cap_3";
		break;
		
		case "ecliaton_cap_3":
			dialog.text = "Werden Sie mir die Einzelheiten dieser bevorstehenden Operation erzählen?";
			link.l1 = "Natürlich. Wir werden zur spanischen Insel Trinidad ziehen, die etwa eine Woche Reise südöstlich von hier entfernt liegt. Wir werden das Fort, das die Kolonie San Jose bewacht, unvermittelt angreifen und es in Grund und Boden rennen. Dann werden wir mit den Spaniern über unsere Entschädigung für den jüngsten Angriff auf die französische Siedlung Saint-Pierre sprechen.";
			link.l1.go = "ecliaton_cap_4";
		break;
		
		case "ecliaton_cap_4":
			dialog.text = "Ich verstehe. Wann brechen wir auf?";
			link.l1 = "So schnell wie möglich. Wir müssen diese Aufgabe in einem Monat abschließen, also haben wir mehr als genug Zeit.";
			if (GetCompanionQuantity(pchar) > 4) link.l1.go = "ecliaton_cap_5_1";
			else link.l1.go = "ecliaton_cap_5";
		break;
		
		case "ecliaton_cap_5":
			dialog.text = "In Ordnung, Kapitän de Maure. Wir werden auf Ihren Befehl hin ablegen.";
			link.l1 = "";
			link.l1.go = "ecliaton_cap_6";
		break;
		
		case "ecliaton_cap_6":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_AddEcliaton();
		break;
		
		case "ecliaton_cap_wait":
			dialog.text = "Haben Sie Befehle oder vielleicht Fragen, Kapitän de Maure?";
			link.l1 = "Noch nicht...";
			link.l1.go = "ecliaton_cap_wait_1";
		break;
		
		case "ecliaton_cap_wait_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
		break;
		
		case "ecliaton_cap_5_1":
			dialog.text = "Aber, Kapitän de Maure, zuerst müssen Sie Ihre Staffel verkleinern - mein Schiff kann sich Ihnen nicht anschließen, sonst wäre es eine zu große Staffel.";
			link.l1 = "Hmm. Du hast recht. Ich werde ein Schiff hier im Hafen lassen.";
			link.l1.go = "ecliaton_cap_5_2";
		break;
		
		case "ecliaton_cap_5_2":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_5_3";
		break;
		
		case "ecliaton_cap_5_3":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Haben Sie Ihr Geschwader noch nicht kleiner gemacht, Monsieur?";
				link.l1 = "Ja-ja, ich erinnere mich, ich arbeite dran.";
				link.l1.go = "ecliaton_cap_5_2";
			}
			else
			{
				dialog.text = "So ist es, die 'Eclatant' ist bereit, sich Ihrem Geschwader anzuschließen, Monsieur.";
				link.l1 = "Dann werde ich zu meinem Schiff gehen, und du solltest dich darauf vorbereiten, das Meer zu betreten.";
				link.l1.go = "ecliaton_cap_5";
			}
		break;
		
		case "ecliaton_cap_7":
			dialog.text = "Grüße, Kommodore. Haben wir eine weitere Schlacht vor uns?";
			link.l1 = "In der Tat tun wir das. Wieder einmal vereinen wir unsere Kräfte. Wir werden Philipsburg stürmen. Der Generalgouverneur hat uns beauftragt, die Niederländer von Saint-Martin zu vertreiben.";
			link.l1.go = "ecliaton_cap_9";
			link.l2 = "Wir tun es Kapitän, aber etwas später. Ich werde dir sagen wann. Die 'Eclatant' muss bereit sein, jederzeit das Meer zu betreten.";
			link.l2.go = "ecliaton_cap_8";
		break;
		
		case "ecliaton_cap_8":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_7";
			npchar.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "ecliaton_cap_9":
			dialog.text = "Alles ist klar. Es wird eine harte Mission, Monseigneur. Soweit ich gehört habe, hat das Fort von Philipsburg viele Kanonen.";
			link.l1 = "Ich bin mir sicher, mein Freund, aber wir werden es schaffen. Bereite dich auf die See vor, wir brechen bald auf.";
			link.l1.go = "ecliaton_cap_10";
		break;
		
		case "ecliaton_cap_10":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_BastionAddEcliaton();
		break;
		
		case "ecliaton_cap_11":
			dialog.text = "Freut mich, Sie an Deck der 'Eclatant' zu sehen, Vizeadmiral! Was sind Ihre Befehle?";
			link.l1 = "Bereitet die 'Eclatant' für die Abreise vor. Zuerst segeln wir zur Küste von Jamaika und dann greifen wir zusammen mit dem Geschwader von Oberst D'Oyley Curacao an.";
			link.l1.go = "ecliaton_cap_13";
			link.l2 = "Es wird Befehle geben, Kapitän, aber später. Ich werde es Ihnen sagen, wann. Die 'Eclatant' muss jederzeit bereit sein, das Meer zu betreten.";
			link.l2.go = "ecliaton_cap_12";
		break;
		
		case "ecliaton_cap_12":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_11";
			npchar.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "ecliaton_cap_13":
			dialog.text = "Die 'Eclatant' und ihre Besatzung sind bereit, Vizeadmiral!";
			link.l1 = "Ausgezeichnet. Dann brechen wir sofort auf.";
			link.l1.go = "ecliaton_cap_14";
		break;
		
		case "ecliaton_cap_14":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_CuracaoAddEcliaton();
		break;
		
		// belamour legendary edition -->
		case "ecliaton_cap_15":
			dialog.text = "Entschuldigen Sie, meine Herren, ich konnte mich Ihnen nicht früher anschließen, ich war damit beschäftigt, Befehle auf dem Schiff zu geben. Ich dachte schon, dass ich ziemlich spät dran war, weil ich Sie nicht in der Residenz gefunden habe, und deshalb wollte ich zum Schiff zurückkehren...";
			link.l1 = "...";
			link.l1.go = "ecliaton_cap_16";
		break;
		
		case "ecliaton_cap_16":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_111";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_17":
			dialog.text = "Es war mir eine Ehre, an Ihrer Seite zu kämpfen, Monsieur de Maure! Ich muss sagen, dass ich selten so kompetente und geschickte Offiziere wie Sie treffe. Ich bin sicher, ich selbst hätte mich nicht so schnell mit dem Fort der spanischen Kolonie in Trinidad befassen können!";
			link.l1 = "Sie unterschätzen sich selbst, Monsieur Dassier. Wir haben es gemeinsam bewältigt.";
			link.l1.go = "ecliaton_cap_18";
		break;
		
		case "ecliaton_cap_18":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_113";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_19":
			dialog.text = "Das stimmt. Obwohl ich ein Marquis bin, bin ich immer noch ein Seemann. Für mich ist die karibische Inselgruppe neu, unerforscht und voller neuer Abenteuer. Das letzte Mal war ich nur wenige Monate hier, aber als ich nach Europa zurückkehrte, fing ich an, diesen Ort zu vermissen. Ich würde gerne hier unserem Vaterland dienen. Und du bist ein sehr talentierter und erfahrener Kapitän, es ist dir gelungen, meine aufrichtige Achtung und meine Freundschaft zu gewinnen. Es wäre mir eine Ehre, unter deinem Kommando zu dienen, Vizeadmiral!";
			link.l1 = "Nun, ich kann nicht und was mehr ist! - Ich will Ihnen nicht ablehnen, Monsieur Dassier!";
			link.l1.go = "ecliaton_cap_20";
		break;
		
		case "ecliaton_cap_20":
			dialog.text = "Ich verstehe auch, dass die Eclatant nun Ihr Flaggschiff ist, daher werde ich es perfekt verstehen, wenn Sie sich entscheiden, es persönlich zu kommandieren. In diesem Fall können Sie mich als Ihren Offizier belassen, mir ein anderes Schiff geben oder mich einfach von meinen Pflichten entbinden - Monsieur Forget hat mir freundlicherweise versprochen, dass er mir dann eine würdige Position in der Flotte der Französischen Westindien-Kompanie finden würde.";
			link.l1 = "Ich kann Ihnen versichern, mein Freund, dass es dazu nicht kommen wird. Sie sind einer der besten Kapitäne, die ich je getroffen habe, und mit Ihnen an meiner Seite werden wir unaufhaltsam sein.";
			link.l1.go = "ecliaton_cap_21";
		break;
		
		case "ecliaton_cap_21":
			dialog.text = "Danke für diese schmeichelhafte Einschätzung meiner Fähigkeiten. Und noch etwas, Vizeadmiral. Ich kenne die Größe Ihrer Staffel im Moment nicht, also werde ich sicherheitshalber auf der Kapitänsbrücke der Eclatant im Hafen von Capsterville auf Sie warten. Sobald Sie sich entscheiden, das Schiff unter Ihr Kommando zu nehmen - lassen Sie es mich einfach wissen.";
			link.l1 = "Sehr gut, Monsieur Dassier.";
			link.l1.go = "ecliaton_cap_22";
		break;
		
		case "ecliaton_cap_22":
			dialog.text = "Dann bitte ich um Erlaubnis, mich zu verabschieden. Vizeadmiral, Baron...";
			link.l1 = "Bis bald, Monsieur Dassier.";
			link.l1.go = "ecliaton_cap_23";
		break;
		
		case "ecliaton_cap_23":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_119";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
	
		case "ecliaton_cap_24":
			dialog.text = "Vizeadmiral, willkommen an Bord. Möchten Sie das Kommando über die Eclatant übernehmen?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				
				link.l1 = "Noch nicht, Marquis. Warte auf Befehle.";
				link.l1.go = "ecliaton_cap_24_1";
			}
			else
			{
				link.l1 = "Ja, Marquis, ich bitte Sie, sich meiner Staffel anzuschließen. Dieses schöne Schiff wird ein Symbol für die Größe und Macht Frankreichs in der Karibik sein!";
				link.l1.go = "ecliaton_cap_25";
			}
		break;
		
		case "ecliaton_cap_24_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_24";
			npchar.DeckDialogNode = "ecliaton_cap_24";
		break;
		
		case "ecliaton_cap_25":
			dialog.text = "Ich könnte nicht mehr zustimmen, Eure Exzellenz!";
			link.l1 = "... Nun, lasst uns sehen, wozu wir wirklich fähig sind!";
			link.l1.go = "ecliaton_cap_26";
		break;
		
		case "ecliaton_cap_26":
			DialogExit();
			DeleteAttribute(npchar, "ShipHideImmortal");
			SetCharacterRemovable(npchar, true);
			npchar.CompanionEnemyEnable = true; 
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			npchar.DeckDialogNode = "hired";
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.Payment = true;
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerWantToGo.DontGo = true;
			
			// удаление группы Эклятона, иначе клон-призрак
			pchar.quest.Patria_EcliatonDelGroup.win_condition.l1 = "ExitFromSea";
			pchar.quest.Patria_EcliatonDelGroup.function = "Patria_EcliatonDelGroup";
		break;
		// <-- legendary edition
		
		// д'Ойли на Антигуа
		case "doily":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "end" && colonies[FindColony("Pirates")].nation == PIRATE)
			{
				PlaySound("Voice\English\LE\Doily\Edvard_Doily_01.wav");
				dialog.text = "Oh, was für eine Bekanntschaft! Ist es nicht Kapitän Charles de Maure selbst?! Ich habe gehört, du hast jetzt eine Position in der französischen Marine. Was für eine Überraschung, wenn man bedenkt, für wen du zuvor, sagen wir mal, 'gearbeitet' hast...";
				link.l1 = "Grüße, Herr. Sprechen Sie über die Angelegenheit mit Isla Tesoro? Ach, aber ich war es nicht, der die englischen Gesetze geschrieben hat, nach denen die Insel an den Erben des Entdeckers, der sie gefunden hat, nach seinem Willen weitergegeben wurde. Also, ich bin nicht schuld daran, ich habe nur Miss Sharp geholfen, das zu bekommen, was ihr zurecht gehörte.";
				link.l1.go = "doily_1";
			}
			else
			{
				dialog.text = TimeGreeting()+", Kapitän. Ich nehme an, der Vertreter der französischen Marine ist mit einem wichtigen Ziel im Kopf nach Antigua gekommen?";
				link.l1 = "In der Tat, Herr. Ich wurde hierher von dem Generalgouverneur der französischen Kolonien, Philippe de Poincy, geschickt. Saint-Christopher wird von den spanischen und niederländischen Marinegeschwadern belagert. Der Chevalier bittet Sie und Sir Jonathan Fox um Hilfe. Hier ist sein Brief für Sie, Oberst.";
				link.l1.go = "doily_3";
			}
		break;
		
		case "doily_1":
			dialog.text = "Ich frage mich, Kapitän, wie viel Geld Sie damit verdient haben? Ich nehme an, ziemlich viel, da Sie es geschafft haben, die Dienste des Schurken Loxley zu bezahlen, die überhaupt nicht billig sind. Ich bin sicher, die Piratenbarone zahlen Ihnen regelmäßig Abzüge dafür, dass sie die Insel in ihrem Besitz halten. Wir beide wissen sehr gut, dass Helen Sharp nur eine Maske ist.";
			link.l1 = "Oberst, wir wissen beide auch, dass die Piratenbarone hauptsächlich im Interesse Englands handeln, nicht offiziell, wohlgemerkt... Ohne sie wäre es ziemlich schwierig, der Hegemonie der Spanier in der Region zu widerstehen, würden Sie nicht zustimmen? Also, aus der Sicht der Politiker, war die Tatsache, dass die Bruderschaft der Küste die Insel für sich behalten hat, vielleicht sogar profitabler als wenn Isla Tesoro eine englische Marinebasis geworden wäre...";
			link.l1.go = "doily_2";
		break;
		
		case "doily_2":
			dialog.text = "Das ist wohl wahr, Kapitän, aber ... sei es, wie es ist. Sie sind mit einem wichtigen Ziel in Antigua angekommen, nehme ich an? Vielleicht hat es etwas mit der Tatsache zu tun, dass sich die Beziehungen zweier ehemaliger Verbündeter - Frankreich und Holland, erheblich verschlechtert haben?";
			link.l1 = "Ganz richtig. Ich wurde vom Generalgouverneur der französischen Kolonien, Philippe de Poincy, gesandt. Saint-Christopher wird von der spanischen und holländischen Marine belagert. Der Ritter bittet um Ihre Hilfe. Hier ist sein Brief an Sie, Oberst.";
			link.l1.go = "doily_3";
		break;
		
		case "doily_3":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Lass mich sehen... (liest)";
			link.l1 = "";
			link.l1.go = "doily_3_1";
		break;
		
		case "doily_3_1":
			LAi_Fade("", "");
			dialog.text = "Hmm... sehr intrigierend! Kapitän, Ihr Kommandant weiß, wie er mein Interesse wecken kann, es ist nicht ungewöhnlich, dass die Leute ihn einen schlauen Fuchs nennen. Wir hätten das schon lange tun sollen, anstatt zu versuchen, uns mit den Niederländern anzufreunden. Wie wir sehr gut wissen, wofür die niederländische Gesellschaft und ihr Direktor stehen. Nun, ich denke, dass wir in dieser Situation wirklich nicht leugnen sollten, dem belagerten Casterville zu helfen, und wir haben mehr als genug Truppen dafür.\nWie sind die Zahlen und Arten der Schiffe in ihren Geschwadern, Kapitän?";
			link.l1 = "Ich habe sechs Schiffe gezählt: ein achtzig-Kanonen-Linienschiff dritten Ranges und fünf Schiffe des vierten Ranges. Sie könnten auch Fregatten und Galeonen haben.";
			link.l1.go = "doily_4";
		break;
		
		case "doily_4":
			dialog.text = "Hmm... Wir können unser Geschwader, bestehend aus einem hundertkanonigen Schiff der ersten Klasse, zwei Schiffen der vierten und einer schweren Fregatte, gegen deren aufstellen.";
			if (!CheckAttribute(pchar, "questTemp.Patria.FailLugger"))
			{
				link.l1 = "Herr, wir haben auch ein 66-Kanonen-Kriegsschiff, die 'Eclatant', das zur Verteidigung von Saint-Christopher von der Küste von Guadeloupe segelt.";
				link.l1.go = "doily_5";
			}
			else
			{
				link.l1 = "Ein Schiff erster Klasse wird uns in der bevorstehenden Schlacht sehr helfen.";
				link.l1.go = "doily_5_1";
			}
		break;
		
		case "doily_5":
			dialog.text = "Perfekt. In diesem Fall sind wir weit über die Feuerkraft unserer Feinde hinaus. Der Sieg wird unser sein.";
			link.l1 = "Und vergessen Sie nicht mein eigenes Schiff, Herr. Ich werde so eine Schlacht nicht verpassen, denken Sie nicht einmal daran.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_5_1":
			dialog.text = "Das ist wahr. Mit der Hilfe von der Festung Casterville wird der Sieg unser sein.";
			link.l1 = "Und vergessen wir mein eigenes Schiff nicht, Herr. Ich werde eine solche Schlacht nicht verpassen, denken Sie nicht einmal daran.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_6":
			dialog.text = "Natürlich, Monsieur de Maure. Was auch immer der Fall sein mag, Geschichten über Ihre Segeltalente sind in der ganzen Inselgruppe zu hören. Ihr Flaggschiff wird das Geschwader anführen.";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "Ich werde den Rest der Schiffe aus meinem Geschwader in Bereitschaft stellen, dann zu dir zurückkehren und wir werden zur Hilfe der Belagerten eilen.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "Ich werde mein Schiff gleich vorbereiten und wir werden den Belagerten zu Hilfe eilen.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_7_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_7_2";
		break;
		
		case "doily_7_2":
			dialog.text = "Also, bist du bereit zur Abfahrt?";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "Warten Sie nur ein kleines bisschen, Herr.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "Ja, Herr.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_8":
			dialog.text = "Dann lass uns beginnen, und möge Gott uns helfen!";
			link.l1 = "...";
			link.l1.go = "doily_9";
		break;
		
		case "doily_9":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Patria", "42");
			Patria_SiegeAddEngSquadron();
		break;
		
		case "doily_10":
			dialog.text = "Haben Sie noch weitere Fragen, Herr?";
			link.l1 = "Nein, Oberst...";
			link.l1.go = "doily_11";
		break;
		
		case "doily_11":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			npchar.DeckDialogNode = "doily_10";
		break;
		
		case "doily_12":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_02.wav");
			dialog.text = "Holt den Brief für den Stuyvesant, Herr. Wenn Sie nicht wissen, wer ich bin, lassen Sie mich mich vorstellen: Oberst Edward Doily, Gouverneur von Port-Royal und Kommandant dieser Expedition!\nUm Ihnen die Wahrheit zu sagen, habe ich ein großes Verlangen, das Banditenversteck namens Willemstad dem Erdboden gleichzumachen. Die abscheulichste, doppelzüngigste und verachtenswerteste Organisation in der Karibik, bekannt als die Niederländische Westindien-Kompanie, die glaubt, dass der gesamte Handel im Archipel ausschließlich ihr Recht sei, und die Leute wie Jacob van Berg und andere Piraten anheuert, um die Schiffe englischer Kaufleute zu kapern und zu versenken...";
			link.l1 = "...";
			link.l1.go = "doily_13";
		break;
		
		case "doily_13":
			dialog.text = "Ich bin hier, um diesen empörenden Taten ein Ende zu setzen, und, glücklicherweise für euch, schlage ich einen diplomatischen Weg vor. Für jetzt... Aber wenn der Direktor dieser abscheulichen Organisation nicht hier für die Gespräche auftaucht, werde ich sein Geschäft zugrunde richten. Nachdem wir die Stadt gestürmt haben, werde ich nur Asche hinterlassen, und jedes Pulver, das wir finden, werden wir in den Keller eurer Festung bringen und in die Luft sprengen. Das gleiche Schicksal wird euren Plantagen erwarten, und der Stuyvesant selbst wird am Rah der mein Flaggschiff hängen...";
			link.l1 = "...";
			link.l1.go = "doily_14";
		break;
		
		case "doily_14":
			dialog.text = "Sie werden mehr als ein Jahr brauchen, um Ihre Kolonie wieder aufzubauen, und dann werden Sie keine Zeit für Ihre Pläne und Intrigen haben. Erzählen Sie Ihrem 'Mynheer Direktor' alles, was ich gerade gesagt habe, und denken Sie nicht, dass dies Witze und leere Versprechen sind. Mir ist die Geduld ausgegangen, also müssen Sie mich perfekt verstehen. Verstehen Sie, Offizier?!";
			link.l1 = "Alles ist perfekt klar, Herr Oberst.";
			link.l1.go = "doily_15";
		break;
		
		case "doily_15":
			dialog.text = "Gut. Dann geh. Ich gebe dir genau einen Tag zum Nachdenken. Wenn Peter Stuyvesant nach vierundzwanzig Stunden nicht hier steht wie du jetzt, soll er sich selbst die Schuld geben.";
			link.l1 = "...";
			link.l1.go = "doily_16";
		break;
		
		case "doily_16":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_17";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "doily_17":
			dialog.text = "Ich glaube, dass dieser verdammte Hund Stuyvesant hierher kommen wird. Und wenn nicht - er kann nur sich selbst die Schuld geben!";
			link.l1 = "...";
			link.l1.go = "doily_17_1";
		break;
		
		case "doily_17_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_17";
			AddQuestRecord("Patria", "63");
			Patria_CuracaoParlamenterGo();
		break;
		
		case "doily_18": // д'Ойли на берегу
			dialog.text = "Sie haben gute Arbeit mit der Festung geleistet, Monsieur de Maure. Nun werden wir uns zu Land den Stadtmauern nähern. Ich übernehme die Kanonen von hier, der Weg hier ist kürzer und einfacher, und Sie werden Ihre Marinekompanie am Kap Santa-Maria absetzen und nach Willemstad vorrücken. Wenn Sie unterwegs auf Feinde treffen, wissen Sie, was zu tun ist. Niemand darf hinter uns zurückbleiben.";
			link.l1 = "Natürlich, Oberst. Ich treffe Sie am Tor!";
			link.l1.go = "doily_19";
		break;
		
		case "doily_19":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Patria", "61");
			npchar.dialog.currentnode = "doily_10";
			Patria_CuracaoGotoMarch();
		break;
		
		case "doily_20":
			dialog.text = "Nun, es scheint, dass unsere Mission recht erfolgreich abgeschlossen wurde. Herzlichen Glückwunsch, Kapitän! Oh, entschuldigen Sie - Vizeadmiral! Lassen Sie uns zu den Schiffen zurückkehren. Ich werde meinen Männern sagen, dass sie Wache stehen - dieser Narr Stuyvesant wird uns wahrscheinlich nicht angreifen, während wir uns zurückziehen, aber es schadet nicht, vorsichtig zu sein.";
			link.l1 = "Ich bin sicher, die Holländer werden es nicht wagen, einen gerade erst unterzeichneten Vertrag zu brechen.";
			link.l1.go = "doily_21";
		break;
		
		case "doily_21":
			dialog.text = "Es war mir ein Vergnügen, mit Ihnen zusammenzuarbeiten, Monsieur de Maure. Ich denke, wir werden uns erneut in Port-Royal oder Capsterville treffen.";
			link.l1 = "Ohne Zweifel, Oberst. Jetzt sagen wir unseren Männern, sie sollen sich zurückziehen.";
			link.l1.go = "doily_22";
		break;
		
		case "doily_22":
			DialogExit();
			AddQuestRecord("Patria", "64");
			Patria_CuracaoClear();
		break;
		
		case "doily_23":
			dialog.text = "Es scheint, die Holländer haben endlich gelernt, dass sie keine Chance haben, uns von der Festung aus über diesen schmalen Pfad unter unserem Artilleriefeuer zu erreichen. Und diejenigen, die in der Stadt festsitzen, werden wahrscheinlich kein Risiko eingehen, es sei denn, sie sind völlig verrückt. Jetzt werden wir etwas Panik säen: Lassen wir die Stadt mit unseren Kanonen bombardieren. Die Männer auf meinem Schiff werden es sehen und es so aussehen lassen, als ob sie sich auf eine Landung vorbereiten. Nach ein oder zwei Stunden wird Stuyvesant sich in die Hosen scheißen und bereit sein, die Waffenstillstandsboten zu schicken.";
			link.l1 = "Alles läuft nach unserem Plan, Oberst! Lass es uns tun!";
			link.l1.go = "doily_24";
		break;
		
		case "doily_24":
			DialogExit();
			Patria_CuracaoTownBombing();
		break;
		
		// голландский парламентёр под стенами Виллемстада
		case "holoff":
			dialog.text = "Ich bin hier angekommen, um die Verhandlungen zu beginnen. Was sind Ihre Forderungen?";
			link.l1 = "Wir fordern ein Treffen mit dem Direktor der Gesellschaft, Peter Stuyvesant. Insbesondere möchten wir über die Tatsache sprechen, dass Willemstad derzeit aufgrund des Verschuldens seiner Gesellschaft und seines eigenen, vor der Zerstörung steht.";
			link.l1.go = "holoff_1";
		break;
		
		case "holoff_1":
			dialog.text = "Sehr gut, ich werde Mynheer Stuyvesant davon erzählen, und wir werden einen sicheren Weg in die Stadt für Ihre Delegation organisieren...";
			link.l1 = "Und was ist mit einem sicheren Ausgang?";
			link.l1.go = "holoff_2";
		break;
		
		case "holoff_2":
			dialog.text = "Ich verstehe nicht, Mynheer?";
			link.l1 = "Ich sagte: Wirst du für uns einen sicheren Ausgang aus der Stadt arrangieren? Ich bin mir da nicht so sicher. Ich fürchte, Mynheer Stuyvesant könnte einfach beschließen, unsere Gesandten gefangen zu nehmen. Aus diesem Grund lade ich Mynheer Stuyvesant ein, genau hier für die Verhandlungen zu erscheinen.";
			link.l1.go = "holoff_3";
		break;
		
		case "holoff_3":
			dialog.text = "Aber...";
			link.l1 = "Offizier, wir bestimmen hier die Bedingungen. Ihre Flotte ist zerstört, die Garnison von der Stadt abgeschnitten, und wir werden die Verteidigung von Willemstad durchbrechen wie eine Fregatte ein Ruderboot durchdringt, wenn wir beschließen, die Stadt zu stürmen. Jetzt werden Sie einen Brief für Mynheer Stuyvesant erhalten, und Sie werden ihn ihm zusammen mit unserer Einladung übergeben...";
			link.l1.go = "holoff_4";
		break;
		
		case "holoff_4": // перекидываем pchar на офицера и говорим с д'Ойли
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Curacao_parlamenter_1"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		// офицер-испанец на маяке Тринидада
		case "SanJoseSpanish":
			dialog.text = "Also, Kapitän, Sie haben die Waffenstillstandsboten gerufen, weil Sie Ihre Forderungen diktieren wollten?";
			link.l1 = "Sie haben absolut recht, Senor. Lassen Sie mich kurz erklären, warum ich in Trinidad angekommen bin - dies ist unsere Antwort auf Ihren jüngsten Angriff auf Saint-Pierre. Sie haben die Stadt erheblich beschädigt und nun werden Sie gezwungen sein, sie zu entschädigen. Der Preis der Entschädigung beträgt dreihunderttausend Peso. Und das ist nicht so viel, wenn man bedenkt, welche abscheulichen Taten Ihre Soldaten auf Martinique begangen haben.";
			link.l1.go = "SanJoseSpanish_1";
		break;
		
		case "SanJoseSpanish_1":
			dialog.text = "Entschuldigen Sie, senor, aber was hat San Jose mit Saint-Pierre zu tun? Warum muss unsere Kolonie zahlen?";
			link.l1 = "Weil die Angreifer Spanier waren, nicht Holländer oder Engländer. Dann werden Sie die Rechnung für Don de Mendosa auf die Vorsehung setzen, zusammen mit meinen aufrichtigsten Grüßen. Wie Sie verstehen, falls Sie sich weigern, die Entschädigung zu zahlen, werde ich meinen Männern befehlen, an Land zu gehen, und dann wird San Jose viel mehr verlieren. Ich bin sicher, der Gouverneur Ihrer Kolonie wird die richtige Entscheidung treffen. Sie haben einen Tag Zeit, um zu antworten. Ich wünsche Ihnen alles Gute, senores.";
			link.l1.go = "SanJoseSpanish_2";
		break;
		
		case "SanJoseSpanish_2":
			DialogExit();
			npchar.dialog.currentnode = "SanJoseSpanish_3";
			Patria_SanJoseMayakSpanishGo();
		break;
		
		case "SanJoseSpanish_3":
			dialog.text = "";
			link.l1 = "Also, wenn ich das richtig verstehe, hat der Gouverneur die richtige Entscheidung getroffen?";
			link.l1.go = "SanJoseSpanish_4";
		break;
		
		case "SanJoseSpanish_4":
			AddMoneyToCharacter(pchar, 300000);
			dialog.text = "Hol dir deine dreihunderttausend und verlass unsere Kolonie.";
			link.l1 = "Ausgezeichnet, Senores. Ich versichere Ihnen - das war der beste Weg. Ich hoffe, das wird den Don de Mendosa und andere davon abhalten, unsere Kolonien anzugreifen. Vergessen Sie nicht, die Nachricht an die Vorsehung und ihn persönlich zu senden. Ich wünsche Ihnen alles Gute, meine Herren.";
			link.l1.go = "SanJoseSpanish_5";
		break;
		
		case "SanJoseSpanish_5":
			DialogExit();
			Patria_SanJoseMayakSpanishFin();
		break;
		
		// вестовой на 5 задание
		case "fraofficer":
			dialog.text = "Kapitän Charles de Maure, erlauben Sie mir zu berichten: Chevalier Philippe de Poincy wollte Ihnen mitteilen, dass Baron Noel Forget bereit ist, nach Saint-Martin abzureisen und Sie am Pier erwarten wird.";
			link.l1 = "Ausgezeichnet! Danke, Monsieur.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			Patria_SanMartinSetBaron();
		break;
		
		case "fraofficer_2":
			dialog.text = "Kapitän Charles de Maure! Der Generalgouverneur ruft Sie gerade jetzt. Eine mächtige feindliche Eskadron ist an der Küste von Saint-Christopher aufgetaucht!";
			link.l1 = "Dann lass uns keine Zeit verschwenden!";
			link.l1.go = "fraofficer_3";
		break;
		
		case "fraofficer_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			Patria_SiegeHovernor();
		break;
		
		// патруль у рудника
		case "engofficer":
			dialog.text = "Wer bist du? Was machst du hier?";
			link.l1 = "Ähh...";
			link.l1.go = "engofficer_1";
		break;
		
		case "engofficer_1":
			dialog.text = "Keine Fremden dürfen hier eintreten! Wer seid ihr, Spione? Ich bringe euch zum Kommandantenbüro, die werden sich um euch kümmern.";
			link.l1 = "Aber wir können nicht ins Kommandantenbüro gehen...";
			link.l1.go = "engofficer_2";
		break;
		
		case "engofficer_2":
			dialog.text = "Wenn du nicht freiwillig gehst - dann müssen wir dich eben mit Gewalt ziehen! Gib deine Waffen ab!";
			link.l1 = "Kein Deal...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierBeachFight");
		break;
		
		// бывший управляющий рудника
		case "miner":
			dialog.text = "";
			link.l1 = "Also, ist alles klar?";
			link.l1.go = "miner_1";
		break;
		
		case "miner_1":
			dialog.text = "Ja, monsieur. Der Brief soll persönlich an meinen Herrn Peter Stuyvesant oder Mathias Beck übergeben werden.";
			link.l1 = "Ich bin sicher, dass Sie keine Schwierigkeiten haben werden, ein Schiff von Willemstad nach Cartagena zu finden. Wir haben Ihnen alle notwendigen Mittel gegeben, um die Reise und die Unterkunft zu bezahlen. Und falls Sie es benötigen - werden Sie Ihre Berichte vor der französischen Kommission in einem halben Jahr bestätigen?";
			link.l1.go = "miner_2";
		break;
		
		case "miner_2":
			dialog.text = "Herr, ich halte mein Wort.";
			link.l1 = "Sehr gut. Dann wünsche ich dir Glück. Dieser Weg führt nach Willemstad, folge ihm. Es ist nicht weit von hier.";
			link.l1.go = "miner_3";
		break;
		
		case "miner_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Patria_CondotierOnCuracaoWait", 15.0);
			AddQuestRecord("Patria", "82");
			ReleasePrisoner(npchar);
		break;
		
		// курьер в Капстервиль
		case "cureer":
			dialog.text = "Vizeadmiral Charles de Maure, richtig?";
			link.l1 = "Genau. Mit wem habe ich die Ehre zu sprechen?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "Ich habe eine Nachricht für dich von Baron Noel Forget. Er hat dir gesagt, du sollst so schnell wie möglich zum Gouverneurspalast in Casterville kommen.";
			link.l1 = "Oh! Großartige Neuigkeiten! Danke, ich werde sofort aufbrechen!";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			Patria_EuropePrepare();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
		break;
		
		case "burden":
			dialog.text = "Grüße, Vizeadmiral. Baron Forget hat mir Geschichten über Sie erzählt. Viele Geschichten. Ich danke Ihnen aufrichtig für Ihren treuen und brillanten Dienst zum Wohle Frankreichs in den Kolonien, sowie für Ihre Hilfe bei der Aufdeckung der Intrigen des Betrügers de Poincy. Jetzt werden ich und der Finanzminister uns persönlich um ihn kümmern, und Sie werden den Platz Ihres ehemaligen Kommandanten einnehmen. Zumindest vorerst.";
			link.l1 = "Aber...";
			link.l1.go = "burden_1";
		break;
		
		case "burden_1":
			dialog.text = "Keine 'Abers', Vizeadmiral! Diese Entscheidung wurde bereits getroffen und vom König genehmigt. Ich habe hier einen von ihm persönlich unterzeichneten Befehl, der Sie zum faktischen Generalgouverneur der französischen Kolonien im Archipel ernannt. Wir haben keine besseren Kandidaten für diese Position. Ihre herausragende Kriegserfahrung, Ihre Kenntnisse der Region und der Menschen, die hier für alles verantwortlich sind, Ihre Fähigkeiten und Talente sind alle würdig für diese hohe und respektable Position. Wenn ich ehrlich zu Ihnen sein darf, erwarte ich, dass Sie nach einiger Zeit erneut für diese Position ernannt werden, ohne den 'de facto'-Teil.";
			link.l1 = "Aber ich träumte davon, nach Paris zurückzukehren...";
			link.l1.go = "burden_2";
		break;
		
		case "burden_2":
			dialog.text = "Frankreich braucht dich hier! Der Finanzminister sammelt gerade eine Marine in Europa, und auch unsere Präsenz hier, im Archipel, wird nicht unbemerkt bleiben. Deine Hauptaufgabe wird es sein, die Kolonien zu stärken und zu befestigen und die militärische Macht unserer Flotte zu erhöhen, während sich Baron Forget und die Französische Westindien-Handelsgesellschaft auf den Handel und die inländische Entwicklung konzentrieren! Und wer sonst, wenn nicht du, kann helfen, die französische Marine vorzubereiten?\nAlso, fang an zu arbeiten, Generalgouverneur! Ich weiß, dass du es nicht magst, den ganzen Tag in einem Raum zu sitzen, aber deine Aufgabe erfordert das nicht einmal!";
			link.l1 = "Sofort, Eure Gnaden! Befehle sind nicht in Frage zu stellen!";
			link.l1.go = "burden_3";
		break;
		
		case "burden_3":
			dialog.text = "Ich freue mich, dass Sie mich richtig verstanden haben. Und ich werde Sie auch bitten, den Chevalier de Poincy zu besuchen: er bestand darauf, Sie zu treffen. Wir können ihm solch ein Vergnügen vor seiner Abreise nach Paris doch nicht verweigern, oder? Sie finden ihn im Gefängnis.";
			link.l1 = "Sehr gut, Eure Gnaden...";
			link.l1.go = "burden_4";
		break;
		
		case "burden_4":
			DialogExit();
			DoQuestReloadToLocation("Charles_prison", "goto", "goto19", "Patria_EuropePuancieInPrison");
		break;
		
		// Портной Пуанси Xenon
		case "Tailor":
			dialog.text = "...wird stillstehen, verstehst du? Ich habe diese Materialien vor mehreren Monaten bestellt!";
			link.l1 = "...";
			link.l1.go = "Tailor_01";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_01":
			DialogExit();
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_02":
			dialog.text = "Und wie haben sie priorisiert, was sie auf das erste Schiff und was auf das zweite laden?! Ich bin nicht irgendeine Näherin aus der Pampa - ich habe sogar einen Auftrag vom Generalgouverneur, seiner Exzellenz Chevalier de Poincy!";
			link.l1 = "...";
			link.l1.go = "Tailor_03";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_03":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor_02";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_04":
			dialog.text = "Nun, was kann ich jetzt noch tun... Ich werde warten. Aber eins solltest du wissen: Ich übernehme keine Verantwortung für nicht erfüllte Aufträge!";
			link.l1 = "Grüße. Ich sehe, du hast Ärger?";
			link.l1.go = "Tailor_05";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_05":
			dialog.text = "Ärger? Das ist milde ausgedrückt! Oh, ich glaube, ich erkenne dich... Du bist der neue Vizeadmiral, richtig?";
			link.l1 = "Schnell im Verstehen. Das ist korrekt, vor Ihnen steht der zweite Mann in den französischen Kolonien, Vizeadmiral der französischen Flotte, Charles de Maure.";
			link.l1.go = "Tailor_06";
			link.l2 = "Lass diese Förmlichkeiten, wir sind nicht auf einem Schiff. Und mach dir keine Sorgen, ich werde die Wachen nicht rufen, nur weil du mich nicht sofort erkannt hast. Nenn mich einfach Charles de Maure.";
			link.l2.go = "Tailor_07";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tailor_06":
			AddCharacterExpToSkill(pchar, "Leadership", 300);//харизма
			dialog.text = "Eure Exzellenz, bitte verzeihen Sie mir, dass ich Sie nicht sofort erkannt habe! Ja, Sie haben recht, ich bin auf unvorhergesehene Umstände gestoßen.";
			link.l1 = "Und was wären diese Umstände? Soweit ich verstehe, haben sie Ihnen keine Materialien aus Paris gebracht?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_07":
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			dialog.text = "Oh, vielen Dank. Du hast recht, ich bin auf unvorhergesehene Umstände gestoßen, weshalb ich nicht sofort erkannt habe, wer vor mir steht.";
			link.l1 = "Und unter welchen Umständen wäre das? Soweit ich verstehe, haben sie dir keine Materialien aus Paris gebracht?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_08":
			dialog.text = "Ja, das ist korrekt. Ich habe sie vor mehreren Monaten bestellt. Der Gouverneur hat damals den Auftrag für Ihre Ernennung unterzeichnet und darauf bestanden, dass ich alle notwendigen Materialien für eine neue Admiralsuniform vorbereite, zuversichtlich, dass sie in der Metropole genehmigt werden würde.";
			link.l1 = "Und die Materialien wurden nicht geliefert, nehme ich an?";
			link.l1.go = "Tailor_09";
		break;
		
		case "Tailor_09":
			dialog.text = "Stell dir das vor! Ich habe erklärt, wie wichtig es war, habe die Bestellung aufgegeben... Aber sie haben dringendere Lieferungen zu erledigen! Was soll ich tun? Soll ich meine Bestellungen ein Jahr im Voraus aufgeben, in der Hoffnung, dass sie sich herablassen, mir die Materialien zu bringen?";
			link.l1 = "Was genau fehlt Ihnen? Vielleicht kann es in der Karibik beschafft werden?";
			link.l1.go = "Tailor_10";
		break;
		
		case "Tailor_10":
			dialog.text = "Auch wenn es möglich ist, habe ich keine Ahnung wo... Du wirst hier keine guten Materialien finden. Obwohl... Ich könnte deine alte Offiziersjacke als Grundlage verwenden, wenn du erlaubst. Du wirst sie wahrscheinlich nicht mehr brauchen, sobald du eine Admiralsuniform hast, oder?";
			link.l1 = "Wenn ich eine Admiraluniform habe, dann brauche ich natürlich keine einfache Offiziersjacke. Was noch?";
			link.l1.go = "Tailor_11";
		break;
		
		case "Tailor_11":
			dialog.text = "Ich muss Manschettenknöpfe und einen Kragen für die Uniform finden. Normalerweise bestelle ich sie direkt aus Pariser Werkstätten. Auch wenn sie sehr einfach sind, kann ich sie verändern und ihnen ein ansehnlicheres Aussehen verleihen. In diesem Fall brauche ich allerdings mehr davon...";
			link.l1 = "Da es in der Karibik keine Pariser Werkstätten gibt, werde ich Ihnen eine ganze Ladung lokaler Kleidung mit abnehmbaren Kragen und Manschetten besorgen. Was sonst?";
			link.l1.go = "Tailor_12";
		break;
		
		case "Tailor_12":
			dialog.text = "Für den letzten Schliff benötige ich sehr hochwertige Stoffe. Ich habe eine Spinnerin, die solchen Stoff sogar aus grober Faser herstellen kann. Aber dafür brauche ich Material - idealerweise Baumwolle. Eine Ballen reicht mehr als genug.";
			link.l1 = "Das kann auch beschafft werden. Was kommt als nächstes?";
			link.l1.go = "Tailor_13";
		break;
		
		case "Tailor_13":
			dialog.text = "Sie sollten einen Admiralsdreispitz aus Paris liefern, aber ich kann ihn selbst herstellen, wenn ich das Material habe. Während der Dreispitz für dich aus Stoff sein sollte, wäre Leder besser für die salzigen Winde und die sengende Sonne der Karibik. Es würde länger halten.";
			link.l1 = "I'll get you the leather; don't worry. I won't even have to chase bulls through the jungles of Espanola. Is that all?";
			link.l1.go = "Tailor_14";
		break;
		
		case "Tailor_14":
			dialog.text = "Sie sollten auch hochwertige Seide aus Lyon liefern. Sie ist leicht, atmungsaktiv, nimmt leicht Feuchtigkeit auf und trocknet noch schneller. Und am wichtigsten, sie dehnt sich nicht aus und behält ihre Form.";
			link.l1 = "Ja, ich verstehe, von welcher Seide du sprichst. Das könnte in den Kolonien allerdings schwieriger zu bekommen sein.";
			link.l1.go = "Tailor_15";
		break;
		
		case "Tailor_15":
			dialog.text = "Das war's mit den Materialien. Ich habe auch gehört, dass Sie mit der höchsten Auszeichnung Frankreichs ausgezeichnet wurden... Der Orden von Saint Louis sollte nicht wie irgendein Schmuckstück an Ihrem Gürtel getragen werden. Er hat seinen Platz. Also bringen Sie ihn bitte zu mir, und ich werde ihn so aufnähen, wie es sein sollte.";
			link.l1 = "Also gut, ich bringe es auch. Verliere es nur nicht!";
			link.l1.go = "Tailor_16";
		break;
		
		case "Tailor_16":
			dialog.text = "Gewiss nicht! Ich werde es mit meinem Leben bewachen!";
			link.l1 = "Gut dann. Wenn das alles ist, werde ich die Materialien holen.";
			link.l1.go = "Tailor_17";
		break;
		
		case "Tailor_17":
			dialog.text = "Es gibt noch eine Sache... Meine Schneiderwerkzeuge sind unbrauchbar geworden. Ich habe neue aus Paris bestellt, aber ach... Wenn Sie alle notwendigen Materialien finden und mir die Werkzeuge leihen könnten, wenn Sie sie haben - nur leihen, ich werde später neue bekommen! - Ich würde sofort mit dem Nähen beginnen.";
			link.l1 = "Nun, was kann ich tun? Ich bringe Ihnen alles, was Sie brauchen. Wo kann ich Sie finden? Sie werden doch nicht auf mich in der Hafenbehörde warten, oder?";
			link.l1.go = "Tailor_18";
		break;
		
		case "Tailor_18":
			dialog.text = "Meine Werkstatt befindet sich im Gebäude direkt am Pier - wenn du an Land gehst, wird es auf deiner Rechten sein.";
			link.l1 = "Abgemacht. Ich besorge dir die Materialien.";
			link.l1.go = "Tailor_19";
		break;
		
		case "Tailor_19":
			DialogExit();
			AddQuestRecord("Patria", "65_1");
			chrDisableReloadToLocation = false;
			ChangeCharacterAddressGroup(npchar, "Charles_houseS3", "barmen", "Stay");
			npchar.dialog.currentnode = "Tailor_20";
			LAi_SetOwnerType(npchar);
			pchar.questTemp.PatriaTailor = true;
		break;
		
		case "Tailor_20":
			dialog.text = "Grüße, Vizeadmiral! Haben Sie alles Notwendige für Ihre neue Uniform mitgebracht?";
			link.l1 = "Noch nicht, ich hatte keine Zeit. Warte mal, ich werde alles besorgen.";
			link.l1.go = "Tailor_20_exit";
			if(CheckCoatItems())
			{
				link.l2 = "Ja, ich habe alles mitgebracht. Hier ist meine alte Jacke, der Orden und die Schneiderwerkzeuge. Den Rest der Materialien bringen meine Matrosen in Kürze zu Ihrer Werkstatt.";
				link.l2.go = "Tailor_21";
			}
		break;
		
		case "Tailor_20_exit":
			npchar.dialog.currentnode = "Tailor_20";
			DialogExit();
		break;
		
		case "Tailor_21":
			RemoveItems(pchar, "talisman9", 1);
			RemoveItems(pchar, "suit1", 1);
			RemoveItems(pchar, "tailor_tool", 1);
			RemoveCharacterGoods(pchar, GOOD_CLOTHES, 1);
			RemoveCharacterGoods(pchar, GOOD_COTTON, 1);
			RemoveCharacterGoods(pchar, GOOD_LEATHER, 1);
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			dialog.text = "Wunderbar! Um ehrlich zu sein, ich dachte nicht, dass Sie in der Lage sein würden, all dies zu beschaffen. Ich bin es gewohnt, nur mit Stoffen aus Paris zu arbeiten, aber es scheint, dass man aus lokalen Materialien recht anständige Anzüge machen kann.";
			link.l1 = "Wie lange dauert es, bis meine neue Uniform fertig ist?";
			link.l1.go = "Tailor_22";
		break;
		
		case "Tailor_22":
			dialog.text = "Normalerweise dauert es nicht weniger als eine Woche, aber wenn man bedenkt, dass die Kunden die beiden höchsten Beamten Frankreichs in den Kolonien sind... Komm in drei Tagen zu mir, und ich verspreche dir, alles wird auf bestmögliche Weise fertig sein! Wir brauchen keine Maße zu nehmen, ich mache alles basierend auf deiner alten Jacke.";
			link.l1 = "Großartig! Ich komme dann in drei Tagen zurück.";
			link.l1.go = "Tailor_23";
		break;
		
		case "Tailor_23":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
			SetFunctionTimerCondition("Patria_Tailor_Done", 0, 0, 3, false);
		break;
		
		case "Tailor_24":
			if(CheckAttribute(pchar,"questTemp.PatriaTailorDone"))
			{
				dialog.text = "Vizeadmiral! Es ist eine Freude, Sie zu sehen!";
				link.l1 = "Nun, ich bin wegen der neuen Uniform gekommen, wie wir vereinbart haben.";
				link.l1.go = "Tailor_27";
			}
			else
			{
				dialog.text = "Grüße, Vizeadmiral! Entschuldigung, aber Ihre Uniform ist noch nicht fertig.";
				link.l1 = "Nun, kann ich wenigstens einen kleinen Blick darauf werfen, was vor sich geht?";
				link.l1.go = "Tailor_25";
			}
		break;
		
		case "Tailor_25":
			dialog.text = "Nein, nein! Im Moment sieht es völlig unansehnlich aus, und ich möchte Ihre Erwartungen nicht enttäuschen. Bitte haben Sie Geduld.";
			link.l1 = "Оk, ich werde warten.";
			link.l1.go = "Tailor_26";
		break;
		
		case "Tailor_26":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
		break;
		
		case "Tailor_27":
			dialog.text = "Ja, natürlich! Ich muss Ihnen sagen, dass es nicht schlechter geworden ist als die in Paris hergestellten! Sie hatten recht, sogar in den Kolonien kann man geeignetes Material finden, wenn man weiß, wo man suchen muss. Nur einen Moment. Hier ist es! Bitte, untersuchen und probieren Sie es an.";
			link.l1 = "Danke dir. Hervorragende Qualität! Und es passt gut.";
			link.l1.go = "Tailor_28";
		break;
		
		case "Tailor_28":
			dialog.text = "Nicht nur gut! Sie können dies stolz als Vizeadmiral von Frankreich in den Kolonien tragen! Und Ihr Orden, wie ich versprochen habe, befindet sich nun an seiner richtigen Stelle, nicht baumelnd an Ihrem Gürtel.";
			link.l1 = "Gute Arbeit! Wenn du Chevalier de Poincy triffst, kannst du ihm sagen, dass ich zufrieden bin.";
			link.l1.go = "Tailor_29";
		break;
		
		case "Tailor_29":
			dialog.text = "Ich werde es ihm definitiv sagen! Möge die Uniform Ihnen treu dienen! Viel Glück!";
			link.l1 = "Danke! Auf Wiedersehen.";
			link.l1.go = "Tailor_30";
		break;
		
		case "Tailor_30":
			DialogExit();
			npchar.dialog.currentnode = "first time";
			npchar.lifeday = 0;
			DeleteAttribute(pchar,"questTemp.PatriaTailorDone");
			DeleteAttribute(pchar, "questTemp.PatriaTailor");
			//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			GiveItem2Character(pchar, "suit5");
			EquipCharacterbyItem(pchar, "suit5");
			GiveItem2Character(pchar, "hat5");
			EquipCharacterbyItem(pchar, "hat5");
			AddItems(pchar, "tailor_tool", 1);
			Log_Info("You have received the Vice-Admiral's uniform!");
			AddQuestRecord("Patria", "65_2");
		break;
		
		//belamour legendary edition
		case "BladeUpg":
			string sItem, attrL, attrB;
			ref rItem;
			aref arItems; 
			int i, n, iItemsNum;
			dialog.text = "Welche Klinge möchten Sie verbessern?";
			
			i = 1;
			makearef(arItems, pchar.items);
			iItemsNum = GetAttributesNum(arItems);
			for(n=0; n<iItemsNum; n++)
			{
				sItem = GetAttributeName(GetAttributeN(arItems, n));
				rItem = ItemsFromID(sItem);
				if(!CheckAttribute(rItem, "groupID")) continue;
				if(rItem.groupID != BLADE_ITEM_TYPE) continue;
				if(rItem.price == 0) continue;
				if(IsEquipCharacterByItem(pchar, rItem.id)) continue;
				if(sItem != "" && rItem.groupID == BLADE_ITEM_TYPE) 
				{
					attrL = "l" + i;
					Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt") + ": Attack - " + FloatToString(stf(rItem.attack),1) + ", balance - " + FloatToString(stf(rItem.Balance),1) + ", weight - " + FloatToString(stf(rItem.Weight),1);
					Link.(attrL).go = "bladeindex_"+GetItemIndex(rItem.id);
					i++;
				}
			}
			
			link.l500 = "Ich habe es mir anders überlegt";
			link.l500.go = "exit";
		break;
	}
} 

bool CheckCoatItems()
{
	if(GetSquadronGoods(pchar, GOOD_CLOTHES) > 0
	&& GetSquadronGoods(pchar, GOOD_COTTON) > 0
	&& GetSquadronGoods(pchar, GOOD_LEATHER) > 0
	&& GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0
	&& GetCharacterFreeItem(pchar, "talisman9") > 0
	&& GetCharacterFreeItem(pchar, "suit1") > 0
	&& GetCharacterFreeItem(pchar, "tailor_tool") > 0)
	return true;
	
	return false;
}
