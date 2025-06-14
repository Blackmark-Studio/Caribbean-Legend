void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			dialog.text = "Was wollen Sie?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";
		break;

		// Диалог с Алонсо после успешного абордажа
		case "Memento_MortimerGrimDead_Alonso_1":
			dialog.text = "Käpt’n, der Tag gehört uns. Die Vorhut beendet gerade die Säuberung des unteren Decks. Keine Gefangenen… Ha! Ich sehe, auch Sie haben keine Gnade gezeigt.";
			link.l1 = "Irgendwie habe ich von ihm eine pathetische Rede erwartet. Aber er stürzte sich sofort in den Kampf.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_2";
			Achievment_Set("ach_CL_154");
		break;

		case "Memento_MortimerGrimDead_Alonso_2":
			dialog.text = "Erlauben Sie mir, offen zu sprechen?";
			link.l1 = "Erlaubt.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_3";
			link.l2 = "Nein, wir sind hier fertig.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_end";
		break;

		case "Memento_MortimerGrimDead_Alonso_3":
			dialog.text = "Warum haben wir sie angegriffen? Diese Brigg stellte keinerlei Bedrohung dar, transportierte keine Waren. Über Grim gab es viele Gerüchte, aber gefürchtet wurde er nur von Sklavenhändlern. Heute haben Sie viele getötet – und wofür?";
			if (sti(pchar.questTemp.ISawDiegoDeLanda) >= 2)
			{
				link.l1 = "...";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_4";
			}
			else
			{
				link.l1 = "Sprichst du gerade im Namen der Mannschaft?";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
			}
		break;

		case "Memento_MortimerGrimDead_Alonso_4":
			dialog.text = "Und das ist nicht das erste Mal...";
			link.l1 = "Sprichst du gerade im Namen der Mannschaft?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
		break;

		case "Memento_MortimerGrimDead_Alonso_5":
			dialog.text = "Nein. Glauben Sie mir – wenn die Mannschaft solche Fragen hätte, hieße das, ich mache meinen Job schlecht, und Sie wären bereits ein toter Mann\n"+
			"Zum Glück für Sie hat das blutige Abenteuer gute Beute gebracht. Die Taschen jedes Matrosen sind bis zum Rand mit Dublonen gefüllt!\n"+
			"Keine wertvolle Fracht – nur einheimischer Kram und unheimliche Amulette. Aber die Leute haben trotzdem gut abgesahnt. Grim hat sie wohl gut bezahlt\n"+
			"Ich hoffe, Sie beanspruchen Ihren Anteil an diesem Gold nicht, Käpt’n?";
			link.l1 = "Nein, Alonso. Danke, dass du mich auf dem Laufenden hältst.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_6";
			link.l2 = "Doch. Sorge dafür, dass mein Anteil in meine Kajüte gebracht wird.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_7";
		break;
		
				case "Memento_MortimerGrimDead_Alonso_6":
			dialog.text = "Ich stehe immer auf Ihrer Seite, Käpt’n. Übrigens, was haben Sie mit der 'Memento' vor?";
			link.l1 = "Ich nehme sie als Prise – was denn sonst?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Ich habe mich noch nicht entschieden.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
		break;

		case "Memento_MortimerGrimDead_Alonso_7":
			dialog.text = "Ich stehe immer auf Ihrer Seite, Käpt’n. Übrigens, was haben Sie mit der 'Memento' vor?";
			link.l1 = "Ich nehme sie als Prise – was denn sonst?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Ich habe mich noch nicht entschieden.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
			AddCrewMorale(Pchar, -10);
			AddItems(Pchar, "gold_dublon", 500);
		break;

		case "Memento_MortimerGrimDead_Alonso_8":
			dialog.text = "Besser nicht. Das Schiff ist voll mit seltsamen einheimischen Symbolen behangen. Und es gibt böse Gerüchte – angeblich hat es einst eine furchtbare Seuche überstanden und auf den Decks tanzten nur noch die Toten\n"+
			"Vom Skelett am Heck will ich gar nicht erst anfangen: solange kein Idiot den Schädel aus Jux klaut, wird dort außer mir wohl keiner Wache halten wollen.";
			link.l1 = "Verstanden, Alonso. Zurück an die Arbeit.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_9";
		break;

		case "Memento_MortimerGrimDead_Alonso_9":
			dialog.text = "Jawohl, Käpt’n.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_end";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_end":
			DialogExit();
			AddDialogExitQuestFunction("Memento_MortimerGrimDead_Alonso_2");
		break;
		
		// Диалог с Алонсо в первую ночь
		case "Memento_Dich_EtapOne_Alonso_1":
			dialog.text = "Käpt’n, entschuldigen Sie die Störung zu dieser Stunde.";
			link.l1 = "Berichte, Alonso.";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_2";
			if (CheckAttribute(pchar, "questTemp.Memento_Dich_EtapTwo"))
			{
				dialog.text = "Käpt’n? Was machen Sie hier? Haben Sie hier etwa geschlafen?";
				link.l1 = "Spielt keine Rolle.";
				link.l1.go = "Memento_Dich_EtapTwo_Alonso_2";
				link.l2 = "In meiner Kajüte ist es irgendwie... ungemütlich.";
				link.l2.go = "Memento_Dich_EtapTwo_Alonso_2";
			}
		break;

		case "Memento_Dich_EtapOne_Alonso_2":
			dialog.text = "Die Lage ist miserabel. Die Stimmung in der Mannschaft ist im Keller! Die Leute sagen ganz offen, dass das Schiff verflucht ist. Sie beschweren sich, dass sie nachts Dinge sehen.";
			link.l1 = "Was genau sehen sie?";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_3";
		break;

		case "Memento_Dich_EtapOne_Alonso_3":
			dialog.text = "Irgendwelche Albträume. Aber das Schlimmste: einer unserer Leute ist am Fieber gestorben. Ein junger Kerl, kräftig wie ein Bär – und in ein paar Stunden war er hinüber.";
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				link.l1 = "Das soll der Arzt entscheiden. "+sld.name+" weiß, was er tut.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
			else
			{
				link.l1 = "So etwas gibt’s doch nicht. Halte die Mannschaft im Zaum, Alonso. Das ist dein Job.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
		break;

		case "Memento_Dich_EtapOne_Alonso_4":
			dialog.text = "Jawohl!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapOne_End");
		break;
		
		// Диалог с Алонсо во вторую ночь
		case "Memento_Dich_EtapTwo_Alonso_2":
			dialog.text = "Verstehe. Viele aus der Mannschaft schlafen jetzt zusammen – sie haben Angst, allein zu sein. Als ob man auf diesem Schiff überhaupt allein sein könnte…";
			link.l1 = "Wie du siehst, hat’s bei mir auch nicht geklappt. Was ist passiert?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_3";
		break;

		case "Memento_Dich_EtapTwo_Alonso_3":
			dialog.text = "Eine Schlägerei – José hat Marcel erstochen. Er hat geschrien, der bringe 'die Seuche'.";
			link.l1 = "Hat sich die Lage verschärft?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_4";
		break;

		case "Memento_Dich_EtapTwo_Alonso_4":
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				dialog.text = ""sld.name+" hat Ihnen doch heute früh berichtet. Elf Mann haben wir verloren. Was sollen wir tun?";
			}
			else
			{
				dialog.text = "Noch elf Mann haben wir verloren. Was sollen wir tun?";
			}
			link.l1 = "Ich treffe eine Entscheidung.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_5";
		break;

		case "Memento_Dich_EtapTwo_Alonso_5":
			dialog.text = "Hoffentlich, Kapitän. Was machen wir mit José? Mord ist kein Spaß.";
			link.l1 = "Aufhängen nach der Wache. Wir zeigen, dass alles unter Kontrolle ist.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_6";
			link.l2 = "Dreißig Peitschenhiebe. Wenn er überlebt – war’s Gottes Wille.";
			link.l2.go = "Memento_Dich_EtapTwo_Alonso_7";
		break;

		case "Memento_Dich_EtapTwo_Alonso_6":
			dialog.text = "Jawohl!";
			link.l1 = "...";
			link.l1.go = "exit";
			SetCrewQuantity(pchar, GetCrewQuantity(pchar) - 1);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;

		case "Memento_Dich_EtapTwo_Alonso_7":
			dialog.text = "Jawohl!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddCrewMorale(Pchar, -10);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;
		
		// Диалог с Алонсо в третью ночь
		case "Memento_Dich_EtapThree_AlonsoPrizrak_1":
			dialog.text = "Käpt’n! Achtung! Sie müssen sofort ins Zwischendeck!";
			link.l1 = "Was ist passiert?";
			link.l1.go = "Memento_Dich_EtapThree_AlonsoPrizrak_2";
		break;

		case "Memento_Dich_EtapThree_AlonsoPrizrak_2":
			dialog.text = "Am besten sehen Sie es sich selbst an. Kommen Sie, schnell!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_4_1");
		break;

		// Уже утром
		case "Memento_Dich_EtapThree_Alonso_1":
			dialog.text = "Guten Morgen, Käpt’n!";
			link.l1 = "Ah?!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_2";
		break;

		case "Memento_Dich_EtapThree_Alonso_2":
			dialog.text = "Äh... Sie sehen bleich aus. Schlecht geschlafen? Keine Sorge, ich habe gute Nachrichten. Die Epidemie ist vorbei. Eigentlich hat sie nie stattgefunden, wie sich herausstellte.";
			link.l1 = "Wie das?";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_3";
		break;

		case "Memento_Dich_EtapThree_Alonso_3":
			dialog.text = "Die Leute haben sich verrückt gemacht, dummen Gerüchten über ein verfluchtes Schiff gelauscht. Die Macht der Selbstsuggestion ist unheimlich, das sage ich Ihnen. Sie hat schon so manches Schiff ins Verderben geführt.";
			link.l1 = "Aber Menschen sind gestorben!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_4";
		break;

		case "Memento_Dich_EtapThree_Alonso_4":
			dialog.text = "Kampf, schmutzige Wunden, verdorbenes Pökelfleisch – normale See-Arithmetik. Hätten wir uns nicht so mit Geschichten über verfluchte Schiffe verrückt gemacht, hätten wir vielleicht ein paar Leute weniger verloren.\n"+
			"Das Skelett am Heck war auch nicht gerade ermutigend. Zum Glück hat irgendein... Spaßvogel ihm nachts den Hut gestohlen.\n"+
			"Da kein Blitz in das Schiff einschlug, wurde die Stimmung besser und der seemännische Scharfsinn machte sich daran, neue Schabernackpläne mit dem Skelett zu schmieden. Zum Beispiel...";
			link.l1 = "Kein Finger an das Skelett!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_5";
		break;

		case "Memento_Dich_EtapThree_Alonso_5":
			dialog.text = "Äh... Wenn Sie zärtliche Gefühle für ihn hegen, dann natürlich nicht. Einen schönen Tag noch, Käpt’n.\n"+
			"Übrigens: ein großartiger Hut! Steht Ihnen hervorragend. Dem Vorbesitzer war er eindeutig zu klein.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_End");
		break;
		
		// Диалоги с командой Мементо
		case "Memento_Sailor_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Grüße, Kapitän. Sie sollten mit Kapitän Grimm sprechen.";
				link.l1 = "Verzeih mir, Matrose, aber du fällst hier auf.";
				link.l1.go = "Memento_Sailor_1_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Noch etwas, Kapitän?";
				link.l1 = "Nichts.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_1_1":
			dialog.text = "Ich verstehe, was Sie meinen, Kapitän. Ich diente unter einem freien Kapitän – so wie Sie. Er suchte Schätze, handelte, fuhr Fracht. Und dann wollte er nebenbei noch ein paar Händler ausnehmen – ging schief. Die Überlebenden wurden wegen Piraterie zum Galgen verurteilt.";
			link.l1 = "Und Kapitän Grimm hat Sie freigekauft?";
			link.l1.go = "Memento_Sailor_1_2";
		break;

		case "Memento_Sailor_1_2":
			dialog.text = "Als eine Partie, wie Ware. Ein erfahrener Matrose wird immer gebraucht, aber Kapitän Grimm rekrutiert nicht in Tavernen ... Dafür füttert er gut und zahlt großzügig. Und wir dienen – und nehmen am Los teil.";
			link.l1 = "Am Los?";
			link.l1.go = "Memento_Sailor_1_3";
		break;

		case "Memento_Sailor_1_3":
			dialog.text = "Verzeihen Sie, darüber sollten wir nicht sprechen.";
			link.l1 = "Warum gehen Sie dann nicht?";
			link.l1.go = "Memento_Sailor_1_4";
		break;

		case "Memento_Sailor_1_4":
			dialog.text = "Wohin denn? So besteht wenigstens eine Chance. Vielleicht haben wir Glück. Auf jedem Schiff gibt es sein eigenes Los. Kapitän Grimm hat seines, Sie haben Ihres. Wir sind keine Menschen, nur Zahlen in den Schiffsbüchern.";
			link.l1 = "Auf meinem Schiff herrschen andere Regeln.";
			link.l1.go = "Memento_Sailor_1_5";
		break;

		case "Memento_Sailor_1_5":
			dialog.text = "Wie Sie sagen, Kapitän. Einen schönen Tag noch.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_2":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Schon lange keine Gäste mehr auf unserem stolzen Schiff!";
				link.l1 = "Du bist Matrose? Siehst nicht so aus.";
				link.l1.go = "Memento_Sailor_2_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Noch etwas, Kapitän?";
				link.l1 = "Nichts.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_2";
		break;

		case "Memento_Sailor_2_1":
			dialog.text = "Ha! Der Käpt’n hat mich direkt aus der Zelle freigekauft. Ich sollte in Port Royal gehängt werden: hab so einen Kerl abgestochen – ein junger Fatzke, der ständig Gedichte rezitierte. Hat’s verdient, das Schwein.";
			link.l1 = "Dann hatten Sie wohl Glück?";
			link.l1.go = "Memento_Sailor_2_2";
		break;
		
		case "Memento_Sailor_2_2":
			dialog.text = "Aber sicher! Der Käpt’n spart nicht, allerdings muss man manchmal an seinen ... Spielen teilnehmen.";
			link.l1 = "Was für Spiele?";
			link.l1.go = "Memento_Sailor_2_3";
		break;

		case "Memento_Sailor_2_3":
			dialog.text = "Einmal die Woche ziehen wir Stäbchen: Wer das kurze zieht, muss gefährliche Arbeiten übernehmen oder sogar über Bord springen. Ein Spaß, irgendwie. Nicht für jeden, natürlich, aber der Käpt’n sagt: So trennt man die Untauglichen aus.";
			link.l1 = "Untauglich wofür?";
			link.l1.go = "Memento_Sailor_2_4";
		break;

		case "Memento_Sailor_2_4":
			dialog.text = "Woher soll ich das wissen? Der Käpt’n redet viel, wie ein Priester: 'Nur wer den Tod kennt, kann wahrhaft leben!'\n"+
			"(spuckt aus)";
			link.l1 = "Fürs Spucken an Deck gibt’s die Peitsche. Du benimmst dich wie ein Bandit, nicht wie ein Seemann. Leb wohl.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_2";
		break;

		case "Memento_Sailor_3":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Guten Tag, Kapitän.";
				link.l1 = "Wie bist du hierher gekommen?";
				link.l1.go = "Memento_Sailor_3_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Noch etwas, Kapitän?";
				link.l1 = "Nichts.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_3";
		break;

		case "Memento_Sailor_3_1":
			dialog.text = "Kapitän Grimm hat ein Sklavenschiff überfallen, auf dem ich war. Ich war damals krank, lag im Laderaum und starb fast ... Ich erinnere mich kaum. Als ich wieder zu mir kam, war ich auf der 'Memento'.";
			link.l1 = "Und was wurde aus den anderen Sklaven?";
			link.l1.go = "Memento_Sailor_3_2";
		break;

		case "Memento_Sailor_3_2":
			dialog.text = "Ich weiß es nicht. Der Kapitän sagt, er habe alle freigelassen, aber ich war der Einzige, der aufs Schiff gebracht wurde. Die anderen sind wohl auf den Inseln verschwunden oder an ihren Wunden gestorben. Ich erinnere mich schlecht an diesen Tag.";
			link.l1 = "Aber du bist frei.";
			link.l1.go = "Memento_Sailor_3_3";
		break;

		case "Memento_Sailor_3_3":
			dialog.text = "Frei? Hier ist niemand frei. Der Kapitän gibt Gold, Essen, Kleidung, aber verlangt absolute Treue – und veranstaltet dieses grausame Losspiel.";
			link.l1 = "Losspiel?";
			link.l1.go = "Memento_Sailor_3_4";
		break;

		case "Memento_Sailor_3_4":
			dialog.text = "Jede Woche zieht jemand das kurze Stäbchen und übernimmt eine gefährliche Aufgabe, von der nicht alle zurückkehren. Der Kapitän sagt: So trennt man die Lebenden von den Toten.";
			link.l1 = "Und ihr duldet das?";
			link.l1.go = "Memento_Sailor_3_5";
		break;
		
		case "Memento_Sailor_3_5":
			dialog.text = "Jeder hofft, dass er Glück hat. Der Kapitän kennt für jeden den richtigen Hebel: Angst, wieder in der Schlinge zu hängen, Gier nach Gold, das Bedürfnis, eine gerettete Seele zu bedanken. Mich interessiert das nicht. Ich brauche kein Geld, und wie soll ich etwas zurückzahlen, woran ich mich nicht erinnere?";
			link.l1 = "Du hast keine Angst, so offen zu sprechen?";
			link.l1.go = "Memento_Sailor_3_6";
		break;

		case "Memento_Sailor_3_6":
			dialog.text = "Was soll man mir antun? Dies ist ein Schiff der Toten, Kapitän, und ich gehöre hierher. Sie aber nicht.";
			link.l1 = "Wie du meinst. Leb wohl.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_3";
		break;

		case "Memento_Sailor_4":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Willkommen an Bord der 'Memento', Kapitän.";
				link.l1 = "Ein spanischer Soldat auf einem Piratenschiff? Das ist ungewöhnlich.";
				link.l1.go = "Memento_Sailor_4_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Noch etwas, Kapitän?";
				link.l1 = "Nichts.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_4";
		break;

		case "Memento_Sailor_4_1":
			dialog.text = "Ich bin ein Deserteur. Kapitän Grimm hat mich direkt vom Galgen auf dem Platz von San José freigekauft. Hat viel bezahlt – ein ganzer Sack Dublonen für meine staubige Haut.";
			link.l1 = "Und wofür wurden Sie verurteilt?";
			link.l1.go = "Memento_Sailor_4_2";
		break;

		case "Memento_Sailor_4_2":
			dialog.text = "Offizier Saldo schickte uns zur Bewachung von Arbeitern im Dschungel, wo die Hälfte innerhalb einer Woche an Fieber stirbt. Ich entschied, dass mein Leben mehr wert ist. Jetzt ... diene ich dem, der es mit Gold aufwog.";
			link.l1 = "Bereuen Sie es nicht?";
			link.l1.go = "Memento_Sailor_4_3";
		break;

		case "Memento_Sailor_4_3":
			dialog.text = "So lange das Seil auch sein mag ... Der Kapitän ist großzügig zu denen, die ihm treu sind. Allerdings veranstaltet er manchmal seltsame Prüfungen – das Los. Nicht jeder hat Glück.";
			link.l1 = "Das Los?";
			link.l1.go = "Memento_Sailor_4_4";
		break;

		case "Memento_Sailor_4_4":
			dialog.text = "Na ja, Sie wissen schon. Einer muss bei Sturm in den Mastkorb, ein anderer in die Vorhut. Der Kapitän sagt: So zeigt sich, ob man bereit ist. Wofür, weiß ich nicht, aber ich hoffe auf mein Glück.";
			link.l1 = "Viel Glück ... wohl.";
			link.l1.go = "Memento_Sailor_4_5";
		break;
		
		case "Memento_Sailor_4_5":
			dialog.text = "Danke, Kapitän. Der Tod geht sowieso jedem nach.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_4";
		break;

		/*case "Memento_Sailor_5":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Диалог 5";
				link.l1 = "Диалог 5";
				link.l1.go = "exit";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Что-нибудь ещё, капитан?";
				link.l1 = "Ничего.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_5";
		break;*/

		case "Memento_MortimerGrim_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Willkommen an Bord der 'Memento', Kollege. Mein Name ist Mortimer Grimm.";
				link.l1 = "Kapitän "+GetFullName(pchar)+". Danke, dass Sie mich aufgenommen haben...";
				link.l1.go = "Memento_MortimerGrim_2";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Worüber möchten Sie noch sprechen?";
				if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
				{
					link.l1 = "Sie haben eine beeindruckende Klinge, Kapitän.";
					link.l1.go = "Memento_MortimerGrim_question_1_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
				{
					link.l2 = "Ihr Fernrohr passt perfekt zum Skelett.";
					link.l2.go = "Memento_MortimerGrim_question_2_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
				{
					link.l3 = "Man muss sagen, Ihre Mannschaft ist sehr bunt zusammengewürfelt.";
					link.l3.go = "Memento_MortimerGrim_question_3_1";
				}
				link.l4 = "Nichts... Kollege. Allzeit gute Fahrt.";
				link.l4.go = "exit";
				NextDiag.TempNode = "Memento_MortimerGrim_1";
			}
		break;
		
		case "Memento_MortimerGrim_2":
			dialog.text = "Die Karibik ist großzügig zu denen, die eilig zum Schafott streben – ich weiß es aus erster Hand.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_3";
		break;

		case "Memento_MortimerGrim_3":
			dialog.text = "Ja? Sie wollten etwas fragen?";
			link.l1 = "Hinter Ihnen hängt ein Skelett.";
			link.l1.go = "Memento_MortimerGrim_4";
			link.l2 = "Heute weht ein guter Wind, was? Und das Wetter ist herrlich.";
			link.l2.go = "Memento_MortimerGrim_5";
		break;

		case "Memento_MortimerGrim_4":
			dialog.text = "Welches Skelett? Hinter mir ist nur das blaue Karibische Meer.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_5":
			dialog.text = "Einverstanden, Kollege. So könnte es jeden Tag sein!";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_6":
			dialog.text = "Ha-ha-ha! Dieser Scherz wird nie alt! Keine Angst: der alte Yorick ist wie dieses Schiff – ein Souvenir aus meinem früheren Leben. Im wörtlichen Sinne, versteht sich.";
			link.l1 = "'Versteht sich'?";
			link.l1.go = "Memento_MortimerGrim_7";
		break;

		case "Memento_MortimerGrim_7":
			dialog.text = "Kollege, haben Sie Angst vor dem Tod? Keine Drohung – es interessiert mich wirklich.";
			link.l1 = "Natürlich. Wer etwas anderes sagt, lügt.";
			link.l1.go = "Memento_MortimerGrim_8_leadership";
			link.l2 = "Nein. Wir kommen alle irgendwann dorthin.";
			link.l2.go = "Memento_MortimerGrim_8_weapon";
			link.l3 = "Und Sie?";
			link.l3.go = "Memento_MortimerGrim_8_sneak";
		break;

		case "Memento_MortimerGrim_8_leadership":
			dialog.text = "Oh! Der Tod ist die Mutter aller Ängste. Einsamkeit, Dunkelheit oder Strafe – all das sind nur seine Masken.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Memento_MortimerGrim_8_weapon":
			dialog.text = "Oh! Der Tod ist die Mutter aller Ängste. Einsamkeit, Dunkelheit oder Strafe – all das sind nur seine Masken.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "Memento_MortimerGrim_8_sneak":
			dialog.text = "Oh! Der Tod ist die Mutter aller Ängste. Einsamkeit, Dunkelheit oder Strafe – all das sind nur seine Masken.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Memento_MortimerGrim_9":
			dialog.text = "Warum in die Ferne schweifen? Nehmen Sie den alten Yorick: Ein Haufen Knochen mit einer Laterne im Brustkorb – und selbst einen so furchtlosen Kapitän wie Sie hat er nervös gemacht!";
			if (startHeroType == 4)
			{
				dialog.text = "Warum in die Ferne schweifen? Nehmen Sie den alten Yorick: Ein Haufen Knochen mit einer Laterne im Brustkorb – und selbst die furchtlose Helen, Tochter des großen Sean MacArthur, hat er nervös gemacht!";
			}
			link.l1 = "Schön gesprochen – aber was soll man damit anfangen?";
			link.l1.go = "Memento_MortimerGrim_10";
		break;

		case "Memento_MortimerGrim_10":
			dialog.text = "Ich kenne die Antwort, aber mein Heilmittel ist nicht für jeden. Probieren können Sie es immer noch – aber sagen Sie zuerst, was Sie selbst denken.";
			link.l1 = "Die Bibel sagt, es gibt keinen Tod.";
			link.l1.go = "Memento_MortimerGrim_11_1";
			link.l2 = "Wenn ich Angst bekomme, ist das Schiff verloren.";
			link.l2.go = "Memento_MortimerGrim_11_2";
			link.l3 = "Die Antwort liegt auf dem Grund einer Rumflasche.";
			link.l3.go = "Memento_MortimerGrim_11_3";
		break;

		case "Memento_MortimerGrim_11_1":
			dialog.text = "Das stimmt. Das ist das Einzige, worin ich diesem Buch zustimme.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_11_2":
			dialog.text = "Lobenswert. Aber Sie brauchen sich nicht zu sorgen – es gibt keinen Tod.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_11_3":
			dialog.text = "Yo-ho-ho! Zyniker. Aber auch ohne Rum sage ich: Es gibt keinen Tod.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_12":
			dialog.text = "Es ist ganz einfach: Das wahre Leben beginnt erst, wenn man den Tod besiegt. Ich war dort, jenseits des Schleiers, und glauben Sie mir – wirklich gelebt habe ich erst seitdem.";
			link.l1 = "Wie bitte?";
			link.l1.go = "Memento_MortimerGrim_13";
		break;

		case "Memento_MortimerGrim_13":
			dialog.text = "Ach, unwichtig, Kollege.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
		break;

		case "Memento_MortimerGrim_question_1_1":
			dialog.text = "Schön, dass Sie das bemerkt haben, Kollege! Angeberei liegt mir fern, aber was wäre ich für ein Pirat ohne einen furchteinflößenden Krummsäbel?";
			link.l1 = "Ist das denn wichtig?";
			link.l1.go = "Memento_MortimerGrim_question_1_2";
		break;
		
		case "Memento_MortimerGrim_question_1_2":
			dialog.text = "Allerdings! Das einzige Mal, dass ich die Schiffskasse merklich für persönliche Zwecke erleichtert habe, war für diese Klinge. Zwei Tausend goldene Dublonen, Kollege! Zum Teufel – wenn ich ein zweites Mal von den Toten auferstehen könnte, dann nur wegen seines Wertes!\n"+
			"Die Waffe ist übrigens hervorragend. Aber irgendwie scheint ihr etwas zu fehlen...";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "Memento_MortimerGrim_question_2_1":
			dialog.text = "Ein Geschenk eines Mannes. Ein großartiger Gesprächspartner, der den Tod verstand wie kein anderer – und eine blühende Fantasie hatte, wie Sie vielleicht bemerkt haben.";
			link.l1 = "Sieht unheimlich aus.";
			link.l1.go = "Memento_MortimerGrim_question_2_2";
		break;

		case "Memento_MortimerGrim_question_2_2":
			dialog.text = "Memento mori, Kollege.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_2 = true;
		break;

		case "Memento_MortimerGrim_question_3_1":
			dialog.text = "Meine Mannschaft hat mehr gemeinsam, als man denkt... Ich habe sie alle vom Galgen und aus Ketten befreit – jeder von ihnen hat den Tod gespürt. Dieses Gefühl verbindet Menschen besser als Blut oder Fahne.";
			link.l1 = "Man könnte also sagen, Sie rekrutieren nicht in Tavernen?";
			link.l1.go = "Memento_MortimerGrim_question_3_2";
		break;

		case "Memento_MortimerGrim_question_3_2":
			dialog.text = "Sie würden staunen, wie bereitwillig ehemalige Sklaven und Todeskandidaten zur 'Memento' kommen: den Laderaum eines Sklavenschiffs oder das Schafott gegen mein Deck zu tauschen? Ich habe derzeit 178 Mann an Bord – und jeder von ihnen steht in meiner Schuld.";
			link.l1 = "Aber Sie müssen doch die Mannschaft bezahlen und das Schiff unterhalten. Dankbarkeit allein reicht nicht.";
			link.l1.go = "Memento_MortimerGrim_question_3_3";
		break;

		case "Memento_MortimerGrim_question_3_3":
			dialog.text = "Ich bin ein erfolgreicher Pirat, Kollege. Ein wahrer hostis humanitatis. So würden mich die wahren Feinde der Menschheit nennen – Sklavenhändler und gekrönte Häupter. Der Unterschied zwischen ihnen ist nur der Name\n"+
			"Zum Glück haben sie genug Gold. Die Münzen aus den Truhen der Menschenhändler verwende ich, um jene zu retten, die von der Krone zum Tode verurteilt wurden. Den Rest gebe ich der Mannschaft – mir selbst brauche ich nichts. Wozu braucht ein Toter Gold? Bald werden sie es verstehen...";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_3 = true;
		break;
		
		// Диалог с Алонсо
		case "Memento_Alonso_phantom_11":
			dialog.text = "So ist es bei uns gelaufen, Kapitän – richtig beschissen.";
			link.l1 = "Was ist das?!";
			link.l1.go = "Memento_Alonso_phantom_12";
		break;

		case "Memento_Alonso_phantom_12":
			dialog.text = "Nur Sie sind übrig geblieben. Die Krankheit hat alle dahin gerafft. Sie haben uns im Stich gelassen.";
			link.l1 = "Das kann nicht sein!";
			link.l1.go = "Memento_Alonso_phantom_13";
		break;

		case "Memento_Alonso_phantom_13":
			dialog.text = "Sie haben uns auf ein verfluchtes Schiff geführt.";
			link.l1 = "...";
			link.l1.go = "Memento_Alonso_phantom_14";
		break;

		case "Memento_Alonso_phantom_14":
			dialog.text = "Sie haben uns alle dem Tod geweiht!";
			link.l1 = "Alonso, was ist mit dir?!";
			link.l1.go = "Memento_Alonso_phantom_15";
			npchar.model = "skel1";
			npchar.model.animation = "skeleton";
			npchar.sex = "skeleton";
			Characters_RefreshModel(npchar);
			SetMusic("classic_music_retribution_1");
		break;

		case "Memento_Alonso_phantom_15":
			dialog.text = "Mortui vivos docent.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_6");
		break;

		// Диалог с Гримом

		case "Memento_MortimerGrim_phantom_11":
			dialog.text = "Was ist los, Kollege? Kalte Füße bekommen? Warum haben Sie dann angegriffen?";
			link.l1 = "Grimm? Aber du bist doch tot!";
			link.l1.go = "Memento_MortimerGrim_phantom_12";
		break;

		case "Memento_MortimerGrim_phantom_12":
			dialog.text = "Ha! Was tot ist, kann nicht sterben. Und außerdem, du bist zu früh dran – du hast das Entern gewonnen, aber wirst du auch überleben...? Das finden wir jetzt heraus!";
			link.l1 = "Dieser Kampf war vor Wochen! Du bist tot!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_11");
		break;

		case "Memento_MortimerGrim_phantom_21":
			dialog.text = "Jetzt ist es vollbracht. Glückwunsch zum Sieg.";
			link.l1 = "Grimm?";
			link.l1.go = "Memento_MortimerGrim_phantom_22";
			LAi_UseAtidoteBottle(pchar);
		break;

		case "Memento_MortimerGrim_phantom_22":
			dialog.text = "Weißt du, ich bin froh. Wirklich froh, dass du mich getötet hast. Endgültig.";
			link.l1 = "Wovon redest du?";
			link.l1.go = "Memento_MortimerGrim_phantom_23";
		break;

		case "Memento_MortimerGrim_phantom_23":
			dialog.text = "Ich bin ein Feigling, Kollege. Ein ganz gewöhnlicher, erbärmlicher Feigling, der Angst vor dem Tod hatte – wie Tausende vor ihm. Als die Mannschaft an der Pest starb... und auch noch durch meine Schuld, da bin ich vor Angst wahnsinnig geworden. Einen Monat lang bin ich allein auf einem Totenschiff umhergetrieben.";
			link.l1 = "Was ist wirklich passiert?";
			link.l1.go = "Memento_MortimerGrim_phantom_24";
		break;
		
		case "Memento_MortimerGrim_phantom_24":
			dialog.text = "Ich habe die Prüfung des Todes nicht bestanden. Anstatt ihn zu akzeptieren, zu überleben und daraus zu lernen, habe ich nur noch mehr Angst bekommen. Und um diese Angst zu unterdrücken... zwang ich andere, durch das Gleiche zu gehen.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_25";
		break;

		case "Memento_MortimerGrim_phantom_25":
			dialog.text = "Danke dir, Kollege. Dafür, dass du mich von diesem... Dasein befreit hast. Jetzt weiß ich mit Sicherheit, dass es den Tod nicht gibt. Und ich habe keine Angst mehr. Es gibt niemanden mehr zu beschuldigen oder zu versklaven.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_26";
		break;

		case "Memento_MortimerGrim_phantom_26":
			dialog.text = "Trennt die 'Memento' nicht von ihrem Kapitän. Mortimer… Kapitän Mortimer war ein guter Mensch. Findet ihn auf Dominica. Und das Schiff... das Schiff wird euch annehmen.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_27";
		break;

		case "Memento_MortimerGrim_phantom_27":
			dialog.text = "Mortui vivos docent, Kollege. Die Toten lehren die Lebenden. Leb wohl.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_13");
		break;
		
	}
} 