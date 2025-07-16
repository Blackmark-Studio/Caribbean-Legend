// Хосе Диос - картограф
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Wünschen Sie etwas?";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "dios")
			{
				link.l3 = TimeGreeting()+"! Sag mir, bist du Jose Dios, der Kartograph?";
				link.l3.go = "island";
			}
			link.l1 = "Nein, nichts.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;
		
		case "island":
			dialog.text = "Ja, das bin ich. Ich kenne Sie nicht, Senor. Was wollen Sie von mir?";
			link.l1 = "Mein Name ist "+GetFullName(pchar)+" und ich wurde von Jan Svenson geschickt. Erinnerst du dich an ihn?";
			link.l1.go = "island_1";
		break;
		
		case "island_1":
			dialog.text = "Ach, Senor Svenson! Natürlich erinnere ich mich an ihn! Kommen Sie, machen Sie es sich bequem... Wie geht es dem angesehenen Jan?";
			link.l1 = "Danke, es geht ihm gut. Senor Dios, ich brauche Ihre Hilfe. Ich möchte mit Ihnen über eine Angelegenheit sprechen, mit der Sie aufgrund Ihres Berufes vertraut sein müssen. Jan hat Sie als Geographieexperten für die Karibikregion empfohlen...";
			link.l1.go = "island_2";
		break;
		
		case "island_2":
			dialog.text = "Ich höre zu, Senor. Was möchten Sie über die Geographie des Archipels wissen?";
			link.l1 = "Man sagt, es gäbe eine Insel oder eine andere Formation nordwestlich von Havanna, zwischen Kuba und dem Golf von Mexiko. Diese Insel wurde noch nie auf irgendeiner Karte verzeichnet. Ich würde gerne wissen, wie vertrauenswürdig diese Gerüchte sind.";
			link.l1.go = "island_3";
		break;
		
		case "island_3":
			dialog.text = "Hm... Sie haben etwas angesprochen, das mich schon seit vielen Jahren beschäftigt. Dieser Ort, den Sie erwähnt haben, zieht schon lange die neugierigen Köpfe der Geographen an, aber niemand war jemals mutig genug, diese Region zu erforschen.";
			link.l1 = "Warum?";
			link.l1.go = "island_4";
		break;
		
		case "island_4":
			dialog.text = "Die Sache ist, dass dieser Ort eine Art natürliche Anomalie ist. Die Wahrscheinlichkeit von Stürmen in dieser Region ist viel höher als irgendwo anders. Vielleicht liegt der Grund in der kalten Meeresströmung, aber das ist nur meine Hypothese. Viele Schiffe sind dort verschwunden und das war genug, um die Seeleute diesen Ort meiden zu lassen, alle Hauptseewege führen sowieso weit an dieser Region vorbei.";
			link.l1 = "Ich nehme an, dass Sie auch die Wahrheit nicht kennen...";
			link.l1.go = "island_5";
		break;
		
		case "island_5":
			dialog.text = "Genau, Senor. Aber ich habe ein paar historische Dokumente und einige materielle Beweise, also habe ich allen Grund, eine hohe Wahrscheinlichkeit für die Existenz dieses Ortes zu vermuten.";
			link.l1 = "Können Sie mir mehr erzählen?";
			link.l1.go = "island_6";
		break;
		
		case "island_6":
			dialog.text = "Sicher. Das wichtigste Beweisstück ist das historische Dokument mit Auszügen aus dem Tagebuch von Kapitän Alvarado, der die Insel im Jahr 1620 besucht hat. Eine ziemlich interessante Geschichte, sage ich Ihnen!";
			link.l1 = "Kapitän Alvarado? Das ist das zweite Mal, dass ich diesen Namen höre...";
			link.l1.go = "island_7";
		break;
		
		case "island_7":
			dialog.text = "Ich bin nicht überrascht. Die Geschichte von Kapitän Alvarado ist seit Jahren Teil der Folklore. Sie hat sich verändert, wurde mit Gerüchten, Lügen und Träumen gefüllt, und so ist sie entstanden - die Legende von der Insel der verlassenen Schiffe.\nKlatsch kann sich ändern, aber Papier und Tinte können es nicht, sie bleiben über Hunderte von Jahren intakt. Hier, lesen Sie diese Geschichte - vielleicht hilft sie Ihnen, das zu enthüllen, was Sie suchen.";
			link.l1 = "Danke! Haben Sie noch etwas?";
			link.l1.go = "island_8";
		break;
		
		case "island_8":
			dialog.text = "Es gibt eine Theorie, dass der Meeresboden in diesem Gebiet hoch genug ansteigt, um eine riesige Untiefe zu bilden. Und ich habe bereits die Strömung erwähnt. Laut den Gesprächen der Seeleute gibt es auch eine große Ansammlung von Möwen und anderen Seevögeln.\nAlvorado nannte Namen von Schiffen, die Teil des Geschwaders von Admiral Francisco Betancourt waren, einem Geschwader, das vor mehr als fünfzig Jahren verloren ging. Ich bezweifle, dass dies nur ein Zufall ist...";
			link.l1 = "Ich werde zu meinem Schiff zurückkehren und Alvarados Notizen sorgfältig durchlesen. Danke für Ihre Hilfe, Senor Dios!";
			link.l1.go = "island_9";
		break;
		
		case "island_9":
			dialog.text = "Bitte sehr. Eigentlich habe ich Ihnen gar nicht geholfen, Sie haben nicht die Koordinaten des Ortes und ich auch nicht. Ich kann nicht einmal beweisen, dass dort eine bewohnte Insel existiert. Aber soweit ich verstehe, beabsichtigen Sie, dieses Gebiet zu erkunden?\nWenn ja, dann sei Ihnen bewusst, dass ich wirklich dankbar für jegliche Information wäre, besonders wenn sie mit materiellem Beweis versehen ist. Es scheint, dass Sie ein wohlhabender Mann sind, aber ich werde einen Weg finden, Sie zu entlohnen.";
			link.l1 = "Gut. Dann haben wir einen Deal, Senor Dios. Vielleicht werden meine Notizen auch in der Zukunft von jemandem gelesen... Und vielleicht wird sogar jemand eine Legende schreiben...";
			link.l1.go = "island_10";
		break;
		
		case "island_10":
			dialog.text = "Warum nicht? Senor "+pchar.name+", Ich sehe, dass Sie ein abenteuerlustiger Mann sind, der viel reist, also möchte ich Sie bitten, etwas zu tun.";
			link.l1 = "Ja? Ich höre zu.";
			link.l1.go = "island_11";
		break;
		
		case "island_11":
			dialog.text = "Sie wissen, dass ich Kartograph bin. Also, ich habe zwei Jahre lang Karten des karibischen Archipels gezeichnet, um den Admiralsatlas für den Vizekönigswettbewerb von Nueva Granada zu erstellen. Aber alle meine vierundzwanzig Karten wurden auf unverschämteste Weise aus meinem Haus gestohlen, während ich von Piraten gefangen genommen wurde, von denen senor Svenson mich gerettet hat.\nIch bin sicher, dass der Angriff von einem meiner Konkurrenten organisiert wurde, um meine Karten zu erwerben. Es ist schon lange her, aber ich habe keine einzige Karte aus meinem Set wieder gesehen.";
			link.l1 = "Ich verstehe. Sie möchten, dass ich Ihre Karten suche.";
			link.l1.go = "island_12";
		break;
		
		case "island_12":
			dialog.text = "Genau. Vielleicht werden Sie sie auf Ihren zukünftigen Abenteuern finden. Sie sind leicht zu erkennen - mein Zeichen ist auf jeder einzelnen von ihnen. Ich werde Sie großzügig belohnen, wenn Sie es wie durch ein Wunder schaffen, alle vierundzwanzig Karten zu sammeln.";
			link.l1 = "Gut. Ich werde ab jetzt jede Karte, die ich im Archipel finde, aufmerksam betrachten. Nun, ich muss jetzt gehen. Danke für das interessante Gespräch und für das Dokument.";
			link.l1.go = "island_13";
		break;
		
		case "island_13":
			DialogExit();
			AddQuestRecordInfo("LSC_Alvorado", "1");
			AddQuestRecord("SharkHunt", "4");
			pchar.questTemp.Saga.SharkHunt = "LSC";
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			pchar.questTemp.AdmiralMap = "true";
		break;
		
		case "Dios":
			dialog.text = "A-ah, Sie sind es, Senor "+GetFullName(pchar)+"? Haben Sie etwas Interessantes zu erzählen?";
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 0 && CountAdmiralMapFromCharacter() < 24 && !CheckAttribute(npchar, "quest.mapinfo"))
			{
				link.l3 = TimeGreeting()+"! Senor Dios, bitte schauen Sie sich diese Karte an, die ich gefunden habe. Es muss eine Ihrer Karten sein, laut dem Zeichen.";
				link.l3.go = "map_info";
			}
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 23)
			{
				link.l3 = TimeGreeting()+"! Senor Dios, ich habe gute Nachrichten für Sie. Ich konnte den vollständigen Satz Ihrer einzigartigen Karten sammeln, genau wie Sie es wollten. Hier sind alle vierundzwanzig Karten.";
				link.l3.go = "amap";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Dios")) // был в LSC
			{
				link.l4 = TimeGreeting()+"! Ja, habe ich. Ich war an diesem mystischen Ort, von dem wir gesprochen haben.";
				link.l4.go = "LSC";
			}
			link.l9 = "Bisher nichts, Senor. Wollte nur sehen, wie es Ihnen geht.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Dios";
		break;
		
		case "map_info":
			dialog.text = "Zeigen Sie es mir... (schaut hin) Natürlich! Das ist eine meiner Karten für den Admiralatlas! Kapitän, ich bitte Sie wirklich, alle zu finden! Ich verstehe, dass es fast unmöglich ist, aber trotzdem... Ich will die Hoffnung nicht verlieren.";
			link.l1 = "Verlieren Sie nicht den Kopf, Senor. Ich habe diese Karte gefunden, also besteht die Chance, dass ich auch den Rest finde. Sie sind immer noch in der Karibik.";
			link.l1.go = "map_info_1";
		break;
		
		case "map_info_1":
			dialog.text = "Ihr Optimismus ermutigt mich wirklich, Senor Kapitän. Vielleicht werde ich noch die Gelegenheit bekommen, Don Juan de Cordova zu zeigen, wer der beste Kartograph des Archipels ist!";
			link.l1 = "Sie werden in der Lage sein, all Ihre konkurrierenden Übeltäter zu besiegen. Die Karten sind wirklich wunderbar... Lebewohl, Senor!";
			link.l1.go = "exit";
			npchar.quest.mapinfo = "true";
			NextDiag.TempNode = "Dios";
		break;
		
		case "amap":
			Achievment_Set("ach_CL_110");
			dialog.text = "Ich kann meinen Augen nicht trauen! Haben Sie sie wirklich gefunden? Alle von ihnen?";
			link.l1 = "Ja. Es war nicht einfach, aber ich hatte Glück bei dieser Suche. Nehmen Sie Ihre Karten. Sie sind so wunderbar, dass es mir Leid tut, mich von ihnen zu trennen.";
			link.l1.go = "amap_1";
		break;
		
		case "amap_1":
			for(i=1; i<=24; i++)
			{
				sTemp = IdentifyAdmiralMapLast();
				if (sTemp != "") RemoveItems(pchar, sTemp, 1);
			}
			Log_Info("Sie haben den vollständigen Satz von Admiralskarten gegeben");
			PlaySound("interface\important_item.wav");
			dialog.text = "Unglaublich! Das ist einfach zu unglaublich! Um ehrlich zu sein, habe ich nie geglaubt, dass dieser Moment eintreten würde.";
			link.l1 = "Dum spiro spero, Senior Dios. Sie können sich nun Don Cordova stellen. Ich bin sicher, er wird Ihre Talente sehr schätzen.";
			link.l1.go = "amap_2";
		break;
		
		case "amap_2":
			dialog.text = "Sie haben meinen Dank, Kapitän! Sie realisieren gar nicht, welch großen Dienst Sie mir erwiesen haben. Und wie versprochen - ich werde Sie belohnen. Ich habe auch ein Geschenk für Sie. Ich denke, als Seemann werden Sie es sehr nützlich finden.";
			link.l1 = "Sie haben mich neugierig gemacht, Senor!";
			link.l1.go = "amap_3";
		break;
		
		case "amap_3":
			GiveItem2Character(pchar, "spyglass5"); 
			Log_Info("Du hast ein Schiffsteleskop erhalten");
			PlaySound("interface\important_item.wav");
			dialog.text = "Hier! Dies ist ein Schiffsteleskop meiner Anfertigung. Es ist einzigartig und Sie werden nirgendwo anders ein solches finden. Die Linsen wurden von dem geschicktesten Meister in Spanien in Europa angefertigt. Das Gehäuse wurde von einem befreundeten Büchsenmacher gemacht. Ein spezielles Stativ hilft Ihnen, das Gerät trotz jeglichen Rollens zu richten. Sie können alles sehen, was Sie sehen wollen, sei es ein Schiff oder eine Festung.";
			link.l1 = "Ein so wunderbares Geschenk! Danke, Senor Dios.";
			link.l1.go = "amap_4";
		break;
		
		case "amap_4":
			dialog.text = "Nehmen Sie es, Senor Kapitän. Ich hoffe, dass mein Teleskop Ihnen gut dienen wird.";
			link.l1 = "Kein Zweifel! Ich freue mich darauf, es auf dem Deck meines Schiffes zu platzieren und hindurch zu schauen.";
			link.l1.go = "amap_5";
		break;
		
		case "amap_5":
			dialog.text = "Sie werden überrascht sein, das kann ich Ihnen versichern... Nochmals vielen Dank, dass Sie meine Karten gerettet haben!";
			link.l1 = "Danke ebenso, senor. Ich glaube wir werden uns wiedersehen. Aber für jetzt, verabschiede ich mich. Ich werde Ihr prächtiges Gerät ausprobieren. Auf Wiedersehen!";
			link.l1.go = "amap_6";
			link.l2 = "Danke auch Ihnen, Senor. Ein nautisches Fernrohr ist eine einzigartige und sehr nützliche Sache für einen Seemann. Dennoch mag es nicht wertvoller sein als eine Reihe Ihrer Karten. Ich beneide Don de Cordova zutiefst. Ah! Ich würde solch schöne Karten gerne auf meinem Kapitänstisch in meiner Kabine haben.";
			link.l2.go = "amapcopy_01";
		break;
		
		case "amap_6":
			DialogExit();
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 1000); // харизма
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность (раз телескоп дали)
			ChangeCharacterComplexReputation(pchar, "nobility", 10);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 5);// репутация-авторитет
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			ChangeOfficersLoyality("good_all", 5);
			DeleteAttribute(pchar, "questTemp.AdmiralMap");
		break;
		
		case "amapcopy_01":
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 1000); // харизма
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность (раз телескоп дали)
			ChangeCharacterComplexReputation(pchar, "nobility", 10);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 5);// репутация-авторитет
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			ChangeOfficersLoyality("good_all", 5);
			DeleteAttribute(pchar, "questTemp.AdmiralMap");
			dialog.text = "Ach, senor, aber die Karten sind einzigartig. Und wenn ich anfinge, Kopien zu machen, wäre die Einzigartigkeit dieses Atlas verloren, sobald Don Juan de Cordova herausfände, dass jemand anderes die gleichen hat.";
			link.l1 = "Hmm... Senor Dios, gibt es eine Möglichkeit, dass Sie eine Ausnahme machen würden?";
			link.l1.go = "amapcopy_02";
		break;
		
		case "amapcopy_02":
			dialog.text = "Eine Ausnahme?";
			link.l1 = "Wir beide sind ehrliche Menschen, wir hatten die Gelegenheit, uns gegenseitig davon zu überzeugen. Wenn Sie eine Kopie Ihrer Karten für mich anfertigen würden, würde ich schwören, dass niemand jemals davon erfahren würde. Verstehen Sie: Ihre Karten sind wirklich großartig, und für mich als Seemann ist dieser Atlas ein wahrer Schatz. Außerdem würde ich Sie für Ihre Arbeit großzügig entlohnen.";
			link.l1.go = "amapcopy_03";
		break;
		
		case "amapcopy_03":
			dialog.text = "Senor "+pchar.lastname+", Ich zweifle keine Sekunde daran, dass Sie Ihr Wort halten würden. Und angesichts dessen, was Sie für mich getan haben, fällt es mir sehr schwer, Ihre Bitte abzulehnen. Darüber hinaus ist die Tatsache, dass Sie, ein hervorragender Seemann, meine Karten so hoch schätzen, bereits ein wertvolles Kompliment für mich als Kartograph.";
			link.l1 = "Glauben Sie mir, ich habe kein bisschen übertrieben. Was sagen Sie dazu?";
			link.l1.go = "amapcopy_04";
		break;
		
		case "amapcopy_04":
			dialog.text = "Also gut, ich stimme zu, Ihnen eine Kopie dieses Atlas zu machen. Aber es gibt ein kleines Problem. Als mein kostbarer Atlas gestohlen wurde, haben die Diebe auch all meine Werkzeuge mitgenommen - vielleicht um sicherzustellen, dass ich nie mehr Karten erstellen kann oder um sie auch meinen Konkurrenten zu verpfänden. Und wenn ich weitere Karten von solcher Qualität erstellen soll, kann ich nicht einfach gewöhnliches Schreibwarenmaterial verwenden.\nIch habe versucht, Schreibwaren auf dem Markt zu kaufen, aber ich hatte kein Glück - es gibt nichts zu verkaufen. Wenn Sie mir die notwendigen Materialien besorgen können, werde ich Kopien dieser Karten für Sie anfertigen.";
			link.l1 = "Kein Problem, ich bringe Ihnen hochwertige Schreibwaren. Und was ist mit der Bezahlung?";
			link.l1.go = "amapcopy_05";
		break;
		
		case "amapcopy_05":
			dialog.text = "Ich möchte nicht geizig erscheinen, Senor... Aber ich muss Sie um drei Kisten Dublonen für diese Arbeit bitten. Außerdem benötige ich einen Monat, um die Arbeit zu beenden - solche Karten können nicht in ein paar Stunden erstellt werden.";
			link.l1 = "Natürlich, ich stimme zu! Der Wert Ihrer Karten übersteigt bei weitem den von Ihnen genannten Betrag.";
			link.l1.go = "amapcopy_06";
		break;
		
		case "amapcopy_06":
			dialog.text = "Dann werde ich auf Sie mit den benötigten Vorräten und der vereinbarten Bezahlung warten. Sobald Sie alles bringen, werde ich anfangen zu arbeiten.";
			if(GetCharacterItem(pchar,"chest") >= 3 && GetCharacterItem(pchar,"mineral21") > 0)
			{
				link.l1 = "Sie müssen nicht lange warten: wie es der Zufall will, habe ich alles, was Sie brauchen. Hier, bitte.";
				link.l1.go = "amapcopy_07";
			}
			link.l2 = "Sie werden nicht lange warten müssen, Senor!";
			link.l2.go = "amapcopy_exit";
		break;
		
		case "amapcopy_07":
			dialog.text = "Fantastische Neuigkeiten! Sie wissen, für einen wahren Kartographen gibt es nichts Erfreulicheres, als wenn seine Arbeit so hoch geschätzt wird. Ich muss zugeben, ich bin froh, dass ein wahrer professioneller Seemann meine Arbeit nutzen wird. Jetzt brauche ich einen Monat, um sie zu beenden. Danach werde ich Sie bei mir erwarten!";
			link.l1 = "Ich werde in einem Monat zurück sein, Senor Dios. Und nochmals vielen Dank!";
			link.l1.go = "amapcopy_08";
		break;
		
		case "amapcopy_08":
			TakeNItems(pchar,"chest", -3);
			TakeNItems(pchar,"mineral21", -1);
			Log_info("Du hast Schreibzeug und drei Truhen mit Dublonen übergeben.");
			PlaySound("interface\important_item.wav");
			SetTimerFunction("Amapcopy_comlete", 0, 0, 30);
			pchar.questTemp.AdmiralMapCopy = "wait";
			NextDiag.CurrentNode = "amapcopy_waitmonth";
			DialogExit();
		break;
		
		case "amapcopy_exit":
			DialogExit();
			NextDiag.CurrentNode = "amapcopy_waitchest";
		break;
		
		case "amapcopy_waitchest":
			dialog.text = "Grüße, Senor "+pchar.lastname+"! Haben Sie das gebracht, was ich gefragt habe?";
			link.l1 = "Noch nicht, Senor Dios. Aber ich werde definitiv alles bringen!";
			link.l1.go = "amapcopy_exit";
			if(GetCharacterItem(pchar,"chest") >= 3 && GetCharacterItem(pchar,"mineral21") > 0)
			{
				link.l2 = "Ja, Senor Dios. Hier sind Ihre neuen Schreibmaterialien und die vereinbarte Zahlung.";
				link.l2.go = "amapcopy_07";
			}
		break;
		
		case "amapcopy_waitmonth":
			if(CheckAttribute(pchar,"questTemp.AdmiralMapCopy") && pchar.questTemp.AdmiralMapCopy == "complete")
			{
				dialog.text = "Und hier sind Sie, mein lieber Freund! Ich hoffe, es macht Ihnen nichts aus, wenn ich Sie so nenne?";
				link.l1 = "Ganz und gar nicht, mein Freund. Ich bin wirklich froh, dass wir Freunde geworden sind.";
				link.l1.go = "amapcopy_09";
			}
			else
			{
				dialog.text = "Willkommen, Senor! Ich bitte um Verzeihung, aber die Karten sind noch nicht fertig!";
				link.l1 = "Ja, ich erinnere mich, dass Sie sagten, Sie würden einen Monat benötigen. Ich bin nur vorbeigekommen, um nach Ihnen zu sehen.";
				link.l1.go = "amapcopy_waitmonth_01";
			}
		break;
		
		case "amapcopy_waitmonth_01":
			NextDiag.CurrentNode = "amapcopy_waitmonth";
			DialogExit();
		break;
		
		case "amapcopy_09":
			dialog.text = "Ich habe wunderbare Neuigkeiten für Sie! Ich habe endlich eine Kopie des Admiralsatlas fertiggestellt. Ich werde das Original für mich behalten, da ich immer noch vorhabe, mich am Dienst des Vizekönigs von Neu-Grenada zu beteiligen. Aber die Kopien sind eure! Ich hoffe, sie werden euch gut dienen.";
			link.l1 = "Vielen Dank, Senor! Sie haben keine Ahnung, wie wertvoll Ihr Atlas für jemanden wie mich ist! Ich schwöre auf meine Ehre: Niemand wird jemals erfahren, dass Sie diese Kopie für mich gemacht haben!";
			link.l1.go = "amapcopy_10";
		break;
		
		case "amapcopy_10":
			GiveAdmiralAtlasToCharacter(pchar);
			Log_Info("Du hast einen Satz Admiralenkarten erhalten.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ich bin froh, dass Sie zufrieden sind. Da alles so gekommen ist, habe ich noch ein weiteres Angebot für Sie.";
			link.l1 = "Was ist los? Ich höre sehr aufmerksam zu.";
			link.l1.go = "best_map";
		break;
		
		case "best_map":
			dialog.text = "Während ich diese Karten für Sie gezeichnet habe, kam mir der Gedanke, dass sie zwar gut für einen Entdecker sind, aber nicht alles bieten, was ein Seekapitän braucht. Sehen Sie selbst: Alle Buchten, Kaps und Lagunen darauf sind sehr genau dargestellt, aber du kannst sie nicht benutzen, um einen Kurs zwischen den Inseln zu plotten.";
			link.l1 = "Das stimmt, man kann den Kurs nicht nach ihnen bestimmen. Aber ich wage es keineswegs zu klagen, senor Dios! Sie haben die Karten für mich gemacht, genau wie wir vereinbart haben, nichts weniger.";
			link.l1.go = "best_map_01";
		break;
		
		case "best_map_01":
			dialog.text = "Aber ich kann auch eine Archipelkarte für Sie erstellen! Und nicht die Art, welche Sie von der Niederländischen Westindien-Kompanie kaufen können, sondern eine einzigartige, ausgezeichnete Karte.";
			link.l1 = "Danke, Senor Dios, aber ich brauche keine solche Karte. Trotzdem vielen Dank für das Angebot!";
			link.l1.go = "best_map_02";
			link.l2 = "Machen Sie Witze?! Senor Dios, wie könnte ich bloß so ein Angebot ablehnen? Sagen Sie mir einfach, was Sie brauchen - ich werde kein Geld oder Werkzeuge sparen!";
			link.l2.go = "best_map_04";
		break;
		
		case "best_map_02":
			dialog.text = "Nun, ich musste es anbieten. Auf jeden Fall war es ein Vergnügen, Geschäfte mit Ihnen zu machen, Senor "+pchar.lastname+"!";
			link.l1 = "Ebenso! Viel Glück Ihnen!";
			link.l1.go = "best_map_03";
		break;
		
		case "best_map_03":
			DeleteAttribute(pchar, "questTemp.AdmiralMapCopy");
			DialogExit();
			NextDiag.CurrentNode = "Dios";
		break;
		
		case "best_map_04":
			dialog.text = "Sie haben mir bereits die Werkzeuge gebracht, danke. Ich brauche eine reguläre Archipelkarte und bitte auch um einen Kompass und einen funktionierenden Chronometer: die Karte muss genau sein, sonst wird sie Ihnen nur im Weg stehen. Und was die Bezahlung angeht - ich bitte um eine Kiste mit Dublonen.";
			link.l1 = "Eine gewöhnliche Archipelkarte, ein Kompass, ein funktionierender Chronometer und eine Kiste voller Dublonen... Warum brauchen Sie all das? Ich dachte, Sie würden nur eine Kopie anfertigen, wie bei deinen Inselkarten...";
			link.l1.go = "best_map_05";
		break;
		
		case "best_map_05":
			dialog.text = "Ja, genau wie bei den anderen Karten, habe ich bereits eine Kopie der allgemeinen Archipelkarte angefertigt. Der Kunde war der gleiche - der Vizekönig von Neu-Grenada, Don Juan de Cordova. Er brauchte diese Karte für den Kapitän einer riesigen Flotte, die zwischen der Alten und Neuen Welt durch den Atlantik segelt. Aber die Karte ist bereits in den Händen ihres Besitzers.";
			link.l1 = "Jetzt verstehe ich. Sie müssen diese Karte noch einmal zeichnen?";
			link.l1.go = "best_map_06";
		break;
		
		case "best_map_06":
			dialog.text = "Genau. Deshalb brauche ich eine reguläre Karte, um mich zu orientieren, sowie Navigationsinstrumente für genauere Messungen. Es wird etwa eine Woche dauern, sie zu erstellen - immerhin ist es nicht das erste Mal, dass ich solche Karten zeichne. Oh, die Bedingung ist die gleiche wie zuvor: Dies muss unter uns bleiben. Der Vizekönig könnte wütend werden, wenn er herausfindet, dass ich solche Karten nicht nur für ihn zeichne.";
			if(CheckAMapItems())
			{
				link.l1 = "Ich erinnere mich daran, Senor Dios. Mach dir keine Sorgen, niemand wird von diesen Karten erfahren. Und ich habe bereits alles, was Sie benötigen, bei mir. Hier, nehmen Sie es.";
				link.l1.go = "best_map_07";
			}
			link.l2 = "Ich erinnere mich daran, Senor Dios. Keine Sorge, niemand wird etwas über diese Karten herausfinden. Und ich werde alles bringen, was Sie benötigen, warten Sie nur ab.";
			link.l2.go = "best_map_07e";
		break;
		
		case "best_map_07e":
			DialogExit();
			NextDiag.CurrentNode = "best_map_waititems";
		break;
		
		case "best_map_waititems":
			dialog.text = "Grüße, mein lieber Freund! Hast du gebracht, was ich gefragt habe?";
			link.l1 = "Noch nicht, Senor Dios. Aber ich werde es definitiv bringen!";
			link.l1.go = "best_map_07e";
			if(CheckAMapItems())
			{
				link.l2 = "Ja, Senor Dios. Hier ist alles, was Sie gefordert haben: eine reguläre Karte des Archipels, ein Boussole, ein funktionierender Chronometer und die vereinbarte Bezahlung.";
				link.l2.go = "best_map_07";
			}
		break;
		
		case "best_map_07":
		    Log_Info("Du übergabst eine reguläre Karte des Archipels, eine Boussole, einen tarifierten Chronometer und eine Truhe mit Dublonen.");
			TakeNItems(pchar,"chest", -1);
			TakeNItems(pchar,"map_normal", -1);
			TakeNItems(pchar,"bussol", -1);
			TakeNItems(pchar,"clock2", -1);
			dialog.text = "Nun, dann werde ich an die Arbeit gehen. Kommt in einer Woche zu mir zurück, und ich verspreche euch, ihr werdet es nicht bereuen!";
			link.l1 = "Ich habe keinen Zweifel, Senor. Wir sehen uns in einer Woche!";
			link.l1.go = "best_map_08";
		break;
		
		case "best_map_08":
			SetTimerFunction("AdmAtlas_comlete", 0, 0, 7);
			NextDiag.CurrentNode = "best_map_wait";
			pchar.questTemp.AdmiralAtlas = true;
			DialogExit();
		break;
		
		case "best_map_wait":
			if(CheckAttribute(pchar,"questTemp.AdmiralAtlas") && pchar.questTemp.AdmiralAtlas == "complete")
			{
				dialog.text = "Ach, da sind Sie ja, Senor "+pchar.lastname+"! Ich freue mich, Ihnen mitteilen zu können, dass ich die Karte des Archipels fertiggestellt habe! Und ich kann Ihnen versichern, es ist genauso gut wie die erste Zeichnung, die ich für Don Juan de Cordova gemacht habe!";
				link.l1 = "Mein Freund... Diese Karte ist erstaunlich! Sie ist nichts weniger als ein Meisterwerk! Wie kann ich dir für alles danken, was du für mich getan hast?";
				link.l1.go = "best_map_09";
			}
			else
			{
				dialog.text = "Grüße, Senor! Ich muss mich entschuldigen, aber die Karte ist noch nicht fertig.";
				link.l1 = "Ja, ich erinnere mich, dass Sie eine Woche gebraucht haben. Ich bin nur gekommen, um nach Ihnen zu sehen.";
				link.l1.go = "best_map_wait_01";
			}
		break;
		
		case "best_map_wait_01":
			NextDiag.CurrentNode = "best_map_wait";
			DialogExit();
		break;
		
		case "best_map_09":
			dialog.text = "Ach, komm schon, mein Freund. Es war mir ein Vergnügen, solche Karten für einen edlen Kapitän zu erstellen, der sie wirklich schätzt. Ah ja, du kannst deine Kopie der regulären Karte zurückhaben. Viel Glück auf hoher See!";
			link.l1 = "Vielen Dank! Sie haben Recht, diese Karten sind für mich unbezahlbar. Lebewohl, Senor Dios!";
			link.l1.go = "best_map_10";
		break;
		
		case "best_map_10":
			TakeNItems(pchar,"Map_Best", 1);
			TakeNItems(pchar,"map_normal", 1);
			Log_Info("Du hast eine ausgezeichnete Archipelkarte erhalten!");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "Dios";
			DialogExit();
		break;
		
		case "LSC":
			dialog.text = "Wirklich?! Haben Sie es gefunden? Machen Sie es sich bequem, ich denke, das kommende Gespräch wird eine Weile dauern, habe ich recht?";
			link.l1 = "Ich habe Ihnen wirklich viel über die Insel zu erzählen. Aber zuerst möchte ich, dass Sie mir etwas versprechen. Ich sehe, dass Sie ein Ehrenmann sind, also bin ich sicher, dass Sie Ihr Wort halten werden...";
			link.l1.go = "LSC_1";
		break;
		
		case "LSC_1":
			dialog.text = "Wovon reden Sie, Kapitän?";
			link.l1 = "Dort leben Menschen... und sie werden nicht glücklich sein, wenn jemand sich in ihr Leben einmischt. Ich glaube nicht, dass die mögliche Ankunft eines 'Forschungs' Geschwaders willkommen sein wird.";
			link.l1.go = "LSC_1_1";
		break;
		
		case "LSC_1_1":
			dialog.text = "";
			link.l1 = "Also möchte ich, dass Sie mir Ihr Ehrenwort geben, dass Sie innerhalb von zehn Jahren nach unserem Gespräch keine Informationen veröffentlichen, die zur Auffindung der Insel genutzt werden können. Sie dürfen gerne Informationen über die Einheimischen, ihr Leben und so weiter veröffentlichen, nur den Standort der Insel nicht preisgeben.";
			link.l1.go = "LSC_2";
		break;
		
		case "LSC_2":
			dialog.text = "Ich stimme zu, Kapitän. Ich gebe Ihnen das Wort eines Edelmanns, dass ich in den nächsten zehn Jahren niemandem weder den Standort der Insel noch Informationen, die ihren Bewohnern schaden könnten, verraten werde.";
			link.l1 = "Hören Sie meine Geschichte an. Schreiben Sie sie auf, wenn Sie wollen. Also, die Insel besteht aus vielen gesunkenen Schiffen, deren Wracks auf einem weiten Riff liegen...";
			link.l1.go = "LSC_3";
		break;
		
		case "LSC_3":
			DialogExit();
			SetLaunchFrameFormParam("Zwei Stunden später...", "LSC_FinalDiosStory", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "LSC_4":
			dialog.text = "Unglaublich! Sie haben mir sehr wertvolle Informationen erzählt, Kapitän! Die Nachkommen von Admiral de Betancourt leben auf der Insel! Jetzt wissen wir, was mit seiner Staffel passiert ist. Und es gibt jetzt eine weiße Stelle weniger auf der Karte des karibischen Archipels... Vielen Dank für Ihre Geschichte, "+pchar.name+"!";
			link.l1 = "Sehen Sie jetzt, warum ich Sie gebeten habe, bei der Wiedergabe meiner Informationen wirklich vorsichtig zu sein?";
			link.l1.go = "LSC_5";
		break;
		
		case "LSC_5":
			dialog.text = "Ich verstehe. Sie können sicher sein, dass ich mein Wort halte. Sagen Sie mir... haben Sie irgendwelche materiellen Attribute von der Insel?";
			if (CheckCharacterItem(pchar, "LSC_navigation_map"))
			{
				link.l1 = "Ich habe Segelanweisungen zur Insel der Verlassenen Schiffe. Hier, schauen Sie mal. Sie ermöglichen es Ihnen, mit einem kleinen Schiff durch die Riffe und Trümmer zu segeln und sicher auf der Insel zu landen. Ohne diese Anweisungen ist es unmöglich, die Insel zu erreichen.";
				link.l1.go = "LSC_6";
			}
			else
			{
				link.l1 = "Leider habe ich keine.";
				link.l1.go = "LSC_7_1";
			}
		break;
		
		case "LSC_6":
			Log_Info("Du hast die Segelanweisungen gegeben");
			PlaySound("interface\important_item.wav");
			dialog.text = "(blickend) So ein ausgezeichnetes Dokument! Es wurde von einem Mann gezeichnet, der in der Kartographie bewandert ist. Selbst ich könnte es nicht besser machen. Unglaublich! Kapitän, warum geben Sie mir nicht diese Segelanweisungen? Eine Geschichte ist eine Geschichte, aber dieses Papier muss den berühmtesten Geographen der Alten Welt gezeigt werden!";
			link.l1 = "Senor Dios, leider brauche ich dieses Dokument für mich selbst. Wie ich schon gesagt habe, ist es unmöglich, ohne es durch die Riffe um die Insel zu kommen. Aber Sie können eine Kopie der Anweisungen machen, wenn Sie möchten, und ich wäre nur froh, wenn Sie sie auch in Ihrem Besitz haben.";
			link.l1.go = "LSC_10";
			//link.l2 = "Herr Gott, leider brauche ich diesen Gegenstand für mich selbst. Wie ich schon sagte, ist es unmöglich, die Riffe um die Insel ohne ihn zu umgehen. Ich würde es im Namen der Wissenschaft opfern, aber... Ich bin sicher, dass Sie verstehen.";
			//link.l2.go = "LSC_7";
		break;
		
		case "LSC_7":
			Log_Info("Du hast die Segelanweisungen erhalten");
			PlaySound("interface\important_item.wav");
			dialog.text = "Absolut. Es ist Ihr Recht, obwohl es schade ist... Wie dem auch sei, danke für Ihre Geschichte! Sie haben einen großen Dienst für Geographen, Kartographen und andere neugierige Leute geleistet.";
			link.l1 = "Gern geschehen, Senor. Nun, ich muss jetzt gehen. Lebewohl.";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_7_1":
			dialog.text = "Wie schade... Trotzdem danke für Ihre Geschichte! Sie haben einen großen Dienst für Geographen, Kartographen und andere neugierige Menschen geleistet.";
			link.l1 = "Gern geschehen, Senor. Nun, ich muss jetzt gehen. Auf Wiedersehen.";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_8":
			dialog.text = "Sicher, "+pchar.name+". Sie haben mir viel Ihrer Zeit geschenkt. Richten Sie Senor Svenson meine Grüße aus!";
			link.l1 = "Auf Wiedersehen, Senor Dios.";
			link.l1.go = "LSC_9";
		break;
		
		case "LSC_9":
			DialogExit();
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 400);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 500); // харизма
			ChangeCharacterComplexReputation(pchar, "nobility", 5);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 2);// репутация-авторитет
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 5);
			DeleteAttribute(pchar, "questTemp.LSC.Dios");
			LAi_SetOwnerType(npchar);
		break;
		
		case "LSC_10":
			Log_Info("Du hast die Segelanweisungen erhalten");
			PlaySound("interface\important_item.wav");
			dialog.text = "Vielen Dank! Das ist sehr nett von Ihnen. Geben Sie mir etwas Zeit...";
			link.l1 = "...";
			link.l1.go = "LSC_11";
		break;
		
		case "LSC_11":
			DialogExit();
			SetLaunchFrameFormParam("Zwei Stunden später", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 0);
			npchar.dialog.currentnode = "LSC_12";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LSC_12":
			//RemoveItems(pchar, "LSC_navigation_map", 1);
			dialog.text = "Vielen Dank! Das war sehr nett von Ihnen. Jetzt haben wir nicht nur mündliche Beweise, sondern auch materielle... Ich werde Sie nicht unbelohnt lassen, Kapitän. Ich habe ein kleines Geschenk für Sie.";
			link.l1 = "Welche Art von Geschenk?";
			link.l1.go = "LSC_13";
		break;
		
		case "LSC_13":
			sld = characterFromId("Pirates_shipyarder");
			sld.quest.sextant = "true"; // атрибут Алексу на хронометр
			GiveItem2Character(pchar, "sextant1"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "Ich habe nicht nur eine Vorliebe für Kartographie und Geographie, sondern auch für Mathematik und Astronomie. Es hat mich ein Jahr des Versuchens gekostet, ein universelles Werkzeug zur Bestimmung von Breiten- und Längengraden zu erschaffen. Und ich habe Fortschritte gemacht. Schauen Sie mal:\nDas ist mein Sextant. Ich habe es selbst entworfen. Das Problem ist, es funktioniert nicht. Es erfordert einen äußerst genauen Chronometer. Selbst jene, die von den besten Handwerkern hergestellt wurden, geben mit der Zeit inakzeptable Fehler. Daher ist mein Werkzeug vorerst wertlos.\nAber da Sie viel reisen, werden Sie vielleicht einen Chronometer finden, der genau genug für den Sextant ist. Sobald Sie eine solche Uhr finden - werden Sie keine Boussole, keinen Kompass, keinen Astrolabium, keine Sanduhren und andere miese Chronometer mehr brauchen - mein Werkzeug wird sie alle ersetzen.";
			link.l1 = "Danke, Senor Dios. Hoffen wir, dass ich einen Chronometer finde, der Ihre Erfindung zum Laufen bringt. Ich hätte gerne ein solches Gerät... in funktionierendem Zustand. Nun, ich muss jetzt gehen. Auf Wiedersehen.";
			link.l1.go = "LSC_8";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Du bist "+GetSexPhrase("ein Dieb, wie ich sehe! Wachen, packt ihn!","ein Dieb, wie ich sehe! Wachen, nehmt sie fest")+"!!!","Ich kann es nicht glauben! Ich habe mich für eine Sekunde abgewendet - und du stöberst in meinen Sachen! Haltet den Dieb!!!","Wachen! Raub! Haltet den Dieb!!!");
			link.l1 = "Aaaah, Teufel!!!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

bool CheckAMapItems()
{
	return GetCharacterItem(pchar,"chest")      && 
		   GetCharacterItem(pchar,"map_normal") &&
		   GetCharacterFreeItem(pchar,"bussol") &&
		   GetCharacterFreeItem(pchar,"clock2");
}