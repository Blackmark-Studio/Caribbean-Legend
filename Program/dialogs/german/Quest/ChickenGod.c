int questShips[50];
int questShipsNum = 0;

extern void InitGunExt(string id,			
				string sAttr,       
				string sBullet,     
				string sGunPowder,  
				float  DmgMin_NC,   
				float  DmgMax_NC,   
				float  DmgMin_C,    
				float  DmgMax_C,    
				float  EnergyP_NC,  
				float  EnergyP_C,   
				bool   Stun_NC,     
				bool   Stun_C,      
				bool   MultiDamage, 
				int    MisFire,     
				bool   SelfDamage,  
				bool   Explosion,   
				float  Accuracy,    
				int    ChargeSpeed, 
				bool   isDefault );

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp, attr, companion;
	ref chref;
	int iTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string node = Dialog.CurrentNode;
	if(HasSubStr(node, "joruba_p3_ship_")) {
		iTemp = findsubstr(node, "joruba_p3_ship_", 0);
	 	companion = strcut(node, iTemp + strlen("joruba_p3_ship_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p3";
	}
	
	if(HasSubStr(node, "joruba_p4_off_")) {
		iTemp = findsubstr(node, "joruba_p4_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_p4_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p4_off";
	}

	if(HasSubStr(node, "joruba_o6_off_")) {
		iTemp = findsubstr(node, "joruba_o6_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_o6_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_o6_off";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Du sollst das nicht sehen.";
			link.l1 = "Zeit, einen Fehlerbericht einzureichen.";
			link.l1.go = "exit";
		break;
		
        case "native":
			dialog.text = "Uh-oh! Ta'kahi, junger Mann. Ich möchte nicht unhöflich sein, aber wie sind Sie hier reingekommen? Ich habe der Madame dringend geraten, das Etablissement für die Dauer meines Aufenthalts zu schließen.";
			link.l1 = "Uh-oh in der Tat. Wie haben sie dich reingelassen? Warum wurde dieses Bordell noch nicht von zornigen gottesfürchtigen Menschen niedergebrannt?";
			link.l1.go = "native_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Panama");
		break;
		
        case "native_1":
			dialog.text = "Goldene Dublonen öffnen alle Wege und machen weiße Menschen glücklicher. Wusstest du das nicht?";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text+" Ich kann den fast verwitterten Geruch von Versailles spüren, wo du mit solch einem Quietschen hineingelassen wurdest.";
			}
			link.l1 = "Rede nicht so mit mir, Rotgesicht. Es ist wahr, dass ich neu hier bin, obwohl ich nicht weiß, wie du Wind davon bekommen hast. Ich könnte dich genau dort erschießen, wo du stehst, und jede Frau für die Nacht bekommen, um die Unannehmlichkeiten wettzumachen.";
			link.l1.go = "native_var1";
			link.l2 = "Ich weiß nicht, wer dir diesen Unsinn erzählt hat, aber du redest ziemlich geschmeidig, das gebe ich zu. Es ist das erste Mal, dass ich einen so gebildeten Eingeborenen gesehen habe.";
			if (HasSubStr(pchar.model, "Sharle")) {
				link.l2 = link.l2+"Versailles, mein Arsch!";
			}
			link.l2.go = "native_var2";
		break;
		
        case "native_var1":
			dialog.text = "Nein, Kapitän, du weißt nichts. Ich bin hier vollkommen sicher... fürs Erste. Da wir jedoch so schnell so vertraut geworden sind, lass es uns nochmal versuchen. Trinken?";
			link.l1 = "Ich kann das tun, du hast definitiv mein Interesse geweckt.";
			link.l1.go = "native_play";
		break;
		
        case "native_var2":
			dialog.text = "Bravo! Ich sehe, wir sind bereits beim Du und tauschen Sticheleien aus. Jetzt schlage ich vor, wir trinken auf den Frieden und sprechen über Geschäfte.";
			link.l1 = "Ich kann das tun, du hast definitiv mein Interesse geweckt.";
			link.l1.go = "native_play";
		break;
		
        case "native_play":
			dialog.text = "Angesichts des Zwecks dieses Ortes beunruhigt mich Ihr Kommentar, Kapitän, ziemlich! Ich stecke hier seit fast einem Monat fest. Habe alles versucht, was mir einfällt, und bin bereit, vor Langeweile und Sinnlosigkeit die Wände hochzugehen.";
			link.l1 = "Verlasse dann. Besuche mal eine Kirche... in die sie dich nicht reinlassen werden.";
			link.l1.go = "native_play_1";
		break;
		
        case "native_play_1":
			dialog.text = "Es ist nicht so einfach, da ich laut meinem... Vertrag verpflichtet bin, weitere vierundzwanzig Stunden in diesem Bordell zu verbringen.";
			link.l1 = "Klingt natürlich schrecklich, aber von mir bekommst du kein Mitleid. Eine exklusive Bordellmiete für einen Monat ist ein Traum, der wahr wird!";
			link.l1.go = "native_play_2";
		break;
		
        case "native_play_2":
			dialog.text = "Fürchte deine Wünsche, Kapitän. Ich weiß nicht, wie du hierher gekommen bist, denn ich sollte diesen Monat alleine verbringen. Alleine mit Squaw und Wein, aber ich konnte nur bis zum dritten Tag oder so Wein trinken. Und heute war der Tag, an dem ich es auch satt hatte.";
			link.l1 = "Und was soll ich tun? Soll ich mit dir eine Ladung Mädchen und Wein teilen?";
			link.l1.go = "native_play_3";
		break;
		
        case "native_play_3":
			dialog.text = "Vielleicht, aber ich schlage vor, wir zocken zuerst! Tausend Silber pro Karte! Übrigens, mein Name ist Agueybana.";
			link.l1 = "Meins ist "+GetFullName(pchar)+". Sicher, lass uns spielen.";
			link.l1.go = "native_accept";
			link.l2 = "Mein ist "+GetFullName(pchar)+". Tausend Pesos? Nicht schlecht. Ich werde darüber nachdenken, aber keine Versprechungen.";
			link.l2.go = "native_decline";
		break;
		
        case "native_play_again":
			dialog.text = "Haben Sie Ihre Meinung geändert, Kapitän? Sollen wir?";
			link.l1 = "Sicher, warum zur Hölle nicht.";
			link.l1.go = "native_accept";
			link.l2 = "Noch nicht.";
			link.l2.go = "native_decline";
		break;
		
        case "native_decline":
			DialogExit();
			
			NextDiag.CurrentNode = "native_play_again";
		break;
		
        case "native_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1");
		break;
		
        case "native_cards_loss":
			dialog.text = "Danke für das Spiel, Kapitän. Ich dachte, es würde mich besser fühlen lassen, aber das tat es nicht. Bitte lass mich in Ruhe - irgendwie werde ich noch einen Tag alleine zurechtkommen. Verdammt sei dieser Bastard!";
			link.l1 = "Das ist alles? Zugegebenermaßen ist meine Enttäuschung größer als die Bitterkeit, eine Menge Geld zu verlieren.";
			link.l1.go = "native_cards_loss_1";
		break;
		
        case "native_cards_loss_1":
			dialog.text = "Sie sollten gar nicht hier sein, Kapitän. Aber wenn Sie herausfinden wollen, worum es eigentlich ging... suchen Sie nach einem alten Tempel auf dem Kontinent. Und bringen Sie viel Tuunich Kaane' mit. Hier, nehmen Sie einen.";
			link.l1 = "Ein Adderstein? Ein Stein mit einem Loch passt definitiv zum Ort. Danke, Agueybana";
			link.l1.go = "native_cards_loss_2";
		break;
		
        case "native_cards_loss_2":
			dialog.text = "Auf Wiedersehen, Kapitän.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game1LossGoAway");
		break;
		
        case "native_cards_win":
			dialog.text = "Uh-oh! Danke, Kapitän! Schade um das Geld, aber zumindest habe ich wieder einen Hauch von Leben gespürt!";
			link.l1 = "Ja, das ist das erste Mal, dass ich jemanden so aufgeregt über eine Route wie diese gesehen habe. Wo hast du eigentlich all das Geld her?";
			link.l1.go = "native_cards_win_1";
		break;
		
        case "native_cards_win_1":
			dialog.text = "Eine unverschämte Frage, die du niemals deinem Gleichgestellten stellen würdest, Kapitän! Aber die Nacht ist noch jung, und ich habe noch eine Menge Münzen übrig. Wie wäre es mit einem Rückspiel?";
			link.l1 = "Warum zur Hölle nicht? Lass uns noch einen machen!";
			link.l1.go = "native_cards_win_2";
		break;
		
        case "native_cards_win_2":
			dialog.text = "Ich schlage vor, dieses Mal würfeln wir und erhöhen ein bisschen den Einsatz. Ich habe auch eine Geschichte zu erzählen, also miete bitte ein Zimmer oben für uns beide. Zu viele Ohren hier! Ich würde es schätzen, wenn du zur Madame gehst und für das Zimmer bezahlst. Mein Kredit gilt leider nicht für dich.";
			link.l1 = "Mieten Sie ein Zimmer? Für zwei? Hier? Fick dich, Agueybana! Ich bin hier raus!";
			link.l1.go = "native_cards_rematch_decline";
			link.l2 = "Oh, was zur Hölle. Diese Geschichte endet entweder als gute Anekdote oder als sehr teures Blutbad. Mein Schwert bleibt bei mir, also keine lustigen Geschäfte, ha-ha! Warte hier, ich werde das klären.";
			link.l2.go = "native_cards_rematch_accept";
		break;
		
        case "native_cards_rematch_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinNoRematch");
		break;
		
        case "native_cards_rematch_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinRematch");
		break;
		
        case "native_dice":
			dialog.text = "So?";
			link.l1 = "Ich hoffe aufrichtig, Sie haben mich nur wegen Alkohol und Glücksspiel hierher gerufen.";
			link.l1.go = "native_dice_1";
		break;
		
        case "native_dice_1":
			dialog.text = "Mach dir keine Sorgen, Kapitän, ich bin nicht an solchem Unsinn interessiert! Obwohl, wenn du am ersten Tag hier aufgetaucht wärst... ha ha! Sollen wir anfangen?";
			link.l1 = "Dem Tüchtigen hilft das Glück!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game2");
		break;
		
        case "native_dice_win":
			dialog.text = "Uh-oh! Das fühlt sich gut an! Herzlichen Glückwunsch zu Ihrem Sieg, Kapitän.";
			link.l1 = "Übertreib es nicht. Zeit, dass du mich aufklärst, was zum Teufel hier vor sich geht?";
			link.l1.go = "native_dice_story";
			link.l2 = "Du bist seltsam, Agueybana. Wenn ich diesen Ort nicht sofort verlasse, wird mein Ruf als Edelmann und Mann unwiderruflich beschädigt. Gib mir mein Silber und lass uns unsere Wege trennen.";
			link.l2.go = "native_dice_win_not_story";
		break;
		
        case "native_dice_loss":
			dialog.text = "Wie schade, ich hatte gehofft, den Tag auf einer anderen Note zu beenden...";
			link.l1 = "Das ist das erste Mal, dass ich einen Mann so aufgebracht über den Sieg in diesem plebejischen Spiel sehe. Kannst du mich nun wenigstens darüber aufklären, was zum Teufel hier vor sich geht?!";
			link.l1.go = "native_dice_story";
			link.l2 = "Fick dich, Agueybana! Ich habe genug davon!";
			link.l2.go = "native_dice_loss_not_story";
		break;
		
        case "native_dice_story":
			dialog.text = "So viel ich kann, Kapitän. Ich bin mir nicht sicher, ob ich das darf, aber dennoch, Sie haben meine letzten Tage erhellt... In diesem Bordell, meine ich.";
			link.l1 = "Und worum ging es dabei?";
			link.l1.go = "native_dice_story_1";
		break;
		
        case "native_dice_story_1":
			dialog.text = "Macht nichts... Hör zu, weißer Mann! Ich bin der große Häuptling der Taino-Leute, Agueybana. Manchmal träume ich davon, dass ich hundert Jahre früher geboren wurde und die spanischen Eindringlinge von meinen Inseln vertrieb! Aber stattdessen habe ich dreitausend meiner Stammesgenossen für zehn Dublonen pro Kopf an die Minen verkauft.";
			link.l1 = "Eine würdige Biografie. Ich habe plötzlich das Verlangen, dich, Agueybana, zu erschießen und dich in dieser sauren, nach Wein riechenden Müllhalde verrotten zu lassen.";
			link.l1.go = "native_dice_story_2";
		break;
		
        case "native_dice_story_2":
			dialog.text = "Egal, Kapitän. Alles was ich je wollte, war wie du zu sein.";
			link.l1 = "Wie ich?";
			link.l1.go = "native_dice_story_3";
		break;
		
        case "native_dice_story_3":
			dialog.text = "Ich habe eure Schiffe gesehen - Wunder der menschlichen Genialität - und ich wollte selbst eines haben. Ich habe eure Frauen in engen Korsetts gesehen und davon geträumt, eines meiner eigenen auszuziehen. Ich habe sogar die elendigsten eurer Kommandanten Macht ausüben sehen, die über die Träume eines unserer Anführer hinausgeht. Geschichten über Europa und die riesigen Steinhäuser, in denen die Menschen leben anstatt zu überleben, habe ich gehört. Und ich hatte all das! Darüber hinaus war ich sogar in Europa und all das im vergangenen Jahr!";
			link.l1 = "Du hast zu viel Wein getrunken, Häuptling. Die einzigen Tickets nach Europa für dich wären Ketten, zur Freude des Vatikans und der Straßenkünstler. Was du redest, ist in der Welt, in der wir leben, einfach unmöglich.";
			link.l1.go = "native_dice_story_4";
		break;
		
        case "native_dice_story_4":
			dialog.text = "Das ist die Welt, in der wir leben, Kapitän. Mir wurde bereits erklärt, dass unsere Welt falsch, imaginär ist und alles möglich ist.";
			link.l1 = "Und wer war der Klugscheißer, der dir das erzählt hat? Anscheinend lassen sie dich nicht nur in Bordelle, sondern auch in Irrenanstalten!";
			link.l1.go = "native_dice_story_5";
		break;
		
        case "native_dice_story_5":
			dialog.text = "Nun kommen wir zum Punkt meiner Geschichte. Ihr wisst doch, wie es hier läuft, oder? Die Spanier und Engländer bezahlen für unsere Kriegsgefangenen mit Waffen, Werkzeugen und Schießpulver. Ich habe für meine Stammesgenossen mit eurem Geld bezahlt. Warum glaubt ihr, ist das so?";
			link.l1 = "Ich habe das Gefühl, du wirst mich gleich erleuchten.";
			link.l1.go = "native_dice_story_6";
		break;
		
        case "native_dice_story_6":
			dialog.text = "Nur die Götter können unsere tiefsten und beschämendsten Wünsche erfüllen. Wenn du das Leben, das du willst, nicht leben kannst, dann bitte sie, in das Schicksal einzugreifen. Nur sie können unsere tiefsten und beschämendsten Wünsche erfüllen. Das ist der Weg. Aber hier ist das Problem: Fast alle unsere Götter sind bereits tot, und selbst wenn sie es nicht wären, waren sie nie an Gold interessiert. Glücklicherweise verabscheut die Natur ein Vakuum, und ein neuer Gott ist in einer der alten Pyramiden aufgetaucht. Es ist ihm egal, wer du bist: Einheimischer oder Europäer, Schurke oder Held - zahle einfach und du bekommst, was du verlangst! Alle Stämme wissen das, und einige deiner Leute auch. Ich habe den Preis in Gold bezahlt und wie einer von euch gelebt. Morgen wird es ein Jahr sein.";
			link.l1 = "Welcher Gott? Nach Europa und zurück in einem Jahr? Und der Höhepunkt deiner Reise war ein lausiges Bordell in der Karibik? Ach, was soll's. Klingt wie eine Trunkenboldgeschichte, und ich kaufe sie als solche. Lass uns einen trinken und mit deiner Geschichte weitermachen.";
			link.l1.go = "native_dice_story_7";
		break;
		
        case "native_dice_story_7":
			dialog.text = "Alles, was ich dir erzählt habe, ist die Wahrheit. Es gibt nichts mehr zu erzählen.";
			link.l1 = "Du hast noch nicht lange genug in unserer Welt gelebt, Agueybana. Jedes durch Alkohol inspirierte Märchen, besonders eines, das betrunken in einem Bordell erzählt wird, muss mit einer Moral enden. Wir sollten definitiv philosophieren, bevor wir unser Salon ordentlich beenden.";
			link.l1.go = "native_dice_story_8";
		break;
		
        case "native_dice_story_8":
			dialog.text = "Wie enden sie normalerweise?";
			link.l1 = "Du weißt es nicht? Das hängt natürlich vom Geschlecht des Teilnehmers ab! Prügele mit den Männern, nimm Frauen mit ins Bett. Manchmal gebietet die Mode allerdings das Gegenteil. Also, was ist die Moral deiner Fabel? Geld kauft kein Glück? Langweilig!";
			link.l1.go = "native_dice_story_9";
		break;
		
        case "native_dice_story_9":
			dialog.text = "Das ist nicht die Moral meiner Fabel, wie du es ausdrückst. Aber da du es angesprochen hast, fühle ich den Drang zu sagen, dass ich nicht mit deinem Punkt übereinstimme. Im Gegenteil, ich glaube, dass Geld Glück kauft und Menschen verbessert.";
			link.l1 = "Unsinn! Du scheinst dir jetzt selbst zu widersprechen. Du hast ein beträchtliches Vermögen durch den Handel mit deinen eigenen Leuten angehäuft. Erinnerst du dich an die gesamte Summe, die du daraus geschlagen hast? Fast dreißigtausend Goldmünzen? Denk einen Moment nach, aber für mich ist klar, dass Geld dir kein Glück gekauft hat. Es hat dir allerdings diese schöne Suite gekauft.";
			link.l1.go = "native_dice_story_10";
		break;
		
        case "native_dice_story_10":
			dialog.text = "Gut, ich werde meinen anfänglichen Standpunkt korrigieren: Geld macht das Leben und die Menschen besser.";
			link.l1 = "Das ist besser, aber was lässt dich denken, dass es die Leute besser macht? Du bist also jetzt ein Musterbeispiel für Tugend? Und was ist mit denen, die nicht viel Geld haben? Werden wir sie als schlechte Menschen abstempeln?";
			link.l1.go = "native_dice_story_11";
		break;
		
        case "native_dice_story_11":
			dialog.text = "Sie wissen, Kapitän, ich schätze dieses Gespräch wirklich. Lassen Sie mich noch einmal klarstellen: Geld macht das Leben und die Menschen besser, aber nur diejenigen, die bereits einen Funken Tugend besitzen.";
			link.l1 = "Hört, hört! Also, kein Funke für dich, was?";
			link.l1.go = "native_dice_story_12";
		break;
		
        case "native_dice_story_12":
			dialog.text = "Nein. Ich war der Anführer meines Volkes und, im Gegensatz zu Geld, korrumpiert Macht definitiv Männer. Weißt du was, Kapitän? Ich schaue dich jetzt an und erkenne, dass du eines Tages vor dem gleichen Dilemma stehen wirst.";
			link.l1 = "Nein. Ich war der Anführer meines Volkes und, im Gegensatz zu Geld, korrumpiert Macht definitiv Männer. Weißt du was, Kapitän? Ich schaue dich jetzt an und erkenne, dass du eines Tages vor dem gleichen Dilemma stehen wirst.";
			link.l1.go = "native_dice_story_13";
		break;
		
        case "native_dice_story_13":
			dialog.text = "Lassen wir unser... ähem, Salon ohne Schlägereien und Betten beenden, bitte. Ich habe es versäumt, eine Moral für meine Geschichte zu erfinden, also möchte ich stattdessen einen Toast vorschlagen.";
			link.l1 = "Hört, hört!";
			link.l1.go = "native_dice_story_14";
		break;
		
        case "native_dice_story_14":
			dialog.text = "Hier ist auf das, was wir wollen, immer dem entspricht, was wir brauchen. Danke, Kapitän, das ist ein passendes Ende für... unseren Abend. Wenn du eines Tages die Wahrheit meiner Fabel testen möchtest, gehe zum Kontinent und finde dort einen alten Tempel. Bring hundertdreizehn 'tuunich kaane' mit. Ich habe noch neunundneunzig - nimm sie und lebe wohl!";
			link.l1 = "Ein Haufen Steine mit Löchern? Passt gut zur Lage. Danke für den Abend, Agueybana. Sehen wir uns wieder?";
			link.l1.go = "native_dice_story_15";
		break;
		
        case "native_dice_story_15":
			dialog.text = "Nein, das wirst du nicht. Auf Wiedersehen, Kapitän.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_BuyAmulets");
		break;
		
        case "native_dice_win_not_story":
			dialog.text = "Ich verstehe, Kapitän. Zum Guten oder zum Schlechten, ich gebe Ihnen einen Hinweis auf den Schatz. Immerhin haben Sie meine letzten Tage erleuchtet... In diesem Bordell, meine ich. Suchen Sie nach einem antiken Tempel im großen Land und bringen Sie einen Haufen Tuunich Kaane' dazu. Hier, nehmen Sie eins.";
			link.l1 = "Eine Schlangenstein? Wie charmant und ein Stein mit einem Loch passt definitiv zum Ort. Ich habe genug von deiner Behandlung!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_loss_not_story":
			dialog.text = "Ich verstehe, dass du verärgert bist, Kapitän. Zum Besseren oder zum Schlechteren, ich gebe dir einen Hinweis auf den Schatz. Schließlich hast du meine letzten Tage aufgehellt... In diesem Bordell, meine ich. Suche nach einem alten Tempel im großen Land und bringe einen Haufen Tuunich Kaane' dorthin. Hier, nimm einen.";
			link.l1 = "Eine Adder-Stein? Wie charmant und ein Stein mit einem Loch passt definitiv zur Lage. Ich habe genug von deiner Behandlung!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_not_story":
			dialog.text = "Auf Wiedersehen, Kapitän.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotBuyAmulets");
		break;
		
		case "joruba":
			dialog.text = "Noch einer? Oh verdammt, ich bin so satt von euch allen!";
			link.l1 = "A-a-ah! Verschwinde!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_1";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_1":
			dialog.text = "Eh? Ja, richtig. Verneige dich vor mir, Sterblicher! Sieh die Macht meiner Pyramide!";
			link.l1 = "(schreit verzweifelt)";
			link.l1.go = "joruba_2";
			link.l2 = "(töte das Monster)";
			link.l2.go = "joruba_3";
		break;
		
		case "joruba_2":
			dialog.text = "Das stimmt. Willkommen in meiner bescheidenen Faktorei, Kapitän.";
			link.l1 = "W-was bist du?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_3":
			DialogExit();
			
			NextDiag.CurrentNode = "joruba_3_next";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_3_next":
			dialog.text = "Ich bewundere Ihre Hartnäckigkeit. Was ist Ihr nächster Schritt, Kapitän? Wie wäre es mit etwas Handel?";
			link.l1 = "W-was bist du?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_4":
			dialog.text = "Es ist egal, wer ich bin, es kommt auf die Funktion an, die ich ausübe. Im Moment mache ich Handelsabkommen mit den Bewohnern dieses Rattenlochs zum gegenseitigen Vorteil.";
			link.l1 = "Das Rattenloch? Du meinst diesen Tempel?";
			link.l1.go = "joruba_6";
			
			AddDialogExitQuestFunction("ChickenGod_JorubaToNormal");
		break;
		
		case "joruba_6":
			dialog.text = "Deine erste und letzte Warnung, Kapitän! Diese Pyramide ist allerdings tatsächlich etwas eng, offensichtlich bin ich ihr entwachsen.";
			link.l1 = "Du hast etwas von Handel gesagt. Welche Art von Handel meinst du?";
			if (CheckAttribute(pchar, "questTemp.ChickenGod.SawJoruba")) {
				link.l1.go = "joruba_7A";
			} else {
				link.l1.go = "joruba_7";
			}
		break;
		
		case "joruba_7":
			dialog.text = "Ich gebe, was die Leute am meisten brauchen.";
			link.l1 = "Du erfüllst Wünsche? Wie ein Dschinn aus einem Märchen? Lieber Herr, was geht hier vor?!";
			link.l1.go = "joruba_7_1";
		break;
		
		case "joruba_7_1":
			dialog.text = "Sei nicht absurd! Ich helfe Menschen nur dabei, auf schnellstmögliche und angenehmste Weise das zu bekommen, für das sie in diese Welt gekommen sind.";
			link.l1 = "Bist du ein Schamane oder so etwas?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_7A":
			dialog.text = "Nun, du hast Agueybana getroffen, das sollte dir einige Ideen geben.";
			link.l1 = "Dieser arme, verlorene und betrunkene Indianer war dein Werk?";
			link.l1.go = "joruba_7A_1";
		break;
		
		case "joruba_7A_1":
			dialog.text = "Es war nicht ich, der seinen Stamm für ein paar tausend Pfund Gold verkauft hat, es war nicht ich, der Fässer voller Schnaps in seinen Hals geschüttet hat, und sicherlich habe ich ihn nicht gezwungen, jede Krankheit, bekannte und unbekannte, von hunderten von Huren aufzugreifen. Er bat mich, ihn in einen weißen Aristokraten zu verwandeln, also habe ich das getan. Wie es sein Schicksal von mir verlangte.";
			link.l1 = "Du erfüllst Wünsche? Wie ein Dschinn aus einem Märchen? Lieber Herr, was geht hier vor?!";
			link.l1.go = "joruba_7A_2";
		break;
		
		case "joruba_7A_2":
			dialog.text = "Sei nicht lächerlich! Ich helfe den Menschen nur dabei, auf schnellste und angenehmste Weise zu bekommen, was sie in diese Welt gekommen sind. Agueybana sollte sein Volk vor dem Joch der europäischen Eindringlinge retten, aber stattdessen sabberte er zu sehr über das Korsett der Tochter des Kommandanten und entschied sich, sein eigenes zu verpfänden\nVon da an war die einzige Bedeutung in seinem Leben, die Tiefe seines Fehlers zu erkennen und bald neu zu beginnen. Ein Jahr in Europa, Zirrhose und die Zeit, die ihr beide im Bordell verbracht habt, müssen geholfen haben. Aber ich gebe zu, er hatte einen tollen Urlaub, ha ha!";
			link.l1 = "Cirrho was? Bist du ein Schamane oder so etwas?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_8":
			dialog.text = "Oder so was. Aber mein Angebot wird dir gefallen. Und zur Abwechslung werde ich wirklich gerne helfen.";
			link.l1 = "Richtig. Wie viel?";
			link.l1.go = "joruba_9A";
			link.l2 = "Warum? Bin ich etwas Besonderes?";
			link.l2.go = "joruba_9B";
		break;
		
		case "joruba_9A":
			dialog.text = "Nicht zu schlecht, Kapitän. Entweder bist du schlau oder dumm wie ein Esel, aber deine Chancen sind gerade ein wenig gestiegen. Der Preis wird kein Problem sein.";
			link.l1 = "Müssen Sie jemanden umbringen? Das mache ich nicht.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_9B":
			dialog.text = "Weil dein Zweck in diesem Leben darin besteht, Löcher in einen guten Freund von mir zu machen, ha ha!";
			link.l1 = "Müssen Sie jemanden töten? Das mache ich nicht.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_10":
			dialog.text = "Zuerst, du tust. Zweitens, wir werden vier größere Transaktionen durchführen und vier weitere kleinere. Jeder wird dich viel stärker machen und deine Chancen in dieser grausamen und seltsamen Welt erhöhen. Wenn du jeden Deal abschließt, garantiere ich, dass du eines Tages in der Lage sein wirst, herauszugehen und mit Göttern auf gleicher Augenhöhe zu kämpfen, ganz zu schweigen von gewöhnlichen Sterblichen.";
			link.l1 = "Hört sich nach Spaß an. Erzähl mir davon.";
			link.l1.go = "joruba_11";
		break;
		
		case "joruba_11":
			dialog.text = "Kluge Wahl! Normalerweise führen meine Reden dazu, dass Leute mit Verdacht auf Herzinfarkt nach Blueweld abtransportiert werden, aber du hältst dich ziemlich gut. Hier ist die Aufgabenliste: kleine Besorgungen von Tauschhandel, die ich von dir erwarte. Keine Fristen, hehe.";
			link.l1 = "Interessant. Ich werde die Liste später lesen. Noch etwas?";
			link.l1.go = "joruba_12";
		break;
		
		case "joruba_12":
			dialog.text = "Ja, die erste große Transaktion. Zweitausend Dublonen ist der Preis.";
			link.l1 = "Vielleicht beiße ich an... Aber das ist viel Geld! Warum brauchst du so viel? Kann ich in Pesos bezahlen?";
			link.l1.go = "joruba_13";
			link.l2 = "Bist du verrückt? Mit dem Geld kann ich eine Fregatte kaufen!";
			link.l2.go = "joruba_insult";
		break;
		
		case "joruba_13":
			dialog.text = "Die Pyramide muss repariert werden - die Mauerarbeit fällt manchmal auf die Köpfe der Kunden und das ist schlecht für das Geschäft. Meine Männer flicken sie jeden Tag, aber unsere Organisation braucht dringend Geld von außen, um die Situation endgültig zu beheben. Was Pesos betrifft - ich mag sie nicht besonders, da ihr Wechselkurs ziemlich volatil ist.";
			link.l1 = "Sie sind einfach unfair gegenüber ehrlichen Pesos... Moment mal, Sie sind nicht alleine hier?";
			link.l1.go = "joruba_14";
		break;
		
		case "joruba_14":
			dialog.text = "Nein, ich bin die Fassade einer seriösen Organisation. Also, bist du dabei?";
			link.l1 = "Ich werde darüber nachdenken, aber zuerst möchte ich wissen, was ich für eine solch stattliche Summe bekomme.";
			link.l1.go = "joruba_15";
		break;
		
		case "joruba_15":
			dialog.text = "Warum die Überraschung verderben? Außerdem, betrachte dieses Geld einfach als Steuer. Dein wertvollster Erwerb wird das Freischalten der nächsten Geschäfte sein. Die Belohnungen werden göttlich sein. Auch einzigartig, denn du wirst sie nirgendwo anders finden!";
			link.l1 = "Gut. Wie war noch mal dein Name?";
			link.l1.go = "joruba_16";
		break;
		
		case "joruba_16":
			dialog.text = "Aruba der Prächtige. Eine letzte Sache, "+pchar.name+", der Eintritt in die Pyramide ist nur einmal am Tag erlaubt. Verzögern Sie nicht andere Kunden und belästigen Sie mich nicht umsonst.";
			link.l1 = "Ich sehe die Schlange nicht sich aufreihen... Lebewohl, Eure Majestät.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			AddDialogExitQuestFunction("ChickenGod_GiveFirstTask");
		break;
		
		case "joruba_wait":
			dialog.text = "Ahoi, Kapitän. Was hast du für mich?";
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1.Completed") && PCharDublonsTotal() >= 2000) {
				link.p1 = "Here are your doubloons. It's hard enough to carry that damned metal around... but it is even harder to part with it!";
				link.p1.go = "joruba_p1";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2.Completed") && GetCharacterItem(pchar, "cannabis7") >= 15) {
				link.p2 = "I kept my end of the bargain. Here's your herb, Aruba.";
				link.p2.go = "joruba_p2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3.Completed") && ChickenGod_FindQuestShips()) {
				for (i = 0; i < questShipsNum; i++) {
					sTemp = "p3_" + (i + 1);
				
					chref = GetCharacter(questShips[i]);
					sld = GetRealShip(sti(chref.ship.type));
					link.(sTemp) = "Aruba, ahoy! " + GetStrSmallRegister(XI_ConvertString(sld.BaseName)) + " '" + chref.Ship.Name + "' is all yours!";
					link.(sTemp).go = "joruba_p3_ship_" + questShips[i];
					if (FindCompanionShips(SHIP_PINK) && sti(pchar.questTemp.ChickenGod.Tasks.Schyot) <= 1 && startHeroType != 4)
					{
						link.(sTemp) = "Aruba, ahoy! Pink '" + chref.Ship.Name + "' is all yours!";
						link.(sTemp).go = "joruba_p3_PinkOtkaz";
					}
					/*if (FindCompanionShips(SHIP_GALEON_SM))
					{
						link.(sTemp) = "Aruba, ahoy! Galeon '" + chref.Ship.Name + "' is all yours!";
						link.(sTemp).go = "joruba_p3_HolyMercy";
					}*/
				}
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.p3 = "I'm willing to make a sacrifice.";
				link.p3.go = "joruba_p4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Lady") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Completed")) {
				link.o2 = "I am bringing you a bride and troubles with the Spanish authorities, sir. The lady is taking a stroll outside, well protected by my men. I will not give her to you until you convince me of the nobility of your intentions.";
				link.o2.go = "joruba_o2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3.Completed") && GetCharacterFreeItem(pchar, "cirass4") >= 1) {
				link.o3 = "Here's your armor, Aruba. Make sure my reward will make up for it.";
				link.o3.go = "joruba_o3";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4.Completed") && GetPrisonerQty() >= 30) {
				link.o4 = "I have the prisoners you asked for.";
				link.o4.go = "joruba_o4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5.Completed") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.p2 = "I brought you your junk. Here, a hundred and thirteen stones, just like you asked for.";
				link.p2.go = "joruba_o5";
			}
			
			bOk = (PCharDublonsTotal() >= 25000) || (ChickenGod_HaveOfficers());
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.Completed") && bOk) {
				link.p3 = "I'm willing to make a sacrifice.";
				link.p3.go = "joruba_o6";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.respec = "(Respec character's stats)";
				link.respec.go = "joruba_respec";
			}
			
			link.exit = "I am just passing by.";
			link.exit.go = "joruba_wait_1";
			
			NextDiag.TempNode = "joruba_wait";
		break;
		
		case "joruba_wait_1":
			dialog.text = "Nächstes Mal dann.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "joruba_p1":
			dialog.text = "Nicht schlecht, ich werde dieses Gold gut gebrauchen. Hier, ein kleiner Anhänger, der zuvor einem sehr tugendhaften Taino-Häuptling gehörte. Hilft beim Tragen von Goldhaufen. Hat ihm sicherlich geholfen, heh-heh...";
			link.l1 = "Danke und hoffe, ich werde es nicht bereuen. Was ist der nächste Handel?";
			link.l1.go = "joruba_p1_1";
			link.l2 = "Warte mal eine Minute. Ich habe dir einen Haufen Gold gegeben und im Gegenzug einen Klumpen Ton bekommen? Nun, ich brauche eine Rückerstattung!";
			link.l2.go = "joruba_insult";
			
			RemoveDublonsFromPCharTotal(2000);
			pchar.questTemp.ChickenGod.Gold = 2000;
			
			pchar.questTemp.ChickenGod.Tasks.p1.Completed = true;
			GiveItem2Character(pchar, "talisman13");
			//Log_info("You received Taino Figurine");
			PlaySound("interface\important_item.wav");
		break;
		
		case "joruba_p1_1":
			dialog.text = "Eh? Ja, der nächste Handel. Dieses Gold sollte fürs Erste ausreichen, also ist es an der Zeit, über spirituellere Waren nachzudenken. Ich muss ein Heilmittel finden.";
			link.l1 = "Wie, bist du krank?";
			link.l1.go = "joruba_p1_2";
		break;
		
		case "joruba_p1_2":
			dialog.text = "Meine Seele ist. Siehst du, Priester meiden meine bescheidene Pyramide seit dem Vorfall mit der Inquisition, also müssen wir uns auf traditionellere Methoden verlassen. Ich brauche, nun, meine Faktorei braucht fünfzehn Magarosa-Pflanzen, um betriebsbereit zu bleiben.";
			if (!ChickenGod_TalkedToAmelia()) {
				link.l1 = "Ist das ein Kraut?";
			} else {
				link.l1 = "Ich weiß, was es ist, heh-heh.";
			}
			link.l1.go = "joruba_p1_3";
		break;
		
		case "joruba_p1_3":
			dialog.text = "Ich werde ehrlich sein - es handelt sich um eine seltene und sehr wertvolle Pflanze. Überlege es dir gut, ob du wirklich Jahre damit verbringen willst, sie im gesamten Archipel zu sammeln?";
			link.l1 = "Keine Versprechungen, aber ich wünsche dir gute Gesundheit und hoffe, dass meine Belohnung für das Kraut es wert sein wird.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveSecondTask");
		break;
		
		case "joruba_p2":
			dialog.text = "In Ordnung, ich erkläre diesen Tag offiziell zu meinem freien Tag! Ein Schnäppchen wie dieses ist einen echten Schatz wert. Sieh her!\nDiese Machete war einmal kurz davor, den Kopf dieses Tölpels Kanek zu zerschmettern! Daher ist sie mir sehr lieb und ich bitte Sie demütig, gut darauf aufzupassen. Sie ist alt, aber äußerst gut gearbeitet, solchen Stahl gibt es heutzutage nicht mehr.";
			link.l1 = "Kanek? Wer ist das?";
			link.l1.go = "joruba_p2_1";
			
			TakeNItems(pchar, "cannabis7", -15);
			pchar.questTemp.ChickenGod.Tasks.p2.Completed = true;
			if (pchar.rank >= 21)
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 80.0;
			}
			else
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 60.0;
			}
			GiveItem2Character(pchar, "machete2");
			//Log_info("You received Machete Conquistador");
			PlaySound("interface\important_item.wav");
			SetAlchemyRecipeKnown("bullet_double");
			SetAlchemyRecipeKnown("grapeshot_double");
			ChickenGod_InitAmmo();
		break;
		
		case "joruba_p2_1":
			dialog.text = "Oh, ihr beide werdet euch treffen. Nun, ich hoffe, du bist nicht einer dieser aufgeblasenen Arschlöcher, die Handarbeit verachten? Wenn ja, hast du Scheiße aus Glück, denn der zweite Teil der Belohnung sind die Pläne für doppelt geladene Munition.";
			if (pchar.HeroParam.HeroType == "HeroType_4") {
				link.l1 = "Oh, ich liebe diese. Aber was ist so besonders daran? Eine doppelte Pulverladung ist keine Neuigkeit, also schließe ich daraus, dass du offensichtlich seit den Zeiten dieses Museums-Machete deine Pyramide nicht verlassen hast.";
			} else {
				link.l1 = "Das ist alles? Hey...";
			}
			link.l1.go = "joruba_p2_2";
		break;
		
		case "joruba_p2_2":
			dialog.text = "Sei kein Schlaukopf und hör zu! Jeder Idiot kann zwei Haufen Schießpulver in ein Fass stecken und riskiert dabei blind zu werden, sich das Gesicht zu verbrennen oder die Nase zu brechen. Ich biete dir einen kleinen Zaubertrick an: Prüfe die Qualität des Pulvers sorgfältig, mahle es auf die richtige Konsistenz, stecke eine Kugel oder Schrot hinein und würze es mit einem gehackten Dublonen. Der Knall wird selbst einen Kürass in Fetzen reißen!";
			link.l1 = "Geld schießen, hm? So typisch für dich.";
			link.l1.go = "joruba_p2_3";
		break;
		
		case "joruba_p2_3":
			dialog.text = "Du bist unerträglich! Gut, schnapp dir eine Handgranate und dazu ein Dutzend Granaten. Wenn du so verdammt schlau bist, wirst du in kürzester Zeit die Pläne für die Granaten selbst beschaffen!";
			link.l1 = "Vielen Dank, mein Herr. Was kommt als nächstes?";
			link.l1.go = "joruba_p2_4";
			
			//Log_info("You received Hand mortar");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "mortairgun");
			TakeNItems(pchar, "grenade", 10);
		break;
		
		case "joruba_p2_4":
			dialog.text = "Du wirst es nicht lieben. Ich brauche ein Schiff... nein, ich brauche das Schiff. Du weißt schon, mit einer Geschichte dahinter.";
			link.l1 = "Warum? Du bist nicht einmal ein Kapitän.";
			link.l1.go = "joruba_p2_5";
		break;
		
		case "joruba_p2_5":
			dialog.text = "Das geht dich nichts an! Konzentriere dich lieber auf deine Belohnung, denn ich könnte verlangen, dass du diese Pyramide von oben bis unten säuberst, und du wärst mir immer noch etwas schuldig!";
			link.l1 = "Du bist definitiv kein Kapitän, sonst wüsstest du, dass ein Schiff einen Pier oder eine Bucht zum Anlegen braucht. Wie zum Teufel erwartest du, dass ich ein Schiff in deine Pyramide bekomme?!";
			link.l1.go = "joruba_p2_6";
		break;
		
		case "joruba_p2_6":
			dialog.text = "Hast du zufällig einen riesigen See hinter meiner Pyramide bemerkt? Das ist richtig. Dock einfach mit dem richtigen Schiff in der nahegelegenen Staffel an und meine Männer erledigen den Rest. Jetzt raus hier, du hältst die Linie auf.";
			link.l1 = "Aber natürlich. Tschüss!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveThirdTask");
		break;
		
		case "joruba_p3":
			sld = GetCharacter(sti(companion));
			pchar.questTemp.ChickenGod.Tasks.p3.ship = sld.ship.type;
			RemoveCharacterCompanion(pchar, sld);
			AddPassenger(pchar, sld, false);
						
			npchar.ship.type = pchar.questTemp.ChickenGod.Tasks.p3.ship;
			SetCharacterShipLocation(npchar, "Temple");
						
			sld = GetRealShip(sti(pchar.questTemp.ChickenGod.Tasks.p3.ship));
					
			dialog.text = "Schön! Verstanden!";
			link.l1 = "Lass deine Schlauheit beiseite und gib mir meine Belohnung!";
			link.l1.go = "joruba_p3_1";
			switch (sti(sld.BaseType)) {
				case SHIP_MAYFANG:
					dialog.text = "Was ist mit den anderen beiden? Konntest du sie nicht für dich selbst retten? Heh-heh.";
				break;
				
				case SHIP_MIRAGE:
					dialog.text = "Was ist mit den anderen beiden? Konntest du sie nicht für dich behalten? Heh-heh.";
				break;
				
				case SHIP_VALCIRIA:
					dialog.text = "Was ist mit den anderen beiden? Konntest du sie nicht für dich selbst retten? Heh-heh.";
				break;
				
				case SHIP_FRIGATE_L:
					dialog.text = "Scheiße, ich bin beeindruckt, dass du sie nicht für dich behalten wolltest. Das nenne ich mal ein Schiff mit Geschichte! Verdammt, William... Ich wünschte wirklich, du würdest nach Hause zurückkehren und eine großartige Bank gründen, wie du es dir immer erträumt hast.";
				break;
				
				case SHIP_CORVETTE_QUEST:
					sTemp = "privateer";
					if (isMainCharacterPatented()) {
						sTemp = GetStrSmallRegister(GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur)));
					}
					
					dialog.text = "Würden Sie sich das ansehen! Sie sind eine Schande für Ihren Auftrag, "+sTemp+"!";
				break;
				
				case SHIP_POLACRE_QUEST:
					dialog.text = "Charlie Prince hat beschlossen, belastende Beweise in meiner alten Pyramide loszuwerden? Ich billige!";
				break;
				
				case SHIP_ECLIATON:
					dialog.text = "Viel Glück dabei, Ihren Vorgesetzten den Verlust des Flaggschiffs zu erklären, Admiral. Oh, entschuldigen Sie mich, Generalgouverneur.";
				break;
				
				case SHIP_CURSED_FDM:
					dialog.text = "Bist du ein abergläubischer Narr oder einfach nur ein Narr? Sie ist ein Vermögen wert! Ich bin mir nicht sicher, ob es ein fairer Tausch ist, aber was auch immer.";
				break;
				
				case SHIP_FDM:
					dialog.text = "Bist du ein abergläubischer Narr oder einfach nur ein Narr? Sie ist ein Vermögen wert! Ich bin mir nicht sicher, ob es ein fairer Handel ist, aber was auch immer.";
				break;
				
				case SHIP_RENOVATED_FDM:
					dialog.text = "Bist du ein abergläubischer Narr oder einfach nur ein Narr? Sie ist ein Vermögen wert! Ich bin mir nicht sicher, ob es ein fairer Handel ist, aber was auch immer.";
				break;
				
				case SHIP_ELCASADOR:
					dialog.text = "Gute Entscheidung! Ich liebe die Kastilier, weißt du. Vielleicht gebe ich sie ihnen zurück, wenn ich fertig bin.";
				break;
				
				case SHIP_HIMERA:
					dialog.text = "Wahrhaftig, es fehlt Ihnen an einem Herzen, Kapitän. Dieses Schiff stinkt nach Verrat. Ich werde es übernehmen.";
				break;
				
				case SHIP_PINK:
					if (startHeroType == 4)
					{
						dialog.text = "Aye, dieses Schiff mag eine Geschichte haben... aber war es nicht zu einfach zu bekommen? Ah, gut. Dein Fall ist speziell, meine Liebe, also nehme ich es. Bringt zumindest einige Erinnerungen an meine Jugend zurück.";
						Achievment_Set("ach_CL_127");
					}
					else 
					{
						dialog.text = "Aye, dieses Schiff mag eine Geschichte haben ... aber war es nicht zu einfach zu bekommen? Ach, was soll's. In Ordnung, Käpt'n, ich lasse das durchgehen, da du einen großartigen Job mit den Aufgaben auf meiner Liste gemacht hast. Ich nehme es. Bringt zumindest einige Erinnerungen an meine Jugend zurück.";
					}
				break;
				
				case SHIP_GALEON_SM:
					dialog.text = "Und hast du den Priester gesehen? Nun, du wirst ihn treffen. Und du solltest dich besser mit Doppelschuss-Pistolenladungen eindecken. Wenn das nicht hilft - versuche es mit einem Holzpflock.";
				break;
				
				case SHIP_LADYBETH:
					dialog.text = "Und hast du den Priester gesehen? Nun, du wirst ihn treffen. Und du solltest dich besser mit Doppelschuss-Pistolenladungen eindecken. Wenn das nicht hilft - versuche es mit einem Holzpflock.";
				break;
			}
		break;
		
		/*case "joruba_p3_HolyMercy":
			dialog.text = "Und hast du den Priester gesehen?";
			link.l1 = "Welcher Priester?";
			link.l1.go = "joruba_p3_HolyMercy_2";
		break;
		
		case "joruba_p3_HolyMercy_2":
			dialog.text = "Nun, du wirst ihn treffen. Und du solltest dich besser mit Doppelschuss-Pistolenladungen eindecken. Wenn das nicht hilft - versuche es mit einem Holzpflock.";
			link.l1 = "...";
			link.l1.go = "joruba_p3_1";
		break;*/
		
		case "joruba_p3_PinkOtkaz":
			dialog.text = "Jawohl, dieses Schiff mag eine Geschichte haben... aber war es nicht zu einfach zu bekommen? Auf keinen Fall! Du hast noch einen Haufen unerledigter Arbeit auf der Liste. Wenn du das erledigt hast, werden wir dieses Opfer nochmal besprechen.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "joruba_p3_1":
			dialog.text = "Ich segne dich, "+GetFullName(pchar)+". Möge das Meer Ihnen günstig sein. Nun, diskutieren wir die nächste Transaktion...";
			link.l1 = "Warte, was? Sogar Tölpel fallen in unserem Zeitalter der Vernunft nicht auf solchen Unsinn herein! Ich habe keinen Centime in deine Spendenbox gesteckt, ich habe dir ein vollwertiges Kriegsschiff gegeben!";
			link.l1.go = "joruba_insult";
			link.l2 = "Halt eine Sekunde. Was genau bedeutet dein Segen für mich?";
			link.l2.go = "joruba_p3_2";
			
			pchar.questTemp.ChickenGod.Tasks.p3.Completed = true;
		break;
		
		case "joruba_p3_2":
			dialog.text = "Jedes Schiff, das du beherrschst, wird von nun an mit einem stärkeren Rumpf gesegnet sein, während deine Feinde das Gegenteil erleiden werden. Auch wird die Zeit auf See für dich langsamer vergehen. Und wenn das nicht genug ist, um dieses ganze Dreckloch in die Knie zu zwingen, solltest du besser zu deinem Vater gehen und eine Rückerstattung verlangen!";
			link.l1 = "Wenn es nicht funktioniert, schwöre ich, ich komme heute Nacht zurück und brenne deine Pyramide nieder! Erzähl mir von dem nächsten Handel!";
			link.l1.go = "joruba_p3_3";
			notification("+10% hull defence", "None");
			notification("+10% damage to enemy ships hull", "None");
			notification("+5% speed on the Global Map", "None");
			PlaySound("Interface\new_level.wav");
		break;
		
		case "joruba_p3_3":
			dialog.text = "Entwickelst du etwa einen Geschmack dafür, eh Kapitän? Unglücklicherweise für dich, ich auch. Warum glaubst du, habe ich diese Pyramide als mein Büro gewählt?";
			link.l1 = "Wahrscheinlich, weil die Hexenverfolgung immer noch eine Sache ist?";
			link.l1.go = "joruba_p3_4";
		break;
		
		case "joruba_p3_4":
			dialog.text = "Heh-heh, nein, nicht ganz. Ich führe mein Geschäft hier durch, weil die besten Geschäfte Blut erfordern. Diese Pyramide erfordert Blut. Ich erfordere Blut. So war es, so wird es sein.";
			link.l1 = "Denk nicht einmal daran, du Ungeheuer. Ich werde keine Opfer für dich zum Töten liefern!";
			link.l1.go = "joruba_p3_5";
		break;
		
		case "joruba_p3_5":
			dialog.text = "Und wie viele hast du getötet, hm? Warte, ich werde dir sogar die genaue Zahl sagen: du hast persönlich getötet "+(Statistic_AddValue(pchar,"Lötzinn_s",0)+Statistic_AddValue(pchar,"Bürger_s",0)+Statistic_AddValue(pchar,"Krieger_s",0)+Statistic_AddValue(pchar,"Löten_g",0)+Statistic_AddValue(pchar,"Bürger_g",0)+Statistic_AddValue(pchar,"Krieger_g",0))+" Leute! Ihr habt einen Berg von Leichen auf dem Altar eurer Ambition und Gier nach Reichtum gelegt! ";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text+"Die Schulden deines Bruders haben bereits mehr Menschen getötet als ein durchschnittlicher europäischer Krieg! ";
			}
			dialog.text = dialog.text+"Moralpredigten kannst du dir hier sparen, besonders weil ich dich nicht beurteilen werde. Der Erfolg einiger wird immer von den Tragödien anderer bezahlt, und die Götter, oh, Götter, sie werden zusehen und ihren Anteil einfordern!";
			link.l1 = "Ich kann dir jetzt keine Antwort geben... Ich muss hier raus.";
			link.l1.go = "joruba_p3_6";
		break;
		
		case "joruba_p3_6":
			dialog.text = "Eine dringende Notwendigkeit, deinen Kopf zu klären? In Ordnung, aber hör mir zuerst zu. Ich werde dir Macht und vollständige Kontrolle über deinen Körper und Geist geben, wenn du mir einen Mann von großem Wert bringst. Nicht einen Statisten, nicht eine gesichtslose graue Maus von den Straßen oder eine Ratte aus den stinkenden Bilgen. Bring mir einen Mann, der dir folgt und eine wichtige Rolle in deiner Tragikomödie spielt.";
			link.l1 = "Einer meiner Offiziere? Du kannst nicht tiefer sinken, Aruba! Wenn das rauskommt...";
			link.l1.go = "joruba_p3_7";
		break;
		
		case "joruba_p3_7":
			dialog.text = "Ich werde wie immer für Geheimhaltung sorgen. Und bevor du wieder anfängst zu jammern, lasse ich dich wissen, dass es einen anderen Weg gibt.";
			link.l1 = "Was soll das bedeuten? Also muss ich meine eigenen Leute nicht zum Altar schleppen?";
			link.l1.go = "joruba_p3_8";
		break;
		
		case "joruba_p3_8":
			dialog.text = "Nein, aber die Alternative wird dir nicht gefallen. Wenn du nicht mit Blut bezahlen willst, kannst du mit Gold bezahlen. Dreitausend Dublonen und ein reines Gewissen. Geld kann das und mehr - ich liebe es!";
			link.l1 = "Tschüss, Aruba. Ich möchte nicht mehr mit dir reden.";
			link.l1.go = "joruba_p3_9";
		break;
		
		case "joruba_p3_9":
			dialog.text = "Du weißt, wo du mich finden kannst.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveFourthTask");
		break;
		
		case "joruba_p4":
			dialog.text = "Lass uns das schnell machen, bevor die Spanische Inquisition auftaucht. Blut oder Gold?";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Gold ist es. Hier sind deine dreitausend, obwohl ich mir nicht vorstellen kann, wie du einen so enormen Betrag in dieser Wildnis ausgeben kannst.";
				link.l1.go = "joruba_p4_1";
			}
			if (ChickenGod_HaveOfficers()) 
			{
				link.l2 = "Blut.";
				link.l2.go = "joruba_p4_other";
			}
			link.l3 = "Macht nichts.";
			link.l3.go = "exit";
		break;
		
		case "joruba_p4_1":
			dialog.text = "...";
			link.l1 = "Bist du fertig? Lass uns über meine Belohnung sprechen.";
			link.l1.go = "joruba_p4_reward_1";
			RemoveDublonsFromPCharTotal(3000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 3000;
		break;
		
		case "joruba_p4_other":
			dialog.text = "So sei es. Nenne den Namen.";
			
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Irons");
		break;
		
		case "joruba_p4_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand ist kein Offizier, sondern ein rücksichtsloser Söldner, also wähle ein anderes Opfer.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "Ich akzeptiere deine Huldigung. Du musst nicht zusehen.";
			link.l1 = "Nein, das tue ich nicht. Ich komme in einer Stunde zurück, um meine Belohnung abzuholen.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_p4_reward";
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
		break;
		
		case "joruba_o6_money":
			dialog.text = "Tolle Wahl. Ich hasse es, den Altar von all dem Blut zu säubern, also ist Gold vorzuziehen. Hier, nehmen Sie diesen Trank - ein Kompliment von einem guten Freund von mir.";
			link.l1 = "Der Geschmack ist gar nicht schlecht...";
			link.l1.go = "exit";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			RemoveDublonsFromPCharTotal(25000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 25000;
			
			if (sti(pchar.questTemp.ChickenGod.Gold) >= 30000) {
				Achievment_Set("ach_CL_87");
			}
			
			notification("+3 P.I.R.A.T.E.S. point", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_p4_reward":
			dialog.text = "";
			link.l1 = "Bist du fertig? Lass uns über meine Belohnung sprechen.";
			link.l1.go = "joruba_p4_reward_1";
		break;
		
		case "joruba_p4_reward_1":
			dialog.text = "Sprechen Sie mich jederzeit an, wenn Sie Ihr Schicksal ändern möchten.";
			link.l1 = "Aber was bedeutet das genau für mich?";
			link.l1.go = "joruba_p4_reward_2";
		break;
		
		case "joruba_p4_reward_2":
			dialog.text = "Macht über dich selbst! Versuche es manchmal und du wirst es lieben. In der Zwischenzeit, lass mich dir von der nächsten Transaktion erzählen. Der wichtigsten.";
			link.l1 = "Ich bin mir nicht mehr sicher, ob es das wert ist!";
			link.l1.go = "joruba_p4_reward_3";
			link.l2 = "Los, spuck's schon aus.";
			link.l2.go = "joruba_p4_reward_3";
		break;
		
		case "joruba_p4_reward_3":
			dialog.text = "Sie haben die Möglichkeit, nicht nur Ihr Schicksal zu ändern, sondern neben den Genies und Göttern unserer Zeit zu stehen. Ja, Sie können Ihren Körper und Geist jetzt so viel ändern, wie Sie wollen, aber Sie werden nie über Ihren Kopf springen, denn ein gewöhnlicher Mensch kann nicht in allem gut sein. Was ich vorschlage, ist, dass Sie diese Grenzen durchbrechen.";
			link.l1 = "Was wird es mich kosten? Mehr Blut? Gold?";
			link.l1.go = "joruba_p4_reward_4";
		break;
		
		case "joruba_p4_reward_4":
			dialog.text = "Jawohl. Entweder du bringst mir fünfundzwanzigtausend Dublonen oder einen deiner Gefährten. Sobald wir fertig sind, wird es keine weiteren Transaktionen geben.";
			link.l1 = "Ich werde es mir überlegen.";
			link.l1.go = "joruba_p4_reward_5";
		break;
		
		case "joruba_p4_reward_5":
			dialog.text = "Du weißt, wo du mich finden kannst. Und zögere nicht, mich jederzeit zu besuchen, wenn du dein Schicksal ändern möchtest.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			
			pchar.questTemp.ChickenGod.Tasks.p4.Completed = true;
			AddDialogExitQuestFunction("ChickenGod_GiveFifthTask");
		break;
		
		case "joruba_respec":
			dialog.text = "Wie du wünschst.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ChickenGod_Respec");
		break;
		
		case "joruba_o2":
			dialog.text = "Zunächst einmal, das ist meine Frau, keine Braut. Zweitens, du hast ein Problem mit den Kastilier, nicht mit mir. Und schließlich habe ich sie bereits genommen und deine Männer abgewiesen. Und was ehrenwerte Absichten angeht... Schau mich an, bin ich nicht ein Muster eines anständigen Gentleman? Tlazolteotl, segne ihn, dass er eines Tages auch eine echte Frau kennen darf. Oder einen Mann.";
			link.l1 = "Leck mich, Aruba!";
			link.l1.go = "exit";
			
			notification("+ 10 HP, + 10 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(10.0);
			pchar.questTemp.ChickenGod.Tasks.o2.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			sld = CharacterFromID(pchar.questTemp.ChickenGod.Tasks.o2.Lady);
			RemovePassenger(pchar, sld);
			ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto1");
			LAi_SetCitizenTypeNoGroup(sld);
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o3":
			dialog.text = "Nicht schlecht, danke. Ehrlich gesagt, ich brauche es wirklich nicht, aber vielleicht werde ich es in irgendeinem Salon oder so tragen. Im Namen von Ishtar segne ich dich. Jetzt geh und sündige.";
			link.l1 = "Was für ein seltsames Gefühl...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o3.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			TakeItemFromCharacter(pchar, "cirass4");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o4":
			dialog.text = "Ich nehme sie. Was? Ich brauche Tote in meiner Mannschaft, genau wie du, nur dass ich im Gegensatz zu dir nicht in Tavernen rekrutieren kann. Nun, Bast, segne den Helden für seine zukünftigen Unternehmungen.";
			link.l1 = "Was für ein seltsames Gefühl...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o4.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
			
			AddDialogExitQuestFunction("ChickenGod_RemovePrisoners");
		break;
		
		case "joruba_o5":
			dialog.text = "Ja, wir werden sie zurückstreuen müssen, weil die Leute sie ständig verlieren, und wir brauchen Kunden. Freya, schütze diesen großartigen Steinsammler.";
			link.l1 = "Was für ein seltsames Gefühl...";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o5.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6":
			dialog.text = "Lass uns das schnell machen, bevor die spanische Inquisition auftaucht. Blut oder Gold?";
			
			if (PCharDublonsTotal() >= 25000)
			{
				link.money = "Here's your gold, you greedy bastard.";
				link.money.go = "joruba_o6_money";
			}
			
			if (ChickenGod_HaveOfficers())
			{
				link.blood = "Blood.";
				link.blood.go = "joruba_o6_blood";
			}
			link.l3 = "Macht nichts.";
			link.l3.go = "exit";
		break;
		
		case "joruba_o6_blood":
			dialog.text = "Sag den Namen.";
			
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Irons");
			
			if (!CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Helena");
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Mary");
			}
		break;
		
		case "joruba_o6_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Mary" || pchar.questTemp.ChickenGod.Sacrifice == "Helena") {
				pchar.questTemp.ChickenGod.Tasks.o6.gf = true;
				sTemp = "future wife";
				sld = CharacterFromID(pchar.questTemp.ChickenGod.Sacrifice);
				if (sld.lastname == pchar.lastname) {
					sTemp = "current wife";
				}
				
				dialog.text = "Das ist durchaus verlockend, aber ich werde nur dieses eine Mal eine Ausnahme machen - Ich werde dein Opfer nicht annehmen. Ich werde das nicht an deinen "+sTemp+", obwohl ich es wahrscheinlich sollte. Denk dran, dass du ohne sie nichts bist. Jetzt, verschwinde und belästige mich heute nicht.";
				link.l1 = "";
				link.l1.go = "exit";
				
				AddDialogExitQuestFunction("ChickenGod_KickedFromTemple");
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand ist kein Offizier, sondern ein rücksichtsloser Söldner, also wähle ein anderes Opfer.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "So sei es. Hier, nimm diesen Trank - ein Kompliment von einem guten Freund von mir.";
			link.l1 = "Der Geschmack ist gar nicht so schlecht...";
			link.l1.go = "joruba_o6_reward";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			notification("+3 P.I.R.A.T.E.S. points", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6_reward":
			dialog.text = "Bis zum nächsten Mal, Kapitän.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.OnExitKick = true;
		break;
		
		case "joruba_final":
			dialog.text = "Ahoi! Endlich ist alles vorbei!";
			link.l1 = "Hä?";
			link.l1.go = "joruba_final_1";
		break;
		
		case "joruba_final_1":
			dialog.text = "Wir sind hier fertig, Kapitän. Die Geschäfte sind abgeschlossen, jeder ist zufrieden und es gibt keinen Raum für Rückzahlungen. Unser Büro schließt und zieht um.";
			link.l1 = "Wartet einen Moment, Aruba. Ich habe dir viel Gold gegeben, mit Blut bezahlt, Frauen und Gefangene in dieses teuflische Versteck gebracht. Ich kann übernatürliche Ereignisse, die anscheinend in der Karibik auftreten, bewältigen. Aber unsere 'Transaktionen' mit dir trotzen jeder Logik. Bitte erkläre.";
			link.l1.go = "joruba_final_2";
		break;
		
		case "joruba_final_2":
			dialog.text = "You know what? I'll tell you.\nI'm fed up with this world, and I want out. Every day, it's the same old routine: an ancient pyramid with a crumbling ceiling, those loathsome identical palm trees, and a never-ending stream of captains, each with their own ingenious ideas. Yes, I provide people with what they desire; it's my calling, and I take pride in it. But by the gods, how I detest all of you!";
			link.l1 = "Hält dich jemand hier fest? Der Ausgang ist direkt dort, Genie!";
			link.l1.go = "joruba_final_3";
		break;
		
		case "joruba_final_3":
			dialog.text = "Du hast absolut recht, niemand hält mich mehr hier. Nicht mehr. Und das alles dank dir, mein Freund.";
			link.l1 = "Das ist ein plötzlicher Sinneswandel. Ich erwartete eine Geschichte, aber bisher habe ich nur die bedeutungslosen Tiraden eines abscheulichen kleinen Gottes in einer staubigen Pyramide gehört.";
			link.l1.go = "joruba_final_4";
		break;
		
		case "joruba_final_4":
			dialog.text = "Nun, jeder muss sich von Zeit zu Zeit Luft machen, nicht wahr? Ich bin wirklich froh, dass du hierher gekommen bist, denn dank dir kann ich endlich von dieser Welt abfahren. Gold, Besatzung, Ausrüstung und ein Schiff, mein Freund. Erinnert dich das an etwas? Das ist alles, was ich brauchte, und du hast es mir alles zur Verfügung gestellt.";
			link.l1 = "Sie sind willkommen. Allerdings klärt das immer noch nicht Ihre eigenartige Art zu sprechen und fast göttlichen Kräfte. Wenn Sie so allmächtig sind, hätten Sie schon vor langer Zeit Ihr eigenes Schiff, Ihre eigene Mannschaft und Gold herbeizaubern können!";
			link.l1.go = "joruba_final_5";
		break;
		
		case "joruba_final_5":
			dialog.text = "Was ich getan habe, wie du sehen kannst. Jeder hat seine eigenen Methoden.";
			link.l1 = "Aber wie in aller Welt? Wer sind Sie genau?";
			link.l1.go = "joruba_final_6";
		break;
		
		case "joruba_final_6":
			dialog.text = "Nun... das ist einfach das, was ich mache. Wir sehen uns in der neuen Welt, "+GetPersonaName()+". Wirklich neu beim nächsten Mal hoffe ich. Danke und auf Wiedersehen.";
			link.l1 = "Nein, ich will dich nie wieder sehen.";
			link.l1.go = "exit";
			link.l2 = "Dann bis später, Aruba... das war interessant.";
			link.l2.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_FinalGood");
		break;
		
		case "joruba_insult":
			dialog.text = "Sieht aus, als wären alle Deals geplatzt. Zeit zu gehen, Kapitän.";
			link.l1 = "Zeit für dich zu v...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Insult");
		break;
		
		case "ChickenGod_TheInquisition_1":
			dialog.text = "Im Namen der spanischen Inquisition, nenne dich selbst!";
			link.l1 = "Kapitän "+GetFullName(pchar)+". Und es ist wahr, was sie sagen, niemand erwartet die spanische Inquisition...";
			link.l1.go = "ChickenGod_TheInquisition_2";
		break;
		
		case "ChickenGod_TheInquisition_2":
			dialog.text = "... Dieser Witz trifft immer ins Schwarze, obwohl er schon so manchen unschuldigen Christen auf den Scheiterhaufen gebracht hat.";
			link.l1 = "...";
			link.l1.go = "ChickenGod_TheInquisition_3";
		break;
		
		case "ChickenGod_TheInquisition_3":
			dialog.text = "Nur ein Scherz, Kapitän. Sie haben einen Scherz gemacht, und ich habe einen Scherz gemacht. Mein Name ist Padre Emilio Bocanegra und diese Soldaten Christi sind meine bewaffneten Wächter.";
			link.l1 = "Was kann ich für Sie tun, Padre?";
			link.l1.go = "ChickenGod_TheInquisition_4";
		break;
		
		case "ChickenGod_TheInquisition_4":
			dialog.text = "Kennen Sie einen gewissen Senor Aruba?";
			link.l1 = "Ja, er lebte bis vor kurzem in dieser alten Pyramide.";
			link.l1.go = "ChickenGod_TheInquisition_5";
		break;
		
		case "ChickenGod_TheInquisition_5":
			dialog.text = "Was meinst du, er hat dort gelebt? Ist es möglich, dort zu leben? Und warum 'bis vor kurzem'?";
			link.l1 = "Dieser Señor hat uns vor ein paar Minuten auf einem Schiff verlassen.";
			link.l1.go = "ChickenGod_TheInquisition_6";
		break;
		
		case "ChickenGod_TheInquisition_6":
			dialog.text = "Wie wissen Sie das? Die nächste Bucht ist Tage entfernt!";
			link.l1 = "Dieser See muss größer sein, als er aussieht. Ich habe keine andere Erklärung für dich, Padre.";
			link.l1.go = "ChickenGod_TheInquisition_7";
		break;
		
		case "ChickenGod_TheInquisition_7":
			dialog.text = "Seltsame Dinge geschehen in den Ländereien des Vizekönigreichs.";
			link.l1 = "Dies sind englische Ländereien, Padre.";
			link.l1.go = "ChickenGod_TheInquisition_8";
		break;
		
		case "ChickenGod_TheInquisition_8":
			dialog.text = "Lassen Sie die Ketzer weiterhin so denken. Wir werden sicher unseres zurückbekommen. Verzeihen Sie mir, mein Sohn, dass ich so viele Fragen stelle: Santiago hat mich beauftragt, eine offizielle Untersuchung dieser Pyramide ... und ihres ehemaligen Bewohners durchzuführen.";
			link.l1 = "Was genau ist passiert, padre?";
			link.l1.go = "ChickenGod_TheInquisition_9";
		break;
		
		case "ChickenGod_TheInquisition_9":
			dialog.text = "Da der Fall wahrscheinlich geschlossen wird, kann ich euch mit einer kleinen Geschichte unterhalten.\nGerüchte über diesen Ort kursieren schon seit einiger Zeit überall auf dem Main. Wir hatten zuverlässige Berichte erhalten, dass eine Reihe von Personen, die in der Geschichte der Region eine bedeutende Rolle gespielt hatten, hier in der Vergangenheit regelmäßige Besuche abgestattet hatten.\nJedoch begann Santiago, diesen Gerüchten nach dem Panama-Vorfall wirklich Beachtung zu schenken.\nEin bestimmter Indianer hatte in jener glorreichen Stadt großen Wirbel verursacht und sogar mehrere Predigten von eher philosophischer Natur gehalten. Leider zogen die Einwohner von Panama eher oberflächliche Schlüsse und überzeugten sich selbst, dass diese Pyramide unermessliche Schätze birgt und alle Wünsche erfüllt.\nNatürlich reinster Irrglaube... also mussten wir gegen einige Einwohner von Panama und diesen Indianer, Aguebana, verfahren.";
			link.l1 = "Warum haben die panamaischen Behörden nicht durchgegriffen?";
			link.l1.go = "ChickenGod_TheInquisition_10";
		break;
		
		case "ChickenGod_TheInquisition_10":
			dialog.text = "Wie immer in solchen Fällen behaupteten sie, verhext zu sein. Diese juristische Lücke hätte geschlossen werden können, wenn wir Aguebana befragt hätten, aber er starb plötzlich.";
			link.l1 = "Wie ist er gestorben?";
			link.l1.go = "ChickenGod_TheInquisition_11";
		break;
		
		case "ChickenGod_TheInquisition_11":
			dialog.text = "Der Trunkenheit hat ihn umgebracht. Sein Tod hat jedoch unsere Probleme nicht gelöst, denn die Ketzerei hatte sich über das gesamte Archipel ausgebreitet, und Hunderte von Menschen unternahmen eine Art Pilgerfahrt zu diesem alten Tempel.";
			link.l1 = "Ich habe noch nie Menschenmassen hier gesehen... Also was, du wolltest Aruba einnehmen und ihn vor Gericht stellen?";
			link.l1.go = "ChickenGod_TheInquisition_12";
		break;
		
		case "ChickenGod_TheInquisition_12":
			dialog.text = "Natürlich nicht, mein Sohn. Das Urteil der Inquisition ist hart, aber fair. Es muss einen guten Grund für einen Prozess geben. Nein, ich wollte nur senor Arubas Aussage sammeln und sie nach Santiago liefern.";
			link.l1 = "Nun, das ist unglücklich für dich.";
			link.l1.go = "ChickenGod_TheInquisition_13";
		break;
		
		case "ChickenGod_TheInquisition_13":
			dialog.text = "Man weiß nie, mein Sohn. Es ist Gottes Wille.";
			link.l1 = "Auf Wiedersehen, Padre.";
			link.l1.go = "ChickenGod_TheInquisition_14";
		break;
		
		case "ChickenGod_TheInquisition_14":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Temple", "reload2", false);
			LAi_SetActorType(npchar);
			//LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "ChickenGod_TheInquisitionLeave", -1);
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition = "ChickenGod_TheInquisitionLeave";
		break;
		
	}
} 

void ChickenGod_InitAmmo() {
	if(LoadSegment("items\initItems.c")) {
		InitGunExt(		 "pistol1", "t3", 	 "bullet_double",               "", 100.0, 300.0,  60.0, 260.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 40, 20, 0);
		InitGunExt( 	 "pistol2", "t2", "grapeshot_double",               "",  60.0, 160.0,  20.0, 100.0,  0.0,  0.0, 0, 1, 1, 0, 1, 1, 40, 20, 0);
		InitGunExt(		 "pistol3", "t2", "grapeshot_double",               "",  80.0, 180.0,  30.0, 110.0,  0.0,  0.0, 0, 1, 1, 2, 1, 1, 40, 20, 0);
		InitGunExt(		 "pistol4", "t3",    "bullet_double",               "",  70.0, 270.0,  30.0, 230.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 35, 30, 0);
		InitGunExt(		 "pistol5", "t3", 	 "bullet_double",               "", 130.0, 330.0,  90.0, 290.0,  0.0,  0.0, 1, 0, 0, 2, 0, 0, 70, 30, 0);
		InitGunExt(		 "pistol6", "t3",    "bullet_double",               "", 100.0, 300.0,  60.0, 260.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 50, 20, 0);
		InitGunExt(		 "pistol8", "t4", "grapeshot_double",               "",  50.0, 100.0,  30.0,  60.0,  5.0,  5.0, 1, 1, 1, 0, 1, 1, 20, 20, 0);
		InitGunExt(		 "pistol9", "t3", 	 "bullet_double",               "", 100.0, 320.0,  80.0, 280.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 40, 30, 0);
		InitGunExt(		 "pistol10", "t3",   "bullet_double",               "", 140.0, 280.0, 100.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 45, 30, 0);
		InitGunExt(		 "pistol11", "t3",   "bullet_double",               "",  10.0, 700.0,  10.0, 620.0, 40.0, 30.0, 1, 1, 0, 0, 0, 0, 45,100, 0);
		InitGunExt(		 "pistol12", "t3",   "bullet_double",               "",  80.0, 290.0,  60.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 45, 20, 0);
		InitGunExt(		 "pistol13", "t3",   "bullet_double",               "", 130.0, 300.0,  90.0, 260.0, 15.0,  0.0, 1, 1, 0, 0, 0, 0, 60, 30, 0);
		InitGunExt(		 "howdah",  "t3", "grapeshot_double",	            "",  50.0, 140.0,  30.0,  70.0,  5.0,  5.0, 1, 1, 1, 0, 0, 1, 50, 30, 0);
		InitGunExt(		 "pistol14", "t3",   "bullet_double",               "", 130.0, 330.0,  90.0, 290.0,  0.0,  0.0, 1, 0, 0, 4, 0, 0, 70, 34, 0); // Дуэльный двухзарядный пистоль cle 1.3
		
		UnloadSegment("items\initItems.c");
	}
	
	CGInitGrapeGunExt(	"pistol2",	"t2",		3,		50,		4.25,	5.0,	3);		// трёхствольный дробовик, двойной заряд
	CGInitGrapeGunExt(	"pistol3",	"t2",		4,		40,		6.0,	5.0,	4);		// тромбон, двойной заряд
	CGInitGrapeGunExt(	"pistol8",	"t4",		4,		110,	5.0,	3.0,	2);		// бландербуз, двойной заряд
	CGInitGrapeGunExt(	"howdah",	"t3",		3,		85,		3.0,	5.5,	2);		// гауда, двойной заряд
	CGInitGrapeGunExt(	"mushket3",	"t2",		3,		60,		6.0,	3.0,	3);		// аркебуза, картечь
	CGInitGrapeGunExt(	"mushket6",	"t3",		3,		90,		4.0,	3.5,	2);		// башенный мушкетон, картечь
}

void CGInitGrapeGunExt(string id, string sAttr, int basedmg, int shards, float width, float height, int dispersion)
{
	ref gun = ItemsFromID(id);
	gun.type.(sAttr).basedmg = basedmg;
	gun.type.(sAttr).shards = shards;
	string sArea = "grapes_area_"+dispersion;
	gun.type.(sAttr).area = XI_ConvertString(sArea);
	gun.type.(sAttr).width = width;
	gun.type.(sAttr).height = height;
}

bool ChickenGod_FindQuestShips() {
	questShipsNum = 0;
	
	for(int i = 1; i < COMPANION_MAX; i++) {
		int index = GetCompanionIndex(pchar, i);
		if (index < 0) {
			continue;
		}
		
		sld = GetCharacter(index);
		int shipIndex = sti(sld.ship.type);
		if (shipIndex == SHIP_NOTUSED) {
			continue;
		}
		
		ref realShip = GetRealShip(shipIndex);
		if (!CheckAttribute(realShip, "QuestShip")) {
			continue;
		}
		
		if (!GetRemovable(sld) || !GetShipRemovable(sld)) {
			continue;
		}
		
		if (CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip")) {
			if (sti(realShip.BaseType) == SHIP_MAYFANG || sti(realShip.BaseType) == SHIP_MIRAGE || sti(realShip.BaseType) == SHIP_VALCIRIA) {
				continue;
			}
		}
		
		questShips[questShipsNum] = sti(sld.index);
		questShipsNum++;
	}
	
	return (questShipsNum > 0);
}

void ChickenGod_AddOfficerLink(aref link, string prefix, string id) {
	if (GetCharacterIndex(id) < 0) {
		return;
	}
	
	if (!CheckPassengerInCharacter(pchar, id)) {
		return;
	}
	
	if (id == "Mary" && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) {
		return;
	}
	
	if (id == "Helena" && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
		return;
	}
	
	sld = CharacterFromID(id);
	
	if (!GetRemovable(sld)) {
		return;
	}
	
	link.(id) = GetFullName(sld) + ".";
	link.(id).go = prefix + id;
}

bool ChickenGod_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}

bool ChickenGod_HaveOfficers() {
	object fakelink;
	
	ChickenGod_AddOfficerLink(&fakelink, "", "Duran");
	ChickenGod_AddOfficerLink(&fakelink, "", "Baker");
	ChickenGod_AddOfficerLink(&fakelink, "", "Folke");
	ChickenGod_AddOfficerLink(&fakelink, "", "Avendel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tonzag");
	if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(&fakelink, "", "Longway");
	ChickenGod_AddOfficerLink(&fakelink, "", "Knippel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tichingitu");
	ChickenGod_AddOfficerLink(&fakelink, "", "Irons");
	
	if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
		ChickenGod_AddOfficerLink(&fakelink, "", "Helena");
		ChickenGod_AddOfficerLink(&fakelink, "", "Mary");
	}
	
	return (GetAttributesNum(&fakelink) > 0);
}
