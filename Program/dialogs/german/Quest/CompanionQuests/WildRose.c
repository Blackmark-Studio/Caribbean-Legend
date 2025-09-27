void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
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
			dialog.text = "Was wollt ihr?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";
		break;
		
		// =================================================================
		// ================== ЭТАП 1. «ЛОЩИНА ВЛЮБЛЁННЫХ» ==================
		// =================================================================
		case "Mary_1":
			dialog.text = ""+pchar.name+", schau mal her!";
			link.l1 = "Leise, "+npchar.name+", wir sind hier vielleicht nicht allein.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_2":
			dialog.text = ""+pchar.name+"!";
			link.l1 = ""+npchar.name+"? Bist du mir etwa auf Schritt und Tritt gefolgt, ja, gell?";
			link.l1.go = "Mary_3";
		break;
		
		case "Mary_3":
			dialog.text = "Und anscheinend nicht umsonst, ja, gell!   Was ist denn hier passiert?";
			link.l1 = "Wenn ich es gewusst hätte, "+npchar.name+", wenn ich es nur gewusst hätte...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_4":
			dialog.text = "Mein Gott...";
			link.l1 = "Ja, das arme Ding hat wohl schwer gelitten vor dem Tod. So ein Ende wünscht man wirklich niemandem, ja, gell?...";
			link.l1.go = "Mary_5";
		break;
		
		case "Mary_5":
			dialog.text = "Und wer ist das da, ihr Mann? Was zum Teufel machen die im Dschungel?! Haben die denn noch nie von entlaufenen Sklaven gehört?";
			link.l1 = "Ich fürchte, auf diese Frage werden sie jetzt keine Antwort mehr geben können...";
			link.l1.go = "Mary_6";
		break;
		
		case "Mary_6":
			dialog.text = "Glaubst du, derjenige, der das getan hat, ist noch irgendwo in der Nähe, ja, gell?";
			link.l1 = "Durchaus möglich. Deshalb sollten wir uns lieber ruhig verhalten – wir müssen sie zuerst entdecken, ja, gell?";
			link.l1.go = "Mary_7";
		break;
		
		case "Mary_7":
			dialog.text = "Zu spät, "+pchar.name+". Sieht so aus, als hätten sie uns schon bemerkt. Schau mal dorthin.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "Na, na, Jungs, schaut euch das mal an. Hier ist ja direkt ein Tal der Verliebten, was? Kaum haben zwei Turteltauben dem Herrgott ihre Seelen übergeben, tauchen schon zwei andere an ihrer Stelle auf, hehe...";
			if (GetOfficersQuantity(pchar) >= 2)
			{
				link.l1 = "Sehr witzig. Aber du kannst wohl nicht zählen – im Gegensatz zu diesen armen Kerlen sind wir hier nämlich nicht allein.";
				link.l1.go = "Naemnik_2";
			}
			else
			{
				link.l1 = "Mit uns wird es schon ein bisschen schwieriger, glaub mir einfach, ja, gell...";
				link.l1.go = "Naemnik_4";
			}
		break;
		
		case "Naemnik_2":
			dialog.text = "Ich würde ja sagen, dass ihr klüger seid als die — aber das wäre eine gottverdammte Lüge. Selbst in dieser Zahl hättet ihr diese Bastarde nicht geschafft. Und deine Kleine da hätte dasselbe Schicksal ereilt wie das Mädchen zu deinen Füßen...";
			link.l1 = "Du meinst die entlaufenen Sklaven? Ist das einer von ihnen? Also seid ihr Leute von Bishop, ja, gell?";
			link.l1.go = "Naemnik_3";
		break;
		
		case "Naemnik_3":
			dialog.text = "Auf alle Fragen – ja, gell? Mehr als zwei Tage lang haben wir zusammen mit den Soldaten diese Halunken über die ganze Insel gejagt. Dann haben sich die Mistkerle aufgeteilt. Ein Teil ist in Richtung Höhle geflohen – die Wache ist ihnen gefolgt, die anderen sind zur Bucht abgehauen. Bei ihrem Hinterhalt, eine halbe Meile westlich von hier, haben wir ein paar Jungs verloren, und während wir uns gesammelt und neu formiert haben, haben sie sich mit diesem Dummchen amüsiert...";
			link.l1 = "...";
			link.l1.go = "Naemnik_7";
		break;
		
		case "Naemnik_4":
			dialog.text = "Fass deinen Zahnstocher nicht an, Bürschchen – nerv mich und meine Jungs nicht. Ich würde zu gern sehen, wie der dir helfen würde, wenn du von einem Dutzend solcher Dreckskerle umzingelt wärst, wie die, die wir in der Bucht erledigt haben. Nur einer hatte Glück – aber das hält nicht lange... Sobald dieses Schwein in Bishops Händen ist...";
			link.l1 = "Seid ihr also seine Söldner, ja, gell?";
			link.l1.go = "Naemnik_5";
		break;
		
		case "Naemnik_5":
			dialog.text = "Na ja, das sind offensichtlich keine Garnisonssoldaten. Wenn diese Waschlappen nicht gewesen wären, hätten wir die Halunken schon gestern geschnappt – und dieser Trottel mit seiner Frau wären noch am Leben, ja, gell?...";
			link.l1 = "Also war das nicht euer Werk...";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "Für wen hältst du uns eigentlich, hm? Wir sind zwar keine Engel, aber wenn uns danach ist, gehen wir ins Bordell und nicht...";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		case "Naemnik_6_add":
			StartInstantDialog("WildRose_Naemnik_Rab", "Naemnik_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_7":
			dialog.text = "Er lügt doch nur, lügt – dieser niederträchtige Schuft! Hört nicht auf ihn, "+GetAddress_Form(NPChar)+"! Wir haben diese armen Leute nicht mal mit dem Finger angerührt!";
			link.l1 = "Ach ja? Und warum sollten wir Ihnen glauben und nicht ihm?";
			link.l1.go = "Naemnik_8";
			link.l2 = "Ja, gell?   Oder lügst   vielleicht   du   gerade?   Für   eine   Heilige   hält   dich   hier   jedenfalls   niemand.";
			link.l2.go = "Naemnik_9";
		break;
		
		case "Naemnik_8":
			dialog.text = "Na, überleg doch mal selbst, um Himmels willen! Wir sind doch vor diesem Biest Bishop geflohen, zwei Tage lang durch den Dschungel gerannt, haben unsere Spuren verwischt – und wofür? Damit wir jetzt eine arme Lady schänden und diesen Blutsaugern erlauben, uns einzuholen?! Meine Freunde konnten sich doch kaum noch auf den Beinen halten, als wir an diesem Strand ankamen, "+GetAddress_Form(NPChar)+"! Wir hatten nicht einmal die Kraft, mit unseren Musketen zu schießen, sonst hätten wir diesen Halunken nie erlaubt, ihr finsteres Werk zu vollbringen... Das waren alles sie, wir haben es gesehen!..";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Naemnik_9":
			dialog.text = "Na, überleg doch mal selbst, um Himmels willen! Wir sind doch vor diesem Biest Bishop geflohen, zwei Tage lang durch den Dschungel gerannt, haben unsere Spuren verwischt – und wofür? Damit wir jetzt eine arme Lady schänden und diesen Blutsaugern erlauben, uns einzuholen?! Meine Freunde haben sich doch kaum noch auf den Beinen gehalten, als wir an diesem Strand ankamen, "+GetAddress_Form(NPChar)+"! Wir hatten nicht einmal die Kraft, mit unseren Musketen zu schießen, sonst hätten wir diesen Halunken nie erlaubt, ihr finsteres Werk zu vollbringen... Das waren alles sie, wir haben es gesehen!..";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		case "Naemnik_9_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_10":
			dialog.text = "Halt die Klappe, Casper, du verlauster Köter!";
			link.l1 = "...";
			link.l1.go = "Naemnik_10_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab"));
		break;
		case "Naemnik_10_add":
			StartInstantDialog("Mary", "Naemnik_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_11":
			dialog.text = "Was hast du gesagt?!";
			link.l1 = "...";
			link.l1.go = "Naemnik_11_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_11_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_12":
			dialog.text = "Hörst du schlecht, Fräulein? Ich hab ihm gesagt, er soll die Klappe halten. Unser Jerry kann stundenlang Märchen erzählen – darin ist er wirklich ein Talent, ja, gell? Bishop wollte ihm die Zunge rausschneiden und sie ihn selbst fressen lassen, aber dann hat er's sich anders überlegt – was ein Fehler war, verdammt nochmal!";
			link.l1 = "...";
			link.l1.go = "Naemnik_12_add";
			CharacterTurnByChr(npchar, CharacterFromID("Mary"));
		break;
		case "Naemnik_12_add":
			StartInstantDialog("Mary", "Naemnik_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_13":
			dialog.text = "Aber... Du hast ihn Casper genannt, ja, gell...";
			link.l1 = "...";
			link.l1.go = "Naemnik_13_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_13_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_14":
			dialog.text = "Hör mal, Junge, erklär deiner Freundin, dass Menschen, selbst so ein Taugenichts wie der hier, nicht nur einen Vornamen, sondern auch einen Nachnamen haben. Ich hab ja schon oft gehört, dass schöne Frauen manchmal dumm wie Stroh sind, aber so was hab ich noch nie erlebt, dass ich gleich draufgehen könnte...";
			link.l1 = "...";
			link.l1.go = "Naemnik_14_add";
			CharacterTurnByChr(npchar, pchar);
		break;
		case "Naemnik_14_add":
			StartInstantDialog("Mary", "Naemnik_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_15":
			dialog.text = "Genau das werde ich dir jetzt zeigen, ja, gell!";
			link.l1 = "Mary, halt! Ich kümmere mich selbst darum. Steck die Waffe weg. Sofort.";
			link.l1.go = "Naemnik_15_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "normal to fight", "1", 2.5);
			DoQuestFunctionDelay("WildRose_Etap1_EscapeSlaves_6_1", 3.0);
		break;
		case "Naemnik_15_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_16":
			dialog.text = "Oh, wir haben es hier ja mit einem echten Gentleman zu tun. Dein Verhalten ist wirklich ehrenhafter als das Gejammer dieses Schleimers. Der hat lauter gebrüllt als seine arme Frau – so laut, dass man es sogar hinter dem Hügel hören konnte. Ehrlich gesagt, hat er uns sogar geholfen – genau so haben wir diese Halunken aufgespürt...";
			link.l1 = "Hier in der Karibik ist Edelmut eine ziemlich seltene Sache. Und jetzt atmen wir alle einmal tief durch – es gibt nichts Ehrenhaftes daran, hier und jetzt ins Gras zu beißen.";
			link.l1.go = "Naemnik_17";
			link.l2 = "Die einzigen Schurken hier seid ihr. Entschuldige dich sofort bei Mary, und vielleicht kommen wir ohne Blutvergießen aus.";
			link.l2.go = "Naemnik_22";
		break;
		
		case "Naemnik_17":
			dialog.text = "Schwer, da nicht zuzustimmen. Aber bring erst mal deine...";
			link.l1 = "Sie heißt Mary Casper. Ich denke, das erklärt schon einiges.";
			link.l1.go = "Naemnik_18";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Naemnik_18":
			dialog.text = "Kasper? Ist sie etwa seine Tochter, haha?";
			link.l1 = "Ich bezweifle das sehr. Aber ich hoffe, du bist jetzt klug genug, deine Worte zurückzunehmen.";
			link.l1.go = "Naemnik_19";
		break;
		
		case "Naemnik_19":
			dialog.text = "Zurück? Und was dann? Fordert du mich etwa zum Duell heraus? Nur zu... Wenn du dich traust, deine Liebste ganz allein mitten im Dschungel zu lassen, he-he. Wir Jungs würden uns über so eine Wendung riesig freuen.";
			link.l1 = "Da habt ihr also euer wahres Gesicht gezeigt. Besonders gut habt ihr euch ja nicht verstellt, ja, gell?";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_22":
			dialog.text = "Du bist wirklich ein wandelnder Widerspruch, Mister – so friedlich und doch ein verdammter Rüpel. Und trotzdem interessiert es mich: Flehst du ernsthaft um Vergebung bei dieser rothaarigen Verrückten?";
			link.l1 = "Ihr Name ist Mary Casper, und wenn du jetzt nicht...";
			link.l1.go = "Naemnik_23";
		break;

		case "Naemnik_23":
			dialog.text = "Casper? Ich soll verdammt sein! Jerry, ist das etwa deine Tochter, was? Ha-ha-ha-ha! Ich glaub meinen Ohren nicht! So was gibt’s doch nicht!";
			link.l1 = "Weißt du, was sonst noch klar ist? Solche wie du – Vollidioten, die Ehre nur vom Hörensagen kennen – benehmen sich gegenüber Damen, als wären sie im Stall aufgewachsen. Aber was will man erwarten – wenn im Kopf nur Stroh ist, woher sollen dann Manieren kommen.";
			link.l1.go = "Naemnik_24";
		break;

		case "Naemnik_24":
			dialog.text = "Na schau mal einer an... So ein frecher Wurm. Sag mal, Freund – ist deine Kleine gut im Hängematte?\nAch, was red ich – ich bin mir sicher vom Gegenteil... und überzeug mich gern selbst davon.";
			link.l1 = "Jetzt hast du dich verraten. Hat nicht lange gedauert. Zum Kampf!";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_7");
		break;
		
		case "Djerry_1":
			dialog.text = "Ihr habt ihnen aber ordentlich eingeheizt, "+GetAddress_Form(NPChar)+", - diese Halunken. Sollen sie in der Hölle schmoren! Schade, dass ich euch nicht helfen konnte. Das Musket, das ich auf dem Weg hierher gesehen habe, lag einfach zu weit weg. Offenbar hat einer von uns es verloren, als wir geflohen sind. Ich hätte diesem Mistkerl Primer nur zu gern eigenhändig eine Kugel verpasst.";
			link.l1 = "Anscheinend hat Primer dir ganz schön zugesetzt, wenn du dich entschieden hast, zurückzukommen.";
			link.l1.go = "Djerry_2";
		break;
		
		case "Djerry_2":
			dialog.text = "Und ob er mich gequält hat. Wegen diesem Mistkerl ist mein ganzer Rücken zerkratzt. Aber am schlimmsten war, dass er uns das Wassertrinken verbieten konnte, wann immer er wollte, ja, gell?";
			link.l1 = "Schade, keiner von diesen Halunken hat überlebt. Man hätte ihn den Soldaten übergeben können – die kommen bestimmt bald hierher, ja, gell?";
			link.l1.go = "Djerry_3_1";
		break;
		
		case "Djerry_3_1":
			dialog.text = "Ich verstehe nicht ganz, warum, äh, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "Na ja... Der Kommandant hätte ihm ein Geständnis entlockt und damit eure Namen reingewaschen – deinen und die deiner gefallenen Freunde, ja, gell?";
			link.l1.go = "Djerry_4";
		break;
		
		case "Djerry_4":
			dialog.text = "Ja, klar, haha. Und dann zieht mir William Bishop eigenhändig die Haut ab – davon hat mir mal so ein Schwarzer von der Plantage erzählt... Bishop macht kurzen Prozess mit Ausreißern – egal, ob du schwarz bist oder weiß, das spielt keine Rolle, ja, gell?";
			link.l1 = "Ich fürchte, du wirst so oder so auf die Plantage zurückkehren müssen...";
			link.l1.go = "Djerry_5";
			link.l2 = "Also, freiwillig kehrst du nicht auf die Plantage zurück, ja, gell?";
			link.l2.go = "Djerry_6";
		break;
		
		case "Djerry_5":
			dialog.text = "Du bist ein ganz schöner Spaßvogel – hat man dir das schon mal gesagt, was, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Kein Spaß, "+npchar.name+". Glaubst du wirklich, ich bin zufällig hier? Ich bin in den Urwald gegangen, um euren Trupp zu finden, ihn zur Plantage zurückzubringen – und mir etwas Gold zu verdienen. Aber du bist der Einzige, der übrig geblieben ist. Für dich kriege ich nicht viel, also lasse ich dich vielleicht laufen. Aber sag mir – was hast du dir überhaupt dabei gedacht? Du bist allein. Alle anderen sind tot. Worauf hoffst du zum Teufel noch? Dich weiter in den Bergen und Büschen zu verstecken, bis dich eine Kugel erwischt, du am Fieber stirbst oder als Jaguarfutter endest?";
			link.l1.go = "Djerry_8";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "Djerry_6":
			dialog.text = "Du bist wirklich ein lustiger Spaßvogel – hat dir das schon mal jemand gesagt, was, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Kein Witz, "+npchar.name+". Denkst du etwa, ich bin zufällig hier? Ich bin in die Wildnis gegangen, um eure Truppe aufzuspüren, sie zur Plantage zurückzubringen – und dabei etwas Gold zu verdienen. Aber du bist der Letzte, der noch lebt. Für dich springt nicht viel raus, also lasse ich dich vielleicht gehen. Aber sag mir – was hast du dir überhaupt gedacht? Du bist allein. Die anderen sind alle tot. Worauf hoffst du, verdammt noch mal? Dich zu verstecken, bis dich eine Kugel trifft, das Fieber dich holt oder du von einem Jaguar gefressen wirst?";
			link.l1.go = "Djerry_8";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Djerry_8":
			dialog.text = "So ist es mir lieber, beim Himmel, "+GetAddress_Form(NPChar)+" - Also ich finde, das ist immer noch besser, als an den Qualen zu verrecken, die Bishop für mich vorbereitet hat, ja, gell? Aber eigentlich ist alles gar nicht so schlimm – bei Kap Ragged Point ist ein Boot mit Segel versteckt.";
			link.l1 = "Die nächstgelegenen Länder von Barbados sind Dominica mit den Eingeborenen und Tobago mit den Spaniern. Ich weiß gar nicht, was für dich... schlimmer ist.";
			link.l1.go = "Djerry_9";
		break;
		
		case "Djerry_9":
			dialog.text = "Ich denke, ich werde es mit den Dons riskieren – auf Tobago werfen Schmuggler und Piraten oft den Anker. Oh, ich sehe, du verurteilst meine Wahl, "+GetAddress_Form(NPChar)+". Ich habe meinem Land ehrlich gedient – aber was soll ich tun, wenn es mich in die Steinbrüche geschickt hat?";
			link.l1 = "Ich verurteile dich nicht, "+npchar.name+". Jeder hat seinen eigenen Weg. Und jetzt nimm ordentlich Pulver und Kugeln mit – und geh. Bevor hier noch Soldaten auftauchen, ja, gell?";
			link.l1.go = "Djerry_10";
		break;
		
		case "Djerry_10":
			dialog.text = "Danke, "+GetAddress_Form(NPChar)+". Und Sie, junge Dame, äh, Mary. (verbeugt sich). Wir sind zwar keine Verwandten, aber in so einer, äh, Situation einen Namensvetter zu treffen... das ist wirklich unerwartet und...";
			link.l1 = "...";
			link.l1.go = "Djerry_10_add";
		break;
		case "Djerry_10_add":
			StartInstantDialog("Mary", "Djerry_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Djerry_11":
			dialog.text = "Wahrscheinlich schon, ja, gell? Und jetzt leb wohl, Jerry.";
			link.l1 = "...";
			link.l1.go = "Djerry_12";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab_mushketer"));
		break;
		
		case "Djerry_12":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_9");
		break;
		
		case "Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", bist du irgendwie beunruhigt? Du hast dich ziemlich überstürzt von deinem Namensvetter verabschiedet, ja, gell?";
			link.l1.go = "Mary_12";
		break;
		
		case "Mary_12":
			dialog.text = "Ich wollte diesen Menschen einfach nur so schnell wie möglich loswerden... Seine Geschichte ist doch total an den Haaren herbeigezogen, ja, gell?";
			link.l1 = "Wovon sprichst du, Liebling?";
			link.l1.go = "Mary_13";
		break;
		
		case "Mary_13":
			dialog.text = "Nachdem ich gehört habe, was dieser Handlanger von Bishop gesagt hat, habe ich keinen Zweifel mehr, dass diese armen Kerle genau durch seine Hand gestorben sind. Aber was davor war... Kasper – hast du aufmerksam zugehört, was er gesagt hat?";
			link.l1 = "Und was hat dir nicht gepasst, Liebes?";
			link.l1.go = "Mary_14";
		break;
		
		case "Mary_14":
			dialog.text = "Er behauptet, am Strand sei ein Boot versteckt. Aber von der Plantage sind über zwanzig Leute geflohen. Das heißt, das Boot muss ziemlich groß sein, ja, gell? Jerry ist ein Deserteur von der Flotte, er kann doch nicht ernsthaft glauben, dass er so ein großes Schiff ganz allein steuern kann, ja...";
			link.l1 = "Er muss nur das Segel setzen und den Kurs halten – den Rest erledigt der Wind. Ja, er geht ein großes Risiko ein, aber vielleicht ist der Tod auf See wirklich besser als durch die Hand eines Henkers auf der Plantage, ja, gell?";
			link.l1.go = "Mary_15";
		break;
		
		case "Mary_15":
			dialog.text = "Meinetwegen. Aber jetzt ist mir noch etwas anderes aufgefallen, das nicht zusammenpasst... Seinen Worten nach haben er und seine Freunde aus der Ferne zugesehen, wie die Söldner sich an diesem armen Mädchen vergangen haben, ja, gell?...";
			link.l1 = "Anstatt Hals über Kopf zu deinem Boot zu rennen... Ja, ich verstehe schon, worauf du hinauswillst, ja, gell? "+npchar.name+". Vielleicht sollte ich Mister Casper noch ein paar Fragen stellen, ja, gell?...";
			link.l1.go = "Mary_15_add";
		break;
		case "Mary_15_add":
			StartInstantDialog("WildRose_Naemnik_Rab_mushketer", "Mary_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Mary_16":
			dialog.text = "...";
			link.l1 = " Hey, "+npchar.name+", Alter! Warte mal eine Minute...";
			link.l1.go = "Mary_17";
		break;
		
		case "Mary_17":
			dialog.text = "...";
			link.l1 = "Verdammt!!! Mary, pass auf!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_11");
		break;
		
		case "Mary_21":
			dialog.text = "Verdammter Schuft! Wir haben ihm das Leben gerettet, und er! Was soll das denn heißen, "+pchar.name+"? Also...";
			link.l1 = "Ja, "+npchar.name+",   es ist niemand mehr am Leben, der die Wahrheit über das Geschehene wusste...";
			link.l1.go = "Mary_22";
		break;
		
		case "Mary_22":
			dialog.text = "Wir sollten hier verschwinden, "+pchar.name+". Wenn die Soldaten uns hier entdecken, bekommen wir richtig Ärger, ja, gell?";
			link.l1 = "Du hast recht, Mary. Gehen wir...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_15");
		break;
		
		case "Mary_23":
			dialog.text = "Weißt du, "+pchar.name+"Nach all dem würde ich jetzt wirklich gern ordentlich einen trinken, ja, gell?";
			link.l1 = "Da widerspreche ich nicht, Liebes. Ich hab selbst Lust, mir die Kehle zu befeuchten. Lass uns doch im 'Irischen Gehörnten' vorbeischauen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_2");
		break;
		
		case "Barmen_1":
			dialog.text = "Verzeihen Sie, dass ich Sie geweckt habe, Kapitän...";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Hast angeklopft, und dafür danke ich dir. Und jetzt sag schon, was willst du von mir, ja, gell?";
				link.l1.go = "Barmen_2";
			}
			else
			{
				link.l1 = "Gut, dass du daran gedacht hast zu klopfen, Kumpel. Wärst du einfach so reingeplatzt, wärst du schon die Treppe runtergekullert.\nWas glotzt du so? Raus mit der Sprache, warum hast du deinen Kadaver hierher geschleppt?";
				link.l1.go = "Barmen_2";
			}
		break;
		
		case "Barmen_2":
			dialog.text = "Einer der Stadtbewohner möchte Sie sprechen – Lewis Gernon. Er sagt, er hat ein wichtiges Gespräch mit Ihnen, ja, gell?";
			link.l1 = "Den Namen höre ich zum ersten Mal. Ich hoffe, er hat wirklich etwas Wichtiges, wenn er mich so von... meiner Arbeit abhält. Soll er reinkommen...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_5");
		break;
		
		case "Lewis_1":
			dialog.text = "Guten Tag, Mister "+pchar.lastname+". Miss... Casper.";
			link.l1 = ""+TimeGreeting()+", Mister "+npchar.lastname+". Ich kann mich nicht erinnern, dass wir uns schon einmal begegnet sind. Woher kennen Sie uns denn?";
			link.l1.go = "Lewis_2";
		break;
		
		case "Lewis_2":
			dialog.text = "Erinnern Sie sich nicht? Ach, verstehe... Mein Gesicht war voller Blut und Staub verschmiert, ich selbst habe mich erschrocken, als ich mich vor ein paar Stunden im Spiegel gesehen habe...";
			link.l1 = "...";
			link.l1.go = "Lewis_2_add";
		break;
		case "Lewis_2_add":
			StartInstantDialog("Mary", "Lewis_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_3":
			dialog.text = "Du... du bist doch der Mann, ja, wir haben dich gefunden und...";
			link.l1 = "...";
			link.l1.go = "Lewis_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_3_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_4":
			dialog.text = "Und meine Susan. Meine arme Suzi...";
			link.l1 = "...";
			link.l1.go = "Lewis_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_4_add":
			StartInstantDialog("Mary", "Lewis_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_5":
			dialog.text = "Wir dachten, ihr wärt tot. So wie... Sie war eure Frau, ja, gell?";
			link.l1 = "...";
			link.l1.go = "Lewis_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_5_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_6":
			dialog.text = "Ja, Ma’am. Sie war meine Frau, und ich war wie gelähmt vor Angst... und konnte nichts tun. Mein Gott, mein Gott...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_8");
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		
		case "Lewis_7":
			dialog.text = "(schluchzt) Sie haben mich verprügelt und mich gezwungen, dabei zuzusehen...";
			link.l1 = "Stehen Sie auf, "+GetAddress_Form(NPChar)+". Sie trifft keine Schuld. Niemand hätte es allein gegen so viele Halunken geschafft.";
			link.l1.go = "Lewis_8";
		break;
		
		case "Lewis_8":
			dialog.text = "Es waren so viele, so viele... Aber trotzdem habe ich...";
			link.l1 = "Aber immerhin haben Sie überlebt, und die Mörder Ihrer Frau schmoren in der Hölle. Das ist ein schwacher Trost, aber immerhin etwas, Mister "+npchar.lastname+". Aber ich wollte dich noch etwas fragen, ja, gell?...";
			link.l1.go = "Lewis_9";
			LAi_ActorAnimation(npchar, "ground_standup", "WildRose_Etap1_City_8_1", 7);
		break;
		
		case "Lewis_9":
			dialog.text = "Ja, Mister "+pchar.lastname+"?";
			link.l1 = "Wer war das? Bishops Söldner oder entlaufene Sklaven?";
			link.l1.go = "Lewis_10";
		break;
		
		case "Lewis_10":
			dialog.text = "Das waren Jerry Casper und die anderen Flüchtlinge. Ihr habt Bruce Primer und seine Leute zu Unrecht verdächtigt.";
			link.l1 = "Bishops Söldner?";
			link.l1.go = "Lewis_11";
		break;
		
		case "Lewis_11":
			dialog.text = "Ja. Bruce war zwar wirklich ein Gauner und hat für Bishop viele schmutzige Sachen erledigt – aber ein Vergewaltiger war er nicht, ja, gell?";
			link.l1 = "Mir kam das irgendwie nicht so vor. Aber ich will mich nicht mit Ihnen streiten, "+npchar.name+". Allerdings, da Sie ja bei Bewusstsein waren und alles gesehen haben, hätten Sie doch aufstehen und...";
			link.l1.go = "Lewis_12";
		break;
		
		case "Lewis_12":
			dialog.text = "Verzeih mir, "+GetAddress_Form(NPChar)+". Du kannst mich für einen erbärmlichen Feigling halten – aber ich konnte mich einfach nicht rühren, so sehr hatte ich Angst. Als diese Halunken mir und Susie den Weg versperrten, habe ich zuerst aus Leibeskräften geschrien, wollte um Hilfe rufen.";
			link.l1 = "Und sie haben Sie verprügelt.";
			link.l1.go = "Lewis_13";
		break;
		
		case "Lewis_13":
			dialog.text = "Jerry hat mir mit dem Kolben seines Musketen einen Schlag verpasst und dann gesagt, er würde mich in Stücke schneiden, direkt vor Susans Augen. Mir... mir ist es peinlich, das zuzugeben, aber ich glaube, ich habe für ein paar Sekunden sogar vor Angst das Bewusstsein verloren. Und währenddessen haben sie...";
			link.l1 = "Ich habe Sie verstanden, Mister "+npchar.lastname+". An Ihrem Verhalten ist nichts Beschämendes. So etwas kann längst nicht jeder ertragen. Schade, dass Sie nicht eingegriffen haben – aber was geschehen ist, lässt sich nicht rückgängig machen. Doch ich bin froh, dass wir immerhin einen der Mörder Ihrer Frau ins Jenseits befördert haben – auch wenn es ihm fast gelungen wäre, uns zu täuschen.";
			link.l1.go = "Lewis_14";
			link.l2 = "Heißt das, wir sind im Kampf gegen Bishops Söldner fast draufgegangen – nur weil ihr Angst hattet, ja, gell? Eine großartige Ausrede, "+npchar.name+". Gut, dass wir überhaupt, wenn auch spät, die Sache klären konnten...";
			link.l2.go = "Lewis_15";
		break;
		
		case "Lewis_14":
			dialog.text = "Ja, "+GetAddress_Form(NPChar)+". Ich bin gekommen, um Ihnen dafür zu danken. Auch wenn Sie ihm anfangs geglaubt haben...";
			link.l1 = "Bruce Primer hat sich dafür ganz schön ins Zeug gelegt. Er sollte besser aufpassen, was er so von sich gibt...";
			link.l1.go = "Lewis_16";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Lewis_15":
			dialog.text = "Ja, "+GetAddress_Form(NPChar)+". Ich bin gekommen, um Ihnen dafür zu danken. Auch wenn Sie ihm anfangs geglaubt haben...";
			link.l1 = "Bruce Primer hat sich dafür ziemlich ins Zeug gelegt. Er sollte besser aufpassen, was er so von sich gibt...";
			link.l1.go = "Lewis_16";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Lewis_16":
			dialog.text = "Leider haben wir an diesem Tag alle Fehler gemacht... Susan und ich hätten nicht nach Ragged Point spazieren gehen sollen, Bruce hätte rechtzeitig den Mund halten sollen... Und Sie hätten Jeremy nicht vertrauen dürfen. Aber dank Miss Casper wurde die Gerechtigkeit wiederhergestellt.";
			link.l1 = "...";
			link.l1.go = "Lewis_16_add";
		break;
		case "Lewis_16_add":
			StartInstantDialog("Mary", "Lewis_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_17":
			sld = CharacterFromID("WildRose_Lewis");
			dialog.text = "Ich ahne, worüber Sie mich fragen wollen, Mister "+sld.lastname+". Aber ich habe mit diesem Menschen überhaupt nichts zu tun.";
			link.l1 = "...";
			link.l1.go = "Lewis_17_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_17_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_18":
			dialog.text = "Ich weiß, Miss. Das habe ich sofort verstanden, als ich diesen Raum betreten habe. Sie und er haben nicht das Geringste gemeinsam. Und trotzdem, Susan... war überzeugt, dass in dieser Welt nichts zufällig geschieht.";
			link.l1 = "...";
			link.l1.go = "Lewis_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_18_add":
			StartInstantDialog("Mary", "Lewis_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_19":
			dialog.text = "Ihre Frau hatte recht. Davon habe ich mich selbst schon oft überzeugt, ja, gell? Und "+pchar.name+" auch.";
			link.l1 = "...";
			link.l1.go = "Lewis_19_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_19_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_20":
			dialog.text = "...";
			link.l1 = "Stimmt. Allerdings glaube ich nicht, dass jetzt der richtige Moment für philosophische Gespräche ist. Das wird euch wohl kaum helfen, "+npchar.name+". Damit kann nur die Zeit helfen, ja, gell?";
			link.l1.go = "Lewis_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), pchar);
			CharacterTurnByChr(CharacterFromID("Mary"), pchar);
		break;
		
		case "Lewis_21":
			dialog.text = "Wahrscheinlich haben Sie recht, Mister "+pchar.lastname+". Nun, danke Ihnen noch einmal und leben Sie wohl. Ich werde für Sie und Miss Casper beten.";
			link.l1 = "Mach's gut, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_10");
		break;
		
		case "Mary_31":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Ich weiß, Liebes, ich hätte den Bastard fast laufen lassen...";
			link.l1.go = "Mary_32";
		break;
		
		case "Mary_32":
			dialog.text = "Einen Mistkerl namens Jerry Casper.";
			link.l1 = "Stimmt... Moment mal... du glaubst doch nicht etwa, dass er...";
			link.l1.go = "Mary_33";
		break;
		
		case "Mary_33":
			dialog.text = "Ich weiß, dass das wirklich dumm ist...";
			link.l1 = "Und ob! Und was, wenn du Smith oder Jones heißen würdest? Davon laufen doch unzählige durch die Straßen – und irgendeiner von denen begeht bestimmt Schandtaten... Und dieser Jerry, soll er doch in der Hölle schmoren – vielleicht ist er ja gar kein Casper...";
			link.l1.go = "Mary_34";
			link.l2 = "So ist es, meine Liebe. Dieser verdammte Jerry hätte sich überhaupt mit einem falschen Nachnamen vorstellen können – das ist alles.";
			link.l2.go = "Mary_35";
		break;
		
		case "Mary_34":
			dialog.text = "Und trotzdem... Ich weiß, dass du mich nicht verstehst, aber stell dir einfach vor, was du denken würdest, wenn er deinen Nachnamen hätte "+pchar.lastname+".";
			link.l1 = "Das ist nicht dasselbe, Mary. "+pchar.lastname+" - ein Adelsgeschlecht, ja, gell?...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Mary_35":
			dialog.text = "Und trotzdem... Ich weiß, dass du mich nicht verstehst, aber stell dir einfach vor, was du denken würdest, wenn er deinen Nachnamen hätte "+pchar.lastname+".";
			link.l1 = "Das ist nicht dasselbe, Mary. "+pchar.lastname+" - ein Adelsgeschlecht, ja, gell?...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Mary_36":
			dialog.text = "Und die Caspers, das sind halt Leute ohne Herkunft, ohne Familie, ja, gell? Wahrscheinlich sollte ich jeden Tag dem lieben Gott danken, dass du überhaupt auf mich aufmerksam geworden bist und nicht auf irgendeine eingebildete...";
			link.l1 = ""+npchar.name+", ich habe das ganz und gar nicht so gemeint – das verstehst du doch. Mitglieder eines Adelsgeschlechts sind durch Blutsbande miteinander verbunden – und das ist etwas ganz anderes, als einfach nur denselben Nachnamen zu tragen. Den, wie ich schon sagte, sich dieser Jemand außerdem einfach aneignen konnte...";
			link.l1.go = "Mary_37";
		break;
		
		case "Mary_37":
			dialog.text = "Es geht nicht nur darum, "+pchar.name+"...";
			link.l1 = "Liebling, wir hatten einen langen und schweren Tag. Wir sind meilenweit durch den Dschungel gestapft, hätten sterben können... und dann konnten wir nicht mal richtig schlafen. Es ist kein Wunder, dass dir allerlei seltsame Gedanken durch den Kopf gehen. Wir beide müssen einfach mal richtig ausschlafen.";
			link.l1.go = "Mary_38";
		break;
		
		case "Mary_38":
			dialog.text = "Ich finde das gar nicht seltsam, aber gut... reden wir morgen.";
			link.l1 = "Mit klarem Kopf werden wir alles viel schneller klären. Leg dich hin, Liebes, wir müssen diesen Tag hinter uns lassen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_1");
		break;
		
		case "Waitress_1":
			dialog.text = "Ist alles in Ordnung mit Ihnen, "+GetAddress_Form(NPChar)+"? Ihr seht ja ganz seltsam aus, als hättet ihr einen Geist gesehen. Vielleicht wollt ihr einen Rum trinken? Oder lieber Wein? Wir haben eine ausgezeichnete Auswahl, ja, gell? Ein bisschen Entspannung würde euch guttun.";
			link.l1 = "Zum Teufel mit dem Alkohol. Ich suche ein Mädchen...";
			link.l1.go = "Waitress_2";
		break;
		
		case "Waitress_2":
			dialog.text = "Da sind Sie hier falsch, Kapitän. Das ist eine Taverne, kein Bordell. Gehen Sie einfach raus, und gegenüber sehen Sie...";
			link.l1 = "Hör zu, mir ist nicht nach Scherzen. Ich suche ein rothaariges Mädchen, im roten Wams, sie ist bewaffnet. Ihr Name ist Mary Casper.";
			link.l1.go = "Waitress_3";
		break;
		
		case "Waitress_3":
			dialog.text = "Na gut, wenn es nicht zum Scherzen ist, dann habe ich Ihnen nichts zu sagen. Meine Schicht hat vor einer Stunde angefangen, und ich habe hier niemanden mit roten Haaren in einem roten Wams gesehen.";
			link.l1 = "Also ist sie in der Nacht verschwunden... Aber wohin könnte sie nur gegangen sein?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_4");
		break;
		
		case "Mary_41":
			dialog.text = "Guten Morgen, mein Lieber! Du hast aber lange geschlafen...";
			link.l2 = "Du hast mich aber ganz schön nervös gemacht, ja, gell? "+npchar.name+". Verschwinde nicht mehr einfach so, ohne Vorwarnung, ja, gell?...";
			link.l2.go = "Mary_43";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_43":
			dialog.text = "Ich wollte dich nicht wecken. Und außerdem, du verschwindest ja auch manchmal einfach so, ohne ein Wort zu sagen, ja, gell?...";
			link.l1 = "Und du hast dich entschieden, meine Gefühle zu erwidern, ja, gell?";
			link.l1.go = "Mary_44";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;
		
		case "Mary_44":
			dialog.text = "Eigentlich musste ich einfach mal allein mit meinen Gedanken sein, ja, gell? Ich wollte nicht, dass du dir Sorgen machst.";
			link.l1 = "Beunruhigt dich etwas, ja, gell?";
			link.l1.go = "Mary_46";
		break;
		
		case "Mary_46":
			dialog.text = "Unser gestriges Gespräch. Über Nachnamen, Blutsbande...";
			link.l1 = "Also bist du doch sauer auf mich, ja, gell?...";
			link.l1.go = "Mary_47";
		break;
		
		case "Mary_47":
			dialog.text = "Nein, mein Lieber, darum geht es mir gar nicht. Mir ist nur plötzlich klar geworden, dass ich eigentlich gar nichts über meine Familie weiß. Du zum Beispiel bist der Sohn eines Adelsgeschlechts. Die Jungs an Bord erzählen hin und wieder etwas über ihre Familien. Und ich? Ich habe gar nichts zu erzählen – ich habe meine Eltern nie gekannt. Verdammt, ich weiß ja nicht einmal, wo ich geboren wurde...";
			link.l1 = "War das nicht auf der Insel der Gerechtigkeit?";
			link.l1.go = "Mary_48";
		break;
		
		case "Mary_48":
			dialog.text = "Eric, der Mann, der mich großgezogen hat, hat das immer behauptet. Aber wenn das so ist – warum hat nie jemand von den Bewohnern der Insel je von meinen Eltern erzählt, sie nicht einmal erwähnt? Ich habe Donald Greensby mal darauf angesprochen, aber er hat mir nichts Vernünftiges geantwortet.";
			link.l1 = "Oder wollte einfach nicht reden.";
			link.l1.go = "Mary_49";
		break;
		
		case "Mary_49":
			dialog.text = "Siehst du! Genau das habe ich mir auch gedacht, ja, gell? Weißt du, früher habe ich einfach so vor mich hingelebt, ohne groß über sowas nachzudenken. Aber gestern, als wir diesem Mistkerl Jerry begegnet sind... da habe ich mich gefragt – wer war eigentlich mein Vater? Und meine Mutter? Warum hat mir nie jemand von ihnen erzählt, als ob sie gar nicht existiert hätten? Was, wenn mein Vater genauso ein Halunke war wie dieser Jerry?";
			link.l1 = "Das spielt überhaupt keine Rolle, "+npchar.name+". Andere Menschen haben dich großgezogen – und sie haben es gut gemacht.";
			link.l1.go = "Mary_50";
			link.l1 = "Ich bezweifle, dass das so ist. Und ich habe ehrlich gesagt keine Ahnung, was das überhaupt für eine Rolle spielt, wenn du dir früher darüber offenbar nie Gedanken gemacht hast.";
			link.l1.go = "Mary_51";
		break;
		
		case "Mary_50":
			dialog.text = "Aber für mich ist das wichtig, "+pchar.name+", ja, gell? Ich will wissen, ich habe ein Recht darauf zu wissen, wer meine Eltern waren. Findest du nicht auch, dass ich das wissen sollte?";
			link.l1 = "Natürlich bin ich einverstanden, anders geht es ja gar nicht. Aber wenn man überhaupt etwas über deinen Vater und deine Mutter herausfinden will, dann nur auf der Insel der Gerechtigkeit. Du kennst ja nicht einmal ihre Namen, stimmt's?";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "Mary_51":
			dialog.text = "Aber für mich ist das wichtig, "+pchar.name+", ja, gell? Ich will wissen, ich habe ein Recht darauf zu wissen, wer meine Eltern waren. Bist du da nicht auch meiner Meinung, ja, gell?";
			link.l1 = "Natürlich bin ich einverstanden, anders geht es ja gar nicht. Aber wenn man überhaupt etwas über deinen Vater und deine Mutter herausfinden will, dann nur auf der Insel der Gerechtigkeit. Du kennst ja nicht einmal ihre Namen, stimmt's?";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Mary_52":
			dialog.text = "Genau so ist es, Liebling. In meiner Gegenwart wurden sie kein einziges Mal erwähnt, ja, gell?";
			link.l1 = "Das heißt, in die Stadtarchive der englischen Kolonien zu gehen, ist wohl noch zu früh. Erst müssen wir auf diesen Schiffsfriedhof zurückkehren und versuchen, dort irgendwelche Spuren deiner Herkunft zu finden.";
			link.l1.go = "Mary_53";
		break;
		
		case "Mary_53":
			dialog.text = "Ich bin froh, dass du mich verstehst, ja, gell? "+pchar.name+". Danke dir.";
			link.l1 = ""+npchar.name+", du überraschst mich wirklich, ja, gell? Das ist das Mindeste, was ich für dich tun kann, meine Liebe.";
			link.l1.go = "Mary_54";
		break;
		
		case "Mary_54":
			dialog.text = "Irgendwie habe ich ja fast zwanzig Jahre gelebt, ohne irgendetwas über sie zu wissen, ja, gell?...";
			// dialog.text = "Am Ende hat mich das über zwanzig Jahre lang überhaupt nicht gekümmert...";
			link.l1 = "...";
			link.l1.go = "Mary_55";
		break;
		
		case "Mary_55":
			dialog.text = "Also kann ich es noch eine Weile aushalten, ja, gell?";
			link.l1 = "Ich sehe, dass dir das wichtig ist und dass du es brauchst, "+npchar.name+". Also werde ich versuchen, dich nicht warten zu lassen. Und jetzt lass uns gehen, wir müssen zurück zum Schiff. Dort bin ich wenigstens etwas beruhigter, was dich angeht.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_6");
		break;
		
		// ============================================================
		// ================== ЭТАП 2. «ДИТЯ ОСТРОВА» ==================
		// ============================================================
		case "Mary_61":
			dialog.text = "Heimatliche Küsten... Weißt du, "+pchar.name+"Ich glaube, wenn wir in zehn Jahren wieder hier wären, würde alles genauso aussehen wie jetzt, ja, gell?";
			link.l1 = "Vielleicht, "+npchar.name+", vielleicht. Die Schiffe des inneren Rings werden zwar noch schwimmen, aber die Menschen hier werden schon andere sein.";
			link.l1.go = "Mary_62";
			link.l2 = "Ich bezweifle das stark – hier hält alles nur noch mit Ach und Krach zusammen. Und dank dem Genie des Mechanikers.";
			link.l2.go = "Mary_63";
		break;
		
		case "Mary_62":
			dialog.text = "Und weißt du, ich erinnere mich kaum noch an diejenigen, die vor zehn oder fünfzehn Jahren auf diesen Schiffswracks gelebt haben. Nur an die, die mir wirklich nahe standen – Alan, Erik...";
			link.l1 = "Wahrscheinlich soll es so sein. Man kann sich nicht an alles und jeden erinnern. Auch bei mir verblassen die Namen und Gesichter – aus der Zeit in Paris, ganz zu schweigen von Gascogne. Und ich dachte, so etwas passiert nur alten Leuten.";
			link.l1.go = "Mary_64";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Mary_63":
			dialog.text = "Und eigentlich erinnere ich mich kaum noch an die, die auf diesen Schiffswracks vor zehn, fünfzehn Jahren gelebt haben. Nur an die, die mir am nächsten standen – Alan, Erik...";
			link.l1 = "Wahrscheinlich soll es so sein. Man kann sich nicht an alles und jeden erinnern. Auch bei mir verblassen Namen und Gesichter – aus der Pariser Zeit, von Gascogne ganz zu schweigen. Und ich dachte, so etwas passiert nur alten Leuten.";
			link.l1.go = "Mary_64";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Mary_64":
			dialog.text = "Aber dieser Ort... Es ist wie eine andere Welt, ja, gell? Stell dir vor, einige von denen, die erst vor Kurzem hier angekommen sind, behaupten, dass die Zeit hier fast dreimal so schnell vergeht wie auf dem Festland...";
			link.l1 = "Ha-ha, wie alt bist du denn dann, ja, gell?";
			link.l1.go = "Mary_65";
		break;
		
		case "Mary_65":
			dialog.text = "Ich habe das übrigens ganz ernst gemeint, ja, gell? "+pchar.name+", ja, gell!";
			link.l1 = "Also, mal im Ernst, es wird Zeit, zur Sache zu kommen. Gibt es unter den Narwalen jemanden, der älter ist als Grinspie, ja, gell?";
			link.l1.go = "Mary_66";
		break;
		
		case "Mary_66":
			dialog.text = "Mhm, nein, ich glaube nicht. Aber ich habe dir doch schon gesagt, dass er mir nichts gesagt hat, als ich ihn danach gefragt habe, ja, gell?";
			link.l1 = "Und trotzdem habe ich keine anderen Ideen, wer uns helfen könnte, die Ereignisse von vor zwanzig Jahren aufzuklären. Zumindest im Moment nicht. Also nehmen wir Kurs auf die 'Esmeralda'.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_2");
		break;
		
		case "Schmidt_1":
			dialog.text = "Ah, "+pchar.name+" und Mary, was für ein Treffen! Freut mich, euch hier zu sehen... und noch lebendig, hehe. Im letzten Monat sind am äußeren Ring zwei oder drei Schiffe zerschellt – das Meer ist zurzeit verdammt unruhig. Ja, und versucht nicht, eine verschlossene Tür einzurennen – am Ende macht ihr noch das Schloss kaputt, und ich darf es dann reparieren. Ihr wollt doch sicher zu Donald, oder?";
			link.l1 = "Und dir auch einen guten Tag, Freund. Zu ihm selbst. Aber wenn die Tür abgeschlossen ist, dann ist er entweder auf ein anderes Schiff umgezogen oder will alte Freunde nicht sehen.";
			link.l1.go = "Schmidt_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Schmidt_2":
			dialog.text = "Weder noch, haha. Greenspy ist gerade am äußeren Ring, beim Training.";
			link.l1 = "Übungen? Wirklich? Bereitet er sich etwa auf einen neuen Krieg mit den Rivadors vor, ja, gell?";
			link.l1.go = "Schmidt_3";
		break;
		
		case "Schmidt_3":
			dialog.text = "Eigentlich hat sie ja nie aufgehört, ja, gell? "+pchar.name+". In letzter Zeit gibt es einfach viel weniger Schlägereien als früher. Aber trotzdem, in Sanchos Taverne bekommt immer noch ab und zu jemand eins auf die Nase... und manchmal fliegt auch ein Messer, ja, gell?";
			link.l1 = "Hm, früher sind die Clanmitglieder wohl nicht in der Taverne aufgetaucht, ja, gell?";
			link.l1.go = "Schmidt_4";
		break;
		
		case "Schmidt_4":
			dialog.text = "Nun, einiges hat sich verändert, seit ihr von der Insel weg seid. Donald und Eddie schaffen es, die Leute im Zaum zu halten. Bis jetzt. Aber wer weiß, was morgen passiert? Deshalb hat der alte Donnie das Ganze überhaupt angezettelt...";
			link.l1 = "Ich habe mir solche Mühe gegeben, das Gemetzel auf der Insel zu verhindern, nur damit ihr hier wieder Soldaten spielt, ja, gell? Und wie lange hängt er schon am äußeren Ring rum?";
			link.l1.go = "Schmidt_5";
			link.l2 = "Übungen sind ja gut und schön, aber schaden sie nicht vielleicht dem ohnehin schon brüchigen Waffenstillstand? Und wie lange drillt Greenspy die Jungs eigentlich schon, ja, gell?";
			link.l2.go = "Schmidt_6";
		break;
		
		case "Schmidt_5":
			dialog.text = "Seit drei Tagen schon. Er soll morgen bis Mittag zurück sein. Bei dem Eifer, mit dem sie da ihre Musketen durchspülen, haben sie bis morgen bestimmt nichts mehr zum Schießen übrig! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Schmidt_6":
			dialog.text = "Seit drei Tagen schon. Er soll morgen bis Mittag zurück sein. Bei dem Eifer, mit dem sie da ihre Musketen schrubben, haben sie bis morgen bestimmt nichts mehr zum Schießen übrig! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Schmidt_5_add":
			StartInstantDialog("Mary", "Schmidt_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_7":
			dialog.text = "Ist meine Kajüte auf der 'Ceres Smithy' noch frei? Oder hat sich da schon jemand eingenistet?";
			link.l1 = "...";
			link.l1.go = "Schmidt_7_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_7_add":
			StartInstantDialog("Schmidt_Clone", "Schmidt_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_8":
			dialog.text = "Da ist alles noch genauso, wie an dem Tag, als du das letzte Mal dort warst. Wir haben die Tür nicht einmal aufgeschlossen. Das Schloss haben wir in all der Zeit, ehrlich gesagt, auch nicht gereinigt oder geölt. Also, falls es aufgebrochen werden muss – sagt einfach Bescheid.";
			link.l1 = "...";
			link.l1.go = "Schmidt_8_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_8_add":
			StartInstantDialog("Mary", "Schmidt_9", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_9":
			dialog.text = "Unbedingt. Danke, Jürgen.";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_3");
			
			//доп
		break;
		
		case "Mary_71":
			dialog.text = "Es ist wirklich alles wie früher geblieben. Alles steht noch an seinem Platz – als wäre ich nie von hier fortgegangen... Hier haben wir uns zum ersten Mal getroffen, "+pchar.name+". Erinnerst du dich?";
			link.l1 = "Na klar! Du hast die beiden so fertiggemacht, dass ich schon dachte – hoffentlich lande ich nicht auch noch an ihrer Stelle!";
			link.l1.go = "Mary_72";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_72":
			dialog.text = "Es war doch alles ganz anders, ja, gell! Du hast mich buchstäblich aus den Klauen des Todes gerissen!";
			link.l1 = "Es scheint, dieses Treffen war mir vom Schicksal selbst bestimmt, ja, gell?";
			link.l1.go = "Mary_73";
		break;
		
		case "Mary_73":
			dialog.text = "Denkst du das wirklich, Liebling?";
			link.l1 = "Natürlich, meine Liebe. Und seitdem danke ich ihr jeden Tag dafür, dass sie mich direkt auf die 'Ceres Smithy' geführt hat, ja, gell?";
			link.l1.go = "Mary_74";
		break;
		
		case "Mary_74":
			dialog.text = ""+pchar.name+"... Sag mal, was hast du gedacht, als du mich zum ersten Mal gesehen hast, ja, gell?";
			link.l1 = "Nun... Ich erinnere mich nur daran, dass mein Herz aus der Brust springen wollte, als das passiert ist. Du warst so...";
			link.l1.go = "Mary_75";
		break;
		
		case "Mary_75":
			dialog.text = "Welche?";
			link.l1 = "Du bist ganz anders als alle, die ich vorher kannte. Deine Anmut, deine Stimme... und dieser rote Wams. Ich hatte nicht den Hauch einer Chance, dir zu widerstehen. Ich geb’s zu, ich habe mich immer gefragt: Warum gerade der? Warum ein roter Wams und kein Kleid, kein Hemd oder Korsett?";
			link.l1.go = "Mary_76";
		break;
		
		case "Mary_76":
			dialog.text = "Ich habe ihn gefunden, als ich neun war, am äußeren Ring. Damals habe ich es geliebt, dort spazieren zu gehen – alles Neue zu erforschen, Dinge zu finden, die es auf der Insel nicht gab, besonders Bücher. Ich wollte ihn unbedingt anprobieren, aber damals hätte ich darin höchstens untergehen können. Ich habe ihn dort versteckt, wo ich all meine anderen Funde aufbewahrt habe – in einem der Krähennester, die aus dem Wasser ragten.";
			link.l1 = "Und als er dir dann gepasst hat, hast du dich wieder an ihn erinnert, ja, gell?";
			link.l1.go = "Mary_77";
		break;
		
		case "Mary_77":
			dialog.text = "Vor ein paar Jahren, als ich so durch das Ringviertel gestreift bin, habe ich ein Buch über einen tapferen Kapitän in einer roten Uniform gefunden. Er kannte keine Angst, kämpfte gegen Hunderte von Feinden um der Liebe seines Lebens willen und war furchtlos. Damals habe ich ihn zum ersten Mal ausprobiert. Er gibt mir Selbstvertrauen...";
			link.l1 = "Und ein ganz besonderer Charme, meine Liebe! Aber weißt du was? Im Moment will ich nur eins... es dir ausziehen...";
			link.l1.go = "Mary_78";
		break;
		
		case "Mary_78":
			dialog.text = "Worauf wartest du dann noch, mein tapferer Kapitän?";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_5");
		break;
		
		case "Mary_81":
			dialog.text = "Guten Morgen, mein Lieber. Die Narwale sind gerade auf die 'Esmeralda' und die 'San Gabriel' zurückgekehrt, und Donald ist mit ihnen. Ich habe ihn in einem der Boote gesehen, ja, gell?";
			link.l1 = "Guten Morgen, guten Morgen... Ehrlich gesagt, nach so einer Nacht hätte ich bis Mittag geschlafen, und du bist schon auf den Beinen, schwirrst herum, ja, gell?";
			link.l1.go = "Mary_82";
		break;
		
		case "Mary_82":
			dialog.text = "Gestern haben wir über den Wams und das Krähennest gesprochen, wo ich ihn damals mal versteckt habe... Und plötzlich überkam mich so eine Sehnsucht nach jener Zeit, als ich mich dort vor allen versteckt habe, um in Ruhe Bücher über das große Land zu lesen... Ich konnte nicht anders und bin dorthin gesegelt. Früher konnte ich dort stundenlang sitzen, aber heute... habe ich dort einfach den Sonnenaufgang erlebt. Und ich habe verstanden: Am meisten auf der Welt möchte ich bei dir sein.";
			link.l1 = "Und ich bin an deiner Seite, "+npchar.name+". Na los, gehen wir zu Donald? Wir haben einiges mit ihm zu besprechen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_7");
		break;
		
		case "Grinspy_1":
			dialog.text = ""+pchar.name+", Mary, schön, Sie zu sehen! Man hat mir schon von Ihrem gestrigen Besuch berichtet. Ich wollte selbst bei Ihnen auf der 'Ceres Smithy' vorbeischauen, aber Sie waren schneller als der alte Mann. Ach, hätte ich doch noch Ihre Jugend...";
			link.l1 = "Na, an Energie mangelt es dir ja wirklich nicht, wie wir festgestellt haben, ja, gell? Wie liefen die Übungen?";
			link.l1.go = "Grinspy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_2":
			dialog.text = "Besser, als ich erwartet hatte. Wir haben das Entern feindlicher Schiffe und das Stürmen der Räume geübt... Kurz gesagt, wir haben uns richtig ins Zeug gelegt. Klar, ich habe die Jungs ganz schön angetrieben, aber das tut ihnen nur gut. Sie haben ihre Knochen schon lange nicht mehr durchbewegt, oh, schon lange nicht mehr, haha.";
			link.l1 = "Und was, wenn ich fragen darf, hat dich denn zu solchen Heldentaten getrieben? War dir auf der Insel zu langweilig, ja, gell?";
			link.l1.go = "Grinspy_3";
		break;
		
		case "Grinspy_3":
			dialog.text = "Hm, ich höre da Unzufriedenheit in deiner Stimme, ja, gell? "+pchar.name+". Ich kann seine Gründe natürlich schon verstehen, ja, gell?...";
			link.l1 = "Wirklich, "+npchar.name+"?";
			link.l1.go = "Grinspy_4";
		break;
		
		case "Grinspy_4":
			dialog.text = "Du bist ganz schön herumgerannt auf diesen morschen Schiffswracks, nur damit wir uns hier nicht gegenseitig die Kehle durchschneiden – das habe ich nicht vergessen. Niemand hat das vergessen.";
			link.l1 = "Und so hast du mir meine Mühen vergolten! Man sagt wohl zu Recht – einen echten Krieger drückt die Welt nur nieder, ja, gell?";
			link.l1.go = "Grinspy_5";
			link.l2 = "Und ich muss sagen, auf deinen gesunden Menschenverstand habe ich viel mehr gesetzt als auf den der Piraten oder der Rivadors, ja, gell?";
			link.l2.go = "Grinspy_6";
		break;
		
		case "Grinspy_5":
			dialog.text = "Lass mich ausreden. Ja, wir haben es geschafft, den Frieden zu bewahren – aber unsere Gegensätze sind nicht verschwunden. Zumindest nicht mit diesen schwarzgesichtigen Gottlosen. Letzte Woche wurde bei einer Schlägerei in der Taverne einer der Narwale getötet. Aber auch wir sind ihnen nichts schuldig geblieben...";
			link.l1 = "Ja, ja, genau so fängt es meistens an, ja, gell?";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_6":
			dialog.text = "Lass mich ausreden. Ja, wir haben es geschafft, den Frieden zu bewahren – aber unsere Gegensätze sind nicht verschwunden. Zumindest nicht mit diesen schwarzgesichtigen Gottlosen. Letzte Woche wurde bei einer Schlägerei in der Taverne einer der Narwale getötet. Aber wir haben uns auch nicht lumpen lassen...";
			link.l1 = "Ja, ja, genau so fängt es meistens an, ja, gell?";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_7":
			dialog.text = "Du irrst dich in zwei Dingen, "+pchar.name+". Erstens, es fängt nicht an, sondern geht weiter. Wenn du naiv gedacht hast, dass du dem ein Ende gesetzt hast, dann irrst du dich. Und zweitens, ich bin keine Heilige, die die andere Wange hinhält. Die Schwarzen sind wieder außer Rand und Band, und das gefällt mir gar nicht. Dexter übrigens auch nicht, aber er hält sich für einen großen Politiker und zieht es vor, sich über den Dingen zu halten. Deshalb habe ich nach einigem Überlegen meiner Meinung nach den... schmerzlosesten Weg gewählt, um den brüchigen Frieden zu bewahren.";
			link.l1 = "Hast du beschlossen, die Rivadors mit deinen Lehren einzuschüchtern?";
			link.l1.go = "Grinspy_8";
		break;
		
		case "Grinspy_8":
			dialog.text = "Vor ein paar Wochen hat ein englischer Galeone mit einer militärischen Ladung am äußeren Ring angedockt – da war wirklich alles Mögliche dabei... Aber das Wichtigste waren fünfzig nagelneue Flinten und guter Schießpulver. Und dann noch die Beiboote... An denen war die Farbe noch nicht mal richtig getrocknet! Die alten waren ja völlig durch, und nach den Stürmen bleiben eh nicht mehr viele Boote heil, sag ich dir...";
			link.l1 = "Und das alles ist jetzt im Besitz der Narwale, ja, gell?";
			link.l1.go = "Grinspy_9";
		break;
		
		case "Grinspy_9":
			dialog.text = "Ich hätte es vielleicht mit dem Admiral geteilt, aber wenn er sich schon für den Klügsten hält, will ich auch nicht wie ein Dummkopf dastehen. Mein Plan hat übrigens funktioniert, ja, gell?";
			link.l1 = "Hat dir Schwarzer Eddie einen Brief geschickt, in dem er verspricht, deinen Jungs nicht mehr das Messer an die Kehle zu setzen, ja, gell?";
			link.l1.go = "Grinspy_10";
		break;
		
		case "Grinspy_10":
			dialog.text = "Schwarzer Eddie hat seinen schwarzen Burschen befohlen, sich ruhig zu verhalten. Ich hatte befürchtet, dass es in meiner Abwesenheit mehr Provokationen von ihrer Seite geben würde – aber das Gegenteil war der Fall: die Rivadors sitzen still und halten sich sowohl von meinen Leuten als auch von den Zivilisten fern, die sie vorher auch regelmäßig schikaniert haben. Schwarze bleiben Schwarze – sie verstehen nur Gewalt. So hat Alan es gesagt, und möge dieses Schiff auf der Stelle untergehen, wenn er sich geirrt hat!";
			link.l1 = "Und wenn sie nach einer Weile wieder aufmüpfig werden, wirst du zur Abschreckung einen Bleiregen aus deinen neuen Musketen auf die 'Furia' und den 'Protector' niederprasseln lassen?";
			link.l1.go = "Grinspy_11";
		break;
		
		case "Grinspy_11":
			dialog.text = "Die Idee ist mutig und frech, ja, gell? Aber ich glaube, so weit wird es nicht kommen. Vielleicht tun wir nur so, als würden wir einen Überfall auf ihre Schiffe vorbereiten – und dann reißt sich Leighton zusammen und greift doch ein. Er ist zwar ein bisschen eingebildet geworden, aber trotzdem ein vorausschauender Kerl. Die Vernichtung weder unseres Clans noch der Schwarzen liegt in seinem Interesse – drei ungefähr gleich starke Machtzentren sorgen wenigstens für ein bisschen Gleichgewicht. Fällt eines davon weg, geht alles den Bach runter. Ich bin sicher, das weiß er – aber aus irgendeinem Grund muss ich seine Arbeit für ihn erledigen, ja, gell?";
			link.l1 = "Vielleicht schaue ich mal bei ihm vorbei, solange wir hier sind – es sei denn, er fängt wieder mit seinen Übungen an, haha.";
			link.l1.go = "Grinspy_12";
			link.l2 = "Ich werde versuchen, bei Gelegenheit bei ihm vorbeizuschauen – um darüber zu reden. Wer weiß, vielleicht hört er ja zu, ja, gell?";
			link.l2.go = "Grinspy_13";
		break;
		
		case "Grinspy_12":
			dialog.text = "Wenn es jemanden gibt, der ihn dazu bringen kann, die Schwarzen im Zaum zu halten, dann bist das du, "+pchar.name+". Aber an euren Gesichtern sehe ich, dass ihr nicht gekommen seid, um über Politik zu plaudern. Also, raus mit der Sprache, was gibt’s?";
			link.l1 = "...";
			link.l1.go = "Grinspy_12_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Grinspy_12_add":
			StartInstantDialog("Mary", "Grinspy_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_13":
			dialog.text = "Meine Eltern, Donald.";
			link.l1 = "...";
			link.l1.go = "Grinspy_13_add";
		break;
		case "Grinspy_13_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_14":
			dialog.text = "Ich verstehe nicht ganz, was du von mir willst, Mary.";
			link.l1 = "...";
			link.l1.go = "Grinspy_14_add";
		break;
		case "Grinspy_14_add":
			StartInstantDialog("Mary", "Grinspy_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_15":
			dialog.text = "Erzähl mir von ihnen, bitte, ja, gell? Du hast sie doch gekannt! Ich habe dich schon einmal nach ihnen gefragt, aber damals hast du meine Fragen nicht beantwortet...";
			link.l1 = "...";
			link.l1.go = "Grinspy_15_add";
		break;
		case "Grinspy_15_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_16":
			dialog.text = "Und deshalb hast du beschlossen, Charles hierher zu schleppen, haha! Du bist mir vielleicht eine, Mädchen, beim Donner! Wenn ich nie mit dir über deinen Vater und deine Mutter gesprochen habe, dann nur, weil ich sie nie gekannt habe, das ist alles!";
			link.l1 = "...";
			link.l1.go = "Grinspy_16_add";
		break;
		case "Grinspy_16_add":
			StartInstantDialog("Mary", "Grinspy_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_17":
			dialog.text = "Aber du bist doch das älteste Mitglied unseres Clans, ja, gell! Du bist schon hier, solange ich denken kann...";
			link.l1 = "...";
			link.l1.go = "Grinspy_17_add";
		break;
		case "Grinspy_17_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_18":
			dialog.text = "Ich bin vor etwas weniger als zwanzig Jahren auf der Insel aufgetaucht, schon nach deiner Geburt. Du warst damals noch ein richtig kleiner Wirbelwind, bist unter Tischen und Hockern herumgekrochen und hast Erik Udett keine Ruhe gelassen... Natürlich habe ich ihn gefragt, woher so ein unermüdliches Geschöpf hierhergekommen ist – und er hat mir geantwortet, dass du vor ein paar Jahren auf der Insel geboren wurdest. Über deinen Vater oder deine Mutter hat er kein Wort verloren. Und falls doch, dann habe ich es entweder nicht behalten oder längst vergessen...";
			link.l1 = "...";
			link.l1.go = "Grinspy_18_add";
		break;
		case "Grinspy_18_add":
			StartInstantDialog("Mary", "Grinspy_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_19":
			dialog.text = "So viele Jahre sind vergangen... Ich verstehe das, Donald, ja, gell?";
			link.l1 = "...";
			link.l1.go = "Grinspy_19_add";
		break;
		case "Grinspy_19_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_20":
			dialog.text = "Schade, dass Erik nicht bei uns ist – er war an diesem Ort schon lange vor mir. Übrigens, wenn er von deinen nächsten Streichen erzählte, erwähnte er oft Aurélie Bertin. Die alte Dame hat dich wirklich abgöttisch geliebt, das weiß ich noch ganz genau... Ich habe mir diese Frage nie gestellt, aber ich denke, als du zur Welt kamst, war sie schon auf der Insel. Vielleicht kann sie dir helfen?";
			link.l1 = "...";
			link.l1.go = "Grinspy_20_add";
		break;
		case "Grinspy_20_add":
			StartInstantDialog("Mary", "Grinspy_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_21":
			dialog.text = "Vielleicht. Ein guter Grund, sie mal wieder zu besuchen – ich weiß gar nicht mehr, wann ich das letzte Mal bei ihr war. Das ist nicht gut gelaufen, ja, gell?";
			link.l1 = "...";
			link.l1.go = "Grinspy_21_add";
		break;
		case "Grinspy_21_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_22":
			dialog.text = "Ich glaube nicht, dass sie dir böse ist. Aber setzt sie nicht zu sehr unter Druck – ich habe gehört, sie ist krank geworden. Wer weiß, was sonst noch...";
			link.l1 = "...";
			link.l1.go = "Grinspy_22_add";
		break;
		case "Grinspy_22_add":
			StartInstantDialog("Mary", "Grinspy_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_23":
			dialog.text = "Sei still, Donald, sonst ziehst du noch Unglück an! Aurélie wird uns alle überleben, ja, gell?";
			link.l1 = "...";
			link.l1.go = "Grinspy_24";
		break;
		
		case "Grinspy_24":
			dialog.text = "Komm, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "Grinspy_24_add";
		break;
		case "Grinspy_24_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_25":
			dialog.text = "...";
			link.l1 = "Mach’s gut, "+npchar.name+". Wir sehen uns bald.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_9");
		break;
		
		//
		case "Jillian_1":
			dialog.text = "Herrgott im Himmel, mir ist fast das Herz aus der Brust gesprungen. Kann man Leute denn so erschrecken, ja, gell?..";
			link.l1 = "...";
			link.l1.go = "Jillian_1_add";
			DelLandQuestMark(npchar);
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_1_add":
			StartInstantDialog("Mary", "Jillian_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_2":
			dialog.text = "Jillian! Ich hätte nicht erwartet, dich hier zu sehen, ja, gell? Was machst du denn hier? Und wo ist Aurélie?";
			link.l1 = "...";
			link.l1.go = "Jillian_2_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_2_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_3":
			dialog.text = "Und dir auch hallo, Mary. Und Ihnen, "+pchar.name+". Aurélie ist krank, wusstest du das nicht, ja, gell? Ich kümmere mich um sie, weil Bruder Julian mich darum gebeten hat. Er gibt mir Mixturen, mit denen ich sie versorge, aber... es sieht so aus, als würden sie nicht wirklich helfen. Im Moment schläft sie in der Kajüte hinten am Heck. Ich habe sie dorthin gebracht, damit ich hier aufräumen kann.";
			link.l1 = "...";
			link.l1.go = "Jillian_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_3_add":
			StartInstantDialog("Mary", "Jillian_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_4":
			dialog.text = "Wir haben es erst heute erfahren, ja, gell? Donald hat es uns erzählt. Wie geht es ihr?";
			link.l1 = "...";
			link.l1.go = "Jillian_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_4_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_5":
			dialog.text = "Schlecht. Sie klagt über Schwäche im Körper, steht kaum noch aus dem Bett auf. Manchmal murmelt sie irgendetwas Unverständliches, irgendeinen Unsinn... Ich habe schon so viele Geschichten aus längst vergangenen Zeiten gehört, dass ich sie nicht mehr zählen kann.";
			link.l1 = "...";
			link.l1.go = "Jillian_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_5_add":
			StartInstantDialog("Mary", "Jillian_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_6":
			dialog.text = "Hm, genau wegen so einer Geschichte sind wir eigentlich hier. Ich hoffe, sie weigert sich nicht, mit uns zu sprechen...";
			link.l1 = "...";
			link.l1.go = "Jillian_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_6_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_7":
			dialog.text = "Ist das wirklich so notwendig, Mary? Ich glaube nicht, dass wir sie in diesem Zustand stören sollten.";
			link.l1 = "...";
			link.l1.go = "Jillian_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_7_add":
			StartInstantDialog("Mary", "Jillian_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_8":
			dialog.text = "Es geht um meine Eltern. Aurélie könnte sie gekannt haben. Das ist mir wirklich wichtig, Jillian, ja, gell?";
			link.l1 = "...";
			link.l1.go = "Jillian_9";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "Jillian_9":
			dialog.text = "Gibt es auf der Insel kein Heilmittel, das ihren Zustand verbessern könnte?";
			link.l1 = "...";
			link.l1.go = "Jillian_9_add";
		break;
		case "Jillian_9_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_10":
			dialog.text = "Bruder Julian bereitet ihr Tinkturen zu. Aber sie helfen nur für eine Weile. Und selbst dann weigert sie sich, sie zu trinken, und ich muss sie ihr fast mit Gewalt einflößen. Manchmal habe ich Angst, dass sie daran einfach ersticken könnte – ich muss sie sogar dazu bringen, alles zu schlucken...";
			link.l1 = "...";
			link.l1.go = "Jillian_10_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_10_add":
			StartInstantDialog("Mary", "Jillian_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_11":
			dialog.text = "Die arme Aurélie! Gibt es denn wirklich niemanden auf der Insel, der ihr helfen kann?";
			link.l1 = "...";
			link.l1.go = "Jillian_11_add";
		break;
		case "Jillian_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_12":
			dialog.text = "Du weißt doch selbst, dass es hier keinen richtigen Arzt gibt. Und was kannst du hier schon ausrichten? Das Alter verschont bekanntlich niemanden, ja, gell?...";
			link.l1 = "...";
			link.l1.go = "Jillian_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_12_add":
			StartInstantDialog("Mary", "Jillian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_13":
			dialog.text = ""+pchar.name+", vielleicht jemanden von unserem Schiff mitbringen?";
			link.l1 = "Ich fürchte, "+npchar.name+", hier braucht man keinen Schiffsarzt, sondern einen erfahrenen Medicus.";
			link.l1.go = "Jillian_14";
		break;
		
		case "Jillian_14":
			dialog.text = "Ich bin jetzt sogar bereit, an Magie zu glauben, wenn das hilft, ja, gell?";
			link.l1 = "Hm... Magie? Vielleicht sollte ich mich an Chimiset wenden...";
			link.l1.go = "Jillian_14_add";
		break;
		case "Jillian_14_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_15":
			dialog.text = "Dem Chimiset? Dem schwarzen Hexer? "+pchar.name+", meint ihr das ernst, ja, gell?";
			link.l1 = "Wie noch nie. Ob er schwarz oder weiß ist, ist mir im Moment völlig egal. Wer Aurélie sonst noch helfen könnte – ich weiß es nicht. Ich glaube, ihr auch nicht. Also tretet zur Seite und kommt bloß nicht auf die Idee, mir im Weg zu stehen.";
			link.l1.go = "Jillian_16";
			link.l2 = "Mehr als das. Aurélie helfen weder die Medizin noch die Gebete von Bruder Julian. Chimiset ist unsere letzte Hoffnung.";
			link.l2.go = "Jillian_17";
		break;
		
		case "Jillian_16":
			dialog.text = "Ich traue meinen Ohren nicht! Aber das ist doch... ein Gottloser!";
			link.l1 = "Und das ist eine sterbende Frau, die kurz davor ist, zu vergessen, wie sie heißt. Ja, er ist ein Zauberer, aber ich habe gehört, dass sie zu vielem fähig sind, zu sehr vielem. Und wenn er es schafft, ihr den Verstand zurückzugeben – ist es da jetzt wirklich noch wichtig, welchem Glauben er angehört?";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_17":
			dialog.text = "Ich traue meinen Ohren nicht! Aber das ist doch... ein Gottloser!";
			link.l1 = "Und das ist eine sterbende Frau, die kurz davor ist, zu vergessen, wie sie heißt. Ja, er ist ein Hexer, aber ich habe gehört, dass sie zu vielem fähig sind, zu sehr vielem, ja, gell? Und wenn er es schafft, ihr den Verstand zurückzugeben – ist es da jetzt wirklich noch so wichtig, welchem Glauben er angehört?";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Jillian_18":
			dialog.text = ""+pchar.name+", hören Sie, mir liegt Aurélie selbst am Herzen... Gott ist mein Zeuge – ich tue alles in meiner Macht Stehende, um ihr Leid zu lindern! Aber wollen Sie wirklich diesem schwarzen Ketzer erlauben, hier in dieser Kajüte sein Ritual abzuhalten? Und was, wenn er dabei das Schiff in Brand setzt oder beschließt, jemandem ein Opfer darzubringen?";
			link.l1 = "Das werden wir nicht zulassen, "+npchar.name+", das versichere ich Ihnen.";
			link.l1.go = "Jillian_19";
		break;
		
		case "Jillian_19":
			dialog.text = "Und ich versichere euch beiden, falls das jemand herausfindet... Könnt ihr euch vorstellen, was hier los sein wird? Den anderen Bewohnern wird das nicht gefallen, und den Narwalen – erst recht nicht!";
			link.l1 = "Da haben Sie recht. Wir sollten nicht Chimiseta hierher schleppen, sondern Aurelie zu ihm bringen.";
			link.l1.go = "Jillian_20";
		break;
		
		case "Jillian_20":
			dialog.text = "Ihr habt sie nicht gesehen – die Alte kann kaum noch auf den Beinen stehen. Es wäre ein Wunder, wenn sie nicht über Bord fällt!";
			link.l1 = "Nun, manchmal bleibt uns wirklich nur noch das Wunder zu hoffen, ja, gell?   Und, Jillian...";
			link.l1.go = "Jillian_21";
		break;
		
		case "Jillian_21":
			dialog.text = "Was noch?";
			link.l1 = "Ich hoffe, dass Sie darüber schweigen werden. Sie sind ein kluges Mädchen und haben alles richtig eingeschätzt... Die Unruhen auf der Insel könnten leicht in ein Blutvergießen ausarten, und das will doch wirklich niemand, oder?";
			link.l1.go = "Jillian_22";
			link.l2 = "Kein Wort zu niemandem, klar? Wir haben euch vertraut – bringt uns nicht dazu, das zu bereuen. Ich denke, ihr versteht, dass, wenn unser Vorhaben kein Geheimnis mehr bleibt, auf der Insel ein Blutbad losbricht, wie sie es noch nie erlebt hat.";
			link.l2.go = "Jillian_23";
		break;
		
		case "Jillian_22":
			dialog.text = "Gut. Aber dann sorgt dafür, dass niemand sieht, wie ihr sie auf die 'Protector' bringt... Sonst muss ich unangenehme Fragen beantworten.";
			link.l1 = "Wir ersparen Ihnen unangenehme Antworten. Wir erledigen das in der Nacht.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Jillian_23":
			dialog.text = "Gut. Aber dann sorgt dafür, dass niemand sieht, wie ihr sie auf die 'Protector' bringt... Sonst muss ich unangenehme Fragen beantworten.";
			link.l1 = "Das lassen wir nicht zu. Wir machen das in der Nacht.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_24":
			dialog.text = "Kommt nach Mitternacht. Sie wird hier sein. Und um Himmels willen, seid vorsichtig.";
			link.l1 = "Keine Sorge, "+npchar.name+", wir werden äußerst aufmerksam sein.";
			link.l1.go = "Jillian_25";
		break;
		
		case "Jillian_25":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10");
		break;
		
		case "Jillian_26":
			if (GetHour() >= 3 && GetHour() <= 24)
			{
				dialog.text = "Komm nach Mitternacht. Sie wird hier sein...";
				link.l1 = "Gut.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Jillian_26";
			}
			else
			{
				dialog.text = "Oreli ist bereit. Ihr könnt sie führen.";
				link.l1 = "Ausgezeichnet. Dann auf geht’s.";
				link.l1.go = "exit";
				DelLandQuestMark(npchar);
				AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10_2");
			}
		break;
		
		case "Oreli_1":
			dialog.text = "Junge Leute, aber wohin... wohin gehen wir denn?! Das ist doch das Schiff der Rivadós! Wo ist Erik?!";
			link.l1 = "Eric hat sich mit Eddie Black angefreundet, wusstest du das nicht, ja, gell?";
			link.l1.go = "Oreli_2";
		break;
		
		case "Oreli_2":
			dialog.text = "Was redest du da, Junge! Ja, Erik kann Schwarze auf den Tod nicht ausstehen!";
			link.l1 = "Nicht schlecht! Dann lass uns ihn mal fragen, was zum Teufel er hier eigentlich macht, ja, gell?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_11");
		break;
		
		case "Eddy_1":
			dialog.text = "Schaut mal, wer uns da besucht! "+GetFullName(pchar)+" höchstpersönlich! Freut mich, meinen weißen Bruder zu begrüßen, haha! Erzähl, was führt dich her!";
			link.l1 = "Und dir auch hallo, "+npchar.name+"Ich würde ja gern einfach nur auf einen Becher Rum vorbeischauen, aber ich fürchte, ich habe ein dringendes Anliegen an dich – oder besser gesagt an Chimiset, ja, gell?";
			link.l1.go = "Eddy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Eddy_2":
			dialog.text = "Wir stehen tief in deiner Schuld, mein Freund. Wir tun alles, was in unserer Macht steht.";
			link.l1 = "Na gut, wenn das so ist. Denn auf sonst niemanden kann ich mehr hoffen, ja, gell?";
			link.l1.go = "Eddy_3";
		break;
		
		case "Eddy_3":
			dialog.text = "Mit welcher dieser Damen brauchst du Hilfe, "+pchar.name+"?";
			link.l1 = "Ich weiß nicht, ob du das ernst meinst oder nur Spaß machst, "+npchar.name+", aber mir ist nicht zum Lachen. Hilfe braucht Aurelie, natürlich.";
			link.l1.go = "Eddy_3_add";
		break;
		case "Eddy_3_add":
			StartInstantDialog("LSC_Oreli", "Eddy_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_4":
			dialog.text = "Erik! ERIK! Zeig dich, du alter Schlingel! Was soll das für ein Benehmen sein?! Beweg sofort deinen dürren Hintern hierher!";
			link.l1 = "...";
			link.l1.go = "Eddy_4_add";
		break;
		case "Eddy_4_add":
			StartInstantDialog("Eddy", "Eddy_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_5":
			dialog.text = "Also stimmt es wohl doch... Meine Leute haben mir berichtet, dass bei diesem Wrack da oben was im Kopf nicht ganz richtig läuft. Jetzt sehe ich – sie hatten recht. Aber ich verstehe nicht ganz, was du von Rivados willst...";
			link.l1 = "Lass mich mit Chimiset sprechen, und du wirst alles verstehen...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_12");
		break;
		
		case "Chimset_1":
			dialog.text = "Sprich, mein lieber Freund. Ich bin bereit, dir aufmerksam zuzuhören.";
			link.l1 = "Ich fasse mich kurz, Chimisette. Aurélie besitzt die Informationen, die Mary und ich brauchen. Aber aufgrund ihres Zustands, der – wenn ich das richtig verstehe – einfach nur am Alter liegt, können wir... weder diese Auskünfte von ihr bekommen, noch sicher sein, dass sie überhaupt stimmen. Ich habe von den Wundern gehört, zu denen sowohl indianische als auch afrikanische Schamanen fähig sind – deshalb bin ich hier, um dich um Hilfe zu bitten, Chimisette.";
			link.l1.go = "Chimset_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Chimset_2":
			dialog.text = "Ich habe dich gehört, mein Freund. Schamanen besitzen geheimnisvolle und mystische Kräfte, die oft selbst ihren eigenen Stammesangehörigen fremd und unverständlich bleiben, ganz zu schweigen von den Weißen. Manche nennen es Zauberei, andere ein Wunder. Wir können tatsächlich vieles – aber niemand vermag es, einen Fluss rückwärts fließen zu lassen... Und ihn aufzuhalten – das auch nicht.";
			link.l1 = "Was meinst du, Chimisette?";
			link.l1.go = "Chimset_3";
		break;
		
		case "Chimset_3":
			dialog.text = "Ich spreche vom Fluss der Zeit, mein Freund. Oder vom Fluss des Lebens – wie es dir lieber ist. Siehst du, du hast völlig recht – die Wurzel ihres Leidens liegt tatsächlich in ihren Jahren, in nichts anderem.";
			link.l1 = "Ich habe ein wenig darüber gehört. Ich weiß nur, dass das kein allzu seltenes Problem ist.";
			link.l1.go = "Chimset_4";
		break;
		
		case "Chimset_4":
			dialog.text = "Du hast recht. Menschen in ihrem Alter werden oft in die Täler der Träume getragen, manchmal aber auch in die der Albträume. Sie kehren zurück, nur um bald wieder dorthin zu entgleiten – nicht so sehr aus eigenem Willen, sondern wegen unbekannter Kräfte, die sie dorthin ziehen. Mit der Zeit wird die Krankheit immer stärker – und dann erinnert sich der Mensch weder an sich selbst noch an seine Freunde.";
			link.l1 = "Also kannst du wirklich nichts dagegen tun, ja, gell?";
			link.l1.go = "Chimset_5";
		break;
		
		case "Chimset_5":
			dialog.text = "Krankheit vertreiben – nein. Das liegt nicht in meiner Macht. Aber ich kann etwas anderes tun...";
			link.l1 = "Was genau?";
			link.l1.go = "Chimset_6";
		break;
		
		case "Chimset_6":
			dialog.text = "In dem Moment, wenn diese Frau wieder bei sich ist, werde ich ein schnelles Ritual durchführen, auf das ich mich vorher vorbereiten werde...";
			link.l1 = "Wird er die Krankheit zumindest verlangsamen, wenn er sie schon nicht aufhalten kann?";
			link.l1.go = "Chimset_7";
		break;
		
		case "Chimset_7":
			dialog.text = "Nicht ganz. Es wird sie zwingen, all ihre Lebenskraft zu mobilisieren, um so lange wie möglich bei Verstand zu bleiben.";
			link.l1 = "Wie lange ist „so lange wie möglich“?";
			link.l1.go = "Chimset_8";
		break;
		
		case "Chimset_8":
			dialog.text = "Das hängt nicht vom Ritual ab, sondern vom Menschen. Mancher hält eine Woche durch, ein anderer einen Monat... Ich habe von einem Mann gehört, der bei klarem Verstand und mit festem Gedächtnis fast über ein Jahr gelebt hat... Und als schon alle dachten, er sei geheilt, kam die Krankheit zurück – und hat ihn in derselben Nacht geholt.";
			link.l1 = "Um das herauszufinden, was wir brauchen, reicht eine Stunde. Wann kannst du das Ritual durchführen, Chimiset?";
			link.l1.go = "Chimset_9";
		break;
		
		case "Chimset_9":
			dialog.text = "Ich nehme die Frau jetzt gleich mit, bringe sie in den Laderaum – dort ist ein  Heiligtum eingerichtet... genau für solche Angelegenheiten. Wie es weitergeht, hängt davon ab, wann sie wieder zu sich kommt... Aber ich denke, bis zum Morgen sind wir fertig.";
			link.l1 = "Dann will ich euch nicht weiter stören. Und möge dir... dein Gott helfen, Chimiset.";
			link.l1.go = "Chimset_10";
		break;
		
		case "Chimset_10":
			dialog.text = "Zikomо! Hilf mir, die weiße Frau in den Laderaum zu bringen.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_13");
		break;
		
		case "Chimset_11":
			dialog.text = "Es hat geklappt, weißer Bruder. Wir haben es geschafft...";
			link.l1 = "...";
			link.l1.go = "Chimset_11_add";
			DelLandQuestMark(npchar);
		break;
		case "Chimset_11_add":
			StartInstantDialog("LSC_Oreli", "Chimset_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_12":
			dialog.text = "Oh, "+GetFullName(pchar)+"! Ich wusste gar nicht, dass ihr mit Mary zurück auf die Insel gekommen seid! Was für eine angenehme Überraschung!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_14_1");
		break;
		
		case "Chimset_13":
			dialog.text = "...";
			link.l1 = "Chimisette, danke dir! Ich weiß gar nicht, wie ich dir danken soll...";
			link.l1.go = "Chimset_14";
			link.l2 = "Na so was, Chimiset – du hast es geschafft! Ich hab’ ja gar nicht an dir gezweifelt...";
			link.l2.go = "Chimset_15";
		break;
		
		case "Chimset_14":
			dialog.text = "Alle Rivadors stehen für immer in deiner Schuld, mein Freund! Die Türen des 'Protektors' stehen dir immer offen.";
			link.l1 = "Ich hoffe, ich muss euch nicht weiter belästigen... Mary, Aurélie, wir müssen zurück auf die 'Pluto'.";
			link.l1.go = "Chimset_15_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Chimset_15":
			dialog.text = "Alle Rivados stehen für immer in deiner Schuld, mein Freund! Die Türen des 'Protektors' stehen dir immer offen.";
			link.l1 = "Ich hoffe, ich muss euch nicht weiter belästigen... Mary, Aurélie, wir müssen zurück auf die 'Pluto'.";
			link.l1.go = "Chimset_15_add";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		case "Chimset_15_add":
			StartInstantDialog("LSC_Oreli", "Chimset_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_16":
			dialog.text = "Ich habe ganz vergessen, wie ich meine Kajüte verlassen habe... Ach, dieses Alter – das Gedächtnis taugt einfach gar nichts, ja, gell? ";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_15");
		break;
		
		case "Oreli_11":
			dialog.text = "Na, na, junge Dame, was haben Sie denn in meiner Kajüte verloren?";
			link.l1 = "...";
			link.l1.go = "Oreli_11_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_12":
			dialog.text = "Orélie, ich...";
			link.l1 = "...";
			link.l1.go = "Oreli_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_12_add":
			StartInstantDialog("Mary", "Oreli_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_13":
			dialog.text = " Aurélie, ich habe sie gebeten, hier ein wenig aufzuräumen, während du weg warst. Es bringt doch nichts, wenn du dir mit deinen kranken Knien noch den Rücken krümmst, ja, gell? ";
			link.l1 = "...";
			link.l1.go = "Oreli_13_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
			
		break;
		case "Oreli_13_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_14":
			dialog.text = "Aufräumen?! Du...";
			link.l1 = "Jillian, danke dir für deine Arbeit. (flüsternd) Es hat alles geklappt. Chimiset hat es geschafft.";
			link.l1.go = "Oreli_15";
		break;
		
		case "Oreli_15":
			dialog.text = "Das kann nicht sein...";
			link.l1 = "Wie du siehst. Und jetzt lass uns bitte reden.";
			link.l1.go = "Oreli_15_add";
		break;
		case "Oreli_15_add":
			StartInstantDialog("LSC_Oreli", "Oreli_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_16":
			dialog.text = "Nun denn, meine Lieben, danke, dass ihr das alte Weib begleitet habt. Ich fürchte, bald werde ich gar nicht mehr rausgehen können. Meine Beine, ach, meine armen Beine...";
			link.l1 = "Wenn Sie gestatten, "+npchar.name+", wir bleiben kurz bei euch – wirklich nur für einen Moment. Mary und ich haben eine sehr wichtige Angelegenheit mit euch, ja, gell?";
			link.l1.go = "Oreli_17";
		break;
		
		case "Oreli_17":
			dialog.text = "Wenn ich nicht wieder auf ein anderes Schiff abgeschoben werde, helfe ich dir, so gut ich kann. Ich höre dir zu.";
			link.l1 = "...";
			link.l1.go = "Oreli_17_add";
		break;
		case "Oreli_17_add":
			StartInstantDialog("Mary", "Oreli_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_18":
			dialog.text = "Aurélie, ich möchte, dass du mir von meinen Eltern erzählst. Und von dem Tag, an dem ich zur Welt gekommen bin. Das ist doch hier auf der Insel passiert, ja, gell? Donald behauptet, dass es so war, aber damals war er ja noch gar nicht hier, also kann er es nicht genau wissen. Du lebst aber schon viel länger hier als er, ja, gell? Schon mehr als zwanzig Jahre, oder?";
			link.l1 = "...";
			link.l1.go = "Oreli_18_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_18_add":
			StartInstantDialog("LSC_Oreli", "Oreli_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_19":
			dialog.text = "Langsam, langsam, Mädchen, sprich nicht so schnell, bitte! Sonst komm ich gar nicht mehr mit, ja, gell?";
			link.l1 = "...";
			link.l1.go = "Oreli_19_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_19_add":
			StartInstantDialog("Mary", "Oreli_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_20":
			dialog.text = "Verstanden, ja, gell? Also, lass uns nochmal von vorne anfangen...";
			link.l1 = "...";
			link.l1.go = "Oreli_20_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_20_add":
			StartInstantDialog("LSC_Oreli", "Oreli_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_21":
			dialog.text = "Nicht nötig, Mary, ich bin noch nicht so schlecht dran, haha... Ich habe gehört, was du mir gesagt hast. Aber da ich wirklich schon am längsten auf der Insel lebe, hoffe ich, du wirst mein Alter mit Respekt und Verständnis behandeln...";
			link.l1 = "...";
			link.l1.go = "Oreli_21_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_21_add":
			StartInstantDialog("Mary", "Oreli_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_22":
			dialog.text = "Aber natürlich, Aurélie! Wie konntest du nur etwas anderes denken?";
			link.l1 = "...";
			link.l1.go = "Oreli_22_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_22_add":
			StartInstantDialog("LSC_Oreli", "Oreli_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_23":
			dialog.text = "Ach, wenn ich mir die heutige Jugend so anschaue... nein, nein, wir haben uns den Älteren gegenüber nie so benommen. Aber das gilt natürlich nicht für dich. Ich wollte nur sagen, es wäre einfacher, wenn ich deine Fragen nacheinander beantworte und nicht alle auf einmal...";
			link.l1 = "...";
			link.l1.go = "Oreli_23_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_23_add":
			StartInstantDialog("Mary", "Oreli_24", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_24":
			dialog.text = "Ich verstehe, Aurélie. Wie du willst, ja, gell? Also warst du auf der Insel, als ich geboren wurde? Wenn das überhaupt hier passiert ist, natürlich...";
			link.l1 = "...";
			link.l1.go = "Oreli_24_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_24_add":
			StartInstantDialog("LSC_Oreli", "Oreli_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_25":
			dialog.text = "Ich bin im Jahr 1633 auf die Insel gekommen, ja, gell? Manchmal habe ich Albträume von diesem Tag. Ein Sturm, unsere 'Reprisal' – eine Flöte, mit der mein Mann und ich nach Florida unterwegs waren – wird von den Wellen hin und her geworfen, als würde sie gleich kieloben gehen, und wir murmeln alle gelernten Gebete und denken uns neue aus... Und dann ein Krachen und...";
			link.l1 = "...";
			link.l1.go = "Oreli_25_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_25_add":
			StartInstantDialog("Mary", "Oreli_26", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_26":
			dialog.text = "Du bist also fünf Jahre vor meiner Geburt hier gelandet, ja, gell?";
			link.l1 = "...";
			link.l1.go = "Oreli_26_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_26_add":
			StartInstantDialog("LSC_Oreli", "Oreli_27", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_27":
			dialog.text = "So ungefähr. Damals war hier alles noch etwas anders – die 'San Jerónimo' hielt sich noch über Wasser, und der äußere Schiffsring war vielleicht anderthalb- bis zweimal kleiner... Und das sind noch lange nicht alle Schiffe, die hier untergegangen sind! Ich sag’s euch, junge Leute: Wenn ihr bei klarem Wetter auf den Meeresgrund schaut – euch wird angst und bange bei dem Anblick all der Schiffswracks da unten...";
			link.l1 = "...";
			link.l1.go = "Oreli_27_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_27_add":
			StartInstantDialog("Mary", "Oreli_28", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_28":
			dialog.text = "Uns interessiert das Schiff, mit dem meine Eltern hierher gekommen sind. Mit mir... oder ohne mich?";
			link.l1 = "...";
			link.l1.go = "Oreli_28_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_28_add":
			StartInstantDialog("LSC_Oreli", "Oreli_29", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_29":
			dialog.text = "Mit dir, Mädchen, mit dir.";
			link.l1 = "...";
			link.l1.go = "Oreli_29_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_29_add":
			StartInstantDialog("Mary", "Oreli_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_30":
			dialog.text = "Heißt das, ich bin also doch auf dem Festland geboren, ja, gell?";
			link.l1 = "...";
			link.l1.go = "Oreli_30_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_30_add":
			StartInstantDialog("LSC_Oreli", "Oreli_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_31":
			dialog.text = "Nein, ich meinte 'mit dir' in einem etwas anderen Sinn. Du warst im Bauch deiner Mutter und bist eine Woche später geboren.";
			link.l1 = "Findest du das etwa lustig, Aurélie?";
			link.l1.go = "Oreli_32";
			link.l2 = "Und Sie haben im Laufe der Jahre Ihren Sinn für Humor nicht verloren, Aurélie.";
			link.l2.go = "Oreli_33";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_32":
			dialog.text = "Nun, über mich selbst lache ich viel öfter als über andere. Entschuldige, Mary, ich wollte dich nicht verletzen.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_33":
			dialog.text = "Nun, über mich selbst lache ich viel öfter als über andere. Entschuldige, Mary, ich wollte dich nicht verletzen.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		case "Oreli_33_add":
			StartInstantDialog("Mary", "Oreli_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_34":
			dialog.text = "Alles in Ordnung, Aurélie. Bitte – erzähl weiter, ja, gell? Was ist mit meinen Eltern nach meiner Geburt passiert?";
			link.l1 = "...";
			link.l1.go = "Oreli_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_34_add":
			StartInstantDialog("LSC_Oreli", "Oreli_35", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_35":
			dialog.text = "Danach? Meine Liebe, allein die Tatsache, dass sie beide das überlebt haben – das war ein wahres Wunder! Was für ein fürchterlicher Sturm in jener Juninacht tobte! Als am Morgen das Boot deine Mutter zum inneren Ring brachte, konnten es viele erst gar nicht glauben – dass eine hochschwangere Frau, die kurz vor der Geburt stand, solch ein schreckliches Schiffsunglück überlebt hatte. Die arme Teresa... ich erinnere mich, als wäre es gestern gewesen...";
			link.l1 = "...";
			link.l1.go = "Oreli_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_35_add":
			StartInstantDialog("Mary", "Oreli_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_36":
			dialog.text = "Theresa? So hieß sie?";
			link.l1 = "...";
			link.l1.go = "Oreli_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_36_add":
			StartInstantDialog("LSC_Oreli", "Oreli_37", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_37":
			dialog.text = "Ja, so hat sie sich vorgestellt – und das war so ziemlich alles, was sie gesagt hat. Gegen Ende des Tages fiel sie in ein Fieberdelirium, das bis zur Geburt andauerte. Niemand war sicher, ob sie überhaupt in der Lage sein würde zu gebären – und noch weniger glaubte man daran, dass das Kind lebend zur Welt kommen würde, nach all dem, was sie durchgemacht hatte. Aber Teresa hat es geschafft. Sie hat es geschafft – und dann ihren letzten Atemzug getan. Möge der Herr ihre Seele behüten...";
			link.l1 = "...";
			link.l1.go = "Oreli_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_37_add":
			StartInstantDialog("Mary", "Oreli_38", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_38":
			dialog.text = "Mama ist gestorben, und ich blieb mit meinem Vater zurück? Aber warum haben dann alle behauptet, dass ich von Erik Udett aufgezogen wurde? Und...";
			link.l1 = "...";
			link.l1.go = "Oreli_38_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_38_add":
			StartInstantDialog("LSC_Oreli", "Oreli_39", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_39":
			dialog.text = "Mary, Liebling, ich hab dich doch gebeten... Überhäuf mich nicht mit so vielen Fragen, ja, gell?";
			link.l1 = "...";
			link.l1.go = "Oreli_39_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_39_add":
			StartInstantDialog("Mary", "Oreli_40", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_40":
			dialog.text = "Entschuldige, Aurélie, ich war kurz abgelenkt, ja, gell? Mein Vater, er hat doch auch einen Schiffbruch überlebt?";
			link.l1 = "...";
			link.l1.go = "Oreli_40_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_40_add":
			StartInstantDialog("LSC_Oreli", "Oreli_41", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_41":
			dialog.text = "Dein Vater... Weißt du, ich kann nicht viel über deinen Vater sagen – außer, dass ich so einen Kerl wirklich niemandem als Vater wünsche. Ein paar Tage nach deiner Geburt ist er einfach verschwunden und hat dich deinem Schicksal überlassen. Du hattest Glück, dass Erik so ein gutes und weiches Herz hatte – fast wie ein Zwieback, der in einer Tasse Grog eingeweicht wurde...";
			link.l1 = "...";
			link.l1.go = "Oreli_41_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_41_add":
			StartInstantDialog("Mary", "Oreli_42", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_42":
			dialog.text = "Sag mir wenigstens, wie er hieß, ja, gell!";
			link.l1 = "...";
			link.l1.go = "Oreli_42_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_42_add":
			StartInstantDialog("LSC_Oreli", "Oreli_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_43":
			dialog.text = "Oh... War es Jeffrey oder John, wenn ich mich nur erinnern könnte, ja, gell?";
			link.l1 = "Also, ihr erinnert euch nicht? Stimmt, "+npchar.name+"?";
			link.l1.go = "Oreli_44";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_44":
			dialog.text = "Zweifeln Sie etwa an meinen Worten, junger Mann?!";
			link.l1 = "Leise, "+npchar.name+",   ruhig. Ich wollte Ihnen nicht zu nahe treten. Es schien mir nur, dass Sie sich an diese Tage ziemlich gut erinnern, das ist alles.";
			link.l1.go = "Oreli_45";
			link.l2 = "Ich habe keinen Zweifel, ja, gell? "+npchar.name+". Ich versuche einfach nur, mir alle Details richtig zu merken – nicht mehr und nicht weniger. Aber das ganze Durcheinander macht die Sache etwas komplizierter, ja, gell?";
			link.l2.go = "Oreli_46";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_45":
			dialog.text = "Erinnerung ist eine wählerische Dame, "+pchar.name+", ziemlich wählerisch. Besonders, wenn so viele Jahre vergangen sind. Teresa vergisst man nicht so leicht – ich habe ihre Qualen die ganze Woche über mitangesehen! O-oh, wie leid sie mir tat!";
			link.l1 = "Und ihr Mann, war er denn nicht bei ihr?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Oreli_46":
			dialog.text = "Erinnerung ist eine wählerische Dame, "+pchar.name+", ziemlich wählerisch. Vor allem, wenn so viele Jahre vergangen sind. Teresa vergisst man nicht so leicht – ich habe die ganze Woche lang ihr Leiden mitangesehen! O-oh, wie leid sie mir tat!";
			link.l1 = "Und ihr Mann, war er denn nicht bei ihr?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_47":
			dialog.text = "Sehr selten. Fast die ganze Woche war er irgendwo unterwegs – auf der Suche nach Medikamenten und Mixturen, die damals auf der Insel sehr knapp waren...";
			link.l1 = "Also war er wohl ein guter Ehemann – immerhin hat er versucht, seiner Frau zu helfen, ja, gell?";
			link.l1.go = "Oreli_48";
		break;
		
		case "Oreli_48":
			dialog.text = "Als Ehemann war er vielleicht wirklich gut. Das habe ich nie bestritten, wenn ich das anmerken darf. Versuchen Sie nicht, mich durcheinanderzubringen, junger Mann!";
			link.l1 = "Und daran habe ich wirklich nicht gedacht, das schwöre ich, "+npchar.name+". Es ist nur offensichtlich, dass Sie nicht die beste Meinung von ihm haben. Und dass Sie sich nicht einmal an seinen Namen erinnern...";
			link.l1.go = "Oreli_49";
		break;
		
		case "Oreli_49":
			dialog.text = "Ich habe diesen Mann nur flüchtig im Dunkel der Kajüte von 'Ceres Smitty' gesehen, dort, wo jetzt Herr Jürgen wohnt. Er kam immer nur nachts, und an sein Gesicht erinnere ich mich nur sehr vage. Was seinen Namen angeht – beim Vornamen hat ihn niemand genannt, nur beim Nachnamen. Mal hieß es Casper hier, Casper da...";
			link.l1 = "Ich habe Sie verstanden, "+npchar.name+". Also wurde Mary geboren, und ein paar Tage später war er spurlos verschwunden. Haben sie ihn umgebracht?";
			link.l1.go = "Oreli_50";
		break;
		
		case "Oreli_50":
			dialog.text = "Schwierige Frage, junger Mann. Sehen Sie, an diesem Ort ist es ziemlich schwer, etwas geheim zu halten – hier liegt alles offen. Wenn es mal wieder Streit gibt – selbst innerhalb der Schiffe – weiß am nächsten Tag schon die ganze Insel Bescheid.";
			link.l1 = "Kein Wunder.";
			link.l1.go = "Oreli_51";
		break;
		
		case "Oreli_51":
			dialog.text = "Die Leichen der Ermordeten werden längst nicht immer gefunden – erfahrene Burschen versenken die Körper, indem sie Hände und Füße mit Ketten umwickeln oder ihnen Kanonenkugeln oder Steine anbinden. Die Krabben auf dem Grund erledigen dann den Rest. Doch die persönlichen Sachen der Toten tauchen entweder sofort oder nach einiger Zeit wieder auf.";
			link.l1 = "Vom Grund?!";
			link.l1.go = "Oreli_52";
		break;
		
		case "Oreli_52":
			dialog.text = "Natürlich nicht! Ich meinte, dass sie ins Auge fallen – ein Ring, eine Pistole mit Gravur, ein Ehrensäbel... Fragen dazu werden selten gestellt. Den Menschen bringt das ja auch nicht zurück, und unnötige Konflikte braucht wirklich niemand, ja, gell?";
			link.l1 = "Hatten Geoffrey oder John Casper irgendwelche auffälligen Sachen?";
			link.l1.go = "Oreli_53";
		break;
		
		case "Oreli_53":
			dialog.text = ""+pchar.name+"Ach, Gott mit euch – ich kann mich ja kaum an seinen Namen erinnern, und ihr stellt mir solche Fragen! Wenn da überhaupt etwas war, habe ich jedenfalls nichts davon gehört, dass dieses Ding bei einem anderen Bewohner der Insel gelandet wäre. Damals habe ich als Schankmaid in der Taverne gearbeitet, und kaum ein Gerücht ist an mir vorbeigegangen. Aber das heißt noch lange nicht, dass ich wirklich alles wusste.";
			link.l1 = "Wenn man sagt, dass Menschen spurlos verschwinden, meint man normalerweise, dass sie getötet wurden. Im Fall von Mister Casper sind Sie sich da aber offensichtlich nicht so sicher...";
			link.l1.go = "Oreli_54";
		break;
		
		case "Oreli_54":
			dialog.text = "Ich sage ja nur, dass 'verschwunden' noch lange nicht 'tot' heißt. Vor allem in jenen Jahren, als zwischen der Insel und Kuba ständig Tartanen von Schmugglern und Hehlern unterwegs waren... Wissen Sie, ich erinnere mich nicht mehr an seine Gesichtszüge, aber sein Blick... Das war der Blick eines Menschen, der überall zurechtkommt. Oder zumindest fest daran glaubt, ja, gell?";
			link.l1 = "Tartanen, Tartanen... Nichts ist unmöglich. Wenn wir seinen Namen wüssten, könnten wir die kolonialen Archive jener Jahre durchsuchen. Aber es wäre viel einfacher, wenn wir den Typ und den Namen des Schiffs hätten, auf dem er hierher 'gekommen' ist.";
			link.l1.go = "Oreli_55";
		break;
		
		case "Oreli_55":
			dialog.text = "Und was schauen Sie mich so an, junger Mann? Glauben Sie etwa, ich erinnere mich daran?";
			link.l1 = "Wir hoffen darauf, "+npchar.name+" - wenn man bedenkt, wie viel Sie uns schon erzählt haben.";
			link.l1.go = "Oreli_56";
			link.l2 = "Hm... Daran habe ich große Zweifel, ja, gell?";
			link.l2.go = "Oreli_57";
		break;
		
		case "Oreli_56":
			dialog.text = "Vielleicht fragen Sie auch noch, wie viele Kanonen er hatte und welchen Kaliber sie waren? Mein Lieber, wissen Sie, wie viele Schiffe hier über die Jahre untergegangen sind? Und Sie glauben, ich erinnere mich an jedes einzelne? Außerdem haben sich von diesem Schiff nur ein paar Leute gerettet – es hat sich ja kaum einen Tag über Wasser gehalten, gell...";
			link.l1 = "Klar... Verständlich, zwanzig Jahre sind vergangen. Danke, dass ihr wenigstens das nicht vergessen habt, was man uns damals erzählt hat, ja, gell?";
			link.l1.go = "Oreli_58";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Oreli_57":
			dialog.text = "Vielleicht wollen Sie auch noch wissen, wie viele Kanonen er hatte und welchen Kaliber sie waren? Mein Lieber, wissen Sie, wie viele Schiffe hier über die Jahre untergegangen sind? Und Sie glauben, ich erinnere mich an jedes einzelne? Außerdem haben sich von diesem Schiff nur ein paar Leute gerettet – es hat sich keine Tag an der Wasseroberfläche gehalten, ja, gell...";
			link.l1 = "Klar... Verständlich, zwanzig Jahre sind vergangen. Danke, dass ihr wenigstens das nicht vergessen habt, was man uns damals erzählt hat.";
			link.l1.go = "Oreli_58";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_58":
			dialog.text = "Ich hoffe, Sie machen keine Scherze und wollen sich nicht über eine alte Frau lustig machen, deren Gedächtnis löchrig wie ein Sieb geworden ist.";
			link.l1 = "Auf keinen Fall, "+npchar.name+". Ihr habt uns wirklich sehr geholfen. Gute Besserung. Nun, wir gehen dann.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_16");
		break;
		
		case "Mary_91":
			dialog.text = "Also, Teresa... So hieß sie. Meine arme Mama, ja, gell...";
			link.l1 = "Na ja, jetzt wissen wir wenigstens, von wem du so viel Kraft und Sturheit hast. Eine schwangere Frau auf einem sinkenden Schiff... Da läuft einem ja ein Schauer über den Rücken bei dem Gedanken, ja, gell?";
			link.l1.go = "Mary_92";
		break;
		
		case "Mary_92":
			dialog.text = "Aber was hat sie in diesem Zustand auf diesem Schiff gemacht, "+pchar.name+"?! Man muss ja verrückt sein, um so etwas zu wagen, ja, gell?";
			link.l1 = "Diese Frage kann nur dein Vater beantworten – John, Jack, Jacob, Jasper, Jordan...";
			link.l1.go = "Mary_94";
		break;
		
		case "Mary_94":
			dialog.text = "Hast du beschlossen, dich an alle englischen Namen zu erinnern, die mit „J“ anfangen? Aurélie hat doch nur Geoffrey und John genannt, ja, gell?";
			link.l1 = "Vielleicht hat sie sich einfach nicht mehr an die anderen erinnert, so wie ich? Na ja, du weißt schon, das Alter und so...";
			link.l1.go = "Mary_95";
		break;
		
		case "Mary_95":
			dialog.text = ""+pchar.name+", du denkst...";
			link.l1 = "Ich würde mich jetzt nicht ganz auf ihr Gedächtnis verlassen, ja, gell? Aber selbst wenn es so ist, müssten wir nicht nur die kolonialen, sondern sogar die Flottenarchive von 1638 durchforsten, und das ist viel schwieriger: Die Informationen sind schließlich vertraulich, besonders wenn es um Offiziere geht. Und ich bezweifle stark, dass ein einfacher Matrose seine Frau an Bord hätte schmuggeln dürfen, ja, gell?";
			link.l1.go = "Mary_96";
		break;
		
		case "Mary_96":
			dialog.text = "Andererseits ist es viel einfacher, Informationen über einen Offizier zu finden als über einen gewöhnlichen Matrosen.";
			link.l1 = "Wenn man den Namen des Schiffs kennt. Oder seinen vollständigen Namen. Und nicht 'Jeffrey oder John oder, wenn’s hochkommt, Jack...'. Da hätten wir noch Glück, wenn das Schiff zur Marine gehörte. Bei Händlern sieht’s mit den Mannschaftslisten viel schlechter aus.";
			link.l1.go = "Mary_97";
		break;
		
		case "Mary_97":
			dialog.text = "Aber was sollen wir dann tun, "+pchar.name+"? Noch einmal mit Aurélie reden? Wir haben doch schon alles aus ihr herausgeholt, findest du nicht auch, ja, gell?";
			link.l1 = "Nicht mit Aurélie. Mit Donald.";
			link.l1.go = "Mary_98";
		break;
		
		case "Mary_98":
			dialog.text = "Und wie soll er uns helfen? Er hat doch gesagt, dass er 1638 nicht mal in der Nähe der Insel der Gerechtigkeit war, ja, gell?";
			link.l1 = "Aber die anderen Narwale waren doch hier, ja, gell?";
			link.l1.go = "Mary_99";
		break;
		
		case "Mary_99":
			dialog.text = "Ich verstehe nicht ganz, worauf du hinauswillst.";
			link.l1 = "Du wirst schon sehen, Liebes, du wirst sehen. Da gibt es noch einen Faden, an dem wir ziehen können. Komm.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_17");
		break;
		
		case "Grinspy_31":
			dialog.text = "Ah, wieder ihr! Na, wie laufen eure Nachforschungen?";
			link.l1 = "Hallo, "+npchar.name+". Könnte besser sein – im Moment irren wir noch wie in dieser Höhle voller Geheimnisse und Rätsel umher. Aber ich spüre, dass der Ausgang schon ganz nah ist.";
			link.l1.go = "Grinspy_32";
			link.l2 = "Und dir auch hallo, "+npchar.name+". Besser, als ich mir am Anfang hätte vorstellen können. Die Lage... ist gar nicht so hoffnungslos, ja, gell?";
			link.l2.go = "Grinspy_33";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_32":
			dialog.text = "Freut mich zu hören. Ehrlich. Aber ihr beide wollt doch schon wieder etwas von mir, ja, gell? Was habt ihr herausgefunden?";
			link.l1 = "Mary wurde hier, auf der Insel, im Juni 1638 geboren. Ihre Mutter, Teresa, starb gleich nach der Geburt. Ihr Vater – jemand mit dem Nachnamen Casper – war wenige Tage nach Marys Geburt wie vom Erdboden verschluckt. Über ihn wissen wir nichts, außer dass sein Name mit 'J.' anfängt. Es gibt die Vermutung, dass er nicht den Krabben im seichten Wasser zum Opfer fiel, sondern die Insel auf einer der Schaluppen der Schmuggler verlassen hat...";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_33":
			dialog.text = "Schön, das zu hören. Ehrlich. Aber ihr beide wollt doch wieder etwas von mir, oder? Was habt ihr herausgefunden?";
			link.l1 = "Mary wurde hier auf der Insel im Juni 1638 geboren. Ihre Mutter, Teresa, starb gleich nach der Geburt. Der Vater – ein gewisser Casper – war wenige Tage nach Marys Geburt wie vom Erdboden verschluckt. Über ihn wissen wir nichts, außer dass sein Name mit 'J.' beginnt. Manche meinen, er sei nicht den Krabben im seichten Wasser zum Opfer gefallen, sondern habe die Insel auf einer der Schaluppen der Schmuggler verlassen...";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_34":
			dialog.text = "Und er hat seine Tochter einfach im Stich gelassen? Seltsame Entscheidung.";
			link.l1 = "So ist es. Aber niemand außer eben diesem Mister J. kann das erklären.";
			link.l1.go = "Grinspy_35";
		break;
		
		case "Grinspy_35":
			dialog.text = "Und ihr glaubt, dass er noch lebt? Und deshalb sucht ihr ihn, ja, gell?";
			link.l1 = "Nicht nur deswegen. Wir wollen wissen, wer er war, wie er gelebt hat. Für Mary ist das sehr wichtig, ja, gell?";
			link.l1.go = "Grinspy_36";
		break;
		
		case "Grinspy_36":
			dialog.text = "Hm, ich verstehe. Und es tut mir leid, dass ich euch eigentlich nicht wirklich helfen kann...";
			link.l1 = "Eigentlich kannst du das. Sag mal, die Narwale führen doch irgendwie Buch über die Schiffe, die an der Insel untergegangen sind, ja, gell?";
			link.l1.go = "Grinspy_37";
		break;
		
		case "Grinspy_37":
			dialog.text = "Ich verstehe nicht ganz, was du meinst, "+pchar.name+".";
			link.l1 = "Grinspie, Grinspie... Vergiss nicht, dass du deinen Hintern immer noch nur dank mir in diesem Sessel wärmst. Also sei so nett – strapazier nicht meine Geduld.";
			link.l1.go = "Grinspy_38";
			link.l2 = "Bist dir sicher, dass du das verstehst, Donald. Und im Namen unserer Freundschaft wirst du doch nicht herumdrucksen, ja, gell?";
			link.l2.go = "Grinspy_39";
		break;
		
		case "Grinspy_38":
			dialog.text = "Hm-m...";
			link.l1 = "An das äußere Ring treiben immer wieder Schiffe heran. Manche sinken sofort, andere bleiben eine Weile über Wasser – dann werden sie durchsucht und alles Wertvolle wird abgenommen. Was die Rivadors angeht, weiß ich nicht, aber ich bezweifle, dass die Narwale um jeden einzelnen Fund an Bord kämpfen – wahrscheinlich werfen sie alles in einen gemeinsamen Topf, dann wird alles inventarisiert, und erst danach teilen sie die Beute auf.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Grinspy_39":
			dialog.text = "Hm-m...";
			link.l1 = "An das äußere Ring treiben immer wieder Schiffe. Manche sinken sofort, andere bleiben eine Weile über Wasser – die werden durchsucht, und alles Wertvolle wird abgenommen. Was die Rivadors angeht, weiß ich nicht, aber ich bezweifle, dass die Narwale um jedes gefundene Kleinod an Bord kämpfen – wahrscheinlich werfen sie alles in einen gemeinsamen Topf, dann wird alles inventarisiert, und erst danach teilen sie die Beute auf.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "Grinspy_40":
			dialog.text = "Du bist nicht dumm, "+pchar.name+". Im Gegensatz zu vielen hier. Ja, so läuft das ungefähr ab. Mir persönlich ist diese Schreiberei zuwider, aber das wurde schon zu Zeiten von Alan Milrow und denen, die den 'Narwal'-Klan vor ihm geführt haben, gemacht. Wir führen solche Aufzeichnungen – und mehr noch: Wir erfassen sogar die Schiffe, zu denen zuerst die Rivados oder Piraten gelangt sind. Aber in solchen Fällen wissen wir natürlich nicht, wer und was an Bord war...";
			link.l1 = "Da Marys Eltern nach dem Schiffsbruch auf der 'Ceres Smithy' abgesetzt wurden, haben wohl die Narwale ihr Schiff gefunden. Das heißt, es müsste einen entsprechenden Eintrag geben.";
			link.l1.go = "Grinspy_41";
		break;
		
		case "Grinspy_41":
			dialog.text = "Vielleicht ist es so. Genau sagen kann ich es nicht. Und ich werde es auch nicht können.";
			link.l1 = "Jetzt verstehe ich nicht mehr, was du meinst, "+npchar.name+".";
			link.l1.go = "Grinspy_42";
		break;
		
		case "Grinspy_42":
			dialog.text = "Die Register der verlorenen Schiffe. Als Leighton Dexter nach Dodsons Abreise Admiral wurde, hat er uns diese Unterlagen weggenommen.";
			link.l1 = "Einfach so genommen und eingesteckt? Und du hast nichts dagegen gesagt?";
			link.l1.go = "Grinspy_43";
		break;
		
		case "Grinspy_43":
			dialog.text = "Also, erstens war er ziemlich höflich. Zweitens hat er versprochen, sie bald zurückzugeben. Und drittens... wozu zum Teufel brauche ich diese Zettel überhaupt, ja, gell?";
			link.l1 = "Gar nicht mal die nutzlosesten Aufzeichnungen, ja, gell?";
			link.l1.go = "Grinspy_44";
		break;
		
		case "Grinspy_44":
			dialog.text = "Ich sag doch, das ist einfach eine Tradition, die hauptsächlich dazu dient, dass sich die Mitglieder unseres Clans nicht gegenseitig wegen der Beute von den Schiffen die Kehle durchbeißen. Ein Schiff wird angespült, wir nehmen alles runter, was wir können, machen eine Liste, teilen manches auf, anderes verschwindet in unseren Laderäumen – das war’s auch schon. Warum soll ich die Schränke vollstopfen? Jetzt ist da ein bisschen Platz frei geworden – vielleicht sollte ich dem Admiral dafür sogar dankbar sein.";
			link.l1 = "Na gut, alles klar. Dann nehmen wir Kurs auf 'San Augustin'. Aber vielleicht schauen wir später noch bei dir vorbei, ja, gell? "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_18");
		break;
		
		case "WildRose_Dexter_1":
            dialog.text = "Ah, "+pchar.name+", komm rein, komm rein. Bist du wegen einer Sache bei mir, Freund, oder wolltest du einfach nur mal vorbeischauen?";
            link.l1 = "Diesmal geht es um etwas. Sagen wir mal, es ist persönlich, ja, gell?";
            link.l1.go = "WildRose_Dexter_2";
			DelLandQuestMark(npchar);
        break;

        case "WildRose_Dexter_2":
            dialog.text = "Und ziemlich wichtig für dich – so aufgeregt, wie du aussiehst.";
            link.l1 = "In der Tat? Eher müde, würde ich sagen. Ich musste in den letzten Tagen ganz schön durch deine Ländereien streifen. Die Gelenke machen sich schon bemerkbar – und ich war doch so naiv zu glauben, dass so etwas nur alten Knackern wie dir passiert.";
            link.l1.go = "WildRose_Dexter_3_1";
            link.l2 = "Ein bisschen aus der Puste bin ich – das ist alles. Ich sitze nämlich nicht nur im Sessel, weißt du. Aber dich, sehe ich, tragen die Beine ja gar nicht mehr, ha-ha-ha!";
            link.l2.go = "WildRose_Dexter_3_2";
        break;

        case "WildRose_Dexter_3_1":
            dialog.text = "Hast du dich mal gefragt, warum ich mit meinem Hintern an diesem Stuhl festgewachsen bin, hehe? Weißt du, die Sicht auf die Welt kann sich ziemlich ändern, wenn du begreifst, dass man Gesundheit nicht mal für all den Reichtum dieser Insel kaufen kann.";
            link.l1 = "Lustig – genau darüber wollte ich eigentlich mit dir sprechen.";
            link.l1.go = "WildRose_Dexter_4";
			AddCharacterExpToSkill(pchar, "Defence", 100);
        break;
		
		case "WildRose_Dexter_3_2":
            dialog.text = "Hast du dich je gefragt, warum ich mit meinem Hintern an diesem Stuhl festgewachsen bin, hehe? Weißt du, die Sicht auf die Welt kann sich ganz schön ändern, wenn du begreifst, dass du Gesundheit nicht mal für all den Reichtum dieser Insel kaufen kannst.";
            link.l1 = "Lustig – genau darüber wollte ich mit dir sprechen.";
            link.l1.go = "WildRose_Dexter_4";
			AddComplexSelfExpToScill(100, 100, 100, 100);
        break;

        case "WildRose_Dexter_4":
            dialog.text = "Um meine Gesundheit?";
            link.l1 = "Nein, über die Schätze der Insel. Oder, um genauer zu sein, über deren Verzeichnisse. Und ganz genau genommen, über die Logbücher, in denen diese Verzeichnisse stehen.";
            link.l1.go = "WildRose_Dexter_5";
        break;

        case "WildRose_Dexter_5":
            dialog.text = "Kch-kch... "+pchar.name+", ich verstehe nicht ganz, worüber du sprichst, ja, gell?";
            link.l1 = "Vor nicht allzu langer Zeit hast du den Narwalen die Logbücher der am Eiland gestrandeten Schiffe abgenommen...";
            link.l1.go = "WildRose_Dexter_6";
        break;

        case "WildRose_Dexter_6":
            dialog.text = "Also, und dieser Trottel Grinspie hat dich tatsächlich hinter ihnen hergeschickt? Was für ein Frechdachs, ja, gell?";
            link.l1 = "Keineswegs, "+npchar.name+", Donald hat damit nichts zu tun. Ich bin mit dieser Frage zu ihm gekommen, und er hat mich an dich verwiesen. Aber ehrlich gesagt, deine Reaktion hat mich amüsiert, ja, gell? Verrätst du mir, wozu du die Narwal-Aufzeichnungen brauchst?";
            link.l1.go = "WildRose_Dexter_7";
        break;

        case "WildRose_Dexter_7":
            dialog.text = "Warum erzählst du es nicht einfach? Mir, wie du dir denken kannst, sind die Schiffe selbst egal. Und auf die Schätze, mit denen ihre Laderäume vollgestopft sind, gebe ich im Grunde auch nichts. Es reicht für alle, solange man nicht gierig wird – so sehe ich das. Was mich wirklich interessiert, ist das Waffenzeug: Musketen, Säbel... und am Ende auch Kanonen. Ja, diese Schlauen nehmen manchmal sogar die mit. Den hohlen Schwarzen fehlt dazu der Verstand, aber die Narwale...";
            link.l1 = "Und du hast beschlossen herauszufinden, wie bereit die Leute von Greenspy für eine neue Runde des Widerstands sind, ja, gell?";
            link.l1.go = "WildRose_Dexter_8";
        break;

        case "WildRose_Dexter_8":
            dialog.text = "Und ihm zu verstehen geben, dass ich und meine Leute wachsam sind. Die Botschaft ist ziemlich eindeutig, aber angesichts des Zirkus, den Donald mit diesen Übungen veranstaltet hat, kann ich mir gut vorstellen, dass er beschlossen hat, ich hätte es auf sein Geld abgesehen.";
            link.l1 = "Ja, gell? Ich sehe schon, die Lage entwickelt sich wohl nicht ganz so, wie du es dir vorgestellt hast. Und was ist mit Rivadós? Macht dir Schwarzer Eddie keine Schwierigkeiten?";
            link.l1.go = "WildRose_Dexter_9";
        break;

        case "WildRose_Dexter_9":
            dialog.text = "Rivados, Eddie... Widerliche Schwarze – kein Wunder, dass der Hai sie so gehasst hat, ja, gell?";
            link.l1 = "Heißt also, es gefällt dir.";
            link.l1.go = "WildRose_Dexter_10";
        break;

        case "WildRose_Dexter_10":
            dialog.text = "Genau das ist es ja, verdammt noch mal! Die Schwarzen sind still geworden, hocken auf ihren Schiffen...";
            link.l1 = "Und was zum Teufel passt dir dann nicht, "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_11";
        break;

        case "WildRose_Dexter_11":
            dialog.text = "Wie soll ich dir das nur erklären, "+pchar.name+"... Siehst du, das ist wie der Wind auf offener See. Mal ist er schwach, mal stark, und manchmal bricht sogar ein Sturm los. Aber so oder so treibt der Wind das Schiff voran, und ein guter Kapitän weiß, ihn zu bändigen.";
            link.l1 = "Eine leichte Brise ist immer besser als ein wilder Sturm.";
            link.l1.go = "WildRose_Dexter_12";
        break;

        case "WildRose_Dexter_12":
            dialog.text = "Ja, gell?   Aber manchmal gibt es einfach gar keinen Wind. Flaute – und dagegen kann kein einziger Steuermann etwas ausrichten. Du sitzt einfach auf dem Achterdeck, starrst aufs Wasser und fragst dich, was zum Teufel wohl als Nächstes passiert. Mit Eddie und seinem Kumpel Chimiset ist es genau dasselbe – die planen irgendwas, das spüre ich mit jeder Faser, und das kann nichts Gutes bedeuten, beim Donner, ich schwör’s!";
            link.l1 = "Vielleicht solltest du mal deinen Hintern aus dem Sessel heben und mit Edward unter vier Augen reden. Oder noch besser – ihr trefft euch zu dritt mit Donald und besprecht alles offen. Das ist allemal besser, als die Insel wieder im Blut zu ertränken. Aber na gut... Kehren wir zurück zu dem, weshalb ich gekommen bin.";
            link.l1.go = "WildRose_Dexter_13";
        break;

        case "WildRose_Dexter_13":
            dialog.text = "Also interessierst du dich für die Schätze der Narwale, ja, gell? Was willst du dort finden?";
            link.l1 = "Mich interessieren die Listen der hier gesunkenen Schiffe. Genauer gesagt – für das Jahr 1638. Es ist nämlich so, dass wir versuchen, Informationen über Marys Eltern zu finden. Mit der Mutter ist soweit alles mehr oder weniger klar – aber über den Vater kann man das nicht sagen. Die Angaben zu ihm sind ziemlich vage, wir kennen nicht einmal seinen Namen, und wenn wir uns an irgendetwas festhalten können, dann ist es der Name des Schiffs, das im Juni 1638 am äußeren Ring zerschellt ist...";
            link.l1.go = "WildRose_Dexter_14";
        break;

        case "WildRose_Dexter_14":
            dialog.text = "Das ist eine ehrenwerte Sache – ich selbst habe mir früher oft den Kopf darüber zerbrochen, wer wohl mein eigener Vater war. Aber helfen kann ich euch leider nicht.";
            link.l1 = "Und warum denn, wenn ich fragen darf?";
            link.l1.go = "WildRose_Dexter_15";
        break;

        case "WildRose_Dexter_15":
            dialog.text = "Vor dir gibt es keine Geheimnisse, "+pchar.name+". Es geht gar nicht um mich, sondern um Donald – er hat mir nur Unterlagen ab 1651 gegeben. Ich habe gefragt, was mit älteren Aufzeichnungen ist, wenigstens aus dem Jahrzehnt davor – und bekam zur Antwort, dass es keine weiteren Papiere gibt. Das sei alles, was ihm in dieser Hinsicht von Alan Milrow vererbt wurde – so hat er gesagt.";
            link.l1 = "Ich glaube nicht, dass er einen Grund hatte zu lügen.";
            link.l1.go = "WildRose_Dexter_16";
        break;

        case "WildRose_Dexter_16":
            dialog.text = "Ich denke genauso, Freund. Wenn man bedenkt, dass er mir die neuen Aufzeichnungen ohne jede Frage gegeben hat. Außerdem hatte ich das Gefühl, dass er sogar irgendwie froh war, diesen Kram loszuwerden... Wer weiß, vielleicht hat Milrow einfach nur die Papiere der vergangenen Jahrzehnte entsorgt... Verbrannt, oder vielleicht...";
            link.l1 = "Nein, das kann nicht sein.";
            link.l1.go = "WildRose_Dexter_16_Add";
        break;

        case "WildRose_Dexter_16_Add":
            StartInstantDialog("Mary", "WildRose_Dexter_17", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_17":
            dialog.text = "Nein, das kann nicht sein. Alan würde so etwas nie tun.";
            link.l1 = "Warum bist du dir da so sicher, ja, gell? "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_17_1";
            link.l2 = "Ich dachte immer, er war eher für Messer und Axt zu haben als für all diesen Papierkram. Ich bin überrascht, dass er überhaupt lesen konnte.";
            link.l2.go = "WildRose_Dexter_17_2";
        break;

        case "WildRose_Dexter_17_1":
            dialog.text = "Er war sehr sorgfältig mit allen Aufzeichnungen, die die Insel betrafen. Er hielt sie für einen Teil ihrer Geschichte. Und Geschichte – nicht nur die dieses Ortes – war Alans wahre Leidenschaft, ja, gell? Er studierte alle historischen Dokumente und Bücher, die er finden konnte... Manchmal dachte ich, er wäre ein viel besserer Gelehrter als ein Haudegen – einmal habe ich ihm das sogar gesagt.";
            link.l1 = "...";
            link.l1.go = "WildRose_Dexter_18";
        break;

        case "WildRose_Dexter_17_2":
            dialog.text = "Er war sehr sorgfältig mit allen Aufzeichnungen, die die Insel betrafen. Er betrachtete sie als Teil ihrer Geschichte. Und Geschichte, nicht nur von diesem Ort, war Alans wahre Leidenschaft, ja, gell? Er hat alle historischen Dokumente und Bücher studiert, die er finden konnte... Manchmal dachte ich, er wäre ein viel besserer Gelehrter geworden als ein Haudegen – einmal habe ich ihm das sogar gesagt.";
            link.l1 = "Vielleicht hätte er wirklich lieber zu Brille, Papier und Feder als zu Degen und Pistole greifen sollen – dann würde er vielleicht immer noch auf den morschen Planken dieser Schiffe herumstapfen. Aber wenn Milrow so ein Liebhaber von Archivmaterialien war, wo hat er dann all diese Aufzeichnungen gelassen? Sagen wir, ein Blatt Papier hätte er aus Versehen mit Tinte bekleckern können – aber es waren doch Dutzende, wenn nicht Hunderte, oder?";
            link.l1.go = "WildRose_Dexter_18";
        break;

        case "WildRose_Dexter_18":
            dialog.text = "Ich weiß nur, dass er solche Dokumente wie seinen Augapfel gehütet hat, ja, gell? Vielleicht hat sie jemand gestohlen, oder er hat sie selbst jemandem gegeben...";
            link.l1 = "Geklaut?   Wer könnte wohl Interesse an Informationen über längst ausgeschlachtete Schiffe vom Achterdeck bis zum Kiel haben?   Verschenkt – das klingt schon wahrscheinlicher, aber nur an wen und warum?";
            link.l1.go = "WildRose_Dexter_19_Add";
        break;

        case "WildRose_Dexter_19_Add":
            StartInstantDialogNoType("Dexter", "WildRose_Dexter_20", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_20":
            dialog.text = "Irgendeinem anderen Geschichtsfan, haha! Ich stimme Charles zu – ich habe keine Ahnung, wem diese alten Kritzeleien sonst noch nützlich sein könnten, ja, gell?";
            link.l1 = "Jemand hat sie aber doch gebraucht. Da muss ich mir wohl ein paar Gedanken dazu machen, ja, gell? "+npchar.name+", wir wollen dich nicht länger aufhalten. Wir sehen uns noch, ja, gell?";
            link.l1.go = "Exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19");
        break;
		
		case "WildRose_Betancur_1":
			dialog.text = ""+pchar.name+", freut mich, dich wiederzusehen. Wie läuft es mit Mary bei euch?";
			link.l1 = "Und wir freuen uns, dich zu sehen, "+npchar.name+". Wie es bei uns weitergeht – das hängt jetzt von dir ab, ja, gell?";
			link.l1.go = "WildRose_Betancur_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Betancur_2":
			dialog.text = "Ein ziemlich faszinierender Gesprächsbeginn, das muss ich zugeben. Und ein wenig beängstigend, wenn man eure Gesichtsausdrücke betrachtet.";
			link.l1 = "Erschrick nicht, "+npchar.name+", denn du bist ja nicht schuld daran. Wir sind einfach ein bisschen müde vom Herumrennen auf diesen knarrenden Schiffswracks. Und heute ist es auch ziemlich schwül, findest du nicht, ja, gell?";
			link.l1.go = "WildRose_Betancur_3_1";
			link.l2 = "Diese Hitze gibt uns wirklich keine Kraft, ja, gell? Außerdem mussten wir auf der Insel herumrennen, während wir dich gesucht haben – wir brauchen deine Hilfe.";
			link.l2.go = "WildRose_Betancur_3_2";
		break;

		case "WildRose_Betancur_3_1":
			dialog.text = "Ähm, ja, eine leichte Brise käme jetzt wirklich gelegen. Also, was kann ich für euch tun?";
			link.l1 = "Siehst du, Mary und ich haben eine Nachforschung begonnen, um Licht in die Ereignisse von vor zwanzig Jahren zu bringen.";
			link.l1.go = "WildRose_Betancur_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Betancur_3_2":
			dialog.text = "Ähm, ja, eine leichte Brise käme jetzt wirklich gelegen. Also, was kann ich für euch tun, ja, gell?";
			link.l1 = "Weißt du, Mary und ich haben eine Untersuchung gestartet, um Licht in die Ereignisse von vor zwanzig Jahren zu bringen.";
			link.l1.go = "WildRose_Betancur_4";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Betancur_4":
			dialog.text = "Klingt spannend.   Und worum geht es dabei?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_4_add";
		break;
		
		case "WildRose_Betancur_4_add":
			StartInstantDialog("Mary", "WildRose_Betancur_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_5":
			dialog.text = "Meine Eltern, Antonio. Charles und ich versuchen herauszufinden, wer sie waren. Und was mit ihnen geschehen ist. Meine Mutter ist bei der Geburt gestorben, das haben wir schon herausgefunden. Aber mit meinem Vater ist es nicht so einfach...";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_5_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_6":
			dialog.text = "In welchem Jahr bist du geboren, sag mal...";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_6_add":
			StartInstantDialog("Mary", "WildRose_Betancur_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_7":
			dialog.text = "Im Jahr 1638. Im Juni.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_7_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_8":
			dialog.text = "Damals war ich erst zwölf Jahre alt, Mary. Ich erinnere mich nicht besonders gut an diese Zeit. Einige Erinnerungsfetzen tauchen natürlich jetzt in meinem Kopf auf, aber sie zu einem vollständigen Bild zusammenzusetzen, ist ehrlich gesagt ziemlich schwierig. Tut mir leid, aber ich glaube nicht, dass ich dir helfen kann...";
			link.l1 = "Wir brauchen von dir nicht ganz das, Antonio. Aber falls dir noch etwas von dem Tag einfällt, an dem Mary zur Welt kam, wären wir dir wirklich sehr dankbar, ja, gell?";
			link.l1.go = "WildRose_Betancur_9";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_9":
			dialog.text = "Womit kann ich euch dann helfen, "+pchar.name+"?";
			link.l1 = "Du hast mir erzählt, dass du dich für Geschichte interessierst. Sowohl für die Weltgeschichte im Allgemeinen als auch besonders für die Geschichte der Insel, ja, gell?";
			link.l1.go = "WildRose_Betancur_10";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;

		case "WildRose_Betancur_10":
			dialog.text = "Das stimmt. Ich habe alle möglichen Bücher gelesen, habe jedes Manuskript studiert, das ich nur auftreiben konnte...";
			link.l1 = "Es geht genau um die Manuskripte. Außer dir gab es auf der Insel nur einen Menschen, der sich genauso sehr für Geschichte begeisterte wie du...";
			link.l1.go = "WildRose_Betancur_12";
		break;

		case "WildRose_Betancur_12":
			dialog.text = "Alan Milrow. Ja, wir haben darüber gesprochen, als er nicht gerade damit beschäftigt war, Pläne zur Vernichtung der Rivadors und später auch der Piraten zu schmieden. Er war ein kluger Kerl, mit wirklich außergewöhnlichen Talenten, ja, gell?";
			link.l1 = "Ich habe keinen Zweifel – der Kerl war wirklich was Besonderes. Er hatte etwas, das uns helfen könnte. Und das ist für niemanden auf der Insel der Gerechtigkeit von praktischem Wert, außer für euch beide. Es sind die Schiffsregister der Schiffe, die an der Insel zerschellt sind, mit Beschreibungen der geborgenen Ladungen und Wertgegenstände und vielleicht sogar den Namen der Passagiere...";
			link.l1.go = "WildRose_Betancur_13";
		break;

		case "WildRose_Betancur_13":
			dialog.text = "So ist es.";
			link.l1 = "Also hast du sie gesehen, ja, gell?";
			link.l1.go = "WildRose_Betancur_14";
		break;

		case "WildRose_Betancur_14":
			dialog.text = "Ich habe sie nicht nur gesehen – ich habe die darin enthaltenen Informationen in meine Aufzeichnungen übernommen. In einem unserer Gespräche erwähnte er zufällig, dass es diese Logbücher gibt, und ich bat ihn, sie mir zum Studium zu überlassen – ich versuche nämlich so etwas wie eine Chronik der Insel der Gerechtigkeit zu erstellen, und diese Aufzeichnungen waren dabei äußerst hilfreich. Alan war begeistert von meiner Idee, die Geschichte dieses Ortes aufzuschreiben. Allerdings hat er mir nicht alle Unterlagen überlassen – die Einträge aus den 1650er Jahren behielt er für sich. Aber fürs Erste reichte mir der Rest.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_14_add";
		break;
		
		case "WildRose_Betancur_14_add":
			StartInstantDialog("Mary", "WildRose_Betancur_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_15":
			dialog.text = "Da gibt es doch Aufzeichnungen aus dem Jahr 1638, oder? Bitte, sag, dass es sie gibt, ja, gell?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_15_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_15_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_16":
			dialog.text = "Ich habe einen ganzen Stapel von diesen Logbüchern – und zwar seit 1620. Genau damals, sagt Alan, hat man angefangen, diese Aufzeichnungen zu führen. Und ja, das Jahr 1638 ist auch dabei, Mary.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_16_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_16_add":
			StartInstantDialog("Mary", "WildRose_Betancur_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_17":
			dialog.text = "Lässt du uns einen Blick darauf werfen?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_17_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_17_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_18":
			dialog.text = "Sieht nicht so aus, als hätte ich eine Wahl gehabt, haha! Einen Moment. Sie sind alle hier, in der unteren Schublade von diesem Schrank.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19_1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_19":
			dialog.text = "Bitte. Mach es dir bequem, schau dich um...";
			link.l1 = "Darum kümmern wir uns jetzt.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_20");
			AddQuestRecordInfo("WildRose_Records", "1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;
		
		case "WildRose_Mary_101":
			dialog.text = "Hier, "+pchar.name+", schau mal, ja, gell! Joshua und Teresa Casper! Ich kann’s kaum fassen – wir haben es geschafft, geschafft, ja, gell! Und der Name des Schiffs – ‚Wrangler‘! Jetzt können wir alles über meinen Vater herausfinden – wer er war, wie er hierher gekommen ist…";
			link.l1 = "Ich fürchte, "+npchar.name+", du bist zu voreilig...   Das könnte sich als schwieriger erweisen, als es scheint.   Ein Schiff Seiner Majestät...   Wir müssen überlegen, wer uns helfen könnte, an Informationen aus den Archiven der Königlichen Flotte zu kommen...";
			link.l1.go = "WildRose_Mary_102";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Mary_102":
			dialog.text = "Lass uns nachdenken! Wir überlegen und bekommen es, "+pchar.name+"! Das Schwierigste liegt schon hinter uns, ja, gell!";
			link.l1 = "Vielleicht macht es auch Sinn, mit den Herren Young und Friddick zu sprechen. Allerdings kann ich mich nicht erinnern, dass es solche Leute auf der Insel gibt.";
			link.l1.go = "WildRose_Betancur_20_add";
		break;
		
		case "WildRose_Betancur_20_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "Weil es sie hier nicht gibt, "+pchar.name+". Diese beiden sind in der darauffolgenden Nacht gestorben, nachdem sie zusammen mit den Caspers gerettet wurden, ja, gell?";
			link.l1 = "Interessant.   Eine schwangere Frau hat noch eine Woche überlebt, aber zwei Matrosen von der Royal Navy sind plötzlich gestorben...";
			link.l1.go = "WildRose_Betancur_22";
		break;

		case "WildRose_Betancur_22":
			dialog.text = "Sie waren sowieso schon schlimm, wenn ich mich recht erinnere. Jetzt ist es mir wieder eingefallen, "+pchar.name+" - Ich war nämlich ganz in der Nähe der 'Ceres Smithy', als sie an Bord gebracht wurden... Ja, ich war auf der 'Esmeralda' – zusammen mit Aurélie Bertin, glaube ich. Und da war auch noch Chimisette – der Schamane dieser schwarzen Heiden, der aus irgendeinem Grund im Laden auftauchte. Zuerst dachte ich, die beiden Matrosen wären schon tot – aber gestorben sind sie erst einen Tag später...";
			link.l1 = "Nun, da lässt sich wohl nichts machen. Aber wir haben trotzdem schon einiges herausgefunden. Danke dir für deine Hilfe, Antonio.";
			link.l1.go = "WildRose_Betancur_23";
		break;

		case "WildRose_Betancur_23":
			dialog.text = "Ich habe damit nichts zu tun, "+pchar.name+". Das ist alles Alan zu verdanken, ja, gell? Kaum einer von diesen Kürassieren hätte den wahren Wert dieser Aufzeichnungen erkannt. Gerade durch solche Dokumente wird Geschichte schließlich wieder lebendig!";
			link.l1 = "Ich hoffe, Mary und ich werden eines Tages deine Chroniken lesen, Freund. Hier, nimm das Logbuch, verlier es nicht. Nun, wir müssen los. Vielleicht sehen wir uns ja wieder, Kumpel.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_21");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "Weil es die hier nicht gibt, "+pchar.name+". Diese beiden sind in der darauffolgenden Nacht gestorben, nachdem sie zusammen mit den Caspers gerettet wurden, ja, gell?";
			link.l1 = "Interessant.   Eine schwangere Frau hat noch eine Woche überlebt, aber zwei Matrosen von der Royal Navy sind plötzlich verstorben...";
			link.l1.go = "WildRose_Betancur_22";
		break;
		
		case "WildRose_Chimiset_21":
			dialog.text = "Schön, dich wiederzusehen, mein Freund. Was führt dich zu mir?";
			link.l1 = "Mit einer Bitte, "+npchar.name+"... Besser gesagt, mit einer Frage.";
			link.l1.go = "WildRose_Chimiset_22";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_22":
			dialog.text = "Stell deine Frage. Oder sag, was du möchtest. Ich tue alles, was ich kann, um dir zu helfen.";
			link.l1 = "Na gut.   Wie lange lebst du schon auf der Insel?";
			link.l1.go = "WildRose_Chimiset_23";
		break;

		case "WildRose_Chimiset_23":
			dialog.text = "Jahrzehnte, mein Freund – viele, viele Jahre. Ich kam hierher als Kind, aber schon klug genug, um alles zu begreifen – an Bord eines Sklavenschiffs. Meine Geschichte unterscheidet sich kaum von den vielen, die du hier gehört hast. Ein Sturm, ein Schiffsbruch... Der englische Galeone, in dessen Laderaum ich eingesperrt war, schaffte es nicht einmal bis zum äußeren Ring – er zerbrach in zwei Hälften, nachdem eine Welle ihn auf eines der Riffe schleuderte.";
			link.l1 = "Wie hast du denn überlebt? Die Riffe sind doch ziemlich weit vom äußeren Ring entfernt, und von dort durch Sturmwellen zu schwimmen ist, ehrlich gesagt, alles andere als einfach...";
			link.l1.go = "WildRose_Chimiset_24";
		break;

		case "WildRose_Chimiset_24":
			dialog.text = "Die Götter waren in jener Nacht auf meiner Seite. Es gelang mir, mich von den Fesseln zu befreien und mich an einem Stück festzuhalten, das einst ein Beiboot gewesen war. Bei mir war ein Stammesgenosse, Asana – gemeinsam kämpften wir gegen die Wellen, bis wir vor Erschöpfung das Bewusstsein verloren.";
			link.l1 = "Hat es euch an eines der Schiffe verschlagen?";
			link.l1.go = "WildRose_Chimiset_25";
		break;

		case "WildRose_Chimiset_25":
			dialog.text = "Ja, wir krochen in ein Loch im Laderaum... Dort verlor ich erneut das Bewusstsein, so schwach war ich. Ich kam erst wieder zu mir, als Asana zu schreien begann – er wurde von einer riesigen Krabbe zerfetzt, die sich ebenfalls auf das Wrack geschleppt hatte, auf dem wir gestrandet waren. Und ich sah zu und wusste, dass ich der Nächste sein würde – gelähmt vor Angst und Schwäche konnte ich mich keinen Zentimeter rühren.";
			link.l1 = "Du hättest versuchen können, deinem Freund zu helfen. Aber dann würden wir jetzt nicht miteinander reden, ja, gell? Wie hast du dich denn gerettet?";
			link.l1.go = "WildRose_Chimiset_26_1";
			link.l2 = "Du hast Glück gehabt, dass er nicht mit dir angefangen hat, ja, gell? "+npchar.name+". Wie hast du dich denn gerettet – bist du einfach wieder ins Wasser gesprungen und davongeschwommen?";
			link.l2.go = "WildRose_Chimiset_26_2";
		break;

		case "WildRose_Chimiset_26_1":
			dialog.text = "Die Schreie von Asana wurden von einigen Rivadors gehört, die nach dem letzten Sturm auf der Jagd nach Fracht aus den Laderäumen der Schiffe waren. Sie umzingelten das Biest und töteten es. Für Asana gab es keine Rettung mehr, aber ich hatte viel mehr Glück. So bin ich hierher gekommen. Aber jetzt antworte du mir, mein Freund – warum wolltest du das alles wissen?";
			link.l1 = "Ehrlich gesagt, "+npchar.name+", ich wollte nicht wissen, wie du hierher gekommen bist, sondern wann das passiert ist.";
			link.l1.go = "WildRose_Chimiset_27";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_26_2":
			dialog.text = "Die Schreie von Asana wurden von einigen Rivadors gehört, die nach dem letzten Sturm auf Beutezug in den Laderäumen der Schiffe waren. Sie umzingelten das Biest und töteten es. Für Asana gab es keine Rettung mehr, aber ich hatte deutlich mehr Glück. So bin ich hierher gekommen. Aber jetzt antworte du mir, mein Freund – warum wolltest du das alles wissen?";
			link.l1 = "Ehrlich gesagt, "+npchar.name+", ich wollte nicht wissen, wie du hierher gekommen bist, sondern wann das passiert ist.";
			link.l1.go = "WildRose_Chimiset_27";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Chimiset_27":
			dialog.text = "Hm, nach eurem Kalender war das das Jahr 1623, Spätsommer – genauer kann ich es leider nicht sagen...";
			link.l1 = "Das ist auch gar nicht nötig. Also warst du im Jahr 1638 schon seit fünfzehn Jahren auf der Insel.";
			link.l1.go = "WildRose_Chimiset_28";
		break;

		case "WildRose_Chimiset_28":
			dialog.text = "Sieht ganz so aus, mein Freund.";
			link.l1 = "Im Juni jenes Jahres wurde durch einen Hurrikan die Brigg 'Wrangler', ein Schiff der Flotte Seiner Majestät Karl I., König von England, an den äußeren Ring gespült. Von der gesamten Besatzung überlebten nur vier – darunter Marys Eltern: Joshua und Teresa Casper.";
			link.l1.go = "WildRose_Chimiset_29";
		break;

		case "WildRose_Chimiset_29":
			dialog.text = "Ja, ich erinnere mich daran, mein Freund. Verschwommen, wie im Nebel, aber ich erinnere mich...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_29_add";
		break;
		
		case "WildRose_Chimiset_29_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_30":
			dialog.text = "Weißt du wirklich noch? Erzähl schon!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_30_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_30_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_31":
			dialog.text = "Viel kann ich nicht sagen. Vier Personen: ein Offizier, seine Frau und zwei Matrosen. Die Frau war schwanger, und diejenigen, die sie gerettet haben, dachten, sie würde die Nacht nicht überleben – aber sie war stark wie eine Löwin. Die beiden Matrosen hingegen verließen diese Welt schon weniger als einen Tag später... Ich habe sie gesehen: Sie waren schwach, ja, aber sie hatten trotzdem noch genug Lebenskraft in sich...";
			link.l1 = "Willst du damit sagen, dass sie getötet wurden?";
			link.l1.go = "WildRose_Chimiset_32";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_32":
			dialog.text = "Selbst wenn es so war, gab es dafür keine Zeugen, ebenso wenig wie Wunden an ihren Körpern, mein Freund...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_32_add";
		break;
		
		case "WildRose_Chimiset_32_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_33", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_33":
			dialog.text = "Hast du 'Offizier' gesagt, ja, gell?... War mein Vater wirklich ein Offizier?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_33_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_33_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_34":
			dialog.text = "Er trug eine Offiziersuniform – das ist wohl das Einzige, woran ich mich erinnere, wenn ich versuche, mich an sein Aussehen zu erinnern.";
			link.l1 = "Wenn er Offizier war, dann konnte er ja kaum etwas anderes tragen – sein Kleiderschrank war bestimmt nicht besonders abwechslungsreich... Vielleicht erinnerst du dich ja noch an ein paar weitere Einzelheiten, "+npchar.name+"? Besondere Merkmale... Sagen wir, eine Narbe im Gesicht oder eine andere Verletzung...";
			link.l1.go = "WildRose_Chimiset_35";
		break;
		
		case "WildRose_Chimiset_35":
			dialog.text = "Ich erinnere mich an nichts Besonderes, mein Freund. Sein Gesicht ist fast aus meinem Gedächtnis verschwunden – es sind zwanzig Jahre vergangen... Aber seinen Blick – den erinnere ich mich sehr gut. Ich habe nur einmal mit diesem Mann gesprochen, aber der Ausdruck seiner grauen Augen – genau wie Marys – wird mir nie entfallen. In ihnen mischten sich Verzweiflung, Angst, wie bei einer gehetzten Antilope, und zugleich Wut und Entschlossenheit, die eines Löwen würdig sind...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_35_add";
		break;
		
		case "WildRose_Chimiset_35_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_36":
			dialog.text = "Hast du mit ihm gesprochen, ja, gell? Worüber?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_36_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_36_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_37":
			dialog.text = "Das geschah nur wenige Stunden vor deiner Geburt. Er kam hierher, auf die 'Protector', und verlangte, mich zu sprechen. Der Anführer der Rivadors, Mogedi, war von seiner Dreistigkeit beeindruckt – aber plötzlich wurde dieser Mann für mich interessant. Als er vor mir stand, fiel er auf die Knie und flehte mich an, seine Frau zu retten... Jemand hatte ihm in der kurzen Zeit, die sie hier waren, schon von mir erzählt. Ich willigte ein, obwohl Mogedi dagegen war...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_37_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_37_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_38":
			dialog.text = "Also bin ich dir mein Leben schuldig, ja, gell?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_38_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_38_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_39", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_39":
			dialog.text = "Es hat keinen Sinn zu lügen – wir haben es geschafft, zu deiner Mutter zu kommen, aber es war zu spät: Die Narwals weigerten sich, mich auf die 'Ceres Smithy' zu lassen. Deinem Vater gelang es, sie zu... überzeugen, aber die arme Theresa habe ich erst in ihrem letzten Atemzug gesehen. Sie hat dich noch zur Welt gebracht, und wäre ich früher gekommen, hätte ich ihr Leben vielleicht retten können, aber...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_39_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_39_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_40", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_40":
			dialog.text = "Mama ist gestorben, ja, gell?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_40_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_40_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_41", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_41":
			dialog.text = "Leider. Sie hat dich angesehen und ihren letzten Atemzug getan, aber davor, als hätte sie all ihre Kraft zusammengenommen, hat sie nach irgendeinem Rupert gerufen. Sie hat seinen Namen aus voller Kehle geschrien, als würde sie um Hilfe rufen – und ist gestorben.";
			link.l1 = "Ruperta? Nicht Joshua?";
			link.l1.go = "WildRose_Chimiset_42";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_42":
			dialog.text = "Während ich Ihnen das erzählte, mein Freund, habe ich diesen Moment noch einmal durchlebt. Ich werde das niemals vergessen – weder ihren Todesschrei noch ihr von Schmerz verzerrtes Gesicht. Und ja, das Letzte, was über ihre Lippen kam, war tatsächlich 'Rupert'.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_42_add";
		break;
		
		case "WildRose_Chimiset_42_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_43":
			dialog.text = "War sie schön, meine Mama? Kannst du beschreiben, wie sie ausgesehen hat, Chimisette?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_43_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_43_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_44", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_44":
			dialog.text = "Das ergibt keinen Sinn, Mary. Du musst nur in den Spiegel schauen – ihr seid euch wie ein Ei dem anderen ähnlich. Nur die Augen hast du von deinem Vater, ja, gell?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_44_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_44_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_45", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_45":
			dialog.text = "Und er, was ist mit ihm passiert? Wir haben herausgefunden, dass er ein paar Tage nach meiner Geburt wie vom Erdboden verschluckt war, ja, gell? Aber umgebracht haben sie ihn doch nicht, oder?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_45_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_45_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_46", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_46":
			dialog.text = "Als man ihm berichtete, dass Teresa im Sterben lag, geriet Joshua in rasende Wut – ich schwöre, selbst Löwen in der Savanne greifen ihre Beute nicht mit so viel Zorn an, wie dein Vater sich auf die Narwals stürzte, die mir den Weg zur Fregatte versperrten... Es brauchte ein halbes Dutzend Männer, um ihn zu bändigen – nachdem er zwei Krieger des Clans in voller Montur über Bord geworfen hatte.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_46_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_46_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_47", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_47":
			dialog.text = "Und was hast du mit ihm gemacht – sag schon, na los!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_47_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_47_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_48", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_48":
			dialog.text = "Er wurde in eine der Zellen auf der 'Tartarus' geworfen. Keiner wollte ihn richten – sie wollten erst, dass die Geschichte sich beruhigt... Fast alle hatten Mitleid mit ihm, aber nur wenige wollten mit so einem Menschen Seite an Seite leben. Nach ein paar Tagen war Joshua verschwunden – und zur selben Zeit verließen mehrere Boote von Schmugglern die Insel. In den Booten hat ihn niemand gesehen – das brachte die Gerüchte über seinen Tod in Umlauf.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_48_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_48_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_49", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_49":
			dialog.text = "Also glaubst du, dass er noch lebt, ja, gell?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_49_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_49_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_50", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_50":
			dialog.text = "Ich sage nur das, was euch sicher auch andere erzählen werden – seine Leiche hat niemand gefunden. Vielleicht hat er sich doch auf dem Grund eines der Boote versteckt, oder vielleicht hat man ihm in jener Zelle die Kehle durchgeschnitten und ihn den Krabben zum Fraß vorgeworfen...";
			link.l1 = "Die Tatsache, dass er genau mit dem Aufbruch dieser Händler verschwunden ist, spricht eher für Ersteres – solche Zufälle gibt es nicht. Und vielleicht hat er jemandem gegenüber seine Pläne angedeutet? Wenn er geflohen ist, dann hat er dabei sein neugeborenes Kind hiergelassen – was auf gewisse Weise nachvollziehbar ist, denn ein Säugling hätte die Überfahrt nach Kuba in einem wackeligen Boot wohl kaum überlebt... Aber er hatte mit Sicherheit vor, zurückzukehren.";
			link.l1.go = "WildRose_Chimiset_51";
		break;
		
		case "WildRose_Chimiset_51":
			dialog.text = "Das weiß ich nicht, mein Freund. Wenn Joshua Casper in jenen Tagen überhaupt mit jemandem gesprochen hat, dann wohl nur mit seinen Kerkermeistern – aber die sind schon längst nicht mehr auf dieser sündigen Welt. Ach ja, an einem der Tage kam Padre Domingo zu ihm – er war bei den Weißen der Priester, noch bevor Bruder Julian kam...";
			link.l1 = "Hat er etwa beichten wollen? Scheint so, als hätte er Angst gehabt, beim Ausbruch zu sterben.";
			link.l1.go = "WildRose_Chimiset_52";
		break;

		case "WildRose_Chimiset_52":
			dialog.text = "Ich kann kein Licht auf etwas werfen, das ich nicht weiß, mein Freund. Und Domingo kann euch auch nichts mehr erzählen – er ist schon seit etwa fünfzehn Jahren tot, ertrunken. Ob ihm jemand eins über den Kopf gezogen hat oder ob er sich einfach nur betrunken hat – das war nämlich ganz sein Ding...";
			link.l1 = "Aber vielleicht hat Domingo ein Tagebuch geführt... oder seinem Bruder Julian von diesem Gespräch mit Joshua erzählt, ja, gell?";
			link.l1.go = "WildRose_Chimiset_52_add";
		break;
		
		case "WildRose_Chimiset_52_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_53", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_53":
			dialog.text = "Ich muss mit ihm reden, "+pchar.name+", ja, gell? Und zwar so schnell wie möglich. Ich will nicht mal daran denken, aufs Schiff zurückzukehren, bevor wir das hier geklärt haben.";
			link.l1 = "Falls es da überhaupt noch etwas zu klären gibt. Julian weiß davon vielleicht gar nichts – aber wir werden es auf jeden Fall herausfinden. Danke dir, Chimisette.";
			link.l1.go = "WildRose_Chimiset_53_add";
		break;
		
		case "WildRose_Chimiset_53_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_54", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_54":
			dialog.text = "Ich stehe dir immer zur Verfügung, mein Freund. Aber erlaub mir, euch beiden einen Rat zu geben.";
			link.l1 = "Und was für einer?";
			link.l1.go = "WildRose_Chimiset_55";
		break;
		
		case "WildRose_Chimiset_55":
			dialog.text = "Wenn ihr auf der Jagd seid, verirrt euch nicht zu tief ins Dickicht – vielleicht findet ihr dann nicht mehr heraus, ja, gell?";
			link.l1 = "Das werden wir nicht vergessen, Schamane. Und jetzt – leb wohl.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_22");
		break;
		
		case "WildRose_Julian_1":
			dialog.text = "Seid gegrüßt im Schutz des Hauses Gottes, meine Kinder. Wollt ihr beichten oder einfach nur beten?";
			link.l1 = "Grüß Sie, Bruder Julian. Ich fürchte, das Aufzählen unserer Sünden würde zu viel Zeit in Anspruch nehmen – die wir leider nicht haben. Aber seien Sie versichert – wir, als gute Katholiken, besuchen in jedem Hafen die Kirche.";
			link.l1.go = "WildRose_Julian_2_1";
			link.l2 = "Sei gegrüßt, Bruder Julian. Mit einem Gebet zu unserem Herrn beginnen wir als gute Katholiken den Tag und beenden ihn ebenso, ja, gell?";
			link.l2.go = "WildRose_Julian_2_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Julian_2_1":
			dialog.text = "Gute Katholiken, die ohne Trauschein unter einem Dach leben... Das grenzt an Gotteslästerung, mein Sohn. Und das, erinnere ich dich, ist eine Todsünde!";
			link.l1 = "Steht denn nicht in der Schrift, dass die Liebe alle Sünden zudeckt?";
			link.l1.go = "WildRose_Julian_3";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Julian_2_2":
			dialog.text = "Gute Katholiken, die ohne Trauschein unter einem Dach leben... Das grenzt an Gotteslästerung, mein Sohn. Und das, erinnere ich dich, ist eine Todsünde!";
			link.l1 = "Steht denn nicht in der Schrift, dass die Liebe alle Sünden zudeckt, ja, gell?";
			link.l1.go = "WildRose_Julian_3";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_3":
			dialog.text = "Liebe besteht darin, dass wir nach seinen Geboten handeln – muss ich sie dir etwa in Erinnerung rufen, mein Sohn?";
			link.l1 = "Ein andermal vielleicht. Wir sind aus einem anderen Grund hier.";
			link.l1.go = "WildRose_Julian_4";
		break;

		case "WildRose_Julian_4":
			dialog.text = "Verirrte Seelen können immer noch auf den rechten Weg zurückfinden... Aber ich höre euch zu, meine Kinder.";
			link.l1 = "Wir haben uns tatsächlich ein wenig verirrt, Bruder Julian. In den Wirren der Vergangenheit. Und wir hoffen, dass es in eurer Macht steht, uns den Weg ins Licht zu zeigen.";
			link.l1.go = "WildRose_Julian_5";
		break;

		case "WildRose_Julian_5":
			dialog.text = "Sehr witzig, mein Sohn. Du solltest bedenken, dass nicht der Mensch zum Licht führt, sondern der Herr – und wenn du Ihm folgst, denke daran, dass unergründlich sind Seine Wege.";
			link.l1 = "Ich fasse mich kurz, Bruder Julian. Wir versuchen, alles Mögliche über Marys Eltern herauszufinden. Mit ihrer Mutter, Teresa, ist alles mehr oder weniger klar – sie kam zusammen mit ihrem Mann auf die Insel und starb eine Woche später bei der Geburt. Aber der Vater... Er verschwand ein paar Tage nach Marys Geburt und floh dabei von der 'Tartarus'. Gerüchten zufolge war der letzte Mensch, mit dem er hier gesprochen hat, Padre Domingo – Ihr Vorgänger.";
			link.l1.go = "WildRose_Julian_6";
		break;

		case "WildRose_Julian_6":
			dialog.text = "Dann seid ihr mehr als anderthalb Jahrzehnte zu spät, meine Kinder.";
			link.l1 = "Ja, wir wissen, dass der Padre schon vor einiger Zeit gestorben ist. Und damals, Bruder Julian, waren Sie noch viel zu jung, um auf der Insel im entsprechenden Amt zu sein, nicht wahr?";
			link.l1.go = "WildRose_Julian_7";
		break;

		case "WildRose_Julian_7":
			dialog.text = "Ich bin erst einige Jahre nach seinem Tod hierher gekommen. Es hat mich viel Mühe gekostet, hier auf diesem Schiff alles in Ordnung zu bringen, aber mit Gottes Hilfe habe ich es geschafft, mein Sohn.";
			link.l1 = "Als ihr euch hier umgesehen habt, habt ihr da vielleicht irgendwelche Aufzeichnungen von Padre Domingo gefunden, ja, gell?";
			link.l1.go = "WildRose_Julian_8";
		break;

		case "WildRose_Julian_8":
			dialog.text = "Meinen Sie etwas Bestimmtes, mein Sohn?";
			link.l1 = "Uns interessieren Tagebücher oder irgendwelche Aufzeichnungsbücher... Die Hoffnung auf ein Wunder ist gering, aber der Padre könnte den Inhalt dieses Gesprächs in einem seiner Einträge festgehalten haben. Wir vermuten, dass Marys Vater die Insel auf einem der Schmugglerbarkassen verlassen hat – vielleicht hat er dem Padre angedeutet, wohin er gehen wollte und wann er zurückkommt, um seine Tochter zu holen?";
			link.l1.go = "WildRose_Julian_9";
		break;

		case "WildRose_Julian_9":
			dialog.text = "Tagebücher oder etwas Ähnliches habe ich ganz sicher nicht gefunden, aber dafür allerlei Aufzeichnungen... Was die Führung kirchlicher Angelegenheiten angeht, war er ziemlich gewissenhaft – nicht jeder Diener des Herrn ist mit solcher Pedanterie gesegnet, ja, gell? Aber seine Papiere enthalten nur trockene Zahlen und Namen – und sonst nichts.";
			link.l1 = "Soweit wir herausfinden konnten, war es Joshua Casper – so hieß er –, der im Zorn über den Tod seiner Frau zwei Mitglieder des Narwal-Clans tötete, weil sie den Zauberer Rivados Chimiseta nicht zu Marys Mutter lassen wollten...";
			link.l1.go = "WildRose_Julian_10";
		break;

		case "WildRose_Julian_10":
			dialog.text = "Sie haben gehandelt wie Kinder der wahren Kirche! Für diesen Diener des Teufels weinen die Keller der Inquisition, ja, gell?";
			link.l1 = "Herrgott, ich glaube, er wäre entsetzt, wenn er wüsste, wie viele Menschen in seinem Namen gequält wurden. Casper hatte mehr Glück – er wurde in eine Zelle auf der 'Tartarus' geworfen, aber zu einem Urteil kam es nicht, ja, gell?";
			link.l1.go = "WildRose_Julian_11_1";
			link.l2 = "Ja, ja, ganz bestimmt. Casper wurde in eine der Zellen der ‚Tartarus‘ geworfen, aber ein Urteil wurde nicht gefällt – nicht alle verurteilten die Tat eines Mannes, der seine Frau verloren hatte.";
			link.l2.go = "WildRose_Julian_11_2";
		break;

		case "WildRose_Julian_11_1":
			dialog.text = "Und was dann – ist dieser Ketzer etwa geflohen?";
			link.l1 = "Weniger als eine Woche später war Joshua verschwunden. Und in der Nacht davor hat ihn Padre Domingo besucht. Da stellt sich die Frage – warum? Ein Protestant wie Casper würde sich wohl kaum einem katholischen Priester anvertrauen – was meint ihr?";
			link.l1.go = "WildRose_Julian_12";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_11_2":
			dialog.text = "Und was ist dann passiert – ist dieser Ketzer entkommen?";
			link.l1 = "Weniger als eine Woche später war Joshua verschwunden. Und in der Nacht davor hat ihn Pater Domingo besucht. Da stellt sich die Frage – warum? Ein Protestant, was Casper mit Sicherheit war, würde sich wohl kaum einem katholischen Priester anvertrauen – was meinst du?";
			link.l1.go = "WildRose_Julian_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Julian_12":
			dialog.text = "Es ist nie zu spät, zum wahren Glauben zu finden, mein Sohn. Aber du denkst richtig. Wenn er keine Beichte wollte, hat er vielleicht mit dem Padre über das Begräbnis seiner Frau gesprochen – vorausgesetzt natürlich, sie war Katholikin. Oder über die Taufe seiner Tochter, oder besser gesagt, über deren Ablehnung, denn Protestanten taufen keine Säuglinge, weil sie meinen, der Mensch müsse die Entscheidung zur Taufe selbst und bewusst treffen.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_12_add";
		break;
		
		case "WildRose_Julian_12_add":
			StartInstantDialog("Mary", "WildRose_Julian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_13":
			dialog.text = "Aber ich wurde getauft, Bruder Julian. Erik Udett hat mir davon erzählt.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_13_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_13_add":
			StartInstantDialog("Julian", "WildRose_Julian_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_14":
			dialog.text = "Das sind nur meine Vermutungen, meine Tochter. Die Wahrheit ist mir unbekannt. Der Herr öffnet uns die Augen nur für das, was wirklich wichtig und notwendig ist.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_14_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_14_add":
			StartInstantDialog("Mary", "WildRose_Julian_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_15":
			dialog.text = "Und für mich ist es genauso, ja, gell? Vielleicht ist in den Aufzeichnungen von Padre Domingo doch noch etwas, das Ihnen entgangen ist, Bruder Julian? Sie haben sie doch nur durchgeblättert, oder?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_15_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_15_add":
			StartInstantDialog("Julian", "WildRose_Julian_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_16":
			dialog.text = "Ich hatte dort nichts zu suchen, meine Tochter. Ich sehe, dass ihr euch schon lange und mit großer Sorgfalt dieser Sache widmet – der Herr führt euch auf diesem steinigen Weg. Wenn es dir bestimmt ist, das zu finden, wonach du suchst, so ist es sein Wille, und es steht mir nicht zu, mich ihm zu widersetzen. Ich kann euch die Aufzeichnungen von Domingo aus deinem Geburtsjahr geben, vielleicht findet ihr darin etwas Nützliches.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_16_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_16_add":
			StartInstantDialog("Mary", "WildRose_Julian_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_17":
			dialog.text = "Das wäre wirklich großzügig von Ihnen, Bruder Julian. Gibt es noch Aufzeichnungen aus dem Jahr 1638?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_17_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;
		
		case "WildRose_Julian_17_add":
			StartInstantDialog("Julian", "WildRose_Julian_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_18":
			dialog.text = "So, so... (pustet den Staub weg). Sieht so aus, als wäre es das. Das Buch der Aufzeichnungen aus dem Jahr 1638 nach Christi Geburt.";
			link.l1 = "Lassen Sie mich, Bruder Julian...";
			link.l1.go = "exit";
			AddQuestRecordInfo("WildRose_Records_2", "1");
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_23");
		break;
		
		case "WildRose_Mary_111":
			dialog.text = "Schau, "+pchar.name+": 3. August. An diesem Tag wurden Fabian und ich getauft. Geboren bin ich aber am 22. Juni. Aber über meinen Vater kein Wort, ja, gell?";
			link.l1 = "Alles ist genauso, wie Bruder Julian gesagt hat – trockene Zahlen und Namen. Interessant ist, dass Padre Domingo so eifrig war, dass er sogar Protestanten die letzte Ehre erwiesen hat – van Eckus, Young und Friddicks waren wohl kaum Katholiken, ja, gell?";
			link.l1.go = "WildRose_Mary_111_add";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Mary_111_add":
			StartInstantDialog("Julian", "WildRose_Mary_112", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_112":
			dialog.text = "Sie könnten sich durchaus dem wahren Glauben zugewandt haben, kurz bevor sie ins Reich Gottes eingetreten sind, mein Sohn.";
			link.l1 = "Natürlich, Bruder Julian – womit hätten sie sich sonst beschäftigen sollen? Besonders, wenn sie so gestorben sind wie Soren und Rojas – ich nehme an, das sind genau die Narwale, die Chimiseto den Weg versperrt haben.";
			link.l1.go = "WildRose_Mary_112_add";
		break;
		
		case "WildRose_Mary_112_add":
			StartInstantDialog("Mary", "WildRose_Mary_113", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_113":
			dialog.text = "Besser wäre es, wenn Padre Domingo die zweiten Namen ganz ausgeschrieben hätte, ja, gell? Was sollen denn diese „V.“ und „J.“ nach den Namen von meiner Mutter und mir bedeuten?";
			link.l1 = "Und wer ist dieser Fabian, der am selben Tag wie du getauft wurde, ja, gell?";
			link.l1.go = "WildRose_Mary_114";
		break;
		
		case "WildRose_Mary_114":
			dialog.text = "Der Sohn von Cécile Gallard. Oh, das fällt mir gerade erst wieder ein! Sie hat mich großgezogen, auch wenn sie nie besonders herzlich zu mir war. Wahrscheinlich, weil ich überlebt habe und Fabian nicht. Er ist ein paar Monate nach seiner Geburt gestorben, ja, gell?";
			link.l1 = "Vielleicht sollten wir mit ihr reden, wenn wir aus diesem Büchlein schon kaum etwas Nützliches erfahren haben – es sei denn, man zählt dein Geburts- und Taufdatum dazu, ja, gell?";
			link.l1.go = "WildRose_Mary_115";
		break;

		case "WildRose_Mary_115":
			dialog.text = "Sie ist nicht viel jünger als Aurélie, "+pchar.name+". Man kann nur hoffen, dass sie wenigstens noch alle Tassen im Schrank hat, ja, gell?   Aber was willst du denn eigentlich von ihr wissen?";
			link.l1 = "Nun, da sie deine Amme war, konnte sie vom Padre Domingo durchaus Einzelheiten über sein Gespräch mit Joshua erfahren haben. Wem hätte er das sonst erzählen sollen, wenn nicht ihr? Vielleicht noch Aurélie oder Erik. Aber ich glaube, aus der ersten haben wir alles herausgeholt, was ging, und der zweite wird niemandem mehr etwas sagen, ja, gell?";
			link.l1.go = "WildRose_Mary_115_add";
		break;
		
		case "WildRose_Mary_115_add":
			StartInstantDialog("Julian", "WildRose_Mary_116", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_116":
			dialog.text = "Diese gute Frau ist eine treue Kirchgängerin dieses Gotteshauses. Sie verpasst keine Messe und geht regelmäßig zur Beichte. Ich denke, sie kann euch wirklich helfen, meine Kinder.";
			link.l1 = "Vielen Dank, Vater. Lebt wohl.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_24");
		break;
		
		case "WildRose_Sesil_1":
			dialog.text = ""+GetFullName(pchar)+" und Mary Casper. Was für ein angenehmes Wiedersehen!";
			link.l1 = "Ganz meinerseits, "+npchar.name+". Wir sind eigentlich zu Ihnen gekommen. Wir würden gerne etwas mit Ihnen besprechen.";
			link.l1.go = "WildRose_Sesil_2";
			DelLandQuestMark(npchar);
			LAi_SetStayType(npchar);
		break;
		
		case "WildRose_Sesil_2":
			dialog.text = "Ach ja? Na dann, ich bin ganz Ohr, ja, gell?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_2_add";
		break;
		
		case "WildRose_Sesil_2_add":
			StartInstantDialog("Mary", "WildRose_Sesil_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Sesil_3":
			dialog.text = "Es geht um meine Eltern, Cécile. Über meine Mutter haben wir schon alles herausgefunden, was wir konnten... Sie ist gleich nach meiner Geburt gestorben. Aber mein Vater... er ist ein paar Tage später einfach spurlos verschwunden. Wir neigen dazu zu glauben, dass er nicht gestorben ist, ja, gell?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_3_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_4":
			dialog.text = "So jemanden wie ihn ins Jenseits zu befördern, das musste man erst mal schaffen, ja, gell?...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_4_add":
			StartInstantDialog("Mary", "WildRose_Sesil_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_5":
			dialog.text = "Hast du ihn gesehen?! Hast du mit ihm gesprochen?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_5_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_6":
			dialog.text = "Mein Mädchen, ich habe gesehen, wie er mit zwei Narwalen fast mit bloßen Händen fertig geworden ist...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_6_add":
			StartInstantDialog("Mary", "WildRose_Sesil_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_7":
			dialog.text = "Mit Sorrento und Rojas?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_7_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_8":
			dialog.text = "Ich hatte damals schon genug um die Ohren, um mir die Namen dieser Halunken zu merken – und jetzt weiß ich sie erst recht nicht mehr, ja, gell?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_8_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_8_add":
			StartInstantDialog("Mary", "WildRose_Sesil_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_9":
			dialog.text = "Schon gut, das ist nicht wichtig. Mach bitte weiter, Cécile.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_9_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_9_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_10", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_10":
			dialog.text = "Was soll ich denn noch erzählen? Er hat die beiden ins Wasser geworfen, sie sind wie Steine auf den Grund gesunken, und ihn selbst haben sie gepackt und auf die 'Tartarus' gebracht. Und das war auch richtig so – wer weiß, wen dieser Schläger sonst noch ertränkt hätte...";
			link.l1 = "Schläger? Das klingt aber ziemlich grob – finden Sie nicht auch, Mrs. Gallard? Wir sprechen hier von einem Menschen, von einem Offizier, der gerade erst seine Frau verloren hat...";
			link.l1.go = "WildRose_Sesil_11_1";
			link.l2 = "Ich sehe, Sie halten nicht allzu viel von ihm – das sagt man nicht über jeden Offizier, ja, gell?";
			link.l2.go = "WildRose_Sesil_11_2";
		break;

		case "WildRose_Sesil_11_1":
			dialog.text = "Ein Offizier, sagen Sie? Na ja. Die Uniform war schick, das weiß ich noch genau. Fast wie frisch aus der Schneiderei. Aber ich habe viele Offiziere gesehen, junger Mann. Und alle benahmen sich weitaus anständiger als dieser... Herr.";
			link.l1 = "Hat er noch etwas getan? Außer die beiden umzubringen?";
			link.l1.go = "WildRose_Sesil_12";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;

		case "WildRose_Sesil_11_2":
			dialog.text = "Ein Offizier, sagen Sie? Na ja. Die Uniform war schick, das weiß ich noch genau. Fast wie frisch aus der Schneiderei. Aber ich habe viele Offiziere gesehen, junger Mann. Und alle benahmen sich weitaus anständiger als dieser... Herr.";
			link.l1 = "Hat er noch etwas getan? Außer die beiden umzubringen?";
			link.l1.go = "WildRose_Sesil_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Sesil_12":
			dialog.text = "Er verlangte nach einem Priester in seine Zelle – Padre De la Cruz...";
			link.l1 = "Na sowas! Genau darüber wollten wir mit Ihnen sprechen. Kennen Sie die Einzelheiten dieses Gesprächs?";
			link.l1.go = "WildRose_Sesil_13";
		break;

		case "WildRose_Sesil_13":
			dialog.text = "Na klar doch, junger Mann! Dieser Nichtsnutz von Protestant hat vom Padre verlangt, seine Tochter nicht zu taufen – obwohl ihre Mutter Irin war, also katholisch, ja, gell?";
			link.l1 = "Ich höre fast zum ersten Mal, dass eine Engländerin so über einen Protestanten spricht... Ähm, entschuldigen Sie, dass ich Sie unterbrochen habe, Mrs. "+npchar.lastname+".";
			link.l1.go = "WildRose_Sesil_14";
		break;

		case "WildRose_Sesil_14":
			dialog.text = "Früher war ich selbst Protestantin, was soll ich leugnen. Aber Bruder Julian hat es geschafft, mich auf den rechten Weg zu führen.";
			link.l1 = "So ist das also... Wahrlich ein fähiger Diener des Herrn. Aber wir sind abgeschweift. Also wollte Kasper, dass seine Tochter im protestantischen Glauben aufwächst.";
			link.l1.go = "WildRose_Sesil_15";
		break;

		case "WildRose_Sesil_15":
			dialog.text = "Genau das hat er auch unserem Padre De la Cruz gesagt. Und außerdem – er hat befohlen, das Mädchen Julia zu nennen...";
			link.l1 = "Ach so, das bedeutet also dieses 'J.'. Mary Julia Casper... Aber warum hat man sie dann Mary genannt?";
			link.l1.go = "WildRose_Sesil_16";
		break;

		case "WildRose_Sesil_16":
			dialog.text = "Weil es ihre Mutter so wollte, das ist der Grund. Als das Mädchen aus ihrem Leib geholt wurde, hat sie den Namen geflüstert – Mary. Ich war damals nicht dabei, aber Aurélie Bertin war bei der Geburt anwesend. Ihr könnt sie fragen, wenn ihr wollt...";
			link.l1 = "Also wurde genau der Wunsch der Mutter berücksichtigt.";
			link.l1.go = "WildRose_Sesil_17";
		break;

		case "WildRose_Sesil_17":
			dialog.text = "Und hätte es denn anders sein sollen – schließlich ist der liebe Papa wie vom Erdboden verschluckt, ja, gell?";
			link.l1 = "Angesichts... der Talente von Padre De la Cruz bezweifle ich, dass die Meinung des Paters überhaupt berücksichtigt worden wäre – selbst wenn er weiter brav auf der 'Tartarus' sitzen geblieben wäre. Hat Domingo sich euch gegenüber nicht geäußert – wusste er nichts von Kaspers Plänen zur Flucht und einer möglichen Rückkehr wegen des Mädchens?";
			link.l1.go = "WildRose_Sesil_18_1";
			link.l2 = "Wahrscheinlich haben Sie recht. Aber zurück zu Pater Domingos Gespräch mit Mr. Casper – hat der Priester vielleicht erwähnt, ob Joshua mit ihm über eine Flucht und eine mögliche Rückkehr zu seiner Tochter gesprochen hat?";
			link.l2.go = "WildRose_Sesil_18_2";
		break;

		case "WildRose_Sesil_18_1":
			dialog.text = "Er hat nie davon gesprochen. Ja, und überleg doch selbst, "+npchar.name+", wenn ihr aus dem Gefängnis ausbrechen wolltet – würdet ihr das dem Erstbesten auf die Nase binden? Der Kerl jedenfalls hätte das ganz sicher nicht getan, das sag ich euch.";
			link.l1 = "Also hat uns diese Spur auch ins Nichts geführt. Nun gut, danke Ihnen für Ihre Zeit, Mrs. "+npchar.lastname+". Wir sehen uns noch, ja, gell?";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", -1);
			AddCharacterExpToSkill(pchar, "charisma", 100);
		break;

		case "WildRose_Sesil_18_2":
			dialog.text = "Er hat von so etwas nie erzählt. Ja, überleg doch selbst, "+npchar.name+",   wenn Sie aus dem Gefängnis ausbrechen wollten, würden Sie das dem Erstbesten erzählen? Der Kerl hätte das ganz bestimmt nicht getan, das sag ich Ihnen, ja, gell?";
			link.l1 = "Also hat uns auch diese Spur ins Nichts geführt. Nun gut, danke Ihnen für Ihre Zeit, Mrs. "+npchar.lastname+". Wir sehen uns wieder.";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;
		
		case "WildRose_Sesil_19":
			StartInstantDialog("Mary", "WildRose_Mary_121", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_121":
			dialog.text = "Wir haben einiges Interessantes herausgefunden, "+pchar.name+". Aber wir sind kaum vorangekommen, ja, gell?";
			link.l1 = "Und ein bisschen verwirrt sind wir auch. Wer ist wohl dieser Rupert, zu dem deine Mutter vor ihrem Tod gerufen hat?";
			link.l1.go = "WildRose_Mary_122";
		break;

		case "WildRose_Mary_122":
			dialog.text = "Vielleicht ein Bruder oder... ein enger Freund?";
			link.l1 = "Ein Freund, sagst du, na ja... Ich frage mich, ob Joshua von ihm wusste, ja, gell?...";
			link.l1.go = "WildRose_Mary_123";
		break;

		case "WildRose_Mary_123":
			dialog.text = "Worauf willst du hinaus, "+pchar.name+"?";
			link.l1 = "Dass wir das alles gründlich überdenken sollten. Zum Glück haben wir dafür genug Zeit, während wir jemanden suchen, der uns bei der weiteren Suche helfen kann. Wir haben bereits viel erreicht – aber wir sind noch nicht am Ziel. Uns selbst steht der Weg ins Büro der Royal Navy nicht offen, zumal es sich jenseits des Ozeans in London befindet... Hast du eine Idee, wer uns in dieser Angelegenheit unterstützen könnte?";
			link.l1.go = "WildRose_Mary_127";
		break;
		
		case "WildRose_Mary_127":
			dialog.text = "Was ist mit Serge Benoit, Charles?";
			link.l1 = "Der Abt? Er hat zwar große Verbindungen, das stimmt, aber an die Archive der Königlichen Flotte wird er wohl kaum herankommen, ja, gell?";
			link.l1.go = "WildRose_Mary_128";
		break;
		
		case "WildRose_Mary_128":
			dialog.text = "Wenn er es selbst nicht kann – vielleicht bringt er uns mit jemandem zusammen, der es kann, ja, gell?";
			link.l1 = "Wahrscheinlich schon. Also, Kurs auf Saint-Pierre.";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_25");
		break;
		
		// =================================================================
		// =================== ЭТАП 3. «БУМАЖНАЯ РАБОТА» ===================
		// =================================================================
		
		case "WildRose_Mary_131":
			dialog.text = "Nun, jetzt bleibt uns nur noch zu warten, ja, gell?";
			link.l1 = "Ich bin sicher, er wird alles herausfinden, "+npchar.name+". Die Zeit wird wie im Flug vergehen, du wirst es gar nicht merken. Und bis dahin – wir haben ja genug zu tun, ja, gell?";
			link.l1.go = "WildRose_Mary_132";
		break;

		case "WildRose_Mary_132":
			dialog.text = "Willst du damit auf etwas Bestimmtes hinaus, Liebling?";
			link.l1 = "Wir haben noch so viel zu tun, aber warum gehen wir jetzt nicht einfach zurück aufs Schiff, schließen die Tür ab und nehmen uns ein bisschen Zeit füreinander? Was meinst du?";
			link.l1.go = "WildRose_Mary_133";
		break;

		case "WildRose_Mary_133":
			dialog.text = "Ich wusste doch, dass du das vorschlagen würdest, ja, gell! Also, ich sag’s mal so: Verlieren wir keine Zeit!";
			link.l1 = "Komm schon, meine Liebste.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_3");
		break;
		
		case "WildRose_Mary_134":
			dialog.text = "Oh, "+pchar.name+", du kannst dir gar nicht vorstellen, wirklich nicht vorstellen, welche Last mir gerade von der Seele gefallen ist, ja, gell!";
			link.l1 = "Ich kann es mir sehr gut vorstellen, meine Liebe – du strahlst ja förmlich, haha! Wie du siehst, war das alles nicht umsonst.";
			link.l1.go = "WildRose_Mary_135";
		break;

		case "WildRose_Mary_135":
			dialog.text = "Mein Vater war ein berühmter Offizier, stell dir das mal vor! Aber wie schade, dass wir uns nie begegnet sind. Und wir haben nie erfahren, ob er das Festland je erreicht hat, ja, gell?";
			link.l1 = "Wenn das passiert wäre, wäre er bestimmt wieder in den Dienst zurückgekehrt, und irgendwo hätte man bestimmt etwas von ihm gehört, ja, gell? So ein Mensch hätte doch nie ruhig an einem Ort sitzen können – sonst, von wem hättest du das wohl?";
			link.l1.go = "WildRose_Mary_136";
		break;

		case "WildRose_Mary_136":
			dialog.text = "Glaubst du wirklich, dass er tot ist? Dass er in die Hände der Spanier auf Kuba gefallen ist oder vielleicht sogar auf der Insel der Gerechtigkeit getötet wurde?";
			link.l1 = "Ich versuche, der Wahrheit nüchtern ins Auge zu sehen, ja, gell? "+npchar.name+". In jenen Jahren gab es wenigstens irgendeine Verbindung mit der Insel, Schmuggler fuhren regelmäßig mit ihren Tartanen dorthin, ja, gell? Hätte er die Insel verlassen können, bin ich sicher, dass er nach einiger Zeit zurückgekehrt wäre, um dich zu holen.";
			link.l1.go = "WildRose_Mary_137";
		break;

		case "WildRose_Mary_137":
			dialog.text = "Um mich von dort wegzuholen. Aber dann hätten wir uns nicht getroffen, ja, gell?";
			link.l1 = "So ist das Leben, meine Liebe. Man weiß nie, wo man etwas findet und wo man es verliert. Ich hoffe, du bereust es nicht, dass du gerade jetzt hier bei mir bist.";
			link.l1.go = "WildRose_Mary_138";
		break;

		case "WildRose_Mary_138":
			dialog.text = "So einen Unsinn habe ich in meinem Leben noch nie gehört, ja, gell! "+pchar.name+", du bist der Beste, du bist großartig! Danke, dass du dir so viel Mühe gegeben hast, mir bei all dem zu helfen. Das bedeutet mir wirklich viel, ja, gell! Aber lass uns die Unterlagen anschauen – vielleicht finden wir darin noch etwas, das unser Freund uns nicht erzählt hat...";
			link.l1 = "Gute Idee. Fangen wir gleich an.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_7");
		break;
		
		case "WildRose_Mary_139":
			dialog.text = "Na, "+pchar.name+", hast du etwas Interessantes bemerkt?";
			link.l1 = "Ja, "+npchar.name+". Es gibt da was...";
			link.l1.go = "WildRose_Mary_140";
		break;

		case "WildRose_Mary_140":
			dialog.text = "Du schaust, als hättest du ein Gespenst gesehen, ja, gell?";
			link.l1 = "Hier wird ein gewisser Rupert Northwood erwähnt.";
			link.l1.go = "WildRose_Mary_141";
		break;

		case "WildRose_Mary_141":
			dialog.text = "Rupert Northwood?! Wirklich – der echte?";
			link.l1 = "Leise, "+npchar.name+" - Schrei nicht so. Hm-m... Ich denke, ja, das ist der Mann, von dem Chimiset gesprochen hat. Anders kann es gar nicht sein – solche Zufälle gibt es nicht, ja, gell?";
			link.l1.go = "WildRose_Mary_142";
		break;

		case "WildRose_Mary_142":
			dialog.text = "Und was hältst du von all dem, ja, gell? "+pchar.name+"?";
			link.l1 = "Diese Geschichte wird immer verworrener. Also... aus Plymouth ist die 'Cornwall' ausgelaufen, auf Antigua ist ebenfalls die 'Cornwall' angekommen, und an den Riffen der Insel der Gerechtigkeit ist dann schon die 'Wrangler' zerschellt – immer noch mit Joshua Casper an der Spitze, der es irgendwie geschafft hat, heimlich vor der Admiralität eine Frau zu heiraten, die in ihren letzten Atemzügen nach einem gewissen Rupert gerufen hat.";
			link.l1.go = "WildRose_Mary_143";
		break;

		case "WildRose_Mary_143":
			dialog.text = "Ich verstehe gar nichts. Ich weiß nicht einmal, wer sonst noch ein wenig Licht auf ihn werfen könnte. Je mehr wir über meinen Vater herauszufinden versuchen, desto mehr versinken wir in einem Sumpf aus immer neuen Rätseln und Geheimnissen, ja, gell?";
			link.l1 = "Wenn überhaupt jemand etwas Licht ins Dunkel bringen kann, dann sind das entweder Joshua Casper oder Rupert Northwood.";
			link.l1.go = "WildRose_Mary_144";
		break;

		case "WildRose_Mary_144":
			dialog.text = "Northwood? Aber er ist doch tot, ja, gell? Du glaubst doch nicht etwa, dass der Bericht, der nach der Ankunft der 'Cornwall' in St. John's verfasst wurde, falsche Angaben enthält?";
			link.l1 = "Ach, diese deine Naivität, "+npchar.name+"... Ich fange an zu glauben, dass diese ganze Geschichte von Anfang bis Ende von Lügen durchdrungen ist. Denk doch mal selbst nach: Joshua Casper war ein mustergültiger Offizier – viele Auszeichnungen und kein einziger Verweis. Das passt irgendwie nicht zu dem, was wir auf der Insel der Gerechtigkeit über ihn erfahren haben, wo er ohne zu zögern zwei Menschen umgebracht hat, findest du nicht?";
			link.l1.go = "WildRose_Mary_145";
		break;

		case "WildRose_Mary_145":
			dialog.text = "Er hat um das Leben seiner Frau, meiner Mutter, gekämpft, "+pchar.name+"!";
			link.l1 = "Zweifellos, aber überleg mal – wo kam sie überhaupt her? Und vor allem: Warum hat er seine Heirat vor dem Admiralitätsrat verheimlicht? Ein Offizier durch und durch, treu dem Kodex und seinem Eid – sonst wäre seine Akte wohl kaum so makellos – und dann so ein Ausrutscher?";
			link.l1.go = "WildRose_Mary_146";
		break;

		case "WildRose_Mary_146":
			dialog.text = "Und was, wenn sich dahinter vielleicht eine schöne und romantische Geschichte verbirgt? Sowas kommt doch, wenn auch selten, schon mal vor, ja, gell?";
			link.l1 = "Versteh mich nicht falsch, Mary, aber das klingt alles nicht nach Romantik. Eher nach einem Theaterstück, das aus irgendeinem Grund inszeniert wurde. Warum sonst hätte man das Schiff auf dem Weg nach Providence umbenennen sollen? Es war ein Kriegsschiff – für so etwas landet man schnell vor dem Kriegsgericht.";
			link.l1.go = "WildRose_Mary_147";
		break;

		case "WildRose_Mary_147":
			dialog.text = "Einverstanden – gute Frage.";
			link.l1 = "Und mit diesem Rupert Northwood stimmt doch auch etwas nicht, ja, gell? In dem Gefecht ist fast die halbe Mannschaft gefallen, aber seltsamerweise kein einziger Offizier außer ihm. Und warum hat deine Mutter vor ihrem Tod gerade nach Rupert gerufen und nicht nach ihrem Mann Joshua?";
			link.l1.go = "WildRose_Mary_148";
		break;

		case "WildRose_Mary_148":
			dialog.text = "Also bist du dir wirklich sicher, dass der Erste Maat nicht im Kampf mit den Spaniern gestorben ist, ja, gell? Und ich bin gar nicht die Tochter von Joshua Casper, sondern von Rupert Northwood – darauf willst du hinaus?";
			link.l1 = "Wie ich schon sagte – die Wahrheit kennt nur einer. Entweder Joshua Kasper, der aus irgendeinem Grund Theresa als seine Frau bezeichnete, oder Rupert Northwood, der ebenfalls aus unerklärlichen Gründen den Namen seines Kapitäns annahm.";
			link.l1.go = "WildRose_Mary_149";
		break;

		case "WildRose_Mary_149":
			dialog.text = "Was für ein Teufelszeug, ja, gell! Und was machen wir jetzt, "+pchar.name+"? Jetzt will ich der Wahrheit noch mehr auf den Grund gehen, aber wir haben ohnehin schon aus allen alles herausgeholt, was nur ging, ja, gell?";
			link.l1 = "Wenn es irgendwo Antworten gibt, dann auf der Insel der Gerechtigkeit – nirgendwo sonst sind noch Menschen übrig, außer vielleicht jenseits des Ozeans, die, wenn auch nur flüchtig, deine Eltern kannten. Ich denke, wir sollten noch einmal mit Aurélie Bertin sprechen – vielleicht fällt ihr noch etwas ein, woran wir uns festhalten können.";
			link.l1.go = "WildRose_Mary_150";
		break;

		case "WildRose_Mary_150":
			dialog.text = "Aber was willst du noch von ihr wissen? Sie hat uns doch schon alles erzählt, was sie wusste.";
			link.l1 = "Sie hat uns erzählt, was wir sie gefragt haben, und dabei vielleicht ein wichtiges Detail übersehen. Vielleicht hatte dein Vater eine Narbe im Gesicht oder ihm fehlte ein Finger an der Hand... Ich bezweifle, dass ein Mann, der sich all diese Tricks mit dem Ändern des Schiffnamens und vielleicht sogar seines eigenen Namens ausgedacht hat, einfach so auf einer Insel oder in den Kellern der Kastilier verschwunden ist.";
			link.l1.go = "WildRose_Mary_151";
		break;

		case "WildRose_Mary_151":
			dialog.text = "Wahrscheinlich hast du recht...";
			link.l1 = "Und wenn wir uns entscheiden, die Suche fortzusetzen – diesmal nicht in den verstaubten Regalen des Admiralitätsarchivs, sondern hier, auf dem Archipel, dann brauchen wir mehr als nur einen Namen, und dazu noch einen falschen, ja, gell?";
			link.l1.go = "WildRose_Mary_152";
		break;

		case "WildRose_Mary_152":
			dialog.text = "Weißt du, mir läuft bei all dem echt eine Gänsehaut über den Rücken, ja, gell? Entweder weil das alles so... aufregend ist, oder weil ich daran denken muss, dass mein Vater vielleicht gar nicht so anders war als dieser Mistkerl von der Bishop-Plantage.";
			link.l1 = "Egal wie auch immer, ich verspreche dir, wir werden alles tun, um der Sache auf den Grund zu gehen. Also, verlieren wir keine Zeit. Auf geht’s!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_9");
		break;
		
		// =================================================================
		// ==================== ЭТАП 4. «ПУТЬ К СВЕТУ» =====================
		// =================================================================
		case "WildRose_Mary_161":
			dialog.text = "Komm, "+pchar.name+", wir wollen keine Zeit verschwenden, ja, gell?";
			link.l1 = "Ich hoffe, Aurélie ist in ihrer Kajüte, und wir müssen nicht die ganze Insel nach ihr absuchen...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_2");
		break;
		
		case "WildRose_Mary_162":
			dialog.text = "Sieht so aus, als hätten wir schon wieder Pech gehabt, ja, gell? Und wo könnte sie nur hingekommen sein?";
			link.l1 = "Ich hoffe, die Krankheit hat nicht wieder Macht über ihren Verstand gewonnen...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_4");
		break;
		
		case "WildRose_Jillian_31":
			dialog.text = "Ah, ihr seid wieder da. Na, hallo... Was gibt es, braucht ihr schon wieder Aurélie?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_31_add";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_31_add":
			StartInstantDialog("Mary", "WildRose_Jillian_32", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_32":
			dialog.text = "An Einfallsreichtum mangelt es dir wirklich nicht, Jillian. Weißt du zufällig, wo sie ist?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_32_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_32_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_33", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_33":
			dialog.text = "In der Kirche, sie wollte beichten gehen. Wenn ihr euch beeilt, findet ihr sie dort, ja, gell?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_33_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_33_add":
			StartInstantDialog("Mary", "WildRose_Jillian_34", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_34":
			dialog.text = "Na ja, wenn sie schon beichtet, dann ist sie wohl ganz bei Verstand und klar im Kopf, ja, gell?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_34_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_35", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_35":
			dialog.text = "Schwer zu sagen... Die letzten drei Tage ist sie ganz neben sich, findet einfach keine Ruhe. Wissen Sie, sie war auf einmal furchtbar aufgeregt, als sie die Masten Ihres Schiffs hinter dem äußeren Ring gesehen hat.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_35_add":
			StartInstantDialog("Mary", "WildRose_Jillian_36", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_36":
			dialog.text = "Interessant, woran das wohl liegt, ja, gell?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_36_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_37":
			dialog.text = "Nun, wahrscheinlich widerstrebt ihr der Gedanke, dass sie von dir erneut ausgefragt werden könnte. Aber wann haben dich jemals die Probleme anderer gekümmert, ja, gell?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_37_add":
			StartInstantDialog("Mary", "WildRose_Jillian_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_38":
			dialog.text = "Sprich nicht in diesem Ton mit mir, Jillian. Diesmal verzeihe ich dir, aber wag es ja nicht, so etwas noch einmal zu sagen...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_5");
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "WildRose_Jillian_41":
			dialog.text = "Was für eine nervöse Person, kaum läuft etwas nicht nach ihrem Kopf, stimmt's?";
			link.l1 = "Man sollte sie besser nicht unnötig provozieren, ja, gell? "+npchar.name+". Ihr wisst ja, dass sie das Schwert nicht nur zum Schein trägt, ja, gell?";
			link.l1.go = "WildRose_Jillian_42";
		break;
		
		case "WildRose_Jillian_42":
			dialog.text = "Und ihr hättet so etwas einfach geschehen lassen, "+pchar.name+"?";
			link.l1 = "Ihr habt Mary einfach noch nie im Kampf gesehen, "+npchar.name+". Sonst würden sie sich keine Illusionen machen, dass sie jemand oder irgendetwas aufhalten könnte. Wir sehen uns noch, ja, gell?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_7");
		break;
		
		case "WildRose_Mary_163":
			dialog.text = "Du willst mich bestimmt etwas fragen, ja, gell? "+pchar.name+", ja, gell...";
			link.l1 = "Ehrlich gesagt ist es mir ziemlich egal, was da zwischen euch vorgefallen ist, auch wenn ich ahne, wie sie hieß. Oder besser gesagt, wie sie mal hieß. Willst du wirklich darüber reden?";
			link.l1.go = "WildRose_Mary_164_1";
			link.l2 = "Hast du und Jillian euch um etwas gestritten? Oder besser gesagt, um jemanden, ja, gell?";
			link.l2.go = "WildRose_Mary_164_2";
		break;

		case "WildRose_Mary_164_1":
			dialog.text = "Hm, eigentlich nicht.";
			link.l1 = "Wie du meinst. Und jetzt lass uns Aurelie suchen gehen.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Mary_164_2":
			dialog.text = "Diese Krabbe wird mir nie verzeihen, dass Alan mich ihr vorgezogen hat. Obwohl sie es könnte – immerhin gibt es ihn nicht mehr... Ehrlich gesagt, "+pchar.name+", darüber würde ich lieber nicht sprechen, ja, gell?";
			link.l1 = "Wie du willst, Liebes. Dann gehen wir Aurélie suchen.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Mary_165":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_9");
		break;
		
		case "WildRose_Oreli_61":
			dialog.text = ""+pchar.name+", Mary! Du bist wieder auf der Insel, was für eine Freude!";
			link.l1 = "Schön zu sehen, dass es Ihnen gut geht, "+npchar.name+". Eigentlich sind wir auf die Insel gekommen, um noch einmal mit Ihnen zu sprechen. Aber keine Sorge, das wird nicht lange dauern.";
			link.l1.go = "WildRose_Oreli_62";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Oreli_62":
			dialog.text = "Oh, ihr jungen Leute, ihr habt wirklich kein Erbarmen mit einer alten Frau. Aber ich habe gespürt, dass Sie kommen würden. Es geht doch wieder um deine Eltern, ja, Mary?";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_62_add";
		break;

		case "WildRose_Oreli_62_add":
			StartInstantDialog("Mary", "WildRose_Oreli_63", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_63":
			dialog.text = "Bitte, Aurélie. Ich verstehe, dass es dir schwerfällt, dich daran zu erinnern, nach all der Zeit, aber versuch es bitte noch einmal, ja, gell?";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_63_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;

		case "WildRose_Oreli_63_add":
			StartInstantDialog("LSC_Oreli", "WildRose_Oreli_64", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_64":
			dialog.text = "Ich habe Ihnen doch schon alles erzählt, woran ich mich erinnere. Ich habe wirklich keine Ahnung, was Sie noch aus mir herausbekommen wollen.";
			link.l1 = "Wir werden Ihnen ein paar Fragen stellen, "+npchar.name+". Und versuchen Sie bitte, sich an irgendetwas zu erinnern – an irgendwelche Details oder Einzelheiten. Wir werden Sie nicht unter Druck setzen...";
			link.l1.go = "WildRose_Oreli_65";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;

		case "WildRose_Oreli_65":
			dialog.text = "Macht ihr das nicht gerade jetzt?";
			link.l1 = "Ihr habt schon so viel für uns getan, "+npchar.name+"... Wir hoffen nur, dass sich in den Labyrinthen eures Gedächtnisses noch etwas findet, das uns sehr helfen wird.";
			link.l1.go = "WildRose_Oreli_66_1";
			link.l2 = "Wir haben einen weiten Weg hinter uns, "+npchar.name+". Ihr könnt euch gar nicht vorstellen, wie viel Mühe und Zeit er uns gekostet hat. Aber wir haben uns verirrt, und nur ihr und euer Gedächtnis könnt uns wieder auf den Pfad der Wahrheit führen.";
			link.l2.go = "WildRose_Oreli_66_2";
		break;

		case "WildRose_Oreli_66_1":
			dialog.text = "Erinnerung... Was ist denn noch davon übrig, von dieser Erinnerung. Manchmal weiß ich morgens nicht mal mehr, wie ich heiße, und ihr wollt von mir Einzelheiten – von Ereignissen, die zwanzig Jahre zurückliegen. Aber sei’s drum, fragt ruhig.";
			link.l1 = "Uns interessiert Mister Casper, Marys Vater. Können Sie sich an irgendetwas Auffälliges an seinem Aussehen erinnern? Hatte er vielleicht eine Narbe im Gesicht oder hat er stark gehinkt...";
			link.l1.go = "WildRose_Oreli_67";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "WildRose_Oreli_66_2":
			dialog.text = "Erinnerung... Was ist denn noch übrig davon, von dieser Erinnerung. Manchmal weiß ich morgens nicht mal mehr, wie ich zum Abort komme, und ihr wollt von mir Einzelheiten wissen – von dem, was vor zwanzig Jahren auf diesen Schiffswracks passiert ist. Aber gut, sei’s drum, fragt halt.";
			link.l1 = "Uns interessiert Mister Casper, Marys Vater. Können Sie sich an irgendetwas Auffälliges an seinem Aussehen erinnern? Hatte er vielleicht eine Narbe im Gesicht oder hat er stark gehinkt...";
			link.l1.go = "WildRose_Oreli_67";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Oreli_67":
			dialog.text = "Oh... Ich glaube, ich habe schon erwähnt, dass ich ihn nur in völliger Dunkelheit gesehen habe, im Laderaum der 'Ceres Smithy', wo sie für das arme Ding Teresa ein Lager hergerichtet hatten. Er hat ganz sicher nicht gehinkt – im Gegenteil, er war ein ziemlich flinker Kerl.";
			link.l1 = "Und wie alt war er? War er noch jung oder schon älter?";
			link.l1.go = "WildRose_Oreli_68";
		break;

		case "WildRose_Oreli_68":
			dialog.text = "Als alten Mann würde ich ihn nun wirklich nicht bezeichnen... Aber ich habe ihm auch nicht besonders viel Aufmerksamkeit geschenkt – ich war mehr um Teresa besorgt. Gut sah er natürlich nicht aus – er erinnerte eher an ein Gespenst. Allerdings solltet ihr bedenken, dass er die ganze Woche, während seine Frau hochschwanger war, kaum geschlafen hat... Er ist ständig über die Insel gelaufen, ohne Pause.";
			link.l1 = "Seine Frau hat er also sehr geliebt. Und Sie haben doch viel Zeit mit ihr verbracht, ja, gell? Hat sie nie etwas über ihren Mann gesagt?";
			link.l1.go = "WildRose_Oreli_69";
		break;

		case "WildRose_Oreli_69":
			dialog.text = "Theresa hat ständig nach ihm gefragt. Sie hat viel geschlafen, manchmal vor sich hin gefaselt, aber sobald sie wieder bei sich war, hat sie sofort gefragt, wo er ist. Und das arme Ding hat so, so sehr auf ihn gewartet. Aber im allerwichtigsten Moment – ist er einfach nicht gekommen.";
			link.l1 = "Verstehe. Offenbar war ihre Liebe gegenseitig... Nun, danke Ihnen, Aurélie. Sie haben uns wirklich sehr geholfen.";
			link.l1.go = "WildRose_Oreli_70";
		break;

		case "WildRose_Oreli_70":
			dialog.text = "Und das war's schon? Ich dachte, unser Gespräch würde sich über ein, zwei Stunden hinziehen, ja, gell?";
			link.l1 = "Wir haben doch versprochen, euch nicht lange zu quälen. Passt auf euch auf, "+npchar.name+". Alles Gute.";
			link.l1.go = "WildRose_Oreli_71";
		break;

		case "WildRose_Oreli_71":
			dialog.text = "Wartet, ihr jungen Leute! Ich habe noch etwas für euch... Genauer gesagt – für dich, Mary.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_a";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "WildRose_Oreli_72_a": //
			dialog.text = "Hier, mein Mädchen, nimm... Sobald ich die Segel Ihres Schiffes gesehen habe, nahm ich diesen Hut mit, um ihn nicht zu vergessen. Aber zur Anlegestelle hinauszugehen... dazu hatte ich nicht den Mut.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_add";
		break;

		case "WildRose_Oreli_72_add":
			StartInstantDialog("Mary", "WildRose_Oreli_73", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_73":
			dialog.text = "Was ist das, Aurélie? Ein Hut?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_73_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;

		case "WildRose_Oreli_73_add":
			StartInstantDialog("LSC_Oreli", "WildRose_Oreli_74", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_74":
			dialog.text = "Der Hut deiner Mutter, Teresa. Sie hatte ihn bei sich, als die Überlebenden des Schiffbruchs auf die 'Ceres Smitty' gebracht wurden. Als Teresa gestorben ist, habe ich diesen Hut vom Boden neben ihrem Bett aufgehoben – ja, und dann habe ich ihn vergessen... Erst heute, während unseres Gesprächs, ist er mir wieder eingefallen.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_74_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;

		case "WildRose_Oreli_74_add":
			StartInstantDialog("Mary", "WildRose_Oreli_75", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_75":
			dialog.text = "Oreli... Du hast sie all die Jahre aufbewahrt! Und... und du hast sie nicht weggeworfen, nicht verkauft... Danke, danke dir! Du kannst dir gar nicht vorstellen, wie... wertvoll und wichtig das für mich ist, ja, gell!";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_75_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;

		case "WildRose_Oreli_75_add":
			StartInstantDialog("LSC_Oreli", "WildRose_Oreli_76", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_76":
			dialog.text = "Entschuldige, Mary – ich hätte sie dir schon längst zurückgeben sollen... Aber mein Gedächtnis ist mittlerweile wie ein altes Sieb – weißt du...";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_76_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;

		case "WildRose_Oreli_76_add":
			StartInstantDialog("Mary", "WildRose_Oreli_77", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_77":
			dialog.text = "Besser geht’s gar nicht, Aurélie! Ich probier sie gleich an, ja, gell?";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_hat_1");
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "WildRose_Mary_166":
			dialog.text = "Na, mein Lieber, wie gefalle ich dir?..";
			link.l1 = "Du bist wunderschön. Und der Hut... ist auch noch nicht aus der Mode gekommen, sieht also ebenfalls großartig aus, ja, gell?";
			link.l1.go = "WildRose_Mary_167";
		break;
		
		case "WildRose_Mary_167":
			dialog.text = "Wirklich? Ich freu mich so, dass es dir gefällt, ja, gell!";
			link.l1 = "Und könnte es denn anders sein?";
			link.l1.go = "WildRose_Mary_167_add";
		break;
		
		case "WildRose_Mary_167_add":
			StartInstantDialog("LSC_Oreli", "WildRose_Mary_168", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_168":
			dialog.text = "...";
			link.l1 = "Vielen Dank noch einmal, Aurélie – Sie haben diesen Tag ein wenig heller gemacht! Alles Gute, ruhen Sie sich aus.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_10");
		break;
		
		case "WildRose_Mary_171":
			dialog.text = "Also war es doch Rupert. Rupert Northwood, ja, gell?";
			link.l1 = "Offensichtlich ja, meine Liebe. Er hat alles getan, um seine Frau zu retten... oder seine Geliebte, ich weiß es nicht. Das ist eigentlich auch egal. Wichtig ist nur, dass wir jetzt wissen, wen wir suchen müssen.";
			link.l1.go = "WildRose_Mary_172";
		break;

		case "WildRose_Mary_172":
			dialog.text = "Aber was ist mit dem echten Joshua Casper, dem Kapitän der 'Cornwall', passiert?";
			link.l1 = "Gute Frage, aber im Moment nicht die wichtigste. Warum Rupert nicht zu dir zurückgekehrt ist, wenn er Teresa so sehr geliebt hat – das ist viel spannender. Und das wird das Erste sein, was wir ihn fragen. Falls er überhaupt noch lebt und falls wir ihn finden. Eines steht fest – zur Flotte ist er nicht zurückgekehrt. Es hätte für ihn keinen Sinn gemacht, so ein Risiko einzugehen.";
			link.l1.go = "WildRose_Mary_174";
		break;

		case "WildRose_Mary_174":
			dialog.text = "Was könnte ihn bloß dazu gebracht haben, sich Joshua Casper zu nennen? Was ist an Bord der 'Cornwall', die zum 'Wrangler' wurde, passiert? Ist mein Vater etwa ein Verbrecher, "+pchar.name+"?";
			link.l1 = "Ich fürchte, diese Möglichkeit dürfen wir auch nicht ausschließen, ja, gell? "+npchar.name+". Wir sollten auf wirklich alles vorbereitet sein, ja, gell?";
			link.l1.go = "WildRose_Mary_175";
		break;

		case "WildRose_Mary_175":
			dialog.text = "Ich will gar nicht erst daran denken...";
			link.l1 = "Im Moment müssen wir an etwas anderes denken – nämlich, wo wir ihn suchen sollen. Er könnte sich den Piraten oder Schmugglern angeschlossen haben. Oder er hat sich in irgendeiner Stadt niedergelassen und hält sich versteckt. Alles ist möglich.";
			link.l1.go = "WildRose_Mary_176";
		break;
		
		case "WildRose_Mary_176":
			dialog.text = "Und was schlägst du vor, was wir tun sollen? Wie sollen wir ihn finden? Sollen wir in jede Kolonie gehen, seinen Namen nennen und hoffen, dass irgendjemand schon mal von Rupert Northwood gehört hat?";
			link.l1 = "Oder Joshua Casper. Er hätte durchaus weiter unter der Identität seines ehemaligen Kapitäns leben können – der vermutlich tot war. Aber das brachte gewisse Risiken mit sich, denn nach der verschwundenen Brigg hätte man suchen können. Zumal sich an Bord eine Truhe mit Silber befand, die für die Garnison von Providence bestimmt war.";
			link.l1.go = "WildRose_Mary_177";
		break;

		case "WildRose_Mary_177":
			dialog.text = "Du sagst es, ja, gell?";
			link.l1 = "Und doch wäre der angeblich bei den Azoren ums Leben gekommene Rupert Northwood wohl kaum für jemanden von Interesse gewesen. Allerdings gibt es hier definitiv noch einiges zu überdenken.";
			link.l1.go = "WildRose_Mary_178";
		break;

		case "WildRose_Mary_178":
			dialog.text = "Wie viel Zeit werden wir wohl noch verschwenden müssen, "+pchar.name+"?! Er könnte doch überall sein, in jeder Kolonie, ja, gell!";
			link.l1 = "Wenn er überlebt hat, natürlich. Aber ich bin nicht deiner Meinung. Er sprach wohl kaum fließend Spanisch, also hat er auf Kuba oder Hispaniola nichts zu suchen. Er konnte Französisch sprechen und ist vielleicht nach Tortuga oder in eine der Kolonien auf den Kleinen Antillen gegangen. Oder er hat sich im Westlichen Main niedergelassen, unter dem Schutz seiner Landsleute. Wir könnten wirklich viele Monate mit der Suche nach ihm verbringen – und es ist nicht sicher, dass wir Erfolg haben.";
			link.l1.go = "WildRose_Mary_179";
		break;

		case "WildRose_Mary_179":
			dialog.text = "Aber ich will nicht aufgeben, "+pchar.name+". Nur nicht jetzt, wo wir schon so viel herausgefunden haben, ja, gell!";
			link.l1 = "Das habe ich ja gar nicht vorgeschlagen, ja, gell? "+npchar.name+". Wir müssen ihn nicht selbst suchen – besser, wir wenden uns an jemanden mit guten Kontakten. Einmal hat das schon funktioniert, warum also nicht noch einmal versuchen?";
			link.l1.go = "WildRose_Mary_180";
		break;

		case "WildRose_Mary_180":
			dialog.text = "Willst du etwa, dass wir den Abt noch einmal um Hilfe bitten? Ich hatte den Eindruck, er hat uns ziemlich deutlich gemacht, dass wir in dieser Angelegenheit nicht mehr auf seine Unterstützung zählen können, ja, gell?";
			link.l1 = "Das wäre wirklich zu dreist dem Alten gegenüber, da hast du recht.";
			link.l1.go = "WildRose_Mary_181";
		break;

		case "WildRose_Mary_181":
			dialog.text = "Aber zu wem sollen wir dann gehen? Wer hat genug Geld und die richtigen Verbindungen für so ein Vorhaben?";
			link.l1 = "Die Nachforschungen werden wir wohl selbst finanzieren müssen. Aber was die Kontakte betrifft... Ich denke, Fadej der Moskauer könnte uns helfen. Er kennt bestimmt ein paar fähige Leute, die man in die Kolonien schicken könnte. Oder er weiß zumindest, an wen wir uns wenden sollten.";
			link.l1.go = "WildRose_Mary_182";
		break;

		case "WildRose_Mary_182":
			dialog.text = "Also, machen wir uns auf nach Basse-Terre, ja, gell?";
			link.l1 = "Ja, schauen wir bei unserem Freund vorbei. Das dürfte für ihn keine allzu schwere Aufgabe sein, wie ich finde.";
			link.l1.go = "WildRose_Mary_183";
		break;

		case "WildRose_Mary_183":
			dialog.text = "Hissen wir morgen die Anker, was meinst du? Ich würde gerne den Rest dieses Tages und die Nacht mit dir allein auf der 'Ceres Smitty' verbringen, ja, gell?";
			link.l1 = "Solche Angebote schlägt man nicht aus, Liebes. Wir haben uns eine kleine Pause wirklich verdient, ja, gell?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_12");
		break;
		
		case "WildRose_Jillian_51":
			dialog.text = "Was, ihr verlasst die Insel schon? Nicht einmal zur Beerdigung bleibt ihr, ja, gell?";
			link.l1 = "Beerdigung?..";
			link.l1.go = "WildRose_Jillian_52";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_52":
			dialog.text = "Ach, ihr wisst es also nicht. Verstehe... Aurélie Bertin ist letzte Nacht gestorben.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_52_add";
		break;

		case "WildRose_Jillian_52_add":
			StartInstantDialog("Mary", "WildRose_Jillian_53", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_53":
			dialog.text = "Was?! Das kann doch nicht sein – wir haben doch erst gestern mit ihr gesprochen, und sie war quicklebendig. Oder hat ihr jemand...";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_53_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_53_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_54", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_54":
			dialog.text = "Nein, Mary. Aurélie ist im Schlaf gestorben. Ich bin heute zu ihr gegangen, um ihr die Salben für die Gelenke zu bringen, die Bruder Julian hergestellt hat – und da habe ich sie gefunden. Sie lag auf dem Bett, mit einem seltsamen Lächeln im Gesicht. Aber sie war schon blass und kalt.   Die letzte Woche war die alte Dame ganz anders als sonst, ich dachte sogar, die Krankheit, die der schwarze Zauberer vertrieben hatte, sei zurückgekehrt. Aber sie war ganz klar im Kopf und hat, glaube ich, nicht gefaselt.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_54_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_54_add":
			StartInstantDialog("Mary", "WildRose_Jillian_55", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_55":
			dialog.text = "Wenigstens hat sie nicht gelitten, ja, gell?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_55_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_55_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_56", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_56":
			dialog.text = "Werdet ihr also zur Beerdigung bleiben? Sie findet morgen am entferntesten Riff statt – dort ist es tief genug, und die Krebse kommen nicht dorthin, ja, gell?";
			link.l1 = "Wir bleiben, Jillian. Aurélie hat so viel für Mary getan, dass wir gar nicht anders können. Wenn niemand etwas dagegen hat, organisieren wir die Zeremonie auf unserem Schiff. Wir bestatten sie auf offener See, mit allen Ehren.";
			link.l1.go = "WildRose_Jillian_57";
		break;
		
		case "WildRose_Jillian_57":
			dialog.text = "Niemand wird sich dagegen wehren. Es ist bequemer und am Ende auch sicherer, als zwischen den Wrackteilen herumzuklettern.";
			link.l1 = "Dann kümmert euch um die Beerdigung – Mary hilft euch dabei. Ich muss mich noch mit jemandem unterhalten...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_14");
		break;
		
		case "WildRose_Chimiset_61":
			dialog.text = "Da bist du ja wieder, mein lieber Freund! Was kann ich diesmal für dich tun?";
			link.l1 = "Hallo, "+npchar.name+". Hast du schon gehört, was letzte Nacht passiert ist, ja, gell?";
			link.l1.go = "WildRose_Chimiset_62";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_62":
			dialog.text = "Meinst du den Tod von Aurélie? Ich seh’s dir an. Klar hab ich davon gehört. Sie hat doch auf der ‚Pluto‘ gelebt, das ist ja praktisch Rivados-Gebiet. Und auf den anderen Schiffen reden sowieso alle nur noch darüber, ja, gell?";
			link.l1 = "Wir haben sie erst gestern gesehen, und sie war wohlauf – abgesehen davon, dass sie die ganze letzte Woche über irgendwie beunruhigt war. Und als sie unser Schiff sah, war sie erst recht aufgeregt, ja, gell?";
			link.l1.go = "WildRose_Chimiset_63";
		break;

		case "WildRose_Chimiset_63":
			dialog.text = "Man spürt, wenn der Fluss seines Lebens versickert. Manche zeigen es allen um sich herum, andere verbergen es tief in sich, aber fühlen tun es letztlich alle – besonders die, die auf ihr Herz zu hören wissen.";
			link.l1 = "Mir schien, sie war gesund, fast wie ein junges Reh, "+npchar.name+". Irgendwas passt hier nicht zusammen...";
			link.l1.go = "WildRose_Chimiset_64_1";
			link.l2 = "Und trotzdem war sie offensichtlich noch lange nicht am Ende, "+npchar.name+".";
			link.l2.go = "WildRose_Chimiset_64_2";
		break;

		case "WildRose_Chimiset_64_1":
			dialog.text = "Mein Freund, Verstand und Körper sind Dinge völlig unterschiedlicher Ordnung. Der Verstand lenkt den Körper, manchmal versucht der Körper, die Kontrolle über den Verstand zu übernehmen. Sie sind eng miteinander verbunden, aber dennoch kein einheitliches Ganzes. Ein Mensch kann äußerlich vollkommen gesund erscheinen, doch seine Seele wandelt bereits auf dem Pfad des Todes.";
			link.l1 = "Du bist klug, mein Freund, sehr klug. Wenn du spürst, dass die Wahrheit irgendwo in der Luft liegt, jagst du ihr nach wie ein Löwe der Zebra – und du wirst nicht aufgeben, bis du sie eingeholt hast. Das habe ich sofort erkannt, in dem Moment, als ich dich zum ersten Mal sah.";
			link.l1.go = "WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Chimiset_64_2":
			dialog.text = "Mein Freund, Verstand und Körper sind Dinge völlig unterschiedlicher Ordnung. Der Verstand lenkt den Körper, manchmal versucht der Körper, die Kontrolle über den Verstand zu übernehmen. Sie sind eng miteinander verbunden, aber dennoch kein einziges Ganzes. Ein Mensch kann äußerlich völlig gesund wirken, doch seine Seele wandelt bereits auf dem Pfad des Todes.";
			link.l1 = "Weißt du, mir kam der Gedanke, dass Aurelie uns irgendwie erwartet hat, als hätte sie gewusst, dass wir zu ihr kommen. Die alte Dame hätte ja einen Tag früher oder später sterben können, aber es ist fast direkt danach passiert, nachdem sie uns etwas Wichtiges über Marys Vater erzählt hat."link.l1.go ="WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Chimiset_65":
			dialog.text = "Du bist klug, mein Freund, sehr klug. Wenn du spürst, dass die Wahrheit in der Nähe liegt, jagst du ihr nach wie ein Löwe der Zebra — und du gibst nicht auf, bis du sie erfasst hast. Das wusste ich sofort, in dem Moment, als ich dich sah.";
			link.l1 = "Ich... Moment mal. Das Ritual, das du im Laderaum der 'Protector' durchgeführt hast... das hat doch die Krankheit von Aurélie nicht verlangsamt, oder? Aber was hast du dann getan?";
			link.l1.go = "WildRose_Chimiset_66";
		break;

		case "WildRose_Chimiset_66":
			dialog.text = "Man kann einen Fluss mit Steinen füllen, doch das hält ihn nicht auf. Ich wusste, dass ihr etwas Wichtiges von Aurélie brauchtet – und auch, dass ihr nicht sofort dorthin gelangen würdet. Aber wie lange euer Weg dauern würde, das wusste ich nicht. Deshalb errichtete ich einen Damm und nutzte all ihre Lebenskraft, um die Krankheit zurückzuhalten, bis sie ihre Bestimmung erfüllt hatte. Und sobald das geschehen war, brach die Barriere zusammen...";
			link.l1 = "Heißt das also, Aurélie... Im Moment ihres Todes war sie gar nicht sie selbst, hat sich gar nicht wahrgenommen – wie wir dachten?";
			link.l1.go = "WildRose_Chimiset_67";
		break;

		case "WildRose_Chimiset_67":
			dialog.text = "Sie setzte all ihre Kräfte ein, um bei klarem Verstand und festem Gedächtnis zu bleiben, und als das nicht mehr nötig war, überrollte sie die Krankheit wie eine riesige Welle und riss sie ins Tal des Todes. Ob ihr Tod leicht war, oder ob sie zu eurem Gott ging, gequält von Geistern der Vergangenheit und furchtbaren Albträumen – das kann ich nicht sagen, denn es ist mir nicht bekannt.";
			link.l1 = "Du wusstest ganz genau, worauf das hinausläuft, ja, gell? Warum zum Teufel hast du mich nicht vor den Folgen gewarnt?! Na, sag schon!";
			link.l1.go = "WildRose_Chimiset_68_1";
			link.l2 = "Du wusstest doch, was du tust, ja, gell? "+npchar.name+". Warum hast du mich nicht davor gewarnt, wohin das führen könnte?";
			link.l2.go = "WildRose_Chimiset_68_2";
		break;

		case "WildRose_Chimiset_68_1":
			dialog.text = "Weil ich beschlossen habe, dir zu helfen, mein Freund, das herauszufinden, was ihr wissen musstet, und ihr – ihr Schicksal zu erfüllen. Hätte ich dir gesagt, was sie erwartet, hättest du dich vielleicht nicht dazu entschlossen – und Aurélie hätte ihre Geheimnisse einfach mit ins Grab genommen. Was hätte das gebracht? Sie wäre umsonst gestorben. Wie eine Antilope, die vom Löwen gerissen, aber nicht gefressen und stattdessen den Geiern zum Fraß überlassen wird.";
			link.l1 = "Bestimmung, Nutzen... Du bist ja direkt ein Schicksalslenker, ja, gell? "+npchar.name+". Gott in Menschengestalt.";
			link.l1.go = "WildRose_Chimiset_69";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_68_2":
			dialog.text = "Weil ich beschlossen habe, dir zu helfen, mein Freund, damit du erfährst, was ihr wissen musstet, und sie – damit sie ihre Bestimmung erfüllen kann. Hätte ich dir gesagt, was sie erwartet, hättest du dich vielleicht nicht dazu entschlossen – und Aurélie hätte ihre Geheimnisse einfach mit ins Grab genommen. Was hätte das gebracht? Sie wäre umsonst gestorben. Wie eine Antilope, die vom Löwen gerissen, aber nicht gefressen und stattdessen den Geiern zum Fraß überlassen wird.";
			link.l1 = "Bestimmung, Nutzen... Du bist ja direkt eine Schicksalslenkerin, "+npchar.name+". Gott in Menschengestalt.";
			link.l1.go = "WildRose_Chimiset_69";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Chimiset_69":
			dialog.text = "Ich höre Unzufriedenheit in deiner Stimme, mein Freund. Aber nein, ich halte mich keineswegs für einen Gott – und glaube mir, selbst er ist nicht allmächtig. Weder der, an den ihr glaubt, noch die, denen wir huldigen. Götter können einem Menschen keine größere Kraft verleihen, als die, mit der er bei seiner Geburt gesegnet wurde. Wir Schamanen können diese Kräfte nur in die eine oder andere Richtung lenken – und nicht mehr als das.";
			link.l1 = "Und du hast sie auf einen Weg geführt, der sie ins Verderben gestürzt hat...";
			link.l1.go = "WildRose_Chimiset_70";
		break;

		case "WildRose_Chimiset_70":
			dialog.text = "Ich habe Aurélie nur den Weg gewiesen, auf dem sie Mary helfen konnte – einer Person, mit der sie von Geburt an eng verbunden war. Deine Gefährtin wurde nämlich vor ihren Augen geboren. Bitte, halte mich nicht für verrückt. Du würdest doch nicht behaupten, dass du in mir einen gutmütigen Zauberer gesehen hast, der mit einer Handbewegung den Fluss der Zeit umkehren kann?";
			link.l1 = "Ich weiß nicht, was ich dir sagen soll, "+npchar.name+". Vielleicht war das alles ja wirklich nicht umsonst. Aber so durfte es nicht laufen. Du hättest es mir sagen müssen, und ich hätte die Entscheidung treffen sollen. Doch was geschehen ist, lässt sich nicht rückgängig machen. Also dann, mach’s gut, Freund.";
			link.l1.go = "WildRose_Chimiset_71";
		break;

		case "WildRose_Chimiset_71":
			dialog.text = "Ach, so habe ich mir unser letztes Treffen nicht vorgestellt, mein Freund...";
			link.l1 = "Wie kommst du denn darauf, dass sie die letzte ist, ja, gell?";
			link.l1.go = "WildRose_Chimiset_72";
		break;

		case "WildRose_Chimiset_72":
			dialog.text = "Manche Flüsse münden in andere und werden ein Teil von ihnen, andere versiegen, und einige – wie unserer – enden in einem gewaltigen Wasserfall...";
			link.l1 = "Schon wieder Rätsel, Chimiset? Für heute reicht es mir wohl. Ich denke, wir sehen uns noch.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_15");
		break;
		
		case "WildRose_Mary_191":
			dialog.text = "Hab' ich mir schon gedacht, dass ich dich hier finde, ja, gell? Was wolltest du von Chimiseta, "+pchar.name+"? Was hat er dir gesagt?";
			link.l1 = "Nicht das, was ich erwartet – oder besser gesagt, gehofft – hatte zu hören. Aber etwas, das ich schon ganz vage geahnt habe, ja, gell?";
			link.l1.go = "WildRose_Mary_192";
		break;

		case "WildRose_Mary_192":
			dialog.text = "Du erzählst es mir doch, ja, gell?";
			link.l1 = "Nein, "+npchar.name+". Dieses Mal – nein. Alles, was in der Kajüte der 'Protector' gesagt wurde, bleibt auch dort, nur zwischen mir und Chimiset.";
			link.l1.go = "WildRose_Mary_193";
		break;

		case "WildRose_Mary_193":
			dialog.text = "Ich habe schon lange nicht mehr so viel Entschlossenheit in deiner Stimme gehört, "+pchar.name+". Aber gut, wir haben ja auch noch andere Sorgen, ja, gell? Die Beerdigung findet morgen bei Sonnenuntergang statt, um sieben Uhr.";
			link.l1 = "Komm, ich helfe euch, alles vorzubereiten.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_17");
		break;
		
		case "WildRose_Mary_201":
			dialog.text = "Sieht so aus, als wären jetzt alle da, ja, gell?";
			link.l1 = "Ich dachte, es wären mehr Leute da. Wenigstens von den friedlichen, ja, gell?";
			link.l1.go = "WildRose_Mary_202";
			CharacterTurnToLoc(npchar, "quest", "quest1");
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;

		case "WildRose_Mary_202":
			dialog.text = "Nun, Kuranai wurde nicht eingeladen, genau wie Rivados. Abbott, dieser widerliche, arrogante Truthahn, meinte, er habe Wichtigeres zu tun, als eine Katholikin zu beerdigen. Irgendetwas Ähnliches plapperten auch Lauderdale und Muskett. Kassel, dieser Rüpel, sagte einfach, dass er nicht kommt. Und alle anderen sind hier.";
			link.l1 = "Manche Dinge werden immer über meinem Verständnis stehen. Nun ja, Gott soll ihr Richter sein. Und da ist Bruder Julian... Jetzt geht alles los.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_2");
		break;
		
		case "WildRose_funeral_1":
			dialog.text = "Auch wenn unsere Herzen voller Trauer sind, lasst uns Gott für all die Gaben danken, mit denen Er die verstorbene Aurélie beschenkt hat, und ausrufen: Wir danken Dir, Gott, unser Vater\n"+"In all den Jahren und Tagen, die Aurélie  mit uns verbracht hat\n"+"Für das große Geschenk der heiligen Taufe, durch das Aurélie Deine Tochter geworden ist\n"+"Für die Fähigkeiten und das Wissen, mit denen Du sie beschenkt hast\n"+"Für ihren Dienst am Wohl der Familie und anderer Menschen\n"+"Für ihre Geduld mit unseren Fehlern\n"+"Beten wir zu Gott, dass Er unsere verstorbene Schwester Aurélie in Seine Herrlichkeit aufnimmt, und rufen wir: Wir bitten Dich, Herr\n"+"Mögen Aurels gute Taten reiche Früchte tragen\n"+"Lass das, was sie begonnen hat, fortgesetzt werden\n"+"Vergib ihr die Sünden, die sie begangen hat\n"+"Möge die Erinnerung an sie in unseren Herzen weiterleben\n"+"Beten wir zu Gott, dass er den Glauben und die Hoffnung der Leidenden stärke, und rufen wir zu ihm: Herr, mehre unseren Glauben\n"+"Durch Deinen Sohn, der Mensch geworden ist\n"+"Durch Deinen Sohn, Jesus Christus, der uns unendlich geliebt hat\n"+"Durch Deinen Sohn, der für unsere Sünden gestorben und zu unserem Heil auferstanden ist\n"+"Durch Deinen Sohn, der uns den Weg zum Himmel eröffnet hat\n"+"Zusammen mit allen Getreuen, die uns in die himmlische Heimat vorausgegangen sind, wollen wir beten, wie es uns der Erlöser gelehrt hat.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_7");
			
			WildRose_Etap4_PathToLight_18_funeral_6_1();
		break;
		
		case "WildRose_funeral_2":
			dialog.text = "Allmächtiger Gott, erhöre unsere Gebete, die wir im Glauben an Deinen auferstandenen Sohn emportragen, und stärke unsere Hoffnung, dass auch wir zusammen mit Deiner verstorbenen Dienerin der Auferstehung würdig werden. Durch unseren Herrn Jesus Christus, Deinen Sohn, der mit Dir lebt und herrscht in der Einheit des Heiligen Geistes, Gott von Ewigkeit zu Ewigkeit. Amen.";
			link.l1 = "Gott, allmächtiger Vater, das Geheimnis des Kreuzes ist unsere Stärke, und die Auferstehung Deines Sohnes ist das Fundament unserer Hoffnung; erlöse Deine verstorbene Dienerin aus den Fesseln des Todes und nimm sie auf in die Schar der Erlösten. Durch Christus, unseren Herrn. Amen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_8");
			WildRose_Etap4_PathToLight_18_funeral_7_1();
		break;
		
		case "WildRose_funeral_3":
			dialog.text = ""+pchar.name+", lass uns schnell in die Kajüte gehen, ja, gell? Ich fange gleich an zu weinen... Ich will nicht, dass das jemand sieht.";
			link.l1 = "Natürlich, "+npchar.name+". Gehen wir.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_13");
		break;
		
		case "WildRose_Mary_211":
			dialog.text = "Man beginnt einen Menschen erst nach seinem Tod wirklich zu schätzen – hast du das schon mal gehört, ja, gell? "+pchar.name+"?";
			link.l1 = "Ja – und nicht nur einmal, ja, gell?";
			link.l1.go = "WildRose_Mary_212";
		break;

		case "WildRose_Mary_212":
			dialog.text = "Erik hat das immer wieder gesagt. Ich glaube, er meinte damit seine Familie. Ich habe ihn nie danach gefragt – ich dachte, dafür bleibt noch Zeit. Und dann ist er gestorben, ja, gell? Jetzt ist auch Aurélie fort – und erst jetzt merke ich, wie selten ich ihr Zeit und Aufmerksamkeit geschenkt habe. Viel seltener, als sie es verdient hätte.";
			link.l1 = "Du bist an nichts schuld. Wir können nicht wissen, wann der Herr unsere Liebsten zu sich holt. Und die Zeit mit ihnen ist nie genug. Nie.";
			link.l1.go = "WildRose_Mary_213";
		break;

		case "WildRose_Mary_213":
			dialog.text = "Vielleicht ist das so, ja, gell? Und außerdem hat Erik oft gesagt – und Aurélie hat ihm da zugestimmt –, dass jeder Ort in erster Linie aus Menschen besteht. Nicht aus Häusern, Bäumen oder Straßen, sondern aus Menschen. Wenn man an einen Punkt auf der Karte denkt, erinnert man sich zuerst an diejenigen, die dort leben. Oder gelebt haben.";
			link.l1 = "Habe nie darüber nachgedacht. Aber vielleicht hatte Erik recht – was ist schon ein Zuhause wert, wenn man, sobald man es betritt, nie wieder seinen Vater oder Bruder trifft, ja, gell?";
			link.l1.go = "WildRose_Mary_214_1";
			link.l2 = "Da würde ich widersprechen. Wenn ich zum Beispiel an Paris denke, kommen mir zuerst die Gassen und die Gerüche in den Sinn... Von den Menschen erinnere ich mich nur an wenige – die anderen sind fast schon aus meinem Gedächtnis verschwunden, obwohl erst ein paar Jahre vergangen sind.";
			link.l2.go = "WildRose_Mary_214_2";
		break;

		case "WildRose_Mary_214_1":
			dialog.text = "Ich glaube, Erik und Aurélie haben über die Insel gesprochen, ja, gell? Und über die Leute, die hier einst lebten – vor langer Zeit. Ich war damals noch klein und habe das nicht verstanden, aber jetzt begreife ich es voll und ganz. Immerhin leben hier länger als ich Antonio, Cécile... und einige Rivados, wie Chimiceta – aber mit keinem von ihnen war ich je wirklich eng. Die anderen: Erik, Aurélie, Alan und viele mehr – sind tot.";
			link.l1 = "Ich verstehe. Die Welt ist... ein kleines bisschen kleiner geworden, ja, gell?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "WildRose_Mary_214_2":
			dialog.text = "Ich glaube, Erik und Aurélie haben über die Insel gesprochen, ja, gell? Und über die Leute, die hier gelebt haben – vor langer Zeit. Ich war damals noch klein und habe das nicht verstanden, aber jetzt ist mir alles klar geworden. Schließlich leben hier länger als ich nur Antonio, Cécile... und einige Rivados, wie Chimicet – aber mit keinem von ihnen war ich je wirklich eng. Die anderen: Erik, Aurélie, Alan und viele mehr – sind tot.";
			link.l1 = "Ich verstehe. Die Welt ist... ein kleines bisschen kleiner geworden, ja, gell?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Mary_215":
			dialog.text = "Eher – ist er leer geworden. Diese Welt – die innerhalb des äußeren Rings. Sie ist leer geworden, ja, gell? Und bald – könnte sie ganz verschwinden.";
			link.l1 = "Wovon sprichst du, Mary?.";
			link.l1.go = "WildRose_Mary_216";
		break;

		case "WildRose_Mary_216":
			dialog.text = "Hast du das denn nicht gespürt, ja, gell? "+pchar.name+"? Jetzt, als wir am Grab von Aurélie standen.";
			link.l1 = "Was genau?";
			link.l1.go = "WildRose_Mary_217";
		break;

		case "WildRose_Mary_217":
			dialog.text = "Ich weiß nicht, wie ich das erklären soll. Weißt du, wie die Luft vor einem Gewitter riecht? Erinnerst du dich – als du zum ersten Mal hier warst, wie viel Spannung in der Luft lag... Alle waren bereit, sich gegenseitig die Kehle durchzubeißen, viele meinten, den Geruch von Pulver und Blut zu spüren. Nachdem du Chad getötet hast, hat sich alles verändert – als ob das Atmen leichter wurde... Aber jetzt – ist dieses Gefühl wieder da.";
			link.l1 = "Ja, ich habe so etwas Ähnliches gespürt. Aber vielleicht liegt es einfach an der Stimmung? Es sind ja schließlich eine Beerdigung, ja, gell?...";
			link.l1.go = "WildRose_Mary_218_1";
			link.l2 = "Du bist erschöpft, "+npchar.name+". Ruh dich aus – dann wird es leichter. Ja, und kann man sich auf einer Beerdigung überhaupt anders fühlen, ja, gell?";
			link.l2.go = "WildRose_Mary_218_2";
		break;

		case "WildRose_Mary_218_1":
			dialog.text = "Als wir damals Erik und viele andere von der Insel dem Meer übergaben – das war ganz anders, sag ich dir. Da spürte man so etwas wie... Zusammenhalt. Aber heute – manche haben sich fast wie Wölfe angesehen, obwohl sie doch alle dasselbe Gebet gesprochen haben.";
			link.l1 = "Meinst du Leighton und Donald, ja, gell?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;

		case "WildRose_Mary_218_2":
			dialog.text = "Als wir Erik und viele andere Bewohner der Insel dem Meer übergaben – so war es damals nicht, sage ich dir. Da spürte man so etwas wie... Zusammenhalt. Aber heute – manche haben sich beinahe wie Wölfe angesehen, obwohl sie doch alle dasselbe Gebet gesprochen haben.";
			link.l1 = "Meinst du Leighton und Donald, ja, gell?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Mary_219":
			dialog.text = "Also hast du das auch bemerkt, ja, gell?";
			link.l1 = "Dexter reagiert nervös auf Greenspeys Versuche, ihm Lektionen zu erteilen – wie könnte es auch anders sein?";
			link.l1.go = "WildRose_Mary_220";
		break;

		case "WildRose_Mary_220":
			dialog.text = "Das wird nicht gut ausgehen, ja, gell?";
			link.l1 = "Wenn das so ist, dann fanden heute nicht nur die Beerdigung von Aurélie Bertin statt, sondern auch die dieses... City of Abandoned Ships.";
			link.l1.go = "WildRose_Mary_221";
		break;

		case "WildRose_Mary_221":
			dialog.text = "Stadt der verlorenen Schiffe?";
			link.l1 = "Verzeih mir, Mary, aber dieses Ort als Insel der Gerechtigkeit zu bezeichnen, das bringe ich wirklich nicht übers Herz, ja, gell?";
			link.l1.go = "WildRose_Mary_222";
		break;

		case "WildRose_Mary_222":
			dialog.text = "Jetzt, wo ich die Welt gesehen habe und verstanden habe, wie riesig sie ist, kommt mir dieser Ort wie ein Gefängnis vor, ja, gell? Es ist kaum zu glauben, dass ich hier aufgewachsen bin.";
			link.l1 = "Und ich kann kaum glauben, dass zwischen diesen Schiffswracks eine so wilde, wunderschöne Rose wie du erblühen konnte.";
			link.l1.go = "WildRose_Mary_223";
		break;

		case "WildRose_Mary_223":
			dialog.text = "Ich möchte mich von diesem Ort verabschieden, "+pchar.name+"... Wahrscheinlich werden wir nie wieder hierher zurückkehren, ja, gell? Ich will nicht zurückkommen. Ich will nicht mit eigenen Augen sehen, was hier noch passieren könnte.";
			link.l1 = "Ich rede mit Eddie und Donald. Vielleicht kann ich ihre Hitze ein wenig abkühlen, ja, gell?";
			link.l1.go = "WildRose_Mary_224";
		break;

		case "WildRose_Mary_224":
			dialog.text = "Du verstehst nicht...   Das wird das Unvermeidliche nur hinauszögern, also lohnt sich deine Mühe nicht.   Es wird der Tag kommen, an dem wir zurückkehren – und hier\nSo ist es besser, "+pchar.name+", ja... Nichts hält mich hier mehr, ja, gell?";
			link.l1 = "Wie du willst, meine Liebe. Wir erledigen alles – und dann verschwinden wir für immer von hier.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_20");
		break;
		
		// =================================================================
		// ==================== ЭТАП 5. «ЧУЖИМИ РУКАМИ» ====================
		// =================================================================
		case "WildRose_Mary_231":
			dialog.text = "Rupert Casper? Joshua Northwood, ja, gell?";
			link.l1 = "Ich habe die ganze Zeit darüber nachgedacht, ja, gell? "+npchar.name+". Und ich bin zu dem Schluss gekommen, dass dein Vater sich kaum unter einem Namen versteckt hätte, den er schon einmal benutzt hatte. Gleichzeitig konnte er wohl nicht riskieren, seinen echten Namen oder Nachnamen ganz aufzugeben – was, wenn er sich im falschen Moment nicht unter einem fremden Namen meldet?";
			link.l1.go = "WildRose_Mary_232";
		break;

		case "WildRose_Mary_232":
			dialog.text = "Er hätte sich nennen können, wie er wollte, ja, gell?";
			link.l1 = "Er könnte es natürlich geschafft haben. Und vielleicht hat er es tatsächlich getan. Wenn er auf Kuba überlebt hat, wohin er mit der Schaluppe der Schmuggler gekommen ist. Falls er angekommen ist und nicht zum Futter für die Krebse der Insel der Gerechtigkeit wurde. Jetzt bleibt uns nur noch zu warten – immerhin nicht so lange wie beim letzten Mal. Ich denke, einen Monat halten wir locker durch.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_3");
		break;

		case "WildRose_Mary_235":
			dialog.text = "Mein Vater lebt, "+pchar.name+". Und ich habe das doch immer gewusst, ja, gell!";
			link.l1 = "So wie ich, meine Liebe. Nun, es wird Zeit, diesem Jérôme einen Besuch abzustatten – und zwar möglichst bald, ja, gell?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_7");
		break;
		
		// =================================================================
		// ================= ЭТАП 6. «ЖИЗНЬ ПОСЛЕ СМЕРТИ» ==================
		// =================================================================
		case "WildRose_Mary_241":
			dialog.text = "Endlich sind wir da, ja, gell? Und was jetzt, "+pchar.name+"?";
			link.l1 = "Wir müssen Jérôme finden. Entweder macht er es sich in einem Zimmer der Taverne gemütlich, oder er hat sich ein Häuschen gemietet – Geld dafür hat er bestimmt, ja, gell?";
			link.l1.go = "WildRose_Mary_242";
		break;

		case "WildRose_Mary_242":
			dialog.text = "Wenn man bedenkt, wie viel Faddej ihm bezahlt hat... Ich denke, er hat sich bestimmt für die zweite Möglichkeit entschieden, ja, gell?";
			link.l1 = "Einverstanden. Wir können den Wirt vom 'Glasauge' nach ihm fragen oder uns bei gewöhnlichen Stadtbewohnern umhören. Los, Zeit ist kostbar.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_2");
		break;
		
		case "WildRose_BanditBeliz_1":
			dialog.text = "Na, na, na... Da sind ja unsere Turteltauben. Los, Jungs, machen wir’s kurz und berichten ihm dann.";
			link.l1 = "Jérôme Sauvernier? Was zum Teufel geht hier vor sich?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_5");
		break;
		
		case "WildRose_BanditBeliz_2":
			if (!CharacterIsAlive("WildRose_Bandit_1") && !CharacterIsAlive("WildRose_Bandit_2"))
			{
				dialog.text = "Ihr Mistkerle, kkh-kkh. Na wartet...";
				link.l1 = "Ich rate dir, deine Zunge im Zaum zu halten, wenn dir dein eigenes Fell lieb ist... ";
				link.l1.go = "WildRose_BanditBeliz_2_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "WildRose_BanditBeliz_2_1":
			dialog.text = "...";
			link.l1 = "Das auch. Und jetzt rück raus: Warum zum Teufel habt ihr uns angegriffen – und dann auch noch zusammen mit Sovereignet...";
			link.l1.go = "WildRose_BanditBeliz_3";
		break;

		case "WildRose_BanditBeliz_3":
			dialog.text = "Euer Souverän ist ein gieriger, feiger Bastard. Kaum hat Casper ihm ordentlich eingeheizt und dann noch etwas Geld versprochen, hat er auch schon ganz brav das Briefchen hingekritzelt, kch-kch...";
			link.l1 = "Also hat er ihn wirklich gefunden.";
			link.l1.go = "WildRose_BanditBeliz_4";
		break;

		case "WildRose_BanditBeliz_4":
			dialog.text = "Gefunden, gefunden. Also wirst du bald verrecken. Genau wie deine Freundin. Kasper wird euch beide in Streifen schneiden, he-he. Ich bin sowieso schon ein toter Mann, aber ich helfe dir, deinem Tod entgegenzugehen. Schade nur, dass ich nicht hören werde, wie ihr um Gnade winselt, wenn ihr in seine Hände fallt...";
			link.l1 = "Ja, ich bin ein toter Mann, das stimmt. Also sprich schneller, bevor ich den Geist aufgebe.";
			link.l1.go = "WildRose_BanditBeliz_6";
		break;

		case "WildRose_BanditBeliz_6":
			dialog.text = "Wenn ihr ihn treffen wollt, dann geht zur Bucht von Chetumal, dort hält er sich auf. Suchen müsst ihr ihn nicht, er findet euch von selbst, ja, gell?";
			link.l1 = "Na also, das ist doch prima. Jetzt kannst du sterben, so oft du willst. Und ich muss dann mal.";
			link.l1.go = "WildRose_BanditBeliz_Just_Deth";
			link.l2 = "Ich hoffe es. Und jetzt fahr zur Hölle.";
			link.l2.go = "WildRose_BanditBeliz_Hit_Deth";
		break;
		
		case "WildRose_BanditBeliz_Just_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_8");
		break;
		
		case "WildRose_BanditBeliz_Hit_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_7");
		break;
		
		case "WildRose_Mary_251":
			dialog.text = "Oh Gott, "+pchar.name+"... Ich kann es nicht fassen, einfach nicht, ja, gell! Hat das wirklich mein Vater getan?!";
			link.l1 = "Anscheinend ja, "+npchar.name+". Ich weiß wirklich nicht, was ihn geritten hat und wer zum Teufel er überhaupt ist... Aber es ist wohl kaum ein anderer Rupert Casper. Solche Zufälle gibt es einfach nicht.";
			link.l1.go = "WildRose_Mary_252";
		break;

		case "WildRose_Mary_252":
			dialog.text = "Und was sollen wir jetzt tun? Was soll ich sagen, wenn ich ihm in die Augen schaue?";
			link.l1 = "Zuerst müssen wir ihn überhaupt erreichen. Wahrscheinlich hat er sich selbst außerhalb des Gesetzes gestellt, wenn seine Suche schon... so eine nervöse Reaktion ausgelöst hat. Aber wie dem auch sei, er bleibt dein Vater. Für dessen Suche wir eine Menge Mühe, Zeit und Geld aufgewendet haben.";
			link.l1.go = "WildRose_Mary_253";
		break;

		case "WildRose_Mary_253":
			dialog.text = "Aber was, wenn er nicht einmal mit uns reden will? Warum hat er befohlen, uns umzubringen?";
			link.l1 = "Schon allein deshalb, weil er vielleicht gar nicht wusste, wer genau nach ihm sucht. Fadej hätte einfach nur einen Namen nennen können und die Details über dich verschweigen. Andernfalls, denke ich, müssten wir unsere Klingen jetzt nicht mit Blut besudeln.";
			link.l1.go = "WildRose_Mary_254";
		break;

		case "WildRose_Mary_254":
			dialog.text = "Und was jetzt? Gehen wir zur Bucht von Chetumal? Aber wenn er uns hier schon eine Falle gestellt hat... wer weiß, was uns dort erwartet?";
			link.l1 = "Wir haben einen Zeitvorteil, solange er noch nichts von dem erfährt, was hier passiert ist. Nutzen wir ihn. Wir fahren mit dem Schiff zur Bucht, und zur Unterstützung schicken wir einen Trupp zu Land, angeführt von einem unserer Offiziere.";
			link.l1.go = "WildRose_Mary_255";
		break;

		case "WildRose_Mary_255":
			dialog.text = "Klingt vernünftig, ja, gell? Aber wer wird das anführen?";
			if (CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				link.l1 = "Tichingitu. Er ist kampferprobt an Land. Niemand wäre dafür besser geeignet.";
				link.l1.go = "WildRose_Etap6_Tichingitu";
			}
			if (CheckPassengerInCharacter(pchar, "Duran"))
			{
				link.l2 = "Claude. Er wird natürlich nicht begeistert sein, aber das macht nichts – er wird’s überleben.";
				link.l2.go = "WildRose_Etap6_Duran";
			}
			if (CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l3 = "Hercule. Er weiß ganz genau, wie solche Sachen laufen, ja, gell?";
				link.l3.go = "WildRose_Etap6_Tonzag";
			}
			if (CheckPassengerInCharacter(pchar, "Irons"))
			{
				link.l4 = "Tommy. Selbst wenn etwas schiefgeht, findet der Kerl immer einen Ausweg, glaub mir, ja, gell?";
				link.l4.go = "WildRose_Etap6_Irons";
			}
			if (CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l5 = "Longway. Es ist nicht das erste Mal, dass er einen Feind im Dschungel aufspürt.";
				link.l5.go = "WildRose_Etap6_Longway";
			}
			if (!CheckPassengerInCharacter(pchar, "Tichingitu") && !CheckPassengerInCharacter(pchar, "Duran") && !CheckPassengerInCharacter(pchar, "Tonzag") && !CheckPassengerInCharacter(pchar, "Irons") && !CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l99 = "Alonso. Mit dem Degen fuchtelt er ganz schön geschickt, und dumm ist er auch nicht, ja, gell?";
				link.l99.go = "WildRose_Etap6_Alonso";
			}
		break;
		
		case "WildRose_Etap6_Tichingitu":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tichingitu");
		break;
		
		case "WildRose_Etap6_Duran":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Duran");
		break;
		
		case "WildRose_Etap6_Tonzag":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tonzag");
		break;
		
		case "WildRose_Etap6_Irons":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Irons");
		break;
		
		case "WildRose_Etap6_Longway":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Longway");
		break;
		
		case "WildRose_Etap6_Alonso":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Alonso");
		break;
		
		//
		case "WildRose_Tichingitu_1":
			dialog.text = "Tichingitu aufmerksam zuhören, Kapitän "+pchar.name+".";
			link.l1 = "Mein Freund, dir steht eine verantwortungsvolle Aufgabe bevor. In der Bucht von Chetumal hat sich eine Bande von Halunken verschanzt. Du musst sie aufspüren und vernichten. Wir nähern uns mit unserem Schiff von der Seeseite, ja, gell?";
			link.l1.go = "WildRose_Tichingitu_2";
		break;

		case "WildRose_Tichingitu_2":
			dialog.text = "";
			link.l1 = "Du sollst an der Spitze unserer Truppe durch den Dschungel gehen, um den Halunken in den Rücken zu fallen. Hast du Fragen an mich?";
			link.l1.go = "WildRose_Tichingitu_3";
		break;

		case "WildRose_Tichingitu_3":
			dialog.text = "Die Indianer haben keine Fragen. Morgen Mittag wird die Truppe am Ort sein und dort im Hinterhalt warten.";
			link.l1 = "Sehr gut, Tichingitu. Viel Glück dir.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Duran_1":
			dialog.text = "Gerufen, Käpt’n?";
			link.l1 = "Ich habe einen Auftrag für dich, Claude.";
			link.l1.go = "WildRose_Duran_2";
		break;

		case "WildRose_Duran_2":
			dialog.text = "";
			link.l1 = "Wir müssen eine Truppe Kämpfer zusammenstellen und mit ihr durch den Dschungel bis zur Bucht von Chetumal gelangen. Dort wartet eine Bande unter der Führung eines gewissen Rupert Casper auf uns. Sie wollen uns eine unangenehme Überraschung bereiten. In Wirklichkeit werden aber wir sie überraschen – genauer gesagt, du. Du greifst sie auf mein Zeichen an. Fragen?";
			link.l1.go = "WildRose_Duran_3";
		break;

		case "WildRose_Duran_3":
			dialog.text = "Ich hasse es, durch den Dschungel zu stapfen. Aber wie man so sagt, Befehl ist Befehl. Wir sehen uns am Treffpunkt, denke ich, so gegen morgen Mittag.";
			link.l1 = "Viel Glück, Claude.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Tonzag_1":
			dialog.text = "Ich höre dir zu, Käpt’n.";
			link.l1 = "Herkules, für dich gibt es Arbeit.";
			link.l1.go = "WildRose_Tonzag_2";
		break;

		case "WildRose_Tonzag_2":
			dialog.text = "Muss ich jemandem ein paar Kugeln in seinen wirren Dickschädel jagen? Das mache ich immer gern, weißt du doch, ja, gell?";
			link.l1 = "Fast richtig geraten. Du musst eine Gruppe Kämpfer von unserem Schiff anführen und sie durch den Dschungel zur Bucht von Chetumal bringen. Dort legt ihr einen Hinterhalt für die Bande, die uns dort vermutlich auflauern wird, ja, gell?";
			link.l1.go = "WildRose_Tonzag_3";
		break;

		case "WildRose_Tonzag_3":
			dialog.text = "Ich dachte, du redest von einer ernsten Sache, Käpt’n. Und du fängst fast schon von einem Tavernenbesuch an. Morgen Mittag kannst du drauf zählen, dass wir da sind.";
			link.l1 = "Wir sehen uns dann dort. Viel Glück, Hercule.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Irons_1":
			dialog.text = "Ha, Käpt’n, warum bist du denn so ernst – als würdest du gleich zu einer Beerdigung gehen, ja, gell?";
			link.l1 = "Machst du wieder Witze, Tommy? Soll ich auch mal einen reißen? Deinen Lohn für diesen Monat bekommst du nicht. Und für den nächsten auch nicht. Warum bist du jetzt so angespannt, ja, gell?";
			link.l1.go = "WildRose_Irons_2";
		break;

		case "WildRose_Irons_2":
			dialog.text = "Und nicht mal einen Scherz darf man machen...";
			link.l1 = "Alles zu seiner Zeit, Tommy. Das musst du erst noch lernen, ja, gell? Jetzt hör mir gut zu: Stell eine Truppe zusammen und mach dich durch den Urwald auf den Weg zur Bucht von Chetumal. Sobald ihr dort seid, wartet auf meinen Befehl.";
			link.l1.go = "WildRose_Irons_3";
		break;

		case "WildRose_Irons_3":
			dialog.text = "Durch den Dschungel stapfen? Wir kommen doch frühestens morgen Mittag dort an, ja, gell?";
			link.l1 = "Also, wir sehen uns morgen Mittag dort. Ohne Befehl wird nicht gekämpft, die Positionen werden nicht verlassen. Ist das klar? Ich sehe, dass es klar ist. Und jetzt – an die Arbeit.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Longway_1":
			dialog.text = "Longway hört Euch, Herr Kapitän.";
			link.l1 = "Kumpel, ich habe einen Auftrag für dich.";
			link.l1.go = "WildRose_Longway_2";
		break;

		case "WildRose_Longway_2":
			dialog.text = "...";
			link.l1 = "Du sollst die Truppe unserer Kämpfer anführen, die durch den Dschungel bis zur Bucht von Chetumal vorrücken wird. Dort könnte es zu einem Zusammenstoß mit dem Feind kommen, also bereite deine Leute gut vor.";
			link.l1.go = "WildRose_Longway_3";
		break;

		case "WildRose_Longway_3":
			dialog.text = "Longway alles verstehen, nicht sorgen, Herr Kapitän. Wir kommen ungefähr morgen Mittag an.";
			link.l1 = "Geh und sei vorsichtig.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Alonso_1":
			dialog.text = "Hast du gerufen, Kapitän?";
			link.l1 = "Ja. Hör gut zu, Alonso.";
			link.l1.go = "WildRose_Alonso_2";
		break;
		
		case "WildRose_Alonso_2":
			dialog.text = "";
			link.l1 = "An der Spitze einer Truppe musst du durch den Dschungel marschieren und zur Bucht von Chetumal gelangen. Dort wartet höchstwahrscheinlich eine Bande Halunken auf dich. Du musst Stellung beziehen und sie auf mein Zeichen von hinten angreifen.";
			link.l1.go = "WildRose_Alonso_3";
		break;

		case "WildRose_Alonso_3":
			dialog.text = "Kleinigkeit, Kapitän. Aber geht nicht vor morgen Mittag in der Bucht an Land – vorher kommen die Jungs und ich da nicht hin.";
			link.l1 = "Bereite dich gut vor, Alonso. Und Gott helfe uns, ja, gell?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Mary_256":
			dialog.text = "Charles, hast du gesehen, ja, gell?";
			link.l1 = "Sieht so aus, als würden sie schon auf uns warten. Bestimmt lauern sie hinter dieser Biegung, ja, gell?";
			link.l1.go = "WildRose_Mary_257";
		break;

		case "WildRose_Mary_257":
			dialog.text = "Aber zu einem Sieb sind wir noch nicht gemacht worden. Und nicht mal versucht man es, ja, gell?";
			link.l1 = "Vielleicht will er ja doch zuerst mit uns reden. Wir sollten ihn nicht provozieren – gehen wir einfach selbst hin, unser Trupp sichert uns ab. Los, machen wir dem Ganzen ein Ende.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_18_1");
		break;
		
		case "WildRose_Rupert_1":
			dialog.text = "Stehen bleiben! Keinen Schritt weiter! Jungs, wenn der Bengel sich rührt, macht Löcher in ihn. Das Mädchen bleibt unberührt.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_1_add";
			// link.l1.go = "WildRose_Rupert_87";
		break;

		case "WildRose_Rupert_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_2", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_2":
			dialog.text = "Papa?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_3":
			if (CheckCharacterItem(sld, "MarysHat")) // У Мэри есть своя шляпа
			{
				dialog.text = "Ja-a, ich habe viel gesehen in meinem langen und schweren Leben. Jedes Mal denke ich, nichts kann mich mehr überraschen – und jedes Mal irre ich mich. Also hast du dort tatsächlich überlebt... Und sogar Theresas Hut bewahrt. Ich hätte nie gedacht, dass ich ihn je wiedersehen würde.";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_1_add";
			}
			else
			{
				dialog.text = "Ja, gell, ich habe in meinem langen und nicht gerade leichten Leben schon einiges gesehen. Jedes Mal denke ich, dass mich nichts mehr überraschen kann – und jedes Mal liege ich falsch. Also hast du dort doch überlebt, Julia...";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_add";
			}
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_3_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_2":
			dialog.text = "Sie wurde mir von Aurélie übergeben, vor ihrem... Ableben.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_3":
			dialog.text = "Wie rührend... Jetzt kommen mir gleich die Tränen. Ich dachte schon, man hätte Theresas Hut mit ihr begraben. Sie hat sich keine Sekunde davon getrennt, seit ich ihn ihr geschenkt hatte. Deine Mutter war zwar nur eine einfache Schankmaid, aber der Abenteurergeist sprudelte bei ihr fast aus den Ohren. Als ich sie bei der Einnahme der 'Fleur-de-Lys' fand, wusste ich sofort, dass Theresa verrückt nach ihr sein würde. Sie sah darin lächerlich aus, aber es war ihr völlig egal – sie nahm den Hut nur zum Schlafen ab. Aber dir, Julia, steht er wirklich gut.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_add":
			StartInstantDialog("Mary", "WildRose_Rupert_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_4":
			dialog.text = "Julia? Nein, da irren Sie sich, ich heiße Mary...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_4_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_5":
			dialog.text = "Hm, so that's how it is. Turns out those scoundrels ignored my words and took matters into their own hands. Well, you couldn't expect anything else from those Catholic dogs.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_5_add":
			StartInstantDialog("Mary", "WildRose_Rupert_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_6":
			dialog.text = "Du... Du... Bist du wirklich mein Vater?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_6_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_6_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_7":
			dialog.text = "Na ja, wäre das nicht so, würdet ihr beide mit deinem Kumpel schon längst am Boden liegen, durchlöchert von Blei. Ich glaube schon lange weder an Gott noch an den Teufel, aber vielleicht gibt es sie ja doch. Den Ersteren wohl ganz sicher – schließlich hat er dich mit dem Aussehen von Teresa beschenkt. Und damit hat er dir gerade das Leben gerettet. Wie sagt man so schön: Gottes Wege sind unergründlich, ja, gell? Ha-ha-ha!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_7_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_7_add":
			StartInstantDialog("Mary", "WildRose_Rupert_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_8":
			dialog.text = "Papa... Ich... ich versteh das nicht, ja, gell...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_8_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_8_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_9":
			dialog.text = "Ach, das kannst du doch gar nicht verstehen, ja, gell...";
			link.l1 = "Irgendwie sieht es nicht so aus, als ob Sie sich freuen, Ihre Tochter zu sehen, Mister Casper. Zumal Sie sie ja selbst erkannt haben.";
			link.l1.go = "WildRose_Rupert_10";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_10":
			dialog.text = "An Grips fehlt es dir ja nicht, Bürschchen... Wie war noch gleich dein Name?";
			link.l1 = ""+GetFullName(pchar)+". Während wir nach Ihnen gesucht haben, haben wir uns ständig gefragt, wie Sie all die Zeit überlebt haben. Falls Sie überhaupt überlebt haben. Aber ich sehe – Sie haben es sich hier ganz gut eingerichtet, Mister... Northwood.";
			link.l1.go = "WildRose_Rupert_11";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_11":
			dialog.text = "Ah–so, ihr habt also sogar das herausgefunden. Mein Respekt, Monsieur Froschfresser, was soll ich noch sagen – vor allem, da ich eigentlich dafür gesorgt habe, alle Spuren zu beseitigen.";
			link.l1 = "Nicht nur davor. Wir wissen auch vom 'Cornwall', von seiner Ladung und von Joshua Casper, dessen Namen du dir eine Zeit lang ausgeliehen hast – und dessen Nachnamen wohl für immer, ja, gell?";
			link.l1.go = "WildRose_Rupert_12";
		break;

		case "WildRose_Rupert_12":
			dialog.text = "Bravo (klatscht Beifall). Ich bin beeindruckt. Bist du selbst auf alles gekommen, oder hat mein heißgeliebtes Kind auch seinen Beitrag geleistet?";
			link.l1 = "Ohne Mary hätte ich das nie geschafft. Sie wollte unbedingt alles über ihre Eltern wissen. Das Schicksal von Teresa aufzuklären war nicht schwer, aber deiner Spur sind wir ziemlich lange gefolgt...";
			link.l1.go = "WildRose_Rupert_13";
		break;
		
		case "WildRose_Rupert_13":
			dialog.text = "Das ist ja so rührend, dass mir fast die Tränen kommen. Na, Tochter, bist du jetzt zufrieden? Glücklich? Willst du deinen Papa umarmen?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_13_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_13_add":
			StartInstantDialog("Mary", "WildRose_Rupert_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_14":
			dialog.text = "Ich verstehe das nicht, Vater... Warum quälst du mich so? Wofür denn?! (schreit) Du warst es doch, der mich dort zurückgelassen hat – auf diesen Schiffswracks! Und dann hast du nicht mal daran gedacht, zurückzukommen, ja, gell? Warum? Wer bist du überhaupt, und wer sind diese Leute hinter deinem Rücken?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_14_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_14_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_15":
			dialog.text = "Sag mal, "+pchar.lastname+" , flippt sie oft so aus? Das hat sie von ihrer Mutter. Teresa war ein wunderbares Mädchen, die beste, die ich je getroffen habe. Aber Tränen vergießen und hysterisch werden, das mochte sie, ja-a... Was soll ich sagen... eine Irin.";
			link.l1 = "Beleidigt sie ja nicht! Mary ist nicht schuld an euren Missgeschicken und sie hat so eine Behandlung ganz bestimmt nicht verdient, ja, gell?";
			link.l1.go = "WildRose_Rupert_16";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;
		
		case "WildRose_Rupert_16":
			dialog.text = "Willst du mir etwa das Maul stopfen, du Bengel?!";
			link.l1 = "Im Gegenteil. Ich will, dass Sie uns Ihre Geschichte erzählen. Für Mary ist es sehr wichtig, das zu erfahren. Aber ich werde nicht zulassen, dass Sie sie herabwürdigen. Also reißen Sie sich zusammen.";
			link.l1.go = "WildRose_Rupert_17";
		break;
		
		case "WildRose_Rupert_17":
			dialog.text = "Denkst du, ich will euch wirklich mein Herz ausschütten? Mein Leben ist eben so verlaufen, wie es verlaufen ist, und, wie ihr Papisten zu sagen pflegt – Gott ist mein Zeuge – ich bereue nichts. Außer, dass ich damals Teresa verloren habe – ihretwegen. Hass ich dich, Tochter? Vielleicht war das früher mal so – aber jetzt bist du mir völlig egal.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_17_add";
		break;

		case "WildRose_Rupert_17_add":
			StartInstantDialog("Mary", "WildRose_Rupert_18", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_18":
			dialog.text = "Du gibst mir die Schuld am Tod von Mama?! Du... Was habe ich denn verbrochen – dass ich überhaupt auf die Welt gekommen bin, ja, gell? Na gut, Vater, "+pchar.name+", hat recht – erzähl uns alles, und dann drehen wir uns um und gehen. Und ich werde dir nie wieder unter die Augen treten, wenn du... (fängt an zu weinen).";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_18_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_19", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_19":
			dialog.text = "Ja-a-a, ganz die Theresa. Als wäre ich zwanzig Jahre in die Vergangenheit zurückversetzt, ha-ha. Zum Teufel mit euch. Ich wollte das alles eigentlich nicht wieder aufwühlen... Also, wenn ich am Ende dieser Erzählung entscheide, dir eine Kugel in die Stirn zu jagen, Liebling – gib dir selbst die Schuld.";
			link.l1 = "Dann kriegen auch Sie eine Kugel ab, Rupert. Und ich glaube kaum, dass das in Ihren Plan passt – Sie sehen nämlich aus wie jemand, der sein Leben zu schätzen weiß.";
			link.l1.go = "WildRose_Rupert_20";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_20": //
			dialog.text = "Ich kenne ihren Wert, Junge. Das sind verschiedene Dinge. Aber was weiß so einer wie du schon davon? Na gut, kommen wir zur Sache. Wollt ihr alles über mich wissen? Bitte sehr. Ich wurde auf einem Bauernhof geboren, in der Nähe von Eastbourne – einem kleinen Städtchen an der Küste des Ärmelkanals – im Jahr 1611. Vielleicht ein Jahr früher oder später – meine Mutter hat die Daten ständig durcheinandergebracht, was nicht verwundert, wenn man bedenkt, wie viel Schnaps sie in sich reingeschüttet hat.";
			link.l1 = "Schwere Kindheit? Verstehe.";
			link.l1.go = "WildRose_Rupert_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_21":
			dialog.text = "Wenn du’s unbedingt hören willst – dann halt den Mund und hör zu, mach keine Witze. Einen Vater hatte ich nicht, und ich wusste nicht mal warum – aber im Gegensatz zu dir, Töchterchen, war’s mir auch völlig egal. Der Nachname, den ich von ihm geerbt hab, hat mir gereicht. Als ich dreizehn war, sind eines Nachts Dunkirker Freibeuter an der Küste gelandet. Ja-a, heute erinnert sich daran keiner gern, aber damals haben nicht nur die Holländer was abbekommen – auch wir, die wir an der Ostküste vom alten England gelebt haben.";
			link.l1 = "Hab davon gehört. Diese Kerle haben wirklich niemanden verschont. Wie hast du es geschafft, zu überleben?";
			link.l1.go = "WildRose_Rupert_22_1";
			link.l2 = "Ich weiß von ihren Gräueltaten. Sie haben niemanden verschont – weder Alte noch Kinder. Umso erstaunlicher, dass du da lebend rausgekommen bist.";
			link.l2.go = "WildRose_Rupert_22_2";
		break;

		case "WildRose_Rupert_22_1":
			dialog.text = "In jener Nacht hat dieses papistische Gesindel mehrere Höfe niedergebrannt, auch unseren. Ich konnte mich noch rechtzeitig retten, aber meine Mutter, die sich so mit Cidre vollgestopft hatte, dass sie ihren fetten Hintern nicht mehr aus dem Bett bekam, ist einfach darin verbrannt. Sie war natürlich selbst schuld – aber trotzdem war sie meine Mutter.";
			link.l1 = "Und dann hast du alle Papisten gehasst, ja, gell?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_22_2":
			dialog.text = "In jener Nacht hat dieses papistische Gesindel mehrere Höfe niedergebrannt, auch unseren. Ich selbst konnte noch entkommen, aber meine Mutter, die sich so mit Cidre vollgestopft hatte, dass sie ihren fetten Hintern nicht mehr aus dem Bett bekam, ist einfach darin verbrannt. Sie war natürlich selbst schuld – aber sie war eben trotzdem meine Mutter.";
			link.l1 = "Und dann habt ihr alle Papisten gehasst?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_23":
			dialog.text = "Damals habe ich den Hunger gehasst, Witzbold. Du kennst das wahrscheinlich gar nicht, aber ich hab ihn am eigenen Leib gespürt – und zwar voll und ganz. Ich bin in den Norden gegangen, in die Hauptstadt, und habe mich bei der Marine anheuern lassen – dort gab’s mehr Peitschenhiebe als Essen, aber ein paar Dutzend davon haben gereicht, um mich zur Vernunft zu bringen. Danach bin ich reingewachsen – und ich habe das Leben auf dem Schiff lieben gelernt. Zumal es nie langweilig wurde...";
			link.l1 = "Ja, das glaube ich dir gern. Der Ruhm der englischen Flotte eilt ihr voraus.";
			link.l1.go = "WildRose_Rupert_24";
		break;

		case "WildRose_Rupert_24":
			dialog.text = "Im Jahr 1633 habe ich die Prüfung zum Leutnant bestanden und wurde auf die Brigg 'Cornwall' versetzt.";
			link.l1 = "Unter das Kommando von Joshua Casper.";
			link.l1.go = "WildRose_Rupert_26";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_26":
			dialog.text = "Oh ja-aa. Joshua Casper... So ein Mistkerl ist auf der ganzen verdammten Flotte kaum zu finden, ja, gell? So viele Jahre sind vergangen, und dieses Schwein verfolgt mich immer noch in meinen Träumen.";
			link.l1 = "Wodurch hat er sich denn hervorgetan? Hat er euch wegen übermäßigen Eifers zu einer außerplanmäßigen Wache verdonnert – oder war er heimlich ein Papist, ja, gell?";
			link.l1.go = "WildRose_Rupert_27";
		break;

		case "WildRose_Rupert_27":
			dialog.text = "Dieser grausame Bastard hat die Mannschaft so hart gedrillt, dass die Leute vor Erschöpfung über Bord kippten. Wenn du seinen Namen kennst und weißt, dass er Kommandant der 'Cornwall' war, hast du sicher auch seine Unterlagen gesehen – glänzend wie ein frisch geleckter Katzenarsch.\nUnser heroischer Joshua hatte eine ganze Schatulle voller Auszeichnungen. Viele naive Bengel wie du wollten unter ihm dienen – denn man muss zugeben, er hat euch Froschfresser gemäht wie eine scharfe Sichel das nasse Gras nach einem Regenschauer – aber wer einmal auf der 'Cornwall' war, hat seinen Irrtum sehr schnell begriffen.\nWir waren es tödlich leid, das zu ertragen, "+pchar.lastname+". Manche haben sogar Petitionen für Versetzun
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_28";
		break;

		case "WildRose_Rupert_28":
			dialog.text = "Den Hintern lecken konnte er schon damals – und vielleicht hätten er und Kasper sich sogar zusammengetan, ja, gell? Aber das habe ich nicht zugelassen. Ich habe den kleinen Johnny reingelegt, und der völlig ahnungslose Joshua hat ihn dann vor Wut mit seinem Stock windelweich geprügelt.";
			link.l1 = "Eine echte Demütigung für einen Offizier. Und Lawson hat alles seinem Vater erzählt, ja, gell?";
			link.l1.go = "WildRose_Rupert_32";
		break;

		case "WildRose_Rupert_32":
			dialog.text = "Und ob. Aber siehst du, das System kann sich nicht selbst fressen. Die Sache wurde nie öffentlich gemacht – Lawson wurde eine vorzeitige Beförderung angeboten, und Joshua samt der 'Cornwall' verschwanden in der Versenkung – wir wurden aus London nach Plymouth versetzt, in den Süden Englands. Wir hätten euch Froschfresser weiterhin das Fürchten lehren können, aber die 'Cornwall' wurde zu einem Versorgungsschiff umfunktioniert, das militärische Güter nach Dundalk brachte – so ein kleines irisches Nest.";
			link.l1 = "Und dort hast du Teresa getroffen, ja, gell?";
			link.l1.go = "WildRose_Rupert_33";
		break;

		case "WildRose_Rupert_33":
			dialog.text = "Beim allerersten Mal, als wir dort anlegten. Teresa O’Fatt war, wie ich schon sagte, Kellnerin in einer der Tavernen vor Ort. Drei Tage haben uns gereicht, um zu begreifen – wir waren füreinander bestimmt. Ich denke, da wirst du mich auch verstehen, "+pchar.lastname+", ja, gell?";
			link.l1 = "Wahrscheinlich schon, ja, gell?";
			link.l1.go = "WildRose_Rupert_34_1";
			link.l2 = "Wenn man Sie jetzt so ansieht, würde man nicht denken, dass Ihnen das Wort 'Liebe' etwas sagt.";
			link.l2.go = "WildRose_Rupert_34_2";
		break;

		case "WildRose_Rupert_34_1":
			dialog.text = "Niemanden Schöneren habe ich je getroffen – weder davor noch in all den zwanzig Jahren danach. Wahrscheinlich habe ich mich zum ersten Mal in meinem Leben wirklich glücklich gefühlt, und sie auch – wie sie behauptete.";
			link.l1 = "Und du hast ihr angeboten, mit dir zu gehen?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Rupert_34_2":
			dialog.text = "Niemanden Schöneren habe ich je getroffen – weder davor, noch in all den zwanzig Jahren danach. Wahrscheinlich habe ich mich zum ersten Mal in meinem Leben wirklich glücklich gefühlt, und sie auch – wie sie behauptete.";
			link.l1 = "Und Sie haben ihr vorgeschlagen, mit Ihnen zu gehen?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_35":
			dialog.text = "Natürlich nicht – das war unmöglich, denn die 'Cornwall' blieb ein Kriegsschiff mit einem Mistkerl von Kapitän an der Spitze. Nach einer Woche, die uns wie eine Ewigkeit vorkam, segelte unsere Brigg zurück nach Plymouth. Nach Dundalk kehrten wir erst zwei Monate später zurück – und Teresa überraschte mich mit der Nachricht: Sie war schwanger.";
			link.l1 = "Ja, das passiert eben, wenn man ein Mädchen ins Bett bringt, ja, gell?";
			link.l1.go = "WildRose_Rupert_36";
		break;

		case "WildRose_Rupert_36":
			dialog.text = "Mach keinen auf schlau, Froschfresser. Teresa hat an meiner Schulter geweint, und ich habe überlegt, was ich tun soll. Ich wollte bei ihr bleiben, wirklich sehr – aber schon damals hatte ich das Gefühl, dass von diesem Kind nichts Gutes zu erwarten ist\nIch habe versucht, Teresa zu überreden, es loszuwerden, solange es noch nicht zu spät war – aber stattdessen habe ich mir einen noch heftigeren Wutanfall eingehandelt. Was wir dann tun sollten, wussten wir nicht – wir beschlossen, noch zwei Monate abzuwarten, bis zur nächsten Rückkehr der 'Cornwall' nach Dundalk, denn zu diesem Zeitpunkt hatte das Admiralität noch keinen Groll gegen Casper aufgegeben.";
			link.l1 = "Und ihr habt sie auf die 'Cornwall' geschleppt?";
			link.l1.go = "WildRose_Rupert_37";
		break;

		case "WildRose_Rupert_37":
			dialog.text = "Die Entscheidung musste schnell getroffen werden. Mir war klar, dass Casper keine Frau an Bord dulden würde, und ich hatte vor, in der Nacht nach dem Auslaufen ein Beiboot zu stehlen und damit nach Dublin zu gelangen, das dann gerade an unserer Steuerbordseite liegen würde.";
			link.l1 = "Und was ist passiert? Haben sie euch erwischt?";
			link.l1.go = "WildRose_Rupert_38";
		break;

		case "WildRose_Rupert_38":
			dialog.text = "Theresa wurde früher entdeckt. Casper hatte sich bereits einen ordentlichen Schluck Whiskey gegönnt und war deshalb taub für jegliche Bitten, befahl einfach, das Mädchen über Bord zu werfen. Auf all mein Flehen lachte er sich nur schlapp – verdammt, ich erzähle das, und in meinem Kopf klingt immer noch sein Gelächter...";
			link.l1 = "Und da habt ihr beschlossen, eine Meuterei anzuzetteln?";
			link.l1.go = "WildRose_Rupert_39";
		break;

		case "WildRose_Rupert_39":
			dialog.text = "Ich hatte keine andere Wahl. Ich riss dem Wachposten neben mir die Pistole aus dem Gürtel und blies diesem Mistkerl ein Loch in die Stirn. An Bord brach sofort ein Gemetzel aus – niemand mochte den Kapitän, aber die Angst vor dem Kriegsgericht war größer. Es kostete fast ein Drittel der Mannschaft das Leben – als wir endlich wieder zu uns kamen, war das gesamte Deck der 'Cornwall' mit Blut überzogen und mit den Leichen unserer toten Kameraden übersät.";
			link.l1 = "Nach so etwas habt ihr natürlich beschlossen, nicht nach England zurückzukehren. Dort würde euch alle der Strick erwarten.";
			link.l1.go = "WildRose_Rupert_40";
		break;
		
		case "WildRose_Rupert_40":
			dialog.text = "Ich war mir sicher, dass ich die 'Cornwall' über den Ozean bringen würde. Hier kannte niemand unsere Gesichter, und das gab uns die Chance, ein neues Leben zu beginnen. Die anderen Offiziere zu überzeugen, war nicht besonders schwer – es lag weniger an meinem Ansehen als am Inhalt von ein paar Truhen, von denen die einfachen Matrosen nichts wussten. Die Mannschaft entschied: Joshua Casper musste am Leben bleiben. Wir, eine Handvoll Offiziere, beschlossen, uns etwas Zeit zu verschaffen und eine der Truhen zu opfern.\nAber irgendein Mistkerl hat vom zweiten Schatz ausgeplaudert – und das hat die Mannschaft gespalten.";
			link.l1 = "Haben sie jetzt gegen euch Meuterei angezettelt?";
			link.l1.go = "WildRose_Rupert_45";
		break;

		case "WildRose_Rupert_45":
			dialog.text = "Nein, aber die Zahl derer, die unserem ruhmreichen König weiter dienen wollten, ist stark zurückgegangen. Auch diejenigen, die bereit waren, sich den Piraten anzuschließen, waren nicht viele. Also haben wir einen Mittelweg gefunden – wir beschlossen, in einem der französischen Häfen vor Anker zu gehen. Dort wollten wir das Schiff verkaufen, das Geld untereinander aufteilen, sowohl das, das wir dafür bekamen, als auch das aus der Truhe, und danach – sollten sich unsere Wege trennen.";
			link.l1 = "Und es war Ihnen egal, dass Sie unter diesen von Ihnen so verhassten Katholiken leben mussten?";
			link.l1.go = "WildRose_Rupert_46";
		break;

		case "WildRose_Rupert_46":
			dialog.text = "Mir war es schon egal, wo wir an Land gehen würden: Teresa hielt sich zwar tapfer, aber sie fühlte sich genau so wie jede schwangere Frau nach drei Monaten ununterbrochenen Schaukelns. Und wie schon vor drei Monaten hatte ich nichts gegen die Gesellschaft von Katholiken – Hauptsache, ich war bei ihr.";
			link.l1 = "Aber im Nordwesten der Karibik gibt es keine und gab es nie französische Siedlungen.";
			link.l1.go = "WildRose_Rupert_47";
		break;

		case "WildRose_Rupert_47":
			dialog.text = "Als die Situation an Bord der 'Cornwall' ihren Siedepunkt erreichte, hatten wir bereits die halbe Strecke mit Rückenwind zurückgelegt, der es uns nun nicht mehr erlaubte, Kurs auf Saint Christopher zu nehmen...";
			link.l1 = "Und ihr habt Tortuga als Ziel gewählt?";
			link.l1.go = "WildRose_Rupert_48";
		break;

		case "WildRose_Rupert_48":
			dialog.text = "In jenen Jahren war sie noch ein einfaches Dorf. Um eine mögliche Verfolgung durch die Behörden hinauszuzögern, haben wir das Namensschild am Heck des Brigs ausgetauscht – so wurde aus der 'Cornwall' die 'Wrangler', ja, gell?";
			link.l1 = "Aber irgendwie habt ihr es nie bis zur Schildkröteninsel geschafft. Ihr könnt euch doch nicht so sehr im Kurs geirrt haben, dass ihr statt Tortuga westlich von Kuba gelandet seid?";
			link.l1.go = "WildRose_Rupert_49";
		break;

		case "WildRose_Rupert_49":
			dialog.text = "Nur damit du’s weißt, ich bin eine erfahrene Steuermann – viel besser als viele andere, ja, gell? Es gab keinen Fehler, wir haben den Kurs genau nach Norden gehalten. Aber kaum waren wir in der Windward Passage, da kam ein fürchterlicher Sturm auf. Bis heute frage ich mich, durch welches Wunder wir nicht an der kubanischen Küste zerschellt sind, sondern daran entlanggetrieben wurden, ja, gell?..";
			link.l1 = "Ein wahres Wunder – anders kann man es nicht sagen.";
			link.l1.go = "WildRose_Rupert_50";
		break;

		case "WildRose_Rupert_50":
			dialog.text = "Ich hielt die schluchzende Teresa fest an mich gedrückt und flehte inständig zum Herrn, uns Rettung zu schicken. Und Er hat wirklich geholfen, aber wie, ja, gell?";
			link.l1 = "Ihr seid auf der Insel der Gerechtigkeit angespült worden.";
			link.l1.go = "WildRose_Rupert_51";
		break;

		case "WildRose_Rupert_51":
			dialog.text = "Gerechtigkeit – oh ja! Beim Aufprall auf das Riff ist die 'Wrangler' in zwei Hälften gebrochen, hat aber auf wundersame Weise genug Auftrieb behalten, um bis zu den übereinandergeschobenen anderen Schiffen zu treiben. Der Sturm tobte noch fast zwei Tage weiter, und als er sich endlich legte, wurden wir von den Bewohnern dieser elenden kleinen Insel gerettet.";
			link.l1 = "Euch, Teresa und noch zwei Matrosen. Was danach geschah, können wir uns vorstellen. Erzählen Sie lieber, wie Sie aus dem Gefängnis entkommen und die Insel verlassen haben.";
			link.l1.go = "WildRose_Rupert_63";
		break;

		case "WildRose_Rupert_63":
			dialog.text = "Sie hätten mich besser damals erschossen... Hätte ich nur gewusst, was noch auf mich zukommt, hätte ich mich selbst an die Gitter gekettet und keinen Schritt mehr gemacht.";
			link.l1 = "War es auf der Tartane etwa nicht so bequem wie auf der Brigg, ja, gell? "+npchar.name+"?";
			link.l1.go = "WildRose_Rupert_64_1";
			link.l2 = "Sagt bloß nicht, dass ihr auch noch auf einer Tartane in einen Sturm geraten seid, ja, gell?";
			link.l2.go = "WildRose_Rupert_64_2";
		break;

		case "WildRose_Rupert_64_1":
			dialog.text = "Die Tartanen? Ha-ha-ha... Ja-a-a, das war mein Plan. Ich dachte, ich hätte Glück gehabt. Der Leiter der Gefängniswache war ein ehemaliger Offizier der britischen Marine, der Mitgefühl für mein Schicksal zeigte. Er war es, der mir von den Tartanen der kubanischen Schmuggler erzählte – und auch davon, dass man mich hinrichten wollte. Vielleicht konnte man ihn einen ehrenhaften Mann nennen – er bot mir von sich aus an, mich freizulassen, damit ich mein Schicksal selbst in die Hand nehme.";
			link.l1 = "Ich verstehe nicht... Wenn nicht auf den Tartanen, wie habt ihr dann die Insel verlassen?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_64_2":
			dialog.text = "Die Tartanen? Ha-ha-ha... Ja-a-a, das war mein Plan. Ich dachte, ich hätte Glück gehabt. Der Leiter der Gefängniswache war ein ehemaliger Offizier der britischen Marine, der Mitgefühl für mein Schicksal zeigte. Er war es, der mir von den Tartanen der kubanischen Schmuggler erzählte – und auch davon, dass man mich hinrichten wollte. Vielleicht konnte man ihn einen ehrenhaften Mann nennen – er bot mir von sich aus an, mich freizulassen, damit ich mein Schicksal selbst in die Hand nehme.";
			link.l1 = "Ich verstehe nicht... Wenn nicht mit den Tartanen, wie habt ihr dann die Insel verlassen?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Rupert_68":
			dialog.text = "Wenn du mal die Klappe hältst und zuhörst, wirst du es verstehen. Ich bin zu den Tartanen gesegelt, lange gesegelt – bis ich hinter der Regenwand ein Licht gesehen habe. Das war etwas vollkommen Unglaubliches, verdammt noch mal. Es leuchtete wie die Sonne auf dem Deck eines der halb versunkenen Galeonen, und ich steuerte darauf zu. Noch ahnte ich nicht, dass ich gerade den schlimmsten Fehler meines Lebens machte. Ich kletterte über die Bordleiter aus dem Wasser – und stand direkt vor dem Licht. Es funkelte über einer goldenen Statue und...";
			link.l1 = "Der Kukulkan-Idol. Ja, damals war die ‚San Jeronimo‘ noch nicht gesunken...";
			link.l1.go = "WildRose_Rupert_69";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_69":
			dialog.text = "Also hast du ihn auch gesehen, ja, gell? "+pchar.lastname+"?";
			link.l1 = "Ich habe ihn nicht nur gesehen. Ich habe mich mit seiner Hilfe durch den Raum bewegt, und zwar mehrmals.";
			link.l1.go = "WildRose_Rupert_70";
		break;

		case "WildRose_Rupert_70":
			dialog.text = "Du lügst! Mehrmals, sagst du?! Wie kannst du dann hier stehen, so voller Gesundheit?!";
			link.l1 = "Nachdem ich mich fortbewegt hatte, habe ich einen indianischen Trank getrunken, der hat mir geholfen, am Leben zu bleiben und wieder zu Kräften zu kommen, ja, gell?";
			link.l1.go = "WildRose_Rupert_71";
		break;

		case "WildRose_Rupert_71":
			dialog.text = "Ach so, darum geht's also. Weißt du eigentlich, wie lange ich meine Kräfte wiederhergestellt habe? Weißt du das?!";
			link.l1 = "Ich kann es mir denken. Ihr habt die Statue berührt, und sie hat euch nach Dominica gebracht – ins Indianerdorf, dort wurdet ihr der Statue geopfert und seid dann auf dem Main gelandet, ja, gell?";
			link.l1.go = "WildRose_Rupert_72";
		break;

		case "WildRose_Rupert_72":
			dialog.text = "Ganz genau. So einen Schmerz wie damals, als ich bei jener Statue lag, hatte ich noch nie erlebt. Ich weiß nicht, womit man das vergleichen kann. Vielleicht, wenn ein Steinhaus auf dich einstürzt – selbst dann ist es wohl nicht so schlimm. Kaum kam ich wieder zu mir, sah ich schon, wie erneut eine Gruppe Eingeborener auf mich zukam. Wenn ich ihre Sprache gesprochen hätte – ich schwöre, ich hätte sie angefleht, mich auf der Stelle zu töten.";
			link.l1 = "Waren das Miskito-Indianer aus dem Dorf in der Nähe, ja, gell?";
			link.l1.go = "WildRose_Rupert_76";
		break;

		case "WildRose_Rupert_76":
			dialog.text = "Genau die. Sie haben mich in eine der Hütten geschleppt, wo mir ein seltsamer Eingeborener, der ihnen nicht ähnlich sah, irgendetwas direkt in den Mund gegossen hat. Der Schmerz ließ etwas nach, ging aber nicht ganz weg. Am Abend zerrten sie mich ans Feuer, und dieser bemalte Halunke begann irgendein Ritual abzuhalten. Elender Bastard.";
			link.l1 = "Zmeiiny Glaz... Ihr hättet ihm für die Rettung eures Hinterns dankbar sein sollen.";
			link.l1.go = "WildRose_Rupert_77";
		break;

		case "WildRose_Rupert_77":
			dialog.text = "Rettung?.. Drei Jahre, "+pchar.lastname+". Drei Jahre lang lag ich fast regungslos da, habe unter mich gemacht und bin in meinem eigenen Erbrochenen aufgewacht – weil ich all diese stinkenden Brühen und Tinkturen, die man mir gewaltsam eingeflößt hat, einfach nicht mehr ertragen konnte! Und dann habe ich fast ein weiteres Jahr gebraucht, um wieder laufen zu lernen.";
			link.l1 = "Eine herzzerreißende Geschichte. Aber ehrlich gesagt, ich habe sogar Mitleid mit euch, ja, gell?";
			link.l1.go = "WildRose_Rupert_78";
		break;

		case "WildRose_Rupert_78":
			dialog.text = "Steck dein Mitleid deinem Papa in seinen fetten katholischen Hintern. Ich brauche kein Mitleid von irgendwem. Soll ich weitermachen, oder brauchst du eine Pause zum Heulen, du Grünschnabel?";
			link.l1 = "An Manieren hat euch diese Reise bestimmt nicht bereichert. Aber gut, für Mary halte ich das aus. Auch wenn wir das Wichtigste wohl schon erfahren haben – hören wir euch trotzdem bis zum Ende zu, ja, gell?";
			link.l1.go = "WildRose_Rupert_79";
		break;

		case "WildRose_Rupert_79":
			dialog.text = "Als ich mich irgendwie wieder auf die Beine gestellt hatte, verließ ich dieses verfluchte Dorf und gelangte an die Küste, zur Amatique-Bucht. Dort traf ich auf Schmuggler, deren Schiff in der Nähe vor Anker lag, und schloss mich ihnen an, indem ich mich als Rupert Casper ausgab – auf meinen Vornamen wollte ich nicht verzichten, aber auch den Nachnamen eines der Schuldigen an all meinem Unglück behielt ich. Damit ich nie vergesse, warum ich hier gelandet bin.";
			link.l1 = "Alle anderen sind bei Ihnen schuld, Northwood... Nur Sie selbst nicht. Aber man kann es ja verstehen – Jahre voller Demütigungen und Qualen, jetzt sitzen Sie hier in diesen Wäldern. Da kann man schon mal durchdrehen, ja, gell?";
			link.l1.go = "WildRose_Rupert_80_1";
			link.l2 = "Ihr habt viel durchgemacht, Northwood – das kann man nicht bestreiten. Und nun seid ihr hier... In den Wäldern, am Rand der Zivilisation. Man könnte hier verrückt werden...";
			link.l2.go = "WildRose_Rupert_80_2";
		break;

		case "WildRose_Rupert_80_1":
			dialog.text = "Ich bin der Herr dieser Wälder, "+pchar.lastname+". In über fünfzehn Jahren habe ich es vom erbärmlichen Matrosen auf einem Schmuggler­schiff bis zu ihrem Anführer gebracht. Nicht zum Kapitän irgendeines Kähns – sondern zum Herrn der ganzen Küste, von der Amatique-Bucht bis zur Bucht des Verderbens.";
			link.l1 = "Nun, das ist wirklich eine würdige Wiederauferstehung, das muss ich zugeben.";
			link.l1.go = "WildRose_Rupert_81";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_80_2":
			dialog.text = "Ich bin der Herr dieser Wälder, "+pchar.lastname+". In über fünfzehn Jahren habe ich mich vom armseligen Matrosen auf einem Schmuggler­schiff bis zu ihrem Anführer hochgearbeitet. Nicht zum Kapitän irgendeines Schiffchens – sondern zum Herrscher über die ganze Küste, von der Amatique-Bucht bis zur Bucht des Verderbens.";
			link.l1 = "Nun, das ist wirklich eine würdige Wiederauferstehung, das muss ich zugeben.";
			link.l1.go = "WildRose_Rupert_81";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "WildRose_Rupert_81":
			dialog.text = "Manche sagen, hier sei das Reich des Waldteufels... Eine freche Lüge – das ist mein Land. Und Svensson weiß das, haha. Er hat mehr als einmal seine Leute hergeschickt, wollte meine Identität herausfinden – und keiner von ihnen ist zu ihm zurückgekehrt. Zumindest nicht lebendig, hehe. Nur an einer Hand kann man die zählen, die den Namen kennen, unter dem ich meine Schmugglerkarriere begonnen habe, und wissen, wo ich in diesen Wäldern lebe.";
			link.l1 = "Also nennt ihr euch jetzt anders. Jetzt ist mir klar, warum die Nachricht, dass jemand nach Rupert Casper sucht, euch so in Panik versetzt hat.";
			link.l1.go = "WildRose_Rupert_82";
		break;
		
		case "WildRose_Rupert_82":
			dialog.text = "Panik? Meinst du das ernst, Junge? Hier gerät nur einer in Panik – und das bist du, auf meinem Gebiet, umgeben von meinen Leuten, völlig in meiner Hand! Ich kann mit dir machen, was ich will. Und mit ihr auch – einfach nur, weil sie der Grund für all das Elend ist, das ich durchmachen musste!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_82_add";
		break;

		case "WildRose_Rupert_82_add":
			StartInstantDialog("Mary", "WildRose_Rupert_83", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_83":
			dialog.text = "Du bist verrückt, einfach nur verrückt, ja, gell? Ich kenne kein Heilmittel und keinen Arzt, der dich heilen könnte, Rupert Northwood! Du hast schreckliche Qualen durchgemacht, aber... wie kannst du mir die Schuld an allem geben?!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_83_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_83_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_84", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_84":
			dialog.text = "Ich hab’s doch schon gesagt – ohne dich wäre das alles nie passiert. Gib’s einfach zu, ja, gell?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_84_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_84_add":
			StartInstantDialog("Mary", "WildRose_Rupert_85", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_85":
			dialog.text = "...";
			link.l1 = "Lass ihn, "+npchar.name+". Wir haben genug gehört. Manche Wege sollte man wirklich nicht bis zum bitteren Ende gehen. Ich hatte ein ungutes Gefühl, als wir beschlossen haben, das alles durchzuziehen. Aber ich habe nicht darauf gehört. Schade eigentlich.";
			link.l1.go = "WildRose_Rupert_85_add";
		break;
		
		case "WildRose_Rupert_85_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_86", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_86":
			dialog.text = "Ja-a-a, dann wärt ihr beide jetzt nicht hier, hilflos in der Falle. Spür es jetzt selbst am eigenen Leib, Tochter, was ich damals durchmachen musste!";
			link.l1 = "Und wer hat dir gesagt, dass wir machtlos sind, irgendetwas zu unternehmen? Truu-u-u-pp, zum Kampf!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_20");
		break;
		
		case "WildRose_Rupert_87":
			dialog.text = "Was ist los, Kleiner? Hast du jemanden verloren? Ha-ha-ha... Ha-ha-ha. HA-HA-HA-HA-HA-HA!!! Oh, wenn du dein Gesicht jetzt sehen könntest, Dummkopf! Hey, Mason, bring mein Geschenk für unsere Gäste her.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_22");
		break;
		
		case "WildRose_Rupert_88":
			dialog.text = "...";
			link.l1 = "Schuft! Wo sind meine Leute?";
			link.l1.go = "WildRose_Rupert_89";
		break;
		
		case "WildRose_Rupert_89":
			dialog.text = "Meinst du diese Handvoll Dummköpfe, die dachten, sie könnten mir auflauern? Mein Freund, der Wirt, hat mich rechtzeitig über deine Ankunft in der Stadt informiert, und ich habe sie dann entsprechend empfangen... Einigen ist tatsächlich die Flucht gelungen. Aber mach dir keine Sorgen – einen habe ich lebend erwischt. Damit du mit eigenen Augen sehen kannst, welches Schicksal euch heute erwartet.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_25");
			
			// WildRose_Etap6_LifeAfterDeath_24_1();
		break;
		
		case "WildRose_Rupert_90":
			dialog.text = "Schuft! Dafür wirst du bezahlen! (weint) Ich schwöre es, ja, gell!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_29");
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Alonso_11":
			dialog.text = "...";
			link.l1 = "Alonso! Wie sehr freue ich mich, dich zu sehen!";
			link.l1.go = "WildRose_Alonso_12";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_12":
			dialog.text = "Und ich freue mich auch so sehr, euch zu sehen, Käpt’n! Irgendein Schuft hat diesem Halunken gesteckt, dass ihr ihn sucht — und wir wurden auf halbem Weg von einer Ladung Kartätschen empfangen. Mir und ein paar Jungs ist es gelungen, uns zurückzuziehen, und wir sind so schnell wir konnten in den Hafen gerannt, um zu warnen. Zum Glück hat der Wachposten, sobald er mich auf dem Kahn gesehen hat, den ich hastig in der Stadt gekauft habe, gleich verstanden, was los ist. Er hat schnell Leute zusammengerufen – und wir sind sofort hierher geeilt, um zu helfen.";
			link.l1 = "Vielen Dank, Freund. Du hast uns vor dem sicheren Tod gerettet.";
			link.l1.go = "WildRose_Alonso_13";
		break;

		case "WildRose_Alonso_13":
			dialog.text = "Kleinigkeiten. Was machen wir jetzt, Käpt’n?";
			link.l1 = "Sammle die Leute und geht zum Schiff. Mary und ich brauchen etwas Zeit für uns allein.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		case "WildRose_Mary_261":
			dialog.text = "Mein Gott, "+pchar.name+"... Ich kann es immer noch nicht fassen, einfach nicht glauben. Mein Vater... Er ist ein Monster... Warum tut er mir das an? Ist er wirklich völlig verrückt geworden?";
			link.l1 = "Er musste schreckliche Qualen durchmachen. Die Meuterei auf der 'Cornwall', die Flucht über den Atlantik, der Sturm und der Tod deiner Mutter. Ich kann mir nicht vorstellen, wie er die Reise durch die Portale dieser Idole ohne den Trank der Komantschen überstanden hat – aber genau das hat seinen Verstand zerstört.";
			link.l1.go = "WildRose_Mary_262";
			locCameraFromToPos(-3.80, 1.10, 52.00, false, 0.61, 0.27, 49.69);
			LAi_ActorAnimation(pchar, "sharle_mary_sit", "", 50.0);
			LAi_ActorAnimation(npchar, "sharle_mary_sit", "", 50.0);
			CharacterTurnAy(pchar, 6.00);
			CharacterTurnAy(npchar, 6.00);
		break;

		case "WildRose_Mary_262":
			dialog.text = "Und was, wenn er schon immer so war? Oder wenn er genauso ein Halunke war, nur etwas sanfter, aber meine Mutter wirklich geliebt hat? Was, wenn all das nur das freigesetzt hat, was schon immer in ihm steckte? Und wenn das so ist... was, wenn auch in mir etwas von ihm steckt? Das könnte doch sein, "+pchar.name+", ja, gell?";
			link.l1 = "Du hast definitiv etwas von ihm übernommen, ja, gell? "+npchar.name+". Im heutigen Kampf habe ich es gesehen – du kämpfst mit demselben Durchhaltevermögen, demselben Feuer in den Augen und genau derselben Wut wie er. Aber seinen Wahnsinn – den hast du nicht. Du bist ganz anders. Lebendig, offen, mit dem Herzen auf der Zunge. Genau deshalb habe ich mich in dich verliebt. Und offenbar hatte Northwood recht: vom Wesen her kommst du ganz nach deiner Mutter.";
			link.l1.go = "WildRose_Mary_263";
		break;

		case "WildRose_Mary_263":
			dialog.text = "Denkst du das wirklich, Liebling?";
			link.l1 = "Natürlich, Liebste. Wenn ich ihm einfach so begegnet wäre, ohne zu wissen, wer er ist – ich hätte nie gedacht, dass ihr verwandt seid.";
			link.l1.go = "WildRose_Mary_264";
		break;

		case "WildRose_Mary_264":
			dialog.text = "Weißt du, auf der Insel der Gerechtigkeit gibt es gar nicht so viele Vergnügungen. Schon als Kind habe ich das Fechten geliebt – zuerst habe ich mit den Jungs gekämpft, mit Holzstöcken, und später dann auch mit erwachsenen Männern, mit echten Klingen, ja, gell? Ich wollte immer mit ihnen auf Augenhöhe sein... aber irgendwie habe ich mich trotzdem immer schwächer gefühlt, selbst wenn ich gewonnen habe.   Dann bin ich einfach nach Hause zurückgekehrt – und habe weiter geübt. Stundenlang trainiert, bis mir die Hände zitterten, ja, gell? Ist das dieses Feuer? Diese Wut, von der du sprichst?";
			link.l1 = "In gewissem Sinne – ja, gell? Ich glaube, dieses Feuer gibt dir viel mehr Kraft, als du selbst in dir siehst. Und ob du willst oder nicht, das ist ein Geschenk von deinem Vater. Auch wenn er eigentlich nie vorhatte, dir etwas zu schenken.";
			link.l1.go = "WildRose_Mary_265";
			locCameraSleep(false);
			locCameraFromToPos(-1.95, 1.81, 48.29, true, -2.11, -0.04, 52.55);
		break;

		case "WildRose_Mary_265":
			dialog.text = "Denkst du, wir haben das Richtige getan, als wir die Vergangenheit aufgewühlt haben, ja, gell?";
			link.l1 = "Jetzt, wo wir alles erfahren haben... klingt das gar nicht mehr nach so einer guten Idee. Aber wenn du die Wahrheit wissen willst, musst du auch damit rechnen, dass sie dir vielleicht nicht gefällt.";
			link.l1.go = "WildRose_Mary_266";
		break;

		case "WildRose_Mary_266":
			dialog.text = "Du hast recht, "+pchar.name+", ja... Lass uns noch ein bisschen hierbleiben. Ich möchte jetzt nicht zurück aufs Schiff. Ich will einfach nur... hier sitzen, in der Stille.";
			link.l1 = "Natürlich, Liebling. Ich wollte es selbst schon vorschlagen, ja, gell?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_38");
		break;
	}
} 
