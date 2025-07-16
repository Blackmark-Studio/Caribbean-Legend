// Соукинс в Пуэрто-Принсипе
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
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = "¿Tienes algún asunto conmigo? ¿No? ¡Entonces sal de aquí!";
			link.l1 = "Ya me voy.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";


					if (npchar.city == sti(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "¿Tienes algún trabajo para mí?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "He seguido el rastro, pero necesito algunas monedas - 30.000 pesos para sacar a la rata de su agujero.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "Aquí, mira esta carta que he encontrado en el cadáver del contrabandista";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "Está hecho. Norman Vigo y su barco se han ido al diablo del mar.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Mm... ¿has dicho trabajo? En realidad, es bueno que me hayas preguntado. Necesito a un hombre de fuera. Quiero descubrir algo en la ciudad más cercana, pero mis hombres son conocidos allí. No puedo prometerte mucho, pero obtendrás algo.";
			link.l1 = "¡Genial! ¿Cuál es la misión?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Lo siento, pero no lo arriesgaré por unos pocos restos. Adiós.";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "Entonces escucha, hice un trato para entregar 200 esclavos hace un mes con el capitán del bergantín 'Saintblue'. Quería venderlos al dueño de la plantación. El tiempo ha pasado y el cliente ha comenzado a preocuparse, pero ayer me dijeron que el bergantín fue visto no lejos de la isla. ¡Pero! El capitán no se presentó. Hoy, mi cliente me ha exigido que le devuelva su adelanto y dijo que le ofrecieron comprar esclavos de otro vendedor. Más caro, pero todo el lote de esclavos y de una vez.";
			link.l1 = "¿Y? ¿Tengo que encontrar 200 esclavos en unos pocos días para salvarte de perder un adelanto? ¿Por unas pocas monedas?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Claro que no. ¿Acaso parezco un idiota? De todos modos, no le devolveré su adelanto. Pero necesito pruebas de que esos esclavos que le ofrecieron son míos. Encuentra a los que le ofrecieron un nuevo trato y obtendrás tus 10.000 pesos. ¿Trato?";
			link.l1 = "Estoy dentro. ¿Tienes alguna sospecha? ¿Quién podría hacer eso?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Ni por asomo. Busca a otro. ¿Solo por 10.000? Lo siento, pero no funcionará.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "Si tuviera alguna idea, nunca usaría tus servicios. Esos hombres ya estarían muertos. Pero estoy ansioso por saber cómo se enteraron de la carga del 'Saintblue' y de mi cliente. Parece que fue bastante fácil para ellos. ¿Ves ahora?";
			link.l1 = "Sí, alguien te ha traicionado.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "¡Exactamente! Estoy buscándolo. Matar a mis competidores y devolverme a mis esclavos no es tu prioridad. Necesito a esa rata, en realidad su cabeza ensartada en una lanza, para ser honesto. ¿Ves ahora por qué mis hombres no deberían saber nada sobre tu misión? Sospecharé de todos hasta que descubra quién vende la información. Y realmente no quiero eso...";
			link.l1 = "Ya veo. Entonces mantendré un perfil bajo. Estoy en camino.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "¿Treinta mil dices? Es una suma grande... Solo puedo darte 5.000 pesos, es todo lo que tengo ahora. ¡Y ni se te ocurra escapar con el dinero o te encontraré y te colgaré de la cerca más cercana! ¿Entendido?";
			link.l1 = "Está bien, dame cinco mil entonces...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Tómalo. Estoy esperando el resultado de tu búsqueda.";
			link.l1 = "Todo estará bien.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "¡Ja! ¡Excelentes noticias! Estaba seguro de que lo lograrías. Tengo información intrigante.";
			link.l1 = "He hecho mi trabajo y quiero mis diez mil.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Claro, aquí está tu recompensa. Pero no te vayas, tengo una tarea más para ti.\nPfaifer es un tripulante de Norman Vigo del lanchón 'Séptima'. Estoy seguro de que Norman Vigo es la rata, aunque sea uno de los nuestros. Se le ha visto recientemente en las aguas de la isla. Tu trabajo es enviar a esta rata al diablo del mar. No me fallaste la primera vez, por lo tanto quiero pedirte que te encargues de este asunto también. Te pagaré 15.000 pesos. ¿Trato hecho?";
			link.l1 = "¡Estoy en ello! Considera al traidor Norman Vigo muerto.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "Sabes, no quiero participar en eso... De todos modos, no tengo tiempo. Lo siento, pero me voy.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "Lo sé, lo sé. Mis hombres estaban observando la batalla y ya han informado sobre tu victoria impecable. Bien, has hecho bien tu trabajo. Aquí tienes los 15.000 pesos que prometí. Y gracias, me has ayudado mucho.";
			link.l1 = "¡Está bien, me alegró ayudar! Pero tengo que irme ahora, he estado aquí demasiado tiempo y tengo muchas cosas que hacer. ¡Adiós!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;


	}
}
