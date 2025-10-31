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
			dialog.text = "Was wollt ihr?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";
		break;
		
		case "LEDR_Gonsalo_1":
			if (pchar.sex == "man")
			{
				dialog.text = "He, Junge! Du siehst aus wie ein tapferer Seemann und ein ordentlicher Haudegen obendrein. Hilfst du mir, einen kleinen Ausflug zu machen?";
			}
			else
			{
				dialog.text = "Hey, Schönheit! Du bist wohl nicht auf den Mund gefallen, wenn du dich hierher traust. Hilfst du mir, einen kleinen Ausflug zu machen?";
			}
			link.l1 = "Ich nehme an, du bist der alte Mann, der einen Führer zu dem alten Schiff sucht?";
			link.l1.go = "LEDR_Gonsalo_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LEDR_Gonsalo_2":
			dialog.text = "Heh... Also laufen die Gerüchte schneller als der Wind. Ja, das bin ich. Gonzalo Peralta – der Einzige, der noch lebt, von der gestrandeten 'La Espada del Rey'.";
			link.l1 = "Und ich bin Kapitän "+GetFullName(pchar)+". Willst du dein Schiff noch einmal sehen?";
			link.l1.go = "LEDR_Gonsalo_3";
		break;

		case "LEDR_Gonsalo_3":
			dialog.text = "Ja. Weißt du, seit einiger Zeit quält mich immer wieder derselbe Albtraum. Aber darum geht es eigentlich gar nicht... Ob du es glaubst oder nicht, aber jeden Morgen, sobald der Albtraum vorbei ist, wache ich auf und... vor mir steht ein verdammtes Skelett...";
			link.l1 = "In indianischer Tracht. Man hat mir erzählt, dass du jedem diese Geschichte auftischst.";
			link.l1.go = "LEDR_Gonsalo_4";
		break;

		case "LEDR_Gonsalo_4":
			dialog.text = "Eine Seemannsgeschichte? Heh... Ich wünschte, es wäre nur eine Geschichte. Noch vor ein paar Monaten habe ich ein ruhiges Leben geführt, wie es sich für einen alten Seemann im Ruhestand gehört. Aber jetzt taucht dieser Knochensack jeden Morgen bei mir auf, starrt mich an, stößt einen markerschütternden Schrei aus... Donnerwetter, da würde jedem Bootsmann das Blut in den Adern gefrieren... und dann stürzt er sich in den Kampf. Und weißt du was? Jedes Mal greift er noch wilder an. Genau deshalb will ich so schnell wie möglich zum Schiff – ich habe das Gefühl, dass ich dort etwas finden muss.";
			link.l1 = "Hm... Die Lage ist interessant. Und was genau hoffst du dort nach all der Zeit zu finden?";
			link.l1.go = "LEDR_Gonsalo_5";
		break;
		
		case "LEDR_Gonsalo_5":
			dialog.text = "Ich weiß es nicht, Kapitän, wirklich nicht... Aber es zieht mich zu diesem Schiff wie ein alter Kahn im Sturm. Mein Traum, dieses Skelett und dieses seltsame Gefühl... Beim Meer, sie sind irgendwie miteinander verbunden. Nur wie – das kann ich mir beim besten Willen nicht erklären.";
			link.l1 = "Worum geht es genau in deinem Traum? Hat er etwas mit den Indianern zu tun?";
			link.l1.go = "LEDR_Gonsalo_6";
			link.l2 = "Also siehst du nachts irgendwelche Visionen und kämpfst morgens mit einem Skelett? Vielleicht liegt das Problem gar nicht am Schiff, sondern daran, dass du mal einen Arzt aufsuchen solltest? Ich werde deine blühende Fantasie nicht unterstützen. Such dir einen anderen Dummkopf, der deinen Unsinn glaubt.";
			link.l2.go = "LEDR_Gonsalo_6_end";
		break;
		
		case "LEDR_Gonsalo_6_end":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_End");
		break;
		
		case "LEDR_Gonsalo_6":
			dialog.text = "Und ob ich verbunden bin, Kanonenkugel an meinen Hals... In diesem Traum bin ich mit der toten Mannschaft   auf der 'La Espada del Rey'. Wir... plündern die Dörfer der Kariben auf Hispaniola, töten jeden – Männer, Frauen, Kinder. Die, die kämpfen, und sogar die, die auf die Knie fallen und um Gnade flehen. Wir brennen ein Dorf nach dem anderen nieder. Die Pfeile und Keulen der Indianer gegen uns – wie ein löchriges Tartane gegen eine Kriegsgaleone. Die Kariben flehen verzweifelt um Verhandlungen, und dann...";
			link.l1 = "Mein Gott, bist du etwa an diesen Ausschreitungen beteiligt gewesen? Du brauchst keine Hilfe, sondern einen Strick um den Hals!";
			link.l1.go = "LEDR_Gonsalo_7";
		break;
		
		case "LEDR_Gonsalo_7":
			dialog.text = "Nein! Nein, beim Teufel noch mal, so etwas ist nie passiert, verstehst du?! Ich habe keine Ahnung, warum mir das alles träumt... aber ich schwöre bei allen Heiligen, weder ich noch meine Mannschaft haben an solchen Gräueltaten teilgenommen!";
			link.l1 = "Es wäre besser für dich, wenn das wirklich so ist. Mach weiter.";
			link.l1.go = "LEDR_Gonsalo_8";
		break;

		case "LEDR_Gonsalo_8":
			dialog.text = "Die Kariben baten um Verhandlungen, und der Kapitän stimmte zu. Er lud sie alle in eine der Hütten ein, die 'wir' eingenommen hatten. Die Häuptlinge kamen – zwei Dutzend Leute, nicht weniger, angeführt von ihrer Königin – Anacaona. Nur der Kapitän selbst ging nicht hinein... keiner von uns ging hinein. Kaum war der letzte Häuptling eingetreten, wurde die Tür zugeschlagen und mit Balken verriegelt. Und dann... verdammt noch mal... wurde Feuer gelegt. Nur die Königin wurde verschont, aber nicht für lange. Man zwang sie zuzusehen, wie ihr Volk bei lebendigem Leib verbrannte... Und dann hat man sie an einem Baum aufgehängt.";
			link.l1 = "Und das wiederholt sich jede Nacht? Immer wieder derselbe Traum? Weißt du, ich würde mich nicht wundern, wenn nach all dem dieses Skelett nur das Produkt deines verwirrten Verstandes ist...";
			link.l1.go = "LEDR_Gonsalo_9";
		break;

		case "LEDR_Gonsalo_9":
			dialog.text = "Das ist noch nicht alles. Die überlebenden Kariben flohen nach Kuba, fanden dort Unterstützung bei den einheimischen Stämmen und sammelten sich bald zu einem Heer – unter der Führung eines Häuptlings. Atuey – so hieß er wohl. Sie folgten ihm wie ihrer letzten Hoffnung. Aber wir haben sie alle ohne Mühe niedergemacht. Atuey wurde gefasst und zur Hinrichtung vorbereitet\nAls man ihn ans Kreuz band, um ihn zu verbrennen, bot ihm ein Mönch an, den wahren Glauben anzunehmen – er sagte, das würde seine Qualen lindern und ihm den Weg ins Paradies öffnen. Atuey fragte den Mönch, ob das Paradies auch den Spaniern offenstehe\nUnd als dieser sagte, dass es für gute Spanier natürlich offen sei, antwortete der Kazike ohne langes Nachdenken, dass er in diesem Fall lieber die Hölle wolle – nur um nicht mit so grausamen Menschen an einem Ort zu sein. Danach sprach er noch ein paar Worte in seiner eigenen Sprache, und das Feuer wurde entfacht. Er gab keinen Laut von sich, als die Flammen seine Haut erfassten\nBeim Meer, ich möchte so etwas nicht im wachen Leben sehen. Mein Traum endet immer gleich: Der Kapitän sitzt da, rührt sich nicht. Nur die Kerze neben ihm qualmt, und er blättert immer wieder in irgendeinem abgegriffenen Journal. Langsam, als wäre jedes Wort Gold wert, und murmelt etwas vor sich hin. Selbst im Traum, "+GetSexPhrase("Junge","Mädchen")+", ich verstehe – das ist ein Zeichen. Es ist Zeit, zum Schwert zu greifen, denn er greift schon an.\nHilf mir, diesen Albtraum loszuwerden, Kapitän. Geh mit mir in die Bucht. Allein traue ich mich nicht mehr dorthin – mir fehlt schon das Pulver in den Patronentaschen. Aber bevor du antwortest, muss ich dich warnen: Ich kann dir nichts zahlen, sonst hätte ich schon eine Schlange von Helfern vor der Tür. Also bleibt mir nur, auf die Hilfe eines Bruders – eines Seemanns – zu hoffen.";
			link.l1 = "Na gut. Wenn der Gang zum Schiff dir hilft, diese Träume und anderen Visionen loszuwerden, helfe ich dir. Geh an Bord. Sobald ich meine Angelegenheiten erledigt habe, brechen wir zur Bucht auf.";
			link.l1.go = "LEDR_Gonsalo_10";
		break;
		
		case "LEDR_Gonsalo_10":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_1");
			AddQuestRecord("LEDR", "2");
			AddQuestUserData("LEDR", "sSex", GetSexPhrase("ся","ась"));
		break;
		
		case "LEDR_Gonsalo_11":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				dialog.text = "Da ist er... Einst der Stolz der spanischen Handelsflotte, und jetzt – ein Haufen morsch gewordener Bretter, die nur noch irgendwie zusammenhalten.";
				link.l1 = "Selten sieht man so einen Koloss besiegt am Ufer liegen. Wie ist er hierher geraten?";
				link.l1.go = "LEDR_Gonsalo_12";
				link.l2 = "Dann lass uns umsehen. Vielleicht findest du hier ja wirklich etwas.";
				link.l2.go = "LEDR_Gonsalo_20_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Ich will nicht undankbar oder feige wirken... aber im Moment ist mir hier nicht wohl. Lass uns zurückkommen, wenn die Sonne aufgeht.";
				link.l1 = "In Ordnung, Freund, wie du willst.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LEDR_Gonsalo_11";
			}
		break;
		
		case "LEDR_Gonsalo_12":
			dialog.text = "Damals verließen wir Santiago und hielten Kurs auf Sevilla. Die Ladung war gering, dafür hatten wir einen Passagier – einen echten hohen Herrn, den Bischof höchstpersönlich. Der Mannschaft, das sage ich offen, war so eine Fahrt gar nicht recht... aber wann hat uns je jemand gefragt?\nDen Ozean haben wir damals gar nicht mehr erreicht. Bei Turks wurden wir von einer Piratenbrigg angegriffen – flink, wendig, bis an die Zähne bewaffnet. Keine abgerissene Bande, sondern echte Seewölfe. Der Kapitän wollte zuerst ausweichen – das Leben des Bischofs war ihm zu riskant. Aber bei solchem Wind konnten wir keinen Kurs zurück nehmen, und von Süden drängte schon der Sturm. Also blieb keine Wahl – es kam zum Gefecht.";
			link.l1 = "Zwischen zwei Fronten zu stehen, ist wirklich kein beneidenswertes Schicksal. Und was geschah dann?";
			link.l1.go = "LEDR_Gonsalo_13";
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;

		case "LEDR_Gonsalo_13":
			dialog.text = "Der Kampf dauerte nicht lange. Wir schafften es, ihnen den Fockmast zu zerstören, aber auch die Piraten ließen sich nicht lumpen – eine verirrte Kugel zerschlug das Steuerruder, und wie vom Teufel gelenkt, blieb das Schiff mit dem Bug zum herannahenden Sturm stehen. Er kam so schnell näher, dass die Piraten – Knippel in ihr Großsegel – lieber das Weite suchten und in einer der Buchten von Turks verschwanden. Uns blieb nur eines: darauf zu warten, dass uns der Sturm verschlingt. Der Kapitän befahl, die Segel zu bergen und das Steuerruder zu ersetzen, doch da war es schon zu spät.";
			link.l1 = "Also hat euch der Sturm bei Turks erwischt, hierher verschlagen und schließlich an Land gespuckt?";
			link.l1.go = "LEDR_Gonsalo_14";
		break;

		case "LEDR_Gonsalo_14":
			dialog.text = "Genau so war es auch. Auf dem Schiff herrschte das reinste Chaos. Der Wind zerrte an den Tauen, die Masten stürzten einer nach dem anderen um, zerschmetterten das Deck und begruben die Leute unter sich. Wer sich nicht rechtzeitig festgebunden hatte, wurde über Bord gespült, und wer es geschafft hatte, wurde von den Trümmern zerquetscht. Im Laderaum war es nicht besser – Kanonen, Kisten und Kugeln flogen wie der Teufel hin und her und zermalmten alles, was ihnen in den Weg kam. Als wir schließlich an Land gespült wurden, war ich bewusstlos. Ich kam erst wieder zu mir, als ich schon im Sand lag. Der Bootsmann Sergio hat mich gefunden. Bei ihm waren noch zwei andere.";
			link.l1 = "Nicht gerade viel, für so ein großes Schiff.";
			link.l1.go = "LEDR_Gonsalo_15";
		break;

		case "LEDR_Gonsalo_15":
			dialog.text = "Ach, Kapitän... Wie viele Leichen dort lagen... Uns war sofort klar: Hier konnten wir nicht bleiben. Die Wellen hätten sowohl das Schiff als auch uns mit sich reißen können. In der Nähe fanden wir eine Höhle – dort sind wir, völlig erschöpft, eingeschlafen, kaum dass wir den Boden berührten. Als ich aufwachte, waren weder Sergio noch die anderen beiden in der Höhle.\nIch habe den ganzen Strand abgesucht, aber beim Donner, sie waren einfach verschwunden. Allein aufs Schiff zu klettern, war für mich unmöglich, also beschloss ich, ins Inselinnere zu gehen. So bin ich nach Sharptown gekommen, wo ich aus reiner Naivität einiges angestellt habe.\nIch wollte wenigstens etwas über die Überlebenden erfahren und fing an, allen zu erzählen, was uns passiert war. Doch diese Halunken interessierten sich weder für mich noch für die Mannschaft, sondern nur für die Beute, die sie vom Schiff stehlen konnten. Das Gerücht verbreitete sich rasch über die ganze Insel, und Scharen dieser Ladrones strömten dorthin.";
			link.l1 = "Heißt das, das Schicksal dieser Menschen ist dir bis jetzt nicht bekannt?";
			link.l1.go = "LEDR_Gonsalo_16";
		break;

		case "LEDR_Gonsalo_16":
			dialog.text = "Zurück aufs Schiff zu gehen war viel zu gefährlich. Diejenigen, die das Risiko eingingen, dort nach Beute zu suchen, konnten sich um die Beute streiten und jedem, der in der Nähe war, eine Kugel verpassen… aus Versehen. Oder vielleicht — gar nicht aus Versehen\nBeim Meer, ich habe eine ganze Woche in der Taverne verbracht und jeden ausgefragt, der in der Bucht gewesen war. Aber niemand hatte etwas von meinen Leuten gehört oder wusste, was mit ihnen passiert war\nAm Ende musste ich mich mit dem Gedanken abfinden: Anscheinend bin ich der Einzige, der diesen verfluchten Sturm überlebt hat. Das Schicksal war mir wohl einfach gnädiger als den anderen. Oder vielleicht… lag es an dem Amulett, das mir einst der junge, damals noch Kapitän Eugenio de la Torre, geschenkt hatte. Es war immer bei mir. Und, verdammt, es sieht ganz so aus, als hätte es mir wirklich Glück gebracht.";
			link.l1 = "Und wo ist er jetzt? Sieht so aus, als würde er nicht vor Skeletten schützen, heh...";
			link.l1.go = "LEDR_Gonsalo_17";
		break;

		case "LEDR_Gonsalo_17":
			dialog.text = "Es wurde mir vom Hals gerissen, als wir den oberen Rand des Brunnens in meinem Hof ausbesserten. Ein Balken streifte meinen Hals, und der Talisman fiel ins Wasser. Der Brunnen war schon voll, und niemand hätte ihn für ein kleines Schmuckstück ausgeschöpft.";
			link.l1 = "Und seitdem hast du Albträume?";
			link.l1.go = "LEDR_Gonsalo_18";
		break;

		case "LEDR_Gonsalo_18":
			dialog.text = "Verdammt noch mal! Darüber habe ich nie nachgedacht, aber so ist es tatsächlich gewesen! Kaum hatten wir den Brunnen fertiggestellt, begannen auch schon die Albträume.";
			link.l1 = "Ein lustiger Zufall. Nun, jetzt bist du hier, wie du es wolltest. Was hast du als Nächstes vor?";
			link.l1.go = "LEDR_Gonsalo_19";
		break;

		case "LEDR_Gonsalo_19":
			dialog.text = "Ich weiß nicht, Kapitän... Ich weiß es wirklich nicht. Lass uns erst einmal umsehen – das Gefühl, dass ich hier etwas finden muss, ist nur noch stärker geworden.";
			link.l1 = "Gut. Hoffentlich sind wir nicht umsonst hierher gekommen.";
			link.l1.go = "LEDR_Gonsalo_20";
		break;
		
		case "LEDR_Gonsalo_20":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
		break;
		
		case "LEDR_Gonsalo_20_1":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
			pchar.questTemp.LEDR_NoStory = true;
		break;
		
		case "LEDR_Gonsalo_21":
			dialog.text = "Hör zu... Dieses Gefühl wird immer stärker. Es ist, als stünde ich kurz davor, etwas zu finden, das ich unbedingt entdecken muss. Ich muss auf das Schiff gelangen. Beim Meer, dort gibt es etwas, das erklärt, warum mich dieses vermaledeite Skelett einfach nicht in Ruhe lässt.";
			link.l1 = "Also, bist du vielleicht nicht ganz ohne Grund so eilig hierher gekommen? Hast du etwas Wertvolles auf dem Schiff versteckt und willst jetzt zurück, um deine Beute zu holen?";
			link.l1.go = "LEDR_Gonsalo_22";
		break;

		case "LEDR_Gonsalo_22":
			dialog.text = "Was für ein Unsinn? Glaubst du, ich wäre nach all den Jahren quer durch das ganze Archipel hierher gekommen – nur wegen ein paar Dublonen? Wenn du diesem Skelett auch nur ein einziges Mal begegnet wärst, wären dir solche Gedanken nie in den Sinn gekommen.";
			link.l1 = "Schon gut, schon gut, reg dich nicht auf. Und wie willst du denn an Bord des Schiffs kommen?";
			link.l1.go = "LEDR_Gonsalo_23";
		break;

		case "LEDR_Gonsalo_23":
			dialog.text = "Am Heck gibt es eine geheime Tür. Der Kapitän hat sie eigenhändig ausgesägt – für den Fall, dass ein Entern nicht zu unseren Gunsten ausgeht. Beim Donner, allein kriege ich meinen alten Kadaver da niemals durch, aber zu zweit...";
			link.l1 = "Na gut, zeig mir den Weg, dann bringen wir es hinter uns.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_5");
		break;
		
		case "LEDR_Gonsalo_24":
			DelLandQuestMark(npchar);
			dialog.text = "’Ne Kanonenkugel in den Hals, was für ein Gemetzel! Zum Glück waren die nicht so wild wie der, der mir jeden Morgen erscheint. Und, glaubst du mir jetzt?";
			link.l1 = "Nach so nem Anblick schwer, nicht zu glauben. Alles okay bei dir?";
			link.l1.go = "LEDR_Gonsalo_24_1";
		break;

		case "LEDR_Gonsalo_24_1":
			dialog.text = "Scheint so. Verfluchte Untote... meine Beine sind weggeknickt wie gebrochene Masten.";
			link.l1 = "Na, wenn du heil bist, Schluss mit Rumsitzen. Gib mir die Hand, ich helf dir hoch.";
			link.l1.go = "LEDR_Gonsalo_24_2";
		break;

		case "LEDR_Gonsalo_24_2":
			CharacterTurnByChr(npchar, CharacterFromID("blaze"));
			dialog.text = "...";
			link.l1 = "Schon besser. Sieht so aus, als wären wir nicht die Ersten, die den Weg hierher kannten.";
			link.l1.go = "LEDR_Gonsalo_25";
			LAi_Fade("LEDR_GonsaloStay", "");
		break;

		case "LEDR_Gonsalo_25":
			dialog.text = "Das scheinen meine Leute zu sein. Die, die den Sturm überlebt haben... Ich habe Sergios Weste erkannt... oder besser gesagt, das, was davon übrig ist. Das heißt, sie sind zurückgekommen – entweder um nach Überlebenden zu suchen oder um die Toten zu begraben. Aber offenbar hat sie dieses Ungeziefer ebenfalls erwischt.";
			link.l1 = "Es ist erstaunlich, dass nur Fetzen der Weste erhalten geblieben sind. Und sonst nichts.";
			link.l1.go = "LEDR_Gonsalo_26";
		break;

		case "LEDR_Gonsalo_26":
			if(CheckAttribute(pchar, "questTemp.LEDR_NoStory"))
			{
			dialog.text = "Nicht mal ein Fetzen von der Kutte unseres Passagiers – des Bischofs – ist übrig. Nach dem Schlüssel, den er in der Hand hält, zu urteilen, war dieser arme Kerl da drüben wohl er. Er hat sich nie von diesem Schlüssel getrennt, keine Sekunde. Scheint, als hätte er nicht mehr Glück gehabt als die anderen. Beim Meer – diese Untoten sind nicht grundlos hier herumgeschlichen. Etwas hält sie hier... oder sie bewachen etwas.";
			DeleteAttribute(pchar, "LEDR_NoStory");
			}
			else
			{
			dialog.text = "Nicht mal ein Fetzen von der Kutte des Bischofs ist übrig. Nach dem Schlüssel, den er in der Hand hält, zu urteilen, war dieser arme Kerl da drüben wohl er. Er hat sich nie von diesem Schlüssel getrennt, keine Sekunde. Scheint, als hätte er nicht mehr Glück gehabt als die anderen. Beim Meer – diese Untoten sind nicht grundlos hier herumgeschlichen. Etwas hält sie hier... oder sie bewachen etwas.";
			}
			link.l1 = "Jetzt hab ich auch das Gefühl, dass wir hier etwas finden sollen. Lass uns das hinter uns bringen – ich hab echt keine Lust, hier länger zu bleiben als nötig.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_8");
		break;
		
		case "LEDR_Gonsalo_27":
			dialog.text = "Na, was gibt es, Kapitän? Konntest du etwas finden?";
			link.l1 = "Es sieht so aus, als wäre das die Truhe des Bischofs gewesen. Ich hab unser"+GetSexPhrase("ёл","ла")+" da ist etwas. Sieh mal.";
			link.l1.go = "LEDR_Gonsalo_28";
		break;

		case "LEDR_Gonsalo_28":
			dialog.text = "Velázquez... Donnerwetter... Ich habe dieses Tagebuch in meinen Träumen gesehen! Genau darin hat der Kapitän geblättert, bevor er...";
			link.l1 = "...";
			link.l1.go = "LEDR_Gonsalo_29";
		break;

		case "LEDR_Gonsalo_29":
			dialog.text = "Verdammt, es fühlt sich an, als würde er mir die Hände verbrennen!";
			link.l1 = "Brennen dir die Hände? Ach komm, das ist doch nur ein altes Tagebuch. Oder glaubst du wirklich, dass darin irgendeine dunkle Macht steckt?";
			link.l1.go = "LEDR_Gonsalo_30";
		break;

		case "LEDR_Gonsalo_30":
			dialog.text = "Ich schwöre bei allen Heiligen, ich mache keine Scherze! Dieses verdammte Tagebuch brennt mir förmlich in den Händen. Es muss vernichtet werden! Zerreißen, verbrennen, versenken – irgendetwas! Nein, besser verbrennen. Ja, genau verbrennen, damit nicht einmal Asche davon übrig bleibt!";
			link.l1 = "Wie du willst. Dann gehen wir an Land, machen ein Feuer und schicken diese Chronik der Verbrechen in die Flammen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_10");
		break;
		
		case "LEDR_Gonsalo_31":
			dialog.text = "Das war’s also... Als ob ein Anker von meiner Seele gefallen wäre.";
			link.l1 = "Glaubst du, jetzt ist alles vorbei?";
			link.l1.go = "LEDR_Gonsalo_32";
			TakeItemFromCharacter(pchar, "LEDR_book");
			CharacterTurnToLoc(npchar, "goto", "fire");
			CharacterTurnToLoc(pchar, "goto", "fire");
		break;

		case "LEDR_Gonsalo_32":
			dialog.text = "Wer weiß... Aber beim Meer, so leicht habe ich schon lange nicht mehr geatmet. Als wäre eine alte Schuld endlich vergeben. Und doch... Wäre es besser gewesen, ich hätte dieses verfluchte Tagebuch nie gesehen. Und nie erfahren, was darin steht.";
			link.l1 = "Kein Wunder, dass du so etwas geträumt hast. Auch wenn du an all dem nicht beteiligt warst, bist du der Einzige von den Lebenden, der irgendwie mit dem Tagebuch verbunden war.";
			link.l1.go = "LEDR_Gonsalo_33";
		break;
		
		case "LEDR_Gonsalo_33":
			dialog.text = "Weder Gold noch Glaube rechtfertigen das, was die Menschen unter Velázquez' Befehl getan haben. Und ich bin froh, dass alles, was daran erinnern konnte, verbrannt ist. Solche Dinge dürfen nicht in die Hände derer geraten, die sich daran ein Beispiel nehmen könnten.";
			link.l1 = "Velázquez ist nur einer von vielen. Wer weiß, wie viele solcher Tagebücher noch in den Händen der Leute im alten Europa kursieren und die Gier und Straflosigkeit neuer Eroberer anheizen? Eines ist immerhin erfreulich – dieses hier wird niemanden mehr vergiften. Übrigens, in der Truhe des Bischofs lag nicht nur das Tagebuch, sondern auch ein ordentlicher Vorrat an Dublonen – dreihundert Stück. Die Hälfte davon steht dir zu.";
			link.l1.go = "LEDR_Gonsalo_34_share";
			link.l2 = "Velázquez hat für seine Sünden bezahlt, und wer sich entscheidet, seinen Weg zu gehen, wird das gleiche Schicksal ereilen. Früher oder später wird das Schicksal jedem das Seine geben.";
			link.l2.go = "LEDR_Gonsalo_34_silence";
		break;
		
		case "LEDR_Gonsalo_34_share":
			dialog.text = "Wenn das so ist – ich sage nicht nein. Geld braucht schließlich jeder, und ich gerade besonders. Mich nimmt ja kein Schiff mehr als Matrosen – ich bin zu alt geworden. Also danke, Kapitän, dass Sie mich nicht einfach abgewiesen haben."+GetSexPhrase("ся","ась")+", wie die anderen.";
			link.l1 = "Ich muss zugeben, deine Geschichte kam mir anfangs wie das wirre Gerede eines Verrückten vor. Aber du hast sie so überzeugend erzählt, dass man, ob man will oder nicht, unweigerlich anfängt, zu glauben. Und doch hat mich das Auftauchen dieser indianischen Untoten völlig überrascht.";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "Ich wollte nur herausfinden, ob du nicht verrückt bist. Du verstehst ja selbst, an solche Geschichten glaubt man nicht so einfach.";
			link.l2.go = "LEDR_Gonsalo_35_2";
			RemoveDublonsFromPCharTotal(150);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.quest.LEDR_share = true;
		break;
		
		case "LEDR_Gonsalo_34_silence":
			dialog.text = "Man möchte daran glauben... Aber beim Meer, ich habe zu viele gesehen, denen das Schicksal trotz all ihrer finsteren Taten hold war. Vielleicht holt sie die Strafe noch ein – aber erst dort, im verdammten Kessel. Und dir danke ich, Kapitän. Dafür, dass du dich nicht abgewandt hast, zugehört und mich begleitet hast. Das, weißt du, bedeutet viel.";
			link.l1 = "Ich gebe zu, deine Geschichte kam mir anfangs wie das wirre Gerede eines Verrückten vor. Aber du hast sie so überzeugend erzählt, dass man, ob man will oder nicht, unweigerlich anfängt zu glauben. Und trotzdem hat mich das Auftauchen dieser indianischen Untoten völlig überrascht.";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "Ich wollte nur herausfinden, ob du nicht verrückt bist. Du verstehst ja selbst, an solche Geschichten glaubt man nicht so einfach.";
			link.l2.go = "LEDR_Gonsalo_35_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

		case "LEDR_Gonsalo_35_1":
			dialog.text = "Jetzt weißt du, was ich gefühlt habe, als ich diese Untoten zum ersten Mal gesehen habe. Ich hoffe, das ist jetzt endgültig vorbei... Sonst werde ich das nächste Mal wohl kaum überleben.";
			link.l1 = "Nun, da wir hier fertig sind, wird es Zeit, dass wir verschwinden. Geh an Bord, ich setze dich im Hafen von Sharptown ab.";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "LEDR_Gonsalo_35_2":
			dialog.text = "Jetzt weißt du, was ich gefühlt habe, als ich diese Untoten zum ersten Mal gesehen habe. Ich hoffe, dass wir sie für immer los sind... Sonst werde ich das nächste Mal wohl kaum überleben.";
			link.l1 = "Nun, da wir hier fertig sind, wird es Zeit, aufzubrechen. Komm an Bord, ich setze dich im Hafen von Sharptown ab.";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "LEDR_Gonsalo_36":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_12");
		break;
		
		case "LEDR_Gonsalo_37":
			dialog.text = "Nochmals danke, Kapitän "+GetFullName(pchar)+". Beim Meer, dieses seltsame Gefühl ist verschwunden, und ich hoffe, es hat seinen verfluchten Sack voller Knochen mitgenommen. Wie wär's, wenn wir uns einen Becher gönnen, hm?";
			link.l1 = "Ich danke dir für die Einladung, Gonzalo, aber ich habe noch jede Menge zu tun. Vielleicht ein andermal. Trink auf uns beide.";
			link.l1.go = "LEDR_Gonsalo_38";
		break;
		
		case "LEDR_Gonsalo_38":
			if (CheckAttribute(npchar, "quest.LEDR_share"))
			{
				dialog.text = "Ich verstehe. Aber ich sage dir eins, Kapitän: Nach allem, was wir zusammen durchgemacht haben, kann ich nicht einfach so gehen, ohne mich zu bedanken. Das wäre nicht richtig. Hier, nimm das. In meiner Jugend bin ich oft Schätzen hinterhergejagt, beim Meer, ich schwöre es. Aber jetzt ist die Gesundheit nicht mehr die gleiche, und der Rücken macht auch nicht mehr mit. Du aber bist jung, ein erfahrener Seewolf. Du wirst es ohne Mühe schaffen. Viel Glück, "+GetFullName(pchar)+", günstigen Wind und sieben Fuß Wasser unter dem Kiel.";
				link.l1 = "Danke, Gonzalo. Dir auch viel Glück, leb wohl.";
				AddMapPart();
			}
			else
			{
				dialog.text = "Nun denn, es ist wohl Zeit, Abschied zu nehmen. Gute Reise und stets eine Handbreit Wasser unterm Kiel, Kapitän "+GetFullName(pchar)+"!";
				link.l1 = "Alles Gute, Gonzalo.";
			}
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_14");
		break;
		
		
		
	}
}