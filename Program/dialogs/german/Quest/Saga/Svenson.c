// Ян Свенсон - пиратский барон Западного Мэйна
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson")) {
				if (pchar.questTemp.HelenDrinking.Result == "won") {
					dialog.text = "Ach, Charles. Danke, dass du vorbeikommst. Ich wollte dir für die Zeit danken, die du mit Helen verbracht hast. Das Mädchen musste ihre Wunden heilen, und ich habe gehört, du hattest auch eine gute Zeit, ha-ha! Verdammt, ich bin sogar eifersüchtig!";
					link.l1 = "Du bist nicht verärgert? Wegen dem Fass und... allem anderen?";
					link.l1.go = "after_drinking";
				} else {
					dialog.text = "Ach, Charles. Danke, dass du vorbeigekommen bist. Ich wollte mich nur bei dir bedanken, dass du Zeit mit Helen verbracht hast. Das Mädchen musste ihre Wunden heilen und ich habe gehört, du hattest auch eine gute Zeit, ha-ha! Viel Glück in Cartagena!";
					link.l1 = "Ja, ich bin auch froh, dass gestern alles gut gelaufen ist. Bis wir uns wiedersehen, Jan.";
					link.l1.go = "exit";
				}
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson");
				break;
			}
		
			if(CheckAttribute(pchar, "questTemp.Saga"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga_Late")) // отсекание при провале по времени
				{
					dialog.text = "Oh, mein Freund "+pchar.name+"! Freut mich, dich zu sehen! Was kann ich für dich tun?";
					link.l1 = "Wollte nur vorbeischauen, um zu sehen, wie es dir geht.";
					link.l1.go = "exit";
					if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
					{
						if (GetDataDay() == 14 || GetDataDay() == 28)
						{
							link.l2 = "Jan, ich möchte Eisenholz kaufen.";
							link.l2.go = "trade_bakaut";
						}
					}
					break;
				}
				if(pchar.questTemp.Saga == "svenson")
				{
					dialog.text = "Wie kann ich Ihnen helfen, Mister?";
					link.l1 = "Ich möchte um Ihre Hilfe bitten, Forest Devil.";
					link.l1.go = "saga";
					break;
				}
				if(pchar.questTemp.Saga == "svenson1")
				{
					dialog.text = "Aha, mein Freund "+pchar.name+"! Was sind die Neuigkeiten?";
					link.l1 = "Ich habe es geschafft, viele interessante Dinge von Hangman zu lernen.";
					link.l1.go = "saga_11";
					break;
				}
				if(pchar.questTemp.Saga == "svenson2")
				{
					dialog.text = "Also, "+pchar.name+", hast du mit Gladys gesprochen?";
					link.l1 = "Ja, das habe ich. Jan, schau mal hier... Kannst du mir etwas über dieses Stück Pergament hier sagen?";
					link.l1.go = "saga_17";
					break;
				}
				if(pchar.questTemp.Saga == "helena1" || pchar.questTemp.Saga == "helena2" || pchar.questTemp.Saga == "svenson_wait")
				{
					dialog.text = "Ich habe dir noch nichts Neues zu erzählen, "+pchar.name+". Aber ich arbeite an einer Lösung für unser Anliegen. Komm später wieder.";
					link.l1 = "In Ordnung, Jan. Ich werde dich später sehen.";
					link.l1.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests") // старт трех квестов баронов
				{
					// первая проверка времени. Свенсон очень недоволен растяпством ГГ. Счищаем Элен, к Свенсону доступ закроем
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = ""+pchar.name+", du hast mich völlig enttäuscht. Ich dachte, du seist ein ernsthafter Mann, aber wie sich herausstellt, bist du nur ein dummer Junge. Wo bist du die ganze Zeit gewesen, hm? Die Engländer haben Isla Tesoro beansprucht, während du Gott weiß was gemacht hast!\nAll meine Pläne sind ruiniert! Um ehrlich zu sein, habe ich fast vergessen, dass es dich gibt und ich möchte nicht daran erinnert werden. Verschwinde!";
						link.l1 = "Ich kann es nicht glauben!";
						link.l1.go = "saga_l1";
					}
					else
					{
						dialog.text = "Da bist du ja, "+pchar.name+". Ich habe unsere missliche Lage etwas durchdacht. Ich würde es nicht unbedingt einen Plan nennen, aber...";
						link.l1 = "Ich bin ganz Ohr, Jan.";
						link.l1.go = "saga_25";
					}
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests_1") // идут три квеста баронов
				{
					dialog.text = "Wie läuft's? Kann ich dir irgendwie helfen?";
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "after_marlow")
					{
						link.l3 = "Ich habe mit Black Pastor gesprochen. Leider hat das Ergebnis unseres Gesprächs mich direkt wieder zu dir um Rat gebeten, ich stehe vor einem Rätsel.";
						link.l3.go = "shark_hunt_2";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "LSC" && !CheckAttribute(pchar, "questTemp.Saga.BaronReturn"))
					{
						link.l3 = "Ich habe Dios gefunden und wir hatten ein angenehmes Gespräch. Er erzählte mir viele interessante Dinge, aber leider kamen wir nicht zum Punkt.";
						link.l3.go = "shark_hunt_7";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "third_teleport")
					{
						link.l3 = "Ach, Jan. Ich habe dir so viel zu erzählen, dass es die ganze Nacht dauern würde, alles zu übermitteln, also werde ich mich kurz fassen.";
						link.l3.go = "return_LSC";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "shamane" && !CheckAttribute(npchar, "quest.shamane"))
					{
						link.l3 = "Ich habe Nathaniel Hawk von Justice Island abgeholt. Er ist gerade auf meinem Schiff.";
						link.l3.go = "nathaniel";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "treatment")
					{
						link.l3 = "Ich habe Nathaniel Hawk in einem Miskito-Dorf abgesetzt, um von einem Schamanen namens Snake Eye behandelt zu werden. Er hat mir versprochen, Nathans Gesundheit wiederherzustellen.";
						link.l3.go = "nathaniel_2";
					}
					link.l4 = "Nicht viel zu erzählen im Moment. Bin nur vorbeigekommen um zu sehen, wie es dir geht.";
					link.l4.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "fail_centurion") // провал - потоплен Центурион
				{
					dialog.text = "Wie sind die Neuigkeiten, "+pchar.name+"? Wie steht's?";
					link.l1 = "Oh, es könnte nicht schlimmer sein. Ich habe so viel Arbeit geleistet... Ich habe Jackman aufgespürt, das Feuer eröffnet und ihn wie den größten Idioten ertränkt, zusammen mit allem, was in seiner Kabine hätte sein können. Jetzt habe ich nichts, um den Gestank von Sharks Namen zu nehmen und die Hitze auf Barbazon zu legen. Ich fürchte, es ist eine verlorene Sache, Jan.";
					link.l1.go = "saga_f_1";
					break;
				}
				if(pchar.questTemp.Saga == "calendar") // квесты баронов завершены
				{
					// вторая проверка времени. Отбираем Элен, со Свенсоном нейтральные отношения - ну не выщло и не вышло, хоть попытались. Данни и Натана - в Марун-Таун
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = "Ich habe von deinen heldenhaften Taten gehört! Dannie hat mir die Kurzversion gegeben. Übrigens, wir sind jetzt Freunde. Und Nathan hat sich völlig verändert! All seine Depressionen waren wie weggeblasen, als er seinen 'Centurion' sah.\nAber ich habe schlechte Nachrichten für dich, "+pchar.name+". Wir haben so viel Zeit verschwendet, dass die Erbrechte an Sharps Testament längst verloren gegangen sind und Isla Tesoro zu einer englischen Militärbasis geworden ist. Es gibt nichts mehr, was ich tun könnte, um dir bei Levasseur zu helfen.";
						link.l1 = "Ich bin absolut sprachlos... Wir haben so viele Schwierigkeiten durchgemacht, alles umsonst. Gibt es wirklich nichts, was wir tun können?";
						link.l1.go = "saga_l2";
					}
					else
					{
						dialog.text = "Ich habe alles über deine Heldentaten gehört! Dannie hat mir die Einzelheiten erzählt. Wir haben uns übrigens versöhnt. Nathan ist kaum wiederzuerkennen. Sobald er seinen 'Centurion' sah, hat er sein Gemurre wie einen schlechten Traum hinter sich gelassen...";
						link.l1 = "Nathan ist wieder gesund? Das freut mich zu hören!";
						link.l1.go = "saga_26";
					}
					break;
				}
				if(pchar.questTemp.Saga == "mine") // рудник взят
				{
					dialog.text = "Hier bist du, "+pchar.name+"! Nun habe ich dir etwas zu erzählen.";
					link.l1 = "Hallo, Jan. Ich bin überglücklich! Was gibt's Neues? Ich hoffe, etwas Positives?";
					link.l1.go = "saga_32";
					break;
				}
				if(pchar.questTemp.Saga == "mine_1") // рудник взят совместно
				{
					dialog.text = "Hier bist du, "+pchar.name+"! Hast du dich erholt? Und darf ich schlussfolgern, dass du wieder bereit für große Abenteuer bist?";
					link.l1 = "Hallo, Jan. Ja, ich bin bereit.";
					link.l1.go = "saga_32a";
					break;
				}
				if(pchar.questTemp.Saga == "late_l3") // провал по времени у адвоката
				{
					dialog.text = "Wie stehen die Neuigkeiten, "+pchar.name+"? Wie steht's?";
					link.l1 = "Oh. Die Dinge sind absolut schrecklich. Ich habe mit Zähnen und Klauen gekämpft, aber trotzdem verloren. Wie du dich erinnerst, hatte Sharps Testament eine Frist. Nun, diese Zeit ist abgelaufen und Isla Tesoro ist jetzt eine englische Militärbasis. Es ist eine verlorene Sache, Jan.";
					link.l1.go = "saga_l3";
					break;
				}
				if(pchar.questTemp.Saga == "bakaut") // пришёл от адвоката за деньгами
				{
					dialog.text = "Grüße, "+pchar.name+"! Gute Neuigkeiten: Das Ratsmeeting wurde abgehalten und die Bruderschaft der Küste hat einen neuen Oberhaupt gefunden.";
					link.l1 = "Guten Nachmittag, Jan. Ich freue mich für dich.";
					link.l1.go = "saga_44";
					break;
				}
				if(pchar.questTemp.Saga == "sellbakaut" && GetSquadronGoods(pchar, GOOD_SANDAL) >= 1) // отдает бакаут
				{
					dialog.text = "Nun, "+pchar.name+"? Hast du Molligan eingeholt?";
					link.l1 = "Ich habe es getan. Er war es, der dein Eisenholz gestohlen hat.";
					link.l1.go = "saga_55";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut") && GetNpcQuestPastDayParam(npchar, "bakaut_date") >= 1) // за деньгами за бакаут
				{
					dialog.text = "Pünktlich wie immer, "+pchar.name+". Ich habe das Eisenholz verkauft, das du mir gebracht hast.";
					link.l1 = "Ausgezeichnet. Wie viel Geld hast du verdient?";
					link.l1.go = "saga_57";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut_sum")) // сам продал бакаут
				{
					dialog.text = "Nun, "+pchar.name+ "Hast du Molligan eingeholt?";
					link.l1 = "Habe ich. Er war derjenige, der dein Eisenholz gestohlen hat. Zufällig bin ich auch auf seinen Käufer gestoßen. Es war ein niederländischer Militärkommandant. Ich habe das Produkt an ihn verkauft.";
					link.l1.go = "saga_59";
					link.l2 = "Ich habe es getan. Ich habe versucht, ihn zu zwingen, mir seinen Frachtraum zu zeigen... wir gerieten in eine Auseinandersetzung und...jetzt gibt es keinen Molligan mehr. Aber im Laderaum gibt es nichts zu sehen außer Ebenholz und Mahagoni.";
					link.l2.go = "saga_59_1";
					break;
				}
				if(CheckAttribute(npchar, "quest.jessika")) // информация о Джессике
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Was gibt's Neues?";
					link.l1 = "Jan, ich möchte mit dir über eine Angelegenheit sprechen. Ich habe in die Vergangenheit von Helens Mutter, Beatrice, gegraben und bin zufällig auf jemanden gestoßen, den du ziemlich gut kennst. Soweit ich informiert wurde...";
					link.l1.go = "saga_62";
					break;
				}
				if(pchar.questTemp.Saga == "lastpages") 
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Wie läuft es? Nach deinem Gesicht zu urteilen, kann ich dir gratulieren? ";
					link.l1 = "Ja. Ich habe es endlich geschafft, dieses Durcheinander zu sortieren. Helen hat alle Rechte auf Isla Tesoro erhalten. Niemand wird sich jemals wieder an dem Zufluchtsort der Bruderschaft der Küste vergreifen!";
					link.l1.go = "saga_82";
					break;
				}
				if (pchar.questTemp.Saga == "end") sTemp = "Oh, mein Freund "+pchar.name+"! Ich freue mich, dich zu sehen! Was führt dich hierher?";
				else sTemp = "Sonst irgendwas, "+pchar.name+"?";
				dialog.text = sTemp;
				link.l1 = "Nein, Jan. Im Moment nichts.";
				link.l1.go = "exit";
				if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
				{
					if (GetDataDay() == 14 || GetDataDay() == 28)
					{
						link.l2 = "Jan, ich möchte etwas von deinem Eisenholz kaufen.";
						link.l2.go = "trade_bakaut";
					}
				}
				NextDiag.TempNode = "First time";
			}
			else
			{
				// заглушка Элен
				if(startHeroType == 4)
				{
					dialog.text = "Helen, hallo, meine Liebe. Welche Neuigkeiten hast du? Gab es etwas, das du wolltest?";
					link.l1 = "Hallo, Jan! Alles beim Alten, bin nur vorbeigekommen, um dich zu sehen.";
					link.l1.go = "exit";
					NextDiag.TempNode = "First time";
					break;
				}
				dialog.text = "Kann ich dir bei etwas helfen?";
				link.l1 = "Nein, mir geht's gut.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First time";
			}
		break;
		
		case "saga":
			dialog.text = "Ich kenne dich, verdammt noch mal! Du bist der mutige Kapitän, der Rumba gerettet und die Kanonen der englischen Korvette frontal angegriffen hat! Was für eine Freude, dich zu sehen! Helen ist wie eine Tochter für mich. Von heute an bin ich dir auf ewig verpflichtet. Du kannst mich einfach Jan oder Svenson nennen, wenn du möchtest. Was kann ich für dich tun?";
			link.l1 = "Ich muss Levasseur, den Gouverneur von Tortuga, ausschalten. Ich weiß, dass es keine leichte Aufgabe sein wird, ihn auf seiner Insel zu erreichen, deshalb bin ich zu dir gekommen, um Rat zu suchen.";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "Herrje, wo warst du vor ein paar Jahren! Ich hatte vor, genau das gleiche Abenteuer zu erleben. Er hat das ganze Spiel für uns mit den Franzosen ruiniert. Aber damals war alles anders. Blaze war am Leben, Shark hatte etwas zu sagen, und Nathan gab in Maroon Town den Ton an... Jetzt hat sich alles geändert und, Gott weiß, nicht zum Besseren. Weißt du etwas über uns, über die Bruderschaft?";
			link.l1 = "Ich bin erst kürzlich hier angekommen, also weiß ich im Grunde genommen nichts. Außer der Tatsache, dass du und Jackman Teil des Rates sind.";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			dialog.text = "Oh, ich kann diesen Jackman nicht ausstehen! Als er hier ankam, begannen all unsere Probleme. Ich werde deinen Antrag in Erwägung ziehen. Auf Anhieb fällt mir nichts ein.";
			link.l1 = "Ich habe etwas Interessantes über Jackman.";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			dialog.text = "Hm. Was ist es?";
			link.l1 = "Jackman sucht nach Gladys Chandler und ihrer Tochter. Nachdem ich mit Higgins gesprochen habe, habe ich angefangen zu denken, dass er nach Rumba sucht. Es scheint, dass Gladys nicht Helens leibliche Mutter ist und ihr Nachname Chandler war, bevor sie Sean McArthur heiratete.";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			dialog.text = "Verflucht! Das sind schlechte Nachrichten. Jackman ist stärker als je zuvor. Und dazu habe ich das ungute Gefühl, dass er nicht alleine arbeitet. Er hat einen ziemlich unheimlichen Schatten hinter sich. Wenn er Helen wirklich braucht, dann braucht das Mädchen dringend einen Beschützer. Ich fürchte, ich bin ein wenig zu alt, um das selbst zu tun...";
			link.l1 = "Das ist nicht alles. Jackman sucht auch nach jemandem namens Henry Hangman, ehemaliger Bootsmann der 'Neptune', aus der Crew von Kapitän Butcher.";
			link.l1.go = "saga_5";
		break;
		
		case "saga_5":
			dialog.text = "Verdammt! Meine schlimmsten Befürchtungen haben sich bestätigt! Dieser Butcher und sein 'Neptune' haben das ganze Archipel in Angst und Schrecken versetzt. Damals gab es keine Brüder, jeder war auf sich allein gestellt. Dieser Mann hat viele schlechte Dinge getan, eine mir nahestehende Person ist wegen ihm gestorben.\nIch hatte nie die Gelegenheit, ihn zu treffen. Der 'Neptune' wurde von einer englischen Fregatte versenkt und Butcher wurde in St. John's hingerichtet. Gut so! Obwohl es viele Menschen gab, die sein Glück und seine rücksichtslose Tapferkeit bewunderten.\nJackman selbst war seine rechte Hand und erster Maat auf dem 'Neptune'. Überrascht? Die ehemaligen Verbrecher sind zu Helden der Nation geworden, alles dank Cromwell! Wo ist das gute alte England hin?\nWir müssen Henry Hangman finden, bevor Jackmans Männer es tun. Vielleicht hält er den Schlüssel zu diesem Rätsel, wenn er noch lebt.";
			link.l1 = "Ich wette, du hättest es einfacher, eine Nadel im Heuhaufen zu finden. Hast du zumindest irgendeinen Hinweis?";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Ich kannte Henry, als er noch ein Kind war. Der Sohn einer Hure aus Cartagena, halb Spanier, obwohl er es immer geheim hielt. Seine Mutter war heiß! Kann nicht sagen, dass sie hübsch war, aber es gab sehr wenige Flamencotänzerinnen wie sie. Das ganze Bordell schaute sich Shows der nackten Chica Gonzales und ihrer Kastagnetten an.\nArmes Mädchen. Hatte eine schlimme Krankheit und starb wie eine Kerze. Das war, als ich Henry überredete, nach Providence zu gehen, wo er sich schnell einen Namen machte und sich der Crew von Thomas Beltrope anschloss, einem engen Freund von Nicolas Sharp. Diese beiden waren die letzten Hunde der Königin Elizabeth und arbeiteten immer zusammen. Gute Zeiten!\nThomas segelte zurück nach England, als sein Partner starb. Er nahm seine Crew mit, aber Henry blieb in der Karibik. Segelte unter verschiedenen Kapitänen, bis Butcher auftauchte. Übrigens, er bekam seinen Spitznamen wegen einer Entermesser, die er immer bei sich hatte.";
			link.l1 = "Und was sagt uns diese Information?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Wenn Hangman sich vor den Piraten versteckt hat, wäre der beste Ort für ihn in einer spanischen Stadt. Besonders in seinem Zuhause in Cartagena, wo er Freunde und Verwandte hat. Henry war ziemlich religiös. Daher ist es unwahrscheinlich, dass er zu einer anderen Heiligenkirche gehen würde. Er hat wahrscheinlich immer noch denselben Namen, den er seit seiner Kindheit hatte, Enrique.";
			link.l1 = "Ja... Die Auswahl ist dürftig, aber immerhin ist es besser als nichts.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Versuche ihn zu finden, Charles! Nur wenige wissen von Henrys spanischen Wurzeln, daher haben wir hier einen kleinen Vorteil. Ich werde darüber nachdenken, wie ich Rumba dazu überreden kann, deiner Crew beizutreten. Das Mädchen hat Mumm, hat nie unter jemandes Kommando gedient außer dem ihres Vaters.\nAber sie hat weder Schiff noch Crew und sie muss ihren Lebensunterhalt verdienen. Sicher, ich werde Gladys weiterhin helfen, wie ich es immer getan habe, aber ich werde Helen nicht lange in Blueweld halten können. Und einen solchen Offizier wirst du sehr nützlich finden. Sean hat ihr alles beigebracht, was er wusste, und hat sie wie einen Jungen aufgezogen.\nIch würde mich wohler fühlen, wenn sie unter dem Kommando eines solchen Kapitäns wie dir wäre.";
			link.l1 = "Rumba hat sich als sehr würdig erwiesen. Ich brauche mehr Leute wie sie in meiner Crew. Also, wenn es dir gelingt, sie zu überreden, werde ich sie zu einem Offizier machen. Aber zuerst möchte ich verstehen, wer sie wirklich ist und warum Jackman sie braucht. Ich befürchte, dass er, im Gegensatz zu Donovan, nicht an ihren Reizen interessiert ist. Also werde ich versuchen, Hangman zu finden, obwohl ich nichts versprechen kann.";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Nun, ausgezeichnet. Nimm diese Lizenz der Holländischen Westindien-Kompanie für drei Monate. Schreib deinen Namen dort hinein, es könnte dir bei deinen Suchen sehr nützlich sein. In der Zwischenzeit werde ich über das nachdenken, was du über Levasseur und Tortuga gesagt hast.";
			link.l1 = "Vielen Dank! Dieses Papier wird mir nützlich sein. In diesem Fall gehe ich dann nach Cartagena.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			DialogExit();
			GiveNationLicence(HOLLAND, 90);
			AddQuestRecord("Saga", "14");
			pchar.questTemp.Saga = "cartahena";//идем в Картахену
			pchar.quest.Saga_Gonsales.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales.win_condition.l1.location = "Cartahena_town";
			pchar.quest.Saga_Gonsales.function = "Saga_CreateGonsalesB";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			LocatorReloadEnterDisable("FortOrange_town", "reload6", true); // закрыть резиденцию Джекмана
			npchar.greeting = "svenson_3";
			
			AddQuestRecord("HelenDrinking", "1");
			pchar.questTemp.HelenDrinking.CanDrink = true;
			SetFunctionTimerConditionParam("HelenDrinking_NoVisit", 0, 0, 1, 24 - GetHour(), false);
			
			pchar.questTemp.Saga.HelenRelation = 0;
		break;
		
		case "saga_11":
			dialog.text = "Henry ist tot? Warte, hast du ihn getötet?";
			link.l1 = "Schau mich nicht mit diesen großen Augen an! Ich hatte nichts damit zu tun. Er starb durch seine eigene, von seinem verrottenden Gewissen und seiner Angst vor Jackman. Der alte Pirat hatte Probleme mit seinem Herzen und er hatte nicht mehr lange zu leben. Hier ist, was ich herausfinden konnte...";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Bitte, erzähl!";
			link.l1 = "Vor zwanzig Jahren sollte Henry im Auftrag von Kapitän Butcher eine Kiste Gold an die Pflegemutter seiner leiblichen Tochter übergeben. Es besteht absolut kein Zweifel, dass diese Pflegemutter Mrs. McArthur war. Damals trug sie den Nachnamen Chandler und lebte in Belize. Aber Umstände hielten Hangman einen ganzen zusätzlichen Monat in St. John's auf und als er endlich in Belize ankam, war es nach einem Überfall durch die Spanier in Trümmern, und Tante Gladys und Sean waren bereits unter deinem Schutz auf dem Weg.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "";
			link.l1 = "Sie gaben Helen als ihre leibliche Tochter aus und zogen sie als ihre eigene auf. Henry verlor ihre Spur und hielt sich versteckt, sich der Rache Jackmans bewusst und lebte die ganzen zwanzig Jahre seitdem in Angst. Es stellt sich heraus, dass Jackman nach der Tochter seines Kapitäns sucht. Aber warum, das weiß ich nicht.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "Vielleicht führt er jemandes Befehle aus...";
			link.l1 = "Bezweifle es. Wer könnte ihm Befehle erteilen? Butcher ist tot. Sein Tod wird durch offizielle Dokumente bestätigt. Dutzende, wenn nicht Hunderte von Menschen waren Zeugen seines Todes.";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "Vielleicht geht es hier nicht darum, wer Helens Vater ist. Vielleicht geht es nur um ihre leibliche Mutter. Ich kann schon erraten, wer sie war, aber ich habe Angst, es anzuerkennen. Aber Gladys! Wie konnte sie dieses Geheimnis so viele Jahre lang für sich behalten, ohne es sogar ihrem Ehemann zu verraten! Sean McArthur hätte es mir sicher erzählt. Wir haben nie irgendwelche Geheimnisse gehabt, die wir uns nicht erzählt haben.";
			link.l1 = "Ich werde ein Herz-zu-Herz-Gespräch mit Gladys führen. Ich glaube, ich habe die Mittel, um sie zum Reden zu bringen. Bis zum nächsten Mal, Jan!";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			DialogExit();
			pchar.questTemp.Saga = "gladis1";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_history";
			AddQuestRecord("Saga", "21");
		break;
		
		case "saga_17":
			dialog.text = "Wo hast du das her!?";
			link.l1 = "Gladys hat es mir gegeben. Sie sagte, es sei das 'Erbe von Helens Mutter'. Sie kennt ihren Namen nicht. Etwas sagt mir, dass dies kein durchschnittliches Stück Schmierpapier ist.";
			link.l1.go = "saga_18";
		break;
		
		case "saga_18":
			dialog.text = "Erinnerst du dich, als ich dir sagte, dass ich eine Ahnung hatte, wer Helens wirkliche Mutter war? Jetzt bin ich mir sicher. Ihr Name war Beatrice Sharp. Sie war die biologische Tochter meines Lehrers und Freundes Nicholas Sharp, die erklärte Schwester des Gründers unserer Brüder, Blaze Sharp, und Teilhaberin von Isla Tesoro. Es ist dieses Kartenstück, hinter dem Jackman her ist.";
			link.l1 = "Nun, das ist doch mal was! Aber warum würde er die Hälfte einer Inselkarte benötigen?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "Die Insel wurde von Nicolas Sharp entdeckt. Er nannte sie Isla Tesoro, kartographierte sie und nahm sie durch die Providence Island Company in Besitz, wo er gute Verbindungen hatte.\nNicolas schrieb in seinem Testament, dass die Insel nur von denen geerbt werden kann, die zwei Teile der Karte vorweisen können. Er tat dies, um jegliche Uneinigkeiten zu vermeiden. Er gab die Teile an Beatrice und seinen Stiefsohn Blaze weiter, bevor er tragisch durch spanische Hand starb.";
			link.l1 = "Nun, verdamme mich! Wie seltsam.";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "Du hast recht. Es war keine gute Idee. Und ein schlauer Notar fügte hinzu, dass die Insel zur englischen Krone gehören wird, wenn niemand innerhalb eines Jahres nach dem Tod der Erben beide Teile der Karte vorlegt.\nNiemand hätte das damals erwartet. Und jetzt zahlen wir den Preis für unsere Dummheit. Beatrice starb vor zwanzig Jahren. All diese Jahre sind vergangen und wir haben immer noch keine Ahnung, wo ihr Grab zusammen mit ihrem Teil der Karte ist. Blaze Sharp wurde vor nicht allzu langer Zeit ermordet. Sein Teil ist auch verschwunden.\nWenn niemand innerhalb eines Jahres die ganze Karte von Isla Tesoro den Behörden vorlegt, dann wird Sharptown von England beansprucht. Sie werden einen Gouverneur mit einer Garnison dort schicken und die Bruderschaft wird erledigt sein.";
			link.l1 = "Was schlägst du vor, sollten wir tun?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "Wir dürfen das nicht zulassen. Ich brauche dich, Charles, ich brauche dich, um einen solchen Verlauf der Ereignisse zu verhindern. Und ich werde in der Lage sein, dir bei der Beseitigung von Levasseur zu helfen, erst nachdem wir die Kontrolle über Isla Tesoro übernommen und Shark Dodson zum neuen Anführer der Bruderschaft gewählt haben. Er ist der Würdigste von uns. Ich biete dir ein Bündnis an.\nUnd übrigens, ich habe mit Helen gesprochen. Sie hat zugestimmt, sich deiner Mannschaft anzuschließen.";
			link.l1 = "Du lässt mir keine Wahl, Jan. Ich kann nicht nach Frankreich zurückkehren, ohne die Ehre meiner Familie wiederherzustellt. Und um das zu tun, muss ich Levasseur ausschalten, mit oder ohne deine Hilfe. Unnötige Tode sind nicht das, was ich will und ich hoffe, du kannst herausfinden, wie man Tortuga einnimmt, ohne zu viel Blut zu vergießen. Obwohl, ich muss zugeben, dass ich gerne selbst den nebligen Hintergrund von Sharps' Erbschaft verstehen würde.";
			link.l1.go = "saga_22";
		break;
		
		case "saga_22":
			dialog.text = "Es ist schön, vernünftige Gedanken zu hören! Wir werden den richtigen Weg finden, Tortuga einzunehmen. Das verspreche ich dir. Also, legen wir los?";
			link.l1 = "Ja! Ich schaue später noch einmal vorbei. Überlege dir vorerst, wo du anfangen sollst, das Problem anzugehen.";
			link.l1.go = "saga_23";
		break;
		
		case "saga_23":
			dialog.text = "Komm in zwei oder drei Tagen wieder. Ich denke, bis dahin wird mein Plan zur Vollendung gekommen sein. Und vergiss nicht, Helen auf dein Schiff mitzunehmen. Das arme Mädchen welkt einfach ohne das Meer. Sie wird eine treue Assistentin sein und du musst nicht zweimal darüber nachdenken, sich auf sie zu verlassen.";
			link.l1 = "In Ordnung, Jan. Ich gehe sie jetzt sofort holen.";
			link.l1.go = "saga_24";
		break;
		
		case "saga_24":
			DialogExit();
			pchar.questTemp.Saga = "helena1";
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);//закрыть выходы из города
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			AddQuestRecord("Saga", "23");
		break;
		
		case "saga_25":
			dialog.text = "Zuerst musst du Shark finden. Er wollte Levasseur selbst loswerden und ich versichere dir, dass er einige helle Ideen hat. Natürlich könnten wir auch Marcus dazu überreden, die Führung zu übernehmen. Er ist schließlich der Hüter des Kodex. Aber ich bezweifle, dass er von irgendeinem Nutzen wäre, er hat absichtlich jeden Kontakt mit Levasseur und Tortuga eingeschränkt. Ein Mann der Prinzipien.\nIch habe keine Ahnung, wo Steven und seine Männer sich verstecken, aber seine Fregatte 'Fortune' wurde in Puerto Principe gesehen. Vielleicht kann Zachary Marlow, auch bekannt als der Black Pastor, uns darauf hinweisen, wo wir nach Shark suchen sollten. Zweitens müssen wir die Unterstützung der anderen Barone gewinnen, um Dodson zu wählen. Und um das zu tun, müssen wir ihre indischen Splitter sammeln - die Stimmen. Der neue Führer muss alle fünf von ihnen haben. Das ist es, was uns der Kodex im Falle des Todes des vorherigen Anführers sagt.\nLächerlich! Es ist an der Zeit, die Gesetze zu ändern, aber nur der neue Anführer kann das tun. Wir haben bereits meine Stimme. Ich glaube, dass dem Black Pastor völlig egal ist, wessen Hintern in Sharptown sitzt. Ich hoffe, dass Jackman nicht zuerst mit ihm gesprochen hat. Wir müssen auch sowohl Tyrex als auch Jacques Barbazon überzeugen, die sich gegenseitig hassen. Aber das ist alles irrelevant, bis wir herausfinden, was mit Shark passiert ist. Drittens, eines Tages werden wir Jackman töten müssen und ihn durch jemand anderen ersetzen. Er wird nicht mit uns verhandeln.\nZu schade, dass Hawk tot ist! Die Leute vertrauten ihm und wir könnten sein Wort gebrauchen. Wir werden keinen besseren Baron für Maroon Town finden. Es ist möglich, dass Jackman etwas mit Blazes Mord zu tun hat, also ist er auch der Schlüssel zur Entdeckung des zweiten Teils der Karte. Jacob vertraut niemandem und behält wahrscheinlich den Teil der Karte in seiner Kabine auf der 'Centurion'.\nHawks Familie besaß die Fregatte, aber Jackman hat sie sich genauso wie Hawks Baronie angeeignet. Wenn wir den zweiten Teil der Karte in Jackmans Besitz finden, wäre das ein starkes Argument für Stevens Wahl. Besonders für Marcus Tyrex, den Hüter des Kodex, und seine übermäßige Gewissenhaftigkeit in Bezug auf die Ehre. Wir werden Helen ihre Rechte über Isla Tesoro zurückgeben, sobald wir beide Teile der Karte erworben haben.\nWir müssen jedoch vorsichtig sein, Jackman wird nicht untätig bleiben und einfach nur zusehen, wie wir suchen.";
			link.l1 = "Nun... Ich bin kurz davor, dem Black Pastor einen Besuch abzustatten. Erzähl mir von ihm.";
			link.l1.go = "shark_hunt";
			pchar.questTemp.Saga = "baronsquests_1";
		break;
		
		case "shark_hunt":
			dialog.text = "Himmel, wenn ich wüsste, was in seinem Kopf vorgeht. Manchmal wirkt er wie ein völliger Freak, aber ich glaube, das ist nur kluges Schauspiel. Außerdem sind seine Männer bereit, den Teufel selbst im Namen ihres geliebten Pastors zu bekämpfen. \nSie haben eine Art protestantische Sekte nahe der Spanischen Inquisition auf Kuba gegründet. Also fang gar nicht erst an, dort über theologische Angelegenheiten zu sprechen, sie werden sie nicht billigen.";
			link.l1 = "Ich werde das berücksichtigen...";
			link.l1.go = "shark_hunt_0";
		break;
		
		case "shark_hunt_0":
			dialog.text = "Und, "+pchar.name+": verschwende keine Minute deiner Zeit. Ich meine es ernst. Erinnerst du dich an das Kleingedruckte im Testament, das besagt, dass die Insel an die englische Krone fällt, wenn die Erben sie nicht innerhalb eines Jahres beanspruchen, richtig? Nun, die Zeit ist gerade nicht auf unserer Seite. Als wir uns das letzte Mal sahen, waren nur noch etwa elf Monate übrig, bis die Frist abläuft.";
			link.l1 = "Ich erinnere mich, Jan. Du hast recht, Zeit ist Geld. Ich bin dran!";
			link.l1.go = "shark_hunt_1";
		break;
		
		case "shark_hunt_1":
			DialogExit();
			AddQuestRecord("SharkHunt", "1");
			pchar.questTemp.Saga.SharkHunt = "begin";
			pchar.GenQuest.LigaAttack = "true"; // киллеры Лиги активированы
		break;
		
		case "shark_hunt_2":
			dialog.text = "Hm... Was hat Zachary dir erzählt?";
			link.l1 = "Bevor er verschwand, kam Shark zu ihm, ließ seine Fregatte als Sicherheit für eine Brigg mit etwas Essen bei Zachary zurück und segelte dann irgendwo nordwestlich nach Kuba.";
			link.l1.go = "shark_hunt_3";
		break;
		
		case "shark_hunt_3":
			dialog.text = "Das ist wirklich verdächtig. Rede weiter.";
			link.l1 = "Einen Monat später kehrte Dodson nicht zurück und der Pastor nahm die Fregatte gemäß den Bedingungen der Vereinbarung für sich selbst und verkaufte sie für einen guten Preis an einen Kerl namens Paterson. Was unsere Angelegenheiten betrifft, erwähnte Zachary, dass Shark möglicherweise zur legendären Insel Justice Island aufgebrochen ist, die angeblich irgendwo nicht weit nordwestlich von Kuba liegt.";
			link.l1.go = "shark_hunt_4";
		break;
		
		case "shark_hunt_4":
			dialog.text = "Ich habe von Justice Island gehört. Sie sagen, dass es eine Insel gibt, auf der Weiße und Schwarze friedlich zusammenleben, als Gleiche. Bullshit, verbreitet von allerlei Träumern. Aber es besteht die Möglichkeit, dass im Nordwesten eine Art Schmugglerbasis existiert. Ihre Barken wurden vor zehn Jahren regelmäßig auf hoher See gesehen. Sie brachten verschiedene Waren nach Kuba im Austausch für Lebensmittel.";
			link.l1 = "Schätze für Essen? Der Pastor hat mir auch von den Rindfleischverschiffenden Freibeutern erzählt. Es ist praktisch ein wandelnder Widerspruch.";
			link.l1.go = "shark_hunt_5";
		break;
		
		case "shark_hunt_5":
			dialog.text = "Diese Gerüchte müssen eine Quelle haben, diese Schmuggler- oder Seeräuberschiffe segelten aus irgendeinem Grund in diese Region. Ich erinnere mich, dass Shark mir Geschichten aus seiner Jugend erzählte, er war eine Art Sklave bei einer merkwürdigen Formation aus Schiffswracks mitten im Meer.\nVielleicht ist das unser Ort? Keine Ahnung. Jedenfalls hat der Pastor recht, irgendwas ist da draußen, entweder eine geheime Basis oder eine Insel, auf die Shark hätte gehen können. Hör zu, segle nach Santo Domingo und finde einen Wissenschaftler namens Jose Dios.\nEr ist ein spanischer Kartograph. Ich habe ihn einmal vor dreckigem Gesindel gerettet, ich respektiere gebildete Leute. Er wird dir helfen, sag ihm einfach meinen Namen. Geh nach Hispaniola, finde Dios und sprich mit ihm.\nEr kennt unsere Region's Geographie perfekt und wenn er dir nicht helfen kann - kann es niemand.";
			link.l1 = "In Ordnung, Jan. Klingt nach einem Plan. Ich mach mich auf den Weg!";
			link.l1.go = "shark_hunt_6";
		break;
		
		case "shark_hunt_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "dios";
			AddQuestRecord("SharkHunt", "3");
		break;
		
		case "shark_hunt_7":
			dialog.text = "Das ist zu schade. Ich hatte gehofft, dass Jose uns eine Hand leihen würde.";
			link.l1 = "Ich habe auch darauf gehofft, aber ach. Nun, lass uns nicht in Selbstmitleid versinken. Ich werde noch etwas mehr Zeit mit Nachdenken über diese Angelegenheit verbringen. Ja, Jan, sag mir, wie ist Hawk gestorben?";
			link.l1.go = "baron_return";
		break;
		
		case "baron_return":
			dialog.text = "Niemand hat seinen Tod bezeugt, genauso wie niemand seinen Körper gesehen hat. Er ist einfach vor einigen Monaten verschwunden. Seitdem ist es genauso wie mit Shark. Aber im Gegensatz zu Steven hatte Nathan keinen Grund, sich zu verstecken. Aus diesem Grund haben alle angenommen, dass er in der Selva gestorben ist. Wenn das nicht der Fall gewesen wäre, hätten sie nicht zugestimmt, Jackman an seiner Stelle zu wählen.";
			link.l1 = "Was zum Teufel hat Hawk im Dschungel gemacht?";
			link.l1.go = "baron_return_1";
		break;
		
		case "baron_return_1":
			dialog.text = "Es war mein Fehler, ich bin ein alter Narr! Ich hatte ihn dazu überredet, sich um die neu angekommenen Banditen zu kümmern. Ich habe keine Ahnung, wer sie sind und wer ihr Boss ist. Normalerweise würde es mich nicht interessieren, aber sie begannen, freundliche Miskitos zu entführen. Ihr Kriegshäuptling Kumvana drohte, den Kriegspfad zu erklären und bat um meine Hilfe. Ich hatte keine andere Wahl, als einzugreifen.\nHawk landete mit einer kleinen Einheit an der Moskitoküste, geriet in einen hervorragend organisierten Hinterhalt und wurde dann besiegt. Es sah so aus, als ob er und seine Männer erwartet wurden, dort zu landen. Hawks Leiche wurde nicht unter den anderen im Dschungel gefunden.";
			link.l1 = "Unter deiner Nase geschehen allerlei Schabernack! Hat keiner von Hawks Leuten versucht, die Banditen zu bewältigen?";
			link.l1.go = "baron_return_2";
		break;
		
		case "baron_return_2":
			dialog.text = "Jackman kam allen zuvor. Er hat sich selbst beim Rat der Bruderschaft gemeldet, um das Problem zu lösen und die Entscheidung zu treffen. Die Miskitos hörten auf zu verschwinden, aber die Banditen blieben dort, hielten sich relativ bedeckt.\nJackman sagte, dass sie niemanden von denen, die sie angreifen kamen, als Geisel hielten und es keinen Grund für die Bruderschaft gab, ihnen den Krieg zu erklären. Hawk griff sie zuerst an, also nach unseren Gesetzen hatten die Banditen das Recht, sich zu schützen. Alle stimmten zu. Alle außer...";
			link.l1 = "Aber wer nicht?";
			link.l1.go = "baron_return_3";
		break;
		
		case "baron_return_3":
			dialog.text = "Nathan hatte eine Frau. Ihr Name ist Danielle Hawk und sie ist eine harte Schlampe! Ich bezweifle, dass sie jemals über den Verlust ihres Kapitäns hinweggekommen ist, ganz zu schweigen von der Tatsache, dass sie von Anfang an etwas vermutete und versuchte, Hawk zu entmutigen. Ich erinnere mich, dass sie einen riesigen Streit darüber hatten, aber das war für sie nichts Ungewöhnliches.";
			link.l1 = "Und wo ist Danielle jetzt?";
			link.l1.go = "baron_return_4";
		break;
		
		case "baron_return_4":
			dialog.text = "Wer weiß! Jackman hat dafür gesorgt, dass sie Maroon Town verlässt. Sie besucht mich nicht. Wir mochten uns nie, sie ist im Laufe der Jahre noch zickiger geworden, und jetzt muss sie mich wirklich hassen, weil sie wahrscheinlich glaubt, dass ich der Grund für ihr Unglück bin.\nVielleicht sucht sie auf eigene Faust nach Hawk, aber was kann eine Frau tun, auch wenn sie Hosen und ein Säbel trägt! Übrigens, sie beherrscht den Säbel. Ich empfehle nicht, sie zu testen, wenn du ihr begegnest. Ja, und es lohnt sich auch nicht, mit den Banditen zu reden. Sie haben dort ein sehr beeindruckendes Lager aufgebaut und sind bis an die Zähne bewaffnet.\nSieht so aus, als wären sie ehemalige Militärs und kennen ihr Geschäft gut. Sie lassen niemanden auf ihr Territorium. Sie sagen, dass die Spanier dort früher Gold abgebaut haben. Aber das Gold war erschöpft und sie haben die Mine aufgegeben. Ich habe keine Ahnung, was diese Bastarde dort machen.";
			link.l1 = "Nun, da niemand Hawk's Leiche gesehen hat, besteht weiterhin die Hoffnung, ihn lebend zu finden. Gott weiß, wir könnten ihn sogar wieder in den Baronstand zurückversetzen.";
			link.l1.go = "baron_return_5";
		break;
		
		case "baron_return_5":
			dialog.text = "Ja, wie wäre es damit. Hier, nimm diesen Brief. Wenn du Steve Dodson triffst, gib ihn ihm sofort. Der Inhalt dieses Briefes garantiert deine Sicherheit. Nun, nur für den Fall.";
			link.l1 = "Danke, Jan. Ich werde darauf achten, das zu tun!";
			link.l1.go = "baron_return_6";
		break;
		
		case "baron_return_6":
			DialogExit();
			GiveItem2Character(pchar, "letter_svenson");
			AddQuestRecord("BaronReturn", "1");
			pchar.questTemp.Saga.BaronReturn = "begin";
			pchar.quest.Saga_DannyMeeting.win_condition.l1 = "location";
			pchar.quest.Saga_DannyMeeting.win_condition.l1.location = "SantaCatalina_town";
			pchar.quest.Saga_DannyMeeting.function = "Saga_DannyMeeting";
		break;
		
		case "return_LSC":
			dialog.text = "Nun, warum das lange Gesicht. Bist du müde? Vielleicht ein Glas Rum für dich?";
			link.l1 = "Würde mir nichts ausmachen...";
			link.l1.go = "return_LSC_1";
		break;
		
		case "return_LSC_1":
			LAi_AlcoholSetDrunk(pchar, 51, 5600);
			dialog.text = "Hier, nimm ein Glas. Jetzt sprich.";
			link.l1 = "(trinkend) Ah, das ist viel besser... Nun, Jan, du und der Black Pastor hattet beide recht. Die Insel Justice Island existiert. Ich war dort.";
			link.l1.go = "return_LSC_2";
		break;
		
		case "return_LSC_2":
			dialog.text = "Ich habe dir gesagt, dass dort eine Schmugglerbasis sein sollte!";
			link.l1 = "Es gibt tatsächlich keine Basis irgendeiner Art. Und die Gerüchte in der Karibik haben nicht gelogen. Schwarze und Weiße leben wirklich zusammen dort, sicherlich nicht unbedingt in Frieden, sondern eher wie Katzen und Hunde. Und die Insel selbst besteht aus einer unzähligen Menge von Schiffswracks.";
			link.l1.go = "return_LSC_3";
		break;
		
		case "return_LSC_3":
			dialog.text = "Ich kann es nicht glauben! Jose Dios wird sich sicherlich sehr für deine Geschichte interessieren, da bin ich mir sicher. Besuch ihn übrigens eines Tages.";
			link.l1 = "Ich werde ihn später besuchen. Jetzt ist nicht die beste Zeit dafür. Ich habe im Moment dringendere Angelegenheiten zu erledigen. Ich habe Nathaniel Hawk auf Justice Island gefunden.";
			link.l1.go = "return_LSC_4";
		break;
		
		case "return_LSC_4":
			dialog.text = "Du hast Nathaniel gefunden? Das ist bemerkenswert! Wie geht es ihm?";
			link.l1 = "Nun... Er ist krank, ständig betrunken und tief deprimiert.";
			link.l1.go = "return_LSC_5";
		break;
		
		case "return_LSC_5":
			dialog.text = "Verdammt noch mal, das ist entmutigend. Wo ist er? Auf deinem Schiff?";
			link.l1 = "Nein, er ist auf seinem eigenen Schiff. Auf der Insel.";
			link.l1.go = "return_LSC_6";
		break;
		
		case "return_LSC_6":
			dialog.text = "Was, du hast ihn nicht hierher gebracht? Warum?";
			link.l1 = "Weil es nichts gab, mit dem ich ihn aufnehmen konnte. Ich habe mich ohne Schiff zur Insel durchgeschlagen.";
			link.l1.go = "return_LSC_7";
		break;
		
		case "return_LSC_7":
			dialog.text = "Verdammt noch mal, "+pchar.name+", du hast kaum ein Glas Rum getrunken und redest Unsinn, als hättest du dich ins Delirium getrunken. Was, bist du durch die Karibik geschwommen? Oder hast du dir einige Schildkröten an die Füße gebunden?";
			link.l1 = "Nein, ich bin nicht geschwommen. Jan, ich bin direkt aus dem Dschungel von Main auf die Insel gekommen, genau wie Nathan, durch einen magischen Indianeridol. Ich habe diese Geschichte schon so vielen Leuten erzählt und ich bin es leid zu beweisen, dass ich nicht verrückt geworden bin, also alles was ich zu sagen habe ist: glaubt mir einfach, in Ordnung!?";
			link.l1.go = "return_LSC_8";
		break;
		
		case "return_LSC_8":
			dialog.text = "Indisches Idol?";
			link.l1 = "Es gibt mindestens drei Idole in der Karibik, die als die Kukulcan-Statuen bekannt sind: eine in der Nähe des Miskito-Dorfes West Main, eine auf dem Grund der flachen Gewässer der Insel der Gerechtigkeit und eine weitere im Karib-Dorf Dominica. Diese Idole sind mit Hilfe der indianischen Magie in der Lage, Menschen augenblicklich durch Zeit und Raum zu transportieren.";
			link.l1.go = "return_LSC_9";
		break;
		
		case "return_LSC_9":
			dialog.text = "";
			link.l1 = "Ich bin durch alle drei Statuen in einem Kreis gegangen und bin genau dort herausgekommen, wo ich meine Reise im Miskito-Dorf begonnen habe. Wenn du mir nicht glaubst, kann ich Danielle rufen. Sie hat alles mit eigenen Augen gesehen!";
			link.l1.go = "return_LSC_10";
		break;
		
		case "return_LSC_10":
			dialog.text = "Danielle? Die Frau von Hawk? Sie war bei dir?";
			link.l1 = "Teilweise ja. Sie hat mich selbst in Blueweld gefunden und mich ins Miskito-Dorf gebracht, zu einem Schamanen, der mich zur magischen Statue schickte. Jetzt dient sie vorübergehend als einer meiner Offiziere, natürlich nur vorübergehend.";
			link.l1.go = "return_LSC_11";
		break;
		
		case "return_LSC_11":
			dialog.text = "Ich bin absolut verblüfft, "+pchar.name+"! Es ist genau so, wie die Engländer sagen. Du wurdest mit einem silbernen Löffel im Mund geboren. Du bist ein verdammt glücklicher Sohn einer Hündin! Gut, ich werde dir einfach glauben, obwohl es schwer fällt. Aber die Sache mit Nathan bleibt die gleiche, ihm muss geholfen werden.";
			link.l1 = "Das ist es, was ich vorhabe. Ich bereite eine Expedition zu Justice Island vor. Jetzt habe ich alles, was ich brauche: die Koordinaten der Insel und die Segelanweisungen.";
			link.l1.go = "return_LSC_12";
		break;
		
		case "return_LSC_12":
			dialog.text = "Fabelhaft. Kann ich Ihnen irgendwie helfen?";
			link.l1 = "Nein, danke. Aber ich habe ein kleines Detail weggelassen. Außer Nathan habe ich auch Shark Dodson auf der Insel gefunden.";
			link.l1.go = "return_LSC_13";
		break;
		
		case "return_LSC_13":
			dialog.text = "Also, er ist wirklich dorthin gegangen! Nun, "+pchar.name+", Du hast hervorragende Arbeit geleistet. Wie geht es Dodson dort drüben? Du hast natürlich mit ihm gesprochen, nicht wahr?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				link.l1 = "Ich habe nicht nur mit ihm geredet. Wir sind auch Freunde geworden. Er hat mir die Segelanweisungen gegeben, die ich brauche, um zur Insel zurückzukehren. Steven hat zugestimmt, die Kabine seines Kriegsschiffes gegen die Residenz von Sharptown zu tauschen.";
				link.l1.go = "return_LSC_14";
			}
			else
			{
				link.l1 = "Wir haben gesprochen, ja, aber am Ende stellte es sich als nutzlos heraus. Steven wurde getötet, während ich auf der Insel war, als eine Verschwörung, die von seinem Bootsmann, Chad Kapper, organisiert wurde, in Aktion trat.";
				link.l1.go = "return_LSC_17";
			}
		break;
		
		case "return_LSC_14":
			dialog.text = "Hah! Und wie hat es Shark geschafft, Kapitän eines Kriegsschiffes zu werden?";
			link.l1 = "Das Schiff ist seit über einem halben Jahrhundert in einer nie endenden 'Stille' gefangen. Er ist mit seinen Leuten auf der Insel gefangen. Deshalb hat er sich so lange nicht in der Karibik gezeigt. Wie auch immer, ich werde ihn bald hierher bringen und er wird Ihnen selbst von seinen Abenteuern erzählen.";
			link.l1.go = "return_LSC_15";
		break;
		
		case "return_LSC_15":
			dialog.text = "Ich kann es kaum erwarten! Jetzt wird alles besser. Wir sind gerade mächtiger geworden, "+pchar.name+". Wann planst du, zur Insel zurückzukehren?";
			link.l1 = "Gerade jetzt. Ich bin nur für eine Minute hierher gekommen, um dir von den Neuigkeiten zu erzählen, während Danielle die Vorbereitungen für die Expedition trifft. Sie stirbt vor Sehnsucht, ihren Nathan zu sehen. Und weißt du was, Jan, sie ist nicht so eine Schlampe.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_16":
			dialog.text = "Ja? Nun, vielleicht lag ich mit ihr nicht ganz richtig. Gut, "+pchar.name+", Ich werde dich nicht länger aufhalten. Geh und möge das Glück mit dir sein! Ich freue mich auf deine Rückkehr.";
			link.l1 = "Bis dann, Jan.";
			link.l1.go = "return_LSC_19";
		break;
		
		case "return_LSC_17":
			dialog.text = "Chad Kapper? Verdammt, ich kannte diesen Kerl. Er hat Steven getötet? Dieser Bastard...";
			link.l1 = "Kapper ist tot. Aber wir können Steven nicht zurückbringen, also müssen wir einen Weg finden, unsere Politik weiter zu organisieren.";
			link.l1.go = "return_LSC_18";
		break;
		
		case "return_LSC_18":
			dialog.text = "Hah! Das ist zu schade... Was gibt es da zu überlegen? Wir müssen einfach Tyrex überzeugen, die Bruderschaft zu leiten. Außerdem ist Tyrex nach Blaze als Hüter des Kodex unsere respektabelste Figur. Aber zuerst müssen wir Hawk zurückbringen, um wenigstens ein Ass im Ärmel zu haben. Wann brichst du nach Justice Island auf?";
			link.l1 = "Gerade jetzt. Ich bin nur kurz hierher gekommen, um dir von den Neuigkeiten zu erzählen, während Danielle die Vorbereitungen für die Expedition trifft. Sie kann es kaum erwarten, ihren Nathan zu sehen. Und weißt du was, Jan, sie ist nicht so eine Schlampe.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_19":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "return_LSC";
			// LSC ждёт своего героя!
			i = FindIsland("LostShipsCity");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			pchar.quest.return_LSC.win_condition.l1 = "location";
			pchar.quest.return_LSC.win_condition.l1.location = "LostShipsCity";
			pchar.quest.return_LSC.function = "LSC_ReturnCheckShips"; // проверка типов кораблей
			pchar.quest.return_LSC_attack.win_condition.l1 = "location";
			pchar.quest.return_LSC_attack.win_condition.l1.location = "Beliz";
			pchar.quest.return_LSC_attack.function = "LSC_ReturnJackmanAttack"; // атака наймитов Джекмана
			pchar.quest.return_LSC_main.win_condition.l1 = "Ship_location";
			pchar.quest.return_LSC_main.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.return_LSC_main.function = "LSC_ReturnMain"; // основная функция возвращения
		break;
		
		case "nathaniel":
			dialog.text = "Wie geht es ihm? Du hast gesagt, dass er sich nicht gut fühlt.";
			link.l1 = "Ja, genau das ist richtig. Ich werde ihn mitnehmen, um ihn im Miskito-Dorf von Snake Eye, dem Schamanen, behandeln zu lassen.";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "Dann keine Zeit zu verschwenden! Beeil dich, "+pchar.name+"! Sobald du Nathan zu deinem Schamanen bringst, komm sofort zu mir zurück.";
			link.l1 = "In Ordnung, Jan. Klingt nach einem Plan.";
			link.l1.go = "exit";
			npchar.quest.shamane = "true";
		break;
		
		case "nathaniel_2":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				if (CheckAttribute(npchar, "quest.shark")) //и на месте
				{
					dialog.text = "Sehr gut. Steven ist bereits vorbeigekommen, um mich zu sehen. Jetzt können wir endlich unsere Pläne weiter besprechen.";
					link.l1 = "Ich bin ganz Ohr, Jan.";
					link.l1.go = "barbazon";
				}
				else
				{
					dialog.text = "Das ist natürlich nett, aber warum ist Dodson noch nicht bei mir vorbeigekommen? Was, hast du ihn auf der Insel gelassen?";
					link.l1 = "Hm... Ich war in Eile, Nathan zu Snake Eye zu bringen...";
					link.l1.go = "nathaniel_wait";
				}
			}
			else
			{
				dialog.text = "Sehr gut. Mein Herz weint um Shark. Aber so ist das Leben, also wird Tyrex seinen Platz einnehmen. Nun können wir endlich unsere Pläne weiter besprechen.";
				link.l1 = "Ich höre, Jan.";
				link.l1.go = "barbazon";
			}
		break;
		
		case "nathaniel_wait":
			dialog.text = "... und du hast vergessen, Shark mitzunehmen? Ich kann es nicht glauben, "+pchar.name+"! Übergebe Steven jetzt an Blueweld! Hörst du mich? Geh!";
			link.l1 = "Beruhige dich, Jan. Ich kümmere mich um alles.";
			link.l1.go = "exit";
			NextDiag.TempNode = "nathaniel_wait_1";
		break;
		
		case "nathaniel_wait_1":
			if (CheckAttribute(npchar, "quest.shark"))
			{
				dialog.text = "Steven kam vorbei, um mich zu sehen. Jetzt können wir endlich unsere Pläne weiter besprechen.";
				link.l1 = "Ich höre zu, Jan.";
				link.l1.go = "barbazon";
			}
			else
			{
				dialog.text = "Oh, "+pchar.name+"... Es scheint mir, dass du in letzter Zeit zu viel Rum getrunken hast. Siehst du, es endet nie gut. Zuerst fangen deine Hände an zu zittern, dann verlierst du dein Gedächtnis und dann bekommst du einen schwarzen Fleck...";
				link.l1 = "Ich habe verstanden, Jan. Ich gehe sofort los, um Steven zu holen!";
				link.l1.go = "exit";
				NextDiag.TempNode = "nathaniel_wait_1";
			}
		break;
		
		case "barbazon":
			dialog.text = "Der Black Pastor war sehr deutlich, er interessiert sich nur für dieses theologische Buch. Ich habe meine Männer losgeschickt, um danach zu suchen, vielleicht wird jemand es finden. Marcus Tyrex ist kein Problem, wir werden keine Schwierigkeiten haben, ihn zu überzeugen. Jackman hat Maroon Town kurz nach deinem Besuch verlassen. Er segelte irgendwo auf der 'Centurion', der Fregatte von Hawk.\nEs bleibt nur noch Barbazon - er ist auch bekannt als Jacques Kindman. Wir müssen einen Weg finden, ihn zur Zusammenarbeit zu bewegen. Ich bin mir noch nicht sicher, wie das gehen soll. Aber eines ist offensichtlich - du solltest ihn besuchen.";
			link.l1 = "Erzähl mir über Barbazon."; // Addon 2016-1 Jason пиратская линейка патч 17/1
			link.l1.go = "barbazon_1";
		break;
		
		case "barbazon_1":
			dialog.text = "Heimlichtuer. Tut so, als wäre er arm, doch er ist möglicherweise der reichste Mann in der Karibik. Er kontrolliert alle Schmuggeloperationen des Ostens. Wäre Marcus nicht gegen ihn, würde er den gesamten Schmuggelverkehr auf den Inseln unter dem Winde beherrschen. Tyrex ist wie ein Knochen in seinem Hals.\nSie streiten sich immer im Rat, aber Barbazon hat nicht den Mumm, einen offenen Krieg zu erklären. Vielleicht war er wirklich einmal ein Pirat von Dunkirk, wie er behauptet, aber jetzt erinnert er mich mehr an einen Wucherer.";
			link.l1 = "Wie zur Hölle wurde er zum Baron gewählt?";
			link.l1.go = "barbazon_2";
		break;
		
		case "barbazon_2":
			dialog.text = "Gold, mein Freund, regiert alles und überall, wer das Gold hat, macht die Regeln. Außerdem ist Barbazon sehr gut darin, sich alle möglichen profitablen und illegalen Operationen auszudenken. Er nimmt selbst nicht daran teil, aber er bekommt immer einen Anteil. Deshalb hat er ständig eine Menge tapferer Schläger, die meistens schwach im Kopf sind, um sich. Ohne ihn würden sie alle einfach verhungern oder am Galgen enden.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				link.l1 = "Er erinnert mich an Marcus... Jan, die Sache ist... Ich habe keine Ahnung, wie ich Barbazon ansprechen soll. Es gibt ein Problem, von dem du nichts weißt.";
				link.l1.go = "barbazon_5";
			}
			else
			{
				link.l1 = "Wie komme ich nach Barbazon?";
				link.l1.go = "barbazon_3";
			}
		break;
		
		case "barbazon_3":
			dialog.text = "Tu einfach so, als wärst du einer dieser Tölpel, die einen Tipp für einen fetten Job brauchen. Denke nicht einmal daran, ihn bei seinem Anteil zu täuschen. Der gütige Barbazon vergibt nicht.";
			link.l1 = "Das versteht sich von selbst. Ich mische mich nicht für meinen eigenen Gewinn mit ihm ein. Wie auch immer, es ist Zeit, ihn zu besuchen.";
			link.l1.go = "barbazon_4";
		break;
		
		case "barbazon_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "1");
			pchar.questTemp.Saga.BarbTemptation = "begin";
			pchar.questTemp.Saga.BaronReturn = "barbazon";
			NextDiag.CurrentNode = "First time";
			// тут вычищаем квестовый мусор от LSC
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
			if (CheckCharacterItem(pchar, "letter_chad_1")) RemoveItems(pchar, "letter_chad_1", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "barbazon_5":
			dialog.text = "Wirklich? Was ist es?";
			link.l1 = "Hast du jemals von Charlie Prince gehört?"; 
			link.l1.go = "barbazon_6";
		break;
		
		case "barbazon_6":
			dialog.text = "Ja, ich habe die Gerüchte gehört. Dieser Kerl hat nicht allzu lange für Marcus Tyrex gearbeitet. Hat in sehr kurzer Zeit viel getan, hat sich einen Namen gemacht, indem er Cartagena geplündert hat. Na und?";
			link.l1 = "Dieser Kerl bin ich. Ich bin Charlie Prince. Ich war es. Siehst du jetzt?"; 
			link.l1.go = "barbazon_7";
		break;
		
		case "barbazon_7":
			dialog.text = "Verdammt nochmal! Du bist Charlie Prince? Was für eine Wendung! "+pchar.name+", ich bin beeindruckt! Jetzt sehe ich, woher dein Griff stammt... Aber was hat Barbazon damit zu tun?";
			link.l1 = "Wie wäre es, wenn Charlie Prince Barbazon einen Besuch abstatten würde, Jan?.."; 
			link.l1.go = "barbazon_8";
		break;
		
		case "barbazon_8":
			dialog.text = "Hm... Ich verstehe. Sie hatten schon mal mit ihm zu tun?";
			link.l1 = "Nicht ganz. Einer seiner Schergen namens Ignacio Marco versuchte, mich nach direkten Befehlen von Barbazon zu erledigen. Es war Teil ihres kleinen Krieges."; 
			link.l1.go = "barbazon_9";
		break;
		
		case "barbazon_9":
			dialog.text = "Hat er dein Gesicht gesehen? Hast du dich ihm vorgestellt?";
			link.l1 = "Nein."; 
			link.l1.go = "barbazon_10";
		break;
		
		case "barbazon_10":
			dialog.text = "Sehe hier kein Problem. Ich habe auch vom Korsaren Charlie Prince gehört, aber ich wusste nicht, dass Sie es waren, bevor Sie es mir gesagt haben.";
			link.l1 = "Glaubst du, Barbazon wird mich nicht durchschauen?"; 
			link.l1.go = "barbazon_11";
		break;
		
		case "barbazon_11":
			dialog.text = "Wie könnte er, wenn er dein Gesicht nie gesehen hat? Alles, was er tat, war Befehle zu geben, um einen der Mitarbeiter von Marcus loszuwerden.";
			link.l1 = "Hm... Du könntest recht haben."; 
			link.l1.go = "barbazon_12";
		break;
		
		case "barbazon_12":
			dialog.text = "Wir schaffen das nicht ohne Barbazon. Geh und sieh ihn an, aber sei vorsichtig. Lauf weg, wenn er dich erkennt, in diesem Fall werden wir uns einen anderen Weg einfallen lassen, um ihn zu konfrontieren.";
			link.l1 = "Gut. Ich sollte jetzt gehen. Ich freue mich darauf, das Miststück zu treffen."; 
			link.l1.go = "barbazon_13";
		break;
		
		case "barbazon_13":
			dialog.text = "Spiel nicht den Dummen und versuch nicht, Jacques zu verarschen. Er vergibt nie. Verhalte dich wie ein Idiot, der darauf aus ist, leichtes Geld zu machen.";
			link.l1 = "Meine bevorzugte Rolle, wie es scheint... Leb wohl, Jan!"; 
			link.l1.go = "barbazon_4";
		break;
		
		case "saga_26":
			dialog.text = "Ja. Der indische Schamane hat alles gegeben, Hawk ist so gut wie neu. Er sollte bereits mit Dannie in Maroon Town sein, also wenn du willst, geh ruhig vor und sag hallo. Sie würden sich freuen, dich zu sehen.";
			link.l1 = "Ich werde auf jeden Fall vorbeischauen, um zu sehen, wie es ihnen geht... Jan, ich habe den zweiten Teil von Sharps Karte gefunden! Es war in Jackmans Hütte. Jetzt werden wir keine Probleme haben, Helens Rechte an Isla Tesoro zu beweisen.";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			dialog.text = "Großartig, zeig mir es.\nWir hatten recht, Jacob war es, der Blaze getötet hat. Nun soll der Fleck auf Sharks Namen endgültig entfernt werden. Was den Beweis betrifft, so ist das eine heiklere Angelegenheit. Und sie muss erst nach sehr gründlicher Überlegung angegangen werden.";
			link.l1 = "Noch etwas, Jan. Schaue dir diesen Zettel an. Er war auch unter Jackmans Sachen.";
			link.l1.go = "saga_28";
		break;
		
		case "saga_28":
			RemoveItems(pchar, "letter_parol", 1); // удалить записку
			dialog.text = "Nun, lass uns mal sehen... Ha, also deswegen haben die Banditen auf Jackman gehört und aufgehört, Miskitos zu entführen! Es konnte nicht anders kommen! Dieser Schuft hat alles geplant und war immer einen Schritt voraus.";
			link.l1 = "Ja, und ich kann auch sehen, warum die Männer von Hawk abgeschlachtet wurden. Aber es gibt zwei Dinge, die ich nicht verstehe: erstens, was machen die Komplizen von Jackman in der Mine und zweitens, warum reagierst du so gelassen auf die Tatsache, dass dieses ganze Durcheinander auf deinem Territorium stattfindet?";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "Ich schäme mich... Du hast recht. Jackman ist wirklich aus der Kontrolle geraten. Und seine Handlanger haben in meinem Bereich nichts zu suchen. Es scheint, als wäre die Zeit gekommen, der Karibik zu zeigen, mit wem sie es zu tun haben.";
			link.l1 = "Was hast du vor, Jan?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_30":
			dialog.text = "Wiederbelebung der Vergangenheit... Ich beabsichtige, eine Strafexpedition zu organisieren und jeden Banditen in den Minen auszulöschen. Jetzt haben wir Beweise, dass sie Jackmans Männer sind und ich bin verpflichtet, meine Territorien von diesem Abschaum zu säubern.\n"+pchar.name+", du hast hervorragende Arbeit geleistet. Es ist Zeit für mich, meinen Hintern in Bewegung zu setzen. Du sollst dich jetzt ausruhen. Geh und besuche Hawk. Komm in zehn Tagen zurück!";
			link.l1 = "Gut, Jan. Werde ich tun. Ich komme genau zu der Zeit zurück, die du gesagt hast!";
			link.l1.go = "saga_31";
			link.l2 = "Ha! Ich möchte auch an diesem Kreuzzug teilnehmen. Warum hast du dich entschieden, mich in die Erholungszeit zu stecken?";
			link.l2.go = "saga_31_1";
		break;
		
		case "saga_31_1":
			dialog.text = "Verzeih mir, alter Kamerad. Ich dachte nur, es könnte endlich Zeit für mich sein, etwas Arbeit zu leisten und dir etwas Ruhe zu gönnen. Aber wenn es dein Wunsch ist, wäre ich mehr als glücklich! Lass uns zusammen in den Sturm ziehen! Und alles, was wir in der Mine finden, teilen wir gleichmäßig unter unseren Mannschaften auf, wie es in den Gesetzen der Bruderschaft geschrieben steht.";
			link.l1 = "Abgemacht, Jan! Wann brechen wir auf?";
			link.l1.go = "saga_31_2";
		break;
		
		case "saga_31_2":
			dialog.text = "Komm in drei Tagen mit deinen Leuten zur Moskitoküste. Bis dahin werde ich meine Mannschaft versammelt haben und werde bereits auf dich warten. Komm nicht zu spät!";
			link.l1 = "In Ordnung, Forest Devil. Ich kann es kaum erwarten, mit dir Rücken an Rücken in die Schlacht zu ziehen! Bis bald!";
			link.l1.go = "saga_31";
			npchar.quest.mine_tw = "true";
		break;
		
		case "saga_31": 
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if (CheckAttribute(npchar, "quest.mine_tw"))
			{
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1 = "location";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1.location = "Shore53";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2 = "Timer";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.hour  = sti(GetTime());
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.function = "Saga_MineBanditsPrepareAttack";
				SetFunctionTimerCondition("Saga_MineBanditsAttackOver", 0, 0, 4, false); // таймер
			}
			else SetFunctionTimerCondition("Saga_MineBanditsDestroyed", 0, 0, 10, false); // таймер
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
		break;
		
		case "saga_32a":
			dialog.text = "Ausgezeichnet. Ich habe etwas über den geheimnisvollen Besitzer der Mine, Lawrence Beltrope, herausgefunden.";
			link.l1 = "Also, wer ist dieser Vogel?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_32":
			dialog.text = "Ich habe Jackmans Handlanger in der Mine besiegt. Sie erwiesen sich als harte Nüsse, aber meine Leute sind auch nicht von gestern. Darüber hinaus konnten wir ihre Wachsamkeit senken, nachdem wir ihnen das Passwort aus der Notiz, die du gefunden hast, mitgeteilt haben. Wir drangen in die Mine ein und haben ihnen einen spektakulären Abschied bereitet.";
			link.l1 = "Du hast die Mine eingenommen? Hervorragend!";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "Lass das eine Lektion für jeden sein, der denkt, dass der Forest Devil rostig ist. Ich habe in den letzten Jahren wirklich zu viel herumgelungert und was ist passiert? Jackman hat seinen bösen Plan direkt unter meiner Nase ausgebreitet!";
			link.l1 = "Was hast du in dieser Mine gesehen? Erzähl mir davon!";
			link.l1.go = "saga_34";
		break;
		
		case "saga_34":
			dialog.text = "Die Mine wurde tatsächlich von den Spaniern aufgegeben, jedoch hat Lawrence Beltrope aus Port Royal sie für einen Apfel und ein Ei gekauft und heimlich den Abbau fortgesetzt. Anscheinend haben die Spanier den Schacht zu früh aufgegeben, denn obwohl wir selbst kein Gold gefunden haben, trafen wir auf mehrere Sklaven, die behaupteten, dass dort bis vor kurzem noch Gold zu finden war.";
			link.l1 = "Lawrence Beltrope? Noch nie von ihm gehört. Wer ist er?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_35":
			dialog.text = "Er ist ein Einheimischer, der Sohn von Thomas Beltrope, vor langer Zeit der Schwurbruder von Nicholas Sharp und der Freibeuter der Providence Island Company. Ich kannte Thomas selbst sehr gut. Vor einem Jahr kam Lawrence wieder in die Karibik. Es stellt sich heraus, dass Jackman für ihn gearbeitet hat. Behalte das im Kopf und halte deine Augen offen!";
			link.l1 = "So Jackmans geheimnisvoller 'Chef', der in diesem Brief erwähnt wurde, ist Lawrence Beltrope... Gut, ich werde mir diesen Namen merken.";
			link.l1.go = "saga_36";
		break;
		
		case "saga_36":
			dialog.text = "Noch eine Sache. Mir fällt etwas Seltsames ein. Blaze erwähnte einmal eine verlassene spanische Goldmine und dass er ihr Gold in Sharptown investieren wollte. Aber die Karte der Mine verschwand, nachdem seine Schwester mit Kapitän Butcher weggelaufen war. Vielleicht sprach er von unserer Mine? \nEgal, das war vor zu langer Zeit und ändert nicht viel ... Du und ich sollten uns um den Rat kümmern. Hast du alle fünf Splitter?";
			link.l1 = "Ja. Diese vier: Nathaniel, Tyrex, Marlow und Barbazon. Alle haben ihr Ja gegeben.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			sTemp = "Shark";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			dialog.text = "Großartig. Ich bin sicher, es wird keine Probleme bei der Wahl geben "+sTemp+" als Anführer der Bruderschaft der Küste. Ich werde sofort daran arbeiten, eine Ratsversammlung einzuberufen.";
			link.l1 = "Also Jan, können wir nun alle Probleme als gelöst betrachten? Nathaniel ist in Maroon Town, Jackman ist tot und die Brüderlichkeit hat nun einen neuen Anführer... Vielleicht ist es an der Zeit, dorthin zurückzukehren, wo wir angefangen haben, nämlich nach Tortuga?";
			link.l1.go = "saga_38";
		break;
		
		case "saga_38":
			dialog.text = "Ich erinnere mich, "+pchar.name+", aber wir müssen noch etwas abwarten. Außerdem läuft die Zeit, um Sharp's Erbschaft zu klären, ab und diese Angelegenheit, wie Sie wissen, muss ernsthaft angegangen werden.";
			link.l1 = "Was ist mit dem Erbe los? Ich habe beide Teile der Karte. Alles, was wir wirklich tun müssen, ist sie vorzulegen und das war's...";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = ""+pchar.name+", Ich versichere Ihnen, dass sie heutzutage Inseln nicht einfach so an Leute verschenken. Selbst an die rechtmäßigen Erben, bei denen jeder Paragraph des Testaments erfüllt ist. Die englischen Behörden wollen diese Insel unbedingt, das ist mir wohl bewusst.\nIch glaube nicht, dass Oberst Doyle tatenlos zuschauen wird, wie wir ihm die Insel wegnehmen, die er bereits als englisches Eigentum ansieht. Außerdem sollten Sie und ich im Verborgenen bleiben.";
			link.l1 = "Und was schlägst du vor?";
			link.l1.go = "saga_40";
		break;
		
		case "saga_40":
			dialog.text = "Mach dich auf den Weg nach Port Royal und finde dort einen Mann namens Albert Loxley. Er ist der beste Anwalt in der gesamten Karibik. Er hat eine beachtliche Fähigkeit in zwielichtigen Angelegenheiten aller Art entwickelt, also wird er jede Art von Arbeit annehmen, wenn ihm dafür ein exorbitantes Honorar geboten wird. Er hat einen königlichen Appetit, aber er ist es wert.";
			link.l1 = "Denkst du, Sharps Testament könnte einige Fallstricke enthalten?";
			link.l1.go = "saga_41";
		break;
		
		case "saga_41":
			dialog.text = "Ich denke nicht nur so, ich bin mir sicher. Hast du jemals Geschäfte mit Beamten machen müssen? Weißt du, dass wenn sie etwas von dir wollen, sie dir die Seele herausreißen, deine Nase auf ein fehlplatziertes Komma richten, alles so interpretieren, wie sie es brauchen und dich so nackt wie ein blindes Kätzchen hinterlassen.\nDeshalb wurden Anwälte geschaffen. Sie bekämpfen die Beamten mit ihren eigenen Waffen - dem Geschwätz, dem verschütteten Tintenfass und der Arglist. Daher solltest du Loxley einen Besuch abstatten und ihn engagieren, um unsere Interessen zu schützen, während ich mich um die Wahlen kümmere.";
			link.l1 = "In Ordnung. Ich gehe nach Port Royal. Wie lange wird es dauern, bis der Rat sich trifft und eine Wahl abhält?";
			link.l1.go = "saga_42";
		break;
		
		case "saga_42":
			dialog.text = "Zehn Tage. Also bemühe dich nicht, mich früher in Blueweld zu suchen.";
			link.l1 = "Verstanden. Nun, Jan. In diesem Fall, bis später!";
			link.l1.go = "saga_43";
		break;
		
		case "saga_43":
			DialogExit();
			AddQuestRecord("Testament", "1");
			pchar.questTemp.Saga = "loxly"; // обновляем флаг
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			SetFunctionTimerCondition("Saga_GoldForLoxly", 0, 0, 10, false); // таймер
		break;
		
		case "saga_44":
			sTemp = "Steven Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = ""+sTemp+" sendet seine herzlichsten Grüße. Er wird sich immer freuen, dich in seiner Residenz auf Isla Tesoro zu sehen. Besuch ihn, wenn sich die Gelegenheit ergibt.";
			link.l1 = " Um sicherzustellen dass "+sTemp+" seine neue Residenz nicht verlassen wird, haben du und ich, Jan, noch ein bisschen Arbeit vor uns.";
			link.l1.go = "saga_45";
		break;
		
		case "saga_45":
			sTemp = "Vierhundertfünfzig";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "Eintausend";
			dialog.text = "Ich nehme an, du hast Loxley bereits besucht...";
			link.l1 = "Ja, habe ich. Er übernimmt unseren Fall, aber er verlangte einen Haufen Gold für seine Dienste. "+sTemp+" Dublonen im Voraus. Voraus! Und wir müssen ihm auch noch mehr bezahlen, je nachdem, wie gut Helens Nachweis der Rechte verläuft. Die Summe wird sich verdoppeln oder verdreifachen, wie er sagte.";
			link.l1.go = "saga_46";
		break;
		
		case "saga_46":
			dialog.text = "Ha! Nun, ich habe nichts weniger von einem alten Taktiker wie ihm erwartet. Er riecht Beute von weitem, genau wie eine Hyäne. Natürlich sprechen wir hier von einer ganzen Insel. Es ist lächerlich zu denken, dass Albert nicht ein paar hundert verlangen würde. Also könnte die Gesamtsumme irgendwo bei tausendfünfhundert Gold liegen ...";
			link.l1 = "Jan, das ist ein Haufen Geld!";
			link.l1.go = "saga_47";
		break;
		
		case "saga_47":
			dialog.text = "Ich verstehe, worauf du hinauswillst. Ich stimme dir zu, du bist kein dummes Gorillatier, das alles aus eigener Tasche zahlt. Aber leider habe ich im Moment nicht so viel Gold zur Hand. Ich hatte solche Ausgaben geplant, jedoch hat das Eingreifen eines Schurken alles ruiniert.";
			link.l1 = "Wovon redest du?";
			link.l1.go = "saga_48";
		break;
		
		case "saga_48":
			dialog.text = "Hör zu. Vielleicht weißt du bereits, dass unsere Siedlung nur halb legal ist. Die Engländer halten hier eine Garnison und wir liefern ihnen Mahagoni zu einem guten Preis. Aber es gibt eine sehr schwere und haltbare Art von Holz - Lignum Vitae, das du als Eisenholz kennen sollten.\nEs ist selten und schwer zu verarbeiten, selbst mit gehärtetem Stahl. Sie sagen, dass die Maya-Itza vor langer Zeit ihre schrecklichen Keulen daraus gemacht haben. Man kann Eisenholz nicht auf dem offenen Markt kaufen und geschmuggelt kostet es sein Gewicht in Silber.\nDoyle's Männer kommen gelegentlich und kaufen die gesamte Menge, die wir verarbeitet haben, für billig. Aber ich schaffe es immer, etwas für meinen eigenen Bedarf zu retten.";
			link.l1 = "Ich habe von diesem Baum gehört. Man sagt, dass Musketenkugeln in sein öliges Holz wie Teer versinken! Seine Robustheit ist gut genug, um Zahnräder für Stahlmechanismen daraus zu machen.";
			link.l1.go = "saga_49";
		break;
		
		case "saga_49":
			dialog.text = "Du übertreibst ein wenig über die Zahnräder, aber der Rest stimmt genau. Also, um die Kosten vorherzusagen, habe ich eine große Menge Eisenholz vorbereitet, aber irgendein Schuft hat mein Lagerhaus vor ein paar Tagen ausgeräumt. Es ist einer von uns, das weiß ich. Ich habe einen Verdacht, kann aber nichts Genaues sagen.";
			link.l1 = "Ratten sollen zertreten werden! Wen vermutest du?";
			link.l1.go = "saga_50";
		break;
		
		case "saga_50":
			dialog.text = "Paul Molligan. Sein Ostindischer 'Oyster' segelte gestern nach Barbados. Ich hatte keine Chance, ihre Laderäume zu kontrollieren. Aber er würde das Eisenholz sowieso nicht nach Bridgetown bringen, Lord Willoughby hat dort ernsthafte Zollbeamte und Eisenholz ist ein Rohstoff von strategischer Bedeutung für die englische Marine.\nWenn er wirklich mein Eisenholz hat, dann wird er es verkaufen, bevor er in Bridgetown ankommt. Wenn du nur Molligan abfangen und seine Laderäume inspizieren könntest!..";
			link.l1 = "Du sagst, er ist gestern nach Bridgetown aufgebrochen? Noch ist nicht alles verloren. Ich werde versuchen, ihn einzuholen.";
			link.l1.go = "saga_51";
		break;
		
		case "saga_51":
			dialog.text = "Du weißt, was zu tun ist, wenn Molligan die Ratte ist. Aber versuche zuerst den Namen seines Auftraggebers herauszufinden. Dann kannst du die Ladung entweder selbst zum Auftraggeber bringen oder sie mir zurückgeben.\nBring auch die 'Auster' nach Blueweld, das ist ein feines Schiff, ich würde es gerne für mich selbst nehmen und es für meine eigenen Bedürfnisse umrüsten. Du darfst auch nehmen, was du als Preis willst... Und falls Molligan nicht der Schuldige ist... nein, ich bin sicher, dass er die Ratte ist, die mein Eisenholz gestohlen hat.";
			link.l1 = "Ich werde meine Zeit gut nutzen!";
			link.l1.go = "saga_52";
		break;
		
		case "saga_52":
			dialog.text = "Wenn du das Eisenholz selbst verkaufst, lege eintausendfünfhundert Gold-Dublonen für Loxley zur Seite und wir teilen den Rest halb und halb. Ich kann dir in dieser Angelegenheit vertrauen, oder?";
			link.l1 = "Natürlich. Ich bin keine Ratte.";
			link.l1.go = "saga_53";
		break;
		
		case "saga_53":
			dialog.text = "Ich habe keinen Zweifel. Viel Glück, "+pchar.name+"! Ich hoffe, es lächelt diesmal auf dich herab.";
			link.l1 = "Danke. Bis später!";
			link.l1.go = "saga_54";
		break;
		
		case "saga_54":
			DialogExit();
			pchar.questTemp.Saga = "molligan"; // обновляем флаг
			AddQuestRecord("Testament", "3");
			if(bImCasual) NewGameTip("Erkundungsmodus: Der Timer ist nicht deaktiviert. Halte die Frist ein!");
			Saga_CreateMolliganInWorld(); // ставим корабль Моллигана на карту
		break;
		
		case "saga_55":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "Ich wusste es. Wie viel hatte er in seinen Laderäumen?";
			link.l1 = "Ich habe "+FindRussianQtyString(sti(npchar.quest.bakaut))+" Stück auf der 'Auster' gefunden.";
			link.l1.go = "saga_56";
		break;
		
		case "saga_56":
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp > 100)
			{
				dialog.text = "Wer hätte das gedacht! So viel hatte ich noch nie in meinem Lager. Schau mal, wer sich ein Vermögen gesichert hat. Danke, "+pchar.name+", du hast mich nie enttäuscht. Ich werde das Produkt sofort verkaufen, wir haben bereits einen Käufer. Morgen habe ich das Geld für dich.";
				link.l1 = "In Ordnung. Ich werde dich dann nicht weiter ablenken. Bis morgen.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 90 && iTemp < 101)
			{
				dialog.text = "Ja, ich habe gerade so viel gehabt. Kleine Ratte! Danke, "+pchar.name+", du hast mich nie enttäuscht. Ich werde das Produkt sofort verkaufen, wir haben bereits einen Käufer. Morgen habe ich das Geld für dich.";
				link.l1 = "In Ordnung. Ich werde dich dann nicht weiter ablenken. Bis morgen.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "Er hat wahrscheinlich schon einen Teil der Lieferung an jemanden verkauft, denn es hätte mehr sein sollen. Aber das ist nicht so schlimm, wir haben den größten Teil zurückbekommen. Danke, "+pchar.name+", Ich werde das Produkt sofort verkaufen, wir haben bereits einen Käufer. Morgen habe ich das Geld für dich.";
				link.l1 = "In Ordnung. Ich werde dich dann nicht weiter ablenken. Bis morgen.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 50 && iTemp < 70)
			{
				dialog.text = "Verdammt, dieser Bastard konnte bereits einen anständigen Anteil der Lieferung verkaufen... Ah, das ist zu schlecht. Na ja. Ich werde verkaufen, was ich habe, ich habe bereits einen Käufer. Das Geld werde ich morgen haben.";
				link.l1 = "In Ordnung. Dann werde ich dich nicht weiter ablenken. Bis morgen.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 20 && iTemp < 50)
			{
				dialog.text = "Verdammt noch mal, das ist verwerflich! Dieser Bastard hat es geschafft, mehr als die Hälfte der Lieferung schon zu verkaufen... Ach, das ist zu schade. Nun ja. Ich werde verkaufen, was ich habe, ich habe bereits einen Käufer gefunden. Morgen werde ich das Geld haben.";
				link.l1 = "In Ordnung. Ich werde dich dann nicht weiter ablenken. Bis morgen.";
				link.l1.go = "saga_oust";
				break;
			}
			dialog.text = "Mann, ich habe einfach kein Glück. Er hat fast alles verkauft... Hier, behalte dieses Eisenholz für dich, "+pchar.name+", mach damit, was du willst. Du bist meine einzige Hoffnung, jetzt etwas Geld zu verdienen.";
			link.l1 = "Verstanden. Gut, ich werde selbst nachsehen. Das ist nicht mein erster Rodeo... Tschüss, Jan.";
			link.l1.go = "saga_oust";
		break;
		
		case "saga_oust":
			if (CheckAttribute(npchar, "quest.bakaut"))
			{
				if (sti(npchar.quest.bakaut) < 20) DeleteAttribute(npchar, "quest.bakaut");
				else 
				{
					SaveCurrentNpcQuestDateParam(npchar, "bakaut_date");
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(npchar.quest.bakaut));
				}
				pchar.questTemp.Saga = "removebakaut";
			}
			int iUst = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_EASTINDIAMAN && sld.ship.name == "Oyster") iUst = 1;
				}
			} // есть ли у нас Устрица
			dialog.text = "Warte! Hast du die 'Auster' gefangen?";
			if (iUst == 1)
			{
				link.l1 = "Ja. Sie liegt gerade im Hafen. Ich habe sie für dich verankert, genau wie du es verlangt hast.";
				link.l1.go = "saga_oust_yes";
			}
			else
			{	
				link.l1 = "Nein. Das Schiff war nach der Schlacht so stark beschädigt, dass ich es versenken musste.";
				link.l1.go = "saga_oust_no";
			}
		break;
		
		case "saga_oust_no":
			dialog.text = "Wie schade. Aber es ist, wie es ist. Bis später, "+pchar.name+"!";
			link.l1 = "Auf Wiedersehen, Jan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_oust_yes":
			dialog.text = "Bemerkenswert! Ich werde diese Schönheit so aufriggen, wie sie es verdient. Und später kannst du sie immer für eine Weile ausleihen, genau wie wir es vereinbart haben. Ich denke, in etwa zwei Monaten wird sie bereit sein.";
			link.l1 = "Alles klar. Ein Schiff wie dieses könnte manchmal wirklich nützlich sein... Bis später, Jan!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_RemoveOuster");
			npchar.quest.ouster = "true";
			SaveCurrentNpcQuestDateParam(npchar, "ouster_date"); // через 2 месяца
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_57":
			int idlt;
			iTemp = sti(npchar.quest.bakaut)*30; // Ян за 1 шт бакаута даёт 30 дублонов
			if (iTemp > 1600)
			{
				idlt = makeint(iTemp-1500)/2; // доля Бонса :)
				dialog.text = "Ich habe "+iTemp+" Münzen dafür erhalten. Tausendfünfhundert sind für den Anwalt, plus dein Anteil an Dublonen - "+idlt+". Hier, bitte.";
				link.l1 = "Lobenswert! Jetzt kann ich leicht nach Loxley abheben.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500+idlt);
				break;
			}
			if (iTemp > 1450 && iTemp <= 1600)
			{
				dialog.text = "Ich habe dafür eintausendfünfhundert Dublonen erhalten. Das reicht gerade für den Anwalt. Bitte sehr.";
				link.l1 = "Fantastisch. Jetzt kann ich nach Loxley aufbrechen.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500);
				break;
			}
			dialog.text = "Ich habe "+iTemp+" Dublonen dafür erhalten. Hier, nimm sie. Den Rest wirst du selbst ausgraben müssen.";
			link.l1 = "Nun, wenn alleine dann alleine. Also gut, ich mache mich auf den Weg zu Loxley.";
			link.l1.go = "saga_58";
			TakeNItems(pchar, "gold_dublon", iTemp);
		break;
		
		case "saga_58":
			DialogExit();
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.bakaut");
		break;
		
		case "saga_59":
			dialog.text = "Wie wäre es damit? Das ist interessant. Und wie viel ist der Holländer bereit dafür zu zahlen?";
			link.l1 = "Vierzig Dublonen pro Stück.";
			link.l1.go = "saga_60";
		break;
		
		case "saga_60":
			dialog.text = "Whoa! Meine Käufer zahlen weniger...";
			link.l1 = "Insgesamt habe ich zweitausend Stück Gold für Loxley und "+sti(npchar.quest.bakaut_sum)*2+" Dublonen obendrauf.";
			link.l1.go = "saga_61";
		break;
		
		case "saga_61":
			dialog.text = "Sehr gut. Dann teilen wir es in der Mitte.";
			if (CheckCharacterItem(pchar, "gold_dublon"))
			{
				npchar.quest.bakaut_pay = GetCharacterItem(pchar, "gold_dublon"); // дублоны в кармане
				link.l1 = "Hier, bitte. Ich habe "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "Ich habe die Dublonen auf dem Schiff gelassen. Ich werde schnell rüberlaufen und gleich wieder da sein.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "saga_61_1":
			dialog.text = "Famos. Wie viel hast du mitgebracht?";
			if (CheckCharacterItem(pchar, "gold_dublon"))
			{
				npchar.quest.bakaut_pay = GetCharacterItem(pchar, "gold_dublon"); // дублоны в кармане
				link.l1 = "Hier, bitte. Ich habe "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "Was ist mit meinem Gedächtnis los! Es ist Zeit, mit diesem Rum aufzuhören. Schon wieder habe ich die Dublonen in meiner Truhe gelassen. Ich werde schnell dorthin laufen und sie holen.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay": // оплата
			if (sti(npchar.quest.bakaut_sum) < sti(npchar.quest.bakaut_pay)) // полная сумма
			{
				npchar.quest.bakaut_pay = sti(npchar.quest.bakaut_sum);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.bakaut_sum)-sti(npchar.quest.bakaut_pay);
			npchar.quest.bakaut_sum = iTemp; // запоминаем остаток
			RemoveItems(pchar, "gold_dublon", sti(npchar.quest.bakaut_pay));
			Log_Info("Du hast "+sti(npchar.quest.bakaut_pay)+" Dublonen gegeben");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "Gute Arbeit, "+pchar.name+"! Wieder einmal wird mir bewusst, dass du ein guter Mensch bist, mit dem man sich einlassen kann.";
				link.l1 = "Ich versuche es, Jan...";
				link.l1.go = "bakaut_done";
			}
			else
			{
				dialog.text = "Großartig. Wirst du die übrigen "+FindRussianQtyString(sti(npchar.quest.bakaut_sum))+" Dublonen später bringen?";
				link.l1 = "Ja. Ich konnte einfach nicht so einen großen Haufen Gold auf einmal schleppen.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay_wait":
			dialog.text = "Also, "+pchar.name+", wie geht es meinen Dublonen?";
			link.l1 = "Ich bin bereit, dir noch etwas mehr Gold zu geben.";
			link.l1.go = "saga_61_1";
		break;
		
		case "bakaut_done": // рассчитались
			dialog.text = "Ich habe einen Vorschlag für dich. Da du einen lukrativen Käufer finden konntest, könnte ich dir etwas Eisenholz verkaufen. Früher bekam ich dafür dreißig Dublonen pro Stück. Wenn du willst, kannst du es zu diesem Preis von mir kaufen. Ich verkaufe es lieber an dich als an jemand anderen.";
			link.l1 = "Wie viel Eisenholz kannst du verkaufen?";
			link.l1.go = "bakaut_done_1";
		break;
		
		case "bakaut_done_1":
			dialog.text = "Ich vermeide es, große Mengen anzusammeln. Molligans war eine Ausnahme. Den Behörden wird die Nachricht von einem lokalen Schwarzmarkt nicht gefallen. Also, hier ist der Deal: Ich werde für dich an jedem 14. und 24. eines Monats 25 Stück Eisenholz zurücklegen.\nWenn du es kaufen willst, bringe siebenhundertfünfzig Dublonen mit und nimm den ganzen Haufen mit. Wenn du an diesem Tag nicht auftauchst, dann verkaufe ich es an einen anderen Kunden. Auf diese Weise kannst du monatlich 50 Stück bekommen. Abgemacht?";
			link.l1 = "Du hast einen Deal, Jan! Lass uns das machen. Jetzt ist es Zeit für mich zu gehen...";
			link.l1.go = "saga_oust";
			DeleteAttribute(npchar, "quest.bakaut_sum");
			npchar.quest.trade_bakaut = "true"; // генератор купли-продажи бакаута
			AddQuestRecord("Unique_Goods", "1");
		break;
		
		case "saga_59_1": // укрысил у Яна - нет генератора на бакаут, потерял больше
			dialog.text = "Ach, also entweder war er es nicht oder er hat das Eisenholz schon vorher verkauft... Was für eine Schande. Nun, du bist meine einzige Hoffnung, das Geld für den Anwalt zu bekommen.";
			link.l1 = "Ich bin bereit, diese Verantwortung zu übernehmen. Das ist nicht mein erster Rodeo.";
			link.l1.go = "exit";
			// Ян расстроен и забыл про Устрицу - так что и Устрицы тоже не будет
			DeleteAttribute(npchar, "quest.bakaut_sum");
		break;
		
		case "saga_62":
			dialog.text = "Ist das so? Das ist interessant. Frag ruhig nach. Über wen möchtest du sprechen?";
			link.l1 = "Über ein Mädchen. Ihr Name war... Jessica Rose.";
			link.l1.go = "saga_63";
		break;
		
		case "saga_63":
			dialog.text = "Hm. Hat der neue Anführer unserer Bruderschaft dir von ihr erzählt?";
			link.l1 = "Er hat es auch getan. Aber ich habe von ihr durch Baker erfahren, der alte Henker von St. John's. Der gleiche Mann, der Kapitän Butcher hingerichtet hat.";
			link.l1.go = "saga_64";
		break;
		
		case "saga_64":
			dialog.text = "Gut. Hm. Nun, es sind über zwanzig Jahre vergangen, seit ich Jessica zum letzten Mal gesehen habe. Was weißt du über sie?";
			link.l1 = "Nun, ich weiß, wie sie mit Kapitän Butcher zusammenkam und wie sie gemeinsam piratierten. Ich weiß, dass er sie für Beatrice verlassen hat. Später rächte sie sich mit Hilfe von einem Joshua Leadbeater, auch bekannt als die Maske...";
			link.l1.go = "saga_65";
		break;
		
		case "saga_65":
			dialog.text = "";
			link.l1 = "Ich weiß auch, dass du, Jan, verzeih meine Offenheit, an Jessica interessiert warst. Das ist der Grund, warum ich zu dir gekommen bin. Jessica ist eine wichtige Figur in meinen Nachforschungen. Sie war es, die aus Eifersucht Beatrice Sharp ermordet hat, so wie ich das verstehe.";
			link.l1.go = "saga_66";
		break;
		
		case "saga_66":
			dialog.text = "Nun, du weißt viel. Ja, ich habe wirklich um Jess geworben, aber es war keine Überraschung, alle Piraten von Isla Tesoro waren damals in zwei verschiedene Gruppen unterteilt: diejenigen, die Beatrice ficken wollten und diejenigen, die Jessica wollten.\nIch erinnere mich gut an sie ... Sie war wunderschön, sehr wunderschön!..";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Jess");
			NextDiag.TempNode = "saga_66a";
		break;
		
		case "saga_66a":
			dialog.text = "Sie war etwas Besonderes... Es ist auch ziemlich wahrscheinlich, dass Jess Beatrice getötet hat. Nachdem Butcher sie vom 'Neptune' geworfen hat, hat sie wahrscheinlich an nichts anderes gedacht, als ihre Rache an ihm und Beatrice zu stillen. Übrigens, weißt du, wie Butcher Jessica losgeworden ist?";
			link.l1 = "Nein. Entweder er hat sie einfach auf Barbados abgesetzt oder sie zur Lösegeldforderung aufgestellt.";
			link.l1.go = "saga_67";
		break;
		
		case "saga_67":
			dialog.text = "Das zweite. Er hat sie über alle Maßen erniedrigt. Er sperrte sie einfach in die Kabine, brachte sie nach Barbados, begann mit ihrem Vater Oliver Rose zu verhandeln und verkaufte sie tatsächlich für einen Haufen Dublonen... nach allem, was sie für ihn getan hatte.";
			link.l1 = "Hm. Ich dachte, Butcher verteidigte ihre Ehre, als Piraten den 'Neptune' von Joshua Leadbeater eroberten...";
			link.l1.go = "saga_68";
		break;
		
		case "saga_68":
			dialog.text = "Das ist auch wahr. Aber sie hat ihm auch teuer als Belohnung bezahlt. Jessica hat dieses Abschaums erbärmliches Leben mehrmals gerettet, indem sie ihn von dem Nagelbett hob, das er sich regelmäßig für sein prahlerisches und heftiges Temperament zurechtlegte. Tatsächlich verdankte er den Ruhm eines wohlhabenden Piraten nur ihr.";
			link.l1 = "Ja, ja, sein 'roter Talisman'. Ich habe davon gehört. Sie sagen, dass sobald Butcher Jess abtrat, sein Glück das Gleiche mit ihm tat...";
			link.l1.go = "saga_69";
		break;
		
		case "saga_69":
			dialog.text = "Aber natürlich. Ohne Jessica wurde er nur zu einem weiteren gewöhnlichen Seeräuber, wenn auch einem waghalsig mutigen. Aber Jessica war nicht für ihn da, sie war diejenige, die ihm half, all seine riskanten Operationen zu planen und er konnte sich immer auf ihre Klinge verlassen. \nSicher, Beatrice war auch kein braves Mädchen, aber sie konnte Jess nicht das Wasser reichen, Bea's Reize waren völlig anders... Sie machte den Fehler, sich mit Butcher anzulegen.";
			link.l1 = "Ich habe das schon irgendwo gehört...";
			link.l1.go = "saga_70";
		break;
		
		case "saga_70":
			dialog.text = "Alle Piraten dachten so, einschließlich Blaze Sharp, ihrem Bruder. Er konnte Butcher nicht ausstehen... Aber zurück zu Jessica. Ich wagte nicht einmal an sie zu denken, während sie auf der 'Neptune' war, sie würde ihren geliebten Kapitän nie verlassen. Aber als Butcher sie auf so gemeine Weise loswurde...\nIch kam auf Barbados an und freundete mich mit ihr an. Es war nicht einfach für sie, sie liebte das Meer und gefährliche Abenteuer. Das stumpfe Kolonialleben tötete sie. Außerdem war sie während ihres Dienstes auf der 'Neptune' und in Bridgetown zu einer sehr berüchtigten Person in der Karibik geworden und die Leute von Bridgetown hatten Gründe, sie als Butchers Komplizin zu betrachten...";
			link.l1 = "Aber sie konnten nichts beweisen...";
			link.l1.go = "saga_71";
		break;
		
		case "saga_71":
			dialog.text = "Nein. Aber niemand wollte auch etwas mit ihr zu tun haben. Sie galt trotz ihres Status in Bridgetown als verflucht. Ich denke, ich war der einzige Mann, der mehr als eine halbe Stunde mit Jessica dort verbracht hat.\nIch bot ihr an, mit mir nach West Main zu kommen und dort ein neues Leben zu beginnen. Das Leben, das sie immer wollte - das Meer, Schiffe, Reisen, Abenteuer. Ich hatte zu dieser Zeit bereits eine große Operation in Blueweld aufgebaut und konnte ihr hundertmal mehr bieten als dieser Abschaum Butcher. Aber Jess war sehr verletzt. Sie hatte Butcher seine Verrat und seine Behandlung danach nicht vergeben. Und ich glaube, sie hatte damals immer noch Gefühle für ihn... Trotz all meiner Bemühungen konnte ich sie nicht die Vergangenheit vergessen lassen, sie war besessen von Gedanken an Rache.";
			link.l1 = "Ja, ich beneide sie nicht. Armes Mädchen...";
			link.l1.go = "saga_72";
		break;
		
		case "saga_72":
			dialog.text = "Ich fühlte genauso für sie. Und später fing sie an, sich für alte indische Kulte und Rituale zu interessieren. Es passierte, nachdem ein indischer Magier aus den tiefen Dschungeln von Yucatan gefangen genommen und zur lokalen Plantage gebracht wurde. Jessica kaufte ihn und gab ihm ein Haus auf ihrer Plantage.\nSie verbrachte viel Zeit mit dem Magier. Sie sagte, es sei alles wegen ihres historischen Interesses an magischen indischen Ritualen. Die Leute von Bridgetown wurden besorgt, besonders der örtliche Pastor. Tatsächlich war er einer der wenigen, der Jessica gut gesinnt war.\nDer Priester sprach oft mit ihr, überzeugte sie davon, den Magier loszuwerden, drohte ihr mit Gefahren und der Inquisition, aber Jessica zu erschrecken war eine sinnlose Übung. Eines Nachts brachen einige Fremde in das Haus des Magiers ein und ermordeten ihn.\nIn derselben Nacht griffen zwei Männer Jessica in ihrem eigenen Schlafzimmer an, aber das ging nicht gut für sie aus - niemand in Bridgetown wusste, wie gut Jess ihr flammenbesetztes Schwert beherrschte. Sie schnitt sie buchstäblich in Scheiben.";
			link.l1 = "Ja, sicher... diese rücksichtslose Virago!";
			link.l1.go = "saga_73";
		break;
		
		case "saga_73":
			dialog.text = "Danach fürchtete die ganze Stadt sie. Und dann kam die Maske. Sie fanden sich ziemlich schnell.";
			link.l1 = "Laut den Schriften ist die Maske Joshua Leadbeater, der ehemalige Kapitän der 'Neptune'...";
			link.l1.go = "saga_74";
		break;
		
		case "saga_74":
			dialog.text = "Ich erfuhr das viel später. Eine Woche nach der Ankunft der Maske nahm Jess ihre Sachen, verabschiedete sich von mir und segelte auf einer Militärfregatte in unbekannte Richtungen davon. Sie kehrte nie zurück... genau wie Beatrice nie nach Isla Tesoro zurückkehrte.\nKurz nachdem sie Butcher in St. John's aufgehangen hatten, wurde er von der Maske selbst dorthin gebracht. Aber er überlebte Butcher nur einen Tag.";
			link.l1 = "Ja... Unser Steven Dodson hat Klasse gezeigt...";
			link.l1.go = "saga_75";
		break;
		
		case "saga_75":
			dialog.text = "Ja, das wurde mir gesagt. Er hat Beatrice gerächt... Und so endet Jessicas Geschichte, sie starb irgendwo auf einer unbewohnten Insel in einem Gefecht mit den Piraten von Butcher. Niemand weiß, wo dieser Ort ist. Butcher ist tot und ebenso Jackman und Hangman.";
			link.l1 = "Da liegst du falsch, Jan. Butcher ist am Leben.";
			link.l1.go = "saga_76";
		break;
		
		case "saga_76":
			dialog.text = "Was!? Das kann nicht sein! Er wurde gehängt!";
			link.l1 = "Lies Raymond Bakers Zeugenaussage. Sie ist besser als jede Geschichte.";
			link.l1.go = "saga_77";
		break;
		
		case "saga_77":
			PlaySound("interface\important_item.wav");
			dialog.text = "Zeig mir das...(liest) Hm. Unglaublich! Es stellt sich heraus, dass seine Hinrichtung inszeniert wurde!";
			link.l1 = "Glatt, was? Das ist aber noch nicht alles. Du kennst Butcher. Du weißt nur nicht, wer er jetzt ist.";
			link.l1.go = "saga_78";
		break;
		
		case "saga_78":
			dialog.text = "Ja? Und wer ist er?";
			link.l1 = "Lawrence Beltrope aus Port Royal. Der Besitzer der Mine, dieser sehr geheimnisvolle Schatten hinter Jackman. Ich habe es durch Baker herausgefunden und Baker hat es von der Maske erfahren.";
			link.l1.go = "saga_79";
		break;
		
		case "saga_79":
			dialog.text = "Heilige Scheiße! Also stellt sich heraus, dass er derjenige ist, der das alles orchestriert hat? Nun, in Ordnung... Wir werden uns auch auf den Weg zu Butcher machen. Ich werde darüber nachdenken, wie man diesen üblen Pfennig loswird. Obwohl es nicht einfach sein wird, steht er unter dem nachhaltigen Schutz der englischen Behörden.";
			link.l1 = "Seine Zeit wird kommen, Jan. Bald wird er seinen Bootsmann und Quartiermeister treffen. Gut, danke für die Geschichte. Es ist Zeit für mich zu gehen.";
			link.l1.go = "saga_80";
		break;
		
		case "saga_80":
			dialog.text = "Wohin gehst du gerade?";
			link.l1 = "Auf irgendeine Insel. Ich glaube, es ist der gleiche Ort, an dem Jess und Beatrice gestorben sind und wo die Maske auf Butcher-Beltrope stürzte. Ich brauche Beweise, dass Helen zur Sharp-Familie gehört und ich hoffe, sie dort ausgraben zu können.";
			link.l1.go = "saga_81";
		break;
		
		case "saga_81":
			dialog.text = "In Ordnung. Also, "+pchar.name+", viel Glück für dich. Gib mir die Details, wenn du zurückkommst.";
			link.l1 = "Natürlich. Bis später, Jan!";
			link.l1.go = "saga_81a";
		break;
		
		case "saga_81a":
			DialogExit();
			LAi_SetHuberType(npchar);
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(npchar, "quest.jessika");
			npchar.quest.jessika_peace = "true"; // атрибут на мирное разрешение после боя
		break;
		
		case "saga_82":
			dialog.text = "Tolle Arbeit, "+pchar.name+". Sie haben das Unmögliche vollbracht. Wir alle Barone der Bruderschaft der Küste sind dir zu Dank verpflichtet.";
			link.l1 = "Ja, der Weg zum Sieg war schmal. Wenn ich nur vorher gewusst hätte, dass ich so viel aushalten muss...";
			link.l1.go = "saga_83";
		break;
		
		case "saga_83":
			dialog.text = "Wie geht es Helen? Was plant sie zu tun?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Sie bleibt auf meinem Schiff bei mir. Sie ist nicht mehr nur ein gewöhnlicher Offizier. Die Kontrolle über die Insel wird dem Anführer der Bruderschaft übergeben, und alles, was sie bekommt, ist Miete. Helen hat das selbst entschieden.";
				link.l1.go = "saga_84";
			}
			else
			{
				link.l1 = "Sie machte sich auf den Weg zur Isla Tesoro, um die Baronie in ihre eigenen Hände zu nehmen.";
				link.l1.go = "saga_85";
			}
		break;
		
		case "saga_84":
			dialog.text = "Nun, "+pchar.name+"... Herzlichen Glückwunsch! Viele Männer haben davon geträumt, an deiner Stelle zu sein. Ich freue mich, dass Helen einen Mann gewählt hat, der sie verdient. Es könnte nie einen besseren Kandidaten geben als dich, um ihr Lebensgefährte zu sein.";
			link.l1 = "Danke dir, Jan! Nun möchte ich zu unserem Gespräch über Tortuga und Levasseur zurückkehren.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "Danke dir, Jan!";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_85":
			dialog.text = "Wunderbar. Sie verdient es. Ich denke, der neue Anführer der Bruderschaft wird ihr helfen, ihre Angelegenheiten zu regeln. Sie ist ein talentiertes und kluges junges Mädchen, das schnell begreift und alles lernen kann. Danke, "+pchar.name+"! Helen ist wie eine Tochter für mich und ich bin überglücklich, dass sich für sie gerade eine so wunderbare Zukunft eröffnet hat.";
			link.l1 = "Gern geschehen, Jan... Wie auch immer, ich möchte gerne zu unserem Gespräch über Tortuga und Levasseur zurückkehren.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "Gern geschehen, Jan.";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_86":
			sTemp = "Shark Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = "Während du weg warst, haben "+sTemp+" und ich haben bereits darüber gesprochen, und eine gemeinsame Meinung zur Beseitigung von Levasseur. Segel zur Isla Tesoro und sprich mit unserem neuen Chef, er wird dich mit die Details unseres Plans vertraut machen und dir alle Hilfe geben, die er dir geben kann.";
			link.l1 = "Ich rieche endlich den Duft von Schießpulver! Keine Zeit zu verlieren, ich mache mich auf den Weg zur Isla Tesoro!";
			link.l1.go = "saga_87";
		break;
		
		case "saga_87":
			dialog.text = ""+pchar.name+", warte einen Moment. Ich habe ein paar Geschenke für dich für deine Hilfe bezüglich Helen und den Brüdern. Das erste ist das verzauberte Amulett von Saracen aus dem fernen Osten. Seine Reize stärken die Disziplin auf dem Schiff, von mir persönlich überprüft. Hier hast du es.";
			link.l1 = "Danke dir!";
			link.l1.go = "saga_88";
		break;
		
		case "saga_88":
			GiveItem2Character(pchar, "talisman4");
			Log_Info("Du hast das Amulett 'Janitschar' erhalten.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Das Zweite ist nur ein Andenken an vergangene Abenteuer. Ich habe den Rat überzeugt, diesen lächerlichen Überbleibsel der Verwendung von Steinfragmenten in den Wind zu werfen. Sie werden nicht mehr benötigt. Ich gebe sie dir. Vielleicht findest du irgendwie eine Verwendung für sie.";
			link.l1 = "Einen Verwendungszweck für Fragmente? Hm. Ich weiß nicht... aber als Andenken bin ich sehr dankbar dafür!";
			link.l1.go = "saga_89";
		break;
		
		case "saga_89":
			GiveItem2Character(pchar, "splinter_js"); 
			GiveItem2Character(pchar, "splinter_nh"); 
			GiveItem2Character(pchar, "splinter_mt"); 
			GiveItem2Character(pchar, "splinter_zm"); 
			GiveItem2Character(pchar, "splinter_jb"); 
			Log_Info("Du hast fünf ornamentale Musterfragmente erhalten");
			dialog.text = "Nun, vergiss nicht deinen Freund, "+pchar.name+". Komm vorbei, wenn du in Blueweld ankommst. Wir setzen uns hin und trinken etwas Rum. Ich freue mich immer dich zu sehen.";
			link.l1 = "Sicherlich, Jan. Wir haben jetzt etwas, woran wir uns erinnern können, oder? Ha-ha! Wie auch immer, ich sollte gehen.";
			link.l1.go = "saga_90";
		break;
		
		case "saga_90":
			dialog.text = "Viel Glück, "+pchar.name+"!";
			link.l1 = "Bis dann...";
			link.l1.go = "saga_91";
		break;
		
		case "saga_91":
			DialogExit();
			pchar.questTemp.Saga = "end";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock")) AddQuestRecord("Saga", "26_1");
			else 
			{
				AddQuestRecord("Saga", "26");
				pchar.questTemp.Terrapin = "islatesoro";
			}
			CloseQuestHeader("Saga");
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
	// --> провалы Саги
		case "saga_f_1":
			dialog.text = "Ja... Es sieht wirklich so aus, als wäre unser Plan krachend gescheitert. Jetzt werden wir nicht in der Lage sein, denjenigen, den wir wollten, als Oberhaupt der Bruderschaft einzusetzen. Jackman ist tot, das ist gut und schön. Aber ach, mein Plan wird jetzt nicht funktionieren. Wir werden das Oberhaupt der Bruderschaft auf die übliche Weise wählen müssen und Gott weiß, welche Wendung das nehmen wird...";
			link.l1 = "Das ist bedauerlich. Sehr bedauerlich. Und es sieht so aus, als würde Helen ohne ihr Erbe bleiben.";
			link.l1.go = "saga_f_2";
		break;
		
		case "saga_f_2":
			dialog.text = "Ja, "+pchar.name+". Und ich würde Ihnen wirklich gerne helfen, Tortuga zu nehmen, das würde ich wirklich, aber jetzt weiß ich nicht einmal, wie. Wahrscheinlich kann ich nichts tun, um zu helfen. Es sieht so aus, als müsstest du dich nur auf deine eigenen Stärken und Fähigkeiten zu kämpfen nun verlassen.";
			link.l1 = "Es sieht so aus, als gäbe es keine andere Möglichkeit mehr... Also gut, Jan, ich werde nachdenken, was als nächstes zu tun ist. Bis später...";
			link.l1.go = "saga_f_3";
		break;
		
		case "saga_f_3":
			dialog.text = "Komm vorbei, "+pchar.name+". Ich freue mich immer, dich zu sehen.";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			CloseQuestHeader("Testament");
		break;
		
		case "saga_l1": // проход первый - отбираем Элен и закрываем вход к Свенсону
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l1";
			pchar.quest.Saga_Late_1.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_1.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_1.function = "Saga_HelenaTalk";
			pchar.questTemp.Saga.Jackman = "true";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
		break;
		
		case "saga_l2": // проход второй - отбираем Элен, Натана и Данни в Марун-Таун, чистим квестовый лут
			dialog.text = "Aber ach, es ist zu spät, jetzt noch etwas zu tun. Isla Tesoro ist offiziell in die Gewalt der englischen Krone übergegangen. Dort befindet sich jetzt eine Garnison. Das ist ein schwerer Schlag für die Bruderschaft, von dem wir uns, fürchte ich, nicht erholen werden.";
			link.l1 = "Wie schrecklich... Ah, ich hätte schneller handeln sollen. Dann, siehst du, wäre alles gut gegangen. In Ordnung, Jan, ich werde nachdenken, was ich als nächstes tun werde. Bis später...";
			link.l1.go = "saga_l2_1";
		break;
		
		case "saga_l2_1":
			dialog.text = "Komm doch vorbei, "+pchar.name+". Ich freue mich immer, dich zu sehen.";
			link.l1 = "...";
			link.l1.go = "saga_l2_2";
		break;
		
		case "saga_l2_2":
			DialogExit();
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "letter_parol", 1);
			RemoveItems(pchar, "map_sharp_full", 1);
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l2";
			pchar.quest.Saga_Late_2.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_2.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_2.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
		
		case "saga_l3":
			dialog.text = "Ja... Wir haben wirklich eine harte Niederlage erlitten. Und das Schlimmste daran ist, dass wir buchstäblich einen Schritt vom Sieg entfernt waren. Verdammt! Wie konnte das passieren, hm, "+pchar.name+"? Du hast dich so angestrengt, so viel getan und... so ein hartes Pech!";
			link.l1 = "Ich bin der Trottel, der dafür verantwortlich ist. Ich hätte schneller sein sollen. Und dank mir wird Helen ihr Erbe verlieren. Und der Tortuga-Plan wird niemals verwirklicht werden.";
			link.l1.go = "saga_f_2";
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
	// <-- провалы Саги
		
	//-----------------------------------генератор торговли бакаутом--------------------------------------------
		case "trade_bakaut":
			if (CheckAttribute(pchar, "questTemp.UpgradeBakaut"))
			{
				dialog.text = "In Ordnung, es macht mir nichts aus. Ich habe 125 Einheiten in meinem Lagerhaus. Der Preis, wie Sie sich erinnern, beträgt 3150 Dublonen.";
				if (PCharDublonsTotal() >= 3150)
				{
					link.l1 = "In Ordnung, abgemacht. Hier hast du. Hier sind 3150 Dublonen.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "Ist das nicht verdammt Pech. Ich habe mein Geld auf meinem Schiff vergessen. Ich komme gleich damit zurück.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "In Ordnung, es macht mir nichts aus. Ich habe fünfundzwanzig Einheiten in meinem Lagerhaus. Der Preis, wie Sie sich erinnern, beträgt dreißig Dublonen pro Stück.";
				if (PCharDublonsTotal() >= 750)
				{
					link.l1 = "In Ordnung, abgemacht. Hier hast du. Hier sind siebenhundertfünfzig Dublonen.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "Ist das nicht verdammt Pech. Ich habe mein Geld auf meinem Schiff vergessen. Ich komme gleich damit zurück.";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && !CheckAttribute(pchar, "questTemp.SvensonBakautBlock")) // увеличить объём поставок бакаута
			{
				link.l4 = "Jan, wäre es möglich, die Größe der Pockholz-Lieferungen zu erhöhen?";
				link.l4.go = "UpgradeBakaut";
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && CheckAttribute(pchar, "questTemp.SvensonBakautPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок бакаута, если в первый раз не принесли
			{
				link.l4 = "Jan, ich habe dreitausend Goldstücke gesammelt. Hier, du kannst dieses Geschenk unseren Schmarotzern überreichen. Ich vermute, sie werden heute einen glücklichen Tag haben.";
				link.l4.go = "UpgradeBakaut_Agreed";
			}
		break;
		
		case "trade_bakaut_1":
			RemoveDublonsFromPCharTotal(750);
			Log_Info("Du hast 750 Dublonen gegeben");
			PlaySound("interface\important_item.wav");
			dialog.text = "Lobenswert. Ich werde meinen Leuten befehlen, das Eisenholz auf dein Schiff zu bringen.";
			link.l1 = "Danke dir!";
			link.l1.go = "trade_bakaut_2";
		break;
		
		case "trade_bakaut_2":
			dialog.text = "Wenn du mehr kaufen möchtest, komm in zwei Wochen zurück. Bis dahin werde ich eine weitere Charge zusammengestellt haben.";
			link.l1 = "In Ordnung, Jan. Bis zum nächsten Mal!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SANDAL, 25);
			DeleteAttribute(npchar, "quest.trade_bakaut");
			SetFunctionTimerCondition("Bakaut_SvensonAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "UpgradeBakaut": //
			if (startHeroType == 1) sStr = "mein Freund";
			if (startHeroType == 2) sStr = "mein Freund";
			if (startHeroType == 3) sStr = "mein Freund";
			if (startHeroType == 4) sStr = "Helen";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Freut mich, dass dir das Pockholz gefällt, " + sStr + ". Die Lieferungen zu vergrößern ist kein Problem, aber es gibt da ein 'Aber', verstehst du. Mit steigenden Mengen entsteht auch eine Spur, die unerwünschte Aufmerksamkeit auf sich ziehen kann, besonders von den englischen Behörden. Aber wenn wir zuverlässige Hände, treue Ohren und Leute in der Residenz hinzufügen, die uns helfen, im Schatten zu bleiben, kann alles arrangiert werden. Allerdings wird das nicht billig - dreitausend Dublonen, um die Stadtkasse und die Bedürfnisse Englands zu umgehen. Dann kann ich dir auch fünfmal mehr liefern. Was sagst du dazu?";
				link.l1 = "Dreitausend Dublonen? Jan, das ist ja Raubüberfall am helllichten Tag! Könnten wir nicht irgendwie mit geringeren Kosten auskommen? Vielleicht gibt es einen Weg, die Sache ohne solch märchenhafte Summen zu regeln?";
				link.l1.go = "UpgradeBakaut_1";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Gute Idee, aber ich muss sagen, für solche Mengen im Handelsgeschäft braucht man etwas mehr Erfahrung und Geschick. Eile birgt mehr Risiko als Nutzen. Machen wir es so: Sammle noch etwas mehr Erfahrung, und wenn du für größere Partien bereit bist, komm wieder. Dann besprechen wir alles ordentlich.";
				link.l1 = "Hmm... In Ordnung. Kommen wir später auf dieses Gespräch zurück.";
				link.l1.go = "exit";
				notification("Skill Check Failed (80)", SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeBakaut_1":
			dialog.text = "Leider, "+pchar.name+", das ist heutzutage der Preis für Ruhe - die Appetite dieser Herren in Perücken und Uniformen wachsen mit jedem Tag. Nichts lockt sie mehr als Dublonen, die in ihren Truhen klimpern. Ich garantiere dir einen Rabatt von fünfzehn Prozent auf alle nachfolgenden Lieferungen, wenn dich das tröstet.";
			link.l1 = "Verdammt seien sie! Solche Summen zu verlangen! Mit solcher Gier sollten sie Königsschätze kaufen, nicht um Schweigen feilschen! Jan, vielleicht sollten wir... ihnen zeigen, wer die wahre Macht im Archipel ist, was meinst du?";
			link.l1.go = "UpgradeBakaut_2";
		break;
		
		case "UpgradeBakaut_2":
			if (startHeroType == 1) sStr = "mein Freund";
			if (startHeroType == 2) sStr = "mein Freund";
			if (startHeroType == 3) sStr = "mein Freund";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "Ha! Was für ein Eifer du hast, " + sStr + "! Aber gegen ganz England zu gehen liegt mir jetzt nicht, und die Jahre sind auch nicht mehr dieselben. Lass uns einfach diese Blutsauger bezahlen, und sie sollen ruhig sitzen bleiben - wir müssen unser Geschäft machen. Sammle die nötige Summe, und unser Weg wird frei sein, ohne unnötige Fragen!";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Na gut, Jan, du hast mich überzeugt. So sei es, da es keinen anderen Weg gibt. Hier sind deine dreitausend Dublonen. Nur denk daran: Ich habe nicht vor, diese Geizhälse für immer zu füttern.";
				link.l1.go = "UpgradeBakaut_Agreed";
			}
			link.l2 = "Zum Teufel mit ihnen, Jan! Glaubst du wirklich, dass es keinen anderen Ausweg gibt? Na gut. Ich werde diese Dublonen auftreiben. Aber im Moment habe ich solches Geld nicht.";
			link.l2.go = "UpgradeBakaut_4";
			link.l3 = "Verdammt, Jan, willst du wirklich, dass ich diese Beamten mit ihren gepflegten Damen füttere? Sie sitzen auf ihren Stühlen, tun nichts und verlangen nur Geld! Nein, das gefällt mir nicht! Ich werde ihre Taschen nicht mit meinem Schweiß und Blut füllen! Kehren wir zu den bisherigen Bedingungen zurück. Das reicht mir.";
			link.l3.go = "UpgradeBakaut_3";
		break;
		
		case "UpgradeBakaut_Agreed":
			dialog.text = "Das ist doch mal ein anderes Gespräch! Mit deinem Beitrag werden unsere Geschäfte wie geschmiert laufen, und diese Geizhälse bekommen ihr Teil - und werden nicht einmal mehr in Richtung Pockholz schauen. Ich versichere dir, bald werden wir alle Investitionen hundertfach zurückgewinnen.";
			link.l1 = "Ich hoffe es, Jan, ich hoffe es.";
			link.l1.go = "UpgradeBakaut_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecord("Unique_Goods", "1_1");
			pchar.questTemp.UpgradeBakaut = true;
			pchar.questTemp.SvensonBakautBlock = true;
			DeleteAttribute(pchar, "questTemp.SvensonBakautPotom");
		break;
		
		case "UpgradeBakaut_Agreed_1":
			dialog.text = "Die Geschäfte werden laufen, wie sie sollten, du brauchst dir keine Sorgen zu machen. Und nun zu unseren zukünftigen Geschäften: Ich werde für dich 125 Stämme Pockholz bereithalten, wie bisher, zum 14. und 28. jeden Monats. Du kannst die gesamte Partie für 3150 Dublonen abholen.";
			link.l1 = "Solche Gespräche gefallen mir viel besser! Also hundertfünfundzwanzig Stämme? Ausgezeichnet, Jan. Nun denn, bis bald, ich werde auf die Lieferung warten!";
			link.l1.go = "exit";
		break;
		
		case "UpgradeBakaut_3":
			if (startHeroType == 1) sStr = "mein Freund";
			if (startHeroType == 2) sStr = "mein Freund";
			if (startHeroType == 3) sStr = "mein Freund";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "Wie du willst, " + sStr + ". Und reg dich nicht so auf. So ist diese Welt nun mal eingerichtet.";
			link.l1 = "Ja, Jan, ich weiß, wie diese Welt eingerichtet ist. Aber das heißt nicht, dass ich es ertragen muss. Nun gut, ich muss gehen.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
		break;
		
		case "UpgradeBakaut_4":
			dialog.text = "Ich warte, bis du das Geld zusammenhast. Ich weiß, dass du einen Weg finden wirst. Sobald du bereit bist - erwarte ich dich mit dem Geld, und wir machen weiter.";
			link.l1 = "In Ordnung.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
			pchar.questTemp.SvensonBakautPotom = true;
		break;
		// <-- генератор бакаута
		
	//----------------------------------- штурм рудника --------------------------------------------
		case "mine_attack":
			dialog.text = "Freut mich, dich zu sehen, "+pchar.name+". Meine Leute sind bereit. Ab in den Dschungel?";
			link.l1 = "Ja, Jan. Meine Mannschaft ist bereit für die Schlacht.";
			link.l1.go = "mine_attack_1";
		break;
		
		case "mine_attack_1":
			dialog.text = "Dann lasst uns aufbrechen. Die Mine liegt in der großen Tiefe des Dschungels, genau auf diesem Pfad. Bleibt rechts an der Gabelung. Vorwärts!";
			link.l1 = "Weiter!";
			link.l1.go = "mine_attack_2";
		break;
		
		case "mine_attack_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("shore53", "boat", true);
			LocatorReloadEnterDisable("mine_03", "reload3_back", true);
			LocatorReloadEnterDisable("mine_02", "reload3_back", true);
			pchar.quest.Saga_MineAttack_01.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_01.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_01.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_3":
			dialog.text = "Also, "+pchar.name+", es ist Zeit, zu diskutieren, wie wir diese Operation angehen werden. Ich habe bereits mehrere Miskito-Indianer vorausgeschickt, um das Gebiet zu erkunden und einen Aktionsplan basierend auf ihren Beobachtungen erstellt.";
			link.l1 = "Füll mich ein!";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "Die Grube stellt die Mine unter den Bergen im Dschungel dar. Es gibt ein Lager in der Nähe eines Mineneingangs. Ein paar Häuser und eine Palisade. Es führt ein Weg zur Palisade. Schau, er führt zu einer kleinen, gerodeten Stelle im Dschungel nicht weit von hier. Dort befindet sich der Haupteingang zur Grube\nSie stellt eine hohe Steinmauer zwischen zwei steilen Hügeln dar, die verhindert, dass jemand hineinschleichen kann. Die Tore werden von einer Wache von sechs Männern geschützt. Nicht viel, aber sie haben dort auch zwei Kanonen aufgestellt. Das ist das größte Problem.\nZwei Salven von Traubenschüssen können die Hälfte unserer Truppe niederstrecken, was eine Katastrophe wäre, also ist ein Frontalangriff keine Option...";
			link.l1 = "Ha! Aber wir haben einen Trumpf, wir kennen das Passwort, das uns hineinbringt...";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			dialog.text = "Das ist korrekt. Wir werden das zu unserem Vorteil nutzen, aber lass mich dir jetzt meinen gesamten Plan bis zum Ende mitteilen.";
			link.l1 = "Sicher, Jan. Ich bin ganz Ohr.";
			link.l1.go = "mine_attack_6";
		break;
		
		case "mine_attack_6":
			dialog.text = "Es gibt einen anderen Eingang zur Grube - durch diesen Pfad im Dschungel. Er umrundet die Hügel, die die Mine schützen, und führt zu einer kleinen und engen Mulde, die zum Eindringen genutzt werden kann. Aber die Banditen haben dort einen hohen Zaun aufgestellt und Wachen postiert. Der Zaun hat kleine Tore, aber sie sind von der anderen Seite verbarrikadiert.\nJetzt hört zu, was wir vorhaben. Wir werden uns derer entledigen, die den zweiten Eingang zur Mine bewachen. Ein Teil unserer Truppe wird dort bleiben und einen Baumstamm finden, den wir als Rammbock verwenden können.\nWir werden zum Haupteingang zurückkehren und die Kanonenbesatzungen töten. Das Passwort, das wir haben, wird uns zweimal helfen. Danach werden wir die Mine von zwei Seiten angreifen. Ich werde die erste Angriffseinheit führen und du wirst die zweite führen.";
			link.l1 = "Nun, es ist logisch. Wir werden sie zwingen, gegen uns an zwei Fronten zu kämpfen. Vorwärts!";
			link.l1.go = "mine_attack_7";
		break;
		
		case "mine_attack_7":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.quest.mine01 = "true";
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_02.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_02.win_condition.l1.location = "Mine_04";
			pchar.quest.Saga_MineAttack_02.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_8":
			dialog.text = "Also, hier sind wir... Dies ist der Pfad zum Banditenzaun. Jetzt müssen wir entscheiden, wie wir mit ihnen umgehen. Wenn wir das ganze Geschwader dorthin schicken, wird es zu auffällig sein und sie werden Alarm schlagen.\nWir sollten eine kleine Gruppe von drei, nicht mehr, schicken, diese Gruppe wird in der Lage sein, nahe genug heranzukommen, ohne Verdacht zu erregen und überraschend anzugreifen. Ich kann die Gruppe nicht anführen, mein Gesicht ist hier zu gut bekannt.\nAlso liegt es an dir, "+pchar.name+", denn du bist der Einzige, dem ich vertrauen kann, ohne die ganze Operation zu gefährden. Ich werde dir Gregory und einen Musketier zur Unterstützung geben...";
			link.l1 = "Wie viele Wachen sind am Palisadenzaun?";
			link.l1.go = "mine_attack_9";
		break;
		
		case "mine_attack_9":
			dialog.text = "Vier. Zwei Musketiere und zwei Soldaten.";
			link.l1 = "Wir nehmen sie...";
			link.l1.go = "mine_attack_10";
		break;
		
		case "mine_attack_10":
			dialog.text = "Da ich dich kenne, zweifle ich nicht eine Sekunde daran. Geh zu ihnen und sag ihnen, dass Jackman dich geschickt hat. Sag ihnen das Passwort. Und dann, nachdem sie alle entspannt sind... handel je nach der Situation.";
			link.l1 = "In Ordnung. Wir werden sie auf Trab halten.";
			link.l1.go = "mine_attack_11";
		break;
		
		case "mine_attack_11":
			dialog.text = "Viel Glück, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "mine_attack_12";
		break;
		
		case "mine_attack_12":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 2)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 12)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				LAi_CharacterDisableDialog(sld);//запрет диалога
			}
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(npchar, "quest.mine01");
			npchar.quest.mine02 = "true";
			pchar.questTemp.Saga.MineAttack = "true";
			pchar.quest.Saga_MineAttack_03.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_03.win_condition.l1.location = "Mine_01";
			pchar.quest.Saga_MineAttack_03.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_13":
			dialog.text = "Gute Arbeit, "+pchar.name+"! Sie haben sich wie immer durchgesetzt. Nun werden meine Jungs sich darauf vorbereiten, von dieser Seite der Mine aus einen Sturm zu entfachen und wir werden den Haupteingang freiräumen.";
			link.l1 = "Ich nehme an, ich werde wieder auf die Wachen zugehen?";
			if (GetCharacterIndex("Svensons_off_2") != -1 && GetCharacterIndex("Svensons_sold_12") != -1) link.l1.go = "mine_attack_14";
			else link.l1.go = "mine_attack_14a";
		break;
		
		case "mine_attack_14a":
			dialog.text = "Ja, "+pchar.name+", noch einmal. Ich würde gerne selbst gehen, aber sie würden mich sicherlich erkennen und die ganze Operation würde drunter und drüber gehen. Es wird gefährlicher sein, da es mehr Feinde gibt, und vergiss nicht die Waffen.";
			link.l1 = "Ich nehme meine Offiziere mit mir.";
			link.l1.go = "mine_attack_14_1";
		break;
		
		case "mine_attack_14":
			dialog.text = "Ja, "+pchar.name+", noch einmal. Ich würde gerne selbst gehen, aber sie würden mich sicherlich erkennen und die ganze Operation würde schief gehen. Es wird gefährlicher sein, da es mehr Feinde gibt, und vergiss nicht die Waffen. Wen wirst du mitnehmen, um dir zu helfen? Deine Offiziere oder Gregory und der Musketier wie beim letzten Mal?";
			link.l1 = "Ich nehme meine Offiziere mit.";
			link.l1.go = "mine_attack_14_1";
			link.l2 = "Ich nehme Gregory und den Musketier.";
			link.l2.go = "mine_attack_14_2";
		break;
		
		case "mine_attack_14_1":
			dialog.text = "In Ordnung. Deine eigenen Leute sind deine beste Unterstützung. Jetzt machen wir uns auf den Weg zurück zum Haupteingang. Erinnerst du dich an den Weg?";
			link.l1 = "Natürlich. Zurück, von wo wir gekommen sind, dann bleib links und dann nimm den Pfad um den Hügel herum.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "officer";
		break;
		
		case "mine_attack_14_2":
			dialog.text = "Gut. Du hast es einmal geschafft, also sollte es das zweite Mal ein Kinderspiel sein. Wir machen uns jetzt auf den Weg zurück zum Haupteingang. Erinnerst du dich an den Weg?";
			link.l1 = "Natürlich. Den gleichen Weg zurück, dann links halten und den Pfad um den Hügel herum nehmen.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "soldiers";
		break;
		
		case "mine_attack_15":
			dialog.text = "Keine Zeit zu verschwenden. Lasst uns marschieren!";
			link.l1 = "Weiter!";
			link.l1.go = "mine_attack_16";
		break;
		
		case "mine_attack_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 12) LAi_ActorFollowEverywhere(sld, "", -1);
				else LAi_ActorRunToLocation(sld, "reload", "reload3_back", "mine_01", "goto", "goto"+i, "", 5);
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			if (pchar.questTemp.Saga.MineAttack == "soldiers") LAi_LocationDisableOfficersGen("mine_exit", true);//офицеров не пускать
			LocatorReloadEnterDisable("mine_03", "reload3_back", false);
			LocatorReloadEnterDisable("mine_02", "reload3_back", false);
			DeleteAttribute(npchar, "quest.mine02");
			npchar.quest.mine03 = "true";
			pchar.quest.Saga_MineAttack_05.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_05.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_05.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_17":
			dialog.text = "Richtig, "+pchar.name+", höre auf diese letzten Anweisungen. Diese Teufel, die die Tore bewachen, sind zäh, also wird es nicht einfach für dich sein. Dein Hauptziel ist es, die Kanoniere zu töten, die in der Nähe der Tore stehen, denn wir können dir nicht helfen, wenn sie noch atmen.\nSobald beide tot sind und es keine Chance auf eine Kanonensalve gibt, kommen wir alle und schlachten sie in Sekunden ab. Hast du das verstanden, "+pchar.name+"? Spiele nicht den Helden, töte die Kanoniere und überlasse den Rest uns.";
			link.l1 = "Gut, Jan. Ich werde versuchen, alles so zu machen, wie wir geplant haben. Und wenn etwas schief geht, werde ich improvisieren.";
			link.l1.go = "mine_attack_18";
		break;
		
		case "mine_attack_18":
			dialog.text = "Klingt gut. Gott sei mit dir!";
			link.l1 = "Danke...";
			link.l1.go = "mine_attack_19";
		break;
		
		case "mine_attack_19":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 2)
					{
						LAi_SetActorType(sld);
						LAi_ActorFollowEverywhere(sld, "", -1);
					}
					else LAi_SetStayTypeNoGroup(sld);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			DeleteAttribute(npchar, "quest.mine03");
			pchar.quest.Saga_MineAttack_06.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_06.win_condition.l1.location = "Mine_exit";
			pchar.quest.Saga_MineAttack_06.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_20":
			dialog.text = "Puh! Wir haben diese Hurensöhne niedergemäht... Zäh waren die kleinen Rüpel. Ich kann sagen, dass diese Söldner früher in den regulären Truppen gedient haben. Wir haben hier einiges an Lärm gemacht, ich fürchte, wir sind vielleicht gehört worden. Keine Minute zu verschwenden! "+pchar.name+", es ist Zeit für uns, die Mine anzugreifen.\nIch kehre zu meiner Gruppe am zweiten Eingang zurück - sie müssen bereits einen Baumstamm gefunden und vorbereitet haben, um den Zaun zu durchbrechen. Du und deine Männer werdet durch das zentrale Tor gehen. Warte eine halbe Stunde auf uns, greife nicht sofort an...";
			link.l1 = "Jan, wenn sie die Schüsse in der Mine gehört haben, haben wir diese halbe Stunde nicht. Diese Banditen könnten eine Verteidigungslinie aufbauen oder wahrscheinlich direkt zu den zentralen Toren kommen und meine Gruppe mit allem, was sie haben, angreifen...";
			link.l1.go = "mine_attack_21";
		break;
		
		case "mine_attack_21":
			dialog.text = "Verdammt! Das ist durchaus möglich. Was schlägst du vor, dass wir tun?";
			link.l1 = "Hm... Ha! Ich habe eine Idee! Kanonen! Schau dich um. Hier gibt es nicht nur Kartätschenkugel, sondern auch Bomben! Jetzt sind diese Banditen erledigt! Warum bin ich nicht früher darauf gekommen?!";
			link.l1.go = "mine_attack_22";
		break;
		
		case "mine_attack_22":
			dialog.text = "Was glaubst du, sollten wir tun?";
			link.l1 = "Wir nehmen eine Kanone. Mit einer können wir uns viel schneller und effizienter bewegen. Wir rollen sie hinein, hinter die Tore, in die Mine und stellen sie in Position. Wenn sie selbst einen Angriff starten, gibt es eine große Explosion, und wenn sie sich zurückhalten, bombardieren wir einfach ihr Lager. Kannst du mir sagen, wo genau das Lager hinter den Toren liegt?";
			link.l1.go = "mine_attack_23";
		break;
		
		case "mine_attack_23":
			dialog.text = "Das Lager liegt im Tiefland an einem Berg. Direkt hinter den Toren führt ein Pfad hinunter und windet sich um den Hügel. Das Lager befindet sich direkt hinter diesem Hügel.";
			link.l1 = "Prächtig! Wir werden uns oben auf dem Pfad aufstellen und ein paar Bomben über den Hügel in ihr Nest werfen! Oh, wir werden sie überall herumtanzen lassen!";
			link.l1.go = "mine_attack_24";
		break;
		
		case "mine_attack_24":
			dialog.text = "Verdammt noch mal, "+pchar.name+", gut gemacht! Volle Fahrt voraus! Ich überlasse Randolf deinem Kommando, er ist mein bester Kanonenschütze. Mach ihn zu deinem Schützen und er wird dich nicht enttäuschen. Ich gehe jetzt zu meiner Einheit.";
			link.l1 = "In Ordnung. Ich werde ihre Positionen für eine halbe Stunde zur Hölle bombardieren, bis ihr die Tore durchbrecht.";
			link.l1.go = "mine_attack_25";
		break;
		
		case "mine_attack_25":
			dialog.text = "Ich werde versuchen, rechtzeitig da zu sein. Wir treffen uns im Lager!";
			link.l1 = "Abgemacht... Trupp! Hört auf meinen Befehl! Bereitet euch vor, die Kanone an eine neue Stelle zu bringen! Nehmt Schießpulver, Bomben und Traubenschuss mit! Zum Bergwerk durch die Tore. Marsch, marsch!";
			link.l1.go = "mine_attack_26";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 5);
			if (GetCharacterIndex("Svensons_off_2") != -1)
			{
				sld = characterFromId("Svensons_off_2");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", 5);
			}
		break;
		
		case "mine_attack_26":
			DialogExit();
			int n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "mine_bandits");
			LocatorReloadEnterDisable("mine_exit", "reload1_back", false);
			pchar.quest.Saga_MineAttack_07.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_07.win_condition.l1.location = "Mine";
			pchar.quest.Saga_MineAttack_07.function = "Saga_MineGunAttack";
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine_exit", "reload2_back", true);
			LAi_LocationDisableOfficersGen("mine_exit", false); // офицеров пускать
			n = Findlocation("mine");
			locations[n].models.always.Gun = "mortair";
			Locations[n].models.always.Gun.locator.group = "goto";
			Locations[n].models.always.Gun.locator.name = "fire"; // орудие - к бою!
			Locations[n].hidden_sound = true;
		break;
		
		case "mine_attack_27":
			dialog.text = "Puh, sind wir nicht zu spät, "+pchar.name+"?";
			link.l1 = "Jan, heiliger Dreck! Was hat dich so lange aufgehalten? Meine Mannschaft hat gerade einen gewaltigen Schlag erlitten!";
			link.l1.go = "mine_attack_28";
		break;
		
		case "mine_attack_28":
			dialog.text = "Dieser verdammte Holzzaun hat sich als wirklich stabil herausgestellt. Wir haben ihn mit Gewalt durchbrochen... Wir haben euer Getöse gehört. Sieht so aus, als hättet ihr diesen Ort gut gesäubert! Er brennt bis auf den Grund!";
			link.l1 = "Randolfs Handlungen... Ich wünschte, du hättest sehen können, wie viele Schurken wir begraben mussten, bevor wir endlich in den Nahkampf eintraten!";
			link.l1.go = "mine_attack_29";
		break;
		
		case "mine_attack_29":
			dialog.text = "Caramba! Ich ziehe meinen Hut vor dir, "+pchar.name+". Gut gemacht! Nun, über die Verluste... die hat man immer im Krieg.";
			link.l1 = "Jetzt müssen wir das Bergwerk selbst aufräumen. Es ist möglich, dass einige Überlebende sich darin verstecken.";
			link.l1.go = "mine_attack_30";
		break;
		
		case "mine_attack_30":
			dialog.text = "Lass uns nur zu zweit gehen. Erkunden wir die Situation dort.";
			link.l1 = "Klingt nach einem Plan!";
			link.l1.go = "mine_attack_31";
		break;
		
		case "mine_attack_31":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, "");
			TakeNItems(npchar, "potion2", 8); 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "Mine_mines", "reload", "reload1", "", -1);
			LAi_LocationDisableOfficersGen("Mine_mines", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_08.win_condition.l1 = "locator";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.location = "mine";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator_group = "reload";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator = "reload4";
			pchar.quest.Saga_MineAttack_08.function = "Saga_MineAttackMines";
		break;
		
		case "mine_attack_32a":
			dialog.text = "Wir haben die ganze Mine noch nicht durchsucht! Ich garantiere dir, dass hier drinnen noch mehr von diesen Schurken versteckt sind!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_32a";
		break;
		
		case "mine_attack_32":
			dialog.text = "Ich glaube nicht, dass noch ein anderer Abschaum übrig ist...";
			link.l1 = "Jan, ich dachte, wir kämen hierher nur um die Situation zu erkunden...";
			link.l1.go = "mine_attack_33";
		break;
		
		case "mine_attack_33":
			dialog.text = "Ha-ha, nun, ich habe dir nicht gesagt, dass dies eine besondere Erkundung, eine blutige Erkundung sein würde... Ich habe mich schon lange nicht mehr so aufgewärmt! Jetzt kann jeder sicher sein, dass kein Schurke dieser Mine entkommen ist!";
			link.l1 = "Also, was werden wir als nächstes tun, Jan?";
			link.l1.go = "mine_attack_34";
		break;
		
		case "mine_attack_34":
			dialog.text = "Was meinst du, was wir als nächstes machen werden? Wir werden nach Gold und Silber suchen. Ich glaube nicht, dass Jackman hier aus Langeweile so eine Befestigung hielt. Er hat hier ein ganzes Garnison platziert. Hast du die Sklaven in der Mine gesehen? Du solltest dich erkundigen, wo sie die Auszüge lagern.";
			link.l1 = "In Ordnung. Dann gehst du die Sklaven verhören und ich klettere hoch und durchsuche alle Häuser im Lager, vielleicht finde ich etwas.";
			link.l1.go = "mine_attack_35";
		break;
		
		case "mine_attack_35":
			dialog.text = "Verstanden! Zeit, sich zu bewegen!";
			link.l1 = "...";
			link.l1.go = "mine_attack_36";
		break;
		
		case "mine_attack_36":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine", "reload1", true);
			LocatorReloadEnterDisable("mine", "reload6", true);//закрыть выходы с рудника
			pchar.quest.Saga_Mine_letter.win_condition.l1 = "item";
			pchar.quest.Saga_Mine_letter.win_condition.l1.item = "letter_mine";
			pchar.quest.Saga_Mine_letter.function = "Saga_FindMineLetter";
			NextDiag.CurrentNode = "mine_attack_36a";
		break;
		
		case "mine_attack_36a":
			dialog.text = "Geh, Kumpel. Und kehre diese erbärmlichen Hütten von innen nach außen!";
			link.l1 = "Ich bin auf dem Weg!";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_36a";
		break;
		
		case "mine_attack_37":
			dialog.text = "Ha-ha! "+pchar.name+", es ist großartig, dass du dich freiwillig gemeldet hast, mit mir diese Mine aufzureißen! Es ist ein weiterer klarer Indikator dafür, dass du unter einem glücklichen Stern geboren wurdest.";
			link.l1 = "Hast du Gold gefunden?";
			link.l1.go = "mine_attack_38";
		break;
		
		case "mine_attack_38":
			dialog.text = "Ja, verdammt! Nicht Gold, sondern Silber, ein guter Haufen davon. Einen Tag später und sie hätten es aus dem Lager bewegt. Deshalb waren hier so viele Schläger - sie waren eine Eskorte. \nDank dir haben wir es rechtzeitig geschafft, ohne dich würde ich immer noch Leute sammeln. Glückwunsch, Partner!";
			link.l1 = "Ha! Ich sehe... Wie viel Silber haben wir?";
			link.l1.go = "mine_attack_39";
		break;
		
		case "mine_attack_39":
			dialog.text = "Wir haben ungefähr vier tausend Stück. Wir teilen es in zwei Teile - die Hälfte für mich, die Hälfte für dich, genau wie wir es vereinbart haben.";
			link.l1 = "Ausgezeichnet! Wir können eine ganze Menge Geld für diesen Kram bekommen!";
			link.l1.go = "mine_attack_40";
		break;
		
		case "mine_attack_40":
			dialog.text = "Das ist sicher... Hast du etwas Wertvolles gefunden?";
			link.l1 = "Nein. Es gibt nicht mal einen einzigen Dublonen in diesen Hütten. Obwohl ich einige Papiere gefunden habe. Ich habe sie gelesen und erfahren, dass der Besitzer dieser Mine ein gewisser Lawrence Beltrope aus Port Royal ist.";
			link.l1.go = "mine_attack_41";
		break;
		
		case "mine_attack_41":
			dialog.text = "Ach wirklich? Lass mich diese Dokumente sehen...";
			link.l1 = "Hier, bitte.";
			link.l1.go = "mine_attack_42";
		break;
		
		case "mine_attack_42":
			RemoveItems(pchar, "letter_mine", 1);
			dialog.text = "(liest)... Gut... Beltrope? Ich kenne diesen Nachnamen von irgendwoher. Oh, ja! Thomas Beltrope! Das ist interessant... Gut, ich werde das überprüfen, wenn ich nach Blueweld zurückkehre. Ich behalte diese Dokumente bei mir, wenn es Ihnen nichts ausmacht?";
			link.l1 = "Überhaupt nicht. Ich brauche sie für nichts.";
			link.l1.go = "mine_attack_43";
		break;
		
		case "mine_attack_43":
			dialog.text = "Gut. Nun bleibt der beste Teil übrig, ich werde das Silber zu den Schiffen transportieren. Die Miskitos werden uns dabei helfen. Wir stellen einen Wagen zusammen... In der Zwischenzeit, ruhe dich einfach aus, "+pchar.name+". Du hast es mehr als jeder andere verdient!";
			link.l1 = "Danke, Jan. Wir werden auf diesem Hügel ein Lager aufschlagen, der Geruch von Asche ist zu stark. Ja, und wir müssen die Feuer in diesen Hütten löschen, wer weiß, vielleicht werden sie uns in der Zukunft nützlich sein...";
			link.l1.go = "mine_attack_44";
		break;
		
		case "mine_attack_44":
			dialog.text = "Denkst du daran, die Mine zu beanspruchen? Ha-ha! Ich habe bereits mit dem Gedanken gespielt, aber Plündern ist eine Sache, es als Eigentum zu nehmen eine andere. Freund, es hat bereits einen Besitzer. Wir könnten Ärger mit den englischen Behörden bekommen.\nAußerdem haben mir die Sklaven, mit denen ich gesprochen habe, erzählt, dass hier alle Adern im Grunde genommen aufgebraucht sind - große Mengen Silber wurden hier schon mehrere Male weggebracht. Ich fürchte, diese Mine ist erledigt.";
			link.l1 = "Hm... Wir werden sehen. Vielleicht ist noch nicht alles erschöpft. Gut, ich sollte wirklich etwas Ruhe nehmen. Bis später, Jan";
			link.l1.go = "mine_attack_45";
		break;
		
		case "mine_attack_45":
			dialog.text = "Geh voran. Und sorge dich um nichts. Wir kümmern uns selbst um alles andere.";
			link.l1 = "...";
			link.l1.go = "mine_attack_46";
		break;
		
		case "mine_attack_46":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "attack1", "Saga_MineWaitTime", -1);
			n = Findlocation("mine");
			DeleteAttribute(&locations[n], "hidden_sound");
			DeleteAttribute(&locations[n], "hidden_fire");
			n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "models.always.Gun1");
		break;
		
		case "mine_attack_47":
			dialog.text = "Hattest du eine gute Ruhe, "+pchar.name+"?";
			link.l1 = "Es war nicht schlecht... Obwohl, ehrlich gesagt, ich würde töten, um eine Taverne zu finden, einen Drink zu bekommen und in einem sauberen Bett zu schlafen.";
			link.l1.go = "mine_attack_48";
		break;
		
		case "mine_attack_48":
			dialog.text = "Die Indianer haben das Silber an die Küste geliefert und laden es unter Aufsicht meiner Offiziere auf dein Schiff. Du kannst schon zurückkehren. Dein Wunsch nach Rum, einer Taverne und einem Bett wird bald in Erfüllung gehen. Und ich möchte, dass du in fünf Tagen in meinem Haus vorbeischaut, wir haben noch viel zu tun.";
			link.l1 = "Also gut, Jan. Wir sehen uns in fünf Tagen in Blueweld! Viel Glück!";
			link.l1.go = "mine_attack_49";
		break;
		
		case "mine_attack_49":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4", "none", "", "", "", 15.0);
			LocatorReloadEnterDisable("shore53", "boat", false);
			LocatorReloadEnterDisable("mine", "reload1", false);
			LocatorReloadEnterDisable("mine", "reload6", false);
			LocatorReloadEnterDisable("mine_01", "reload3_back", false);
			LocatorReloadEnterDisable("mine_exit", "reload2_back", false); //открыть выходы с рудника
			LAi_LocationDisableOfficersGen("mine_mines", false); // офицеров пускать
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			SetFunctionTimerCondition("Saga_ReturnFromMine", 0, 0, 5, false); // таймер
			pchar.questTemp.Saga.Mines = "true"; // после Саги рудник будет разрабатываться
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			DoQuestReloadToLocation("Shore53", "goto", "goto6", "");
		break;
		// <-- штурм рудника
		
		case "helensleep":
			dialog.text = "";
			link.l1 = "Jan, schrei mich nicht an. Lassen wir die Dinge wie vernünftige Leute klären - denk daran, wir haben Geschäfte zu machen!";
			link.l1.go = "helensleep_1";
		break;
		
		case "helensleep_1":
			dialog.text = "Ich setze meine Hunde sofort auf dich an, du Kröte! Vergiss Levasseur und verschwinde!";
			link.l1 = "Jan! Hör mir zu...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenSleep_SvensonThrowOut");
		break;
		
		case "after_drinking":
			dialog.text = "Welches Fass? Was Helen betrifft, ich werde ihr sicherlich eine gute Tracht Prügel geben... Nur ein Scherz, Charles, nur ein Scherz! Ich weiß, wie das läuft, und was Joanna betrifft - diese Geschichte wird sie hoffentlich ein wenig zum Nachdenken bringen - sie war in letzter Zeit besonders launisch, weißt du... Nun, so ist das Leben. Jedenfalls wünsche ich dir viel Glück in Cartagena!";
			link.l1 = "Bis wir uns wiedersehen, Jan.";
			link.l1.go = "exit";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
