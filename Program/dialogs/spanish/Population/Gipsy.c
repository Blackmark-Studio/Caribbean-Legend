// Jason общий диалог цыганок
//  ugeen <-- добавил продажу мышьяка из под полы
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int poison_price;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c ";
						 if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "Ah hola, querida. ¿Qué quieres?";
		link.l1 = "Nada, supongo.";
		link.l1.go = "exit";
		link.l2 = RandPhraseSimple("Tengo una pregunta para ti.", "Necesito información.");
		link.l2.go = "quests"; //(перессылка в файл города)

		if (npchar.quest.meeting == "0")
		{
			dialog.text = LinkRandPhrase("Querido, ¿serías tan amable de compartir un poco de oro? Te diré tu futuro.", "¡Eh, marinero, no te apresures así! ¿Quieres saber el futuro?", "Dame un poco de tabaco y unas monedas de plata, valiente joven. Y echaré un vistazo a tu futuro. (guiño) ¿Quieres escuchar algo de la magia secreta gitana?");
			link.l1 = "Lo siento, pero tengo que irme.";
			link.l1.go = "exit";
			// --> мангароса
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy" && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				link.l5 = "Escucha, dama artesana, sé que tu gente es experta en pociones y venenos. Me dijeron que podrías estar interesada en esta planta. Échale un vistazo. ¿Qué opinas?";
				link.l5.go = "mangarosa";
			}
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy_trade" && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				link.l5 = "Hola, ojitos oscuros, tengo algo para ti... Esto es mangarosa. ¿Quieres comprar un poco??";
				link.l5.go = "mangarosa_trade1";
			}
			// <-- мангароса
			link.l2 = "¿Puedes adivinar mi futuro?";
			link.l2.go = "guess";
			link.l3 = RandPhraseSimple("Tengo una pregunta para ti.", "Necesito información.");
			link.l3.go = "quests"; //(перессылка в файл города)
			npchar.quest.meeting = "1";
		}
		// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_Start") && !CheckAttribute(pchar, "questTemp.DWH_gipsy") && npchar.city == "SentJons")
			{
				link.l6 = "Escucha, cejinegra, escuché que curas a las personas, incluso de enfermedades graves. ¿Es cierto?";
				link.l6.go = "dwh_gypsy_1";
			}
			// <-- Тёмные воды исцеления
		if (!CheckAttribute(npchar, "quest.poison_price") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && rand(2) == 0)
		{
			link.l4 = "Hola, ojos oscuros, ¿tienes algún veneno para ratas? Están siendo un maldito fastidio en mi barco.";
			link.l4.go = "get_poison_1";
		}
		NextDiag.TempNode = "First time";
		break;

		//-------------------------------------------------гадание-------------------------------------------------
	case "guess":
		dialog.text = "Por supuesto, guapo. Dame unas monedas y muéstrame tu mano derecha. Te contaré sobre tu futuro y te ayudaré a evitar desastres. ¡Nunca engaño! ¡Garantía de devolución del dinero!";
		link.l1 = "Siento que esta es la parte donde tu compatriota me roba... He cambiado de opinión. No estoy de humor.";
		link.l1.go = "exit";
		link.l2 = "¿Cuánto dinero quieres?";
		link.l2.go = "guess_1";
		break;

	case "guess_1":
		dialog.text = "Ah querido, tanto, cuanto tu bolsa de monedas permita y tu corazón desee. ¡Cuantas más piezas de a ocho, más lejos puedo ver en el futuro!";
		link.l1 = "100 pesos";
		link.l1.go = "guess_rate_1";
		link.l2 = "500 pesos";
		link.l2.go = "guess_rate_2";
		link.l3 = "1000 pesos";
		link.l3.go = "guess_rate_3";
		link.l4 = "5000 pesos";
		link.l4.go = "guess_rate_4";
		break;

		sTemp = GuessText();
	case "guess_rate_1": // никаких плюшек
		if (sti(pchar.money) >= 100)
		{
			AddMoneyToCharacter(pchar, -100);
			dialog.text = "¡Ah, gracias por tu caridad, mi apuesto joven halcón! Ahora escucha:  " + sTemp + " ";
			link.l1 = LinkRandPhrase("¡Je! Eso es muy interesante. Lo consideraré...", "¿De veras? Lo consideraré...", "¿Oh, de verdad? ¿Hablas en serio? Recordaré eso...");
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "La desgracia más fea e inevitable te espera. ¡Maldice al burlón! ¡Que nubes oscuras se reúnan sobre ti y que el castigo te encuentre!";
			link.l1 = "¡Ja, ja! ¿De verdad pensaste que te daría dinero, bruja gitana? ¡Fuera de mi camino! ¡Espero que la Inquisición te atrape!";
			link.l1.go = "guess_exit";
		}
		break;

	case "guess_rate_2": // немного в везение или скрытность
		if (sti(pchar.money) >= 500)
		{
			AddMoneyToCharacter(pchar, -500);
			dialog.text = "¡Ah, gracias, mi apuesto joven halcón! Ahora escucha:" + sTemp + "";
			link.l1 = LinkRandPhrase("¡Je! Eso es muy interesante. Lo consideraré...", "¿De veras? Lo consideraré...", "¿Oh, de veras? ¿Hablas en serio? Bueno, recordaré eso...", "¡Eh, ya me siento mejor!");
			link.l1.go = "exit";
			if (hrand(1) == 0)
				AddCharacterExpToSkill(pchar, "Fortune", 30 + rand(10)); // везение
			else
				AddCharacterExpToSkill(pchar, "Sneak", 30 + rand(10)); // скрытность
		}
		else
		{
			dialog.text = "¡La desgracia más fea e inevitable te está esperando. ¡Maldito sea el burlón! ¡Que las nubes oscuras se reúnan sobre ti y que el castigo te encuentre!";
			link.l1 = "¡Ja, ja! ¿Realmente pensaste que te daría dinero, bruja gitana? ¡Fuera de mi camino! ¡Espero que la Inquisición te lleve!";
			link.l1.go = "guess_exit";
		}
		break;

	case "guess_rate_3": // здоровье + везение или скрытность, харизма
		if (sti(pchar.money) >= 1000)
		{
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "¡Ah, gracias por tu plata, mi apuesto joven halcón! Ahora escucha:" + sTemp + "";
			link.l1 = LinkRandPhrase("¡Eh! Eso es muy interesante. Lo consideraré...", "¿En serio? Lo consideraré...", "¿Oh, de veras? ¿Hablas en serio? Bueno, recordaré eso...");
			link.l1.go = "exit";
			AddCharacterHealth(pchar, 1);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (hrand(1) == 0)
				AddCharacterExpToSkill(pchar, "Fortune", 50 + rand(20)); // везение
			else
				AddCharacterExpToSkill(pchar, "Sneak", 50 + rand(20)); // скрытность
		}
		else
		{
			dialog.text = "El infortunio más feo e inevitable te está esperando. ¡Maldice al burlón! ¡Que se reúnan nubes oscuras sobre ti y que el castigo te encuentre!";
			link.l1 = "¡Ja-ja! ¿De verdad pensaste que te daría dinero, bruja gitana? ¡Quítate de mi camino! ¡Espero que la Inquisición te lleve!";
			link.l1.go = "guess_exit";
		}
		break;

	case "guess_rate_4": // умения в оружие, везение+скрытность, здоровье, харизма
		if (sti(pchar.money) >= 5000)
		{
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "¡Oh la la! ¡Gracias por tu generosidad, mi apuesto joven halcón! Ahora escucha:" + sTemp + "";
			link.l1 = LinkRandPhrase("¡Je! Eso es muy interesante. Consideraré eso...", "¿De veras? Lo consideraré...", "¿Oh, de veras? ¿Hablas en serio? Bueno, recordaré eso...");
			link.l1.go = "exit";
			AddCharacterHealth(pchar, 2);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			AddCharacterExpToSkill(pchar, "Fortune", 50 + rand(100)); // везение
			AddCharacterExpToSkill(pchar, "Sneak", 50 + rand(50));	  // скрытность
			AddComplexSelfExpToScill(20, 20, 20, 20);
		}
		else
		{
			dialog.text = "El ineludible infortunio más feo te espera. ¡Maldito sea el burlón! ¡Que las nubes oscuras se reúnan sobre ti y que el castigo te encuentre!";
			link.l1 = "¡Ja, ja! ¿De verdad pensaste que te daría dinero, bruja gitana? ¡Quítate de mi camino! ¡Espero que la Inquisición te atrape!";
			link.l1.go = "guess_exit";
		}
		break;

	case "guess_exit":
		DialogExit();
		AddCharacterHealth(pchar, -10);
		LAi_CharacterDisableDialog(npchar);
		break;
		//<-- гадание

		// --> продажа мышьяка
	case "get_poison_1":
		npchar.quest.poison_price = (hrand(3) + 1) * 10;
		if (hrand(10) == 3 || IsCharacterPerkOn(pchar, "Trustworthy"))
		{
			dialog.text = LinkRandPhrase("¡Oh, no estoy segura, guapo! No hace mucho hubo un tipo pidiendo ayuda para matar ratas, y luego alguien envenenó a los soldados en el fuerte. Se puso bastante caliente para mi gente en la isla mientras los guardias nos interrogaban durante dos semanas hasta que encontraron al asesino. Era un espía enemigo.", "¿Y cómo puedo estar seguro de tu propósito? ¿Quizás solo quieres envenenar a un noble al que eres demasiado cobarde para enfrentar en un duelo honorable?", "Me han dicho que alguien envenenó a un comerciante en la taberna y robó todas sus pertenencias. El hombre sufrió mucho tiempo antes de expirar. Espuma salió de su boca y se puso morado como una berenjena... ¿Eres tú el responsable de eso, mi amor?");
			link.l1 = "¡Vosotras, gitanas, ciertamente os gusta compartir vuestras opiniones! No te preocupes, muchacha, no voy a envenenar a la gente. Esa es una manera femenina de matar, no es mi estilo. Para los hombres tengo mi espada, pero no puedo manejar a esas malditas ratas.";
			link.l1.go = "get_poison_2";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
				notification("Trustworthy", "Trustworthy");
		}
		else
		{
			dialog.text = "¡Estás tratando de atraparme! No señor, no tengo ningún veneno. Tengo plantas y pociones, pero no venenos.";
			link.l1 = "Lo que sea entonces. No me eches el mal de ojo.";
			link.l1.go = "exit";
			notification("Perk Check Failed", "Trustworthy");
		}
		break;

	case "get_poison_2":
		dialog.text = "¡Oh, apuesto, tan galante caballero! (susurrando) Págame " + sti(npchar.quest.poison_price) + "doblones.";
		if (PCharDublonsTotal() >= sti(npchar.quest.poison_price))
		{
			link.l1 = "Caray... Más vale que esto funcione.";
			link.l1.go = "get_poison_4";
		}
		else
		{
			link.l1 = "¡De ninguna manera! ¡Compré lo mismo en casa por cinco pistolas! ¡Podría atrapar cada rata yo mismo por tanto dinero!";
			link.l1.go = "get_poison_3";
		}
		break;

	case "get_poison_3":
		dialog.text = "Entonces atrápalos tú mismo y no me molestes. La próxima vez llamaré a la guardia.";
		link.l1 = "No hay necesidad de los guardias, bruja, me voy.";
		link.l1.go = "exit";
		break;

	case "get_poison_4":
		PlaySound("interface\important_item.wav");
		RemoveDublonsFromPCharTotal(sti(npchar.quest.poison_price));
		TakeNItems(pchar, "rat_poison", 1);
		DialogExit();
		break;
		// <-- продажа мышьяка

		// --> Мангароса
	case "mangarosa":
		dialog.text = LinkRandPhrase("Muéstrame la planta, querida... Hm... Supongo que puedo comprártela. Trescientas piezas de a ocho, ¿de acuerdo?", "Muéstramelo, guapo... Je... Bueno, puedo pagar doscientos y medio por ello.", "Veamos... ¡Oh! ¡Un ejemplo interesante! ¡Doscientos pesos! ¿Trato hecho?") "";
		link.l1 = LinkRandPhrase("Oh Señor... ojos oscuros, no soy un palurdo. Conozco esta planta. Es mangarosa...", "¿Oh, de veras?! Este es un espécimen perfecto de mangarosa. No intentes engañarme, gitano.", "Ajá, y supones que te daré esta mangarosa por una suma tan ínfima.");
		link.l1.go = "mangarosa_1";
		break;

	case "mangarosa_1":
		dialog.text = "Está bien, está bien, guapo. Veo que sabes algo sobre esta planta. Cincuenta doblones. Dámela.";
		link.l1 = "¡Un momento! Quiero saber cómo se puede usar y para qué. ¿Puedes contarme sobre eso? ¡Todos tus compatriotas están dispuestos a pagar mucho oro por este pequeño arbusto!";
		link.l1.go = "mangarosa_2";
		break;

	case "mangarosa_2":
		// тут работает харизма
		if (sti(pchar.questTemp.Mangarosa.g_count) == 5 || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 10 + hrand(25) + hrand(30, "1"))
		{
			dialog.text = "Hm... Supongo que no es tan malo si te cuento un poco al respecto. No podrás hacer nada con esta planta sin habilidades especiales.";
			link.l1 = "Estoy escuchando.";
			link.l1.go = "mangarosa_3";
		}
		else
		{
			dialog.text = LinkRandPhrase("Mi gente podría pagar mucho oro, pero nunca revelarían sus secretos.", "El oro es oro y los secretos son secretos, joven... ", "Sí, estamos dispuestos a pagar pero no a contar.") + "¿Entonces me vas a vender tu mangarosa? Cincuenta doblones es nuestra tarifa, nadie te pagará más.";
			link.l1 = "Oh, está bien... De todas formas me funciona. Cincuenta doblones. Tómalo";
			link.l1.go = "mangarosa_trade";
			link.l2 = "Entiéndeme, no quiero venderlo. Quiero saber por qué lo necesitas. Comparte tu conocimiento conmigo y te lo daré gratis.";
			link.l2.go = "mangarosa_exit";
		}
		break;

	case "mangarosa_trade":
		RemoveItems(pchar, "cannabis7", 1);
		TakeNItems(pchar, "gold_dublon", 50);
		PlaySound("interface\important_item.wav");
		dialog.text = "Toma tus monedas, joven halcón. Y una cosa más, tráenos más de estas plantas. Pero solo podemos comprarlas de una en una porque no llevamos grandes sumas con nosotros. Los guardias no confían en nuestro tipo y les gusta molestarnos...";
		link.l1 = "Está bien. Si encuentro más, lo traeré.";
		link.l1.go = "mangarosa_trade_exit";
		break;

	case "mangarosa_trade_exit":
		DialogExit();
		npchar.quest.mangarosa = "true";
		DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
		pchar.questTemp.Mangarosa = "gipsy_trade";
		AddQuestRecord("Mangarosa", "3");
		break;

	case "mangarosa_exit":
		dialog.text = LinkRandPhrase("¡De ninguna manera! Si no quieres venderlo, entonces no lo hagas. No te diré nada.", "¡No revelaré nuestros secretos a un forastero gorger! (escupe) ¿No quieres venderlo? Al infierno contigo.", "Amigo, eso no es para tus oídos. ¿No quieres venderlo por cincuenta doblones? Ve y véndeselo a la chica comerciante por doscientos pesos.");
		link.l1 = LinkRandPhrase("¡Qué pena para ti entonces! Otro de los tuyos me lo contará de todos modos. Y ella recibirá esta planta como regalo. ¡Nos vemos!", "¿Por qué tan terco? Si no me lo dices tú, entonces lo hará la otra. Y ella recibirá esta mangarosa como regalo. Adiós.", "Tu aliento apesta a ajo. Conseguiré lo que quiero eventualmente. Otro de tu raza será más hablador y conseguirá la planta gratis. Nos vemos.");
		link.l1.go = "exit";
		npchar.quest.mangarosa = "true";
		pchar.questTemp.Mangarosa.g_count = sti(pchar.questTemp.Mangarosa.g_count) + 1;
		break;

	case "mangarosa_trade1":
		dialog.text = "¿Y por qué preguntas, halcón? ¡Claro! Dámelo.";
		link.l1 = "Dame cincuenta doblones.";
		link.l1.go = "mangarosa_trade1_1";
		link.l2 = "¡Ups! Parece que lo he perdido o lo he olvidado en mi barco. Qué pena. Adiós...";
		link.l2.go = "exit";
		npchar.quest.mangarosa = "true";
		break;

	case "mangarosa_trade1_1":
		RemoveItems(pchar, "cannabis7", 1);
		TakeNItems(pchar, "gold_dublon", 50);
		PlaySound("interface\important_item.wav");
		dialog.text = "No te preocupes, no te engañaré. Toma tus monedas.";
		link.l1 = "Toma tu mangarosa. Traeré más si encuentro.";
		link.l1.go = "exit";
		break;

	case "mangarosa_3":
		dialog.text = "Molemos los brotes de esta manera especial, luego los secamos, sacamos las semillas y los tallos, luego los mezclamos con tabaco, llenamos nuestras pipas y fumamos la mezcla. Y obtenemos un... efecto inolvidable. Como la embriaguez con alcohol, pero sin dolor de cabeza después. Una planta es suficiente para dos docenas de pipadas.";
		link.l1 = "¡Ahora lo veo! ¿Puedes enseñarme esta técnica secreta? Puedo pagarte bien...";
		link.l1.go = "mangarosa_4";
		break;

	case "mangarosa_4":
		dialog.text = "Joven halcón, créeme, no necesitas esto. No te involucres, la planta te arruinará. Embota la mente y te hace engordar. Ni siquiera me preguntes. Pero... veo a un hombre valiente frente a mí, con una espada, un hombre del mar... ¿incluso un capitán, tal vez?";
		link.l1 = "Tienes razón.";
		link.l1.go = "mangarosa_5";
		break;

	case "mangarosa_5":
		dialog.text = "Escucha entonces. Mangarosa puede ser utilizada para cosas mucho más nobles y puede que la encuentres útil. Una de nuestras curanderas conoce todos sus secretos. Ella es a quien necesitas\nDame la planta y te diré su nombre y dónde encontrarla. Convencerla de que comparta sus secretos contigo, sin embargo, será tu problema.";
		link.l1 = "Está bien. Toma la planta y dime cómo encontrar a tu mago gitano.";
		link.l1.go = "mangarosa_6";
		break;

	case "mangarosa_6":
		RemoveItems(pchar, "cannabis7", 1);
		PlaySound("interface\important_item.wav");
		dialog.text = "Su nombre es Amelia. Vive sola en una pequeña casa entre las dunas no lejos del mar, en algún lugar de la costa suroeste de Tierra Firme española, como dicen los sabios.";
		link.l1 = "Por el amor de Dios, ¿puedes ser más específico?";
		link.l1.go = "mangarosa_7";
		break;

	case "mangarosa_7":
		dialog.text = "Eres un marinero, valiente halcón, y yo no lo soy. Búscala donde te dije. Su casa está muy cerca de la costa del mar. Está cerca de una bahía en Tierra Firme, al suroeste, los marineros deben conocerla.";
		link.l1 = "Está bien, intentaré encontrarla...";
		link.l1.go = "mangarosa_8";
		break;

	case "mangarosa_8":
		dialog.text = "Llévale una Mangarosa o ni siquiera hablará contigo. Y no te olvides de llevar doblones tampoco, ni pienses que te enseñará gratis.";
		link.l1 = "Qué avaricia. Lo consideraré. ¡Gracias por tu historia!";
		link.l1.go = "mangarosa_9";
		break;

	case "mangarosa_9":
		DialogExit();
		npchar.quest.mangarosa = "true";
		DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
		pchar.questTemp.Mangarosa = "amelia";
		pchar.questTemp.Mangarosa.Tell = "true"; // калеуче
		AddQuestRecord("Mangarosa", "4");
		// создаем и ставим Амелию
		sld = GetCharacter(NPC_GenerateCharacter("Amelia", "gipsy_3", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
		SetFantomParamFromRank(sld, 10, true);
		sld.name = "Amelia";
		sld.lastname = "";
		sld.dialog.FileName = "Quest\Mangarosa.c";
		sld.dialog.currentnode = "amelia";
		// sld.greeting = "";
		LAi_SetOwnerType(sld);
		LAi_SetImmortal(sld, true);
		ChangeCharacterAddressGroup(sld, "Amelia_house", "barmen", "stay");
		break;
		
		// --> Тёмные воды исцеления
		case "dwh_gypsy_1":
			dialog.text = "Verdad, "+GetSexPhrase("cariño","hermosa")+". Para cada dolencia tengo mi propio enfoque. He puesto en pie a plebeyos, ricos y mercaderes. Incluso el gobernador ha recurrido a mis pociones cuando nadie más podía ayudar. Las enfermedades no temen al oro, pero no pueden resistir mis brebajes.";
			link.l1 = "Entonces, ¿por qué te niegas a curar a la niña gravemente enferma, la hija de Thomas Morrison?";
			link.l1.go = "dwh_gypsy_2";
			pchar.questTemp.DWH_gipsy = true;
		break;

		case "dwh_gypsy_2":
			dialog.text = "¿Quién te contó semejante tontería, "+GetSexPhrase("halconcito","palomita")+"? No me opongo a ayudar, pero su padre mismo me echó de la casa. Ya habíamos acordado que me encargaría del tratamiento, pero de repente cambió. Me echó por la puerta como si fuera un enemigo mortal.";
			link.l1 = "¿Es así? Entonces, ¿él mismo condenó a su hija al sufrimiento?";
			link.l1.go = "dwh_gypsy_2_1";
		break;

		case "dwh_gypsy_2_1":
			dialog.text = "¿Qué dices? Es un padre atento, cuesta imaginar por qué habría actuado así.";
			link.l1 = "¿Has intentado hablar con él de nuevo?";
			link.l1.go = "dwh_gypsy_3";
		break;

		case "dwh_gypsy_3":
			dialog.text = "No me deja acercarme a la casa. Escucha, "+GetSexPhrase("cariño","hermosa")+", si te importa el destino de una pobre chica, ¿quizás podrías intentar averiguar qué pasa? Habla con Thomas, ayúdame a salvar a la niña del sufrimiento.";
			link.l1 = "Por supuesto, ayudaré. ¿Dónde puedo encontrar a Thomas?";
			link.l1.go = "dwh_gypsy_4";
			link.l2 = "No, cejas negras. Sea como sea, creo que su padre tiene buenas razones para rechazar tu ayuda. No voy a involucrarme en esto. Que él decida por sí mismo, después de todo es su hija.";
			link.l2.go = "dwh_gypsy_otkaz";
		break;

		case "dwh_gypsy_otkaz":
			DialogExit();
			CloseQuestHeader("DWH");
		break;

		case "dwh_gypsy_4":
			dialog.text = "Su casa está junto al muro, en la parte norte de la ciudad, al lado de una lujosa mansión con columnas. Ve, "+GetSexPhrase("halconcito","palomita")+", habla con él y vuelve conmigo.";
			link.l1 = "Volveré pronto.";
			link.l1.go = "dwh_gypsy_5";
		break;

		case "dwh_gypsy_5":
			DialogExit();
			
			AddQuestRecord("DWH", "2");
			
			sld = GetCharacter(CreateCharacterClone(npchar, -1));
			sld.id = "DWH_gypsy";
			npchar.lifeday = 0;
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_Tomas", "citiz_13", "man", "man", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Thomas";
			sld.lastname = "Morrison";
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas";
			ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "goto", "goto1");
			sld.City = "SentJons";
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- Тёмные воды исцеления

	// замечание по обнажённому оружию от персонажей типа citizen
	case "CitizenNotBlade":
		dialog.text = NPCharSexPhrase(NPChar, "Escúchame, valiente halcón, puede que sea gitano, pero incluso nosotros condenamos la violencia abierta. Por favor, envaina tu espada.", "Escúchame, valiente halcón, como ciudadano de este pueblo te pido que envaines tu espada.");
		link.l1 = LinkRandPhrase("Bien.", "Como desees.", "Como usted diga...");
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}

