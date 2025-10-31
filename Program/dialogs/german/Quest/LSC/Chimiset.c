// колдун ривадос - Чимисет
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Brauchst du etwas?";
			link.l1 = "Nein, vergiss es.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-------------------------------------в тюрьме на Тартарусе-----------------------------
		// вариант R
		case "KillChad":
			dialog.text = "Warte! Halt... Ich bitte dich, mir zuzuhören, bevor du einen Fehler machst.";
			link.l1 = "Ich höre zu... Ich hoffe, dass du ein vernünftiges Argument hast, um mich davon abzuhalten...";
			link.l1.go = "KillChad_1";
			LAi_RemoveCheckMinHP(npchar); //убираем проверяльщик, если ещё есть
		break;
		
		case "KillChad_1":
			dialog.text = "Vom Töten mich, richtig? Ich habe dich mit Chad oben sprechen gehört und ich mache dir keinen Vorwurf - jeder würde wahrscheinlich das Gleiche tun. Aber du irrst dich zu denken, dass Chad dich nach dem Töten von mir gehen lassen wird.";
			link.l1 = "Hm... Interessant, und warum nicht? Das einzige, was ich weiß, ist, dass ich ins Schwitzen kommen muss, um hier rauszukommen, wenn ich dich nicht einfach umbringe.";
			link.l1.go = "KillChad_2";
		break;
		
		case "KillChad_2":
			dialog.text = "Du wirst überhaupt keine Zukunft haben, wenn du mich tötest. Hör zu, die Narwale und Chad wollen mich loswerden, aber sie haben zu viel Angst vor mir, um das selbst zu tun - mein Mörder wird für immer verflucht sein. Also wollen sie, dass du die ganze Drecksarbeit machst\nChad weiß, dass du kein Rivado bist, er verarscht dich. Sobald du mich tötest - werden sie dasselbe mit dir tun und deine Leiche benutzen, um den Hai zu täuschen.";
			link.l1 = "Hai? Steve Dodson? Ist er tatsächlich hier? Und erklären Sie mir endlich - wer zum Teufel sind diese Rivados?";
			link.l1.go = "KillChad_3";
		break;
		
		case "KillChad_3":
			dialog.text = "Heh, es sieht so aus, als würdest du hier tatsächlich nicht leben... Aber es ist nicht die richtige Zeit, um Geschichten zu erzählen. Wir müssen uns selbst retten. Ich habe einen Plan.";
			link.l1 = "Weißt du was, Zauberer, ich habe kürzlich eine Reise durch irgendein mystisches Portal gemacht und bin gerade so davongekommen, daher machen mir deine Flüche keine Angst. Ich habe genug - es ist Zeit, dich zu erledigen.";
			link.l1.go = "KillChad_fightfail";
			link.l2 = "Gut, ich vertraue dir. Was ist der Plan?";
			link.l2.go = "KillChad_4";
		break;
		
		case "KillChad_fightfail":
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "afraid", "", -1);
			LAi_SetImmortal(npchar, false);
			pchar.quest.LSC_fightfail.win_condition.l1 = "NPC_Death";
			pchar.quest.LSC_fightfail.win_condition.l1.character = "Chimiset";
			pchar.quest.LSC_fightfail.function = "LSC_Fightfail_Final";
		break;
		
		case "KillChad_4":
			dialog.text = "Da drüben ist eine Truhe. Sie enthält anständige Waffen und Tränke. Sie ist verschlossen, aber das Schloss ist alt und beschädigt, also finde einen Brechstange, um es zu öffnen\nNimm alles aus der Truhe, bewaffne dich und gehe zur Treppe. Es ist eine gute defensive Position, sie werden gezwungen sein, dich einzeln zu bekämpfen, pass einfach auf die Musketiere auf\nIch hoffe, du bist gut mit einem Schwert, ich bin zu alt, um dir im Kampf zu helfen. Wenn es dir gelingt, sie alle zu töten und dabei zu überleben - garantiere ich dir den Schutz der Rivados, meiner Familie...";
			link.l1 = "Gut. Betet zu euren Göttern für mich - der Kampf wird hart. Die Jungs da oben sehen wirklich ernst aus.";
			link.l1.go = "KillChad_5";
		break;
		
		case "KillChad_5":
			DialogExit();
			pchar.quest.LSC_fightfail.over = "yes"; //снять прерывание
			LAi_SetImmortal(npchar, true);
			ref location = &Locations[FindLocation(pchar.location)];
			location.private1.key = "crowbar";
			location.private1.key.delItem = true;
			NextDiag.CurrentNode = "KillChad_6";
		break;
		
		case "KillChad_6":
			dialog.text = "Verschwende keine Zeit! Breche das Schloss schnell auf...";
			link.l1 = "Ja, ja, ich bin auf dem Weg.";
			link.l1.go = "exit";
			NextDiag.TempNode = "KillChad_6";
		break;
		
		case "Chad_die":
			dialog.text = "Gut gemacht! Du bist wirklich der Meister des Fechtens. Ich schulde dir, Fremder. Sag mir, wie ist dein Name?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+". Und wie ist deins?";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "Mein Name ist Chimiset, ich bin ein Rivados-Schamane und Berater unseres Häuptlings - Black Eddie. Er wird sich freuen zu wissen, dass du mich befreit und mein Leben gerettet hast. Du bist ein Freund von Chimiset, Black Eddie und allen Rivados. Von nun an wirst du immer ein willkommener Gast auf unserem Beschützer sein...";
			link.l1 = "Warte... Chimiset, falls du es immer noch nicht verstanden hast, ich bin erst vor ein paar Stunden hier angekommen. Kannst du mir erklären, wo ich bin, wer die Rivados sind und wo ich Shark Dodson finden kann?";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "Dieser Ort wird die Stadt der verlassenen Schiffe genannt. Obwohl es eher wie Spott klingt. Es ist nicht viel von einer Stadt. Dieser Ort ist eine Insel, die aus Hunderten von toten Schiffen besteht. Das Zentrum ist bewohnbar. Es wird von Menschen bewohnt, die die unerklärlichen Schiffbrüche überlebt haben, die durch Stürme verursacht wurden, die sie hierher geführt haben\nRivados ist ein Clan, eine Gruppe von Menschen, die schon lange zusammenleben. Es gibt auch drei andere Gruppen, die hier leben: der Narwal-Clan, sie sind unsere Feinde, Piraten von Shark Dodson und gewöhnliche Leute. Shark ist im Grunde der Kopf der Insel, er nennt sich selbst einen Admiral\nEr ist recht kürzlich angekommen und hat auf gewaltsame Weise die Macht ergriffen. Er hat die 'San Augustine' erobert, wo wir unsere Lebensmittelvorräte lagerten. Jetzt müssen wir Proviant zu den Preisen kaufen, die Shark vorgibt. Es scheint, dass Sie bereits in diesem Lagerhaus waren\nChad Kapper war Sharks Bootsmann und Leiter des Gefängnisses. Layton Dexter war Sharks Erster Offizier, er hat auch einige Macht. Diese drei und ihre Piraten sind eine dominierende Kraft auf der Insel, die sowohl den Rivados als auch den Narwalen gegenübersteht.";
			link.l1 = "Warum wollte Chad Kapper, dass ich dich töte?";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "Chad hat Kontakte zu den Narwalen, unseren Feinden, aufgebaut. Er wollte Shark mit ihrer Hilfe töten und seinen Platz einnehmen. Die Narwale hegen einen Groll gegen den Admiral wegen des Todes von Alan Milrow, ihrem ehemaligen Anführer. Sie glauben, dass Shark für seinen Tod verantwortlich ist, aber sie irren sich. Ich weiß, wer es getan hat. Chad war es. Ich bin der einzige Zeuge dieses Verbrechens\nDeshalb konnte Chad mich nicht frei lassen, doch er fürchtete sich auch, mir zu schaden. Piraten sind furchtlos in Schlachten, aber sie sind sehr abergläubisch. Also wollte er dich benutzen. Chad und die Narwale hätten Shark getötet und die Rivados beschuldigt.";
			link.l1 = "Ist das so? Erzähl mir warum...";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = ""+pchar.name+", mein Freund, wir reden später. Wir müssen uns beeilen, bevor die Piraten des Sharks auftauchen. Durchsuche Chads Körper und nimm seine Schlüssel. Aber zuerst, überprüfe seinen Schreibtisch, er könnte interessante Papiere dort haben\nGeh zu Shark Dodson, du wirst ihn in der 'San Augustine' finden, einem großen Schiff, das in einiger Entfernung von den anderen abgestürzt ist, es gibt eine Brücke, die von dem Schiff namens 'Pluto' zu ihr führt. Sag ihm, dass Chad eine Verrat geplant hat, und sag, dass die Narwale hinter all dem stecken, und wir, die Rivados, haben nichts damit zu tun.\nIch gebe dir gerne alle Informationen, die du über diese Insel, über meinen Clan und andere, benötigst, sobald du in unserer Residenz im Protector ankommst. Lass uns hier raus!";
			link.l1 = "Gut, Chimiset. Ich werde dich später am... 'Beschützer' finden. Lass uns hier raus!";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "Noch eine Sache. Unsere Schiffe, einschließlich des 'Protector', sind für Fremde gesperrt. Du musst ein Rivado sein oder ein Passwort kennen, um einzutreten. Ich würde es dir sagen, aber es ändert sich jede Woche und ich bin schon zu lange hier, also kenne ich das aktive Passwort nicht\n Du solltest zuerst die 'San Augustine' besuchen. Ich werde unseren Leuten sagen, wer du bist, während du mit Shark sprichst, werden sie dich erwarten. Aber geh jetzt nicht zum 'Protector', sprich zuerst mit Shark, und lass mich zuerst meine Leute treffen, sonst werden die Rivados feindselig gegenüber dir sein";
			link.l1 = "Ich verstehe. Ich gehe nach 'San Augustine'. Auf Wiedersehen!";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.LSC_LetterChad.win_condition.l1 = "item";
			pchar.quest.LSC_LetterChad.win_condition.l1.item = "letter_chad";
			pchar.quest.LSC_LetterChad.function = "LSC_LetterChad_Find";
			sld = characterFromId("SharkMush_17");
			sld.lifeday = 0;
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("SharkSold_1"+(i+3));
				sld.lifeday = 0;
			}
			AddSimpleRumourCityTip("Ha, they say that you are a friend of clan Rivados. This is interesting. Congratulations...", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that you have saved the Rivados wizard Chimiset from 'Tartarus'. Now you are a welcome guest on their ships.", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("So it was you who has set Chimiset free! Interesting. Now you are a friend of Rivados but an enemy of Narwhals. I am not sure whether to congratulate you or to sympathize...", "LostShipsCity", 5, 1, "LSC", "");
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "Was willst du von mir, Fremder?";
			link.l1 = "Dein Name ist Chimiset, richtig?";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "Ja, das bin ich. Haben Sie ein Anliegen oder möchten Sie nur plaudern?";
			link.l1 = "Ich habe ein Geschäft zu besprechen. Ich komme hier vom Admiral, Shark Dodson. Ich habe einen Befehl mitgebracht, Sie freizulassen, aber unter einer Bedingung: Sie müssen mehrere meiner Fragen beantworten.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "Hat Dodson beschlossen, mich freizulassen? Das freut mich zu hören. Stellen Sie Ihre Fragen. Ich hoffe, dass es keine List darin gibt, sonst wäre meine Aufregung umsonst gewesen.";
			link.l1 = "Keine Tricks, ich brauche nur deine Hilfe. Sag mir, Chimiset, gibt es auf dieser Insel eine seltsame Steinidol? Es verwandelt sich um Mitternacht in Gold. Halte mich nicht für verrückt...";
			link.l1.go = "Friend_2";
		break;
		
		case "prisoner_3":
			dialog.text = "Noch mehr Fragen?";
			link.l1 = "Ja. Kennen Sie einen Mann namens der Weiße Junge?";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "Weißer Junge? Sicher, ich kenne ihn. Das ist der Spitzname von Olle Christiansen, unserem örtlichen Idioten. Er ist jetzt ein Erwachsener und sieht nicht mehr wie ein Junge aus, obwohl sein Verstand immer noch kindlich ist.";
			link.l1 = "Ist das so? Sag mir, wo kann ich ihn finden?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "Überall in unserer Stadt. Er konnte oft im Geschäft, in der Taverne oder auf der Straße gefunden werden. Er hat weißes Haar, du wirst ihn erkennen.";
			link.l1 = "Ausgezeichnet! Noch eine Frage: Haben Sie hier einen Mann namens Nathaniel Hawk getroffen? Er muss vor einiger Zeit hier aufgetaucht sein und könnte ernsthaft krank sein.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			dialog.text = "Ich kann Ihnen dabei nicht helfen, Fremder. Ich kenne keinen Mann mit diesem Namen. Ich kann Ihnen versichern, dass er nicht auf den Schiffen der Rivados ist, noch sollte er im neutralen Gebiet sein. Das Gleiche kann ich allerdings nicht über die Gebiete der Narwale sagen, die Rivados besuchen sie nicht.";
			link.l1 = "Nun, danke trotzdem... Du hast mir sehr geholfen, Chimiset!";
			link.l1.go = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "Das ist es? Wird Shark mich jetzt freilassen?";
			link.l1 = "Ja. Ich habe nichts anderes zu fragen. Chad Kapper wird dich befreien. Nun, ich muss gehen...";
			link.l1.go = "prisoner_8";
		break;
		
		case "prisoner_8":
			dialog.text = "Halt! Warte... Komm zurück.";
			link.l1 = "Hast du mir noch etwas zu erzählen?";
			link.l1.go = "prisoner_9";
		break;
		
		case "prisoner_9":
			dialog.text = "Nicht genau... (senkt die Stimme) Ich sehe, dass du nicht einer von Kappers Männern bist. Vertraue ihm nicht. Er ist ein dreckiges Gesindel. Vor nicht allzu langer Zeit tötete er den unbewaffneten Alan Milrow mit einem Breitschwert. Er war der Anführer des Narwal-Clans. Ich habe es nicht kommen sehen, Chad kam einfach zu seiner Zelle und exekutierte ihn. Außerdem habe ich Gerüchte gehört, dass sogar die eigenen Männer des Admirals planen, ihn zu ermorden. Erzähle Shark davon. Und sag ihm, dass ich mehr sagen werde, wenn wir von Angesicht zu Angesicht sprechen.";
			link.l1 = "Hm. Gut, ich werde Dodson davon erzählen. Wir sehen uns!";
			link.l1.go = "prisoner_10";
		break;
		
		case "prisoner_10":
			DialogExit();
			sld = characterFromId("Capper");
			sld.quest.chimiset_talk = "true"; // разговор с Чимисетом состоялся
			if (!CheckAttribute(npchar, "quest.capper_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_10"; // ноду Акуле
			LSC_SetWhiteBoy(); // поставим белого мальчика
			NextDiag.CurrentNode = "prisoner_11";
			AddQuestRecord("SharkHunt", "20");
		break;
		
		case "prisoner_11":
			dialog.text = "Geh zu Shark und erzähl ihm alles, was ich dir erzählt habe. Eh, ich hoffe, sie öffnen diesen Käfig bald...";
			link.l1 = "Ja, ja. Ich bin auf dem Weg.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_11";
		break;
		
		//------------------------беседа на Протекторе, если был старт через Тартарус-----------------
		case "Friend":
			dialog.text = "Da bist du ja, mein lieber Freund. Nochmals vielen Dank, dass du mich gerettet und mir vertraut hast, anstatt Kapper. Ich werde dir diese Amulette als Belohnung geben. Ich bin sicher, dass du sie nützlich finden wirst.";
			link.l1 = "Danke! Das habe ich nicht erwartet...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			GiveItem2Character(pchar, "indian_1");
			GiveItem2Character(pchar, "indian_11");
			GiveItem2Character(pchar, "amulet_1");
			PlaySound("interface\important_item.wav");
			dialog.text = "Und jetzt bin ich bereit, Ihnen zuzuhören. Sie wollten mich etwas fragen, habe ich recht?";
			link.l1 = "Du hast recht, Chimiset. Ich brauche deine Hilfe. Zuerst muss ich wissen, gibt es auf dieser Insel ein seltsames Steinidol? Es verwandelt sich um Mitternacht in Gold. Halte mich nicht für verrückt...";
			link.l1.go = "Friend_2";
		break;
		
		// нода пересечения
		case "Friend_2":
			dialog.text = "Aye, ich verstehe, was du meinst, mein Freund. Mit meinen eigenen Augen habe ich diese Statue von indischen Göttern gesehen. Obwohl sie nur unter den Strahlen der Morgensonne zu Gold wird, und nicht unter dem Mond... viele Male haben wir böse Narwale geopfert und der Gott hat sie alle verschlungen. Aber sie ist nicht mehr auf der Insel.";
			link.l1 = "Wie ist es nicht?! Sagst du, dass es plötzlich verschwunden ist?!";
			link.l1.go = "Friend_3";
		break;
		
		case "Friend_3":
			dialog.text = "Nicht ganz so. Diese Statue war im 'San Geronimo'. Dieses Schiff sank vor mehreren Jahren mit der Statue.";
			link.l1 = "So ein Pech! Es scheint, dass es jetzt unmöglich ist, die Insel zu verlassen... Und wo war dieses Schiff?";
			link.l1.go = "Friend_4";
		break;
		
		case "Friend_4":
			dialog.text = "Nicht weit von den Narwal-Territorien, in der Nähe der Wracks des Schiffes namens 'Phoenix'. An einem guten Tag kann man das Schiff auf dem Meeresgrund liegen sehen.";
			link.l1 = "Ha! Also liegt es auf der Untiefe? Dann kann ich ja hin schwimmen...";
			link.l1.go = "Friend_5";
		break;
		
		case "Friend_5":
			dialog.text = "You can't, my friend. First, it's too deep down there; second, there are many giant crabs. They will tear you apart before you get to the 'San Geronimo'.";
			link.l1 = "Hm. Gut, ich werde darüber nachdenken. Zumindest weiß ich, dass die Statue existiert, und das ist das Wichtigste.";
			if (CheckAttribute(npchar, "quest.chimiset_die")) link.l1.go = "prisoner_3";
			else
			{	
				if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_1";
				else link.l1.go = "Friend_6";
			}
			AddQuestRecord("LSC", "4");
		break;
		// нода пересечения
		
		case "Friend_6":
			dialog.text = "Ich sehe, dass Sie noch mehr Fragen haben. Zögern Sie nicht zu fragen, mein Freund.";
			link.l1 = "Hai Dodson hat mich gebeten, Chads Komplizen im Verbrechen zu finden. Ich habe einen Brief in Chads Truhe gefunden. Dort steht etwas von einem Scharfschützen und einer Waffe. Es sieht so aus, als wollten sie Hai aus der Ferne ermorden. Fällt Ihnen dazu etwas ein?";
			link.l1.go = "Friend_7";
		break;
		
		case "Friend_7":
			dialog.text = "Hm. Sie wollen den Admiral erschießen? Ich muss nachdenken... Die Sache ist, der Admiral verlässt seine Residenz fast nie und wenn er das tut, wird er von einem halben Dutzend Piraten geschützt. Aber er hat eine Gewohnheit, er spaziert gerne spät abends um das Heck herum\nEs gibt zwei Positionen für einen Scharfschützen, um in die Residenz des Admirals zu schießen - der Bug der 'Santa Florentina' und ein Mast der 'Fury'. Aber selbst von diesen Positionen aus könnte ein Scharfschütze den Admiral nicht töten, er müsste ein adleräugiger Schütze sein, um einen solchen Schuss abzugeben. Außerdem bräuchte er ein ausgezeichnetes Gewehr. Du solltest dich auf der Insel umhören, wer Zugang zu solchen Feuerwaffen hat.";
			link.l1 = "Heh, es sieht so aus, als hättest du recht, es steht etwas über eine Pistole im Brief... Hast du jemanden mit einer solchen Pistole gesehen?";
			link.l1.go = "Friend_8";
		break;
		
		case "Friend_8":
			dialog.text = "Nein. Ich habe in meinem Leben noch nie eine solche Waffe gesehen. Frag die Leute, vielleicht kann dir jemand etwas sagen.";
			link.l1 = "Gut... Wie auch immer, deine Informationen sind wertvoll, danke! Nun, die letzte Frage jetzt, obwohl ich nicht erwarte, dass du antwortest... Hast du vom Weißen Jungen gehört?";
			link.l1.go = "Friend_9";
		break;
		
		case "Friend_9":
			dialog.text = "Weißer Junge? Sicher, ich kenne ihn. Das ist der Spitzname von Olle Christiansen, unserem örtlichen Idioten. Er ist jetzt erwachsen und sieht nicht mehr wie ein Junge aus, obwohl sein Verstand immer noch kindisch ist.";
			link.l1 = "Ist das so? Sag mir, wo kann ich ihn finden?";
			link.l1.go = "Friend_10";
		break;
		
		case "Friend_10":
			dialog.text = "Überall in unserer Stadt. Er ist oft im Laden, in der Kneipe oder auf den Straßen zu finden. Er hat weißes Haar - du wirst ihn sicher erkennen.";
			link.l1 = "Großartig! Danke, Chimiset, du hast mir sehr geholfen!";
			link.l1.go = "Friend_11";
		break;
		
		case "Friend_11":
			dialog.text = "Ich helfe immer gerne! Komm und besuche mich, wenn du weitere Fragen hast.";
			link.l1 = "Sicher! Ich muss jetzt gehen. Bis dann!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_2";
			else link.l1.go = "Friend_12";
		break;
		
		case "Friend_12":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
			pchar.questTemp.Saga.SharkHunt = "search_mush_1"; // флаг на магазин - поиск мушкета
			AddQuestRecord("SharkHunt", "11");
		break;
		
		case "freedom":
			dialog.text = "Und da ist mein lieber Freund, dem ich meine Freiheit und vielleicht sogar mein Leben verdanke. Danke, dass du meinen Brüdern geholfen hast, mich vor diesem schmutzigen Kapper zu retten. Als Belohnung gebe ich dir diese Amulette. Ich bin sicher, dass du sie nützlich finden wirst.";
			link.l1 = "Danke! Das habe ich nicht erwartet...";
			link.l1.go = "Friend_1";
		break;
		
		case "freedom_1":
			dialog.text = "Hast du noch etwas zu fragen, weißer Freund?";
			link.l1 = "Sag mir, Chimiset, kennst du den Weißen Jungen?";
			link.l1.go = "Friend_9";
		break;
		
		case "freedom_2":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
		break;
		
		//--> информационный блок
		case "Chimiset_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Oh! Mein weißer Freund "+pchar.name+"! Bist du nicht ertrunken? Die Geister haben dich gerettet, das weiß ich...";
				link.l1 = "Ich bin wohlauf und lebendig, Chimiset. Geister? Vielleicht hast du recht, all dies ist wegen Kukulcan passiert...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "Was führt dich hierher, mein guter Freund?";
			/*if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l1 = "Sag mir, wie der Anführer der Narwale gestorben ist. Du warst der einzige, der das gesehen hat.";
				link.l1.go = "story";
			}*/
			if (!CheckAttribute(npchar, "quest.crab"))
			{
				link.l2 = "Sie haben die Krabben am Grund in der Nähe der 'San Geronimo' erwähnt. Können Sie diese Monster beschreiben?";
				link.l2.go = "crab";
			}
			link.l9 = "Nichts Besonderes, Chimiset. Ich wollte dich nur sehen.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "story":
			dialog.text = "Hier wird eine Geschichte über den Tod von Alan Milrow geschrieben.";
			link.l1 = "Gut!";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "crab":
			dialog.text = "Niemand weiß, woher sie kamen und warum sie eine so gigantische Größe erreicht haben. Wir wissen nicht viel über diese Bestien. Sie existieren, viele Leute haben sie gesehen. Gruppen von ihnen sind zu finden unter den Wracks von Schiffen in flachen Gewässern. Sie lauern auf dem Meeresboden, jagen Fische und fressen allen Müll, den wir wegwerfen\nSie sind eine echte Bedrohung. Ihre Scheren können ernsthafte Wunden verursachen, auch ihr Gebiss setzt ein gefährliches Gift frei, ähnlich dem Gift von Meerfischen. Wenn man vergiftet und unbehandelt bleibt, wird ein Mann seinen Schöpfer treffen. Glücklicherweise kann das Toxin durch ein Gegenmittel aus einheimischen Kräutern neutralisiert werden\nEs gab unter uns einen Krabbenjäger. Er brachte ihr Fleisch mit, ein verdammt leckeres Gericht. Aber das Wichtigste: Er brachte oft die Scheren dieser Monster und Gebisse mit Gift mit. Sie waren die Hauptzutaten in einigen meiner Tränke. Schade, es ist lange her, dass mir jemand davon gebracht hat...";
			link.l1 = "Und wo ist dieser Jäger jetzt?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "Nimm den Hinweis an. Du musst bereit sein, selbst zur Beute zu werden, während du diese Bestien jagst. Eines Tages kam er einfach nicht zurück. Deshalb warne ich dich, vorsichtig und aufmerksam bei diesen Kreaturen zu sein.";
			link.l1 = "Ich sehe...";
			link.l1.go = "exit";
			npchar.quest.crab = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		//<-- информационный блок
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
