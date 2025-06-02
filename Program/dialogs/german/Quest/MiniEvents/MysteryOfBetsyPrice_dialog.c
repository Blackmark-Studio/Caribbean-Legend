void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
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
			dialog.text = "Was wollt Ihr?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";
		break;

		case "Poorman_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "Hey, Schönheit, wie wär’s mit einem exquisiten Schmuckstück für eure Damensammlung? Ein echtes Juwel! Euch – bewundernde Blicke, und mir – ein paar Münzen für Brot und einen Schluck Rum.";
			}
			else
			{
				dialog.text = "Hey, Käpt’n, wie wär’s mit einem exquisiten Geschenk für eure Dame? Ein echtes Juwel! Ihr – ihre warme Dankbarkeit, und ich – ein paar Münzen für Brot und einen Schluck Rum.";
			}
			link.l1 = "Damit in einer Stunde die Soldaten kommen und mich wegen Diebstahls ins Gefängnis stecken? Woher hast du das, Penner?";
			link.l1.go = "Poorman_2_fortune";
			link.l2 = "Ein edles Geschenk? Und wie soll ein Obdachloser wie du an so etwas kommen?";
			link.l2.go = "Poorman_2_leadership";
			if (npchar.quest.meeting == "0") npchar.quest.meeting = "1";
		break;

		case "Poorman_2_fortune":
			dialog.text = ""+GetSexPhrase("Käpt’n, ich","Ich")+" habe dieses wunderschöne Kamee-Amulett gefunden, ehrlich! Soll ich vom Blitz getroffen werden, wenn ich lüge! Es lag einfach da, ohne dass es jemand brauchte. So eine Schönheit lässt man doch nicht im Dreck liegen, oder?";
			link.l1 = "Na gut. Zeig mal, was du da hast.";
			link.l1.go = "Poorman_3";
			link.l2 = "Wer glaubt schon einem so 'ehrenwerten' Herrn wie dir aufs Wort? Such dir jemand anderen, der leichtergläubig ist.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Poorman_2_leadership":
			dialog.text = ""+GetSexPhrase("Käpt’n, ich","Ich")+" habe dieses wunderschöne Kamee-Amulett gefunden, ehrlich! Soll ich vom Blitz getroffen werden, wenn ich lüge! Es lag einfach da, ohne dass es jemand brauchte. So eine Schönheit lässt man doch nicht im Dreck liegen, oder?";
			link.l1 = "Na gut. Zeig mal, was du da hast.";
			link.l1.go = "Poorman_3";
			link.l2 = "Wer glaubt schon einem so 'ehrenwerten' Herrn wie dir aufs Wort? Such dir jemand anderen, der leichtergläubig ist.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Poorman_exit":
			DialogExit();
			AddDialogExitQuestFunction("TBP_PismoVDome");
		break;
		
		case "Poorman_3":
			dialog.text = "Schaut mal... ein feines Stück! Ich habe es im Blumenbeet gefunden, bei dem Haus mit der Laterne, in der Nähe der Taverne. Aber dort ist schon lange niemand mehr, also gibt es niemanden, dem ich es zurückgeben könnte.";
			link.l1 = "Ein interessantes Stück. Und wie viel willst du dafür haben?";
			link.l1.go = "Poorman_4";
		break;

		case "Poorman_4":
			dialog.text = "Nur hundert Pesos"+GetSexPhrase(", Käpt’n","")+"... ein Klacks für jemanden wie Euch! Und für mich – eine ganze Woche ohne Sorgen, wo ich das nächste Stück Brot herbekomme. Schaut nur, wie schön es ist!";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "Na gut, nimm deine hundert Pesos.";
				link.l1.go = "Poorman_5";
			}
			link.l2 = "Ich glaube, ich verzichte. Versuch dein Glück bei jemand anderem.";
			link.l2.go = "Poorman_exit";
		break;

		case "Poorman_5":
			dialog.text = "Danke, "+GetAddress_Form(NPChar)+"! Das Glück wird Euch sicher bald lächeln! Man sieht gleich, Ihr seid ein guter Mensch.";
			link.l1 = "...";
			link.l1.go = "Poorman_exit";
			GiveItem2Character(PChar, "jewelry24");
			pchar.questTemp.TBP_BuyKulon = true;
			pchar.questTemp.TBP_BuyKulonOtdatBetsy = true;
		break;

		case "Pirate_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "Oooh, wer kommt denn da zu uns? Du hast dich wohl nicht in der Tür geirrt, Süße... komm nur rein! Zieh dich aus, fühl dich wie zu Hause.";
				link.l1 = "Na, na... wen haben wir denn da? Seid ihr nicht die Schurken, die Betsy diese 'liebevolle' Drohbotschaft hinterlassen haben?";
			}
			else
			{
				dialog.text = "Was zum Teufel bist du denn für ein Ungetüm?! Hast du dich in der Tür geirrt, Ziegenkopf? Verschwinde, bevor ich dir den Bauch aufschlitze!";
				link.l1 = "Na, na... wen haben wir denn da? Seid ihr nicht die Idioten, die Betsy eine nette kleine Drohung hinterlassen haben?";
			}
			link.l1.go = "Pirate_2";
			PlaySound("Voice/Russian/citizen/Pirati v Gorode-12.wav");
			//PlaySound("Voice/Spanish/citizen/Pirati v Gorode-12.wav");
		break;

		case "Pirate_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "Betsy? Zum Teufel mit dieser Betsy! Viel interessanter ist, was du hier willst, Süße... Jetzt, wo du schon da bist – geh nicht gleich, wir finden schon eine Beschäftigung für dich...";
			}
			else
			{
				dialog.text = "Was zum Teufel für eine Betsy? Versuch dein Glück nicht, Dummkopf. Solange du noch auf deinen eigenen Beinen gehen kannst – geh. Sonst muss man dich in Stücken raustragen!";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_2");
		break;

		case "BetsiPrice_1":
			dialog.text = "Hilfe! Hilfe, ich flehe Euch an!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_3");
			locCameraFromToPos(1.40, 1.62, 1.14, false, 2.58, -0.30, -1.64);
		break;
		
		case "Pirate_3":
			dialog.text = "...";
			link.l1 = "Da ist sie ja. Du steckst bis zum Hals in der Scheiße, Freundchen. Und wenn du nicht willst, dass das dein letzter Fehler war, rate ich dir, sie freizulassen. Sofort.";
			link.l1.go = "Pirate_4";
		break;

		case "Pirate_4":
			dialog.text = "Ha! Hast du das gehört, Reggie? "+GetSexPhrase("Er","Sie")+" droht uns sogar noch. "+GetSexPhrase("Was für ein überheblicher Wurm","Was für eine überhebliche Göre")+". Na los, zeigen wir "+GetSexPhrase("diesem Emporkömmling, welche Farbe seine Gedärme haben","diesem kleinen Biest, was echter Schmerz ist")+".";
			link.l1 = "Das wird euer Schaden sein.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_4");
		break;

		case "Pirate_5":
			if (!CharacterIsAlive("TBP_Bandit_1"))
			{
				dialog.text = "...";
				link.l1 = "Jetzt lass das Mädchen gehen. Oder du landest neben deinem Kumpel.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_HouseBetsi_6");
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Pirate_5";
			}
		break;

		case "BetsiPrice_2":
			dialog.text = "Verdammte Hunde! Dachtet ihr wirklich, ich würde schweigen?!";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_2_1";
			sld = CharacterFromID("TBP_Bandit_2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("TBP_BetsiPrice"));
			CharacterTurnByChr(npchar, sld);
		break;
		
		case "BetsiPrice_2_1":
			dialog.text = "Und du... Du scheinst nicht zu ihnen zu gehören. Wer bist du?";
			link.l1 = "Kapitän "+GetFullName(pchar)+", zu euren Diensten.";
			link.l1.go = "BetsiPrice_2_2";
			CharacterTurnByChr(npchar, pchar);
		break;

		case "BetsiPrice_2_2":
			dialog.text = "Also schulde ich dir mein Leben?";
			link.l1 = "Sieht ganz so aus. Aber wichtiger ist jetzt – wer sind diese Leute und worin bist du da hineingeraten?";
			link.l1.go = "BetsiPrice_3";
		break;

		case "BetsiPrice_3":
			dialog.text = "Diese Leute... Sie wurden von einem wichtigen englischen Beamten geschickt. Früher war er mir sehr nah... und jetzt, wie du siehst, will er meinen Tod.";
			link.l1 = "Ich glaube, ich beginne deine Geschichte zu verstehen. Du warst seine Geliebte, und irgendwann dachtest du, du könntest das zu deinem Vorteil nutzen. Wolltest ihn erpressen... seiner Familie davon erzählen?";
			link.l1.go = "BetsiPrice_4";
		break;

		case "BetsiPrice_4":
			dialog.text = "Du bist erstaunlich nah an der Wahrheit, "+GetSexPhrase("Liebling","Süße")+", und gleichzeitig sehr weit davon entfernt. Wenn das so wäre, wäre ich längst tot. Ja, ich war seine Geliebte, aber ich hätte nie daran gedacht, ein Familiendrama zu inszenieren\nEs war viel komplizierter: Eines Tages fand ich heraus, dass er sich ein neues Spielzeug gesucht hatte und mich einfach loswerden wollte – mich mit leeren Händen zurückzulassen. Einfach wegwerfen wie einen alten Lappen. Aber ich war nie jemand, der mit leeren Händen geht\nAlso nahm ich das, was wirklich von Wert war – Dokumente, die sein Leben ruinieren konnten – und floh in die Neue Welt. Dann bot ich ihm einen Deal an: seine Geheimnisse gegen meine Sicherheit und eine großzügige Entschädigung\nDas ist der Grund, warum ich noch lebe – sie brauchen die Dokumente. Und ich hatte es nicht eilig zu verraten, wo sie versteckt sind.";
			link.l1 = "Du bist nicht nur schön, sondern auch verdammt clever. Du hast mutig gespielt, aber seien wir ehrlich – du hast die Kontrolle über das Spiel verloren. Vielleicht ist es an der Zeit, über einen Ausweg nachzudenken, solange du noch kannst? Wenn sie dich hier gefunden haben, wirst du dich nirgendwo mehr verstecken können. Früher oder später wird dein Glück zu Ende sein.";
			link.l1.go = "BetsiPrice_5";
		break;

		case "BetsiPrice_5":
			dialog.text = "Und was schlägst du vor? Ihm die Dokumente einfach übergeben und mit leeren Händen dastehen? Nach allem, was ich durchgemacht habe?";
			link.l1 = "Du weißt genau, dass du für sie nur ein Problem bist, das aus dem Weg geräumt werden muss. Sie werden nicht aufgeben, bis sie haben, was sie wollen. Aber du hast noch eine Wahl. Gib die Dokumente diesem Trottel da drüben. Er soll sie seinem Herrn bringen und ihm sagen, dass du deine Pläne aufgegeben hast – dass du nur willst, dass das Ganze endlich vorbei ist.";
			link.l1.go = "BetsiPrice_6";
		break;

		case "BetsiPrice_6":
			dialog.text = "Wenn das meine einzige Chance ist... gut, ich bin bereit, das Risiko einzugehen. Ich hatte die Dokumente immer bei mir. Ich habe sie in mein Korsett eingenäht, um mich nie von ihnen zu trennen. Einen Moment...";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_7";
		break;

		case "BetsiPrice_7":
			dialog.text = "Hier, nimm. Das sind alle Dokumente, die ich hatte. Wirst du diesem Mistkerl ein paar Abschiedsworte mitgeben? Du weißt doch, wie man überzeugend"+GetSexPhrase("","e")+" ist, oder?";
			link.l1 = "Ich denke, er hat seine Lektion bereits gelernt. Jetzt muss er nur noch verstehen, was zu tun ist.";
			link.l1.go = "exit";
			notification(StringFromKey("Neutral_15"), "BoxMinus");
			PlaySound("interface\\important_item.wav");
			AddDialogExitQuestFunction("TBP_HouseBetsi_11");
		break;

		case "Pirate_6":
			dialog.text = "...";
			link.l1 = "Hör mir gut zu, Mistkerl. Hier sind die Dokumente, nach denen ihr geschickt wurdet. Bring sie deinem Herrn und sag ihm: Wenn er weiterhin Mörder auf Betsy hetzt, erwartet sie dasselbe Schicksal wie deine Kameraden. Sag ihm, dass sie für immer aus seinem Leben verschwindet – und dass er keinen Grund mehr hat, sie zu verfolgen. Er soll das als ihren freiwilligen Schritt zur Versöhnung verstehen. Ich hoffe, er ist klug genug, das dabei zu belassen. Hast du das verstanden, oder soll ich dir das einprügeln?";
			link.l1.go = "Pirate_7";
			notification(StringFromKey("Neutral_16"), "BoxMinus");
			PlaySound("interface\\important_item.wav");
		break;
		
		case "Pirate_7":
			dialog.text = "Verstanden, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "Dann verschwinde. Und bleib nicht zu lange – du bekommst keine zweite Chance.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_12");
		break;

		case "BetsiPrice_8":
			dialog.text = "Nun, "+GetSexPhrase("mein Held","meine Furie")+", ich glaube, ich habe vergessen, dir zu danken... Das ist wohl die Aufregung. Es ist nicht jeden Tag, dass man gefangen genommen wird und dann durch einen "+GetSexPhrase("mutigen Retter","mutige Retterin")+" die Freiheit zurückerlangt. Sag mal, ist das deine Gewohnheit – Damen in Not zu helfen, oder hatte ich einfach unglaubliches Glück?";
			link.l1 = "Was soll ich sagen, Betsy – ich habe eine Schwäche für dramatische Auftritte und "+GetSexPhrase("schöne Damen","jede Art von Abenteuern")+".";
			link.l1.go = "BetsiPrice_9";
		break;

		case "BetsiPrice_9":
			dialog.text = "Ich heiße Miranda. Miranda Bell. Den Namen Betsy habe ich angenommen, als ich verschwinden musste – neues Leben, neuer Name, du verstehst. Ich bin so hastig aus Europa geflohen, dass ich nur ein paar Münzen und ein paar Schmuckstücke mitgenommen habe\nDer Rest fiel wohl diesen Bastarden in die Hände, die mich jagten. Jetzt statt opulenter Empfänge und edler Kleider – eine armselige Hütte am Stadtrand und ein Job in der Taverne. Ich hätte nie gedacht, dass ich mal Rum ausschenken würde, statt guten Wein in feiner Gesellschaft zu genießen...";
			link.l1 = "Trotz allem wirkst du, als hättest du dein Schicksal fest in der Hand. Vielleicht ist genau das deine wahre Stärke.";
			link.l1.go = "BetsiPrice_10";
		break;

		case "BetsiPrice_10":
			dialog.text = ""+GetSexPhrase("Schmeichler. Aber weißt du – dir steht das","Du schmeichelst mir")+"... Nach all dem ist mir irgendwie mulmig zumute. Was, wenn jemand schon um die Ecke auf mich wartet? Begleite mich nach Hause, bleib noch ein wenig mein "+GetSexPhrase("Retter","Retterin")+".";
			link.l1 = "Ich bin keiner, der etwas auf halbem Weg abbricht. Also, meine Dame – ich bin zu euren Diensten. Gehen wir.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma");
		break;

		case "BetsiPrice_11":
			dialog.text = "Da sind wir also. Weißt du, ich habe dich gar nicht gefragt, was dich in dieses Haus geführt hat?";
			link.l1 = "Ich bin dort nicht zufällig gelandet. Der Wirt war ziemlich besorgt über dein Verschwinden und bat mich, nach dir zu sehen. Wie hätte ich ablehnen können? Eine Dame in Not zurückzulassen – das wäre eines Kapitäns unwürdig.";
			link.l1.go = "BetsiPrice_12";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulonOtdatBetsy") && pchar.questTemp.TBP_BuyKulonOtdatBetsy == true)
            {
			link.l2 = "Ich bin dort nicht zufällig gelandet. Dieser Anhänger hat mich dorthin geführt. Nimm ihn.​ Der Wirt war ziemlich besorgt über dein Verschwinden und bat mich, nach dir zu sehen. Wie hätte ich ablehnen können? Eine Dame in Not zurückzulassen – das wäre eines Kapitäns unwürdig.​";
			link.l2.go = "BetsiPrice_12_otdal_kulon";
			}
		break;

		case "BetsiPrice_12":
			dialog.text = "Oh, das ist so ehrenhaft von dir, Kapitän "+pchar.name+"! Was den Wirt angeht – ich bin mir sicher, dass er sich mehr um seine Einnahmen als um mich gesorgt hat. Leider kann ich dich heute nicht einladen – ich muss mich erst erholen. Die Zeit im Keller hat mich sicher nicht schöner gemacht. Aber wenn wir uns nicht wiedersehen – das werde ich dir nicht verzeihen. Komm morgen in die Taverne. Ich habe etwas für dich... ein Geschenk.";
			link.l1 = "Dann habe ich jetzt einen Grund mehr, vorbeizuschauen. Bis bald, M... Betsy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
		break;
		
		case "BetsiPrice_12_otdal_kulon":
			dialog.text = "Oh, das ist so ehrenhaft von dir, Kapitän "+pchar.name+"! Was den Wirt angeht – ich bin mir sicher, dass er sich mehr um seine Einnahmen als um mich gesorgt hat. Leider kann ich dich heute nicht einladen – ich muss mich erst erholen. Die Zeit im Keller hat mich sicher nicht schöner gemacht. Aber wenn wir uns nicht wiedersehen – das werde ich dir nicht verzeihen. Komm morgen in die Taverne. Ich habe etwas für dich... ein Geschenk.";
			link.l1 = "Dann habe ich jetzt einen Grund mehr, vorbeizuschauen. Bis bald, M... Betsy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
			TakeItemFromCharacter(pchar, "jewelry24");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "TBP_Helena_1":
			dialog.text = "Na sowas... Was für ein herzlicher Abschied. Wer ist denn diese zerzauste Dame? Sieht aus, als hätte sie eine Woche im Keller gesessen, aber selbst das hat dich nicht davon abgehalten, sie mit Blicken zu verschlingen, oder, "+pchar.name+"?";
			link.l1 = "Das ist nicht, was du denkst. Sie war in einer schwierigen Lage, und ich habe ihr einfach geholfen. Mehr nicht.";
			link.l1.go = "TBP_Helena_2";
		break;

		case "TBP_Helena_2":
			dialog.text = "Und du hast natürlich beschlossen, ihr Ritter in glänzender Rüstung zu sein?";
			link.l1 = "Du weißt doch, ich kann nicht einfach wegsehen, wenn jemand in Gefahr ist.";
			link.l1.go = "TBP_Helena_3";
		break;
		
		case "TBP_Helena_3":
			dialog.text = "Gut. Aber beim nächsten Mal, "+pchar.name+", sei vorsichtiger... und gib mir keinen Grund, eifersüchtig zu sein.";
			link.l1 = "Natürlich, Liebling. Lass uns gehen, wir haben noch viel zu tun.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;

		case "TBP_Mary_1":
			dialog.text = "Na sowas... Was für ein herzlicher Abschied. So viel Fürsorge, so viele zärtliche Versprechen... Du hast sie sogar liebevoll beim Namen genannt, stimmt’s, ja, gell? Vielleicht sollte ich auch ein paar Tage verschwinden, damit du mich mit genauso viel Eifer suchst?";
			link.l1 = "Mary, du weißt doch, du bist mein Kompass. Und sie... sie war nur ein Mädchen in Not.";
			link.l1.go = "TBP_Mary_2";
		break;

		case "TBP_Mary_2":
			dialog.text = "Ach, natürlich! Nur ein armes Ding, das einen Ritter braucht! Und dein Blick – das war auch nur aus Höflichkeit? Du hast sie fast mit den Augen ausgezogen!";
			link.l1 = "Mary, du übertreibst! So wie ich dich ansehe – siehst du den Unterschied? Oder soll ich dich daran erinnern... etwas näher?";
			link.l1.go = "TBP_Mary_3";
		break;

		case "TBP_Mary_3":
			dialog.text = "Na gut, "+pchar.name+", dieses Mal kommst du nochmal davon, ja, gell. Aber wenn ich so eine Szene noch einmal sehe...";
			link.l1 = "Dann muss ich dich erneut daran erinnern, wer den ersten und einzigen Platz in meinem Herzen einnimmt. Komm, Liebling, wir haben noch viel zu tun.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;

		case "BetsiPrice_sex_1":

			switch (rand(1))
			{
				case 0:
					dialog.text = "Mmm... Du kannst dir nicht vorstellen, welche Gedanken mir durch den Kopf gehen, wenn ich dir so nahe bin... Und wie sehr ich sie in die Tat umsetzen will.";
					link.l1 = "Dann hör auf, nur daran zu denken... und zeig mir jeden einzelnen davon.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Ah, mein "+GetSexPhrase(" Lieber","e Liebe")+"... Du hast keine Ahnung, wie schwer es mir fällt, mich zu beherrschen, wenn du in der Nähe bist...";
					link.l1 = "Dann ist es genug mit dieser süßen Folter... Komm zu mir...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_3");
		break;

		case "BetsiPrice_sex_2":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Ah, "+GetSexPhrase("mein süßer Kapitän","meine süße "+pchar.name)+"... Ich bin noch ganz in diesem süßen Wahnsinn gefangen.";
					link.l1 = "Vielleicht ist dieser Wahnsinn es wert, sich daran zu erinnern... oder ihn irgendwann zu wiederholen.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Oh, "+pchar.name+"... Wenn ich sage, es war großartig, wirst du dann nicht allzu eingebildet"+GetSexPhrase("","e")+"?";
					link.l1 = "Nur wenn du versprichst, es mir noch einmal zu sagen... im Flüsterton.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_7");
		break;

		
		
		
		
		
		
		
	}
}