string GuessText()
{
	string sText;
	switch (hrand(19))
	{
	case 0:
		sText = "tendrás suerte, valiente joven halcón, ¡mañana tendrás suerte con las cartas!" break;
	case 1:
		sText = "¡la fortuna será benévola con usted en su negocio mercantil, capitán!" break;
	case 2:
		sText = "hay una desgracia esperándote en alta mar, te está esperando, ¡espera tres días!" break;
	case 3:
		sText = "Veo que necesitas pedir ayuda a tus más allegados, ¡no lo conseguirás solo en tu próxima lucha!" break;
	case 4:
		sText = "ve y enciende una vela en una iglesia, has sido maldecido por tu enemigo. ¡No lo lograrás sin la ayuda de Dios!" break;
	case 5:
		sText = "vas a perder mucho pronto, mi halcon, pero no desesperes y espera por ti mismo, busca ayuda de tus amigos..." break;
	case 6:
		sText = "te espera una dura derrota en el mar, pero veo que tú, capitán, sabrás sobrellevarla aunque no consigas lo que quieres." break;
	case 7:
		sText = "¡ha entrado en la meta de la desgracia, capitán! Visite un burdel y descanse un poco." break;
	case 8:
		sText = "conseguirá lo que quiere, capitán, pero no espere nada bueno de ello. Todo lo que ha deseado con tanta pasión, capitán, sólo le traerá cosas malas, así que será mejor que cambie de planes." break;
	case 9:
		sText = "Veo que hay una señal en esa cara tuya, la señal de la suerte suprema. ¡Recibirás más de lo que esperas recibir, jovencito!" break;
	case 10:
		sText = "tienes que evaluar tu deseo una vez más y decidir. ¿Realmente lo necesita? Tu destino te da la oportunidad de recapacitar." break;
	case 11:
		sText = "es una suerte rara, no todos los días tenemos la oportunidad de recapacitar. Descansa unos días, con los ojos brillantes, piensa las cosas. ¡No te apresures a morir!" break;
	case 12:
		sText = "aunque todos tus esfuerzos no te den el resultado esperado, no desesperes, joven halcón, la gran suerte te espera en el día más inesperado, ¡no la pierdas!" break;
	case 13:
		sText = "tu problema no se solucionará de forma positiva pero eres un cabezota y conseguirás lo que quieres pero, quizás, no desde el lugar que esperabas." break;
	case 14:
		sText = "será mejor que te olvides del negocio que te traes entre manos. Nunca tendrás suerte en esto y si sigues en ello, tal vez tu gente más cercana resulte herida o muerta." break;
	case 15:
		sText = "hay un acontecimiento que le espera, capitán, y que cambiará por completo su vida. Sus preocupaciones recientes perderán todo su significado para usted después de eso." break;
	case 16:
		sText = "hay peligro en el camino hacia tu sueño, capitán, y debes ser muy afortunado si consigues lo que quieres sin grandes pérdidas. Es mejor apartarse y olvidar su sueño inalcanzable. O tal vez, este destino podría ser engañado si pierdes en las cartas o los dados ahora mismo..." break;
	case 17:
		sText = "Veo en ti un poder fuerte como una roca y una luz tan brillante como la estrella polar que guía a la gente. ¡Te esperan buenas noticias!" break;
	case 18:
		sText = "una mala señal se levanta en tu camino, teme al mal de ojo y mantén a los hombres leales cerca de ti." break;
	case 19:
		sText = "un acontecimiento afortunado se levanta en tu camino justo a tus espaldas. Busca lo bueno que te llega directamente y no persigas lo inalcanzable." break;
	}
	return sText;
}
