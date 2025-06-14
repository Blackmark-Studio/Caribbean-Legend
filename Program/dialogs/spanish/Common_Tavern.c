#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
#include "interface\ship.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	int iTest, iTemp;
	string sTemp;
	string NPCCity = NPChar.City;
    iTest = FindColony(NPChar.City); // город 
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;
	
	if(!CheckAttribute(pchar, "questTemp.TavernVisit."+(NPCCity) )) 
	{
		pchar.questTemp.TavernVisit.(NPCCity) = true;
		pchar.questTemp.TavernVisit.counter = sti(pchar.questTemp.TavernVisit.counter) + 1;
		notification("Primera visita a la taberna " + XI_ConvertString(NPCCity + "TavernName"), "Drunk");
		AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 10.0);
	}	
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("La alarma se ha levantado en la ciudad, y todos te están buscando. Si yo fuera tú, no me quedaría aquí.","Todos los guardias de la ciudad están peinando la ciudad en busca de ti. ¡No soy un tonto y no hablaré contigo!","Huye, "+GetSexPhrase("compañero","chica")+", antes de que los soldados te conviertan en picadillo..."),LinkRandPhrase("¿Qué necesitas, "+GetSexPhrase("apestoso","granuja")+"? ¡Los guardias de la ciudad tienen tu olor, no llegarás lejos"+GetSexPhrase(", pirata asqueroso",", asquerosa pirata")+"!","¡Asesino, abandona mi lugar de inmediato! ¡Guardias!","No tengo miedo de ti, "+GetSexPhrase("granuja","rata")+". ¡Pronto serás colgado en nuestro fuerte, no llegarás lejos!"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Je, una alarma nunca es un problema para mí...","Nunca me atraparán."),RandPhraseSimple("Cierra tu boca, "+GetWorkTypeOfMan(npchar,"")+", o te arrancaré la lengua!","Je, "+GetWorkTypeOfMan(npchar,"")+", y todos allí, ¡a atrapar piratas! Eso es lo que te digo, compañero: siéntate tranquilo y no morirás..."));
				link.l1.go = "exit";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("¡Y eres tú, canalla! ¿Crees que te estamos sirviendo ron aquí? ¡Ciertamente no! ¡Chicos! ¡A las armas! ¡Matad a este bribón!","¿Quieres una bebida, pirata? ¡Ja! ¡No! ¡Ahora te mostraremos de qué estamos hechos! ¡Chicos, desenvainad vuestros sables!");
				link.l1 = RandPhraseSimple("¿Eh? ¿Qué?","¡Alto!");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//Jason, Бремя гасконца
			if(NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
				{
					link.l1 = "Señor, estoy buscando trabajo. ¿Tiene algún trabajo?";
					link.l1.go = "Sharlie_rum";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
				{
					link.l1 = "He cumplido con tu encargo. La lancha larga con el ron ha sido entregada en la Bahía de Le Francois y entregada a tu gente.";
					link.l1.go = "Sharlie_rum_5";
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "crew" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				dialog.text = "¿Querías algo, señor?";
				Link.l1 = "Hola tabernero, necesito contratar una tripulación para mi barco. ¿Puedes ayudarme con eso?";
				Link.l1.go = "Sharlie_crew";
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "skiper" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Hola de nuevo. ¿Qué es esta vez, señor?";
				Link.l1 = ""+npchar.name+", Me doy cuenta de que te estoy molestando, pero solo una pregunta más. Necesito un navegante, ¿alguna idea de dónde puedo encontrar uno?";
				Link.l1.go = "Sharlie_skiper";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
    			dialog.text = "¿Qué es lo que deseas, señor?";
				Link.l1 = "Esperaba que pudieras responder un par de preguntas.";
				Link.l1.go = "quests";
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l2 = "Me gustaría alquilar una habitación.";
					link.l2.go = "room";
				}
				break;
			}			
			//Бремя гасконца
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "tavern" && npchar.city == "Tortuga")
			{
				dialog.text = "¡Encantado de verte, señor! ¿Cómo puedo servirte? ¿Ron, brandy, whisky escocés?";
				Link.l1 = "Quisiera una botella de su mejor vino francés y una llave de habitación.";
				Link.l1.go = "mtraxx_tortuga";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "room" && npchar.city == "Tortuga")
			{
				dialog.text = "Ya ha pagado señor, su habitación está arriba.";
				Link.l1 = "Gracias.";
				Link.l1.go = "exit";
				break;
			}
			
			// Sinistra - Квест "Длинные тени старых грехов" ==>	
			if (CheckAttribute(pchar, "questTemp.DTSG_BasTerTavern") && npchar.city == "BasTer")
			{
				dialog.text = "¿Cómo puedo servirle, Capitán? Probablemente quiera una bebida después de lo que pasó.";
				Link.l1 = "Eso puede esperar. En realidad, quiero discutir lo que pasó.";
				Link.l1.go = "DTSG_BasTerTavern_1";
				DelLandQuestMark(npchar);
				break;
			}
			// <== Квест "Длинные тени старых грехов" - Sinistra
			
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Start") && !CheckAttribute(pchar, "questTemp.TPZ_Tavern_1") && npchar.city == "BasTer")
			{
				dialog.text = "Mis disculpas, "+GetAddress_Form(NPChar)+", pero hoy no puedo ofrecerle ni una gota de licor.";
				Link.l1 = "¿En serio? ¿Y qué clase de taberna es esta donde ni siquiera pueden servir una gota de ron? ¿Me perdí"+GetSexPhrase("","a")+" una gran celebración que agotó sus existencias?";
				Link.l1.go = "TPZ_Tavern_1";
				pchar.questTemp.TPZ_Tavern_1 = true;
				DelLandQuestMark(npchar);
				break;
			}
			//<-- Торговля по закону

			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("Bienvenido a mi humilde taberna '"+XI_ConvertString(NPChar.City+"TavernName")+"', señor. Me alegra verte.","¡A su servicio, señor! En nuestra taberna '"+XI_ConvertString(NPChar.City+"TavernName")+"' siempre nos alegra dar la bienvenida a nuevos visitantes.","¿Primera vez aquí, señor? No dudes, aquí en '"+XI_ConvertString(NPChar.City+"TavernName")+"'¡siempre te sientes como en casa!"),LinkRandPhrase("Entra, señor capitán. No te reconozco, así que debe ser tu primera vez en '"+XI_ConvertString(NPChar.City+"TavernName")+"'.'","Nunca te he conocido antes, señor. Conozcámonos: Soy "+GetFullName(npchar)+", el posadero de '"+XI_ConvertString(NPChar.City+"TavernName")+"'.'","¡Me alegra dar la bienvenida a nuestro nuevo huésped, Monsieur Capitán! En mi taberna '"+XI_ConvertString(NPChar.City+"TavernName")+"'¡La primera bebida siempre corre por cuenta de la casa! Soy el dueño de este lugar, "+GetFullName(npchar)+", te da la bienvenida."),LinkRandPhrase("¡Señor Capitán! Bienvenido a la taberna '"+XI_ConvertString(NPChar.City+"TavernName")+"'!","¡Oh, qué brillante hidalgo ha visitado nuestra taberna '!"+XI_ConvertString(NPChar.City+"TavernName")+"¿Es tu primera vez aquí, señor?","Buenos días, señor! Soy "+GetFullName(npchar)+", humilde propietario de '"+XI_ConvertString(NPChar.City+"TavernName")+"'¡, estamos encantados de darle la bienvenida aquí!"),LinkRandPhrase("Hola, señor capitán. Soy el dueño de la taberna '"+XI_ConvertString(NPChar.City+"TavernName")+"'. ¿Es la primera vez que se queda con nosotros?","Buenas tardes, señor. Bienvenido a la taberna '"+XI_ConvertString(NPChar.City+"TavernName")+"'.'","¡Qué bueno verte, mi señor capitán! ¡Nuestra taberna '"+XI_ConvertString(NPChar.City+"TavernName")+"' te da la bienvenida! ¿Ron, vino, o si podría tentarte, tenemos un travieso nuevo espíritu holandés llamado ginebra?"));
				Link.l1 = LinkRandPhrase("Un lugar acogedor que tienes aquí... Permíteme presentarme, "+GetFullName(pchar)+", es un placer conocerte.",""+GetFullName(pchar)+", es un placer conocerte. Entonces, ¿qué puedes ofrecerme?","Mi nombre es "+GetFullName(pchar)+" y soy nuevo en este puerto. Dime, ¿por qué es más conocida esta taberna?");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_tavern")
				{
					dialog.text = "¡Ahoy, Rumba! ¿De vuelta de un viaje, o embarcándote en uno nuevo?";
					link.l1 = "Hola, "+npchar.name+". Solo decidí pasar.";
					Link.l1.go = "Helen_meeting";
					NPChar.quest.meeting = "1";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				// Квестовый генератор священника. Квест №1. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
		        {
		            if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToBarmen"))
		            {
		            	iTemp = sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen);
		            	dialog.Text = "Entonces, capitán, ¿me has traído los "+FindRussianMoneyString(iTemp)+"?";
		            	if(sti(PChar.Money) >= iTemp)
		            	{
							link.l1 = "Sí, los tengo. Aquí están...";
							link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
						}
						else
						{
							link.l1 = "No, aún no...";
							link.l1.go = "exit";
						}
		            }
		            else
		            {
		            	dialog.Text = "¿Qué te gustaría, mi buen "+GetSexPhrase("señor","señora")+"?";
						link.l1 = "Una botella de ron para mi compañero en esa mesa allá.";
						link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
					}
					break;
				}
				// <-- Квестовый генератор священника. Квест №1.
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("¡Oh, honorables invitados! Oye, hazte a un lado y haz espacio para un gallardo capitán! ¡Y date prisa, antes de que te eche, jaja!","¡Santo Dios misericordioso! Si no es "+GetFullName(pchar)+"¡Acabo de recibir un nuevo envío de los vinos más selectos, por favor entra!","¡Oh, "+GetAddress_Form(NPChar)+", ¿tienes problemas? ¿Me permites invitarte? Esta botella es por cuenta de la casa. Créeme, es el mejor vino de por aquí..."),LinkRandPhrase("¡Oh, es el Capitán "+GetFullName(pchar)+"¡Eh, tú! ¡Muestra algo de respeto al buen capitán! ¡Esto no es un establo! Disculpa, capi, claramente sus madres nunca les enseñaron modales.","Bien bien, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"¡Nos espera una larga noche, jaja! ¡Chicas, es mejor que llevéis vuestros mejores vestidos!","Buenas tardes, "+GetFullName(pchar)+", ¡Me alegra verte! Por favor señor, tengo una petición. Acabo de comprar mesas nuevas, así que por favor no peleen esta noche."),LinkRandPhrase("Hola, capitán. Siéntete como en casa, pero ten en cuenta que incluso el mismo Capitán Sharp se comporta con maneras en mi establecimiento.","¡O-ho-ho! ¿Mira quién está aquí? Es "+GetFullName(pchar)+" ¡él mismo! ¡Y justo empezábamos a aburrirnos en tu ausencia! ¿Qué tal si entretienes a los compañeros con una aventura mientras yo abro un nuevo barril de ron, capi?","¡O-ho-ho! Es "+GetFullName(pchar)+"¡Por Dios! Espero que no vayas a robar a mis clientes hacia los mares del norte de nuevo con las historias de tus grandiosas aventuras, ¿eh?")),LinkRandPhrase(LinkRandPhrase(""+GetFullName(pchar)+"¡Este viejo lobo de mar siempre está feliz de verte en su establecimiento! Por favor señor, tome asiento y las chicas se ocuparán de usted!","Por favor capitán, ¡póngase cómodo! Siempre contento de saludar a mi invitado favorito. ¿Cuál es tu veneno?","Encantado de verte de nuevo, "+GetFullName(pchar)+"¿Te gustaría una mesa para ti mismo? ¿O preferirías sentarte en la barra?"),LinkRandPhrase("Buenas tardes, capitán. Hay un frío en el aire, permíteme ofrecerte un excelente vino caliente que acabo de hacer, ¡por cuenta de la casa!","Hola, capitán "+GetFullName(pchar)+"¡Me alegra que hayas venido a visitar de nuevo. ¿Qué te gustaría?","Me alegra tenerte, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"¡Me alegro de que frecuentes mi humilde establecimiento! Hacemos todo lo posible para agradar."),LinkRandPhrase("¡Capitán! ¡Bienvenido, bienvenido! Tengo un magnífico d'Anjou digno del mismo Rey Luis y lo he guardado especialmente para ti!",""+GetFullName(pchar)+"¡Estoy tan contento de que hayas venido! ¿Debo echar a todas estas ratas de mar o prefieres que se queden? Créeme, con gusto despejaría toda la taberna para ti!","Por Dios, aquí está el Capitán "+GetFullName(pchar)+"¡Eh, coquetos, llevad el mejor mantel a la mesa del capitán!")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Oh, veo que me recuerdan aquí... Avast, llena mi vaso amigo, mientras echo un vistazo alrededor...","Cálmate, amigo, hoy estoy de buen humor. Empecemos con ron, ¿no?..."),RandPhraseSimple("¡Oh... no estás muy contento de tenerme aquí? Espero haberte oído mal, ¡ja!","Ahoy. ¿Espero que tu vino sea mejor que tu saludo? De lo contrario, puedo enfadarme, ¿sabes?")),RandPhraseSimple(RandPhraseSimple("Siempre contento de visitarte, compadre. ¿Qué tienes para calentar a un perro salado?","¡Ahoy compañero, tu establecimiento mejora con cada día que pasa! Venir a visitar aquí siempre es un placer..."),RandPhraseSimple("¿No has olvidado a un viejo vagabundo? Estoy halagado, compañero.","Bueno ver a un viejo amigo de nuevo... ¿Todavía te queda algo de ron?")));
				Link.l1.go = "step_node";
			}
			break;
				
			case "step_node":
				dialog.Text = LinkRandPhrase("Estoy escuchando, capitán.","Mi taberna '"+XI_ConvertString(NPChar.City+"TavernName")+"' a su servicio, ¡Capitán!","¡Todo oídos, Capitán! ¿Qué te gustaría hoy?");
				Link.l1 = "¿Hay chicos en la isla listos para probar su suerte en los mares?";
				Link.l1.go = "crew hire";
				Link.l2 = "Esperaba que pudieras responder un par de preguntas.";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "Me gustaría hablar sobre asuntos financieros.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		            	{
					link.l10 = LinkRandPhrase("¿Puedes contarme algo sobre el reciente robo en la iglesia?","¿Qué sabes sobre el reciente robo en la iglesia?","¿Has oído algo sobre el reciente robo en la iglesia?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "La gente dice que tú sabes casi todo en esta colonia. Quiero comprar "+pchar.GenQuest.Device.Shipyarder.Type+", y me dijeron que se había vendido en tu pueblo. Bueno, alguien lo estaba vendiendo en el mercado callejero. ¿Puedes contarme algo al respecto?";
					link.l16.go = "Device_Tavern";
				}
				// <-- генератор Неудачливый вор
			
				//Jason --> генератор Место под солнцем
				if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
				{
					link.l17 = "Buscando a un mafioso con el nombre de "+pchar.GenQuest.Sunplace.Trader.Enemyname+". ¿Dónde puedo encontrarlo?";
					link.l17.go = "Sunplace_Tavern";
				}
				// <-- генератор Место под солнцем
			
				// --> Голландский гамбит
				if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Hola, "+npchar.name+". Necesito encontrar a Jacob van Berg, ¿dónde está? No lo veo en tu taberna...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Hola, "+npchar.name+". Estoy buscando a un caballero de nombre Fernando Rodriguez. ¿Apareció en tu ciudad?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				// <-- Голландский гамбит
			
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "Vine a recoger mis ganancias, que se guardaron seguras contigo."+npchar.name+".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
			
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "Me estaba preguntando dónde puedo encontrar a un hombre llamado "+pchar.GenQuest.Marginpassenger.q2Name+"¿Vive en tu pueblo?";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l3 = pcharrepphrase("¿Tienes una habitación libre, compañero?","¿Tienes una habitación libre?, me quedaré aquí por un tiempo.");
					link.l3.go = "room";
				}
				Link.l4 = "Vaya, ya me estoy yendo, "+NPChar.name+". Hasta luego.";
				Link.l4.go = "exit";
		break;
		
		case "Helen_meeting":
			dialog.Text = "Ah, bueno, entra, entra. Siempre eres bienvenido aquí.";
			link.l1 = "Sí, gracias. Fue un placer verte. Adiós.";
			link.l1.go = "exit";
			Link.l2 = "Podría usar algunas manos nuevas. Solo asegúrate de que sean capaces, ¿vale?";
			Link.l2.go = "crew hire";
			link.l3 = "Me gustaría descansar en tierra firme y recoger mis pensamientos, no cuando mi madre está alborotando por la casa.";
			link.l3.go = "Helen_room";
			Link.l4 = "¿Podría preguntarte algo? ";
			Link.l4.go = "quests";
			link.l5 = " Tengo un asunto que discutir contigo, "+NPChar.name+".";
			link.l5.go = "Helen_rumours_tavern";
		break;
		
		case "Meeting":
			// Квестовый генератор священника. Квест №1. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
	        {
	            dialog.Text = "¿Qué te gustaría, amable "+GetSexPhrase("señor","señora")+"?";
				link.l1 = "Una botella de ron para mi compañero de mesa en esa mesa allí.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
				break;
			}
			// <-- Квестовый генератор священника. Квест №1.
			dialog.Text = LinkRandPhrase("Estoy escuchando, capitán.","¿Qué puedo ofrecerte, capitán?","¿Entonces capi, qué va a ser?");
			Link.l1 = "Necesito una tripulación, "+NPChar.name+".";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name+", hablemos un rato...";
			Link.l2.go = "int_quests";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = "Me gustaría hablar sobre asuntos financieros.";
				link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
			}
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	        {
				link.l10 = LinkRandPhrase("¿Puedes contarme algo sobre el reciente robo en la iglesia?","¿Qué sabes sobre el reciente robo en la iglesia?","¿Has oído algo sobre el reciente robo en la iglesia?");
				link.l10.go = "Tavern_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "La gente dice que tú sabes casi todo en esta colonia. Quiero comprar "+pchar.GenQuest.Device.Shipyarder.Type+", y me dijeron que se había vendido en tu pueblo. Bueno, alguien lo estaba vendiendo en las calles. ¿Puedes contarme algo sobre eso?";
				link.l16.go = "Device_Tavern";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
			{
   				link.l17 = "Dime acerca de un mafioso con el nombre de "+pchar.GenQuest.Sunplace.Trader.Enemyname+". ¿Dónde puedo encontrarlo?";
				link.l17.go = "Sunplace_Tavern";
			}
			// <-- генератор Место под солнцем
			
			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Hola, "+npchar.name+". Necesito encontrar a Jacob van Berg, ¿dónde está? No lo veo en tu taberna...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Hola, "+npchar.name+". Estoy buscando a un caballero llamado Fernando Rodriguez. ¿Apareció en tu ciudad?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				//<-- Голландский гамбит
				
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "Vine a cobrar mis ganancias, que están guardadas de forma segura contigo."+npchar.name+".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "Me estaba preguntando dónde puedo encontrar a un hombre llamado "+pchar.GenQuest.Marginpassenger.q2Name+"¿Vive en tu ciudad?";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
			if(!CheckAttribute(pchar,"questTemp.TimeLock"))
			{
				link.l3 = pcharrepphrase("¿Tienes una habitación libre, compañero?","¿Tienes una habitación libre, me quedaría aquí por un tiempo?");
				link.l3.go = "room";
			}
			Link.l4 = "Supongo que volveré más tarde.";
			Link.l4.go = "exit";
		break;
		
		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;
			
			if (!ok)
			{
				Dialog.text = "¿Y para qué necesitarías marineros, capitán? No veo tu barco en el puerto.";
				link.l1 = RandPhraseSimple("Exactamente... Había atracado en el lugar equivocado.","Olvidé entrar al puerto...");
				link.l1.go = "exit";
				break;
			}
			
            if (makeint(environment.time) > 22.0 || makeint(environment.time) < 7.0)
			{
				Dialog.text = "Por lo general, hay muchos hombres buscando convertirse en marineros, pero ahora es demasiado tarde, empezarán a aparecer en la mañana. ¿Quizás te gustaría alquilar una habitación y esperarlos?";
				link.l1 = "Está bien. ¿Tenéis habitaciones libres?";
				link.l1.go = "room";
				link.l2 = "No me interesa una habitación en este momento. Nos vemos.";
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = "¿Crees que servimos a criminales buscados aquí? Agradece que no estoy llamando a los guardias.";
					link.l1 = "Gracias.";
					link.l1.go = "exit";
                }
                else
                {
					if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
					{
						Dialog.text = "Ah, lo siento capitán, llegas un poco tarde. Todos los muchachos que buscaban navegación ya zarparon con el gallardo capitán Blackwood.";
						link.l1 = "¡Qué lástima!";
						link.l1.go = "exit";
						break;
					}
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 3 && GetCrewQuantity(rColony) == 0)
					{
						Dialog.text = "Ah, lo siento capitán, llegas un poco tarde. Todos los muchachos que buscaban navegación ya zarparon con el gallardo capitán "+GetFullName(CharacterFromID(NPChar.CrewHired.PGGId))+".";
						link.l1 = "¡Qué lástima!";
						link.l1.go = "exit_crew";
					}
					else
					{						
						if(bPartitionSet)
						{		
							if(GetPartitionAmount("CrewPayment") > 0)
							{
								if(IsEquipCharacterByArtefact(pchar, "totem_07"))
								{
									DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
									NextDiag.CurrentNode =  NextDiag.TempNode;
									DialogExit();
									LaunchHireCrew();							
								}
								else
								{
									dialog.text = "Capitán, la gente dice que eres bastante tacaño. No tenemos a nadie aquí que quiera unirse a tu tripulación.";
									link.l1 = "Ya veo...";
									link.l1.go = "exit";
								}
							}
							else
							{
								DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
								NextDiag.CurrentNode =  NextDiag.TempNode;
								DialogExit();
								LaunchHireCrew();	
							}
						}	
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
							NextDiag.CurrentNode =  NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();							
						}						
					}
				}
			}
		break;
		
		case "exit_crew" :
			DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
			NextDiag.CurrentNode =  NextDiag.TempNode;
			DialogExit();
			LaunchHireCrew();
		break;
	////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////	
        case "int_quests":
			dialog.text = "Estoy todo oídos.";
			//link.l1 = "Estoy buscando trabajo. ¿Podrías ayudarme?";
			//link.l1.go = "work";
			//homo 15/06/06 слухи
			link.l2 = LinkRandPhrase("¿Puedes contarme las últimas noticias?","¿Qué está pasando en estas tierras?","¿Qué hay de nuevo en tierra?");
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = "Vine por un asunto diferente.";
			link.l3.go = "quests";
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "EncGirlFack_fighted")
				{
					link.l5 = "¿Sabes dónde puedo encontrar "+pchar.GenQuest.EncGirl.name+"?";
					link.l5.go = "EncGirl_1";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					link.l6 = "¿Puedes decirme dónde podría buscar a "+pchar.GenQuest.EncGirl.sLoverId+"?";
					link.l6.go = "EncGirl_3";
				}
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "tavern_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = "¡Ahoy, vengo por invitación de tu hijo!"; 
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.City && CheckAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern"))
			{
				if(pchar.GenQuest.CaptainComission.variant == "A0")
				{												
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Entonces, ¿has visto  "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = "¿Puedes decirme dónde debería buscar a "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_1";
					}
				}	

				if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					link.l9 = "¿Sabes dónde puedo encontrar al capitán de la patrulla '"+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+"', "+pchar.GenQuest.CaptainComission.Name+"?";
					link.l9.go = "CaptainComission_Tavern7";					
				}				
				if(pchar.GenQuest.CaptainComission.variant == "A3" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Entonces, ¿has visto a "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.CanoneerName,NAME_NOM)+"?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{					
						link.l9 = "¿Sabes algo sobre el capitán de la patrulla '"+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+"', "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_Tavern1";
						if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
						{
							pchar.GenQuest.CaptainComission.GetRumour = true;
							SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
						}	
					}	
				}					
			}
			if(CheckAttribute(pchar,"GenQuest.Hold_GenQuest") && NPChar.city == pchar.GenQuest.Hold_GenQuest.City && pchar.GenQuest.Hold_GenQuest.Speak_Tavern == false )
			{
				link.l10 = "¿Podrías decirme dónde puedo encontrar a un hombre llamado "+pchar.GenQuest.Hold_GenQuest.Name+"?";
				link.l10.go = "hold_genquest1";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakTavern") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l11 = "He encontrado por casualidad no muy lejos de aquí algunos documentos del barco....";
				link.l11.go = "ShipLetters_4";			
			}

			// Jason --> квест губера на поиск дезертира
			if(CheckAttribute(pchar, "GenQuest.FindFugitive") && pchar.GenQuest.FindFugitive != "Late" && sti(NPChar.nation) == PIRATE)
			{
				link.l12 = "Escucha, estoy buscando a un viejo amigo mío, "+pchar.GenQuest.FindFugitive.Name+" es su nombre. Un compañero capitán me dijo que se dirigía a tu asentamiento. ¿Lo has conocido por casualidad?";
				link.l12.go = "FindFugitiveTav";
			}
			//<-- поиск дезертира

			link.l15 = "Nada, gracias, .";
			link.l15.go = "exit";
		break;
		
		case "hold_genquest1":
			switch(sti(pchar.GenQuest.Hold_GenQuest.TavernVariant))
			{
				case 0:
					dialog.text = LinkRandPhrase("¿Qué has dicho? "+pchar.GenQuest.Hold_GenQuest.Name+"? Hmm... Nunca he oído hablar de él.","¿Estás seguro de que él proviene de nuestro pueblo? Nunca he oído hablar de tal persona.","No había nadie así en nuestra pequeña colonia. Nunca he oído hablar de él en todo mi tiempo aquí.");
					link.l1 = "¿Estás seguro?";
					link.l1.go = "hold_genquest2";					
				break;
				
				case 1: 
					switch (hrand(3))
					{
						case 0:
							pchar.GenQuest.Hold_GenQuest.foundStr = "la iglesia";						
							pchar.GenQuest.Hold_GenQuest.found = "church";
						break;
						case 1:
							if (npchar.city != "Panama")
							{
							pchar.GenQuest.Hold_GenQuest.foundStr = "el astillero";						
							pchar.GenQuest.Hold_GenQuest.found = "shipyard";
							}
							else
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "la iglesia";						
								pchar.GenQuest.Hold_GenQuest.found = "church";
							}
						break;
						case 2:
							pchar.GenQuest.Hold_GenQuest.foundStr = "el usurero";												
							pchar.GenQuest.Hold_GenQuest.found = "bank";
						break;
						case 3:
							pchar.GenQuest.Hold_GenQuest.foundStr = "la tienda";						
							pchar.GenQuest.Hold_GenQuest.found = "store";
						break;
					} 
					dialog.text = "Echa un vistazo "+pchar.GenQuest.Hold_GenQuest.foundStr+", se le puede encontrar allí bastante a menudo.";
					link.l1 = "Gracias, eso es justo lo que haré.";
					link.l1.go = "hold_genquest3";				
				break;
				
				case 2:
					dialog.text = LinkRandPhrase(RandPhraseSimple("¿Qué dijiste? "+pchar.GenQuest.Hold_GenQuest.Name+"¿Hmm... Nunca he oído hablar de él. ¿Estás seguro de que proviene de nuestro pueblo? Nunca he oído hablar de tal persona.","Je-je... Bueno, ahora sólo el Señor mismo sabe dónde buscarlo, en el infierno o en el cielo. Murió hace más de un año, pero la gente todavía pregunta por él... No hay descanso para el pobre desgraciado..."),RandPhraseSimple("No lo encontrarás allí, al menos no en el mundo de los vivos. Él murió hace poco, fiebre amarilla... Que Dios descanse su alma... ¡Qué hombre tan valiente solía ser! Cuando era joven, ¡era un gran aventurero! Pero cuando la muerte te persigue, no hay mucho que puedas hacer...","¡Oh, ¿le has echado de menos? Él dejó estos lugares hace mucho tiempo. Nadie sabe a dónde se fue: tal vez a las colonias norteamericanas, tal vez a casa a Europa. Simplemente recogió sus pertenencias y se largó."),"¡Oh, estás buscando eso "+pchar.GenQuest.Hold_GenQuest.Name+"¿quién se hizo rico y se compró una casa en Nueva Inglaterra? Sabes, hubo momentos en que le vendí ron a crédito, todavía me debe. La gente es tan ingrata, ya sabes.");
					link.l1 = "Ya veo. Bueno, gracias de todos modos.";	
					link.l1.go = "hold_genquest4";
				break;
				
				case 3:
					dialog.text = "¡Vaya!, ¿dónde más podría estar, sino en la taberna? Es un visitante frecuente allí, ahoga sus pecados en vino, je-je. Vuelve un poco más tarde, si aparece, le diré que te espere.";	
					link.l1 = "Gracias, lo haré.";
					link.l1.go = "hold_genquest5";
				break;
			}
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;
		break;
		
		case "hold_genquest2":
			dialog.text = "¿Cómo no voy a estar seguro si conozco personalmente a todos aquí? No es el primer año que dirijo la taberna aquí."+"He visto a todos en todas las condiciones posibles. A veces una esposa venía a buscar a su marido, a veces se iban por su cuenta, y en algunas ocasiones tuve que echarlos. '¿Estoy seguro?!' ¡Por supuesto que lo estoy!";
			link.l1 = "Bueno, gracias de todos modos...";	
			link.l1.go = "exit";
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			AddQuestRecord("HoldQuest", "7");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "hold_genquest3":
			Hold_GenQuest_GenerateChar();		
			AddQuestRecord("HoldQuest", "8");
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Gen")); 			
			AddQuestUserData("HoldQuest", "sFoundChar", pchar.GenQuest.Hold_GenQuest.foundStr);
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			SetFunctionTimerConditionParam("Hold_GenQuest_FindCharTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
		break;
		
		case "hold_genquest4":
			AddQuestRecord("HoldQuest", "13");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");			
			DialogExit();
		break;
		
		case "hold_genquest5":
			SetFunctionTimerConditionParam("Hold_GenQuest_GetMapTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_GenerateMapChar");			
		break;
		
		case "CaptainComission_1":
			dialog.text = LinkRandPhrase("Él es un visitante frecuente aquí, pero ahora no está. Vuelve de vez en cuando, le diré que te espere aquí si aparece.","Es un visitante frecuente aquí. Si vuelves más tarde, seguro que lo encontrarás allí.","Vuelve de vez en cuando, él es un visitante frecuente aquí. Le haré saber que estabas buscando por él.");
			link.l1 = "Gracias, volveré más tarde...";
			link.l1.go = "CaptainComission_2";
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
		break;
		
		case "CaptainComission_2":
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromTavern.function = "CaptainComission_GenerateChar";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_3":
			dialog.text = "Ya ha venido aquí, así que debería estar por aquí cerca...";
			link.l1 = "Gracias.";
			link.l1.go = "exit";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
		break;
		
		case "CaptainComission_Tavern1":
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
			dialog.text = "¿Hay algún hombre que no lo conozca? Todo el asentamiento lleva varios días hablando de él.";
			link.l1 = "¿Podrías contarme más?";
			link.l1.go = "CaptainComission_Tavern2";
		break;
		
		case "CaptainComission_Tavern2":
			dialog.text = "Un poco, el capitán fue ejecutado, lo mismo se puede decir de algunos de su tripulación. El resto fueron esparcidos por el Caribe despojados de rango y posición... ¿Por qué? Según un juez, había hundido a un pirata durante una patrulla y escondió el botín para él mismo\n"+"Aquí está el asunto, ni el dueño de este barco o mercancías han sido encontrados... han estado peinando las bahías e inlets locales en busca de ellos pero sin éxito.";
			link.l1 = "¿Qué, ninguno de la tripulación reveló la ubicación del escondite?";	
			link.l1.go = "CaptainComission_Tavern3";	
		break;
		
		case "CaptainComission_Tavern3":
			dialog.text = "¡Ni uno solo! ¡Incluso bajo tortura! Todavía no puedo entender, ¿por qué el gobernador creería en esa calumnia tan ansiosamente? El capitán "+pchar.GenQuest.CaptainComission.Name+" tenía una buena reputación, y su tripulación estaba bien entrenada y disciplinada... cualquier almirante le envidiaría.";
			link.l1 = "¿Y dónde debería buscar a los miembros de la tripulación que sobrevivieron?";
			link.l1.go = "CaptainComission_Tavern4";
		break;
		
		case "CaptainComission_Tavern4":
			dialog.text = "Eso no lo sé, se han dispersado a los cuatro vientos... Aunque... todavía queda uno de ellos, pero dudo que aprendas mucho de él. Estaba gravemente conmocionado. Sabes, él servía como artillero bajo "+pchar.GenQuest.CaptainComission.Name+". Fue encontrado inconsciente en una cala dos días después de ese accidente. Primero fue enviado al hospital y tratado como un héroe, pero a medida que la trama se espesaba, lo arrojaron a la mazmorra e intentaron interrogarlo, pero luego decidieron que primero debería ser tratado médicamente, de todos modos.";
			link.l1 = "¿Todavía está aquí?";
			link.l1.go = "CaptainComission_Tavern5";
		break;
		
		case "CaptainComission_Tavern5":
			pchar.GenQuest.CaptainComission.CanoneerName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Sí, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.CanoneerName,NAME_NOM)+" es su nombre. Se deja caer de vez en cuando, gasta los centavos que gana mendigando en ron. Pobre alma. Si lo veo, le diré que te espere aquí.";
			link.l1 = "Gracias, volveré más tarde.";
			link.l1.go = "CaptainComission_Tavern6";
		break;
		
		case "CaptainComission_Tavern6":
			AddQuestRecord("CaptainComission2", "39");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			SetFunctionExitFromLocationCondition("CaptainComission_GenerateCanoneer", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_Tavern7":
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
			dialog.text = "¿Lo conozco? Claro que sí. ¿Y para qué lo necesitas?";
			link.l1 = "Tengo asuntos con él...";
			link.l1.go = "CaptainComission_Tavern8";
		break;
		
		case "CaptainComission_Tavern8":
			dialog.text = ""+GetAddress_Form(pchar)+", deberías tener cuidado con ese 'negocio'. "+pchar.GenQuest.CaptainComission.Name+" está detenido bajo sospecha de piratería, y los hombres del gobernador ahora están peinando la isla en busca de sus cómplices.";
			link.l1 = "¡No me digas! ¿Y qué hizo?";
			link.l1.go = "CaptainComission_Tavern9";
		break;
		
		case "CaptainComission_Tavern9":
			dialog.text = "No sé si es verdad o no, pero dicen que había escondido la carga confiscada de un barco pirata que pasaba y no la entregó. Y aún nadie encontró ni a ese pirata, ni la carga. Todavía no puedo entender, ¿por qué el gobernador creería en esa calumnia tan ansiosamente? Capitán "+pchar.GenQuest.CaptainComission.CapName+"  tenía una reputación decente, y era un gran soldado, puedes confiar en mi palabra, "+GetAddress_Form(pchar)+".";
			link.l1 = "Bueno, gracias por la advertencia. Nos vemos.";
			link.l1.go = "CaptainComission_Tavern10";
		break;
		
		case "CaptainComission_Tavern10":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				pchar.GenQuest.CaptainComission.GetRumour = true;
				SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
				SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
				AddQuestRecord("CaptainComission2", "19");
				AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
				AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			}			
			DialogExit();
		break;
				
		case "EncGirl_1":
			dialog.text = "¿Y para qué la necesitas?";
			link.l1 = "Tengo negocios con ella...";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "La mitad de los hombres en nuestra colonia parecen tener negocios con ella. Si nuestras mujeres la hubieran atrapado, la habrían arrojado fuera de las puertas de la ciudad, desnuda.";
			link.l1 = "Vaya, vaya... "+GetSexPhrase("Parece que me metí en una larga cola, entonces. Bueno, si alguien más viene preguntando por ella, diles que se pongan en la cola detrás de mí.","Lo veo")+"...";
			link.l1.go = "exit";
			pchar.quest.EncGirl_SpeakTavernKeeper.over = "yes";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		
		case "EncGirl_3":
			dialog.text = "Él es un visitante frecuente aquí: generalmente viene en busca de trabajo, pero ahora mismo no está. Vuelve de vez en cuando, le diré que te espere aquí si aparece.";
			link.l1 = "Gracias, volveré más tarde...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "FindingLover";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitTavern.function = "EncGirl_GenerateLover";
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "¡Oh, así que tú eres "+GetSexPhrase("ese capitán, que trajo","esa moza, que trajo")+"¿mi hijo pródigo con una joven novia?";
				link.l1 = "Sí, fui yo quien ayudó.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "¡Oh, ahí "+GetSexPhrase("él es, nuestro benefactor","ella es, nuestra benefactora")+". ¿Esperando una recompensa, supongo?";
				link.l1 = "Bueno, estoy bien sin una recompensa, pero solo tus gracias me bastarían.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Estoy muy agradecido contigo por no haber abandonado a mi hijo en situaciones difíciles y por ayudarlo a encontrar una salida a una situación delicada. Permíteme agradecerte y por favor acepta esta suma modesta y un regalo de mi parte personalmente.";
			link.l1 = "Gracias. Ayudar a esta joven pareja fue un placer para mí.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "¿Gracias? ¿¡Qué gracias?! Ha pasado medio año desde que ese cabezón estaba deambulando sin trabajo, ¡y míralo, tiene suficiente tiempo para un asunto amoroso! Cuando tenía su edad, ¡ya estaba dirigiendo mi propio negocio! ¡Pfft! Un gobernador tiene una hija casadera, ¡y ese bobo ha traído una zorra sin familia ni parientes a mi casa y se ha atrevido a pedir mi bendición!";
			link.l1 = "Supongo que no crees en el amor a primera vista, ¿verdad?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "¿Amor? ¿¡Amor!? ¿Te burlas de mí o eres estúpido? ¡Qué vergüenza complacer los caprichos de los jóvenes y actuar como un proxeneta! No solo has sacado a una chica de su hogar, sino que también has arruinado la vida de mi chico. No habrá agradecimientos para ti. Adiós.";
			link.l1 = "Igual para ti entonces.";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
				
		case "ShipLetters_4":
			pchar.questTemp.different.GiveShipLetters.speakTavern = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "¡Déjame echar un vistazo! Hmm... Pero tú eres un capitán tú mismo. Creo que deberías ver al maestro del puerto sobre esto.";
				link.l1 = "Gracias por tu consejo.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "¡Dejadme echar un vistazo! ¡Ah! Por el nombre, esto pertenece a uno de mis clientes, un caballero bastante respetado. Yo mismo puedo entregar estos documentos al dueño. ¿Me los darás?";
				link.l1 = "En segunda instancia...";
				link.l1.go = "exit";
				link.l2 = "Toma. Me alegra poder ser de ayuda.";
				link.l2.go = "ShipLetters_end";				
			}	
		break;
		
		case "ShipLetters_end":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "3");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//zagolski. переделка
		case "work":
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("No me importa a quién servir ya que el dinero no tiene nacionalidad. Pero no te ayudaré ya que viniste bajo la bandera de "+NationNameGenitive(sti(pchar.nation))+".","Soy solo un sencillo dueño de taberna, pero la colaboración con "+NationNameAblative(sti(pchar.nation))+" no parece atractivo para mí.");
				link.l1 = RandPhraseSimple("Bueno, como quieras...","Bueno, como quieras...");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("Por lo general, tenemos muchos pasajeros aquí. Aún así, no creo que haya siquiera un tonto entre ellos, que pueda aceptar viajar en tu barco. Tu mala reputación te precede, solo un necio se embarcaría con un sinvergüenza como tú.","Con frecuencia me abordan comerciantes que necesitan escolta. Pero tu mala fama te precede, y no te recomendaré a nadie. Me preocupo por mi propia reputación, ¿sabes? Nadie quiere contratar a un lobo para guardar sus ovejas.");
				link.l1 = RandPhraseSimple("Vaya, realmente, no deberías creer todo ese chisme...","Ya veo. Es difícil hacer callar a todos.","La gente es demasiado blanda estos días...");
				link.l1.go = "exit";
				break;
			}
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
        	{
				dialog.text = "¿Y dónde está tu barco? ¿O vas a llevar a los pasajeros en tu espalda y nadar?";
				link.l1 = "Oye, tienes razón...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Puede que tenga un trabajo si no tienes miedo de venir a los asentamientos piratas o a los puertos de las naciones enemigas. ¿Estás buscando algo en particular?";
			link.l1 = "Eso no debería ser un problema. Supongo que podría proporcionar escolta.";
			link.l1.go = "work_1";
			link.l2 = "¿Tienes algún pasajero? Puedo llevarlos a donde quieran, si pagan por ello.";
			link.l2.go = "work_2";
			link.l3 = "No, tal trabajo no es para mí. Gracias.";
			link.l3.go = "exit";
		break;

		case "work_1":
				dialog.text = "Por lo general, no me preguntan sobre el deber de escolta. Pregunta a los comerciantes en la taberna, tal vez necesiten tus servicios.";
				link.l1 = "Bien, como tú digas.";
                link.l1.go = "exit";
		break;

		case "work_2":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2 || bBettaTestMode)
    		{					
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
				{
					dialog.text = "Lo siento, pero no tengo a nadie dispuesto a viajar contigo.";
					link.l1 = "Ya veo.";
					link.l1.go = "exit";
					break;
				}
		         // пассажир
				if (hrand(6) > 1)
				{
					dialog.Text = "Un hombre que acaba de entrar, estaba preguntando recientemente sobre un barco que pasaba. Puedes hablar con él, si quieres.";
					link.l1 = RandPhraseSimple("¿Quién es él? ¿Tal vez es un canalla? ¿O, incluso peor, un pirata buscado?","¿Y quién es él? ¿Habrá algún problema con él?");
					Link.l1.go = "PassangerAreYouSure";
				}
				else
				{
					dialog.text = "No, hoy nadie ha preguntado por ello. Quizás, otro día.";
					link.l1 = RandPhraseSimple("Bueno, si no está allí, no está...","Solo mi suerte... Bueno, entonces, nos vemos.");
					link.l1.go = "exit";
				}
            }
    		else
    		{
				dialog.text = "No hay nadie para hoy. Vuelve en un par de días.";
				link.l1 = "Bien, como tú digas.";
                link.l1.go = "exit";
    		}
        break;

        case "ConvoyAreYouSure":
		    dialog.text = LinkRandPhrase("¿Quién podría saberlo? Preguntaste y respondí.","Bueno, esto es para que lo resuelvas tú. No daría fe de nadie allí.","Todo tipo de gente viene aquí. Esta es una taberna cap'n, no la mansión del gobernador.");
			Link.l1 = "Gracias, entonces regatearemos.";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

        case "PassangerAreYouSure":
		    dialog.text = LinkRandPhrase("¿Quién podría saber? Preguntaste y respondí.","Bueno, esto es para que tú resuelvas. No daría garantías por nadie allí.","Todo tipo de gente viene aquí. Esta es una taberna cap'n, no la mansión del gobernador.");
			Link.l1 = "Ya veo. Vamos a averiguar quién es este hombre...";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

		 case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Helen_room":
			dialog.text = "Por supuesto, Helen. ¿Cuánto tiempo te quedas? ¿Y qué, has tenido una pelea con la vieja Gladys?";
			if(!isDay())
			{
				link.l1 = "Solo para dormir hasta la mañana. Si vuelvo a casa ahora, seguramente la despertaré.";
				link.l1.go = "Helen_room_day";
			}
			else
			{
				link.l1 = "No, no, solo necesito zarpar por la noche, y no quiero despertarla.";
				link.l1.go = "Helen_room_night";
				link.l2 = "Quiero un buen y largo sueño y tomarme mi tiempo para levantarme. Tomaré una habitación por un día.";
				link.l2.go = "Helen_room_day_next";
			}
		break;

		case "room":
   			if (chrDisableReloadToLocation || CheckAttribute(pchar, "GenQuest.TavernClose")) //кто-то должен подойти к ГГ.
			{
				dialog.text = "La habitación está ocupada, "+GetAddress_Form(NPChar)+", no hay nada que pueda hacer por ti.";
				link.l1 = "Bueno, qué lástima...";
				link.l1.go = "exit";
				break;
			}
			// суп из черепахи
			if (CheckAttribute(pchar, "questTemp.Terrapin.Room_close") && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "El señor Henri Thibaut está alquilando la habitación en este momento, y pagó por un mes por adelantado, así que no hay nada que pueda hacer por usted, capitán.";
				link.l1 = "Bueno, es una lástima...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "cave" && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "La habitación está ocupada, "+GetAddress_Form(NPChar)+", no hay nada que pueda hacer por ti.";
				link.l1 = "Bueno, eso es una lástima...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore" && npchar.location == "Baster_tavern") // 070712
			{
				dialog.text = "La habitación está ocupada, "+GetAddress_Form(NPChar)+", no hay nada que pueda hacer por ti.";
				link.l1 = "Bueno, eso es una lástima...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
			{
				Dialog.text = "Por desgracia, no, Capitán. Todas las habitaciones están ocupadas por Blackwood y sus hombres.";
				if (CheckAttribute(pchar, "questTemp.LadyBeth_TavernRoomDialog"))
				{
					link.l1 = "Eh, qué pena...";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "¿Todas las habitaciones? ¿Hay más de una habitación aquí?";
					link.l1.go = "LadyBeth_Room";
				}
				break;
			}
			//-->> квест официантки
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = "¿Quieres alquilar una habitación? No hay problema. 100 piezas de ocho y es tuya.";
				if (sti(pchar.money) >= 100)
				{
					link.l1 = "Aquí está tu dinero.";
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = "Hmm... Supongo que volveré más tarde...";
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//квест официантки
			{
				dialog.text = "La habitación es toda tuya. Entra y relájate.";
				link.l1 = "Gracias, compañero.";
				link.l1.go = "exit";
				break;
			}
			//<<-- квест официантки
			// --> квест "A damsel in the jungle"
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && npchar.city == pchar.GenQuest.EncGirl.city)
			{
				if(pchar.GenQuest.EncGirl == "EncGirl_ToTavern")
				{
					dialog.text = "¿Quieres alquilar una habitación? No hay problema. 100 piezas de ocho y es tuya.";
					if (sti(pchar.money) >= 100)
					{
						link.l1 = "Aquí está tu dinero.";
						link.l1.go = "exit";
						AddMoneyToCharacter(pchar, -100);
						LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
						pchar.GenQuest.EncGirl = "EncGirl_toRoomUp";
					}
					else
					{
						link.l1 = "Hmm... Supongo que volveré más tarde...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.GenQuest.EncGirl == "EncGirl_toRoomUp")//квест  по спасению тетки в пампасах
				{
					dialog.text = "La habitación es toda tuya. Entra y relájate.";
					link.l1 = "Gracias, compañero.";
					link.l1.go = "exit";
					break;
				}
			}
			// <-- квест "A damsel in the jungle"

			// belamour постоялец -->
			if (CheckAttribute(pchar, "GenQuest.Unwantedpostor") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && abs(50-sti(pchar.reputation.nobility)) > 20)
			{
				if(pchar.GenQuest.Unwantedpostor == "start")
				{
					SetFunctionTimerCondition("Unwantedpostor_OneDay", 0, 0, 1, false);
					pchar.GenQuest.Unwantedpostor = "timer";
				}
				dialog.text = "Disculpa, capitán, desafortunadamente no hay habitación disponible. El huésped no se irá. Y aún no me ha pagado...";
				link.l1 = "Parece que tendremos que pasar la noche en la sala común...";
				link.l1.go = "Unwantedpostor_hall_day_wait";
				link.l2 = "Lo siento. Hablemos de algo más.";
				link.l2.go = "int_quests";
				if(pchar.GenQuest.Unwantedpostor != "Lose")
				{
					link.l3 = "Entonces llama a los guardias. ¿Qué clase de huésped es este? No paga dinero, no quiere irse...";
					link.l3.go = "Unwantedpostor";
				}
				break;
			}
			//<-- постоялец

			dialog.text = "¿Cuánto tiempo planeas quedarte aquí?";
			if(!isDay())
			{
				link.l1 = "Hasta la mañana.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Hasta la noche.";
				link.l1.go = "room_night";
				link.l2 = "Hasta la próxima mañana.";
				link.l2.go = "room_day_next";
			}
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				pchar.questTemp.MarySexBlock = true;
				SetTimerFunction("Mary_DeleteSexBlock", 0, 0, 1);
			}
		break;

		case "room_day":
			dialog.text = "Eso te costará 5 piezas de ocho.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Trato hecho. Aquí tienes.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase("¿A ese precio? ¿Estás alquilando aposentos reales? Prefiero quedarme en la sala común gratis.","Vaya, el lujo de dormir en una cama está más allá de mis medios actuales, parece. Supongo que tendré que dormir en la sala común en un banco.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "No ahora. Cambiemos de tema.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_day_next":
			dialog.text = "Eso te costará 10 piezas de ocho.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Trato hecho. Aquí tienes.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase("¿A ese precio? ¿Estás alquilando cámaras reales? Prefiero quedarme en la sala común gratis.","Vaya, el lujo de dormir en una cama está más allá de mis medios actuales, parece. Supongo que tendré que dormir en la sala común en un banco.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "No ahora. Cambiemos de tema.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night":
			dialog.text = "Eso te costará 5 piezas de ocho.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Trato hecho. Aquí tienes.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase("¿A ese precio? ¿Estás alquilando cámaras reales? Prefiero quedarme en la sala común gratis.","Vaya, el lujo de dormir en una cama está más allá de mis medios actuales, parece. Supongo que tendré que dormir en la sala común en un banco.");
			link.l2.go = "hall_night_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "No ahora. Cambiemos de tema.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night_wait":
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (hRand(3) == 1)
            {
                Dialog.text = "¡Lárgate de aquí, malandrín! La sala común puede ser gratuita, pero tenemos expectativas de un comportamiento decente!";
				link.l1 = "Está bien, está bien, me voy.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "¡Lárgate de aquí, canalla! La sala común puede ser gratis, pero esperamos un comportamiento decente!";
				link.l1 = "Bien, bien, me voy.";
				link.l1.go = "exit";
            }
            else
            {
				// belamour прерывание ночной приключенец -->
				if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
					SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
				}
				// <-- прерывание ночного приключенца
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = "¡Detén este comportamiento escandaloso en mi taberna de inmediato o llamaré a los guardias!";
			link.l1 = "Bien, bien, me voy.";
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		//******************* ноды квеста священника. поиск грабителей (квест № 2)**********************
		case "Tavern_GenQuest_Church_2_1":
			dialog.text = "No sé mucho al respecto... Sería mejor que preguntaras a los clientes.";
			link.l1 = "Ya veo, gracias.";
			link.l1.go = "exit";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		break;
			
		//******************* ноды квеста священника. вернуть рукописи (квест № 1)**********************
		case "Tavern_ChurchGenQuest1_Node_1":
			dialog.text = "No proporcionamos servicios a crédito, "+GetSexPhrase("señor","señorita")+".";
			link.l1 = "Pago con buena moneda. ¿Ya no aceptas oro o plata?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_2":
			dialog.text = "Lo siento, "+GetSexPhrase("señor","señorita")+"capitán, pero tu amigo tenía una deuda, y yo pensé...";
			link.l1 = "Piensa menos y trabaja más rápido, compadre. Ahora, ¿cuánto te debe mi valiente amigo?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_3":
			iTemp = (rand(3)+1)*100;
			PChar.GenQuest.ChurchQuest_1.MoneyToBarmen = iTemp;
			if(rand(1) == 0) // "If he's a simple one and pays right away"
			{
				dialog.text = FindRussianMoneyString(iTemp)+", mis"+GetSexPhrase("ter","s")+" capitán, y también empeñó algunos libros de la iglesia, eso es todo lo que tenía encima, que tenía algún valor.";
				if(sti(PChar.money) >= iTemp)
				{
					link.l1 = "Aquí están tus monedas. Entrega los manuscritos. Y cuidado con ellos, esto no es un libro de grabados lujuriosos, sino la Sagrada Escritura!";
					link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
				}
				else
				{
					link.l1 = "Espera un poco... Volveré con el dinero";
					link.l1.go = "exit";
					PChar.GenQuest.ChurchQuest_1.NoMoneyToBarmen = true;
				}
			}
			else // "If he's not a simple one"
			{
				dialog.text = FindRussianMoneyString(iTemp)+", mis"+GetSexPhrase("ter","s")+"capitán.";
				link.l1 = "Pagaré su deuda y tomaré lo que dejó para asegurarla.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2";
			}
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_1":
			DialogExit();
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "8");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", GetFullName(CharacterFromID("ChurchGenQuest1_Cap")));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2":
			dialog.text = "No, señor"+GetSexPhrase("ter","s")+", eso no funcionará así.";
			link.l1 = "¿Qué quieres decir con 'eso no funcionará así'? La deuda de un capitán se paga, él está bien. Tienes tu dinero de vuelta, estás bien. Tomo su promesa, estoy bien. Todos están bien, entonces ¿por qué 'eso no funcionará así'?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_1";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_1":
			dialog.text = "Porque, señor"+GetSexPhrase("ter","s")+"capitán, no necesito el dinero. Porque conozco demasiado bien a ese capitán, así que nunca esperé que él me pagara y tomara estos manuscritos de mí.";
			link.l1 = "¿Qué quieres decir con que no necesitas dinero? ¿Así que planeaste quedarte con estos libros desde el principio? ¿Pero por qué, en nombre de Dios?!";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_2":
			dialog.text = "En el nombre de Dios, exactamente, por eso, señora"+GetSexPhrase("ter","s")+". Mi pequeño estaba muy enfermo, y mi esposa y yo hicimos un voto de hacer una donación a la Iglesia si Nuestro Señor Bendito curaba al niño de fiebre. La misericordia de Nuestro Señor no tiene fin, mi niño está vivo y bien, y ahora debemos cumplir nuestro voto. Y justo a tiempo capitán "+PChar.GenQuest.ChurchQuest_1.CapFullName+" aparece y empeña estos libros de la iglesia. No podía permitir tal obscenidad: pagar las bebidas con la Palabra, por lo tanto, decidí entregar estos libros al pastor de nuestra parroquia.";
			link.l1 = "Bueno, ciertamente esto es una buena acción, pero también deberías saber que estos libros en realidad pertenecen a otro sacerdote, en realidad, no solo a un sacerdote, sino a un obispo y a mi pastor espiritual. Y podría enfadarse e incluso maldecir a aquellos que se atrevieran a donar bienes robados de la Iglesia. Me gustaría comprarlos y llevarlos a salvo a casa. Puedes donar el dinero a tu parroquia, estoy seguro de que Dios lo apreciará de todas formas.";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_3":
			dialog.text = "Mis"+GetSexPhrase("ter","s")+"... Mis"+GetSexPhrase("ter","s")+" capitán... ¡Por supuesto, no tenía ni idea! Se los devolveré, y no requeriré dinero a cambio. Solo tienes que hablar bien de nosotros al obispo, quizás, podría bendecirnos y liberarnos de nuestro voto...";
			link.l1 = "¡Por supuesto que tu promesa será considerada cumplida! Después de todo, has renunciado a tu beneficio para devolver los libros a su legítimo dueño. La iglesia en particular no importa, porque solo hay un Dios y una Santa Iglesia Católica Apostólica, ¿verdad? Muy bien, dámelos, y buena suerte para ti...";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_4";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_4":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "9");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Tavern":
			dialog.text = "Mmm, "+pchar.GenQuest.Device.Shipyarder.Type+"¿Nunca lo había oído antes... Pero qué es en realidad? Nunca había oído hablar de tal cosa en todo mi tiempo.";
			link.l1 = "Bueno, es una herramienta de carpintero de ribera, "+pchar.GenQuest.Device.Shipyarder.Describe+". ¿Alguien te ofreció algo así?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 6)
			{
				dialog.text = "Hmm... Sí, un tipo extraño efectivamente me trajo esa cosa. No me dijo qué era, solo intentó cambiarlo por licor. Por supuesto, me negué, no necesitaba ese abalorio.";
				link.l1 = "¿Y cómo lucía y hacia dónde fue? Necesito ese instrumento con urgencia.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "No, nada como eso. Lo siento, no puedo ayudarte. Pregunta por ahí.";
				link.l1 = "Ya veo. Bueno, ¡hora de preguntar por ahí!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		//Jason --> генератор Место под солнцем
		case "Sunplace_Tavern":
			if (makeint(environment.time) > 12.0 && makeint(environment.time) < 17.0)//в магазине
			{
				dialog.text = "¿"+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Acaba de estar aquí, y ya debe haber encontrado a su compañero, el tendero. Intenta buscarlo en la tienda, seguramente debe estar allí.";
				link.l1 = "¡Gracias! ¡Me has ayudado mucho!";
				link.l1.go = "Sunplace_Tavern_1";
			}
			else//ушел на рыбалку
			{
				dialog.text = "¿"+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Hoy, temprano en la mañana, se ha hecho a la mar en su balandra para un viaje marino. Apuesto a que ahora está parado en el costado, admirando la vista. Si lo necesitas, puedes intentar encontrarlo en el mar o esperar hasta que regrese en un par de días...";
				link.l1 = "¡Gracias! Supongo que no me quedaré esperando... será más fácil encontrarlo en el mar. ¡Buena suerte!";
				link.l1.go = "Sunplace_Tavern_2";
			}
		break;
		
		case "Sunplace_Tavern_1"://магазин
			pchar.quest.Sunplace_Store.win_condition.l1 = "location";
			pchar.quest.Sunplace_Store.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.CityT + "_store";
			pchar.quest.Sunplace_Store.function = "Sunplace_CreateTrader";
			AddQuestRecord("Sunplace", "6");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		
		case "Sunplace_Tavern_2"://рыбалка
			pchar.GenQuest.Sunplace.Trader.IslandID = GetCharacterCurrentIslandId(npchar);
			pchar.GenQuest.Sunplace.Trader.EnemyNation = npchar.nation;
			pchar.quest.Sunplace_Sea.win_condition.l1 = "location";
			pchar.quest.Sunplace_Sea.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.IslandID;
			pchar.quest.Sunplace_Sea.function = "Sunplace_CreateTraderLugger";
			AddQuestRecord("Sunplace", "7");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		// <-- генератор Место под солнцем	
		
		// Jason --> Голландский гамбит
		case "HWICHollJacob_Tavern":
			dialog.text = "Psssst... ¿Por qué estás gritando? Ha estado esperándote durante bastante tiempo. Ya se ha bebido una jarra entera de ron. Sube a la habitación, lo encontrarás allí.";
			link.l1 = "Ah, ya veo. Con suerte, aún estará despierto.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern", "reload2_back", false);
			pchar.questTemp.HWIC.Holl = "JacobInRoom";
			AddDialogExitQuestFunction("Create_JacobVanBerg");
			DelLandQuestMark(npchar);
		break;
		
		case "HWICSelfFernando_Tavern":
			if (NPChar.location == pchar.questTemp.HWIC.Self.SpainCity +"_tavern")
			{
				//DelMapTonzagAllQM();
				dialog.text = "Sí, conozco a ese caballero. Debería estar en algún lugar de la ciudad, recién lo vi pasar por mi ventana.";
				link.l1 = "¡Gracias! ¡Iré a buscarlo!";
				link.l1.go = "Fernando_Land";
				/* if (makeint(environment.time) > 10.0 && makeint(environment.time) < 18.0)//на улице
				{
					dialog.text = "Sí, conozco a ese caballero. Debería estar en algún lugar de la ciudad, recién lo vi pasar por mi ventana.";
					link.l1 = "¡Gracias! ¡Iré a buscarlo!";
					link.l1.go = "Fernando_Land";
				}
				else //в море
				{
					dialog.text = "Sí, ahora está visitando nuestra ciudad. Justo ahora no está aquí, se fue a navegar en su bricbarca. Probablemente no esté lejos de aquí, dentro de las aguas de nuestra isla.";
					link.l1 = "¡Gracias compadre! ¡Me has ayudado mucho!";
					link.l1.go = "Fernando_Sea";
				} */
				pchar.questTemp.HWIC.Self = "KillFernando";
			}
			else
			{
				dialog.text = "¿Fernando Rodríguez? Nunca he oído hablar de él. No, no sé nada acerca de este hombre.";
				link.l1 = "Ya veo... Bueno, la búsqueda continúa....";
				link.l1.go = "exit";
			}
			npchar.quest.HWICTalked = "true";
		break;
		
		case "Fernando_Land":
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.SpainCity +"_town";
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnLand";
			AddQuestRecord("Holl_Gambit", "3-2");
			DialogExit();
		break;
		
		case "Fernando_Sea":
			pchar.questTemp.HWIC.Self.FernandoIslandID = GetCharacterCurrentIslandId(npchar);
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.FernandoIslandID;
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnSea";
			AddQuestRecord("Holl_Gambit", "3-3");
			DialogExit();
		break;
		//<-- Голландский гамбит
		
		//Jason --> гонки на гидропланах
		case "Race_Advantage":
			dialog.text = "Sí, por supuesto. Felicidades capitán. Ya estoy al tanto de tu victoria. Aquí está tu dinero.";
			link.l1 = "Gracias, "+npchar.name+".";
			link.l1.go = "Race_Advantage_1";
		break;
		
		case "Race_Advantage_1":
			DialogExit();
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Racing.Go.Money)*2);
			AddQuestRecord("Racing", "4");
			AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Gen"));
			CloseQuestHeader("Racing");
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
		break;
		//<-- гонки на гидропланах
		
		//Jason --> захват пассажиров
		case "Marginpassenger":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.lose"))
			{
				dialog.text = "Errr, señor, "+pchar.GenQuest.Marginpassenger.q2Name+" murió hace unos "+LinkRandPhrase("un mes","tres semanas","dos meses")+" hace. "+LinkRandPhrase("De repente sucumbió a la fiebre","Fue apuñalado en las puertas de la ciudad por bandidos o por esos salvajes de piel roja","Le dispararon en un duelo")+". Que Dios descanse su alma...";
				link.l1 = "¡Maldita sea!.. ¿Y qué se supone que haga con su...? Bueno, como sea. Gracias por la información. Nos vemos, "+npchar.name+".";
				link.l1.go = "Marginpassenger_1";
			}
			else
			{
				dialog.text = "¿"+pchar.GenQuest.Marginpassenger.q2Name+"? Sí, debería estar en algún lugar del pueblo. Búscalo en las calles. Pero ten en cuenta que cada día hasta el mediodía está en la oficina del gobernador, y después de las nueve de la noche se encierra en su casa.";
				link.l1 = "¡Gracias! Iré a buscarlo...";
				link.l1.go = "Marginpassenger_2";
			}
		break;
		
		case "Marginpassenger_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "7");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "a Puerto Príncipe, con Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "a Le Francois, con Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "Marginpassenger_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "8");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			pchar.GenQuest.Marginpassenger = "street";
		break;
		//<-- захват пассажиров
		
		//Jason --> поиск дезертира
		case "FindFugitiveTav":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 0)
			{
				dialog.text = NPCStringReactionRepeat("Parece que tu capitán estaba diciendo la verdad."+pchar.GenQuest.FindFugitive.Name+" en efecto ha llegado recientemente a nuestro asentamiento. Búscalo en las calles durante el día, usualmente está perdiendo su tiempo.","¡Ya me has preguntado sobre ese hombre, y te conté todo lo que sabía!","¿Me estás tomando el pelo o realmente eres un idiota?! ¡Ya estás preguntando lo mismo por tercera vez!","Solo pensar, cómo un idiota podría convertirse en capitán...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("¡Gracias, amigo, me has ayudado mucho!","Sí, sí, está bien.","Vaya, vaya, no te emociones tanto. Solo lo olvidé.","Bueno, lo hizo, como puedes ver...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveTav_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("No, compañero, nunca he oído ese nombre antes. Pregunta por ahí, tal vez alguien lo conozca...","Ya me has preguntado sobre ese hombre, y te dije: ¡No sé!","¿Me estás tomando el pelo o de verdad eres un idiota?! ¡Ya me has preguntado lo mismo por tercera vez!","Solo pensar, cómo tal idiota pudo convertirse en capitán...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Ya veo. Bueno, gracias de todas formas.","Sí, sí, bien.","Vaya, vaya, no te emociones tanto. Solo lo olvidé.","Bueno, lo hizo, como puedes ver...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveTav_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-1");
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_city";
			LAi_SetLoginTime(sld, 11.0, 18.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_town", "goto", "goto"+(rand(9)+1));
		break;
		//<-- поиск дезертира
		
		//--> Бремя гасконца
		case "Sharlie_crew":
			dialog.text = "Lamentablemente, no puedo ayudarte en este momento, nadie que conozca serviría bajo tu mando. Pero puedo darte un consejo, habla con ese marinero que acaba de sentarse en la mesa que hay justo detrás de ti. Él y sus compañeros acaban de abandonar un barco mercante. Quizás, acepten ir contigo.";
			link.l1 = "¡Está bien, haré justo eso! ¡Muchas gracias!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "sailor";
			//усадим матроса Алонсо
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSailor" , "Alonso", "man", "man", 10, FRANCE, -1, true, "quest"));
			sld.name 	= StringFromKey("HollandGambit_23");
			sld.lastname = "";
			FantomMakeCoolFighter(sld, 10, 20, 20, "blade_05", "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Sharlie_sailor";
			sld.greeting = "town_sailor";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator("FortFrance_tavern", "sit7");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");
			AddQuestRecord("Sharlie", "6-1"); // mitrokosta
		break;
		
		case "Sharlie_skiper":
			dialog.text = "No puedo decirte nada específico, amigo. En este momento ningún navegante frecuenta mi lugar. Intenta preguntar en el puerto, quizás la gente sepa más.";
			link.l1 = "Ya veo. Está bien, iré a hablar con la gente.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "findskiper";
			//сгенерим наводчика
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSkiperTalker", "citiz_"+(rand(19)+21), "man", "man", 10, FRANCE, -1, true, "marginal"));
			FantomMakeCoolFighter(sld, 10, 20, 20, RandPhraseSimple("blade_04","blade_06"), "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "skipertalker";
			sld.greeting = "marginal";
			LAi_SetWarriorType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "patrol", "patrol"+(rand(13)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Бремя гасконца
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_tortuga":
			sld = characterFromId("Tortuga_waitress");
            dialog.text = "¡De inmediato, señor!.. ¡El mejor vino francés que hay! "+sld.name+"¡Ve a preparar la mejor habitación para invitados! Eso serán 1000 pesos, señor.";
			link.l1 = "Aquí.";
			link.l1.go = "mtraxx_tortuga_1";
		break;
		
		case "mtraxx_tortuga_1":
			AddMoneyToCharacter(pchar, -1000);
            DialogExit();
			pchar.questTemp.Mtraxx.Retribution = "room";
			pchar.quest.mtraxx_retribution_room.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.location = "Tortuga_tavern";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.mtraxx_retribution_room.function = "Mtraxx_RetributionToRoom";
		break;
		// belamour постоялец -->
		case "Unwantedpostor_hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "¡Fuera, malandrín! Estás ocupando un espacio valioso para los clientes que pagan!";
				link.l1 = "Bien, de acuerdo... Me voy.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "Unwantedpostor":
				dialog.text = "Sí, y asustar a todos mis clientes con el hecho de que mis guardias arrastran a la gente fuera de la taberna? Y algunos de mis clientes no quieren estar cerca de los soldados. Los pone nerviosos, ¿ves? No quiero arruinar mi reputación...";
				link.l1 = "¿Hmm, y si resuelvo tu problema?";
				link.l1.go = "Unwantedpostor_1";
		break;
		
		case "Unwantedpostor_1":
				dialog.text = "¿Te has decidido? Está armado, es algún tipo de mercenario profesional...";
				link.l1 = "Hmm, tienes razón, no me apetece discutir con un mercenario armado...";
				link.l1.go = "Exit";
				link.l2 = "Bueno, tampoco soy una monja recluida... Y aún quiero alquilar una habitación.";
				link.l2.go = "Unwantedpostor_2";
		break;
		
		case "Unwantedpostor_2":
				dialog.text = "Bueno, si puedes, ejem... convencerle de que se vaya, entonces la habitación es tuya hasta la mañana. Gratis, por supuesto.";
				link.l1 = "Sabes, cambié de opinión. No me apetece convencer a nadie.";
				link.l1.go = "Exit";
				link.l2 = "Querrás ver esto. Tu huésped no deseado está a punto de salir volando de tu taberna como una gaviota gigante.";
				link.l2.go = "Unwantedpostor_kikcoff";
		break;
		
		case "Unwantedpostor_kikcoff":
				DialogExit();
				chrDisableReloadToLocation = true; //закрыть локацию
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location+"_upstairs")], true); //запретить драться
				iTemp = sti(pchar.rank) + rand(5);
				sld = GetCharacter(NPC_GenerateCharacter("Berglar_Unwantedpostor", "citiz_5"+(rand(3)+1), "man", "man", iTemp, PIRATE, -1, true, "quest")); // "mercen_"+(rand(14)+14)
				FantomMakeCoolFighter(sld, iTemp, 50 + rand(30), 50 + rand(30), "topor_04", "", "bullet", 50);
				sld.dialog.filename = "GenQuests_Dialog.c";
				sld.dialog.currentnode = "Unwantedpostor_room";	
				sld.greeting = "Enc_Raiders"; 
				if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
				{
					DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
					ChangeCharacterAddressGroup(sld, pchar.location+"_upstairs", "quest", "quest3");
				} 
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		// <-- belamour постоялец
		
		case "Helen_room_night":
			dialog.text = "Ya veo. Serán cinco platas.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Por supuesto, aquí tienes.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = "En realidad, sabes qué... Quizás en otro momento. Pasaré el resto del día de pie.";
			link.l2.go = "Helen_night_exit";
		break;
		
		case "Helen_room_day":
			dialog.text = "Decisión sabia. Serán cinco platas, y buena noche a usted.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Aquí tienes, gracias y buenas noches.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = "En segunda instancia, no tengo ganas de dormir. Voy a deambular por la ciudad, a tomar algo de aire nocturno.";
			link.l2.go = "Helen_day_exit";
		break;
		
		case "Helen_room_day_next":
			dialog.text = "Por supuesto, Ellen. Serán diez pesos.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Por supuesto, aquí tienes.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = "De hecho... podría hacer algo útil con todo el día. Tal vez en otra ocasión.";
			link.l2.go = "Helen_Next_day_exit";
		break;
		
		case "Helen_night_exit":
			dialog.text = "Como desees, Ellen.";
			link.l1 = "Mhm.";
			link.l1.go = "exit";
		break;
		
		case "Helen_day_exit":
			dialog.text = "Quizás incluso te encuentres somnoliento después de un buen paseo.";
			link.l1 = "Ja-ja, quizás.";
			link.l1.go = "exit";
		break;
		
		case "Helen_next_day_exit":
			dialog.text = "Como veas conveniente.";
			link.l1 = "Bueno, hasta la próxima vez.";
			link.l1.go = "exit";
		break;
		
		case "Helen_rumours_tavern":
			dialog.text = "Por supuesto, Helen, soy todo oídos.";
			link.l1 = "¿Cuáles son las últimas noticias o rumores interesantes en la ciudad?";
			link.l1.go = "rumours_tavern";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Room":
			dialog.text = "Paga el triple del precio habitual, así que... ya me entiendes. Yo no recomendaría rechazarlo, tiene un temperamento difícil. Sobre todo últimamente.";
			link.l1 = "¿Qué le pasa?";
			link.l1.go = "LadyBeth_Room_2";
		break;

		case "LadyBeth_Room_2":
			dialog.text = "Obsesión, eso es. Al principio, era un tipo generoso y amable. Sus marineros tiraban el dinero en las tabernas, compraban regalos para las chicas. Una verdadera celebración comenzaba cuando el «Lady Beth» llegaba a puerto. ¿Y ahora? Ahora sólo compran provisiones y reclutan gente indiscriminadamente. Como si no necesitaran marineros, solo mano de obra. Bueno, puedes hablar con él en persona.";
			link.l1 = "Tal vez lo haga. Gracias.";
			link.l1.go = "exit";
			pchar.questTemp.LadyBeth_TavernRoomDialog = true;
		break;
		// Леди Бет <--
	}
}

string findTraderCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}
