// Филипп де Пуанси - генерал-губернатор французских колоний
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyFox"))
			{
				dialog.text = "Saludos, "+pchar.name+". Pase, ya me han informado.";
				link.l1 = "¿Informado? Puede que haya algún error, Excelencia. Vine a informar sobre la exitosa finalización de su misión, pero veo que no está de buen ánimo.";
				link.l1.go = "PZ_PoincyAngry1";
				DeleteAttribute(pchar, "questTemp.Terrapin");
				DeleteAttribute(pchar, "questTemp.Terrapin_KathyFox");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "done")
			{
				dialog.text = "Me alegra verte, "+pchar.name+". Estoy informado acerca de tus logros y, lo más importante, ¡has tenido éxito en tu misión! Te has mostrado del mejor lado y me alegra no haberme equivocado contigo.";
				link.l1 = "¿Puedo recibir una orden por escrito de vuestra parte para liberar a mi hermano ahora?";
				link.l1.go = "serve";
				AddCharacterExpToSkill(pchar, "Sneak", 500);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga") && CheckAttribute(pchar, "questTemp.Sharlie.LevasserDied"))
			{
				dialog.text = "Me alegra verte, "+pchar.name+". He oído hablar de tus hazañas y, lo más importante, ¡tu misión está cumplida! Aunque, debo decir, esperaba una idea más inteligente que un ataque frontal. Lástima por los soldados franceses muertos.\nPero la guerra es la guerra, siempre hay bajas. Has cumplido con tu deber, y me alegra haber tenido razón sobre ti.";
				link.l1 = "¿Puedo recibir ahora de usted una orden por escrito para liberar a mi hermano?";
				link.l1.go = "serve";
				DeleteAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga");
				DeleteAttribute(pchar, "questTemp.Sharlie.LevasserDied");
				break;
			}
			// Jason НСО 
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && GetCharacterIndex("Noel") == -1 && pchar.questTemp.Patria != "epizode_12_barondie" && pchar.questTemp.Patria != "epizode_12_baronfail" && pchar.questTemp.Patria != "epizode_12_baronkilled" && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "Es un placer verte, Charles. Ante todo, permíteme felicitarte por completar con éxito la compleja tarea de proteger la colonia de Saint-Pierre de los invasores españoles. ¡Brillante trabajo, mi amigo!";
					link.l1 = "Gracias, Chevalier.";
					link.l1.go = "patria";
					Patria_SetInspector();
				}
				else
				{
					dialog.text = "Me alegra verte, Charles. Ante todo, permíteme felicitarte por completar con éxito la compleja tarea de proteger la colonia de Saint-Pierre de los invasores españoles. ¡Brillante trabajo, mi amigo! Te presento otra oportunidad para cooperar con la Armada. Francia necesita desesperadamente oficiales como tú. Espero que esta vez seas más sensato... ¡Toma el patente, Capitán Charles de Maure!";
					link.l1 = "Gracias, Chevalier. ¡Me alegra ayudar al país y estoy ansioso por seguir sirviéndolo!";
					link.l1.go = "patria";
					if (!CheckCharacterItem(pchar, "suit1")) GiveItem2Character(pchar, "suit1");
					GiveItem2Character(pchar, "patent_fra");
					EquipCharacterbyItem(pchar, "patent_fra");
					Items[sti(pchar.EquipedPatentId)].TitulCur = 2; 
					Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
					ChangeCharacterNationReputation(pchar, FRANCE, 100);
					Patria_SetInspector();
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (!CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "Charles, me decepcionas. Como resultado de tus imprudentes acciones, perdiste tu patente y el rango en la Armada Real. No hay lugar para más cooperación. Despedido.";
					link.l1 = "Mm...";
					link.l1.go = "patria_patentfail";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_1_return")
				{
					dialog.text = "Me alegra verte, Charles. ¡Informa!";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "El trabajo está hecho, el rescate de la colonia de San José ha sido recibido. Pero hay malas noticias: en la batalla con el fuerte, el 'Eclatant' fue hundido. Advertí al capitán que tuviera cuidado, pero no me escuchó, y...";
						link.l1.go = "patria_8_1";
					}
					else
					{
						link.l1 = "El trabajo está hecho, el rescate de la colonia de San José ha sido recibido.";
						link.l1.go = "patria_8";
					}
					break;
				}
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(!IsUniformEquip())
				{
					dialog.text = "Monsieur, ¡de ahora en adelante solo entre en mis salones con un uniforme apropiado!";
					link.l1 = "...";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_2_return" && IsUniformEquip())
				{
					dialog.text = "¡Barón, capitán! ¡Me alegra verte!";
					link.l1 = "La misión está completada, Chevalier.";
					link.l1.go = "patria_14";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_3_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", capitán. ¿Qué noticias traes?";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "Los españoles planearon un ataque a Port-au-Prince. En el extremo occidental de La Española encontramos una poderosa escuadra enemiga. Fue completamente destruida. Sin embargo, el 'Eclatant' fue hundido.";
						link.l1.go = "patria_26_1";
					}
					else
					{
						link.l1 = "Los españoles sí planearon un ataque a Port-au-Prince. En el extremo occidental de La Española encontramos una poderosa escuadra enemiga. Fue completamente destruida.";
						link.l1.go = "patria_26";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_4_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", Charles. ¿Cómo está Mynheer Stuyvesant?";
					link.l1 = "Todo está bien, Chevalier. La entrega fue exitosa, aquí está la respuesta a su carta.";
					link.l1.go = "patria_31";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_5_return" && IsUniformEquip())
				{
					dialog.text = "Charles, Barón... ¿Ya has regresado?";
					link.l1 = "...";
					link.l1.go = "patria_36";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_6_return" && IsUniformEquip())
				{
					dialog.text = "No me gusta tu ceño, Charles. ¿Qué dijo Stuyvesant? ¡Informa!";
					if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win") link.l1 = "Literalmente, dijo: 'dile al Chevalier que ya no está a cargo de Saint-Martin. Basta de él. Y respecto a la inspección del estado, que se le ocurra algo. Nunca fue difícil para De Poincy poner todo patas arriba'. Después de anunciar este mensaje, el señor me echó de la residencia. Ese fue el final de nuestras negociaciones.";
					else link.l1 = "Bueno, esto es lo que dijo: 'tu señor ha sido demasiado codicioso en Saint-Martin últimamente, así que es hora de calmar su insaciable hambre.' Después de esto, intentó arrestarme. Tuve que abrirme camino hasta el barco con una espada. Tanto por la diplomacia holandesa.";
					link.l1.go = "patria_43";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_go" && IsUniformEquip())
				{
					dialog.text = "Capitán, te hemos estado esperando. Expliqué el estado actual de los asuntos al barón, y él apoyó plenamente mi decisión. Los holandeses pagarán por su arrogancia.";
					link.l1 = "¿Es la guerra entonces?";
					link.l1.go = "patria_51";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_continue" && IsUniformEquip() && pchar.location.from_sea == "Charles_town") // add-7
				{
					Patria_HunterShipChecker();
					if (CheckAttribute(pchar, "questTemp.Patria.Hunter.GiveShip"))
					{
						dialog.text = "Entonces, mi amigo, veo que has capturado el barco de las Indias Orientales con las mercancías. ¡Excelente!";
						link.l1 = "Te estoy entregando un barco, dé órdenes a los oficiales del puerto, Chevalier.";
						link.l1.go = "patria_55";
					}
					else
					{
						dialog.text = "¿Tienes alguna pregunta, Charles?";
						link.l1 = "No en este momento, Monsieur. Me pondré en marcha, entonces...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8" && IsUniformEquip())
				{
					dialog.text = "¡Finalmente, has llegado, capitán! ¡Hay una emergencia en San Cristóbal!";
					link.l1 = "¿Una escuadra hostil?";
					link.l1.go = "patria_59";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_wait" && IsUniformEquip() && GetCompanionQuantity(pchar) < 5)
				{
					dialog.text = "¿Estás listo para recibir nuestro lugre de correo?";
					link.l1 = "Lo estoy.";
					link.l1.go = "patria_64";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_return")
				{
					dialog.text = "¡Capitán de Maure, Señor Doily! ¡Me alegra verte! ¡Toda la ciudad observó cómo diste una lección a los sinvergüenzas hispano-holandeses que deseaban nuestra colonia!";
					link.l1 = "Era mi deber, Chevalier.";
					link.l1.go = "patria_66";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_start" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", Charles. Comencemos, ¿de acuerdo?";
					link.l1 = "Por supuesto, Chevalier. Por eso estoy aquí.";
					link.l1.go = "patria_69";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_return" && IsUniformEquip())
				{
					dialog.text = "¡Me alegra dar la bienvenida en mi oficina al Vicealmirante de la Armada Real de Francia! Sí, mi amigo, no te has equivocado: personalmente firmé la orden sobre tu nombramiento. Formalmente, aún debe ser aprobado en Francia, pero ni siquiera dudes de que así será. ¡Felicidades!";
					link.l1 = "¡Sirvo a mi nación!";
					link.l1.go = "patria_76";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_10_return" && IsUniformEquip())
				{
					if (GetQuestPastDayParam("questTemp.Patria.Curacao.Date") < 30) sTemp = "estará listo pronto y"; // в зависимости от времени сколько добирался
					else sTemp = "está listo y";
					dialog.text = "¿Has tenido éxito en tus empeños? ¿Quedó satisfecho el Coronel Doily?";
					link.l1 = "Todo salió perfectamente, Chevalier. La caravana de Stuyvesant fue capturada, todos los esclavos llevados a Jamaica, el escuadrón del coronel "+sTemp+" en camino a Curazao.";
					link.l1.go = "patria_81";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_11_return" && IsUniformEquip())
				{
					dialog.text = "¡Gloria a los vencedores! ¡Felicitaciones, felicitaciones, mi amigo! Nunca dejas de asombrar.";
					link.l1 = "Gracias, Chevalier. Stuyvestant fue castigado y está listo para pagar indemnizaciones, la paz ha sido restaurada, Saint-Martin pertenece únicamente a Francia ahora.";
					link.l1.go = "patria_85";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_continue")
				{
					dialog.text = "Entonces, mi amigo, me alegra verte de nuevo. ¿Has descansado bien?";
					link.l1 = "Sí, Chevalier. Fue un descanso muy necesario... ¿Mencionaste algún negocio delicado?";
					link.l1.go = "patria_88";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronalive")
				{
					dialog.text = "¡Amigo mío, debes ser un hechicero! ¡Lograste realizar una hazaña! Nuestro Barón ya no quiere crear una Compañía de Comercio aquí.";
					link.l1 = "Creo que su único deseo ahora mismo es estar de vuelta en París.";
					link.l1.go = "patria_103";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_barondie")
				{
					dialog.text = "Charles, ¿has oído sobre el Barón? Fue capturado por piratas...";
					link.l1 = "Sí, Chevalier. Ay, el barón está muerto. Lo sé con certeza.";
					link.l1.go = "patria_112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronfail")
				{
					dialog.text = "Charles, ¿cómo va tu progreso? Me dijeron que el Barón abordó tu barco...";
					link.l1 = "Sí, Chevalier. Estaba a bordo, estaba trabajando con él, pero... murió de fiebre.";
					link.l1.go = "patria_x112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronkilled")
				{
					dialog.text = "Charles, ¿cómo va tu progreso? Me dijeron que el Barón abordó tu barco...";
					link.l1 = "Sí, Chevalier. Estaba a bordo, estaba trabajando con él, pero... murió en una batalla.";
					link.l1.go = "patria_y112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronwin")
				{
					dialog.text = "¡Amigo mío, debes ser un hechicero! ¡Lograste realizar una hazaña! Nuestro Barón ya no quiere crear una Compañía de Comercio aquí.";
					link.l1 = "Probablemente se dirige a París ahora.";
					link.l1.go = "patria_117";
					break;
				}
				dialog.text = "¿Tienes alguna pregunta, Charles?";
				link.l1 = "No en este momento, monsieur. Me iré entonces...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "¿Qué quieres? ¿Monsieur?";
			link.l1 = "Nada serio, solo una visita de cortesía. Me voy ahora...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// в тюрьме при старте игры
		case "Puancie_Jail":
			dialog.text = "Buen día para ti, Charles. Permíteme presentarme: soy Philippe de Poincy y yo...";
			link.l1 = "¿Por qué diablos me has puesto en la prisión? ¡Es inapropiado! Soy un noble francés y...";
			link.l1.go = "Puancie_Jail_1";			
			// belamour legendary edition -->
			link.l2 = "Buenas... ¿tardes? Buen chiste, señor. ¿Cómo sabe quién soy?";
			link.l2.go = "Puancie_Jail_1a";	
		break;
		
		case "Puancie_Jail_1a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			dialog.text = "¡Joven, te pido que no me interrumpas! ¡Estás hablando con el Gobernador General de las colonias francesas del archipiélago caribeño! Perdonaré tu tono insolente solo porque no podías saber quién estaba frente a ti. Pero te recomendaría que seas más comedido.";
			link.l1 = "Hmm... Lo siento, Su Excelencia.";
			link.l1.go = "Puancie_Jail_2";
		break;
		
		case "Puancie_Jail_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			// <-- legendary edition
			dialog.text = "¡Escúchame, joven, y no me interrumpas! ¡Estás hablando con el Gobernador General de las colonias francesas en el archipiélago del Caribe! Perdonaré tu tono solo por tu ignorancia sobre con quién estabas hablando. Pero te recomendaría ser más comedido en el futuro.";
			link.l1 = "Hum... perdóneme, su Excelencia.";
			link.l1.go = "Puancie_Jail_2";			
		break;
		
		case "Puancie_Jail_2":
			dialog.text = "Mejor. Ahora, en cuanto a tu pregunta anterior, fuiste considerado, por error, como un espía español y puesto bajo arresto hasta que se aclare la situación. Malditos castellanos, se han vuelto más activos últimamente, por eso ordené detener a toda persona sospechosa.\nPero ahora sabemos quién eres... eres realmente Charles de Maure, hermano de Michelle de Monper, y personalmente vine aquí para liberarte. ¡Y me gritas como un niño pequeño!";
			link.l1 = "Perdóneme de nuevo, su Excelencia. ¿Estoy libre ahora?";
			link.l1.go = "Puancie_Jail_3";			
		break;
		
		case "Puancie_Jail_3":
			dialog.text = "Sí, lo estás. Pero quiero hablar en privado contigo antes de que un sargento abra tu celda. ¿Sabes que tu hermano, uno de los guerreros más dignos de la Orden de Malta, fue arrestado y puesto bajo custodia?";
			link.l1 = "Solo sabía que mi hermano está en problemas y necesita ayuda. Por eso vine aquí desde París.";
			link.l1.go = "Puancie_Jail_4";			
		break;
		
		case "Puancie_Jail_4":
			dialog.text = "Me alegra escuchar eso. Quiero que sepas que monsieur de Monper está en serios problemas. Tengo todas las razones para sospecharlo de abuso de autoridad, apropiación indebida de bienes y perjurio. Pero tú puedes ayudarlo.";
			link.l1 = "Monsieur, ¿podría decirme más? No entiendo, Michel era el orgullo de la Orden y...";
			link.l1.go = "Puancie_Jail_5";			
		break;
		
		case "Puancie_Jail_5":
			dialog.text = "Yo también lo creía. ¡Todos lo creíamos! Pero sus acciones recientes nos hicieron... dudar de su lealtad a la Orden, así que fue arrestado. Michel te contará los detalles él mismo. Te explicará cómo podrías ayudarle a manejar las acusaciones y evitar una desgracia.";
			link.l1 = "¿Dónde está mi hermano ahora? Me dijiste que está en la prisión, pero no lo he visto por aquí...";
			link.l1.go = "Puancie_Jail_6";			
		break;
		
		case "Puancie_Jail_6":
			dialog.text = "¿Dije encarcelado, joven? ¿Estás escuchando siquiera? Dije que está bajo arresto. No es lo mismo. Michel de Monper está retenido bajo arresto en la base subterránea de Saint-Pierre, que es propiedad de la Orden de Malta.\nTe permito visitar la base sin ninguna limitación y hablar con tu hermano tantas veces como creas necesario. Los oficiales y soldados de la Orden están al tanto de mis instrucciones y no te detendrán.";
			link.l1 = "¿Dónde está esa base subterránea?";
			link.l1.go = "Puancie_Jail_7";			
		break;
		
		case "Puancie_Jail_7":
			dialog.text = "Está aquí, en Saint-Pierre, por supuesto. Encuentra la base y entra por la puerta con los símbolos de la Orden. Baja a la casamata en el segundo nivel del sótano. Monsieur Monper estará allí. Pero no te preocupes: al salir de la prisión, te recibirán y te escoltarán hasta tu hermano, he arreglado todo... Eso es todo. Espero que nos volvamos a ver, Charles. ¡Sargento!";
			link.l1 = "¡Por favor, espere, su Excelencia! ¿Y qué hay de mis... pertenencias? ¿Mi espada y lo demás?";
			link.l1.go = "Puancie_Jail_8";			
		break;
		
		case "Puancie_Jail_8":
			dialog.text = "Sus pertenencias fueron confiscadas para el pago de la deuda de su hermano. Adiós, Monsieur de Maure.";
			link.l1 = "¿Qué diablos...?";
			link.l1.go = "Puancie_Jail_9";			
		break;
		
		case "Puancie_Jail_9":
			DialogExit();
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Sharlie_GoFromPrison", 3.5);
			NextDiag.CurrentNode = "First time";
			locCameraFromToPos(-11.09, 0.65, 3.05, true, -12.59, 0.09, -4.66);
		break;
		
		// возвращаем деньги
		case "saga":
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Charles_townhall", "reload1_back", false);
			dialog.text = "¡Ajá, Charles de Maure en persona! Me alegra verte. ¿Supongo que has venido aquí para discutir el destino de tu hermano conmigo?";
			link.l1 = "Estoy listo para saldar lo que Michel de Monper le debe a la Orden y personalmente a usted.";
			if (sti(pchar.money) >= 1000000) link.l1.go = "saga_1";
			else link.l1.go = "saga_exit";			
		break;
		
		case "saga_exit":
			dialog.text = "Hm.. Pero, ¿dónde está el dinero? Tienes un extraño sentido del humor, joven, y no lo entiendo.";
			link.l1 = "Perdóneme, Chevalier. Olvidé el dinero en mi cofre del barco. Volveré pronto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_repeat";	
		break;
		
		case "saga_repeat":
			dialog.text = "¿Has traído el dinero, Charles?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "¡Por supuesto! Espero que esta suma cubra por completo todos tus gastos.";
				link.l1.go = "saga_1";
			}
			else
			{
				link.l1 = "Aún no...";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_repeat";
			}		
		break;
		
		case "saga_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Charles");
			AddMoneyToCharacter(pchar, -1000000);
			dialog.text = "¡Espléndido! Los tomaré de ti. ¡Te has mostrado de tu mejor lado, Charles!";
			link.l1 = "¿Cuándo recibiré una orden para la liberación de Michel de Monper?";
			link.l1.go = "saga_2";			
		break;
		
		case "saga_2":
			dialog.text = "No tengas prisa, joven. Solo puedo respetar que pagues las deudas y protejas a tu familia poniendo tu propia vida en peligro. Es una nobleza rara en estos días... Pero el dinero no es la parte principal de esta triste historia. Tu hermano consiguió una suma tan grande con la condición de realizar una misión muy delicada.\nMichel de Monper, como fiel católico, había jurado sobre el Libro que encontraría una manera de castigar a un insolente hereje y restaurar la justicia que él violó para la gloria de la Orden y la Santa Iglesia...";
			link.l1 = "¡Pero no podrá cumplir su palabra estando arrestado! Si lo liberas, los dos seremos capaces de completar la misión mucho más rápido que si lo hiciera yo solo.";
			link.l1.go = "saga_3";			
		break;
		
		case "saga_3":
			dialog.text = "Ves, mi amigo, tu hermano me ha dado una fuerte razón para no confiar en su decencia. No hay garantías de que no escapará y romperá su juramento. Así que si quieres quitarle todas las acusaciones, cumple el juramento tú mismo. Monsieur de Monper te dirá los detalles.";
			link.l1 = "Hum... No esperaba eso. Pero no me dejas otra opción. Tomaré mi decisión final después de hablar con mi hermano.";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			dialog.text = "Empiezo a tomarte mucho aprecio, Charles. Quizás, algún día, lleguemos a ser amigos. En cualquier caso, este es mi último plazo para liberar a tu hermano. Te doy mi palabra de que la reputación de tu familia no se verá perjudicada si haces lo que tu hermano no hizo. Y podrás contar con mi amistad en el futuro.";
			link.l1 = "Te he entendido completamente. ¡Adiós!";
			link.l1.go = "saga_5";			
		break;
		
		case "saga_5":
			DialogExit();
			pchar.questTemp.Saga = "mishelle";//Сага - старт
			AddQuestRecord("Sharlie", "21");
			NextDiag.CurrentNode = "First time";
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
		break;
		
		case "serve":
			dialog.text = "No te preocupes, "+pchar.name+" , mantendré mi palabra. Tu hermano será liberado y todas las acusaciones serán retiradas de él. La reputación de tu familia ya no está en peligro. Diría que todo esto es por tus méritos, y solo tuyos. Tu padre puede estar orgulloso de haber criado a un hijo así.";
			link.l1 = "Gracias por las amables palabras, Chevalier. ¿Puedo dirigirme a Martinica de inmediato?";
			link.l1.go = "serve_1";	
			Island_SetReloadEnableGlobal("Tortuga", true);
			CloseQuestHeader("Terrapin");
			SetFunctionTimerCondition("Terrapin_SetFontene", 0, 0, 5, false); // таймер
		break;
		
		case "serve_1":
			dialog.text = "Espera un poco, amigo mío. Espero que pueda llamarte mi amigo, ¿verdad? Quiero expresar mi gratitud personalmente. He estado observando tu progreso desde que llegaste aquí, y sé de la mayoría de tus hazañas. Te has hecho un gran nombre en el Caribe y, sin duda, también eres bien conocido y respetado en algunos sectores particulares de la sociedad. Francia necesita a gente como tú.\n¡Capitán "+GetFullName(pchar)+"! ¡Por el poder que me otorga Su Majestad, el Rey de Francia, tengo el honor de ofrecerte una patente de Capitán de la Marina Real, y tomar bajo tu mando el navío de la Armada Francesa, ¡una fragata ligera llamada 'Gryffondor'!\nSu ex capitán de Fontenot será gobernador de Tortuga gracias a ti, y la mejor fragata ligera del Caribe necesita un capitán. ¿Aceptas la oferta?";
			link.l1 = "Interesante. ¿A cambio de qué?";
			link.l1.go = "serve_2";		
		break;
		
		case "serve_2":
			dialog.text = "A cambio de muy poco. Una décima parte de tu botín y cumplir misiones delicadas a veces. Estoy esperando tu decisión.";
			link.l1 = "¡Nadie rechazaría tal oferta, su Excelencia! ¡Es un honor servir a mi nación!";
			link.l1.go = "serve_3";
			link.l2 = "Perdóname por ser poco modesto, pero tengo que rechazar su oferta por ahora. Los asuntos de mi familia podrían requerir un regreso inmediato a la patria.";
			link.l2.go = "serve_no";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "serve_no":
			ChangeCharacterComplexReputation(pchar, "fame", 7);
			dialog.text = "Lástima. Esperaba que aceptarías... Pero, no obstante, me veo obligado a pedirte un favor más, de hecho, también está en tu interés. Martinica está bajo ataque. Hay intensos combates en el puerto y en la ciudad misma.\nAy, no tengo a nadie más que enviar allí para ayudar a la guarnición, excepto a ti. Te pido como patriota de tu patria que rechaces el asalto por cualquier medio necesario. Espero que tengas suficientes recursos para hacerlo.\nAdemás, tu hermano todavía está allí, puedes salvarle la vida.";
			link.l1 = "¿Mi hermano está en peligro? ¡Estoy en camino!";
			link.l1.go = "serve_exit";			
		break;
		
		case "serve_3":
			dialog.text = "¡Qué palabras tan honorables! ¡Palabras de un verdadero soldado y leal hijo de la Patria! Felicitaciones, monsieur "+GetFullName(pchar)+". Se le otorga el rango de Comandante de las fuerzas navales de Francia. Acepte este uniforme de mi parte. ¡Llévelo con orgullo y sea digno de él!";
			link.l1 = "¡Sirvo a mi nación!";
			link.l1.go = "serve_4";	
			locCameraFromToPos(-2.63, 2.20, -4.96, true, 2.64, 0.22, -4.96);
			npchar.greeting = "puancie_1";			
		break;
		
		case "serve_4":
			dialog.text = "La fragata ligera 'Gryffondor' está ahora bajo tu mando. Desde este momento, este excelente barco es tuyo. ¡Usa sus altas cualidades para la gloria de Su Majestad y para fortalecer la influencia francesa en el archipiélago del Caribe!";
			link.l1 = "¡De inmediato!";
			link.l1.go = "serve_5";
			LAi_Fade("SharlePutsSuit", "");
		break;
		
		case "serve_5":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Pero tu escuadrón ya es demasiado grande, así que vuelve a buscar el 'Gryffondor' cuando te deshagas de un barco.";
				link.l1 = "Está bien. Haré eso.";
				link.l1.go = "serve_wait";		
			}
			else
			{
				dialog.text = "Junto con el barco obtendrás a su capitán en funciones y a la tripulación. Si quieres, puedes dejarlo bajo tu mando o destinarlo desde un barco y le encontraremos otro puesto.";
				link.l1 = "¡Entendido!";
				link.l1.go = "serve_6";
			}
		break;
		
		case "serve_6":
			dialog.text = "Pero tengo malas noticias para usted, capitán. Me acaban de informar que Martinica está bajo ataque. Hay una feroz batalla en el puerto y en la ciudad misma.\nLamentablemente, no tengo a nadie más que pueda enviar allí para ayudar a la guarnición, excepto a usted. Aquí está su primera misión:\n ¡Proteja Saint-Pierre! Además, su hermano aún está allí, puede salvar su vida.";
			link.l1 = "¿Mi hermano está en peligro? ¡Estoy en camino!";
			link.l1.go = "serve_7";
		break;
		
		case "serve_7":
			DialogExit();
			locCameraTarget(PChar);
			locCameraFollow();
			CreateGriffondor();
			sld = characterFromId("GriffOfficer");
			SetCharacterRemovable(sld, true);
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "24");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 500);
			pchar.questTemp.GoldenGirl_Block = true;	// Запрещаем квест Дороже Золота
		break;
		
		case "serve_wait":
			DialogExit();
			NextDiag.CurrentNode = "serve_shipcheck";
		break;
		
		case "serve_shipcheck":
			dialog.text = "¿Estás listo para tomar el 'Gryffondor' bajo tu mando?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "Todavía no, estoy reposicionando mis barcos en el escuadrón...";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Soy yo.";
				link.l1.go = "serve_5a";
			}
			NextDiag.TempNode = "serve_wait";
		break;
		
		case "serve_5a":
			dialog.text = "¡Espléndido! Junto con el barco recibirás a su capitán en funciones y a la tripulación. Si lo deseas, puedes dejarlo bajo tu mando o destituirlo del barco y le encontraremos otra posición.";
			link.l1 = "¡Entendido!";
			link.l1.go = "serve_6";
		break;
		
		case "serve_exit":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "23");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
		break;
		
		// Jason НСО
		case "patria":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince"); // Rebbebion, удалить команду пиратов на всякий
			dialog.text = "¡Y esto es solo el comienzo, monsieur! ¡Estoy seguro de que llegarás lejos, con tales talentos militares! Y ya tengo otro encargo para un excelente oficial naval, con el cual, estoy seguro, te manejarás igual de bien. Además, está directamente relacionado con tu misión anterior.";
			link.l1 = "Soy todo oídos, monsieur";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Pero permítame primero presentarle a la persona que ha entrado en mi oficina. Le presento al Barón Noel Forget, miembro honorario de la Compañía de Comercio de las Indias Occidentales Francesas. Ha llegado al archipiélago para inspeccionar nuestras colonias con el fin de expandir la organización de plantaciones de caña de azúcar y otros cultivos, así como explorar la posibilidad de desarrollar lazos comerciales en nuestra región. Desde París se prescribe darle todo tipo de apoyo y asistencia en estos asuntos, lo cual sin duda haremos. Barón, le presento a Monsieur Charles de Maure, uno de los capitanes más talentosos al servicio de Francia...";
			link.l1 = "";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			DialogExit();
			sld = characterFromId("Noel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_3":
			dialog.text = "Entonces, Charles, mientras el barón y yo inspeccionamos Saint Christopher, te asigno la siguiente tarea. Nadie puede atacar asentamientos franceses y esperar salir impune, y los españoles, aunque ya se les ha dado una lección por la agresión en Martinica, deben responder por sus crímenes con sus bolsillos y compensar el daño hecho a la colonia.\nJunto con el barón francés, llegó una poderosa escuadra compuesta por un formidable barco de 66 cañones, 'Eclatant'. El capitán del barco es un marinero experimentado, pero en el Caribe por primera vez, así que se pone bajo tu mando. Junto con el 'Eclatant' irás a las costas de la isla española de Trinidad, y exigirás a los españoles una compensación monetaria de trescientos mil pesos por el ataque a Saint-Pierre.";
			link.l1 = "Chevalier, ¿cree usted sinceramente que los españoles van a estar de acuerdo?";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Estoy seguro de ello... después de que el 'Eclatant' y tu escuadrón hayan hecho pedazos el Fuerte San José. Desembarcar tropas y tomar la ciudad, perdiendo soldados, creo que no será necesario. Ataca sin previo aviso, destruye el fuerte, y luego señala al comandante que quieres establecer las condiciones. En esta situación, los españoles no tendrán a dónde ir, y preferirán pagar. ¿Qué harías si actuases en el lugar del gobernador de la ciudad que quedó sin protección?";
			link.l1 = "Hmm, parece razonable, Chevalier.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "¿Está claro lo que tienes que hacer?";
			link.l1 = "Sí, su Gracia.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip())
			{
				dialog.text = "Entonces ponte a ello. Aquí tienes una carta para el Capitán del 'Eclatant' con la confirmación de tu autoridad. Este excelente barco con una tripulación bien entrenada está ahora a tu disposición. Charles, y no olvides que ahora sirves a Francia, y para comunicarte adecuadamente con funcionarios como yo, se aconseja vestir un uniforme. Te queda perfecto. ¡Buena suerte, Capitán de Maure!";
			}
			else
			{
				dialog.text = "Entonces, ponte a ello. Aquí tienes una carta para el Capitán del 'Eclatant' con la confirmación de tu autoridad. Este excelente barco con una tripulación bien entrenada está ahora a tu disposición. Ah, y Charles: ¡ponte el uniforme de capitán, te lo ordeno! Primero, no es digno de un oficial de la Armada Real Francesa parecer un comerciante o algún corsario, y segundo, tu uniforme te queda perfecto. ¡Ejecuta de inmediato, Capitán de Maure!";
			}
			link.l1 = "";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "1");
			pchar.questTemp.Patria = "epizode_1";
			Patria_SetEcliaton();
			pchar.questTemp.GoldenGirl_Block = true;	// Запрещаем квест Дороже Золота
		break;
		
		case "patria_8_1":
			if (sti(pchar.money) >= 300000) AddMoneyToCharacter(pchar, -300000);
			else pchar.questTemp.Patria.NoMoney = "true";
			dialog.text = "¿El 'Eclatant' se hundió? ¡Charles, esto es un desastre! ¿Qué dirá ahora el ministro? ¡Me has decepcionado, Charles! Estaba seguro de que podía confiar en tu experiencia, y tú... Ay, pero tendrás que asumir la responsabilidad por esto. Escribiré un informe, y será mejor que desaparezcas por un tiempo. Tu servicio en la Marina Real ha terminado.";
			link.l1 = "Hmm... Lo siento, Monsieur. Parece que realmente es mejor para mí desaparecer durante uno o dos meses, hasta que el ministro calme su ira. Adiós, y una vez más lamento mucho haberte fallado.";
			link.l1.go = "patria_8_2";
		break;
		
		case "patria_8_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "8");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			if (CheckAttribute(pchar, "questTemp.Patria.NoMoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -20);
				ChangeCharacterNationReputation(pchar, FRANCE, -30);
				DeleteAttribute(pchar, "questTemp.Patria.NoMoney");
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -5);
				ChangeCharacterNationReputation(pchar, FRANCE, -5);
			}
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
		break;
		
		case "patria_8":
			if (sti(pchar.money) >= 300000)
			{
				dialog.text = "¡Perfecto!";
				link.l1 = "Aquí, por favor toma estos trescientos mil.";
				link.l1.go = "patria_9";
			}
			else
			{
				dialog.text = "Perfecto, pero ¿dónde está el dinero, Charles?";
				link.l1 = "¡Eh, en el cofre del barco, lo entregaré en un momento!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_8_3":
			DialogExit();
			npchar.dialog.currentnode = "patria_8_4";
		break;
		
		case "patria_8_4":
			dialog.text = "Entonces, Charles, ¿trajiste el rescate de Trinidad?";
			if (sti(pchar.money) >= 300000)
			{
				link.l1 = "Sí, Monsieur. Aquí está.";
				link.l1.go = "patria_9";
			}
			else
			{
				link.l1 = "¡Lo traeré en un momento!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_9":
			AddMoneyToCharacter(pchar, -300000);
			dialog.text = "Estoy complacido contigo, Charles, nunca decepcionas. La tarea no fue fácil, y se te otorga una suma de 50,000 pesos del monto de redención como recompensa. Tómala, es toda tuya.";
			link.l1 = "Mis gracias, Chevalier.";
			link.l1.go = "patria_10";
		break;
		
		case "patria_10":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "Ya hay una nueva tarea para ti. Monsieur Forget completó la inspección en Saint Christopher, y ahora desea visitar nuestras colonias del norte. Te pido que lleves al barón a Tortuga y La Española, que le ayudes en todo lo posible en sus asuntos y cumplas con sus peticiones. ¿Está claro, Charles?";
			link.l1 = "Por supuesto, Chevalier.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "El Barón tiene poco tiempo, así que le pido que no se distraiga con otros asuntos y que no retrase el viaje por más de dos meses.";
			link.l1 = "Por supuesto, Monsieur. El viaje entre las islas no toma mucho tiempo, a menos que los asuntos de Monsieur Forget en las colonias sean demorados.";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Perfecto. Entonces, el Barón viajará en tu barco. Dale el mejor camarote que haya.";
			link.l1 = "¡Por supuesto, Caballero!";
			if(IsUniformEquip()) link.l1.go = "patria_13";
			else link.l1.go = "patria_13_1";
		break;
		
		case "patria_13_1":
			dialog.text = "Y una cosa más, Charles: ¡Otra vez estás sin tu uniforme de oficial! Esta es tu última advertencia. De ahora en adelante, te pido que vengas a verme solo con el uniforme, de lo contrario, no te escucharé. Estás de servicio, y la disciplina debe serlo todo, especialmente en la apariencia de un oficial naval.";
			link.l1 = "Perdóname, Chevalier. Esto no volverá a suceder.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "9");
			pchar.questTemp.Patria = "epizode_2";
			Patria_VisiterBegin();
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_14":
			sld = characterFromId("Noel");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
			dialog.text = "No tenía duda de que tu viaje sería exitoso. ¿Alguna noticia de Tortuga o de Puerto Príncipe?";
			link.l1 = "...";
			link.l1.go = "patria_15";
		break;
		
		case "patria_15":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_16";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_16":
			dialog.text = "";
			link.l1 = "Sí, Chevalier, traigo noticias, pero no son muy agradables. Primero, el Gobernador de Port-au-Prince está seguro de que los españoles están preparando un ataque a la colonia y para ello están reuniendo una escuadra militar en... em-m, ¿cómo se llama?... en Santiago, sí. Y esto no parece ser un chisme. Creo que no podemos ignorar este asunto, especialmente porque las plantaciones de Port-au-Prince son de las mejores que he visto.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "¿Están los españoles preparando un ataque a Puerto Príncipe? Hmm... De acuerdo. Te daremos instrucciones para que te encargues de esto, capitán Charles de Maure. 'Eclatant' está recién reparado, equipado y listo para zarpar...";
			link.l1 = "Y otra cosa, Monsieur: en París, la isla de Saint-Martin, que se encuentra al norte de aquí, se considera una colonia francesa, pero el Capitán Charles de Maure me dijo que los holandeses tienen el control allí. ¿Es así, Chevalier?";
			link.l1.go = "patria_18";
		break;
		
		case "patria_18":
			dialog.text = "Hmm... Eso es cierto hasta cierto punto. Saint Martin es una colonia francesa. Sin embargo, Barón, desde un punto de vista económico, esta isla es absolutamente inútil: el área es pequeña, el suelo allí es pobre, magro, el agua dulce es escasa, y la que hay en los pozos es turbia y amarga. Incluso me dijeron que allí recolectan agua de lluvia para beber.\nPor lo tanto, Saint Martin fue transferida a la Compañía Holandesa de las Indias Occidentales para un arrendamiento a largo plazo, que la utiliza como un punto de tránsito norteño para los barcos de la Compañía desde la región hacia la metrópoli. Los holandeses expandieron el asentamiento de Phillipsburg allí, construyeron un fuerte y un puerto, y para aquellos que han llegado al archipiélago relativamente recientemente, como el Capitán Charles de Maure, Saint Martin parece una colonia holandesa.";
			link.l1 = "¿Pero de jure la isla nos pertenece?";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			dialog.text = "Por supuesto. Pero como dije, es más rentable obtener dinero por el alquiler que usar sus escasos recursos.";
			link.l1 = "Me parece que esta isla sería muy útil para la Compañía de Comercio de las Indias Occidentales Francesas cuando aparezca en el Caribe. El significado de eso que acabas de anunciar: el puesto avanzado del norte en el camino a Europa. Necesito visitar esta colonia, y es muy probable que el alquiler de la isla a los holandeses se suspenda.";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Primero, necesitas enviar una consulta a Willemstad, al director de la Compañía Holandesa de las Indias Occidentales, la Casa de Moneda de Peter Stuyvesant. Debe dar su permiso para la inspección de la isla, después de todo, los holandeses han estado allí mucho tiempo.";
			link.l1 = "Entonces necesitamos enviar un mensajero a Willemstad.";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			dialog.text = "El problema es que el señor Stuyvesant rara vez está presente en Willemstad, está constantemente viajando y ocupándose de los asuntos de la Compañía en su galeón...";
			link.l1 = "¿Pero al menos a veces está presente allí, supongo? De todos modos, los holandeses están obligados a asegurar la inspección de la isla a sus legítimos propietarios. ¿Por qué no enviamos una carta al Gobernador de Philipsburg?";
			link.l1.go = "patria_22";
		break;
		
		case "patria_22":
			dialog.text = "Mynheer Martin Thomas, con todo respeto hacia él, es solo un empleado simple, la verdadera gestión la lleva a cabo la Compañía. Barón, resolveré este problema, no se preocupe, tomará algo de tiempo.";
			link.l1 = "Bueno, tengo mucho tiempo. Después de todo, todavía tenemos que visitar las colonias del sur, Guadalupe y Martinica. Es una lástima que el Capitán Charles de Maure no me acompañe esta vez, debe dirigirse una vez más a La Española...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetActorType(pchar); // 17-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_24";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
		break;
		
		case "patria_24":
			dialog.text = "¡Sí, sí, estamos retrasando a nuestro querido capitán con nuestras aburridas conversaciones! ¡Charles, lleva el 'Eclatant' al escuadrón, avanza hacia La Española y entérate de cualquier amenaza real a Port-au-Prince por parte de los españoles. Si las hay, entonces ocúpate de ello. Sin embargo, no soy yo quien debe enseñarte, tú sabes todo mejor que yo. Si no encuentras nada, entonces no deberías perder el tiempo, te necesito aquí. Te espero con el informe no más tarde de un mes. ¡Buena suerte, mi amigo!";
			link.l1 = "Gracias, Chevalier. Zarparé de inmediato.";
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10) link.l1.go = "patria_25_1";
			else link.l1.go = "patria_25_2";
		break;
		
		case "patria_25_1":
			dialog.text = "Y una cosa más, Charles: ¿he oído que tienes problemas con las autoridades holandesas? Por favor, resuelve este asunto lo antes posible, en un futuro cercano tendrás que visitar sus colonias. Como entenderás, eso sería imposible bajo el fuego de los fuertes.";
			link.l1 = "Bien, Monsieur, se hará.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25_2":
			dialog.text = "Y una cosa más, Charles: te advierto: evita cualquier conflicto con los holandeses. En un futuro cercano tendrás que visitar sus colonias. Como entenderás, eso sería imposible bajo el fuego de los fuertes...";
			link.l1 = "Bien, Monsieur. No hay disputas con los holandeses.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "15");
			pchar.questTemp.Patria = "epizode_3";
			Patria_PortPaxBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_26_1":
			dialog.text = "¿Se hundió el 'Eclatant'? ¡Charles, esto es un desastre! ¿Qué dirá ahora el ministro? ¡Me has decepcionado, Charles! Estaba seguro de que podía confiar en tu experiencia, y tú... Ay, pero serás responsable de esto. Escribiré un informe, y será mejor que desaparezcas por un tiempo. Tu servicio en la Marina Real ha terminado.";
			link.l1 = "Hmm ... Lo siento, Monsieur. Parece que realmente es mejor para mí desaparecer durante uno o dos meses, hasta que el ministro calme su enojo. Adiós, y una vez más lamento mucho decepcionarte.";
			link.l1.go = "patria_26_2";
		break;
		
		case "patria_26_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "19");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterNationReputation(pchar, FRANCE, -5);
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
		break;
		
		case "patria_26":
			dialog.text = "¡Excelente! Mientras tengamos capitanes en nuestra armada como tú, no deberíamos temer las artimañas de los castellanos. Mañana enviaré un mensajero a Puerto Príncipe con un despacho y una carta de Francia, y al mismo tiempo dejaré caer una insinuación en una carta personal al Monsieur Jeremy Deschamps du Mussaca de que sería bueno agradecerte por el servicio, así que puedo asegurarme de que tú, Charles, recibirás una recompensa bien merecida.\nY ahora pasemos a tu siguiente tarea. Sí, amigo mío, tengo una nueva misión para ti, sin embargo esta vez no es militar sino muy delicada, y me gustaría que la realizaras.";
			link.l1 = "Soy todo oídos, Chevalier.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Supongo que recuerdas mi discusión con Monsieur Forget sobre Saint Martin. Necesitamos asegurar al barón que la colonia ha sido inspeccionada, y tú irás a Curazao, a Willemstad, al director de la Compañía, Peter Stuyvesant. Él está allí ahora mismo, y lo estará por tres semanas más. Además, necesitarás escoltar el fluyt con las mercancías de la Compañía a Curazao y entregarle a Mynheer Stuyvesant una carta de mi parte.";
			link.l1 = "¿Son estas todas las tareas?";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			dialog.text = "Sí, capitán. Infórmame sobre la respuesta de Mynheer Stuyvesant. Deberíamos llegar justo a tiempo antes de que Monsieur Forget regrese de su viaje a Martinica y Guadalupe, y finalmente podrá visitar Saint-Martin, que realmente desea visitar.";
			link.l1 = "Muy bien. ¿Puedo irme?";
			link.l1.go = "patria_29";
		break;
		
		case "patria_29":
			dialog.text = "Puedes, Charles. No tardes mucho, al barón no le gusta esperar. Y al visitar a Peter Stuyvesant, ¡asegúrate de llevar tu uniforme! Todo debe parecer oficial, si entiendes lo que quiero decir.";
			link.l1 = "Por supuesto, Chevalier. ¡Adiós!";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "20");
			pchar.questTemp.Patria = "epizode_4";
			Patria_CureerBegin();
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_1");
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_31":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Gracias, capitán, dámelo... (leyendo)... ¡Bueno, excelente! Peter Stuyvesant dice que el Barón Forget podrá visitar Saint Martin para una inspección y que el gobernador de Philipsburg será notificado al respecto y cooperará. Creo que, después de la visita, el barón tomará la decisión correcta: dejar la isla para que sea alquilada a los holandeses. \nY ahora, ¡la noticia más reconfortante, capitán! Tengo un par de cosas que decirle. Primera: tomando en cuenta todos sus logros militares, usted ha sido ascendido al rango de 'Comodoro'. ¡Acepte mis felicitaciones, Monsieur!";
			link.l1 = "¡Sirvo a Francia!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			dialog.text = "Y en segundo lugar: el gobernador de Puerto Príncipe nos ha enviado un barco mercante lleno de mercancías para ti: 500 grandes sacos de café y 500 más de cacao. Estas son toda la cosecha de las plantaciones en La Española, las que has protegido de las incursiones españolas. Además, un cargamento especialmente valioso estaba destinado para ti - 50 unidades de lignum vitae. No creo que necesite explicarte qué es eso. Tus mercancías están en el almacén de la tienda en Capsterville, y puedes ir a recogerlas del comerciante en cualquier momento.";
			link.l1 = "¡Gracias, Chevalier! ¡Noticias fantásticas!";
			link.l1.go = "patria_33";
		break;
		
		case "patria_33":
			dialog.text = "Y ahora, en cuanto a tu siguiente tarea: el Barón Forget regresará a Saint-Christopher cualquier día de estos. Lo llevarás a Saint Martin y te asegurarás de que esté bien custodiado. Y, por así decir, observarás de cerca lo que suceda en Philipsburg, y luego me informarás. No abandones la ciudad, capitán, tan pronto como llegue el barón, mi peón te encontrará e informará.";
			link.l1 = "Todo está claro. ¿Puedo irme?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "Puedes hacerlo. Unos días de descanso en tierra te vendrán bien y serán útiles.";
			link.l1 = "...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "25");
			pchar.questTemp.Patria = "epizode_5";
			pchar.quest.Patria_CureerBackOver.over = "yes"; // снять таймер
			Items[sti(pchar.EquipedPatentId)].TitulCur = 4; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.quest.Patria_SanMartin_wait.win_condition.l1 = "Timer";
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.hour  = 8+rand(2);
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l2 = "Location_Type";
			pchar.quest.Patria_SanMartin_wait.win_condition.l2.location_type = "town";
			pchar.quest.Patria_SanMartin_wait.function = "Patria_SanMartinBaron";
			pchar.questTemp.Patria.Goods = "true"; // товары-призы
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_36":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_37";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_37":
			dialog.text = "";
			link.l1 = "¡Sí, Chevalier, de vuelta ya! Tus amigos holandeses cerca de Saint Martin nos recibieron con fuego de los cañones del fuerte y nos atacaron con un escuadrón de tres barcos. ¡Solo gracias a las habilidades del capitán Charles de Maure y su tripulación logramos escapar! Parece que, el señor Peter Stuyvesant no quiere ver realmente a los enviados del rey francés en Philipsburg, ¿qué opinas de eso, Chevalier?";
			link.l1.go = "patria_38";
		break;
		
		case "patria_38":
			dialog.text = "¿Qué?! Aquí hay una carta de Stuyvesant con su firma personal, donde él garantiza...";
			link.l1 = "¡Pero el comandante del fuerte de Philipsburg obviamente recibió una carta diferente de Stuyvesant, diciéndole que disparara a discreción y nos emboscara con un escuadrón! ¿Fue eso un accidente, Chevalier?! ¡No! ¡Claramente nos estaban esperando allí! ¡Con balas de cañón y metralla!";
			link.l1.go = "patria_39";
		break;
		
		case "patria_39":
			dialog.text = "Barón, le ruego... Yo me ocuparé de esto. Inmediatamente enviaremos a nuestro querido capitán, Charles de Maure, a Curazao nuevamente para reunirse con Stuyvesant. El capitán tiene una larga experiencia manejando situaciones delicadas... Y ahora, pediré a los sirvientes que preparen un baño y un buen almuerzo para usted.";
			link.l1 = "...";
			link.l1.go = "patria_40";
		break;
		
		case "patria_40":
			DialogExit();
			LAi_SetActorType(pchar); // 14-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_41";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_41":
			dialog.text = "Charles, mi amigo, necesitas apresurarte a Willemstad. Quizás, Stuyvesant todavía esté allí. Si no, averigua dónde está y encuéntralo. Durante la reunión, cuéntale sobre el incidente y exige una explicación. Estoy confiando en tu experiencia y autoridad, y te encomiendo llevar a cabo las negociaciones. Luego, sin perder un solo minuto, regresa y repórtame los resultados de la reunión.";
			link.l1 = "La tarea está clara, Chevalier. Prepararé el barco y partiré de inmediato.";
			link.l1.go = "patria_42";
		break;
		
		case "patria_42":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "29");
			pchar.questTemp.Patria = "epizode_6";
			Patria_DiplomatBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_43":
			dialog.text = "No puedo creer esto...";
			link.l1 = "Además, en el camino de regreso fui atacado por un escuadrón de la armada holandesa. Por favor, explíqueme, Chevalier, ¿qué está pasando aquí?";
			link.l1.go = "patria_44";
		break;
		
		case "patria_44":
			dialog.text = "Mi amigo, soy consciente de lo perspicaz que eres, así que no te ocultaré nada. Lo único que te pediré es que lo que escuches no debe salir de esta sala. ¿Lo prometes?";
			link.l1 = "Por supuesto, Chevalier.";
			link.l1.go = "patria_45";
		break;
		
		case "patria_45":
			dialog.text = "Está bien. Estoy seguro de que te espera una gran carrera en la marina francesa. Con mi ayuda, por supuesto, ¡puedes ascender al rango de vicealmirante! Pero me desvío... Y ahora, en cuanto a los holandeses y Saint-Martin.\nMucho antes de que llegaras a Saint-Martin, se encontraron grandes depósitos de sal allí. Al principio, a nadie le importó, pero luego los españoles en Cuba y La Española expresaron un gran interés en ello, para salar los cadáveres de toros. Como sin duda entiendes, no podemos comerciar con España directamente, por lo tanto...";
			link.l1 = "...has creado un ‘negociador’ en forma de la Compañía Holandesa de Comercio de las Indias Occidentales...";
			link.l1.go = "patria_46";
		break;
		
		case "patria_46":
			dialog.text = "¡Precisamente! Piensas rápido y con precisión, ¡Charles! Y ahora, sabiendo sobre la inspección desde París, Stuyvesant decidió audazmente tomar el negocio de la sal en sus propias manos por completo, contando con el hecho de que no estamos interesados en contarle a todos sobre nuestro trato con los españoles. Pero ahí es donde se equivocó. ¡Nadie puede atreverse a quitarle algo de las manos al Gobernador General francés sin castigo! Y le mostraremos justamente eso.";
			link.l1 = "Según entiendo, el Barón Forget no puede saber sobre esto...";
			link.l1.go = "patria_47";
		break;
		
		case "patria_47":
			dialog.text = "Amigo mío, tienes toda la razón, el barón no necesita conocer los detalles. Ya ha sucedido bastante: un intento de quitar la vida al representante del rey de Francia, el ataque a los barcos de la misión diplomática, es decir, a ti, y lo más importante: ¡la anexión de facto de la isla de Saint-Martin! Esto es suficiente para justificar acciones militares contra los holandeses.";
			link.l1 = "¿¡Guerra!?";
			link.l1.go = "patria_48";
		break;
		
		case "patria_48":
			dialog.text = "¡Exactamente! Amigo mío, la posición de vicealmirante no está tan lejos para ti, ¿entiendes? Imagínate en las conversaciones en el Louvre con el uniforme de almirante, y el propio Luis XIV aceptará a un huésped tan honorable... ¡Tenemos que poner a los holandeses en su lugar! Stuyvesant se arrepentirá de lo que ha hecho. ¿Estás de acuerdo?";
			link.l1 = "Estoy de acuerdo, Chevalier. Los holandeses deben responder por sus acciones escandalosas y viles.";
			link.l1.go = "patria_49";
		break;
		
		case "patria_49":
			dialog.text = "Excelente. ¡Notificaré al barón de nuestra decisión y enviaré mensajeros a las colonias francesas de inmediato! Y tú, mi amigo, puedes descansar después de un largo viaje, y por favor visítame mañana después de las nueve de la mañana. Prepararé una tarea de combate para ti.";
			link.l1 = "Muy bien, Monsieur. Permítame disculparme.";
			link.l1.go = "patria_50";
		break;
		
		case "patria_50":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "33");
			pchar.questTemp.Patria = "epizode_7";
			Patria_HunterBegin();
			pchar.quest.Patria_DiplomatTimeOver.over = "yes"; // снять таймер
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_51":
			dialog.text = "Yo no lo llamaría una guerra, más bien como forzar una paz, de hecho. Y si Stuyvesant cambia de opinión, solo nos hará más felices. Por eso ahora tenemos que mostrarle que al intentar reclamar la isla de Saint-Martin, perderá mucho más de lo que ganará. Ahí es donde entras tú, Charles.";
			link.l1 = "Estoy escuchando.";
			link.l1.go = "patria_52";
		break;
		
		case "patria_52":
			dialog.text = "Saint Martin es una base de transbordo para los barcos holandeses que van a Europa. Los barcos de la Compañía regularmente se quedan en la bahía de Philipsburg. Hasta ahora, las aguas eran bastante seguras para ellos. ¡Hasta ahora, Capitán!.. Partirás hacia las costas de Saint Martin y las patrullarás, capturando los barcos mercantes de la Compañía.\nPara transportar bienes valiosos, la Compañía utiliza los Indo-Orientales, barcos duros, bien armados con grandes bodegas. Esos serán tus objetivos. Captura cinco de esos barcos junto con sus bienes y tráelos como premios a Casterville. Después de eso, continuaremos las negociaciones con Stuyvesant, y quizás, después de contar las pérdidas, cambie de opinión.";
			link.l1 = "La tarea está clara. ¿Puedo irme?";
			link.l1.go = "patria_53";
		// belamour legendary edition -->
			link.l2 = "Monsieur, me veo obligado a preguntar, pero ¿podría usted participar en la financiación de esta operación? Serán meses de navegación, reparaciones constantes y pérdidas...";
			link.l2.go = "patria_53a";
		break;
		
		case "patria_53a":
			AddMoneyToCharacter(pchar, 20000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			dialog.text = "Me temo que nuestras reservas están agotadas, Charles. El mantenimiento del Ecliaton y las batallas ya nos han costado el presupuesto de medio año de las colonias francesas. Ahora, es todo lo que puedo darte. ¡Piensa en futuras recompensas, Charles! ¡Un gran futuro te espera!";
			link.l1 = "¡Sí señor!";
			link.l1.go = "patria_54";
		break;
		// <-- legendary edtion
		case "patria_53":
			dialog.text = "Ve, mi amigo, y que la suerte acompañe cada uno de tus pasos.";
			link.l1 = "...";
			link.l1.go = "patria_54";
		break;
		
		case "patria_54":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "34");
			pchar.questTemp.Patria = "epizode_7_continue";
			Patria_HunterContinue();
		break;
		
		case "patria_55":
			pchar.questTemp.Patria.Hunter = sti(pchar.questTemp.Patria.Hunter)+1;
			if (sti(pchar.questTemp.Patria.Hunter) > 4) // все собрал
			{
				dialog.text = "Has completado la tarea, capitán. ¡Gracias por tu excelente servicio! Deberías recibir una parte de los ingresos por la venta de los trofeos: doscientos mil pesos.";
				link.l1 = "¡Me alegra oírlo, Monsieur!";
				link.l1.go = "patria_57";
			}
			else
			{
				dialog.text = "Entonces, sólo tienes "+FindRussianQtyString(5-sti(pchar.questTemp.Patria.Hunter))+" Los barcos holandeses han partido para traer a nuestro puerto.";
				link.l1 = "¡Sí, Chevalier!";
				link.l1.go = "patria_56";
			}
		break;
		
		case "patria_56":
			DialogExit();
			AddQuestRecord("Patria", "35");
			AddQuestUserData("Patria", "sQty", 5-sti(pchar.questTemp.Patria.Hunter));
			DeleteAttribute(pchar, "questTemp.Patria.Hunter.GiveShip");
		break;
		
		// belamour legendary edition -->
		case "patria_57":
			AddMoneyToCharacter(pchar, 200000);
			dialog.text = "Y eso no es todo. Pensé un poco el otro día... Charles, realmente hiciste mucho por Francia. La eliminación, francamente, del traidor Levasseur, la defensa de Saint-Pierre del insidioso ataque de España, la exitosa derrota del fuerte de la colonia de San José y la obtención de indemnización de los españoles como castigo por su atrevido truco... ¡Y después de eso, acompañaste personalmente al representante de la corona francesa, quien llegó desde Europa, e incluso salvaste su vida al escapar de una emboscada holandesa en las aguas de Philipsburg!";
			link.l1 = "Monsieur, en verdad, me avergüenza... Solo estoy cumpliendo con mi deber.";
			link.l1.go = "patria_57_1";
		break;
		
		case "patria_57_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "Eres modesto como siempre, mi amigo. Y ahora, durante la ejecución de la siguiente tarea de forzar a Holanda a la paz, nuevamente no me has decepcionado. No temo decir esta palabra: ¡el héroe de la nación! Como gobernador general de las colonias francesas en el archipiélago, tengo conmigo varias copias del más alto galardón de Francia y... Pero, por cierto, te pido que leas este documento.";
			link.l1 = "Por servicio destacado a Francia... en nombre de Su Majestad el Rey de Francia... para galardonar a un oficial naval al servicio de Francia, Capitán Charles de Maure, hijo de Henri de Montpe... Chevalier, ¿estás bromeando?";
			link.l1.go = "patria_57_2";
		break;
		
		case "patria_57_2":
			dialog.text = "Ni un poco, mi amigo. Tengo el honor de recompensarte como mereces presentándote con el más alto galardón de Francia: ¡la Orden de San Luis! ¡Cada ciudadano de nuestro país debe conocer a su héroe! ¡Y Saint-Pierre te debe! Mereces esta Orden, Charles.";
			link.l1 = "Realmente, no sé qué decir... ¡Gracias, Gobernador General! ¡Juro seguir sirviendo a Francia con orgullo y no retroceder ante el enemigo!";
			link.l1.go = "patria_57_3";
		break;
		
		case "patria_57_3":
			GiveItem2Character(pchar, "talisman9");
			Log_Info("¡Has recibido la Orden de San Luis! ¡Eres el héroe de la nación!");
			PlaySound("interface\important_item.wav");
			DoQuestCheckDelay("sea_victory", 0.5);
			dialog.text = "¡Palabras de un verdadero oficial! Estoy verdaderamente orgulloso de ti, Charles. Ahora descansa un poco. Te lo mereces. Mientras tanto, atenderé las negociaciones con Stuyvesant; quizás ya se haya dado cuenta de que es mucho más desventajoso para él estar en enemistad con nosotros que ser amigos. No abandones la ciudad, te necesitaré en dos días.";
			link.l1 = "Muy bien, Monsieur. Esperaré más instrucciones.";
			link.l1.go = "patria_58";
		break;
		// <-- legendary edtion
		case "patria_58":
			DialogExit();
			AddQuestRecord("Patria", "36");
			pchar.questTemp.Patria = "epizode_7_end";
			pchar.quest.Patria_siege_begin.win_condition.l1 = "Timer";
			pchar.quest.Patria_siege_begin.win_condition.l1.date.hour  = 9.00;
			pchar.quest.Patria_siege_begin.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l2 = "location";
			pchar.quest.Patria_siege_begin.win_condition.l2.location = "Charles_town";
			pchar.quest.Patria_siege_begin.function = "Patria_SiegeBegin";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_59":
			dialog.text = "Sí. Parece que Stuyvesant ha comenzado a responder con acción militar en alianza con España. Un escuadrón conjunto holandés-español ha sitiado Saint-Christopher. Los fuertes de vigilancia me informan cada hora de cada uno de sus movimientos.";
			link.l1 = "¿Un asedio?";
			link.l1.go = "patria_60";
		break;
		
		case "patria_60":
			dialog.text = "Obviamente. No fueron a un asalto directo, y eso es realmente bueno. Necesitamos actuar rápidamente, capitán, mientras el enemigo no haya logrado bloquear toda la isla.";
			link.l1 = "¿Qué necesitamos hacer?";
			link.l1.go = "patria_61";
		break;
		
		case "patria_61":
			dialog.text = "En Saint-Jones, en Antigua, se encuentra la escuadra de la Marina Inglesa del Coronel Doily. En este momento, está visitando a Sir Jonathan Fox. Debes pasar por los barcos enemigos y llegar a Antigua. Allí, te encontrarás con el Coronel, le entregarás mi carta y le pedirás ayuda.";
			link.l1 = "¿Crees que el Coronel aceptará ayudarnos?";
			link.l1.go = "patria_62";
		break;
		
		case "patria_62":
			dialog.text = "Eso espero. La carta debería convencerlo de que la recompensa por su ayuda será bastante considerable... Además, necesitamos enviar una carta al capitán del 'Eclatant', que actualmente se encuentra cerca de las costas de Guadalupe, él debe apresurarse a Saint Christopher. El poder de fuego del 'Eclatant' nos ayudará considerablemente en la batalla. Como no puedes estar en dos lugares a la vez, nuestro lugger mensajero se unirá a tu escuadrón; debes pasarlo sin daños a través del círculo de enemigos, y partirá hacia Guadalupe, antes de que el 'Eclatant' se dirija al sur...";
			link.l1 = "Entiendo. Atraviesa el asedio, escolta el lugre mensajero y apresúrate a Saint-Jones con tu carta para el Coronel Doily.";
			link.l1.go = "patria_63";
		break;
		
		case "patria_63":
			dialog.text = "Precisamente. ¿Estás listo para aceptar otro barco en tu escuadrón?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "Me desharé de un barco y volveré a ti.";
				link.l1.go = "patria_63_1";
			}
			else
			{
				link.l1 = "Sí.";
				link.l1.go = "patria_64";
			}
		break;
		
		case "patria_63_1":
			DialogExit();
			pchar.questTemp.Patria = "epizode_8_wait";
		break;
		
		case "patria_64":
			dialog.text = "Excelente. Toma la carta, el lugre está listo y espera tus órdenes.";
			link.l1 = "¡No perdamos tiempo, Chevalier!";
			link.l1.go = "patria_65";
		break;
		
		case "patria_65":
			DialogExit();
			AddQuestRecord("Patria", "38");
			pchar.questTemp.Patria = "epizode_8_continue";
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_3");
			Patria_SiegeCreateSquadron();
		break;
		
		case "patria_66":
			dialog.text = "Sí-sí, mi amigo, sé todo sobre tu modestia. ¡Eres un verdadero oficial! Y recibirás una recompensa, ¡te lo aseguro! Supongo que, después de la dura batalla, necesitarás algo de descanso. Tienes una semana entera. Ven a mi habitación para hablar en siete días: la ciudad preparará una recompensa para su héroe.";
			link.l1 = "Sí, Monsieur. ¿Puedo irme?";
			link.l1.go = "patria_67";
		break;
		
		case "patria_67":
			dialog.text = "Ve y descansa bien. Más tarde necesitaremos tratar asuntos serios. Como puedes ver, la paz con los holandeses es imposible en este momento. Por ahora, el coronel y yo discutiremos algunas cuestiones importantes.";
			link.l1 = "Entonces nos encontraremos en una semana, Chevalier.";
			link.l1.go = "patria_68";
		break;
		
		case "patria_68":
			DialogExit();
			AddQuestRecord("Patria", "45");
			pchar.questTemp.Patria = "epizode_8_end";
			Patria_SiegeEnd();
			ChangeCharacterNationReputation(pchar, FRANCE, 20);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_69":
			pchar.quest.Patria_BastionTimeOver.over = "yes"; //снять таймер
			dialog.text = "Hemos tenido una discusión con el Coronel Doily y ha accedido a ayudarme. Inglaterra nos ayudará en la guerra contra los holandeses. Tú y yo necesitamos contraatacar y restaurar la justicia: la isla de Saint-Martin debe regresar a Francia. ¡Asigno esta tarea al mejor capitán de la marina: tú, Charles de Maure! El enemigo aún no se ha recuperado de la derrota de su escuadrón, atacaremos Philipsburg y lo tomaremos.\nLa batalla no será fácil. Primero, necesitamos destruir el fuerte, luego romper la defensa de la guarnición... (susurrando) También necesitarás hacer una marcha forzada a través de la jungla hasta el depósito de sal del que te hablé, y matar a los enemigos acampados allí...";
			link.l1 = "La tarea es bastante difícil, Chevalier...";
			link.l1.go = "patria_70";
		break;
		
		case "patria_70":
			dialog.text = "Entiendo perfectamente, mi amigo. Tu escuadrón será fortalecido. Los gobernadores de Basse-Terre y Saint-Pierre deberían haber preparado ya un barco cada uno, de porte fragata. Solo necesitarás visitar Guadalupe y Martinica y tomar estos fragatas bajo tu mando. Si, por supuesto, si los quieres tú mismo no insistiré en tu elección de barcos. También te doy un subsidio en forma de 20.000 pesos para comprar provisiones y equipo para tu buque insignia. Aquí, tómalo...";
			link.l1 = "Muy bien, Monsieur.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_71";
			else link.l1.go = "patria_71_1";
		break;
		
		case "patria_71_1":
			dialog.text = "Además, como de costumbre, el barco 'Eclatant' está bajo tu mando. Ha sido reparado y equipado, esperando en la rada, y después de hablar con el capitán, podrás tomarlo en cualquier momento.";
			link.l1 = "¡Excelente!";
			link.l1.go = "patria_71";
			pchar.questTemp.Patria.Ecliaton_Bastion = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_7";
			sld.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "patria_71":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "No podemos perder tiempo, capitán. Según me han informado mis espías, los holandeses comprenden el peligro para Saint-Martin, y tienen la intención de reforzar sus defensas. Pero aún tienes dos meses. ¡Tienes que terminar la tarea a tiempo!";
			link.l1 = "Lo haré... (susurrando) ¿Dónde está el depósito de sal de Saint-Martin? No está marcado en ningún mapa de la isla...";
			link.l1.go = "patria_72";
		break;
		
		case "patria_72":
			dialog.text = "(susurrando) Cuando asaltes la ciudad, interroga al virrey de Philipsburg, Mynheer Martin Thomas, él te lo dirá. Ese holandés es un cobarde y no te resistirá, te lo garantizo.";
			link.l1 = "Veo. Entonces, ¿puedo partir?";
			link.l1.go = "patria_73";
		break;
		
		case "patria_73":
			dialog.text = "Espera un momento, Charles. Aún no has recibido tu recompensa por salvar Saint-Christopher. Toma estos cofres de oro de parte del pueblo de la ciudad, así como nuestro más sincero agradecimiento, que ninguna suma de dinero puede expresar.";
			link.l1 = "¡Gracias, Monsieur!";
			link.l1.go = "patria_74";
		break;
		
		case "patria_74":
			TakeNItems(pchar, "chest", 10);
			Log_Info("¡Has recibido 10 cofres de doblones!");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ahora, puedes irte. ¡Buena suerte, capitán! ¡Todos esperamos tu victoria!";
			link.l1 = "Adiós, Chevalier.";
			link.l1.go = "patria_75";
		break;
		
		case "patria_75":
			DialogExit();
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Bastion")) sTemp = "El buque de guerra 'Eclatant' también estará bajo mi mando.";
			AddQuestRecord("Patria", "48");
			AddQuestUserData("Patria", "sText", sTemp);
			pchar.questTemp.Patria = "epizode_9_continue";
			SetFunctionTimerCondition("Patria_BastionSturmTimeOver", 0, 0, 62, false);
			// вернуть Синт-Маартен в норму
			int n = FindIsland("SentMartin");
			Islands[n].reload.l1.radius = 600.0;
			LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false); // открыть городские ворота
			sld = CharacterFromID("Marigo Fort Commander");
			LAi_SetImmortal(sld, false);
			Character_SetAbordageEnable(sld, true);
			// атрибут квестовой высадки десанта
			pchar.TempPerks.QuestTroopers = true;
		break;
		
		case "patria_76":
			dialog.text = "¿Quién hubiera pensado hace solo un año que serías ascendido al rango de vicealmirante, mi amigo? ¡Solo puedo imaginar cuán orgulloso estará tu padre cuando esta noticia llegue a Francia!";
			link.l1 = "Mi querido padre estará encantadísimo con eso.";
			link.l1.go = "patria_77";
		break;
		
		case "patria_77":
			dialog.text = "¡Has ganado tu posición en la flota! ¡Saint Martin ha sido devuelto a Francia, Stuyvesant ha aprendido una dura lección. Esta fue una gran victoria! Pero no debemos detenernos, no podemos dejar que los holandeses descansen ni un minuto. ¡Serán responsables de su traición! El Coronel Doily está en Port-Royal ahora mismo, preparando su escuadrón naval: vamos a quebrar la columna vertebral de nuestro enemigo atacando Curazao. Pero eso será más tarde, por ahora tenemos que matar dos pájaros de un tiro, Charles. \nLa Compañía no obtuvo toda su riqueza incalculable solo con el comercio. La principal fuente de ingresos de los holandeses en la región es el trabajo esclavo en sus plantaciones. Si no lo sabes, Charles: Holanda es la nación más grande en posesión y comercio de esclavos. Los indios orientales que transportan el 'marfil negro' llegan regularmente a Curazao desde África Occidental. Y resulta que sé algo al respecto, desafortunadamente para Stuyvesant. \nEn este momento, dos indios orientales holandeses están navegando hacia el Caribe desde Guinea. Sus bodegas están llenas de prisioneros negros. En diez días o alrededor de ese tiempo, la caravana estará navegando alrededor de la isla de Trinidad en dirección a Curazao. Tu tarea es encontrar la caravana y capturar a estos dos indios orientales y su cargamento. Debes destruir los barcos de escolta y llevar a los esclavos a nuestro aliado, el Coronel Doily, en Jamaica. Esto es muy importante Charles, de esta manera ganaremos su confianza... Espero que entiendas. \nLamento no dejarte tiempo para descansar, pero esta tarea es importante y delicada, y solo puedo confiarla a ti.";
			link.l1 = "El servicio no es miel, Chevalier. Lo sé mejor que nadie. Prepararé mi barco y partiré tan pronto como pueda.";
			link.l1.go = "patria_78";
		break;
		
		case "patria_78":
			dialog.text = "Le deseo buenos vientos y un viaje seguro, vicealmirante. Y cuando regrese a Saint-Christopher, nuestro amigo común, Monsieur Noel Forget, habrá terminado su inspección de Philipsburg, y me aseguraré de que parte de los trofeos que tomen de los holandeses vayan a usted personalmente.";
			link.l1 = "Me hará muy agradecido, Chevalier. ¿Puedo irme?";
			link.l1.go = "patria_79";
		break;
		
		case "patria_79":
			dialog.text = "Ve. ¡Buena suerte, mi amigo!";
			link.l1 = "...";
			link.l1.go = "patria_80";
		break;
		
		case "patria_80":
			DialogExit();
			Items[sti(pchar.EquipedPatentId)].TitulCur = 5; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.questTemp.Patria = "epizode_10_start";
			AddQuestRecord("Patria", "52");
			Patria_SlaveShipsStart();
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_81":
			dialog.text = "¡Excelente! No conoces la palabra 'imposible', Charles. Solía pensar que tu hermano era el mejor oficial de la marina en el Caribe, pero tiene mucho que aprender de ti, si me permites esta cruda comparación. Creo que ya sabes quién irá a nuestro querido coronel para participar en el asalto a Willemstad.";
			link.l1 = "¡Absolutamente no, Monsieur! ¡Cómo podría saberlo!";
			link.l1.go = "patria_82";
		break;
		
		case "patria_82":
			dialog.text = "¡Ah, tu famoso sentido del humor, mi querido amigo! ¡Ja, ja! Por supuesto, serás tú, vicealmirante. El más digno de todos. ¿Estás listo?";
			link.l1 = "Por supuesto, Chevalier. Todo lo que necesito son algunas reparaciones, algo de equipo, y estoy listo para partir.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_83";
			else link.l1.go = "patria_83_1";
		break;
		
		case "patria_83_1":
			dialog.text = "No olvides tomar el 'Eclatant' bajo tu mando. Ha sido reparado y equipado, esperándote en los muelles. El marqués Hubert Dassier ya está impaciente y esperando para entrar en otra batalla contigo.";
			link.l1 = "Estupendo. Un poderoso barco con culebrinas de largo alcance es exactamente lo que necesito para bombardear el fuerte.";
			link.l1.go = "patria_83";
			pchar.questTemp.Patria.Ecliaton_Curacao = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_11";
			sld.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "patria_83":
			dialog.text = "Espera un momento, Charles. Nuestro amigo, el Barón Forget, ha traído noticias para ti desde Saint Martin.";
			link.l1 = "...";
			link.l1.go = "patria_84";
		break;
		
		case "patria_84":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_25";
			sld.greeting = "noel_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
		break;
		
		case "patria_85":
			dialog.text = "Tengo noticias para usted desde París. Su nombramiento para el cargo de vicealmirante ha sido firmado por el Rey. Usted recibirá los papeles pertinentes. ¡Así que, le felicito!";
			link.l1 = "¡Gracias, Monsieur! ¡Encantado de servir a Francia y al Rey!";
			link.l1.go = "patria_coat";
		break;
		
		case "patria_coat":
			dialog.text = "Y yo, como siempre, me complace mucho escuchar estas palabras de ti. Charles, ¿quizás te gustaría compartir un poco de vino conmigo? ¡Traído directamente de París, no encontrarás este tipo aquí ni en un día de viaje!";
			link.l1 = "Gracias, caballero, pero creo que pasaré. Debo regresar al barco más tarde, y no sería adecuado que el vicealmirante de Francia estuviera de pie borracho en el alcázar.";
			link.l1.go = "patria_coat_01";
			link.l2 = "Bueno, ¿por qué no? ¡No todos los días tengo la oportunidad de compartir una copa con el propio gobernador general!";
			link.l2.go = "patria_coat_02";
		break;
		
		case "patria_coat_01":
			dialog.text = "Bueno, podrías tomarte un descanso, no es necesario regresar al barco de inmediato. Pero es tu deseo, y lo respeto. Muy bien, vayamos directo al grano.";
			link.l1 = "Estoy escuchando atentamente.";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_02":
			dialog.text = "¡Y no todos los gobernadores generales tienen la fortuna de que su vicealmirante sea no solo el mejor oficial naval, sino también un amigo, con quien pueda sentarse a la misma mesa y beber vino traído de una patria lejana!";
			link.l1 = "¡Por Francia!";
			link.l1.go = "patria_coat_03";
			link.l2 = "¡A su salud, caballero!";
			link.l2.go = "patria_coat_04";
		break;
		
		case "patria_coat_03":
			dialog.text = "¡Y por el rey!";
			link.l1 = "...";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_04":
			dialog.text = "¡Y a los tuyos, Charles!";
			link.l1 = "...";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_05":
			LAi_Fade("", "");
			if(LAi_GetCharacterHP(pchar) == LAi_GetCharacterMaxHP(pchar))
			pchar.chr_ai.hp = stf(pchar.chr_ai.hp) - 1.0;
			GiveItem2Character(pchar, "potionwine");
			DoCharacterUsedItem(pchar, "potionwine");
			npchar.dialog.currentnode = "patria_coat_06";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorSetHuberMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 1.2);
		break;
		
		case "patria_coat_06":
			dialog.text = "¡Hm, vino exquisito! ¿No lo crees?";
			link.l1 = "Sí, tenías razón. Me recuerda al vino que hacen en casa, en Gascuña...";
			link.l1.go = "patria_coat_07";
		break;
		
		case "patria_coat_07":
			dialog.text = "Estás un poco equivocado, mi amigo es un Burdeos. ¡Sin embargo, estoy seguro de que el vino de Gascuña es igual de bueno!";
			link.l1 = "Creo que estoy empezando a olvidar su sabor... ¿Cuánto tiempo ha pasado desde que dejé Francia? ¿Un año? ¿Dos?";
			link.l1.go = "patria_coat_08";
		break;
		
		case "patria_coat_08":
			dialog.text = "Ah, Charles, parece que nos conocimos hace poco... y no en las circunstancias más agradables. Perdóname por mencionar esto, pero si alguien me hubiera dicho entonces que en la celda de prisión frente a mí estaba mi futuro mano derecha en las colonias francesas, probablemente me habría reído a carcajadas.";
			link.l1 = "Inscrutables son los caminos del Señor.";
			link.l1.go = "patria_coat_09";
		break;
		
		case "patria_coat_09":
			dialog.text = "Disculpe, ¿qué acaba de decir?";
			link.l1 = "Es latín, caballero. Los caminos del Señor son inescrutables. Nadie sabe lo que la vida tiene reservado.";
			link.l1.go = "patria_coat_10";
		break;
		
		case "patria_coat_10":
			dialog.text = "Nunca dejas de asombrarme, Charles. Mírate, no tenía idea de que también hablas latín. Pero por otro lado, hasta cierto punto, forjamos nuestro propio destino, ¿no es así?";
			link.l1 = "Creo que ambas son ciertas. Solo el Señor sabe lo que nos depara el futuro. Pero él recompensa a los persistentes.";
			link.l1.go = "patria_coat_11";
		break;
		
		case "patria_coat_11":
			dialog.text = "No podría estar más de acuerdo. Recuerdo, por ejemplo, haberte entregado la comisión de oficial naval y darte ese uniforme. ¡Y ahora, frente a mí, se encuentra un vicealmirante, nada menos!";
			link.l1 = "El tiempo vuela, chevalier.";
			link.l1.go = "patria_coat_12";
		break;
		
		case "patria_coat_12":
			dialog.text = "En efecto... E incluso en su uniforme, veo los cortes dejados por los sables; algunos cortes han sido cosidos, y otros son claramente recientes. Esto necesita ser corregido.";
			link.l1 = "¿Qué tiene en mente, señor Gobernador General?";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_13":
			dialog.text = "Además de tu nuevo puesto de vicealmirante de la flota francesa en el archipiélago del Caribe, tengo un regalo más para ti.";
			link.l1 = "Me haces sonrojar, caballero. ¿Qué regalo?";
			link.l1.go = "patria_coat_14";
		break;
		
		case "patria_coat_14":
			dialog.text = "He hablado con mi sastre personal, ¡el mejor de las colonias francesas!, para que confeccione un uniforme acorde a tu rango. No te preocupes por el pago, yo me he encargado de todo.";
			link.l1 = "¡Estoy realmente agradecido! Me aseguraré de visitar a vuestro sastre. ¿Dónde puedo encontrarlo?";
			link.l1.go = "patria_coat_15";
		break;
		
		case "patria_coat_15":
			dialog.text = "Debería estar en la oficina del puerto ahora mismo: un nuevo barco correo acaba de llegar del continente con pequeños paquetes. Nuestro sastre siempre pide algunos materiales que son difíciles de encontrar aquí.";
			link.l1 = "Entonces iré a la oficina del puerto. ¡Gracias de nuevo, monsieur!";
			link.l1.go = "patria_86";
		break;
		
		case "patria_86":
			dialog.text = "Y ahora, estoy seguro, necesitarás descansar bien. Te doy un mes, y asegúrate de aprovecharlo bien. Sin trabajo, sin preocupaciones. Deja todo el trabajo a tus oficiales y descansa bien. Puedes usar las habitaciones en mi residencia. Los sirvientes harán que tus vacaciones sean lo más cómodas posible. Nos reuniremos de nuevo en un mes y tendré un asunto delicado que discutir contigo.";
			link.l1 = "Muy bien, ¡Chevalier! ¡Adiós!";
			link.l1.go = "patria_87";
		break;
		
		case "patria_87":
			npchar.dialog.currentnode = "First time";
			LAi_Fade("","");
			LAi_SetHuberType(npchar);
			DialogExit();
			AddQuestRecord("Patria", "65"); // далее коллизия Пуанси-Инспектор-Шарль
			pchar.questTemp.Patria = "epizode_12_start";
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			SetFunctionLocationCondition("Patria_Tailor", "Charles_PortOffice", false)
			Patria_CondotierStart();
			ChangeCharacterComplexReputation(pchar, "nobility", 15); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 15);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
		break;
		
		case "patria_88":
			dialog.text = "Sí, Charles. Pensé que podría manejar esto yo mismo, pero... ay, debo pedirte que uses tus talentos una vez más. Pero primero, necesito darte algo: trescientos mil pesos y cinco cofres de doblones. Esta es una gran parte de la contribución que Stuyvesant me pagó según el acuerdo. Supongo que te has ganado todo esto, ya que has hecho la mayor parte del trabajo. Acéptalo. ¿Estás satisfecho, mi amigo?";
			link.l1 = "El dinero nunca ha herido a nadie, Monsieur, he aprendido bien esa lección.";
			link.l1.go = "patria_89";
		break;
		
		case "patria_89":
			AddMoneyToCharacter(pchar, 300000); 
			TakeNItems(pchar, "chest", 5);
			dialog.text = "Ah, vicealmirante, espero que no estés ofendido por lo que sucedió en el pasado... ¿Sabías que ahora eres un héroe de tu nación? ¿Cómo te sientes en esta nueva posición? Recuerda: muchos oficiales dignos pasaron décadas ascendiendo en la escalera de rangos, pero sin una mano experimentada... se quedan en la posición de comandante. ¡Pero tú, mi amigo, tienes una habilidad única para siempre lograr lo imposible! Y tienes un amigo en las altas esferas, que también es tu guardián, así que si tienes algún problema en el futuro, estaré allí para ayudarte.";
			link.l1 = "Gracias por estas amables palabras, su Excelencia. Tengo la sensación de que he logrado casi todo en esta región. Con su ayuda, por supuesto. Supongo que ahora puedo ocuparme de mis propios asuntos en paz. Debo pensar en mi familia.";
			link.l1.go = "patria_90";
		break;
		
		case "patria_90":
			dialog.text = "¿Quieres casarte, Charles? ¡Ah-ja-ja! Señala a cualquier mujer hermosa en París, ¡y será tuya de inmediato! Pero, ay, eso tendrá que esperar. Te necesito aquí, amigo mío, al menos por ahora.";
			link.l1 = "Parece que Francia es más fuerte que nunca en el Archipiélago. Una alianza con los ingleses, una tregua con la Compañía. No quedan problemáticos... 'Levasseurs'. ¿Verdad?";
			link.l1.go = "patria_91";
		break;
		
		case "patria_91":
			dialog.text = "Las naciones, al igual que las personas, siempre desean más, sin importar cuánto tengan... Y de hecho, tenemos un nuevo 'Levasseur', vicealmirante...";
			link.l1 = "¿De verdad? ¿Y quién es?";
			link.l1.go = "patria_92";
		break;
		
		case "patria_92":
			dialog.text = "Es nuestro viejo conocido mutuo, el Barón Noel Forget. ¿Recuerdas por qué vino aquí?";
			link.l1 = "Ajá... Mencionaste algo sobre la Compañía de Comercio de las Indias Occidentales. ¿París decidió crear la misma organización que los holandeses?";
			link.l1.go = "patria_93";
		break;
		
		case "patria_93":
			dialog.text = "Precisamente. Análogo a la Compañía Holandesa. Pero crear una desde cero es muy difícil. Verás, Stuyvesant tenía décadas de comercio con diferentes continentes en su experiencia, una red desarrollada de agentes y una poderosa flota de barcos comerciales. Francia no tiene eso, y, si no lo sabías, Charles, el Rey está experimentando una grave falta de fondos ahora mismo. Desean arreglar la situación financiera de la metrópolis dirigiendo el comercio aquí, pero no entienden a qué nos enfrentaremos.\nLa rivalidad tanto de los ingleses como de los holandeses, las ambiciones territoriales de los españoles, la piratería floreciendo como nunca antes. Cada fluyt comercial necesita ser escoltado por un barco de la armada, o correrá el riesgo de nunca llegar a su destino. Y no tenemos una poderosa flota como los Indo-Holandeses, o los poderosos Galeones como los de los españoles.";
			link.l1 = "¿Pero le explicaste todo esto al barón? ¿También sobre los piratas?";
			link.l1.go = "patria_94";
		break;
		
		case "patria_94":
			dialog.text = "Por supuesto que lo hice. Y sobre el destierro de los piratas de Tortuga después de tu misión de eliminar a Levasseur, lo cual los piratas no han olvidado y siempre nos guardarán rencor. He organizado reuniones con varias personas que confirmaron mis preocupaciones, pero, ay, eso no tuvo efecto en el barón. Fue enviado aquí por los ministros, y les debe a ellos... Así es como es.";
			link.l1 = "Eh...";
			link.l1.go = "patria_95";
		break;
		
		case "patria_95":
			dialog.text = "Y no ocultemos el hecho de que una compañía comercial en el Archipiélago, con control directo desde París... tú y yo, vicealmirante... no la necesitamos aquí.";
			link.l1 = "Entiendo.";
			link.l1.go = "patria_96";
		break;
		
		case "patria_96":
			dialog.text = "Ves, amigo mío, estoy siendo extremadamente honesto contigo... Así que, esperaba con todo mi corazón que Monsieur Forget cambiara de opinión sobre la creación de esta compañía comercial, pero... eso no sucedió. He desperdiciado toda mi influencia en el barón, y ahora necesitas entrar en el juego.";
			link.l1 = "Hmm... ¿Igual que con Levasseur?";
			link.l1.go = "patria_97";
		break;
		
		case "patria_97":
			dialog.text = "¡Oh, Dios, no, ¿por quién me tomas, Charles?! ¡El barón es una figura influyente, amigo del Ministro de Finanzas! Y además, eliminarlo físicamente no logrará nada: simplemente enviarán a un nuevo político desde París. Necesitamos destruir la idea de organizar tal empresa desde el principio, ¿entiendes, Charles? Para que el barón regrese a Francia e informe que sería financieramente arriesgado, absurdo...";
			link.l1 = "¿Tiene una idea, Monsieur?";
			link.l1.go = "patria_98";
		break;
		
		case "patria_98":
			dialog.text = "Lamentablemente, no, Charles. He intentado de todo. Lo he asustado con la falta de barcos y dinero, los holandeses, piratas... Sin efecto.";
			link.l1 = "Me parece que necesitamos algo más serio que meras palabras. Hm... ¿Piratas, dices?";
			link.l1.go = "patria_99";
		break;
		
		case "patria_99":
			dialog.text = "¿Veo que tienes una idea, mi amigo? No tenía dudas. Tienes una mente brillante. Convence a este barón, y me aseguraré de que tu padre tenga suficiente dinero para llenar toda tu casa con riquezas dignas del Louvre. Te lo prometo, Charles.";
			link.l1 = "Muy bien, Chevalier. La tarea está clara.";
			link.l1.go = "patria_100";
		break;
		
		case "patria_100":
			dialog.text = "Te juro, Charles, no te arrepentirás si tienes éxito. Puedes estar seguro de eso. ¿Acaso te he traicionado alguna vez, mi amigo?";
			link.l1 = "Absolutamente no, Monsieur. ¿Dónde puedo encontrar al Barón?";
			link.l1.go = "patria_101";
		break;
		
		case "patria_101":
			dialog.text = "En este momento, está en Puerto Príncipe. Encuentra los interminables campos y valles de La Española muy encantadores, dijo...";
			link.l1 = "Estupendo. Ahora, permítame disculparme.";
			link.l1.go = "patria_102";
		break;
		
		case "patria_102":
			DialogExit();
			AddQuestRecord("Patria", "67");
			pchar.questTemp.Patria = "epizode_12_pirates";
			Patria_CondotierSail();
		break;
		
		case "patria_103":
			dialog.text = "Precisamente eso. El barón me contó todo. Después de todo lo que ha pasado... Sin embargo, ¡usted puede explicar las cosas claramente, como nadie más, vicealmirante! ¡Debería aprender eso de usted!";
			link.l1 = "He aprendido mucho de usted, Chevalier.";
			link.l1.go = "patria_104";
		break;
		
		case "patria_104":
			dialog.text = "Mi amigo, te debo una. Te aseguro que tu querido padre tendrá todo lo que necesite o pueda necesitar en su vida, y tu casa familiar será la mejor de la provincia... y una de las mejores de Francia. Además, te pagaré 100 000 pesos, espero que cubra tu deuda con los piratas...";
			link.l1 = "¡Eso es encantador de escuchar, Monsieur!";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_105add":
			AddMoneyToCharacter(pchar, 100000); 
			dialog.text = "También he preparado un regalo especial para ti. Estoy seguro de que comprenderás el valor de este objeto y la sinceridad de mi gratitud por tu leal servicio. Así que, Vicealmirante Charles de Maure, ¡te entrego mi espada ceremonial personal de la Orden de Malta! ¡Esta preciada arma combinará con tu uniforme, creo yo! Si decides regresar a París, el Barón Noel Forget ha prometido presentarte al Rey. Deberías ir con él en pleno desfile: vistiendo tu uniforme y portando esta excelente hoja. ¡Te esperan aún más gloriosas oportunidades de carrera en la marina francesa!";
			link.l1 = "¡Esta espada es inigualable en su belleza! Gracias, Monsieur, realmente no merezco este honor...";
			link.l1.go = "patria_105";
		break;
		
		case "patria_105":
			ref itm = ItemsFromID("blade_36");
			itm.picIndex = 16;
			itm.picTexture = "ITEMS_17";
			itm.price = 10000;
			itm.Weight = 3.0;
			itm.lenght = 1.05;
			itm.curve = 1.0;
			itm.Balance = 1.9;
			GiveItem2Character(pchar, "blade_36");
			Log_Info("¡Has recibido la Espada Maltesa!");
			PlaySound("interface\important_item.wav");
			dialog.text = "¡Así es! Y mientras estés aquí, te esperan grandes cambios. Buenos cambios. Vicealmirante Charles de Maure, ¡te nombro gobernador de Saint-Martin!";
			link.l1 = "¡Ja! ¿Te oí correctamente?";
			link.l1.go = "patria_106";
		break;
		
		case "patria_106":
			ChangeCharacterComplexReputation(pchar, "nobility", 12); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 12);
			ChangeCharacterComplexReputation(pchar, "fame", 12);
			dialog.text = "Sí, mi amigo. Ahora eres el gobernador de Saint Martin, que has protegido con tanta diligencia.";
			link.l1 = "Chevalier, permíteme rechazar este honor. ¡No deseo estar atado a esta pobre isla! Y todos estos asuntos domésticos... ¡Eso no es para lo que fui destinado!";
			link.l1.go = "patria_107";
		break;
		
		case "patria_107":
			dialog.text = "No acepto la negativa. Amigo mío, no temas: vivirás como antes. Todas las cosas aburridas serán manejadas por el actual gobernador en funciones. Tú serás el gobernador de facto. Charles, ¿no entiendes por qué fuiste específicamente designado para gobernar Saint Martin? Ahora es el momento adecuado para ello, cuando nadie hará preguntas. Necesito a uno de MIS hombres como gobernador allí, ¿entiendes lo que quiero decir?";
			link.l1 = "¿La mina de sal?";
			link.l1.go = "patria_108";
		break;
		
		case "patria_108":
			dialog.text = "¡Por supuesto! Y la segunda buena noticia: a partir de ahora, el día 15 de cada mes, recibirás parte de las ganancias de la mina, así como del comercio de Doily. Tu ingreso pasivo será de 100.000 pesos al mes.";
			link.l1 = "¡Ja! ¡Me alegra oír eso! Gracias, Chevalier. Bueno, si no estaré atado a quedarme allí, acepto el cargo de gobernador. ¿Y qué si decido navegar a Francia?";
			link.l1.go = "patria_109";
		break;
		
		case "patria_109":
			dialog.text = "Cuando decidas, te irás, y yo, aunque muy decepcionado, encontraré un reemplazo para ti. Pero eso no es todo. Tengo una carta de tu padre aquí. Échale un vistazo.";
			link.l1 = "¿De mi padre? ¡Estoy emocionado!.. Muy bien, Monsieur, trato hecho. ¿Puedo irme ahora? Deseo leer la carta... ¿No hay nuevas tareas para mí?";
			link.l1.go = "patria_110";
		break;
		
		case "patria_110":
			dialog.text = "Ahora no, Gobernador, pero si encuentro algún trabajo, sé cómo encontrarle. ¡Buena suerte, Charles!";
			link.l1 = "¡Y a usted, Chevalier!";
			if (pchar.questTemp.Patria == "epizode_12_baronwin") link.l1.go = "patria_119";
			else link.l1.go = "patria_111";
		break;
		
		case "patria_111":
			DialogExit();
			AddQuestRecord("Patria", "77");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_112":
			dialog.text = "¡Maldita sea, qué desastre! Ahora tenemos más problemas que resolver. ¿Eres tú el responsable de esto, Charles? Dime la verdad. ¿Fue un accidente?";
			link.l1 = "Bueno, algo salió mal...";
			link.l1.go = "patria_113";
		break;
		
		case "patria_x112":
			dialog.text = "¡Por todos los demonios, qué desastre! Ahora tenemos más problemas que resolver. ¡El Barón escogió un lugar muy malo para morir! ¿Estás seguro de que no le ayudaste a partir de este mundo?";
			link.l1 = "¿Qué estás diciendo, Chevalier?! ¡Por supuesto que no!";
			link.l1.go = "patria_x113";
		break;
		
		case "patria_y112":
			dialog.text = "¡Maldita sea, qué desastre! Ahora tenemos más problemas que resolver. ¿Estás seguro de que no le ayudaste a abandonar este mundo?";
			link.l1 = "¿Qué está diciendo, Chevalier?! ¡Por supuesto que no!";
			link.l1.go = "patria_y113";
		break;
		
		case "patria_x113":
			dialog.text = "Está bien. Bueno, amigo mío, tal vez no todo esté arruinado. ¿Una fiebre es una fiebre, verdad? Y hasta que llegue un nuevo inspector del ministerio, limpiaremos el desorden aquí y esperaremos a nuestros invitados bien armados... Y ahora, Charles, necesitamos cerrar todos nuestros contactos. Espero que entiendas por qué.";
			link.l1 = "Por supuesto.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_y113":
			dialog.text = "Está bien. Bueno, entonces, mi amigo, tal vez no todo esté arruinado. Las batallas en el Caribe son de esperar, ¿no? Y hasta que llegue un nuevo inspector del ministerio, limpiaremos el desorden aquí y estaremos esperando a nuestros invitados bien armados... Y ahora, Charles, necesitamos cerrar todos nuestros contactos. Espero que entiendas por qué.";
			link.l1 = "Por supuesto.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_113":
			dialog.text = "Está bien. Bueno, entonces, mi amigo, tal vez no todo esté arruinado. Los piratas son piratas, ¿verdad? Y hasta que llegue un nuevo inspector del ministerio, vamos a limpiar este desorden aquí y estaremos esperando a nuestros invitados bien armados... Y ahora, Charles, necesitamos cerrar todos nuestros contactos. Espero que entiendas por qué.";
			link.l1 = "Por supuesto.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_114":
			dialog.text = "En cualquier caso, amigo mío, has hecho todo lo posible. Y eso es mejor que nada. Me alegra que el destino nos haya unido. Puedes conservar tu puesto, y estoy seguro de que te espera una gran carrera en Francia. Y, creo que es hora de que regreses a París. Aquí, una carta de tu padre. Tómala.";
			link.l1 = "¿Mi padre? ¡Eso es más que bienvenido!.. De acuerdo, Monsieur, entiendo. Sin contactos, total secreto, y tan pronto como pueda ir a París. ¿Puedo irme ahora? Deseo leer la carta...";
			link.l1.go = "patria_115";
		break;
		
		case "patria_115":
			dialog.text = "Ve, Charles. ¡Buena suerte!";
			link.l1 = "¡Y a usted, Chevalier!";
			link.l1.go = "patria_116";
		break;
		
		case "patria_116":
			DialogExit();
			AddQuestRecord("Patria", "78");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_117":
			dialog.text = "Precisamente. ¡Puedes explicar las cosas con claridad como nadie más, vicealmirante! ¡Debo aprender eso de usted!";
			link.l1 = "He aprendido mucho de usted, Chevalier.";
			link.l1.go = "patria_118";
		break;
		
		case "patria_118":
			dialog.text = "Mi amigo, te debo una. Te aseguro que tu querido padre tendrá todo lo que necesita o alguna vez necesitará en su vida, y tu casa familiar será la mejor de la provincia... y una de las mejores de Francia. Además, te pagaré 100.000 pesos, espero que cubra tus gastos de viaje, y te permita obtener un merecido descanso.";
			link.l1 = "¡Eso es encantador de escuchar, Monsieur!";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_119":
			DialogExit();
			AddQuestRecord("Patria", "87");
			pchar.questTemp.Patria = "europe";
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			SetFunctionTimerCondition("Patria_EuropeTime", 0, 0, 175+rand(10), false); // таймер
		break;
		
		case "patria_prison":
			dialog.text = "¡Cómo pudiste, Charles! ¡¿Cómo pudiste hacerme esto?!";
			link.l1 = "Ahem...";
			link.l1.go = "patria_prison_1";
		break;
		
		case "patria_prison_1":
			dialog.text = "¡Sé que fuiste tú! ¡Tú hiciste eso! ¡No lo niegues! Sin tu ayuda, el Barón Forget nunca habría conseguido ni los informes del administrador de la mina, ni la ubicación de la mina, ni siquiera los documentos de Peter Stuyvesant. No se escuchó tu nombre allí, pero déjame decirte, sé con certeza: fuiste tú. ¿Por qué, Charles?.. Solo respóndeme... ¿Por qué? ¿Michel? ¿Un millón de pesos? ¿Levasseur? ¿O quizás la posición de Gobernador General?";
			// belamour legendary edition -->
			link.l1 = "¿Recuerdas nuestro primer encuentro, Chevalier? ¿Cómo me pusiste en mi lugar? ¿Cómo me extorsionaste un millón de pesos? Solo deseaba que un día pudiéramos cambiar de lugar. No tengo nada más que decirte.";
			link.l1.go = "patria_prison_2";
			link.l2 = "Por Levasseur. Una deuda de un millón, aún puedo entender. Trabajé, maté, gané, robé, pero te compensé por todo el daño. Y eso no fue suficiente para ti. ¡Vos, Chevalier, me habéis enviado en una misión suicida contra la corona para que podáis fortalecer aún más vuestro poder personal! ¡Vuestra traición exigía una respuesta! ¡Y la obtuvisteis!";
			link.l2.go = "patria_prison_2";
			link.l3 = "Ambición, Chevalier. En este extraño nuevo mundo, ya había logrado casi todo lo que podía. El puesto de gobernador general me parecía un objetivo digno de mención. He aprendido mucho de ti. ¡Adiós!";
			link.l3.go = "patria_prison_2";
			link.l4 = "No lo sé yo mismo, para ser honesto. ¿Quizás porque estoy impresionado por el barón y su fiel servicio a nuestro país? En cualquier caso, ahora tendrás suficiente tiempo para pensar en este asunto por mí. ¡Adiós!";
			link.l4.go = "patria_prison_2";
			// <-- legendary edition
		break;
		
		case "patria_prison_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			SetFunctionTimerCondition("Patria_EuropePuancieClear", 0, 0, 5, false); // таймер
			pchar.quest.Patria_Europe_final.win_condition.l1 = "location";
			pchar.quest.Patria_Europe_final.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Europe_final.function = "Patria_EuropeFinal";
		break;
		
		case "patria_patentfail":
			DialogExit();
			pchar.questTemp.Patria = "fail";
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			// убрать Эклятон, если есть
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton"))
			{
				sld = characterFromId("Ecliaton_Cap");
				RemoveCharacterCompanion(pchar, sld);
				sld.lifeday = 0;
				DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
			}
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ1":
			SetTimerCondition("PZ_NormanBackToStreets", 0, 0, 1, false);	//Вовзращаем Акулу или Тиракса в Шарптаун
			// ставим сразу прерывание, чтобы потом по тысячу раз не копировать
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang") || CheckAttribute(pchar, "questTemp.PZ.LongwayTorero") || CheckAttribute(pchar, "questTemp.PZ.LongwayElCasador"))
				{
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1 = "location";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1.location = "Charles_town";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition = "PZ_AfterPoincyLongwayDialog";
				}
			}
			
			if (!CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva")) 
			{
				dialog.text = "Me alegra verte, Charles. He oído hablar de tus hazañas. ¡Brillante trabajo!";
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Ese no es todo, Su Excelencia.";
					link.l1.go = "PZ2";
				}
				else
				{
					link.l1 = "¿Puedo obtener una orden escrita de usted para que mi hermano sea liberado de la custodia ahora?";
					link.l1.go = "serve";
				}
			}
			else 
			{
				dialog.text = "Saludos, Charles. Pase, ya me han informado.";
				link.l1 = "¿Informado? Puede que haya algún error, Su Excelencia. Vine a informar sobre la exitosa finalización de su misión, pero veo que no está de buen ánimo.";
				link.l1.go = "PZ_PoincyAngry1";
			}
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube");
		break;
					
		case "PZ2":
			dialog.text = "¿Es así? ¿Qué quieres decir, Capitán?";
			link.l1 = "He logrado capturar a Levasseur con vida y traerlo ante usted. Tan pronto como terminemos, daré la orden de traerlo.";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "¡Nunca pensé que algo así fuera siquiera posible! ¡Realmente, un trabajo brillante, Charles! Dudo que incluso tu ilustre hermano pudiera haberlo hecho mejor. Tu padre estaría orgulloso de ti, mi amigo.";
			link.l1 = "Gracias por sus amables palabras, Monsieur Philippe.";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "PZ5":
			dialog.text = "Muy bien, Charles. Estoy complacido contigo.";
			link.l1 = "¿Puedo obtener una orden escrita de usted para que mi hermano sea liberado de la custodia ahora?";
			link.l1.go = "serve";
			LAi_SetHuberType(npchar);
		break;
		
		case "PZ_PoincyAngry1":
			dialog.text = "Quizás debería haber considerado que no eres tu hermano: no eres un hombre militar, ni un agente secreto, y aún no tienes experiencia en operaciones delicadas. No deberías haber luchado abiertamente contra soldados en las calles de Tortuga. Habrá investigaciones, y también sobre mí. Procedentes de gente seria, como entiendes.";
			link.l1 = "Le ruego me disculpe, Chevalier. Como usted comprende, Levasseur no habría renunciado sin pelear.";
			link.l1.go = "PZ_PoincyAngry2";
		break;
		
		case "PZ_PoincyAngry2":
			dialog.text = "Es cierto, pero... no importa. No está mal para una primera operación. Informaré que atacó al Auditor Real y a su escolta durante una inspección oficial.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
			{
				link.l1 = "Su Excelencia, si ayuda, puedo traerle a Levasseur. Mis hombres y yo tuvimos la suerte de capturarlo en un lugar apartado después de que sus secuaces intentaran arrestarnos en las calles.";
				link.l1.go = "PZ_PoincyAngry3";
			}
			else
			{
				link.l1 = "¿Puedo obtener una orden escrita de usted de que mi hermano será liberado de la custodia ahora?";
				link.l1.go = "serve";
			}
		break;
				
		case "PZ_PoincyAngry3":
			dialog.text = "¿Qué dijiste, Charles? Dilo de nuevo.";
			link.l1 = "François Levasseur está en mi bodega ahora mismo, listo para ser entregado a usted, Monsieur Philippe.";
			link.l1.go = "PZ_PoincyAngry4";
		break;
		
		case "PZ_PoincyAngry4":
			dialog.text = "Olvida todo lo que dije antes. Definitivamente, exageré. Trabajo brillante. No estoy seguro de que ni siquiera tu ilustre hermano podría haberlo logrado.";
			link.l1 = "Gracias, Chevalier.";
			link.l1.go = "PZ_PoincyAngry5";
		break;
		
		case "PZ_PoincyAngry5":
			dialog.text = "Tienes un gran potencial, mi amigo. Desearía que tus talentos se usaran más a menudo para el bien del país. Pero, por favor, intenta ser más... discreto de ahora en adelante. Nuestro trabajo generalmente requiere un enfoque delicado. Ah, sí, y una cosa más.";
			link.l1 = "¿Sí, su Señoría?";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
