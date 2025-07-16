// диалоги обитателей плантаций
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, i, n;
	string sTemp;
	bool bOk;
	
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
			dialog.text = "¿Necesitas algo?";
			link.l1 = "No, no lo hago.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// рабы
		case "plantation_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Estoy tan cansado, ya me estoy cayendo...","¡No puedo seguir viviendo así!"),RandPhraseSimple("Este trabajo me está matando.","¡Los guardias quieren vernos a todos muertos!"));				
			link.l1 = RandPhraseSimple("Qué lástima.","Lo siento.");
			link.l1.go = "exit";				
		break;
		
		// рабы-пираты по пиратской линейке
		case "pirate_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("¡Escucha, lárgate!","¡Lárgate!"),RandPhraseSimple("¿¡Qué quieres?!","¡Lárgate de aquí!"));				
			link.l1 = RandPhraseSimple("Mmm...","Bueno...");
			link.l1.go = "exit";				
		break;
		
		// охрана - солдаты
		case "plantation_soldier":
            dialog.text = RandPhraseSimple(RandPhraseSimple("Ve a molestar al jefe de la plantación","No distraigas a los esclavos, colega."),RandPhraseSimple("Mi trabajo es motivar a estos bastardos perezosos.","Maldición, demasiado caliente hoy, como siempre..."));
			link.l1 = RandPhraseSimple("Ya veo...","En efecto...");
			link.l1.go = "exit";
		break;
		
		// охрана - протектор
		case "plantation_protector":
            if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if (sti(pchar.nation) == PIRATE)
				{
					PlaySound("Voice\Spanish\soldier_arest_1.wav");
    				dialog.text = RandPhraseSimple("¿¡Pirata?! ¡Capturadle!","¡Es un pirata! ¡Ataque!");
					link.l1 = RandPhraseSimple("Pirata. ¿Y qué?","Je, adelante, inténtalo.");
					link.l1.go = "fight"; 
					break;
				}
				PlaySound("Voice\Spanish\soldier_arest_2.wav");
				dialog.text = RandPhraseSimple("¡Ho-ho, estás navegando bajo la bandera de "+NationNameGenitive(sti(pchar.nation))+"¡Creo que a nuestro comandante le gustará hablar contigo!","Bueno-bueno, huele a "+NationNameAblative(sti(pchar.nation))+" ¡aquí! ¿Un espía? Es hora de que hables con nuestro comandante.");
				link.l1 = RandPhraseSimple("¡Primero, te enviaré al infierno!","¡Es hora de que hables con mi espada!");
				link.l1.go = "fight"; 
			}
			else
			{
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					if (sti(pchar.nation) == PIRATE)
					{
						PlaySound("Voice\Spanish\soldier_arest_4.wav");
						dialog.text = RandPhraseSimple("¿¡Pirata?! ¡Atrapadlo!","¡Es un pirata! ¡Ataque!");
						link.l1 = RandPhraseSimple("¿Pirata!? ¿Dónde?","Je, adelante e intenta.");
						link.l1.go = "fight"; 
						break;
					}
					PlaySound("Voice\Spanish\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("¿Quién eres y qué quieres aquí?","¡Alto! ¿Cuál es tu negocio aquí?");
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Quiero ver al jefe de este lugar para discutir negocios. Tengo una licencia de comercio.";
						link.l1.go = "Licence";
					}
					else
					{
						link.l1 = "Quiero ver al jefe de este lugar para discutir negocios.";
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50))) link.l1.go = "PegYou";
						else link.l1.go = "NotPegYou";
					}
					if (IsCharacterPerkOn(pchar, "Trustworthy"))
					{
						link.l2 = "(Digno de confianza) Honorables señores, estoy aquí para un comercio justo y mutuamente beneficioso. Por favor, permítanme ver al dueño de la plantación.";
						link.l2.go = "mtraxx_soldier_1";
						notification("Trustworthy", "Trustworthy");
					}
				}
				else
				{
					PlaySound("Voice\Spanish\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("¿Quién eres y qué quieres aquí?","¡Alto! ¿Cuál es tu negocio aquí?");
					link.l1 = "Quiero ver al jefe de este lugar para discutir negocios.";
					link.l1.go = "NotPegYou";
				}
			}
		break;
		
		case "Licence":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				PlaySound("Voice\Spanish\soldier_arest_2.wav");
				dialog.text = "¿Una licencia? Espera un segundo... ¡Ja-ja, esto es divertido! Sé quién eres. ¡Eres buscado, amigo! ¡Y la recompensa por tu cabeza es muy grande! ¡Atrápenlo!";
				link.l1 = RandPhraseSimple("¡Pues en ese caso solo tienes que conocer a mi espada!","Que te jodan.");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				PlaySound("Voice\Spanish\soldier_arest_1.wav");
				dialog.text = "Veamos... ¡ja! Tu licencia está vencida. Así que sígueme, te llevaré al comandante...";
				link.l1 = RandPhraseSimple("¡Mierda! Supongo que es hora de que conozcas mi espada, compañero.","No lo creo...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			dialog.text = "Bien. Puedes entrar. Compórtate y no molestes a los esclavos.";
			link.l1 = "No te preocupes, amigo.";
			link.l1.go = "plantation_exit";
		break;
		
		case "PegYou":
			PlaySound("Voice\Spanish\soldier_arest_2.wav");
            dialog.text = "¿Negocios? ¡Ja-ja! ¡Vaya, esto es gracioso! Hueles a "+NationNameAblative(sti(GetBaseHeroNation()))+"¡desde mil millas! Es hora de que conozcas a nuestro comandante.";
			link.l1 = "No, creo que es hora de que conozcas mi espada.";
			link.l1.go = "fight";
		break;
		
		case "NotPegYou":
            dialog.text = "Bien. Puedes entrar. Compórtate y no molestes a los esclavos.";
			link.l1 = "No te preocupes, amigo.";
			link.l1.go = "plantation_exit";
		break;
		
		case "plantation_exit":
           DialogExit();
		   NextDiag.CurrentNode = "plantation_repeat";
		break;
		
		case "plantation_repeat":
            dialog.text = "¡Vamos, sigue adelante!";
			link.l1 = "...";
			link.l1.go = "plantation_exit";
		break;
		
		// управляющий в Маракайбо // Addon 2016-1 Jason
		case "Plantator":
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_2") // belamour legendary edition 
			{
				dialog.text = "¿Cuál es su negocio aquí, señor?";
				link.l1 = TimeGreeting()+", señor. Tengo una propuesta de negocio para usted. Tengo esclavos para vender. "+FindRussianQtyString(sti(GetSquadronGoods(pchar,GOOD_SLAVES)))+". ¿Interesado?";
				link.l1.go = "mtraxx";
				break;
			}
            dialog.text = "¿Cuál es tu negocio aquí, señor?";
			link.l1 = "Solo paseando, quería decir hola.";
			link.l1.go = "plantator_x";
		break;
		
		case "plantator_x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator";
		break;
		
		case "plantator_1":
			bOk = GetSquadronGoods(pchar, GOOD_COFFEE) >= 500 || GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500 || GetSquadronGoods(pchar, GOOD_COPRA) >= 500;
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup") && bOk) //пробуем выкупить Красавчика
			{
				dialog.text = "Usted de nuevo, señor. ¿Cómo está?";
				link.l1 = "Tengo una propuesta de negocio para ti. Produces azúcar y cacao. Me gustaría comprar tus productos pero no por dinero, puedo ofrecer mis propios productos a cambio. ¿Quizás, podríamos hacer un trato?";
				link.l1.go = "mtraxx_5";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_6" && bOk)
			{
				dialog.text = "¿Usted otra vez, señor. ¿Cómo está?";
				link.l1 = "Tengo una propuesta de negocio para ti. Producís azúcar y cacao. Me gustaría comprar tus productos pero no por dinero, puedo ofrecer mis propios bienes a cambio. ¿Quizás podríamos hacer un trato?";
				link.l1.go = "mtraxx_5";
				break;
			}
            dialog.text = "Otra vez tú, señor. ¿Cómo estás?";
			link.l1 = "Gracias, estoy bien.";
			link.l1.go = "plantator_1x";
		break;
		
		case "plantator_1x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator_1";
		break;
		
		case "mtraxx":
			// belamour legendary edition возможность обмануть плантатора -->
			if(GetSquadronGoods(pchar, GOOD_SLAVES) >= 50 || CheckCharacterPerk(pchar, "Trustworthy") || ChangeCharacterHunterScore(Pchar, "spahunter", 0) <= -50)
			{
            dialog.text = "Tengo que decepcionarte, señor, pero no necesitamos esclavos en este momento. El capitán Eduardo de Losada ya nos ha suministrado con los piratas que capturó en su última incursión.";
			link.l1 = "¿Piratas aquí? ¿Cómo puedes siquiera dormir aquí?";
			link.l1.go = "mtraxx_1";
			}
			else
			{
				dialog.text = "Ah, veamos entonces... Compraré tus esclavos. Solo me parece que tú no eres quien dices ser. Ven conmigo a la oficina del comandante, querido, y si me equivoco, cubriré completamente tus costos morales. Y ahora te pido disculpas. ¡Guardia!";
				link.l1 = RandPhraseSimple("¡Sigue soñando, no me entregaré vivo!");
				link.l1.go = "mtraxx_fail";
			}
		break;
		
		case "mtraxx_fail":
            DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddQuestRecord("Roger_3", "27");
			sld = characterFromId("Mtr_plantation_boss");
			sld.lifeday = 0;
			Mtraxx_PlantPellyClear();
			Mtraxx_TerraxReset(3);
		break;
		// <-- legendary edition
		case "mtraxx_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "Tenemos una buena guardia, así que las posibilidades de alboroto son bajas. Pero tienes razón en algo: estos bastardos son trabajadores terribles. No los habría comprado si el gobernador no me hubiera pedido que mostrara respeto a don de Losada. Además, tampoco pidió mucho por ellos.";
			link.l1 = "Ya veo. Tendré que navegar hasta Los-Teques entonces... Señor, ¿puedo pasear por su plantación y explorarla? Quizás, me gustaría comprar algo de su producción...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "¿Eres un mercader?";
			link.l1 = "En cierto grado, sí. No soy un comerciante profesional pero nunca me alejaría de un trato prometedor.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Interesante. Muy bien, tienes mi permiso. Vuelve si tienes alguna idea.";
			link.l1 = "Gracias, señor. Creo que lo haré.";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   NextDiag.CurrentNode = "plantator_1";
		   pchar.questTemp.Mtraxx = "plant_3";
		   AddQuestRecord("Roger_3", "5");
		   Mtraxx_PlantSetMaxRocur();
		break;
		
		case "mtraxx_5":
            dialog.text = "¿Por qué no? ¿Qué bienes estás ofreciendo?";
			if (GetSquadronGoods(pchar, GOOD_COFFEE) >= 500)
			{
				link.l1 = "500 cajas de café.";
				link.l1.go = "mtraxx_coffee";
			}
			if (GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500)
			{
				link.l2 = "500 cajas de vainilla.";
				link.l2.go = "mtraxx_cinnamon";
			}
			if (GetSquadronGoods(pchar, GOOD_COPRA) >= 500)
			{
				link.l3 = "500 cajas de copra.";
				link.l3.go = "mtraxx_copra";
			}
		break;
		
		case "mtraxx_coffee":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 11;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "¿Quinientas cajas de café? Bueno-bueno... Veamos... (contando) Estoy listo para cambiar tu café por "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" sacos de azúcar y "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  cajas de cacao. ¿Trato?";
			link.l1 = "Hmm... Esperaba mejores condiciones. Bueno, a quién le importa. ¡Trato hecho!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Digno de confianza) Estimado señor, ¡permítame objetar! Le he traído mercancías de la más alta calidad. Conozco el valor de cada unidad, tanto de lo que ofrezco como de lo que usted ofrece a cambio. Merezco una carga un poco más grande de su parte, y este trato seguirá siendo rentable para usted, eso lo sabe muy bien.";
				link.l1.go = "mtraxx_PlantVykup_2";
				notification("Trustworthy", "Trustworthy");
			}
		break;
		
		case "mtraxx_cinnamon":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 19;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 106;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 106;
            dialog.text = "¿Quinientas cajas de vainilla? Bueno-bueno... Veamos... (contando) Estoy listo para cambiar tu vainilla por "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" sacos de azúcar y "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  cajas de cacao. ¿Trato?";
			link.l1 = "Hmm... Esperaba mejores términos. Bueno, ¿a quién le importa? ¡Trato hecho!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Confiable) Estimado señor, ¡permítame objetar! Le he traído mercancías de la más alta calidad. Conozco el valor de cada unidad, tanto de lo que ofrezco como de lo que usted ofrece a cambio. Merezco una carga ligeramente mayor de su parte, y este trato seguirá siendo rentable para usted, lo sabe muy bien.";
				link.l1.go = "mtraxx_PlantVykup_2";
				notification("Trustworthy", "Trustworthy");
			}
		break;
		
		case "mtraxx_copra":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 20;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "¿Quinientas cajas de copra? Bueno-bueno... Veamos...(contando) Estoy listo para cambiar tu copra por "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" sacos de azúcar y "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  cajas de cacao. ¿Trato?";
			link.l1 = "Hmm... Esperaba mejores condiciones... Bueno, a quién le importa. ¡Trato hecho!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Confiable) Estimado señor, ¡permítame objetar! Le he traído mercancías de la más alta calidad. Conozco el valor de cada unidad, tanto de lo que ofrezco como de lo que usted ofrece a cambio. Merezco una carga ligeramente mayor de su parte, y este trato seguirá siendo rentable para usted, usted lo sabe muy bien.";
				link.l1.go = "mtraxx_PlantVykup_2";
				notification("Trustworthy", "Trustworthy");
			}
		break;
		
		case "mtraxx_6":
            dialog.text = "¡Espléndido! ¡Es un trato rentable para ambos! ¿Cuándo realizaremos el intercambio?";
			link.l1 = "Debería preparar los bienes primero. Tú también lo creo. Comencemos el intercambio mañana a las cuatro de la tarde. Mis hombres entregarán las cajas antes del anochecer.";
			link.l1.go = "mtraxx_7";
		break;
		
		
		case "mtraxx_7":
            dialog.text = "Trato hecho. Entonces, ¡nos vemos mañana señor!";
			link.l1 = "Hasta luego...";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			AddQuestRecord("Roger_3", "10");
			pchar.questTemp.Mtraxx = "plant_7";
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.mtraxx_plant_goods.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtraxx_plant_goods.win_condition.l1.location = pchar.location;
			pchar.quest.mtraxx_plant_goods.function = "Mtraxx_PlantFindRocurDay";
		break;
		
		case "mtraxx_9":
            dialog.text = "Esto es todo, señor. Si alguna vez necesitas azúcar o cacao, por favor ven y búscame. ¡En cualquier momento!";
			link.l1 = "Si este trato resulta ser rentable, nos veremos de nuevo. Debo irme ahora, señor.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_10":
            dialog.text = "¡Adiós, señor!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantAfterTrading");
		break;
		
		case "mtraxx_soldier_1":
            dialog.text = "No pareces un comerciante, extranjero. Muestra tu licencia.";
			link.l1 = "¡Perdóname! ¿Acaso un pedazo de papel decide si una persona puede comerciar o no? ¡Son demasiado caros! Sólo he empezado a comerciar recientemente, ¡pero ya se ha convertido en mi pasión! Déjame pasar y me aseguraré de hablar bien de vosotros dos al dueño.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_soldier_2":
            dialog.text = "Tienes lengua de plata, avaro. Está bien, sigue. Pero no olvides decirle al jefe que fuimos nosotros quienes te recomendamos a él.";
			link.l1 = "Ciertamente. Gracias.";
			link.l1.go = "plantation_exit";
		break;
		
		case "mtraxx_PlantVykup_2":
            dialog.text = "¡Estás bien versado en los precios actuales, Capitán! Tienes un claro talento para la negociación, incluso si pareces un novato. Bueno, si tus mercancías son realmente de primera clase, supongo que debería agregar un poco extra para ti.";
			link.l1 = "Por supuesto, de primera clase, ¡lo juro! Una cosa más, señor. Me gustaría comprarle algo.";
			link.l1.go = "mtraxx_PlantVykup_3";
		break;
		
		case "mtraxx_PlantVykup_3":
            dialog.text = "¿Oh? ¿Y qué podría ser eso?";
			link.l1 = "Alguien, no algo. Me gustaría comprar uno de tus esclavos como sirviente personal. ¿Es eso posible?";
			link.l1.go = "mtraxx_PlantVykup_4";
		break;
		
		case "mtraxx_PlantVykup_4":
            dialog.text = "Sin problema. Encontraremos a alguien adecuado para ti.";
			link.l1 = "Estoy interesado en un esclavo específico. El de la cara encantadora, alguien de quien no te avergonzarías al llevar a eventos formales o tener sirviendo vino a tus invitados. Se presentó como Jean Picard. Ya nos llevamos bien.";
			link.l1.go = "mtraxx_PlantVykup_5";
		break;
		
		case "mtraxx_PlantVykup_5":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 70)
			{
				dialog.text = "Sí, hay demanda por Jean Picard, y no solo para servir vino. Un influyente inglés ya me ha contactado. Un hombre llamado, ¿cómo era... Pattornson? Me entregó una carta.";
				link.l1 = "Pero ni Pattornson ni su cliente han aparecido aún. Estoy listo para comprarte a Jean aquí y ahora. Nombra tu precio, las damas están esperando.";
				link.l1.go = "mtraxx_PlantVykup_10";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Ah, lo entiendo. Pero me temo que debo rechazar, Jean Picard no está en venta. Lo siento, señor.";
				link.l1 = "¿Oh? ¿Por qué es eso? Estoy dispuesto a pagar generosamente. Solo nombra tu precio.";
				link.l1.go = "mtraxx_PlantVykup_6";
				notification("Skill Check Failed (70)", SKILL_COMMERCE);
			}
		break;
		
		case "mtraxx_PlantVykup_6":
            dialog.text = "Invaluable. Ya tiene un comprador. Le he prometido a alguien más. No hay nada más que decir. Volvamos a nuestro trato inicial y completemos el comercio.";
			link.l1 = "Hmm, como desee, señor.";
			link.l1.go = "mtraxx_PlantVykup_7";
		break;
		
		case "mtraxx_PlantVykup_7":
            dialog.text = "¡Espléndido! ¡Es un trato rentable para ambos! ¿Cuándo ejecutaremos el intercambio?";
			link.l1 = "Debería preparar los bienes primero. Tú también lo creo. Comencemos el intercambio mañana a las cuatro de la tarde. Mis hombres entregarán las cajas antes del atardecer.";
			link.l1.go = "mtraxx_PlantVykup_8";
		break;
		
		
		case "mtraxx_PlantVykup_8":
            dialog.text = "Trato hecho. Entonces, ¡nos vemos mañana señor!";
			link.l1 = "Hasta la vista...";
			link.l1.go = "mtraxx_PlantVykup_9";
		break;
		
		case "mtraxx_PlantVykup_9":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup2 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_1");
		break;
		
		case "mtraxx_PlantVykup_10":
            dialog.text = "Como desee, señor. Pero entienda, el precio es alto: quinientos doblones.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Eso no es un problema, aquí tienes. Un buen sirviente personal vale más que un esclavo ordinario, como bien sabes.";
				link.l1.go = "mtraxx_PlantVykup_11";
			}
			else
			{
				link.l2 = "Un precio bastante alto que has fijado, señor. Pero estoy muy interesado en este esclavo. Espera aquí. Si Pattornson aparece, dile que Picard ya ha sido vendido, ja-ja-ja!";
				link.l2.go = "mtraxx_PlantVykup_13";
			}
		break;
		
		case "mtraxx_PlantVykup_11":
            dialog.text = "Tienes razón. Haré los arreglos. Picard te estará esperando afuera.";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "mtraxx_PlantVykup_12":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup3 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Maracaibo_ExitTown", "rld", "loc17", "Mtraxx_PlantPlantVykup_2");
		break;
		
		case "mtraxx_PlantVykup_13":
            dialog.text = "Si viene con la cantidad completa, dudo que lo rechace. Así que apúrate, Capitán.";
			link.l1 = "Volveré pronto.";
			link.l1.go = "mtraxx_PlantVykup_14";
		break;
		
		case "mtraxx_PlantVykup_14":
            DialogExit();
			NextDiag.CurrentNode = "mtraxx_PlantVykup_15";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
		break;
		
		case "mtraxx_PlantVykup_15":
            dialog.text = "¿Ha traído el oro para Jean Picard, Capitán? El tiempo apremia.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Soy bien consciente de eso. Así que aquí tienes, toma tu oro y dame a mi nuevo sirviente de casa.";
				link.l1.go = "mtraxx_PlantVykup_16";
			}
			else
			{
				link.l2 = "Todavía recogiendo, usted es el que puso un precio tan alto, señor.";
				link.l2.go = "mtraxx_PlantVykup_14";
			}
		break;
		
		case "mtraxx_PlantVykup_16":
            dialog.text = "Nunca he visto a alguien gastar tanto en adquirir un sirviente. Pero a juzgar por lo bien vestido que estás, debes estar acostumbrado a tales compras grandiosas. Informaré a mis hombres, y Picard te estará esperando en la salida.";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
	}
} 
