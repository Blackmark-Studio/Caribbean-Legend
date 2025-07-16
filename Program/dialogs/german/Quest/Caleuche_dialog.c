void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Das ist definitiv ein Fehler. Können Sie bitte Jason darüber informieren, wann und wie das passiert ist.";
			link.l1 = "Wird gemacht.";
			link.l1.go = "exit";
		break;
		
		// шаман карибов Туттуатхапак
		case "Tuttuat":
			dialog.text = "Warum bist du zu meiner Hütte gekommen, weißer Mann? Tuttuathapak denkt nicht, dass du sein lieber Gast bist.";
			if (GetCharacterFreeItem(pchar, "mushket1") || GetCharacterFreeItem(pchar, "mushket2") || GetCharacterFreeItem(pchar, "mushket7"))
			{
				link.l1 = "Heil dir, großer Schamane Tuttuathapak. Ich bin zu dir gekommen, um deine Hilfe und deinen Rat zu suchen. Bitte nimm dieses Musket als Zeichen meines guten Willens.";
				link.l1.go = "Tuttuat_1";
			}
			else
			{
				link.l1 = "Sei gegrüßt, großer Schamane Tuttuathapak. Ich bin zu dir gekommen, um deine Hilfe und deinen Rat zu suchen.";
				link.l1.go = "Tuttuat_exit";
			}
		break;
		
		case "Tuttuat_exit":
			dialog.text = "Tuttuathapak hilft keinem Weißen. Weiße Männer sind schlechte Männer. Sie töten und erobern Indianer, machen Indianer zu Sklaven. Tuttuathapak gibt keinem Weißen Rat. Geh jetzt weg.";
			link.l1 = "Hmm...";
			link.l1.go = "Tuttuat_exit_1";
		break;
		
		case "Tuttuat_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat";
		break;
		
		case "Tuttuat_1":
			if (GetCharacterFreeItem(pchar, "mushket1")) 
			{
				sTemp = "mushket1";
			}
			else 
			{
				if(GetCharacterFreeItem(pchar, "mushket2"))
				{
					sTemp = "mushket2";
				}
				else
				{
					sTemp = "mushket7";
				}
			}
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You have given: "+XI_ConvertString(sTemp)+"");
			dialog.text = "Du weißt, was du Tuttuathapak geben sollst, weißer Mann. Tuttuathapak nimmt dein Geschenk an. Er wird sprechen. Welchen Rat suchst du bei mir?";
			link.l1 = "Ich habe gehört, dass du aus einem weit entfernten Ort im Süden kommst. Ich habe ein indisches Amulett, und ein kundiger Mann hat mir gesagt, dass du vielleicht weißt, wie man es benutzen kann.";
			link.l1.go = "Tuttuat_2";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_2":
			dialog.text = "Zeig das Amulett.";
			link.l1 = "Hier haben Sie, großer Schamane.";
			link.l1.go = "Tuttuat_3";
		break;
		
		case "Tuttuat_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(blickt auf das Amulett)... Dein Freund spricht die Wahrheit, weißer Mann. Dieses Amulett gehört meinem Volk, den großen Indianern, Chavin war ihr Name. Verfluchter blasphemischer bleichgesichtiger Schurke entweiht den Schrein und bringt es hierher. Tuttuathapak bestrafte diesen Hund.";
			link.l1 = "Du hast ihm den Verstand geraubt, oder?";
			link.l1.go = "Tuttuat_4";
		break;
		
		case "Tuttuat_4":
			dialog.text = "Weißer Mann überrascht Tuttuathapak mit seinem Wissen. Ja, ich verschlinge den Verstand dieses scheußlichen Hundes. Er und seine schmutzigen Männer bekommen, was sie verdienen.";
			link.l1 = "Ich verstehe... Sag mir, Schamane, wofür ist dieses Amulett? Kann es einen vielleicht im Kampf schützen oder gegen böse Magie abwehren?";
			link.l1.go = "Tuttuat_5";
		break;
		
		case "Tuttuat_5":
			dialog.text = "Dieses Amulett ist für dich von keinem Nutzen, weißer Kapitän. Du kannst seine Kraft nicht nutzen. Nur die großen Schamanen unseres Stammes wissen, wie man es erweckt.";
			link.l1 = "Hmm... Also, es stellt sich heraus, dass ich so eine lange Reise umsonst gemacht habe. Aber, vielleicht, kannst du die Kraft dieses Amuletts wecken, großer Schamane? Sicherlich könnten wir zu einer Einigung kommen...";
			link.l1.go = "Tuttuat_6";
		break;
		
		case "Tuttuat_6":
			dialog.text = "Sogar wenn ich das Amulett wecke, wirst du seine Kraft nicht lange halten. Aber ich biete dir einen Deal an, weißer Mann.";
			link.l1 = "Welche Art von Deal?";
			link.l1.go = "Tuttuat_7";
		break;
		
		case "Tuttuat_7":
			dialog.text = "Drei Amulette wie dieses wurden aus unserem Schrein genommen. Sie haben verschiedene Kräfte, aber wenn sie zusammengebracht werden, sind sie sehr, sehr mächtig. Finde alle drei Amulette und bring sie mir, und ich belohne dich. Ich gebe dir Macht, die du für immer halten kannst.";
			link.l1 = "Ich verstehe nicht ganz... Welche Art von Macht meinst du?";
			link.l1.go = "Tuttuat_8";
		break;
		
		case "Tuttuat_8":
			dialog.text = "Du wirst alles zur rechten Zeit erfahren. Finde und bringe mir alle drei Amulette. Sie sind in der Karibik. Suche und finde. Du wirst sie leicht erkennen - sie sehen gleich aus. Geh, weißer Mann. Tuttuathapak wartet und bittet die Geister, dir zu helfen.";
			link.l1 = "..., Freund.";
			link.l1.go = "Tuttuat_9";
		break;
		
		case "Tuttuat_9":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "ghostship"; 
			AddQuestRecord("Caleuche", "3");
			pchar.quest.Caleuche_ghostship.win_condition.l1 = "location";
			pchar.quest.Caleuche_ghostship.win_condition.l1.location = "Dominica";
			pchar.quest.Caleuche_ghostship.function = "Caleuche_PrepareGhostship";
		break;
		
		case "Tuttuat_10":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "Geh, weißer Mann. Finde zwei weitere Amulette.";
				link.l1 = "Ich habe sie bereits gefunden, großer Schamane. Hier, schau mal.";
				link.l1.go = "Tuttuat_33";
			}
			else
			{
				dialog.text = "Geh, weißer Mann. Finde die anderen zwei Amulette.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_10_1";
			}
		break;
		
		case "Tuttuat_10_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
		break;
		
		case "Tuttuat_11":
			dialog.text = "Bist du schon wieder hier, weißer Mann? Du siehst aus, als hättest du im Dschungel einen wilden Jaguar getroffen.";
			link.l1 = "Schlimmer, großer Schamane. Als ich ins Meer trat, tauchte aus dem Nichts ein gewaltiger Sturm auf und ich wurde von einem Schiff voller Untoter angegriffen! Ihr Kapitän war völlig unbesiegbar. Zuerst nahm er mir das Amulett ab und hätte mich fast getötet - ich überlebte kaum. Und dann versenkten sie fast mein Schiff, nur eine Handvoll meiner Mannschaft überlebte.";
			link.l1.go = "Tuttuat_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Tuttuat_12":
			dialog.text = "Schlechte Nachrichten, Weißer. Die Caleuche geht wieder auf die Jagd.";
			link.l1 = "Der Caleuche? Dieser untote Kapitän nannte sein Schiff das Fliegende Herz. Also, wusstest du von dem Geisterschiff und hast mich nicht davor gewarnt? Wenn ich gewusst hätte, dass dieser segelnde Alptraum auf der Suche nach dem Amulett ist, hätte ich niemals...";
			link.l1.go = "Tuttuat_13";
		break;
		
		case "Tuttuat_13":
			dialog.text = "Tuttuathapak sieht, dass der weiße Kapitän verärgert ist. Der weiße Kapitän muss sich beruhigen.";
			link.l1 = "Beruhigen?! Bist du verrückt, wie kann ich gegen so etwas überleben!";
			link.l1.go = "Tuttuat_14";
		break;
		
		case "Tuttuat_14":
			dialog.text = "Ja. Beruhige dich und schrei nicht. Sag mir - willst du immer noch die große Macht von mir erhalten, die für immer bei dir bleibt?";
			link.l1 = "Nun, sicher habe ich. Aber ich habe das Amulett nicht mehr.";
			link.l1.go = "Tuttuat_15";
		break;
		
		case "Tuttuat_15":
			dialog.text = "Ich lehre dich, wie man das Amulett vom Kapitän der Caleuche nimmt. Es wird nicht einfach sein. Aber wenn du es tust, nimmst du sein Schiff als deine Beute, findest wertvolle Schätze, gewinnst Ruhm bei deinem Volk und erhältst eine Belohnung von mir.";
			link.l1 = "Verdammt! Ich würde dieses verschrumpelte Monster gerne vernichten! Aber wie kann ich ihn besiegen, wenn er weder durch das Schwert noch durch die Kugel verletzt werden kann?!";
			link.l1.go = "Tuttuat_16";
		break;
		
		case "Tuttuat_16":
			dialog.text = "Bist du bereit mir zuzuhören, weißer Kapitän?";
			link.l1 = "Ja, das bin ich, großer Schamane.";
			link.l1.go = "Tuttuat_17";
		break;
		
		case "Tuttuat_17":
			dialog.text = "Als mein Vater ein junger Krieger war, kamen weiße Männer auf dem Schiff Flying Heart in mein Land. Sie gingen in die Berge. Die Legende besagt, dass dort ein Schrein unserer Vorfahren verborgen ist. Der Schrein der Jaguar-Krieger. Die weißen Männer fanden den Schrein und Gold und entweihten das alte heilige Ding. Sie nahmen den großen Schatz der Chavins mit - den Jadetotenschädel von Yum Cimil, dem Gott des Todes und dem Schutzpatron der Jaguar-Männer. \nDie weißen Männer kamen zu ihrem Schiff. Sie beschlossen, zurückzukehren, um mehr Gold zu holen, aber als ihr Mann das trockene Land betrat, starb er vor schrecklichen Schmerzen. Yum Cimil verfluchte den Kapitän und seine Besatzung. Sie wurden unsterblich, konnten aber nicht mehr an Land gehen. Sie segelten viele, viele Winter, ein halbes Jahrhundert nach eurem Kalender. So entstand die Caleuche. \nIhre Körper welken, ihr Fleisch verfault, aber sie leben noch. Wenn man ihnen einen Arm oder ein Bein abschlägt, kommt es zurück. Wenn man sie in zwei Hälften schneidet, werden sie wieder eins. Wenn ihr Schiff untergeht, reparieren sie es unter Wasser und es segelt wieder.";
			link.l1 = "Einfach toll...";
			link.l1.go = "Tuttuat_18";
		break;
		
		case "Tuttuat_18":
			dialog.text = "Der Caleuche terrorisiert Seeleute. Er greift ohne Grund an und verheißt sicheres Verderben. Er ist kein häufiger Gast in der Karibik. Er segelt gerne an den Ufern meiner Heimat. Ich denke, er will den Fluch beseitigen. Aber er wird ihn nie aufheben.";
			link.l1 = "Warum? Was muss getan werden, um den Fluch aufzuheben?";
			link.l1.go = "Tuttuat_19";
		break;
		
		case "Tuttuat_19":
			dialog.text = "Jadeschädel. Er muss zur Schrein von Yum Cimil zurückkehren, Tempel der Jaguar-Krieger. Es gibt mehrere Tempel. Die Ältesten meines Stammes sagen, es gäbe einen auf einer kleinen Insel in der Karibik. Deshalb segelte die Caleuche dorthin. Sobald der Schädel im Tempel ist, bricht der Zauber von Yum Cimil und sie werden sterblich und können ihre Wunden nicht mehr heilen.";
			link.l1 = "Ha! Eher wahrscheinlich, sie werden den Schädel nicht zurückgeben! Warum sollten sie, wenn sie unsterblich und unbesiegbar sind? Und außerdem können sie ihn einfach nicht zurückbringen, wenn sie nicht an Land gehen dürfen, oder?";
			link.l1.go = "Tuttuat_20";
		break;
		
		case "Tuttuat_20":
			dialog.text = "Sie haben keinen Schädel. Der Kapitän warf ihn in meinem Ahnenland weg, als er von der Schrein der Jaguar-Männer zurückkehrte. Jade ist kein Gold, weißer Mann braucht es nicht, er konnte das schöne grüne Juwel in den Augen des Schädels nicht nehmen. Und er warf es weg. Ein Seemann hob es auf, und er wurde nicht vom Fluch berührt\nAls der Seemann sah, was aus der Besatzung der Caleuche geworden ist, floh er. Er kam in unser Dorf. Mein Vater sah diesen Seemann und den Schädel von Yum Cimil. Und dann ging der weiße Mann nördlich entlang der Küste und nahm den Schädel mit ihm.";
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul"))
				{
					link.l1 = "Ein Jadetotenkopf mit grünen Steinen in den Augenhöhlen? Ich hatte ihn in meinen Händen, kannst du dir das vorstellen? Ich habe ihn selbst an Solomon gegeben. Aber er ist mit seiner Tochter nach Europa abgereist, und es scheint, er hat den Totenkopf mitgenommen.";
				}
				else
				{
					link.l1 = "Ein Jadenschädel mit grünen Edelsteinen in den Augenhöhlen? Heilige Scheiße... Ich... Ich habe es mit meinen eigenen Händen gehalten! Und ich habe es an einen Portugiesen verkauft... Merriman, oder so ähnlich... Ja, das hat er gesagt - der Schädel von Yum Cimil! Er wollte es unbedingt haben! Er hat eine halbe Million Pesos dafür bezahlt!";
				}
				link.l1.go = "Tuttuat_21_1";
			}
			else
			{
				link.l1 = "Ein Jadenschädel mit grünen Edelsteinen in den Augenhöhlen? Also muss ich das finden? Aber dieser Seemann könnte vor fünfzig Jahren im Dschungel ums Leben gekommen sein, und der Schädel könnte für immer verloren sein!";
				link.l1.go = "Tuttuat_21_2";
			}
		break;
		
		case "Tuttuat_21_1":
			dialog.text = "Ich weiß, dass der Schädel in der Karibik ist. Die Caleuche ist nicht zufällig hier. In den letzten sechs Monden wurde sie oft auf der Insel gesehen. Früher war sie viele Winter lang nicht da. Der Kapitän der Caleuche kann das Artefakt der Jaguar-Männer spüren. So hat er dich und dein Schiff gefunden.";
			link.l1 = "Also, habe ich das richtig verstanden, dass ich diesen Schädel wiederfinden muss? Und was soll ich dann damit machen?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_21_2":
			dialog.text = "Der Schädel muss hier sein, in der Karibik. Caleuche ist nicht zufällig hier. In den letzten sechs Monden wurde es oft auf der Insel gesehen. Davor war es viele Winter nicht da. Der Kapitän von Caleuche kann das Artefakt der Jaguar-Männer spüren. So hat er dich und dein Schiff gefunden.";
			link.l1 = "Also, habe ich das richtig verstanden, dass ich diesen Schädel wieder finden muss? Und was soll ich dann damit machen?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_22":
			dialog.text = "Zuerst müssen Sie die beiden Amulette finden, von denen wir gesprochen haben. Ohne sie können Sie nichts tun. Das Amulett gibt Ihnen die Kraft, sich gegen die Jaguar-Männer und jeden Feind, auf den Sie stoßen, zu behaupten.";
			link.l1 = "Stell dich gegen Jaguar-Männer? Wovon redest du?";
			link.l1.go = "Tuttuat_23";
		break;
		
		case "Tuttuat_23":
			dialog.text = "Der Tempel, in den du den Jadetotenkopf bringen musst, befindet sich auf einer einsamen Insel in der Karibik. Er wird von Jaguar-Männern bewacht. Sie sind alle tot aber jetzt lebendig. Ohne Amulett kommst du nicht an ihnen vorbei. Die Jaguar-Männer waren im Leben furchterregende Krieger und werden nach dem Tod fast unbesiegbar. Sie werden von Yum Cimil selbst mit Kraft versorgt.";
			link.l1 = "Untote? Wieder? Glücklich ich...";
			link.l1.go = "Tuttuat_24";
		break;
		
		case "Tuttuat_24":
			dialog.text = "Warum so überrascht, weißer Kapitän? Yum Cimil ist ein Gott des Todes, der Jadenschädel verleiht Macht über Tote und Lebende. Karibik. Es wird von Jaguar-Männern bewacht. Ohne Amulett kommst du nicht an ihnen vorbei. Mit Amulett kannst du den Tempel betreten und überleben, du lässt den Schädel dort, dann findest du die Caleuche, besiegst ihren Kapitän und nimmst das Amulett, das er dir abgenommen hat.";
			link.l1 = "Und warum braucht der Kapitän der Caleuche diese Amulette?";
			link.l1.go = "Tuttuat_25";
		break;
		
		case "Tuttuat_25":
			dialog.text = "Mir scheint, er will zum Tempel der Jaguar-Männer gehen und er denkt, dass das Amulett ihm hilft. Aber ich kann mich irren. Dennoch wird die Caleuche immer von Artefakten meines Landes angelockt. Sie segelte nahe der Insel, wo der Tempel der Jaguar-Männer ist, und sie segelte an den Küsten meiner Heimat.";
			link.l1 = "Und wo ist diese Insel?";
			link.l1.go = "Tuttuat_26";
		break;
		
		case "Tuttuat_26":
			dialog.text = "Zuerst findest du den Schädel von Yum Cimil und die Amulette. Dann reden wir über die Insel.";
			link.l1 = "Gut. Kannst du mir einen Hinweis geben, wo ich den Jadetotenkopf suchen soll?";
			link.l1.go = "Tuttuat_27";
		break;
		
		case "Tuttuat_27":
			dialog.text = "Mich wissen nicht. Aber es ist hier, in der Karibik. Und Amulette, auch. Frag. Such. Find.";
			link.l1 = "Heh... Na gut, ich werde es versuchen.";
			link.l1.go = "Tuttuat_28";
		break;
		
		case "Tuttuat_28":
			dialog.text = "Und sei vorsichtig, weißer Kapitän. Die Caleuche spürt Chavins Gegenstände. Wenn du das Amulett hast, sucht sie dich. Wenn sie dich findet, fliehe und das schnell. Wenn sie dich erwischt, bist du ein toter Mann.";
			link.l1 = "Dieses verfluchte Schiff ist wahnsinnig schnell! Es ist etwa doppelt so schnell wie jedes Schiff, das ich je gesehen habe. Aber ich habe bemerkt, dass es Schwierigkeiten hat, gegen den Wind zu segeln.";
			link.l1.go = "Tuttuat_29";
		break;
		
		case "Tuttuat_29":
			dialog.text = "Der Caleuche ist verflucht - deshalb ist sie so schnell. Schwer zu entkommen. Du musst ein Schiff haben, das den Caleuche überholen kann. Oder du endest tot. Wenn du das Amulett findest, bring es zu mir. Behalte das Amulett nicht auf dem Schiff.";
			link.l1 = "Ich habe es bereits bekommen. Danke für deine Geschichte, großer Schamane. Es ist jetzt an der Zeit für mich zu gehen.";
			link.l1.go = "Tuttuat_31";
		break;
		
		case "Tuttuat_31":
			dialog.text = "Mich befrage die Geister, um dir zu helfen und dich vor der Caleuche zu retten.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_32";
		break;
		
		case "Tuttuat_32":
			DialogExit();
			LocatorReloadEnterDisable("Shore27", "boat", false);
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "mayak"; 
			AddQuestRecord("Caleuche", "6");
		break;
		
		case "Tuttuat_33":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given the amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "(schauend) Ja, das ist es. Das zweite Chavins-Amulett. Du bist gut. Du musst noch ein weiteres Amulett finden.";
			link.l1 = "Ich erinnere mich daran, Schamane. Bald wirst du es haben.";
			link.l1.go = "Tuttuat_34";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_34":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
			AddQuestRecord("Caleuche", "22");
			if (!Caleuche_CheckAmulet())
			{
				if (GetCharacterIndex("Map_Caleuche") != -1)
				{
					sld = characterFromId("Map_Caleuche");
					sld.lifeday = 0;
					Map_ReleaseQuestEncounter("Map_Caleuche");
				}
			}
		break;
		
		case "Tuttuat_35":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "Geh, weißer Mann. Finde noch einen Amulett.";
				link.l1 = "Ich habe es bereits, großer Schamane. Hier, schau es dir an.";
				link.l1.go = "Tuttuat_36";
			}
			else
			{
				dialog.text = "Geh, weißer Mann. Finde noch ein Amulett.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_35_1";
			}
		break;
		
		case "Tuttuat_35_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
		break;
		
		case "Tuttuat_36":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given the amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "(blickend) Ja, das ist es. Das dritte Chavins-Amulett. Du bist gut. Du hast alle Amulette gefunden, um die toten Jaguar-Krieger, Diener von Yum Cimil, zu überwinden.";
			link.l1 = "Nun, wie ich verstehe, werde ich den Jadenschädel brauchen?";
			link.l1.go = "Tuttuat_37";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_37":
			dialog.text = "Du sprichst die Wahrheit. Der Jadetotenschädel von Yum Cimil. Du musst ihn zum Tempel von Chavins bringen. Dann verliert die Caleuche für immer ihre Kraft.";
			link.l1 = "Tuttuathapak, bitte, sag mir, wo soll ich suchen? Irgendwelche Gedanken?";
			link.l1.go = "Tuttuat_38";
		break;
		
		case "Tuttuat_38":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "Nein. Denke daran, wo du den Jadetotenkopf zuletzt gesehen hast. Wem du ihn gegeben hast. Beginne dort zu suchen.";
				link.l1 = "In Ordnung, großer Schamane. Ich werde alles tun, was ich kann.";
				link.l1.go = "Tuttuat_39";
			}
			else
			{
				dialog.text = "Ein weißer Hexenmeister interessiert sich für den Schädel von Yum Cimil. Er sucht danach. Er kam sogar in unser Dorf. Ich hörte, der Hexenmeister lebe in einem Haus auf der niederländischen Insel. Suche den Hexenmeister auf der niederländischen Insel, und du könntest etwas erfahren.";
				link.l1 = "In Ordnung, großer Schamane. Ich werde alles tun, was ich kann.";
				link.l1.go = "Tuttuat_39";
			}
		break;
		
		case "Tuttuat_39":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
			AddQuestRecord("Caleuche", "23");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "I'll start with Curacao, where I handed it over to Solomon. Maybe I'll find some clue - to find out what happened to the skull.";
				else sTemp = "I'll start with visiting Curacao - there I've sold the jade skull to Joachim Merriman.";
			}
			else sTemp = "Tuttuathapak told me, that a 'white warlock' showed interest in the jade skull, and adviced seeking for him on Dutch islands. Who might that be?";
			AddQuestUserData("Caleuche", "sText", sTemp);
			if (GetCharacterIndex("Map_Caleuche") != -1)
			{
				sld = characterFromId("Map_Caleuche");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter("Map_Caleuche");
			}
			pchar.questTemp.Caleuche = "skul";
			pchar.quest.Caleuche_villemstad.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstad.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Caleuche_villemstad.function = "Caleuche_CreateMonk";
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Tuttuat_40":
			dialog.text = "Geh, Weißer. Finde den Jadetotenkopf von Yum Cimil.";
			if (pchar.questTemp.Caleuche == "island")
			{
				link.l1 = "Ich habe es hier, großer Schamane, schau mal.";
				link.l1.go = "Tuttuat_45";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Tuttuat_40_1";
			}
		break;
		
		case "Tuttuat_40_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_41":
			dialog.text = "Geh, weißer Mann. Finde den Jadetotenkopf von Yum Cimil.";
			link.l1 = "Ich befürchte, ich werde es nicht schaffen können. Ich habe den Hexenmeister gefunden, aber im letzten Moment ist er mit dem Schädel entkommen. Ich habe absolut keine Ahnung, wo er jetzt sein könnte.";
			link.l1.go = "Tuttuat_42";
		break;
		
		case "Tuttuat_42":
			dialog.text = "Das ist sehr schlecht, weißer Mann. Jetzt kannst du den Tempel nicht passieren und die Caleuche nicht besiegen. Ich gebe dir kein Geschenk. Jetzt gehst du.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_43";
		break;
		
		case "Tuttuat_43":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_44";
		break;
		
		case "Tuttuat_44":
			dialog.text = "Verlasse jetzt, weißer Mann.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_44_1";
		break;
		
		case "Tuttuat_44_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_45":
			dialog.text = "(blickend) Ja, das ist sie. Sehr schön. Und sehr beängstigend.";
			link.l1 = "Sicher... Aber was noch interessanter ist - Ich habe das gesamte karibische Meer von Kuba bis Dominica überquert, und die Caleuche hat nie versucht mich anzugreifen, als ich diesen Schädel hatte, habe ich es nicht mal gesehen. Und als ich Amulette zu dir brachte, hat es mich ständig verfolgt, sobald ich ausgesegelt bin, hat es mich in wenigen Stunden gefunden.";
			link.l1.go = "Tuttuat_46a";
		break;
		
		case "Tuttuat_46a":
			dialog.text = "Ich denke, der Caleuche hat Angst vor dem Schädel oder kann ihn nicht wahrnehmen. Ich habe keine andere Erklärung. Vielleicht hat Yum Cimil den Jadenschädel für den Caleuche sehr gefährlich gemacht - zusätzlich zum Fluch. Vielleicht ist das der Grund, warum der Kapitän so sehr danach trachtete, die drei Amulette meines Volkes zu nehmen. Um Weisheit zu erlangen, wie man den Zauber von Yum Cimil kontrolliert.";
			link.l1 = "Also, solange ich den Jadenschädel an Bord meines Schiffes habe, muss ich keine Angst vor den Angriffen der Caleuche haben?";
			link.l1.go = "Tuttuat_46b";
		break;
		
		case "Tuttuat_46b":
			dialog.text = "Genau, bleichgesichtiger. Du siehst es selbst.";
			link.l1 = "Sehr gut! Also, ich kann das Kommando über ein großes Schiff übernehmen, eine anständige Crew anheuern und eine nette Begrüßung für diesen wandelnden Toten vorbereiten, wenn der Zauber von ihm genommen wird, ohne Angst, dass er mich vorher abfangen würde...";
			link.l1.go = "Tuttuat_46c";
		break;
		
		case "Tuttuat_46c":
			dialog.text = "";
			link.l1 = "...übrigens, wo soll ich den Jadenschädel für diesen Zauber hinbringen?";
			link.l1.go = "Tuttuat_46";
		break;
		
		case "Tuttuat_46":
			dialog.text = "Du musst es zum Tempel von Chavins bringen und deine Reise beenden. Ich will dir eine Geschichte erzählen. Bist du bereit zuzuhören, weißer Mann?";
			link.l1 = "Meine Ohren sind immer offen für deine Weisheit, Tuttuathapak.";
			link.l1.go = "Tuttuat_47";
		break;
		
		case "Tuttuat_47":
			dialog.text = "Wie die Legenden meiner Vorfahren sagen, vor langer Zeit, als die bleichgesichtigen Männer noch nicht in unser Land gekommen waren, baute der große Häuptling der Chavins eine sehr, sehr große Kanu und schickte sie mit einer Kriegergruppe in das Land der vielen Inseln. Der Sohn des großen Häuptlings führte sie an, und dort war auch einer der hohen Schamanen. Im Land der vielen Inseln fanden sie eine öde Gegend und gründeten eine Siedlung und bauten einen großen Tempel für Yum Cimil, den nur unsere großen Vorfahren bauen konnten\nBoten kehrten mit guten Nachrichten zurück, aber niemand sah weder den Sohn des Häuptlings, noch den Schamanen noch die Krieger wieder. Die Legende besagt, dass sie dort geblieben sind, um zu leben, aber der weiseste der Schamanen sprach mit den Geistern und erzählte, dass dort niemand mehr lebte und dass Yum Cimil dieses Land regierte\nDas Land der vielen Inseln ist die Karibik, weißer Mann. Der Tempel von Yum Cimil ist auf einer Insel, wo weder weiße Männer noch Indianer leben. Nur die Diener von Yum Cimil, die Chavinavi, bewachen noch immer die Tempelkorridore.";
			link.l1 = "Und wo ist diese Insel?";
			link.l1.go = "Tuttuat_48";
		break;
		
		case "Tuttuat_48":
			dialog.text = "Ich nehme an, es ist klein und nördlich des Dorfes irgendwo in diesem großen Wasser, das ihr Ozean nennt, es ist nicht weit.";
			link.l1 = "Hmm... Nördlich von Dominica an der Meeresgrenze vielleicht? Verdammt noch mal - es ist ein sehr großes Gebiet im Meer! Wie soll ich dort eine kleine Insel finden, wenn niemand davon gehört hat?";
			link.l1.go = "Tuttuat_49";
		break;
		
		case "Tuttuat_49":
			dialog.text = "Ich kann es nicht besser erzählen. Aber ich kenne noch eine andere Geschichte. Du könntest sie von deinen Brüdern hören. Vor etwa zwanzig Wintern hat ein weißer Mann diese Insel gefunden. Mit einer Frau und einem alten Mann betritt er den Tempel von Yum Cimil und nimmt ein mächtiges Artefakt mit - die Kugel der aufgehenden Sonne. An den Ufern der Insel wird der bleichgesichtige Kapitän vom Caleuche angegriffen\nDer Bleichgesichtige ist schlau. Er blendet den Kapitän und die Crew des Caleuche mit der aufgehenden Sonne. Der Fluch des Caleuche schwächte sich ab und der Kapitän versenkte es, aber die Kugel der aufgehenden Sonne löste sich auf. Wenn du diesen bleichgesichtigen Mann findest, wird er dir sagen, wo die Insel ist.";
			if (CheckAttribute(pchar, "questTemp.NatanStory")) link.l1 = "Ha! Ich glaube, ich kenne diesen 'blassen Mann'... Die Geschichten klingen zu ähnlich. Also, die Caleuche wurde versenkt?";
			else link.l1 = "Hmm... Also, die Caleuche wurde versenkt?";
			link.l1.go = "Tuttuat_50";
		break;
		
		case "Tuttuat_50":
			dialog.text = "Ja, aber der Fluch schützt sie vor dem Tod. Sie haben es repariert und ihre ewige Reise fortgesetzt.";
			link.l1 = "In Ordnung, verstanden. Aber was soll ich im Tempel tun? Wo soll ich den Schädel hinlegen? Wie kann ich die Jaguar-Krieger besiegen, die ihn bewachen? Wenn sie die Chavinavi sind, wie die, die von diesem Hexer Merriman beschworen wurden, wäre es töricht, alleine dorthin zu gehen - jeder von ihnen ist so stark wie zehn Soldaten.";
			link.l1.go = "Tuttuat_51";
		break;
		
		case "Tuttuat_51":
			dialog.text = "Sie sind es nicht. Von weißem Hexer mit Schädel beschworene Chavinavi sind schwach. Viel schwächer als die, die von Yum Cimil selbst beschworen wurden. Du verletzt sie nie, und sie töten dich mit einer Berührung ihrer Waffe.";
			link.l1 = "Halt ein - und wie hat es dieser 'blassgesichtige Mann' geschafft, den Tempel zu betreten und das Artefakt zu stehlen?";
			link.l1.go = "Tuttuat_52";
		break;
		
		case "Tuttuat_52":
			dialog.text = "Bevor der erste bleichgesichtige Mann den Tempel betrat, wurde er von den Geistern der toten Ahnen bewacht. Der Bleichgesichtige war ein starker Krieger und er besiegte sie. Als er die Kugel der aufgehenden Sonne stahl, war Yum Cimil wütend. Er sandte Feuer und Schwefel auf den bleichgesichtigen Mann und zerstörte fast den Tempel, aber er entkam mit dem Artefakt. Jetzt hat Yum Cimil unbesiegbare Jaguar-Krieger herbeigerufen, um den Tempel zu bewachen.";
			link.l1 = "Herrlich! Und wie werde ich mich dann reinschleichen?";
			link.l1.go = "Tuttuat_53";
		break;
		
		case "Tuttuat_53":
			dialog.text = "Ich helfe dir, weißer Mann. Ich gebe dir zwei Chavins-Amulette, die du mir bringst. Ich spreche mit den Ahnengeistern und stärke das Amulett. Wenn du eines bei dir hast, kannst du gegen Jaguar-Krieger kämpfen wie gewöhnliche Soldaten, du wirst wie einer von ihnen sein, obwohl sehr stark. Amulett schützt dich und gibt dir Waffenkraft, um Chavinavi des Tempels zu schaden.";
			link.l1 = "Bist du sicher, dass die Amulette helfen werden?";
			link.l1.go = "Tuttuat_54";
		break;
		
		case "Tuttuat_54":
			dialog.text = "Mich wissen. Mich sprechen mit Ahnen. Mich großer Schamane. Du vertrauen mir. Du nehmen zwei Amulette. Eins schützt. Anderes stärkt Waffe. Ein Amulett musst du verwenden. Welches - du wählst. Wenn du kein Amulett trägst, wirst du den Jaguar-Kriegern zum Opfer fallen\nUnd du erinnern, dass um Mitternacht Yum Cimil alle Krieger, die du getötet hast, wieder zum Leben erweckt. Du musst die Zeit berechnen, um nicht zweimal gegen sie zu kämpfen, oder doch, die Geister sagen mir, dass du könntest.";
			link.l1 = "Ich sehe.";
			link.l1.go = "Tuttuat_55";
		break;
		
		case "Tuttuat_55":
			dialog.text = "Du nimmst Amulette. Hier sind sie. Du erinnerst dich, ihre Kraft hat Grenzen. Sie schwindet in einem Mond. Du erinnerst dich, dass ich gesagt habe, dass du ihre Kraft nicht halten kannst? Nur der große Schamane unseres Stammes kann sie halten.";
			link.l1 = "Ich erinnere mich. Also, ich habe nur einen Mond? Einen Monat?";
			link.l1.go = "Tuttuat_56";
		break;
		
		case "Tuttuat_56":
			dialog.text = "Ja. Wenn du zum Tempel Yum Cimil kommst, musst du den Schrein und eine große Statue des Kondors darin finden. Das ist der wichtigste Teil des Tempels. Hier legst du den Jadenschädel von Yum Cimil ab, und der Fluch wird vom Caleuche genommen. Wenn er dich wieder angreift, besiegst du ihn wie einen gewöhnlichen Mann. Dann bringst du mir das Amulett, das er dir genommen hat.";
			link.l1 = "Condor? Was ist das?";
			link.l1.go = "Tuttuat_57";
		break;
		
		case "Tuttuat_57":
			dialog.text = "Condor ist ein großartiger Vogel, der in den Bergen meiner Heimat lebt. Zum Gedenken an die Heimat haben die Vorfahren eine Condor-Statue in der Nähe des Schreins errichtet.";
			link.l1 = "Gut, ich werde danach suchen...";
			link.l1.go = "Tuttuat_58";
		break;
		
		case "Tuttuat_58":
			dialog.text = "Sei vorsichtig. Viele Gefahren lauern im Tempel neben Jaguar-Kriegern.";
			link.l1 = "Welche Gefahren?";
			link.l1.go = "Tuttuat_59";
		break;
		
		case "Tuttuat_59":
			dialog.text = "Ich weiß es nicht genau. Siehst du selbst. Es könnte eine Falle sein, oder eine... Verwirrung. Den Schrein zu betreten ist schwierig. Der Eingang ist versiegelt, und du musst einen Weg finden, ihn zu öffnen. Meine Vorfahren waren nicht nur große Krieger und Schamanen, sondern auch große Baumeister. Um ihn zu öffnen, musst du nachdenken.";
			link.l1 = "Heh! Klingt erschreckend, aber lass sie alle kommen! Ich werde keine Zeit verschwenden. Ich setze sofort Segel!";
			link.l1.go = "Tuttuat_60";
		break;
		
		case "Tuttuat_60":
			dialog.text = "Geh, weißer Krieger. Ich werde die Geister herbeirufen, um dir gegen die Jaguar-Krieger und die Caleuche zu helfen. Denke daran, wenn du Amulette benutzt, kann ich helfen, wenn nicht, wirst du zugrunde gehen";
			link.l1 = "Danke großer Schamane...Ich werde es erledigen.";
			link.l1.go = "Tuttuat_61";
		break;
		
		case "Tuttuat_61":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
			npchar.greeting = "Tuttuat_3";
			Log_Info("You have received two amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "kaleuche_amulet2");
			GiveItem2Character(pchar, "kaleuche_amulet3");
			// преобразуем амулеты
			ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_sword");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_shield");
			sld = ItemsFromID("kaleuche_amulet2");
			sld.picIndex = 13;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			sld = ItemsFromID("kaleuche_amulet3");
			sld.picIndex = 14;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			SetFunctionTimerCondition("Caleuche_TuttuatAmuletOver", 0, 0, 30, false); // таймер
			// делаем доступным Хаэль Роа
			n = FindIsland("KhaelRoa");
			Islands[n].visible = true;
			Island_SetReloadEnableGlobal(Islands[n].id, true);
			Islands[n].reload.l1.radius = 150.0;
			Islands[n].reload.l2.label = "Shore64_1";
			Islands[n].reload.l2.name = "reload_2";
			Islands[n].reload.l2.go = "";
			Islands[n].reload.l2.emerge = "";
			Islands[n].reload.l2.radius = 0.0;
			Islands[n].reload.l2.pic = 0;
			Islands[n].reload.l2.tex = "t1";
			pchar.questTemp.Caleuche = "khaelroa";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1 = "location";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1.location = "KhaelRoa_port";
			pchar.quest.Caleuche_khaelroa_arrive.function = "Caleuche_KhaelRoaArrive";
			AddQuestRecord("Caleuche", "34");
			if (CheckAttribute(pchar, "questTemp.NatanStory")) 
			{
				pchar.questTemp.Caleuche.NatanInfo = "true";
				AddQuestUserData("Caleuche", "sText", "But I have a clue: it seems that white captain, who had visited the temple of the Chavins, is none other than my good friend Nathaniel Hawk. I remember him saying that he had a map of that island in Maroon Town. Guess I will pay Nathan a visit.");
			}
			else AddQuestUserData("Caleuche", "sText", "That's a huge area in the sea, but I have no choice. I'll have to scour it entirely. Shaman said North of Dominica, and not too far so I could steadily move North, it might very well be a bit to the East or West. He also mentioned some Captain that destroyed the undead ship maybe I will be lucky and I might find him one day, alas, he said that I have only one month to hold this power or whatever it is, oh well it is what it is, let the search begin!");
		break;
		
		case "Tuttuat_62":
			if (pchar.questTemp.Caleuche == "regard" && CheckCharacterItem(pchar, "kaleuche_amulet1") && CheckCharacterItem(pchar, "kaleuche_amulet2") && CheckCharacterItem(pchar, "kaleuche_amulet3")) 
			{
				dialog.text = "Ich spreche mit Geistern. Du warst auf der Insel im Tempel von Yum Cimil. Hast du die Caleuche und das Amulett gefunden?";
				link.l1 = "Du hast recht, großer Schamane. Ich habe die Insel gefunden, bin in den Tempel eingetreten und habe den Jadenschädel hineingelegt.";
				link.l1.go = "Tuttuat_63";
			}
			else
			{
				dialog.text = "Geh, weißer Krieger.";
				if (CheckAttribute(pchar, "questTemp.Caleuche.AmuletOver"))
				{
					link.l1 = "Tuttuathapak, Sie sehen... Ich habe den Schädel nicht rechtzeitig zum Tempel gebracht, und Ihre Amulette haben ihre Kraft verloren.";
					link.l1.go = "Tuttuat_82";
				}
				else
				{
					link.l1 = "...";
					link.l1.go = "Tuttuat_62_1";
				}
			}
		break;
		
		case "Tuttuat_62_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
		break;
		
		case "Tuttuat_63":
			npchar.greeting = "Tuttuat_2";
			pchar.quest.Caleuche_TuttuatAmuletOver.over = "yes"; //снять таймер
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet2")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet3")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "Du hast den Fluch von der Caleuche aufgehoben. Hat sie dich danach gefunden?";
			link.l1 = "Ja. Wir haben uns direkt auf der Insel getroffen. Ich habe mich mit ihr im Kampf gemessen und bin siegreich hervorgegangen. Jetzt habe ich alle drei Amulette. Hier, nimm sie.";
			link.l1.go = "Tuttuat_64";
		break;
		
		case "Tuttuat_64":
			RemoveItems(pchar, "kaleuche_amulet1", 1);
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given three Chavin amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "Du schneller und starker Krieger, bleichgesichtiger. Tuttuathapak mag keine weißen Männer, aber ich respektiere tapfere und geschickte Krieger. Du hast sehr gut gemacht. Du hast die Meere von der Caleuche befreit. Du bringst mir drei Amulette. Ich belohne dich.";
			link.l1 = "Du hast etwas von 'Macht, die ich für immer halten werde' versprochen?";
			link.l1.go = "Tuttuat_65";
		break;
		
		case "Tuttuat_65":
			dialog.text = "Du sprichst die Wahrheit. Ich werde dir diese Macht geben. Niemand in der Karibik kennt das Geheimnis der Pflanze, das ich kenne. Höre mir zu, bleichgesichtiger! In meiner Heimat gibt es eine Heilpflanze. Wir nennen sie Manga Rosa. Hast du von dieser Pflanze gehört?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa.Tell"))
			{
				link.l1 = "Ja. Ich hielt es in meinen Händen. Zigeuner zeigen großes Interesse daran. Und eine von ihnen, die Heilerin Amelia, kann sogar...";
				link.l1.go = "Tuttuat_66";
			}
			else
			{
				link.l1 = "Keine Ahnung...";
				link.l1.go = "Tuttuat_66_1";
			}
		break;
		
		case "Tuttuat_66":
			dialog.text = "Ich höre von Kräuterhexe Amelia. Sie weiß wenig, aber nicht viel. Sie kennt das Geheimnis von Manga Rosa nicht. Nur der große Schamane aus meiner Heimat, von wo Manga Rosa hierher gebracht wurde, kann seine volle Kraft nutzen.";
			link.l1 = "Welche Macht?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_66_1":
			dialog.text = "Dieses Kraut wächst in meiner Heimat, kommt aber auch in der Karibik vor. Es ist eine hellgrüne hohe Pflanze, mit Blättern wie eine Palme mit gespreizten Fingern und angenehmem Geruch. Du wirst es sofort erkennen und mit nichts verwechseln. Ich kenne die Geheimnisse dieser Pflanze. Ich kann ihre Kraft extrahieren.";
			link.l1 = "Ich verstehe, aber welche Art von Macht?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_67":
			dialog.text = "Ich kann Tränke aus Manga Rosa machen. Sehr starke Tränke. Niemand außer mir in der Karibik kann diese herstellen. Meine Tränke machen den Mann für immer stärker, schneller, klüger, scharfsichtig, attraktiver und glücklicher. Ich braue für dich drei solche Tränke.";
			link.l1 = "Sehr interessant!";
			link.l1.go = "Tuttuat_68";
		break;
		
		case "Tuttuat_68":
			dialog.text = "Du großer Krieger, du brauchst zuerst einen Trank, um dich robuster zu machen und einen, um dich schneller zu machen. Und du wählst den dritten Trank, nachdem ich die ersten zwei gemacht habe. Aber du musst mir Manga Rosa bringen, um sie zu machen - ich habe keine.";
			link.l1 = "Wo sollte ich nach Manga Rosa suchen?";
			link.l1.go = "Tuttuat_69";
		break;
		
		case "Tuttuat_69":
			dialog.text = "Manga Rosa ist ein seltenes Kraut in der Karibik. Es wächst dort, wo die Leute nicht viel laufen. Dumme Leute pflücken es, trocknen es und rauchen es. Sehr dumme Leute. NICHT RAUCHEN! Es wäre eine Verschwendung von Kraft... Such den Dschungel und die Buchten, geheime Orte, an denen dumme Leute nicht treten. Schau sorgfältig hin. Für jeden Trank brauche ich fünf Stängel Manga Rosa.";
			link.l1 = "Also gut, großer Schamane. Ich komme zurück zu dir, sobald ich genug Manga Rosa habe.";
			link.l1.go = "Tuttuat_70";
		break;
		
		case "Tuttuat_70":
			dialog.text = "Geh, weißer Krieger. Bring mir Manga Rosa. Du wirst es nicht bereuen. Meine Tränke sind die besten. Ich sage den Geistern, sie sollen dir bei deiner Suche helfen.";
			link.l1 = "Danke! Bis zum nächsten Mal, Schamane!";
			link.l1.go = "Tuttuat_71";
		break;
		
		case "Tuttuat_71":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			pchar.questTemp.Caleuche = "mangarosa";
			pchar.questTemp.Caleuche.Mangarosa = 0;
			AddQuestRecord("Caleuche", "41");
		break;
		
		case "Tuttuat_72":
			dialog.text = "Bringst du fünf Stiele von Manga Rosa für den Trank?";
			if (GetCharacterItem(pchar, "cannabis7") >= 5)
			{
				link.l1 = "Ja. Hier sind fünf Pflanzen, die du brauchst.";
				link.l1.go = "Tuttuat_73";
			}
			link.l2 = "Noch nicht, großer Schamane. Meine Suche geht weiter...";
			link.l2.go = "Tuttuat_72_1";
		break;
		
		case "Tuttuat_72_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
		break;
		
		case "Tuttuat_73":
			RemoveItems(pchar, "cannabis7", 5);
			switch (sti(pchar.questTemp.Caleuche.Mangarosa))
			{
				case 0:
					dialog.text = "Sehr gut. Komm morgen, wenn die Sonne untergeht. Ich werde dir Tränke brauen, die deine Reaktion und Geschicklichkeit erhöhen.";
					link.l1 = "In Ordnung, Schamane. Ich komme morgen Abend.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 1;
				break;
				
				case 1:
					dialog.text = "Sehr gut. Komm morgen, sobald die Sonne untergeht. Ich werde dir Tränke brauen, die deine Ausdauer steigern werden.";
					link.l1 = "In Ordnung, Schamane. Ich komme morgen Abend.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 2;
				break;
				
				case 2:
					dialog.text = "Sehr gut. Welchen Trank möchtest du wählen? Trank der Stärke, scharfen Sicht, Intelligenz, Schönheit oder Glück?";
					link.l1 = "Trank der Stärke.";
					link.l1.go = "Tuttuat_77_1";
					link.l2 = "Trank der scharfen Sicht.";
					link.l2.go = "Tuttuat_77_2";
					link.l3 = "Trank der Intelligenz.";
					link.l3.go = "Tuttuat_77_3";
					link.l4 = "Trank der Schönheit.";
					link.l4.go = "Tuttuat_77_4";
					link.l5 = "Trank des Glücks.";
					link.l5.go = "Tuttuat_77_5";
				break;
			}
		break;
		
		case "Tuttuat_74":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1 = "Timer";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.hour  = 19.0;
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.function = "Caleuche_MangarosaPotion";
		break;
		
		case "Tuttuat_75":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Potion"))
			{
				sTemp = "";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1) sTemp = "  It make your movements faster, and you better fight with fine light weapons.";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2) sTemp = "  It make you more hardy in long journeys, and you better fight with sharp sabers.";
				dialog.text = "Trank fertig, bleichgesichtiger Krieger. Du nimmst es."+sTemp+"";
				link.l1 = "Danke dir, großer Schamane.";
				link.l1.go = "Tuttuat_76";
			}
			else
			{
				dialog.text = "Es ist noch nicht fertig, weißer Mann. Komm später. Stör mich nicht.";
				link.l1 = "Gut...";
				link.l1.go = "Tuttuat_75_1";
			}
		break;
		
		case "Tuttuat_75_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
		break;
		
		case "Tuttuat_76":
			if (sti(pchar.questTemp.Caleuche.Mangarosa) > 2)
			{
				dialog.text = "Ich braue für dich alle Tränke, die ich versprochen habe. Du wirst stärker. Bist du glücklich?";
				link.l1 = "Ja, großer Schamane. Das war in der Tat eine lohnende Belohnung.";
				link.l1.go = "Tuttuat_78";
			}
			else
			{
				dialog.text = "Du findest fünf weitere Stängel von Manga Rosa, du bringst sie zu mir. Ich mache dir einen weiteren Trank.";
				link.l1 = "Ich bringe dir mehr davon. Wir sehen uns!";
				link.l1.go = "Tuttuat_77";
			}
		break;
		
		case "Tuttuat_77":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1)
			{
				ChangeItemDescribe("kaleuche_amulet1", "itmdescr_kaleuche_amulet1_potion");
				sld = ItemsFromID("kaleuche_amulet1");
				sld.name = "itmname_kaleuche_amulet1_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet1");
			}
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2)
			{
				ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_potion");
				sld = ItemsFromID("kaleuche_amulet2");
				sld.name = "itmname_kaleuche_amulet2_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet2");
			}
		break;
		
		case "Tuttuat_77_1":
			dialog.text = "Komm morgen, wie gewohnt. Ich braue dir einen Trank, um dich stärker zu machen, und du kämpfst besser mit einer großen Axt.";
			link.l1 = "Gut.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 31;
		break;
		
		case "Tuttuat_77_2":
			dialog.text = "Komm morgen, wie üblich. Ich braue dir einen Trank, der deine Augen scharf macht, damit du jedes Ziel siehst, und du triffst besser mit feurigen Waffen, die brüllen.";
			link.l1 = "Gut.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 32;
		break;
		
		case "Tuttuat_77_3":
			dialog.text = "Komm morgen, wie üblich. Ich braue dir einen Trank, um dich klüger zu machen, und du solltest dich besser vor den Feinden verstecken.";
			link.l1 = "Gut.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 33;
		break;
		
		case "Tuttuat_77_4":
			dialog.text = "Komm morgen, wie gewohnt. Ich braue dir einen Trank, um dich hübscher zu machen, und du solltest besser die Leute überzeugen.";
			link.l1 = "Gut.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 34;
		break;
		
		case "Tuttuat_77_5":
			dialog.text = "Komm morgen, wie üblich. Ich braue dir einen Trank, um dich glücklicher zu machen, und du hast Glück.";
			link.l1 = "Gut.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 35;
		break;
		
		case "Tuttuat_78":
			dialog.text = "Mich freut, dass dir meine Kunst gefällt, die Kunst des großen Schamanen.";
			link.l1 = "Sag mal, Tuttuathapak, wofür brauchtest du diese drei Amulette? Nur aus Neugier...";
			link.l1.go = "Tuttuat_79";
		break;
		
		case "Tuttuat_79":
			dialog.text = "Du spürst bereits die Kraft dieser beiden Amulette. Die Geister werden mir helfen, ihnen Macht zu verleihen, und alle drei Amulette zusammen verleihen große schamanische Weisheit und die Erleuchtung meiner Vorfahren, der großen Chavins.";
			link.l1 = "Ich verstehe. Nochmals vielen Dank für deine ausgezeichneten Tränke. Du bist wirklich ein großer Schamane. Es ist Zeit für mich zu gehen. Leb wohl, Tuttuathapak, ich hoffe, wir sehen uns wieder.";
			link.l1.go = "Tuttuat_80";
		break;
		
		case "Tuttuat_80":
			dialog.text = "Auf Wiedersehen, weißer Krieger. Du suchst mich nicht mehr. Ich gehe in die Einsamkeit, um die Weisheit meiner Vorfahren zu begreifen. Mögen die Geister dir auf deinen Reisen helfen!";
			link.l1 = "Nun denn... hah... mögen die Geister auch deinen Weg erhellen, großer Schamane. Lebewohl...";
			link.l1.go = "Tuttuat_81";
		break;
		
		case "Tuttuat_81":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			GiveItem2Character(pchar, "kaleuche_amulet3");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_potion");
			sld = ItemsFromID("kaleuche_amulet3");
			sld.name = "itmname_kaleuche_amulet3_potion";
			sld.groupID = SPECIAL_ITEM_TYPE;
			sld.picIndex = 15;
			sld.picTexture = "ITEMS_35";
			sld.price = 0;
			sld.Weight = 1.0;
			sld.reaction = sti(pchar.questTemp.Caleuche.Mangarosa);
			sld.ItemType = "SUPPORT";
			i = sti(sld.reaction);
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet"+i+"_potion");
			AddQuestRecord("Caleuche", "42");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			DeleteAttribute(pchar, "questTemp.Caleuche.Mangarosa");
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
		break;
		
		case "Tuttuat_82":
			Log_Info("You have given amulets");
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			dialog.text = "Du machst mich traurig, bleichgesicht. Ich führe Ritual mit Geistern durch, um diesen Amuletten Kraft zu verleihen, und du verschwendest es. Ich bin traurig. Du gehst jetzt. Tuttuathapak hat nichts mehr zu sagen.";
			link.l1 = "Es tut mir leid, ich hatte wirklich Pech... Nun, Lebewohl, Schamane.";
			link.l1.go = "Tuttuat_83";
		break;
		
		case "Tuttuat_83":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Caleuche", "43");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			sld = ItemsFromID("SkullAztec");
			sld.price = 10000;
		break;

		// капитан Калеуче
		case "CaleucheCap":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_01.wav");
			dialog.text = "Es ist alles umsonst, Seemann. Du wirst mich nicht besiegen. Und all meine Männer, die auf dem Deck liegen, werden ihre Knochen zusammenfügen und vor der Morgendämmerung wieder aufstehen. Wir können nicht getötet werden, denn der Tod hat uns für immer verlassen.";
			link.l1 = "Verdammt! Bist du tot oder lebendig? Wahrscheinlich immer noch lebendig - die Toten liegen normalerweise still und schwingen keine Schwerter. Aber wer bist du und warum hast du mein Schiff angegriffen?";
			link.l1.go = "CaleucheCap_1";
		break;
		
		case "CaleucheCap_1":
			dialog.text = "Ich bin Balthazar de Cordes vom Fliegenden Herzen. Armselige Feiglinge, die nichts über mich wissen, nennen mich Van der Decken, Kapitän des Fliegenden Holländers. Aber das spielt keine Rolle. Was zählt, ist, dass du ein Amulett bei dir hast, das ich jetzt nehmen werde. Ich brauche es! Ich fühle es! Das große Amulett der Chavins, eines von dreien, wird endlich mir gehören! Knie nieder vor mir, Sterblicher! Und ich könnte deinen Tod schmerzlos machen!";
			link.l1 = "Verpiss dich, Leiche!";
			link.l1.go = "CaleucheCap_2";
		break;
		
		case "CaleucheCap_2":
			DialogExit();
			npchar.MultiFighter = 4.0;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(pchar, 10, true, "Caleuche_GhostshipGetOut");
		break;
		
		case "CaleucheCap_3":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_02.wav");
			dialog.text = "Ich kann es nicht glauben! Es ist so lange her, dass ich mein eigenes Blut gesehen und Schmerz gespürt habe...WIE?!";
			link.l1 = "Diesmal hast du verloren, Balthazar de Cordes. Ich kenne deine Geschichte. Der Jadenschädel wurde zum Tempel von Chavins zurückgebracht und der Fluch von Yum Cimil lastet nicht mehr auf dir oder deinen Matrosen. Du wirst deine Seeleute nicht mehr zum Leben erwecken.";
			link.l1.go = "CaleucheCap_4";
		break;
		
		case "CaleucheCap_4":
			dialog.text = "Oh, also hältst du dich wohl für einen Erlöser, ja? Nein! Balthazar de Cordes wird sein kleines Restleben teuer verkaufen!";
			link.l1 = "Die letzte Reise des fliegenden Herzens endet hier, in Khael Roa. Und du wirst dein Schiff nicht vom Meeresboden heben, wie du es vor fünfundzwanzig Jahren getan hast.";
			link.l1.go = "CaleucheCap_5";
		break;
		
		case "CaleucheCap_5":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_03.wav");
			dialog.text = "Achtung! Fünfundzwanzig Jahre sind vergangen, und ich erinnere mich daran, als wäre es erst gestern gewesen. Die Strahlung jener Kugel, die uns blendete und mein Schiff in zwei Hälften spaltete. Das war die erste und letzte Niederlage des Fliegenden Herzens und Balthazar de Cordes... Also lass uns das letzte Mal kreuzen, Kapitän! Der Tod im Kampf ist leicht und willkommen!";
			link.l1 = "...";
			link.l1.go = "CaleucheCap_6";
		break;
		
		case "CaleucheCap_6":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Caleuche_ChangeShip");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// --> // наш матрос на берегу
		case "on_coast":
			dialog.text = "Endlich bist du aufgewacht, Kapitän... Wie fühlst du dich?";
			link.l1 = "Verdammt, was ist passiert? Mein Kopf zerspringt vor Schmerz...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Als wir in die Kajüte des Kapitäns eintraten, lagst du noch regungslos auf dem Boden. Die Jungs hoben dich hoch und schleiften dich zu unserem Schiff - und gerade rechtzeitig, da die toten Männer auf dem Deck wieder aufzustehen begannen\nHeiligste Jungfrau und alle Heiligen! Wir schnitten schnell die Leinen durch und versuchten wegzusegeln, aber eine Salve von ihrem Schiff verwandelte unsere alte Kiste schnell in Splitter und wir verloren die Kontrolle über sie. Dann setzten sie die Segel und waren im Nu verschwunden\nUnser Schiff lief auf Grund, und jeder, der es geschafft hat zu überleben, hat das Ufer in einem Boot erreicht. Viele gute Männer sind heute gestorben... wenn wir nur an Bord geblieben wären... Aber wir waren sicher, dass der Sturm das Schiff endgültig fertig machen wird.";
			link.l1 = "Nicht eure Schuld, Herren. Es war die richtige Entscheidung. Danke, ich werde mich daran erinnern.";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Wir zogen dich ins Boot und brachten dich dann an Land. Du warst fast tot...";
			link.l1 = "Ich schulde dir mein Leben. Wie lange lag ich hier bewusstlos?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Für einen ganzen Tag. Wir haben deine Wunden gewaschen und verbunden, dir Medizin gegeben und etwas Rum in dich hineingegossen. Du solltest bald wieder gesund sein.";
			link.l1 = "Ich werde dieses Mal sicherlich nicht sterben. Obwohl ich mich nicht wirklich gut fühle...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Das ist sicher... War es der Fliegende Holländer, Käpt'n? Warum haben sie uns angegriffen? Und warum haben sie nicht vor dem Entern auf uns geschossen, sondern unser Schiff später mit nur einer Salve fast versenkt?";
			link.l1 = "Ihr Kapitän brauchte das Amulett, von dem ich mit Tuttuathapak, einem indischen Schamanen, gesprochen hatte. Deshalb haben sie uns nicht sofort versenkt, aber als ihr Anführer das Amulett nahm, haben sie uns schnell beseitigt... Was für ein Alptraum! Ein Schiff, bemannt von den Toten! Unmöglich zu glauben...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Ja, jetzt war es an uns, dem Fliegenden Holländer zu begegnen. Wenn ich die Chance habe, gehe ich in die Kirche, zünde die Kerze für meine wundersame Rettung an und bete zu unserem Herrn...";
			link.l1 = "Ich auch... denke ich. Aber zuerst gehe ich zurück zu diesem Dorf. Ich muss Tuttuathapak alles darüber erzählen. Dieses verfluchte Schiff hat uns wegen des Amuletts angegriffen! Ich bin sicher, dass dieser rothäutige Teufel einige Ideen hatte, warum zum Teufel diese Lebenden Toten es gebraucht haben könnten.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "In Ordnung. Aber seien Sie vorsichtig, Kapitän, Ihre Wunden sind kaum verheilt, nehmen Sie zumindest jemanden mit, nur für den Fall.";
			link.l1 = "Ich werde vorsichtig sein, ich verspreche es. Danke, dass du mich nicht verlassen hast!";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "Wovon sprichst du, Käpt'n! Für dich würden wir bis ans Ende der Welt gehen und Tausende von Untoten bekämpfen! Es ist eine verdammte Schande, dass wir so viel verloren haben, aber diese Geschichte wird in Legenden leben.";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		
		// Фергус Хупер
		case "fergus":
			dialog.text = "He! Ich habe noch nicht genug Schlangenhäute gesammelt, um sie dir zu verkaufen, also verpiss dich!";
			link.l1 = "Hmm... Bist du Fergus Hooper?";
			link.l1.go = "fergus_1";
		break;
		
		case "fergus_1":
			dialog.text = "Nein, mein Name ist Tuttuathapak, und ich werde dich verfluchen, wenn du nicht sofort verschwindest. Also beeil dich besser, oder du wirst...";
			link.l1 = "...verliere den Verstand, verbrenne mein eigenes Schiff, und meine Matrosen werden mich töten und all meine Habseligkeiten nehmen. Richtig?";
			link.l1.go = "fergus_2";
		break;
		
		case "fergus_2":
			sld = characterFromId(pchar.questTemp.Caleuche.Amuletmaster);
			dialog.text = "Arrgh... Was zur Hölle, wer bist du!? Wie hast du...";
			link.l1 = "Wir haben einen gemeinsamen Freund, Fergus. Er ist ein Leuchtturmwärter und sein Name ist "+GetFullName(sld)+". Er hat mir von dir erzählt und mich geschickt, dich zu suchen. Übrigens, ich kenne Schamane Tuttuathapak persönlich, also hat dein Witz nicht funktioniert, tut mir leid. Hör zu, ich suche keine Schwierigkeiten. Ich möchte etwas von dir kaufen, und es sind nicht die Schlangenhäute.";
			link.l1.go = "fergus_3";
		break;
		
		case "fergus_3":
			dialog.text = "Ach, also kennst du meinen alten Freund! Wie geht es ihm? Ist er noch nicht vor Langeweile in seinem Leuchtturm gestorben? Bitte, setz dich, Seemann, trink mit mir!";
			link.l1 = "Es tut mir leid, Fergus, ich habe wirklich nicht viel Zeit. Hör zu, ich brauche dieses indische Amulett, eines von denen, die dein verstorbener Kapitän von der Main mit Tuttuathapak genommen hat. Ich werde einen guten Preis dafür zahlen, und du wirst dich von einem gefährlichen Krimskrams befreien.";
			link.l1.go = "fergus_4";
		break;
		
		case "fergus_4":
			dialog.text = "Und was ist so gefährlich daran? Ich habe bisher keinen Schaden davon gesehen. Es ist nur ein nutzloser Stein";
			link.l1 = "Das liegt daran, dass du nicht mehr die Meere befährst. Bis vor kurzem hatte ich einen ähnlichen Amulett. Ein Geisterschiff jagt diese Dinge.";
			link.l1.go = "fergus_5";
		break;
		
		case "fergus_5":
			dialog.text = "Machst du Witze, Kumpel? Vielleicht hat dich das Wissen um Tuttuathapak belastet? Sei vorsichtig, Kapitän, dieser rothäutige Teufel wird deinen Verstand verschlingen...";
			link.l1 = "Glaube mir oder nicht, aber ich sage die Wahrheit. Ich würde es selbst nicht glauben, wenn ich es nicht mit meinen eigenen Augen gesehen hätte, ich kann auf das Buch schwören oder du kannst diejenigen fragen, die bei mir waren. Ich habe kaum überlebt nach dieser Begegnung mit dem Caleuche.";
			link.l1.go = "fergus_6";
		break;
		
		case "fergus_6":
			dialog.text = "Der Caleuche?";
			link.l1 = "Nun, die meisten nennen es Fliegender Holländer, aber sein wahrer Name ist Fliegendes Herz. Was auch immer. Verkaufe mir einfach diesen Amulett. Es ist sowieso nutzlos für dich, das weiß ich.";
			link.l1.go = "fergus_7";
		break;
		
		case "fergus_7":
			dialog.text = "Das stimmt. Das ist nur ein nutzloses Schmuckstück, obwohl recht schön. Hör zu, ich hätte es dir ohne weiteres verkauft, aber du siehst - ich habe es nicht mehr. Es wurde aus meiner Hütte gestohlen, unter anderem, während ich im Dschungel jagen war. Das passierte ziemlich kürzlich, vor etwa einem Monat. Tut mir leid, aber ich kann dir nicht weiterhelfen.";
			link.l1 = "Und wer hat es gestohlen?";
			link.l1.go = "fergus_8";
		break;
		
		case "fergus_8":
			dialog.text = "Sind Sie ernsthaft der Meinung, dass ich hier sitzen würde, wenn ich wüsste, wer mein Zuhause ausgeräumt hat? Es gibt eine Bande von Dieben und Briganten, die außerhalb von Belize arbeiten, und sie haben Informanten in der Stadt. Nun, zumindest denkt das der Kommandant. Ich bin mir sicher, dass sie es waren.";
			link.l1 = "Der Kommandant weiß von den Banditen und tut immer noch nichts?";
			link.l1.go = "fergus_9";
		break;
		
		case "fergus_9":
			dialog.text = "Ob er etwas tut oder nicht, weiß ich nicht. Das Einzige, was ich sicher weiß, ist, dass meine Sachen weg sind, und dein wertvolles Amulett mit ihnen. Versuch, diese Banditen ausfindig zu machen - vielleicht findest du es in ihren Taschen. Es ist unwahrscheinlich, dass sie es verkaufen konnten - Händler haben keine Verwendung für solche Dinge.";
			link.l1 = "In Ordnung, ich werde zum Kommandanten gehen. Viel Glück, Fergus!";
			link.l1.go = "fergus_10";
		break;
		
		case "fergus_10":
			DialogExit();
			AddQuestRecord("Caleuche", "9");
			pchar.questTemp.Caleuche.Bandos = "start"; 
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		// бандит в городе
		case "Beliz_townbandos":
			dialog.text = "He! Was brauchst du? Ich erwarte keine Gäste. Verschwinde!";
			link.l1 = "Warum so unhöflich, Freund? Ich wollte nur fragen...";
			link.l1.go = "Beliz_townbandos_1";
		break;
		
		case "Beliz_townbandos_1":
			dialog.text = "Hast du nicht gehört? Verpiss dich, oder ich werfe dich zur Tür raus!";
			link.l1 = "Hmm... Nun, vielleicht bist du doch die Person, die ich suche. Du scheinst viel zu nervös zu sein, Kumpel...";
			link.l1.go = "Beliz_townbandos_2";
		break;
		
		case "Beliz_townbandos_2":
			dialog.text = "Du hältst dich für zu schlau, nicht wahr? Noch einmal: Entweder du verschwindest jetzt sofort, oder ich rufe die Wachen, und sie werden dich hinter Gitter werfen!";
			link.l1 = "Werft mich hinter Gitter? Wie sehr interessant. Weißt du, jetzt bin ich fast sicher, dass ich denjenigen gefunden habe, den ich gesucht habe. Gut, ich stimme zu. Lasst uns die Wachen rufen und dann gehen wir zusammen zum Kommandantenbüro, wie eine glückliche Familie. Ich war gerade dort, also erinnere ich mich an den Weg... Wachen! WACHEN!";
			link.l1.go = "Beliz_townbandos_3";
		break;
		
		case "Beliz_townbandos_3":
			dialog.text = "Zum Teufel mit dir! Ich werde dich durchbohren!";
			link.l1 = "Oh ho-ho! Nun, du kannst es versuchen!";
			link.l1.go = "Beliz_townbandos_4";
		break;
		
		case "Beliz_townbandos_4":
			DialogExit();
			DeleteAttribute(npchar, "CityType");
			DeleteAttribute(npchar, "city"); // чтобы не было НЗГ
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_BelizTownbandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.Caleuche_letter.win_condition.l1 = "item";
			pchar.quest.Caleuche_letter.win_condition.l1.item = "kaleuche_letter";
			pchar.quest.Caleuche_letter.function = "Caleuche_FindLetter";
		break;
		
		// главарь лесных бандосов
		case "Beliz_forestbandos":
			dialog.text = "He, Reisender! Willkommen, willkommen... Abendessen, Unterkunft - alles für Ihr Geld. Also, bereiten Sie sich darauf vor, Ihre Taschen umzustülpen!";
			link.l1 = "Nicht so schnell, mein guter Mann. Ich habe Geschäfte mit Ihnen.";
			link.l1.go = "Beliz_forestbandos_1";
		break;
		
		case "Beliz_forestbandos_1":
			dialog.text = "Geschäft? Ha-ha! Dein einziges Geschäft ist es, mir all dein Silber und Gold zu geben!";
			link.l1 = "Halt endlich die Klappe. Ich habe dir einen Brief aus Belize gebracht, auf den du gewartet hast. Der Bote konnte nicht mit den Wächtern klarkommen und hat die Angelegenheit mir anvertraut.";
			link.l1.go = "Beliz_forestbandos_2";
		break;
		
		case "Beliz_forestbandos_2":
			dialog.text = "Zeig es mir!";
			link.l1 = "Hier...";
			link.l1.go = "Beliz_forestbandos_3";
		break;
		
		case "Beliz_forestbandos_3":
			Log_Info("You have given a note");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "kaleuche_letter", 1);
			dialog.text = "(liest) Hm... Das ist sicherlich seltsam... Wie bist du da reingeraten?";
			link.l1 = "Ich habe es dir schon gesagt, sie haben deinen Kerl geschnappt, also habe ich seinen Job übernommen. Er versprach Geld und einen herzlichen Empfang von dir...";
			link.l1.go = "Beliz_forestbandos_4";
		break;
		
		case "Beliz_forestbandos_4":
			dialog.text = "A warm welcome? Alright, pal. We'll warm you up, feed you, give you money and all that stuff - but you, you too, will have to prove us that you're not a guards' hound. We've got a score to settle now\nA merchant has recently arrived to a nearby cove; apparently, he wants to sneak into the city with his wares past the customs office. But we will still exact the duty from him. We are lawful folk after all! You'll come with us. Do you know which end of the sword goes where?";
			link.l1 = "Und bekomme ich einen Anteil an dieser Pflicht?";
			link.l1.go = "Beliz_forestbandos_5";
		break;
		
		case "Beliz_forestbandos_5":
			dialog.text = "Sicher wirst du! Wenn du mutig im Kampf bist und am Leben bleibst. Aber erwarte keinen Spaziergang, der Händler ist nicht allein, er hat eine Eskorte, und eine sehr große Eskorte. Nun, es ist Zeit zu gehen - unsere Beute ist nah. Jungs! Bereitet eure Waffen vor, wir brechen auf!";
			link.l1 = "...";
			link.l1.go = "Beliz_forestbandos_6";
		break;
		
		case "Beliz_forestbandos_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LocatorReloadEnterDisable(pchar.location, "reload2_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload3_back", true);
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Beliz_forestbandos_"+i);	
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Beliz_ExitTown", "goto", "goto"+(rand(1)+1), "", 10.0);
			}
			DoQuestCheckDelay("OpenTheDoors", 12.0);
			pchar.quest.Caleuche_bandosrobb.win_condition.l1 = "location";
			pchar.quest.Caleuche_bandosrobb.win_condition.l1.location = "Beliz_ExitTown";
			pchar.quest.Caleuche_bandosrobb.function = "Caleuche_JungleBandosRobbery";
		break;
		
		case "Beliz_forestbandos_7":
			dialog.text = "Ich sehe, du bist kein Feigling. Gut gemacht! Du hast deinen Anteil verdient. Wie möchtest du ihn haben? Bargeld? Ware? Sie hatten viel Alkohol dabei, sicher ist er viel wert.";
			link.l1 = "Geld.";
			link.l1.go = "Beliz_forestbandos_8_1";
			link.l2 = "Ware.";
			link.l2.go = "Beliz_forestbandos_8_2";
		break;
		
		case "Beliz_forestbandos_8_1":
			Log_Info("You have received 100 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Hier hast du! Und diese Geldbörse ist für die Zustellung des Briefes.";
			link.l1 = "Danke! So mag ich es!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_8_2":
			Log_Info("You have received 30 bottles of rum");
			Log_Info("You have received 12 bottles of wine");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "potionrum", 30);
			TakeNItems(pchar, "potionwine", 12);
			dialog.text = "Hier hast du es! Trink dich nur nicht zu Tode, ha-ha-ha! Und dieser Beutel ist für die Zustellung des Briefes.";
			link.l1 = "Danke! So gefällt es mir!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_9":
			Log_Info("You have received a purse");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "purse2", 1);
			dialog.text = "Du siehst für mich aus wie ein anständiger Kerl. Wie wäre es mit einer weiteren Partitur? Es geht um diesen Brief, den du mir hast zustellen lassen.";
			link.l1 = "Sicher.";
			link.l1.go = "Beliz_forestbandos_10";
		break;
		
		case "Beliz_forestbandos_10":
			dialog.text = "Dann komm zur Höhle. Es gibt zwei davon. Geh in den Dschungel zum Punkt, an dem wir uns zuletzt getroffen haben, dann nimm den linken Weg. Wir treffen uns in drei Tagen am Eingang zur Höhle, von Mitternacht bis eins. Hast du das verstanden? Wenn du ein braver Junge bist, nehmen wir dich in unsere Bande auf. Aber behalte im Hinterkopf - wenn du in der Stadt irgendwas ausplauderst, bist du erledigt. Ich habe einen langen Arm.";
			link.l1 = "Hör schon auf, mir Angst zu machen. Ich habe es verstanden. Ich werde still sein wie ein Fisch. Warte drei Tage auf mich, ich werde da sein. Ich liebe leicht verdientes Geld!";
			link.l1.go = "Beliz_forestbandos_11";
		break;
		
		case "Beliz_forestbandos_11":
			dialog.text = "Also gut, Kumpel. Verschwinde jetzt, bevor die Wachen hierher kommen. Wir gehen auch.";
			link.l1 = "Bis dann, Kumpel...";
			link.l1.go = "Beliz_forestbandos_12";
		break;
		
		case "Beliz_forestbandos_12":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload2_back", false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload3_back", false);
			LocatorReloadEnterDisable("Beliz_CaveEntrance_2", "reload1_back", true); // закрываем пещеру
			SetFunctionTimerCondition("Caleuche_CaveOpen", 0, 0, 1, false); // таймер
			SetFunctionTimerCondition("Caleuche_BelizbandosClear", 0, 0, 4, false); // таймер
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			for (i=1; i<=6; i++)
			{
				if (GetCharacterIndex("Beliz_forestbandos_"+i) != -1)
				{
					sld = characterFromId("Beliz_forestbandos_"+i);	
					LAi_SetActorType(sld);
					LAi_group_MoveCharacter(sld, "TMP_FRIEND");
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "OpenTheDoors", 20.0);
				}
			}
			AddQuestRecord("Caleuche", "13");
			// костер
			ref location = &Locations[FindLocation("Beliz_Jungle_01")];
			DeleteAttribute(location, "fire");
			sld = ItemsFromID("fire");
			sld.shown = false;
			// пакуем схрон в пещере
			pchar.GenQuestBox.Beliz_Cave_2 = true;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.kaleuche_amulet2 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.suit4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse1 = 7; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse2 = 3; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potion2 = 10;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potionrum = 55;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.indian_3 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.obereg_4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.berserker_potion = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry2 = 15;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry3 = 33;
			// меняем флаг
			pchar.questTemp.Caleuche.Bandos = "know";
			SaveCurrentQuestDateParam("questTemp.Caleuche.belizbandos");
		break;
		
		// спалили бандосы в пещере
		case "Beliz_cavebandos":
			dialog.text = "Was! Ich nehme an, du hast beschlossen, etwas von unserem Eigentum zu beanspruchen? Du wirst damit nicht davonkommen, du dreckiger Wurm!";
			link.l1 = "Wen hast du gerade einen Wurm genannt, du Abschaum?!";
			link.l1.go = "Beliz_cavebandos_1";
		break;
		
		case "Beliz_cavebandos_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Beliz_cavebandos_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Beliz_cavebandos_3", "citiz_23", "man", "man", 30, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 30, 70, 70, "blade_10", "pistol1", "bullet", 150);
				ChangeCharacterAddressGroup(sld, pchar.location, "monsters", "monster16");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_CaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// капитан гарпии
		case "reginald":
			dialog.text = "Hallo, Kollege! Was hat dich hierher gebracht?";
			link.l1 = TimeGreeting()+", Mynheer Jackson. Ich bin froh, Sie endlich gefunden zu haben.";
			link.l1.go = "reginald_1";
		break;
		
		case "reginald_1":
			dialog.text = "'Mynheer Jackson', ha-ha! Nun, um ehrlich zu sein, werde ich mich bald auch so nennen. Ich arbeite ohne Unterbrechung für diese verfluchte Firma... aber sie zahlen gut, sehr gut!.. Also, was verschlägt dich hierher, Kamerad?";
			link.l1 = "Unser gemeinsamer Bekannter, der Leuchtturmwärter, hat mir erzählt, dass du einen alten indischen Amulett hast. Ich schätze, du hast es nie benutzt, und ich brauche es wirklich dringend. Ich möchte es von dir kaufen.";
			link.l1.go = "reginald_2";
		break;
		
		case "reginald_2":
			dialog.text = "Oh, du meinst diesen schicken Krimskrams, nach dem ich bei diesem pensionierten Bootsmann gefragt hatte? Ja, Freund, du hast recht, es war eigentlich nie nützlich, es sieht einfach hübsch aus.";
			link.l1 = "Wie viel willst du dafür haben?";
			link.l1.go = "reginald_3";
		break;
		
		case "reginald_3":
			dialog.text = "Weißt du, es gibt da ein kleines Problem... Lass es mich erklären. Ich habe es im Moment nicht bei mir. Da ich nie einen Nutzen dafür fand, habe ich es in meiner Truhe am Ufer gelassen, zusammen mit meinen anderen Habseligkeiten.";
			link.l1 = "Oh, das erklärt, dass du noch... na ja, egal. Lass uns einfach zu deiner Truhe gehen, und ich kaufe dir das Amulett ab. So einfach ist das. Wo hast du es?";
			link.l1.go = "reginald_4";
		break;
		
		case "reginald_4":
			dialog.text = "Es ist nicht ganz so einfach. Meine Truhe befindet sich auf Barbados, im Leuchtturmturm, und sie ist sicher verschlossen, damit niemand sie in meiner Abwesenheit ausnutzen kann. Und es tut mir wirklich leid, aber ich kann nicht mit Ihnen nach Barbados fahren, laut meinem Vertrag mit den Niederländern muss ich zwischen Philipsburg und Port Royal segeln und genau nach dem Fahrplan halten. Und Barbados liegt nicht auf dieser Route.";
			link.l1 = "Und was können wir tun? Ich brauche dieses Amulett wirklich, wirklich!";
			link.l1.go = "reginald_5";
		break;
		
		case "reginald_5":
			dialog.text = "Hmm... Nun, es gibt eine Option. Ich gebe dir den Schlüssel zu meiner Truhe, und du segelst alleine nach Barbados. Aber du musst mir alle Sachen, die darin sind, kompensieren und du kannst sie haben. Es tut mir leid für das Misstrauen - aber du musst verstehen. Ich habe dich noch nie zuvor gesehen.";
			link.l1 = "Wie viel?";
			link.l1.go = "reginald_6";
		break;
		
		case "reginald_6":
			dialog.text = "Fünfhundert Goldmünzen. Nicht weniger.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Du hast es! Hier ist dein Gold.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Hmm... Ich habe nicht so viele Dublonen bei mir.";
			link.l2.go = "reginald_7";
		break;
		
		case "reginald_7":
			dialog.text = "Dann komm wieder zu mir, wenn du das Geld aufgetrieben hast. Wenn du mich einmal gefunden hast, wirst du mich wieder finden. Ich werde nun für einige Zeit zwischen St. Martin und Jamaika segeln.";
			link.l1 = "In Ordnung, Abmachung.";
			link.l1.go = "reginald_8";
		break;
		
		case "reginald_8":
			DialogExit();
			NextDiag.CurrentNode = "reginald_9";
			npchar.DeckDialogNode = "reginald_9";
		break;
		
		case "reginald_9":
			dialog.text = "Du schon wieder, Freund? Hast du 500 Münzen?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Ja. Hier ist dein Gold.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Noch nicht, aber ich arbeite daran.";
			link.l2.go = "reginald_8";
		break;
		
		case "reginald_10":
			Log_Info("You have given 500 doubloons");
			PlaySound("interface\important_item.wav");
			RemoveDublonsFromPCharTotal(500);
			DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
			dialog.text = "Großartig! Und hier ist dein Schlüssel. Und ich habe nur eine Bitte: nachdem du alles genommen hast, was drin ist, bitte lasse den Schlüssel im Schloss. Ich würde es hassen, ein neues Schloss und einen Schlüssel dafür in Auftrag geben zu müssen.";
			link.l1 = "In Ordnung.";
			link.l1.go = "reginald_11";
		break;
		
		case "reginald_11":
			dialog.text = "Dann viel Glück, Freund! Gute Reise!";
			link.l1 = "Und das Gleiche für dich... Gute Reise, Mynheer Jackson!";
			link.l1.go = "reginald_12";
		break;
		
		case "reginald_12":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			DeleteAttribute(pchar, "questTemp.Caleuche.Garpiya");
			DeleteAttribute(pchar, "questTemp.Garpiya");
			GiveItem2Character(pchar, "kaleuche_key"); 
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
			AddQuestRecord("Caleuche", "20");
			// сундук со схроном
			i = Findlocation("Mayak2");
			Locations[i].models.always.locators = "lighthouse_Blocators";
			locations[i].private1.key = "kaleuche_key";
			locations[i].private1.key.delItem = true;
			locations[i].private1.items.kaleuche_amulet3 = 1;
			locations[i].private1.items.pistol9 = 1;
			locations[i].private1.items.indian_6 = 1;
			locations[i].private1.items.map_barbados = 1;
			locations[i].private1.items.map_part2 = 1;
			locations[i].private1.items.jewelry22 = 5;
			locations[i].private1.items.jewelry17 = 6;
			locations[i].private1.items.jewelry12 = 3;
			locations[i].private1.items.jewelry16 = 2;
			locations[i].private1.items.jewelry20 = 7;
			locations[i].private1.items.jewelry53 = 11;
			locations[i].private1.items.mineral25 = 1;
			locations[i].private1.items.mineral21 = 1;
			locations[i].private1.items.mineral22 = 5;
			locations[i].private1.items.mineral26 = 1;
			locations[i].private1.items.mineral10 = 1;
			locations[i].private1.items.mineral3 = 10;
			pchar.quest.caleuche_amulet3.win_condition.l1 = "item";
			pchar.quest.caleuche_amulet3.win_condition.l1.item = "kaleuche_amulet3";
			pchar.quest.caleuche_amulet3.function = "Caleuche_ThirdAmuletFind";
		break;
		
		// монах в Виллемстаде
		case "monk_caleuche":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("villemstad");
			npchar.lifeday = 1;
			dialog.text = "Hallo, Kapitän "+GetFullName(pchar)+". Freut mich, Sie in Willemstad begrüßen zu dürfen.";
			link.l1 = "Hallo, Vater. Ich erinnere mich nicht an dich. Kennen wir uns?";
			link.l1.go = "monk_caleuche_1";
		break;
		
		case "monk_caleuche_1":
			dialog.text = "Ich habe mich nach dir erkundigt, sobald dein Schiff angelegt hat. Und ich glaube, ich kann dich um Hilfe bitten.";
			link.l1 = "Sehr interessant. Und warum ich?";
			link.l1.go = "monk_caleuche_2";
		break;
		
		case "monk_caleuche_2":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "Weil Sie viel für die Republik der Freien Provinzen getan haben. Sie stehen in gutem Ansehen bei der Gesellschaft und sind mit dem Gouverneur befreundet. Ich habe bereits an mehreren Stellen appelliert und wurde zurückgewiesen, aber ich hoffe doch, dass eine noble Person wie Sie die bescheidene Bitte eines Diener unseres Herrn nicht ablehnen würde.";
			}
			else
			{
				dialog.text = "Weil Sie nicht im Dienste unseres Gouverneurs stehen. Sie arbeiten nicht für die Kompanie und haben nichts mit unserem Militär zu tun - sonst würden Sie mich wahrscheinlich wie eine lästige Fliege beiseite schlagen, da ich mich bereits an mehrere Instanzen gewandt und abgewiesen wurde.";
			}
			link.l1 = "Gut, dann. Was ist der Natur deines Anliegens?";
			link.l1.go = "monk_caleuche_3";
		break;
		
		case "monk_caleuche_3":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Es gibt ein Haus hinter der Bank. Eine Dame, die dort lebte, vermietete ein Zimmer darin an eine sehr verdächtige Person, nicht ein Einheimischer und auch kein Holländer. Und so unser Oberhaupt, Vater "+sld.name+", hatte ihn erkannt\nEs war Joachim Merriman, ein Portugiese, von der Inquisition beschuldigt der Hexerei und dem Handel mit unheiligen Mächten. Er versteckte sich vor der Inquisition in der Neuen Welt. Du weißt, die Spanier beschuldigen oft diejenigen, die in Ungnade gefallen sind, der Ketzerei und Hexerei, um sie auf dem Scheiterhaufen zu verbrennen, aber... In diesem Fall hatten sie recht. Merriman ist ein Hexenmeister\nAlso, er hatte einige Zeit in Willemstad gelebt, und dann verschwand er so plötzlich, wie er aufgetaucht war. Und nach einiger Zeit wurde eine Frau, die ihm das Zimmer vermietet hatte, nie wieder aus diesem Haus heraus gesehen. Nie! Und sie wurde seitdem nirgendwo mehr gesehen\nUnd in den Nächten können die Bürger gelegentlich rot-blaue Lichter in den Fenstern des zweiten Stocks blinken sehen und seltsame Geräusche hören, fast wie unheilige Schreie. Vater "+sld.name+"appellierte an den Kommandanten. Er schickte eine Patrouille von vier Soldaten, sie durchsuchten das Haus, fanden aber nichts: weder die Wirtin selbst, noch jemand anderes, noch etwas Verdächtiges überhaupt\nAber diese seltsamen Dinge gehen weiter. Die Wirtin ist nie aufgetaucht, und dieses höllische Licht kann nachts immer noch dort gesehen werden. Außerdem sind kürzlich auch zwei Bettler verschwunden. Ich hörte sie, sie sprachen auf dem Vorplatz - sie wussten, dass es keine Besitzer im Haus gibt, und so beschlossen sie, dort zu wohnen. Niemand hat sie danach gesehen.";
			link.l1 = "Ich nehme an, Sie wollen, dass ich in dieses Haus gehe und nachsehe, was wirklich passiert ist?";
			link.l1.go = "monk_caleuche_4";
		break;
		
		case "monk_caleuche_4":
			dialog.text = "Genau, edler Herr. Bitte helfen Sie der Heiligen Kirche. Der Kommandant sagt, dass wir uns Dinge vorstellen, da seine Patrouille nie etwas gefunden hat. Die Regierung denkt dasselbe. Die einfachen Leute kümmern sich einfach nicht darum, weil sie es nicht als eine klare Bedrohung für sie sehen.";
			link.l1 = "Hmm... Und ich muss dort nachts hingehen?";
			link.l1.go = "monk_caleuche_5";
		break;
		
		case "monk_caleuche_5":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Ja, mein Herr. Es ist dort tagsüber ruhig, deshalb denke ich, haben die Soldaten nichts gefunden, ich glaube, der Kommandant hat Angst um seine Männer, ich hätte auch. Aber bitte, ich flehe Sie an. Vater "+sld.name+" wird Ihnen danken und Sie für Ihren Dienst belohnen. Sobald Sie nachts in diesem Versteck waren, sagen Sie ihm bitte, was Sie dort finden. Ich versichere Ihnen, unsere Bedenken sind gut begründet.";
			link.l1 = "In Ordnung. Ich werde darüber nachdenken.";
			link.l1.go = "monk_caleuche_6";
		break;
		
		case "monk_caleuche_6":
			dialog.text = "Danke Ihnen, Kapitän. Ich hoffe, Sie lehnen meine bescheidene Bitte nicht ab. Bitte, tun Sie es im Namen unseres Herrn, unseres Glaubens und allem, was heilig ist. Gehen Sie mit meinem Segen.";
			link.l1 = "...";
			link.l1.go = "monk_caleuche_7";
		break;
		
		case "monk_caleuche_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "none", "", "", "", -1);
			AddQuestRecord("Caleuche", "24");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "visit the house of Joaquim Merriman, where, according to him, strange things happen at night. Remembering that special gleam in Merriman's eyes when he looked at the jade skull, I feel a little creepy. It seems that the old Jew could not resist the sum of half a million pesos. Whatever the case, I don`t feel like going to Merriman former abode at night.";
				else sTemp = "visit the house of my old acquaintance Joachim Merriman, where, allegedly, strange things are happening at nights. I still remember that glitter in Merriman's eyes, when he was looking at the skull, and honestly I feel frightened. I am not really fond of the idea to visit his former abode in the night, who knows what kind of devils lurk there.";
			}
			else sTemp = "visit the house at the back of the bank, where some Joachim Merriman had been renting a room. Apparently it is that warlock, of which Tuttuathapak was talking about. According to the monk, strange things are happening in this house in the night. I really feel uncomfortable about visiting the warlock's former home, who knows what kind of devils lurk there.";
			AddQuestUserData("Caleuche", "sText", sTemp);
			i = Findlocation("Villemstad_town");
			DeleteAttribute(&locations[i], "reload.l14.close_for_night");
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1.location = "Villemstad_houseSp1_room";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2 = "Hour";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.start.hour = 1.00;
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.finish.hour = 3.00;
			pchar.quest.Caleuche_villemstadhouse.function = "Caleuche_CreateJoakimSkel";
		break;
		
		// охотник у пещеры
		case "cavehunter":
			dialog.text = "Halt ein, Kumpel. Du solltest besser nicht dorthin gehen, wenn du dein Leben schätzt.";
			link.l1 = "Und was ist der Deal?";
			link.l1.go = "cavehunter_1";
		break;
		
		case "cavehunter_1":
			dialog.text = "Glaub mir, du willst es nicht wissen. Aber der Tod selbst lauert um die Ecke, und ich schwöre auf das Buch, dass du nicht lebend zurückkehren wirst, es gibt Dinge jenseits deiner Vorstellungskraft.";
			link.l1 = "Nun, wenn du es sagst, werde ich das Schicksal nicht herausfordern. Danke für die Warnung.";
			link.l1.go = "cavehunter_2";
		break;
		
		case "cavehunter_2":
			dialog.text = "Sie sind willkommen. Bleiben Sie klar von diesem Weg.";
			link.l1 = "...";
			link.l1.go = "cavehunter_3";
		break;
		
		case "cavehunter_3":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_4":
			dialog.text = "Bleib weg von diesem Weg, Kumpel.";
			link.l1 = "Ja, ich erinnere mich...";
			link.l1.go = "cavehunter_4_1";
		break;
		
		case "cavehunter_4_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_5":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Bist du sicher, dass du dorthin gehen willst?";
			link.l1 = "Absolut. "+sld.name+", der Vater Superior der Kirche in Havanna, hat mich hierher geschickt. Ich muss herausfinden, was hier vor sich geht, und angemessene Maßnahmen ergreifen.";
			link.l1.go = "cavehunter_6";
		break;
		
		case "cavehunter_6":
			dialog.text = "Was passiert hier? Ich fürchte, du würdest vor Angst zittern, wenn du mit eigenen Augen siehst, was hier passiert.";
			link.l1 = "Du meinst die wandelnden Toten?";
			link.l1.go = "cavehunter_7";
		break;
		
		case "cavehunter_7":
			dialog.text = "Ja. Und du solltest meinen Worten besser glauben.";
			link.l1 = "Und ich glaube dir. Ich bin diesem unseligen Ding schon in Willemstad begegnet und habe es vernichtet. Und jetzt werde ich dort hineingehen und all den Dreck zerstören, der in dieser Höhle lauert.";
			link.l1.go = "cavehunter_8";
		break;
		
		case "cavehunter_8":
			int icpy = GetOfficersQuantity(pchar);
			switch (icpy)
			{
				case 0:
					dialog.text = "Gehst du alleine dorthin? Du bist ein toter Mann, Kumpel. Du hast keine Ahnung, wie viele von diesen Dingen dort sind. Nun, geh, wenn du musst, und ich gehe zur Kirche, um eine Kerze für den Frieden deiner Seele anzuzünden.";
					link.l1 = "Lass mich nicht zu schnell begraben. Ich habe Schlimmeres gesehen.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 1:
					dialog.text = "Nur ihr zwei? Ich fürchte, ihr werdet nicht weit kommen. Ihr habt keine Ahnung, wie viele von diesen Dingen da draußen sind. Es ist Selbstmord.";
					link.l1 = "Du kennst uns einfach nicht gut, Freund. Tritt beiseite, und wir werden dieses unheilige Versteck säubern.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 2:
					dialog.text = "Nur die drei von euch? Ihr müsst erfahrene Kämpfer sein, wenn ihr es wagt, es zu tun. Aber ich fürchte immer noch, dass ihr es nicht schaffen werdet. Ihr habt keine Ahnung, wie viele von diesen Dingen dort in dieser Grotte sind.";
					link.l1 = "Du kennst uns einfach nicht gut, Freund. Tritt zur Seite, und wir werden dieses gottlose Versteck säubern.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 3:
					dialog.text = "Ihr seid keine Feiglinge, wie ich sehe. Aber ihr habt wirklich keine Ahnung, wie viele von diesen Dingen es gibt. Bei solchen Angelegenheiten zählt jeder Mann. Zum Teufel damit, ich komme mit euch und ich werde dieses Drecksvieh mit meiner Muskete erschießen!";
					link.l1 = "Du bist eine tapfere Seele, Freund. Ich werde deine Hilfe nicht ablehnen. Los geht's!";
					link.l1.go = "cavehunter_9";
				break;
			}
		break;
		
		case "cavehunter_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
		break;
		
		case "cavehunter_9":
			DialogExit();
			npchar.quest.caleuche = true;
			npchar.dialog.currentnode = "cavehunter_10";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			// закрываем локаторы выхода
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload1_back", true);
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload3_back", true);
		break;
		
		case "cavehunter_10":
			dialog.text = "Auf geht's! Tod den dreckigen Untoten!";
			link.l1 = "...";
			link.l1.go = "cavehunter_10_1";
		break;
		
		case "cavehunter_10_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_10";
		break;
		
		case "cavehunter_11":
			dialog.text = "Das war ja ein richtiges Massaker! Wer hätte gedacht, dass so viele Tote sich an diesem Ort verstecken! Nun, zumindest können wir jetzt ruhen... Bitte informieren Sie diesen Vater Superior von Ihnen darüber, der Sie hierher geschickt hat. Ich hoffe doch sehr, dass die Inquisition sich nach Ihrem Bericht um das kümmert. Mit Untoten umzugehen, ist schließlich ihre eigene Sache, ich bin ja nur ein einfacher Jäger.";
			link.l1 = "Ich werde es ihm auf jeden Fall sagen. Danke für die Hilfe, Kumpel. Du bist eine seltene Art, nicht viele würden es wagen, den Tod selbst zu bekämpfen! Viel Glück!";
			link.l1.go = "cavehunter_exit";
		break;
		
		// солдат в крипте при провале
		case "cryptguard":
			dialog.text = "Bleib wo du bist! Dieser Ort ist verboten!";
			link.l1 = "Ehh... Und was ist da drin?";
			link.l1.go = "cryptguard_1";
		break;
		
		case "cryptguard_1":
			dialog.text = "Ein gefährlicher Hexenmeister wurde dort gefunden. Nur die heiligen Väter und die sie begleitenden Soldaten dürfen eintreten.";
			link.l1 = "Ich verstehe. Wurde der Hexenmeister verhaftet?";
			link.l1.go = "cryptguard_2";
		break;
		
		case "cryptguard_2":
			dialog.text = "Ich bin nicht befugt, solche Fragen zu beantworten, senor. Es ist Zeit für Sie zu gehen.";
			link.l1 = "In Ordnung, ich habe es. Viel Glück!";
			link.l1.go = "cryptguard_3";
		break;
		
		case "cryptguard_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Caleuche", "31");
			CloseQuestHeader("Caleuche");
			pchar.questTemp.Caleuche = "end";
		break;
		
		// чавинави-вождь
		case "Chavinavi":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_01.wav");
			dialog.text = "Halt still, Mensch! Du befindest dich im allerheiligsten Teil des Tempels, und du bist zu weit gegangen, um jetzt noch umzukehren.";
			link.l1 = "Wer bist du?!";
			link.l1.go = "Chavinavi_1";
		break;
		
		case "Chavinavi_1":
			dialog.text = "Ich bin der Häuptling der Chavinavi, der Hüter und Beschützer dieses heiligen Ortes. Du bist nicht der Erste, der diesen Tempel betritt, aber nur zwei Männer und eine Frau haben ihn vor dir betreten und lebend verlassen. Das ist der einzige Grund, warum ich mich herablasse, jetzt mit dir zu sprechen. Warum bist du hierher gekommen, bleichgesicht?";
			link.l1 = "Ich habe hier ein altes Relikt gebracht, den Jadetotenkopf. Vor fünfzig Jahren wurde er aus einem indischen Tempel tief im Inland genommen. Ich wollte das Heiligtum finden und das Relikt Ihrem Gott zurückgeben.";
			link.l1.go = "Chavinavi_2";
		break;
		
		case "Chavinavi_2":
			dialog.text = "Es ist seltsam, solche Worte von einem deinesgleichen zu hören. Ich glaube dir nicht. Ihr, blassen Gesichter, kommt immer, um etwas zu nehmen, aber niemals, um etwas zurückzugeben.";
			link.l1 = "Ich lüge nicht. Indem ich den Schädel zurückgebe, werde ich den Fluch aufheben, der auf dem Kapitän des Geisterschiffs liegt, das die Karibik terrorisiert, was ihn wieder sterblich macht, und ich werde ihn für immer aus der Welt schaffen.";
			link.l1.go = "Chavinavi_3";
		break;
		
		case "Chavinavi_3":
			dialog.text = "Wie weißt du, dass unser Gott diesen Fluch aufheben wird, bleichgesicht? Spricht unser Gott mit dir?";
			link.l1 = "Nein. Ich kam hierher auf den Rat eines großen Schamanen namens Tuttuathapak. Wie er sagte, ist der Schädel der Schlüssel zum Fluch, und dies ist der einzige Tempel in der Karibik. Und weißt du was - ich glaube, dass er tatsächlich mit den Geistern der Vergangenheit sprechen kann. Vielleicht sogar mit dir, Häuptling der Jaguar-Krieger.";
			link.l1.go = "Chavinavi_4";
		break;
		
		case "Chavinavi_4":
			dialog.text = "Deine Worte überraschen mich, bleichgesicht, aber ich kann dir immer noch nicht vollständig vertrauen. Doch, wenn du zu diesem Tempel gekommen bist, um unser Relikt zurückzubringen, muss dir unser Schamane sicherlich von diesem Ort erzählt haben, seiner Entstehung, seiner Geschichte und Bewohner\nWenn das so ist, wirst du meine Fragen leicht beantworten können. Dann werde ich zugeben, dass du mir gegenüber aufrichtig warst, dich passieren lassen und dich darüber hinaus belohnen.";
			link.l1 = "Dann frag!";
			link.l1.go = "question1";
		break;
		
		case "question1":
			dialog.text = "I am the chieftain of the Chavinavi, and the jaguar warriors. Thousand years ago I was human; now I am carrying out my sacred duty in these chambers. Which god commands me?";
			link.l1 = "Mictlantecuhtli.";
			link.l1.go = "question1_l";
			link.l2 = "Kukulcan.";
			link.l2.go = "question1_l";
			link.l3 = "Yum Cimil.";
			link.l3.go = "question1_r";
			link.l4 = "Inti.";
			link.l4.go = "question1_l";
			link.l5 = "Kauil.";
			link.l5.go = "question1_l";
		break;
		
		case "question1_r":
			dialog.text = "Bevor eure bleichgesichtigen Leute kamen, gehörte dieses ganze Land, von dem großen Schnee im Norden bis zu den großen Ebenen im Süden, uns, Brüdern einer Familie...";
			link.l1 = "";
			link.l1.go = "question2";
		break;
		
		case "question1_l":
			dialog.text = "Bevor deine bleichgesichtigen Leute kamen, gehörte dieses ganze Land, vom großen Schnee im Norden bis zu den großen Ebenen im Süden, uns, Brüdern einer Familie...";
			link.l1 = "";
			link.l1.go = "question2";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question2":
			dialog.text = "Welcher Indianerstamm hat diesen Tempel erbaut?";
			link.l1 = "Inka.";
			link.l1.go = "question2_l";
			link.l2 = "Chavins.";
			link.l2.go = "question2_r";
			link.l3 = "Maya.";
			link.l3.go = "question2_l";
			link.l4 = "Aztekisch.";
			link.l4.go = "question2_l";
			link.l5 = "Arawac.";
			link.l5.go = "question2_l";
		break;
		
		case "question2_r":
			dialog.text = "Unser Volk machte Fortschritte, erlernte Weisheit und unterwarf neue Wälder, Ebenen und Inseln. Die Menschen, die diesen Tempel erbaut haben, kamen aus den Wäldern über das Große Wasser...";
			link.l1 = "";
			link.l1.go = "question3";
		break;
		
		case "question2_l":
			dialog.text = "Unser Volk machte Fortschritte, erlernte Weisheit und unterwarf neue Wälder, Ebenen und Inseln. Die Menschen, die diesen Tempel erbaut hatten, kamen aus den Wäldern jenseits des Großen Wassers...";
			link.l1 = "";
			link.l1.go = "question3";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question3":
			dialog.text = "Wer führte die Partei dieser glorreichen Leute?";
			link.l1 = "Großer Häuptling.";
			link.l1.go = "question3_l";
			link.l2 = "Großer Priester.";
			link.l2.go = "question3_l";
			link.l3 = "Sohn des großen Häuptlings.";
			link.l3.go = "question3_r";
			link.l4 = "Sohn des großen Priesters.";
			link.l4.go = "question3_l";
			link.l5 = "Die Partei hatte keinen Anführer.";
			link.l5.go = "question3_l";
		break;
		
		case "question3_r":
			dialog.text = "Die Indianer, tapfere Krieger und Reisende, liebten und verehrten ihr Heimatland immer, auch nachdem sie sich an einem neuen Ort niederließen. Als Zeichen ihrer Liebe zu ihrer Heimat bauten sie eine Statue im Tempel in Form eines Vogels, dem Symbol ihrer Heimat. Sie steht hinter mir...";
			link.l1 = "";
			link.l1.go = "question4";
		break;
		
		case "question3_l":
			dialog.text = "Die Indianer, tapfere Krieger und Reisende, liebten und verehrten ihr Heimatland immer, selbst nachdem sie sich an einem neuen Ort niedergelassen hatten. Als Zeichen ihrer Liebe zu ihrer Heimat bauten sie eine Statue im Tempel in Form eines Vogels, dem Symbol ihrer Heimat. Sie steht hinter mir...";
			link.l1 = "";
			link.l1.go = "question4";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question4":
			dialog.text = "Wie heißt dieser Vogel?";
			link.l1 = "Albatros.";
			link.l1.go = "question4_l";
			link.l2 = "Adler.";
			link.l2.go = "question4_l";
			link.l3 = "Geier.";
			link.l3.go = "question4_l";
			link.l4 = "Fels.";
			link.l4.go = "question4_l";
			link.l5 = "Condor.";
			link.l5.go = "question4_r";
		break;
		
		case "question4_r":
			dialog.text = "Jahre des Wohlstands sind vergangen und erloschen, wie die Flamme der Lampe, und das Leben hat die Insel verlassen. Nur der Tempel blieb hier als Erinnerung an die große Macht der alten Indianer. Der letzte Schamane hinterließ auf einem Podest eine heilige Sonnenkugel, die den Mutigen Kraft gab und die Bösen bestrafte. Sie wurde von dem Mann genommen, der vor Ihnen hier war.";
			link.l1 = "";
			link.l1.go = "question5";
		break;
		
		case "question4_l":
			dialog.text = "Jahre des Wohlstands sind vergangen und verblasst, wie die Flamme der Lampe, und das Leben hat die Insel verlassen. Nur der Tempel blieb hier stehen als Erinnerung an die große Macht der alten Indianer. Der letzte Schamane hinterließ auf einem Podest eine heilige Sonnenkugel, die den Mutigen Kraft gab und die Bösen bestrafte. Sie wurde von dem Mann genommen, der vor dir hier war.";
			link.l1 = "";
			link.l1.go = "question5";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question5":
			dialog.text = "Wie hieß noch mal diese heilige Kugel?";
			link.l1 = "Orb des strahlenden Sonnens.";
			link.l1.go = "question5_l";
			link.l2 = "Orb der Sonnenstrahlen.";
			link.l2.go = "question5_l";
			link.l3 = "Orb des Mittagssonne.";
			link.l3.go = "question5_l";
			link.l4 = "Orb des aufgehenden Sonne.";
			link.l4.go = "question5_r";
			link.l5 = "Orb des untergehenden Sonne.";
			link.l5.go = "question5_l";
		break;
		
		case "question5_r":
			if (CheckAttribute(pchar, "questTemp.Caleuche.QuestionFail"))
			{
				PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
				dialog.text = "Falsche Antworten zeigen, dass du mich belogen hast, weißer Mann! Du bist mit bösen Absichten gekommen! Du hast es geschafft, an den Wächtern des Tempels und des Heiligtums vorbeizuschleichen, du hast herausgefunden, wie der Mechanismus der Tür funktioniert - aber du wirst trotzdem nicht einem tödlichen Kampf mit mir entkommen. Bereite dich darauf vor zu sterben, bleiches Gesicht!";
				link.l1 = "Nun, wenn du darauf bestehst - lass uns sehen, was für ein großer Krieger du bist...";
				link.l1.go = "chavinavi_fight";
			}
			else
			{
				dialog.text = "Deine Kenntnisse über mein Volk und meinen Tempel ehren dich, Bleichgesicht. Jetzt glaube ich dir. Geh und erfülle das, wofür du hierher gekommen bist. Platziere die heilige Reliquie auf einem Podest vor dem Kondor, wo einst die Kugel der aufgehenden Sonne lag\nDann komm zu mir zurück. Deine Verehrung von Yum Cimil und die Entscheidung, das freiwillig zurückzugeben, was deine Brüder gestohlen haben, müssen belohnt werden.";
				link.l1 = "Danke für Ihr Vertrauen, großer Häuptling.";
				link.l1.go = "chavinavi_exit";
			}
		break;
		
		case "question5_l":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
			dialog.text = "Falsche Antworten zeigen, dass du mich belogen hast, weißer Mann! Du bist mit bösen Absichten gekommen! Du hast es geschafft, an den Wächtern des Tempels und des Schreins vorbeizuschleichen, du hast herausgefunden, wie der Mechanismus der Tür funktioniert - aber du wirst trotzdem nicht einem tödlichen Kampf mit mir entkommen. Bereite dich auf den Tod vor, bleiches Gesicht!";
			link.l1 = "Nun, wenn du darauf bestehst - lass uns sehen, wie großartig ein Krieger du bist...";
			link.l1.go = "chavinavi_fight";
		break;
		
		case "chavinavi_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_TopChavinaviDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "chavinavi_exit":
			DialogExit();
			sld = ItemsFromID("SkullAztec");
			sld.shown = "0";
			sld.useLocation = "KhaelRoa_Treasure_Alcove";
			sld.useLocator = "button01";
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "Chavinavi_5":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_03.wav");
			dialog.text = "Du hast getan, was du versprochen hast, Bleichgesicht. Ich bin froh, dass du nicht der Lügner bist wie die meisten deiner Brüder. Ich werde auch mein Wort halten. Hier, nimm dieses Geschenk von mir - das Symbol der Macht der Jaguar-Krieger. Yum Cimil selbst hat dieses Fell mit ein wenig seiner Stärke versehen.";
			link.l1 = "Wow! Es ist so schön!";
			link.l1.go = "Chavinavi_6";
		break;
		
		case "Chavinavi_6":
			GiveItem2Character(pchar, "KhaelRoa_item");
			Log_Info("You have received jaguar's pelt");
			PlaySound("interface\important_item.wav");
			dialog.text = "Dies ist nicht ein einfacher Pelz. Sobald du ihn trägst, wirst du die Stärke des Jaguar-Kriegers erlangen. Die Macht deiner Waffe, die Feuer atmet und Blei schießt, wird sich verzehnfachen, und du wirst in der Lage sein, das Schlachtfeld mit den Leichen deiner Feinde zu übersäen\nAber kein Sterblicher kann die Macht halten, die Yum Cimil in diesen Pelz gelegt hat. Sobald du sie freisetzt, wird sie dich nur bis zur nächsten Mitternacht begleiten, und dann wird sie verblassen. Pass auf sie auf, bleiches Gesicht, und verschwende ihre Kraft nicht auf ein kleines Scharmützel.";
			link.l1 = "Danke! Ich werde es nur benutzen, wenn ich völlig von Feinden überwältigt bin.";
			link.l1.go = "Chavinavi_7";
		break;
		
		case "Chavinavi_7":
			dialog.text = "Jetzt geh. Und warne deine Brüder davor, die Ruhe dieser heiligen Kammern zu stören. Die Jaguar-Krieger zeigen den Bleichgesichtern keine Gnade und werden ihnen kein Quartier geben.";
			link.l1 = "Auf Wiedersehen, Häuptling.";
			link.l1.go = "Chavinavi_8";
		break;
		
		case "Chavinavi_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Caleuche", "38");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeIndianRelation(10.0);
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
