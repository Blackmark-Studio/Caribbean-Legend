// диалог официантки
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk1, bOk2;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Waitress.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bOk1 = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (sti(pchar.rank) > 6 && npchar.location == "PortSpein_tavern" && !CheckAttribute(npchar, "quest.Consumption")  && bOk1)
				{
					dialog.text = "¿Qué desea, señor? Lo siento, solo estoy...(llora)... oh... Lo siento.";
					link.l1 = "¿Por qué estás tan molesta, señorita? ¿Lágrimas en una cara tan hermosa? ¿Qué ha sucedido?";
					link.l1.go = "Consumption";
					break;
				}
			}
			//<-- Цена чахотки
			
			// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
			if (npchar.location == "PortPax_tavern" && CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin")
            {
				DelMapQuestMarkCity("PortPax");
				DelLandQuestMark(npchar);
				PlaySound("Voice\Spanish\Enc_RapersGirl_1.wav");
				dialog.text = "¡Señor! ¡Señor, ayuda! ¡Asesinato!";
				link.l1 = "¿Eh? ¿Asesinato? ¿Dónde? ¿Es esto una broma, señorita?";
				link.l1.go = "FMQP";
				break;
			}
			
			//--> Тайна Бетси Прайс
			if (npchar.location == "Villemstad_tavern" && CheckAttribute(pchar, "questTemp.TBP_BetsiPrice") && !CheckAttribute(pchar, "questTemp.TBP_BetsiPrice_Sex"))
			{
				bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
				bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
				if (bOk1 || bOk2)
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+"! Qué gusto verte de nuevo... Gracias por pasar... pero ahora no es el mejor momento para conversar. Vuelve cuando estés solo. Entonces podremos hablar... de asuntos más personales.";
							link.l1 = "Siempre es un placer charlar, pero debo irme. Tal vez nos veamos otra vez.";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+"... Empezaba a pensar que habías olvidado el camino a nuestra taberna. Qué pena que no estés solo. Esperaba poder hablar contigo en privado.";
							link.l1 = "Creo que el destino aún nos dará una oportunidad de hablar a solas.";
							link.l1.go = "exit";
						break;
					}
				}
				else
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+"! Sabía que no me harías esperar mucho. Ya no quiero perder ni un minuto. La habitación de arriba está libre... solo para nosotros dos. ¿No vas a rechazarme, verdad?";
							link.l1 = "Sabes cómo atraparme... Bueno, no tengo razones para resistirme. ¿Subimos?";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "Me temo que hoy tengo cosas importantes que atender. Pero te prometo que la próxima vez lo compensaré.";
							link.l2.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+"! Ya empezaba a pensar que disfrutas haciéndome esperar. ¿De verdad vas a quedarte ahí parado como una estatua cuando hay formas mucho más agradables de pasar el tiempo?";
							link.l1 = "Es imposible resistirse a tus encantos... No voy a perder ni un segundo – subo ahora mismo.";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "Eres toda una seductora, Betsy... Pero lamentablemente ahora tengo que estar en otro sitio.";
							link.l2.go = "exit";
						break;
					}
				}
				link.l9 = "Quiero hacerte un par de preguntas.";
				link.l9.go = "quests";
				break;
			}
			//<-- Тайна Бетси Прайс
            NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.different.FackWaitress"))
			{
				if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackWaitress_toRoomUp")
				{
					dialog.text = "Te he pedido que subas. No te quedes aquí llamando la atención.";
					link.l1 = "Bien, me voy, no quiero comprometerte...";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_noMoney" || pchar.questTemp.different == "FackWaitress_fighted")
				{
					dialog.text = "Soy nueva aquí, así que por favor, no me distraiga de mi trabajo. Todavía no me acostumbro...";
					link.l1 = "¿Y dónde está la camarera que trabajaba aquí antes que tú? "+pchar.questTemp.different.FackWaitress.Name+", creo recordar...";
					link.l1.go = "Love_IDN";
				}
				if (pchar.questTemp.different == "FackWaitress_facking")
				{					
					dialog.text = "Vuelve otra vez, cariño. Podríamos divertirnos de nuevo. Si tuviera más tiempo libre...";
					link.l1 = "¡Claro que lo haré, estuviste genial!";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_fackNoMoney")
				{					
					dialog.text = "No le conozco de nada, así que no me moleste...";
					link.l1 = "¿Dónde está mi dinero?!!";
					link.l1.go = "Love_IDN_1";
				}
				break;
			}
		    switch (Rand(4))
			{
				case 0:
					dialog.text = "Lo siento, "+GetSexPhrase("guapo","belleza")+", estoy demasiado ocupada ahora mismo. Es un buen momento para la taberna, ¡pero no para las charlas!";
					link.l1 = "...";
					link.l1.go = "exit";
				break;

				case 1:
					dialog.text = "Por favor, capitán, ¡no se pelee con nadie aquí! Es un trabajo duro limpiar este lugar.";
					link.l1 = ""+GetSexPhrase("Hm... No pretendía hacerlo de igual forma.","¿Parezco un borracho buscando pelea? Solo soy una chica, igual que tú, no te preocupes.")+"";
					link.l1.go = "exit";
				break;

				case 2:
					if (hrand(1) == 0) // Addon-2016 Jason
					{
						dialog.text = ""+GetSexPhrase("¡Oh, capitán! ¿Le gustaría compartir cama conmigo hoy? No me gusta presumir pero...","Toma asiento, capitán. Siempre es un placer conocer a un verdadero lobo de mar como usted.")+"";
						link.l1 = "Qué lástima que tenga prisa. ¡Será para la próxima!";
						link.l1.go = "exit";
						bool bOk = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) || npchar.city == GetLadyBethCity(); // 291112
						if (pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackWaitress") && PChar.sex != "woman" && pchar.GenQuest.EncGirl != "HorseToTavern" && !bOk)
						{
							link.l2 = "¡Con mucho gusto, cariño!";
							link.l2.go = "Love_1";
						}
					}
					else
					{
						dialog.text = "Tome asiento, capitán. Pruebe nuestro ron, juegue una partida de cartas o dados. ¡Siéntase como en casa! Siempre es un placer conocer a un verdadero lobo de mar como usted.";
						link.l1 = "Gracias, linda.";
						link.l1.go = "exit";
					}
				break;

				case 3:
					dialog.text = "Hable con el maestro si quiere pedir algo. Está detrás del mostrador del bar.";
					link.l1 = "Gracias por el consejo.";
					link.l1.go = "exit";
				break;

				case 4:
					dialog.text = "Si quiere descansar y recuperar su salud, alquile una habitación entonces. Pasar toda la noche en el salón no le ayudará mucho.";
					link.l1 = "Te lo agradezco.";
					link.l1.go = "exit";
				break;
			}			
			link.l9 = "Quiero hacerte unas preguntas.";
			link.l9.go = "quests";//(перессылка в файл города)
		break;
		
        case "Love_1":
			dialog.text = "Entonces, escuche. Alquile una habitación aquí en la taberna. Vaya y espéreme ahí. Me escabulliré allí un poco más tarde...";
			link.l1 = "¡Ja! ¡Lo haré, cariño! ¡Te estaré esperando!";
			link.l1.go = "exit";
			pchar.questTemp.different = "FackWaitress_toRoom";
			SetTimerFunction("WaitressFack_null", 0, 0, 1); //освобождаем разрешалку на миниквесты на след. день
			//Шанс, что ограбят, если рендом выпадет на 0. он же делитель сколько она вытащит из кармана
			pchar.questTemp.different.FackWaitress.Kick = hrand(2); 
			pchar.questTemp.different.FackWaitress.Name = GetFullName(npchar); //запомним имя официантки
			pchar.questTemp.different.FackWaitress.City = npchar.city;
			//делаем клона официантки
			sld = GetCharacter(NPC_GenerateCharacter("WairessQuest", npchar.model, "woman", npchar.model.animation, 5, sti(npchar.nation), 3, false, "citizen"));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.dialog.Filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "Waitress";	
			Pchar.quest.WaitressFack_inRoom.win_condition.l1 = "location";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.WaitressFack_inRoom.function = "WaitressFack_inRoom";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
		break;
		
        case "Love_IDN":
			dialog.text = "Ella ya no trabaja aquí, se ha retirado... Lo siento, tengo mucho trabajo que hacer.";
			link.l1 = "Bien...";
			link.l1.go = "exit";
		break;
		
        case "Love_IDN_1":
			dialog.text = "Escucha bien, idiota lujurioso. ¡No sé dónde está tu dinero! Y si sigues presionándome, llamaré a los guardias y te enviarán a prisión!";
			link.l1 = "Bien, no se necesitan guardias... Que tonto he sido...";
			link.l1.go = "Love_IDN_2";
		break;
		
        case "Love_IDN_2":
			dialog.text = "Exactamente, tal tonto. La próxima vez serás más inteligente y decente.";
			link.l1 = "Lo intentaré... (susurrando) Cortesana de mierda...";
			link.l1.go = "exit";
		break;

		case "without_money":
			NextDiag.TempNode = "first time";
			dialog.text = "¿Puede oírme?";
			link.l1 = "Ughh...";
			link.l1.go = "without_money_2";
		break;

		case "without_money_2":
			dialog.text = "¿Se siente mal? ¿Tiene dolor de cabeza?";
			link.l1 = "Maldición... ¿dónde estoy?";
			link.l1.go = "without_money_3";
		break;

		case "without_money_3":
			dialog.text = "¿No lo recuerda? Le han robado.";
			link.l1 = "¿Qué? Oh... Mi cabeza... ¡¿Quién se atrevería?!";
			link.l1.go = "without_money_4";
		break;

		case "without_money_4":
			dialog.text = "¿Cómo debería saberlo? Entraron a la fuerza, amenazaron con matar a todos, revisaron sus bolsillos y se fueron.";
			link.l2 = "Ya veo... Mierda... Me gustaría un poco de agua... Gracias.";
			link.l2.go = "exit";
		break;
		
		//--> Jason Цена чахотки
		case "Consumption":
			npchar.quest.Consumption = "true";
			dialog.text = "No, no es nada, señor... gracias por su amabilidad pero yo ... (llora)";
			link.l1 = "¿Alguien te ha ofendido? Calma, preciosa, cuéntamelo todo.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "No, no, señor, no es nada. Perdóneme por mi falta de contención, es solo que... Es mi hermano, dicen que está muerto, pero no lo creo. No sé qué creer, pero siento con mi propio corazón que está en grandes aprietos. Y no tengo a nadie más que a Angelo después de que nuestros padres murie... (llora)";
			link.l1 = "Entiendo, pero te pido que te calmes, por favor. ¿Qué le sucedió a tu hermano?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "Señor... por favor no me malinterprete, pero ¿por qué debería importarle a un capitán tal, una chica ordinaria y modesta de la taberna? Ni siquiera tengo nada que prometerle por su ayuda...";
			link.l1 = "De hecho, tienes razón. La abnegación no es para mí, así que sé fuerte, todos perdemos a nuestros seres queridos. C'est la vie como decimos en Francia...";
			link.l1.go = "exit";
			link.l2 = "Una mujer siempre puede encontrar una forma de agradecer a un hombre.... Ja-ja. Ahora, solo deja de llorar y cuéntame sobre tu problema.";
			link.l2.go = "Consumption_3_1";
			link.l3 = "Joven señorita, ¿no le han informado que nuestra Iglesia nos enseña a ayudarnos mutuamente? Intentaré ayudarte si puedo hacerlo, por supuesto.";
			link.l3.go = "Consumption_3_2";
		break;
		
		case "Consumption_3_1":
			if(sti(pchar.reputation.nobility) > 36)
			{
				dialog.text = "¿Fue una 'pista'? ¡Disculpe, fue mi error hablar con usted! Adiós 'caballero'...";
				link.l1 = "Como desees, cariño.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Bueno, entonces... Al menos es honesto en sus deseos. Le prometo que si encuentra a Angelo, o me dice lo que realmente le sucedió, obtendrá lo que pide...";
				link.l1 = "Querida señorita, es un placer hacer negocios contigo... Ahora vayamos directo a la historia de tu hermano.";
				link.l1.go = "Consumption_4";
				npchar.quest.Consumption.sex = "true";
			}
		break;
		
		case "Consumption_3_2":
			dialog.text = "¿Está bromeando? ¿Realmente quiere ayudarme gratis?";
			link.l1 = "Solo un mal hombre no ayudaría a una niña llorando. No te preocupes, realmente quiero ayudarte. ¿Qué le pasó exactamente a Angelo?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Muy bien, señor. Mi hermano, él... oh, no es fácil contener las lágrimas para mí, lo siento mucho... Estábamos realmente pobres debido a mi... modestia en el trabajo, quizás... Y Angelo comenzó a trabajar con los contrabandistas locales. Pensó que, con su pequeño bote de pesca ganaría más dinero transportando algo para evitar las aduanas.";
			link.l1 = "Para decirlo en palabras más simples, ¿tu hermano se convirtió en un criminal, verdad?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "No, señor, no entiendes... ¡él no es así! ¡Lo hizo por mí! Para salvarme de ganar dinero extra aquí... ya sabes a lo que me refiero. Estábamos endeudados y lo hizo por mi honor y mi alma. Y luego... fue atrapado. No fue un gran problema, incluso pedí más dinero prestado para pagar su liberación... Pero dijeron que murió.";
			link.l1 = "¿Ellos dijeron eso? ¿Quién ha sido? ¿Y por qué no les crees? ¿Murió en una prisión?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "Sí. Cuando llevé dinero para pagar su liberación, el comandante me dijo que Angelo murió de tuberculosis. ¡Imagínate! Llegó allí en buen estado de salud y murió dos semanas después justo en esas celdas. Ellos... ni siquiera me permitieron ver el cuerpo. Dijeron que enterraron a los prisioneros justo en la bahía cerca del fuerte para evitar una epidemia.";
			link.l1 = "¿Una epidemia? Suena muy cierto. Entonces, ¿simplemente no quieres creer en ello o tienes razones más serias?";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			dialog.text = "¡No... No! (llora) Sé que suena estúpido, pero estoy segura de que lo sabría si él muriera. Verás, Angelo siempre fue fuerte, un verdadero marinero. Pero hay una cosa más\nMi abuelo murió de consunción cuando era niño y él, un viejo, había estado luchando contra su enfermedad durante años. Sé cómo funciona, la consunción, no mata a la gente en días, ¡créeme!";
			link.l1 = "Hm... Tú también me has hecho dudar, algo está muy mal aquí. No puedo prometerte nada, pero intentaré averiguar más.";
			link.l1.go = "Consumption_8";
		break;
		
		case "Consumption_8":
			dialog.text = "¡Incluso una promesa simple es mucho más de lo que esperaba! ¡Eres tan amable, señor! ¡Estaré esperando aquí!";
			link.l1 = "¡Oh, la juventud! Tan inconstante en sentimientos... ¿Serías tan amable de devolverme mi mano, belleza?, aún la necesito ja-ja... Muy bien entonces, iré a averiguar qué es lo que sucede.";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			DialogExit();
			npchar.dialog.filename = "Quest\LineMiniQuests\Consumption.c";
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Consumption = "begin";
			AddQuestRecord("Consumption", "1");
		break;
		//<-- Цена чахотки
		
		// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
		case "FMQP":
			dialog.text = "¡No, no es broma! ¡Arriba! ¡Dos matones están asesinando a un noble caballero! ¡Ayúdele, capitán, eres el único hombre armado aquí!";
			link.l1 = "¡Corre afuera, llama a los guardias! ¡Voy a subir!";
			link.l1.go = "FMQP_1";
			link.l2 = "Querida, debes haberme confundido con un guardia. Llama a una patrulla en caso de asesinato.";
			link.l2.go = "FMQP_exit";
		break;
		
		case "FMQP_exit":
			dialog.text = "¡A-ah, guardias! ¡Ayúdenme!";
			link.l1 = "...";
			link.l1.go = "FMQP_exit_1";
		break;
		
		case "FMQP_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
			LocatorReloadEnterDisable("Portpax_town", "reload4_back", true);
			SetFunctionTimerCondition("FMQP_Remove", 0, 0, 1, false);
		break;
		
		case "FMQP_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			pchar.quest.FMQP_room.win_condition.l1 = "locator";
			pchar.quest.FMQP_room.win_condition.l1.location = "Portpax_tavern";
			pchar.quest.FMQP_room.win_condition.l1.locator_group = "reload";
			pchar.quest.FMQP_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.FMQP_room.function = "FMQP_InRoom";
		break;
	}
}
